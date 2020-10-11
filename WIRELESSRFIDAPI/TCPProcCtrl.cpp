#include "StdAfx.h"
#include "TCPProcCtrl.h"
#include <process.h>
#include <Winsock2.h>
#include "RFIDReader.h"


DWORD WINAPI StartTCPProcThread(LPVOID p)
{
	CTCPProcCtrl *pThis = (CTCPProcCtrl*)p;

	while( !pThis->IsUserExit() )
	{
		if (!pThis->Svr())
		{
			Sleep(50);
		}
		
	}

	pThis->CloseThreadHandle();	
	return 0;
}


CTCPProcCtrl::CTCPProcCtrl(CRFIDReader* pReader)
:ConnetBase(pReader)
{
	m_hThread = NULL;
	mSocket = INVALID_SOCKET;
	m_bThExit = false;
}


CTCPProcCtrl::~CTCPProcCtrl(void)
{
	closesocket(mSocket);
	CloseThread();	
}


bool CTCPProcCtrl::StartThread()
{
	if( NULL == m_hThread )
	{
		m_bThExit = false;
		m_hThread = (HANDLE)_beginthreadex(NULL,
			0,
			(PBEGINTHREADEX_THREADFUNC)StartTCPProcThread,
			(LPVOID)this,
			0,
			NULL);
		if (NULL == m_hThread)
		{
			//SetErrorCode(ERR_STARTREVTHREAD_FAIL);
			return false;
		}
		return true;
	}
	return false;
}


bool CTCPProcCtrl::CloseThread()
{
	m_bThExit = true; //�ر��߳�
	if( m_hThread != NULL )
	{
		m_ThreadExitEvent.WaitEvent(1000);
	}
	return true;
}

bool CTCPProcCtrl::IsUserExit()
{
	return m_bThExit;
}

bool CTCPProcCtrl::CloseThreadHandle()
{
	bool retB = CloseHandle(m_hThread);
	m_hThread = NULL;
	m_ThreadExitEvent.SetEvent();
	return retB;
}

bool CTCPProcCtrl::StartRead()
{
	return StartThread();	
}

bool CTCPProcCtrl::StopRead()
{
	return CloseThread();
}

bool CTCPProcCtrl::Svr()
{
	int byteRecv = SOCKET_ERROR;

	byteRecv = recv(mSocket,pForRev,256,0);	
	if (byteRecv == SOCKET_ERROR)
	{
		byteRecv = 0;	
	}

	bool bRet = mReader->MsgProcess((unsigned char*)pForRev,byteRecv);
	bool RetB = bRet; 
	while(bRet)
	{
		bRet = mReader->MsgProcess((unsigned char*)pForRev,0);
		if (!bRet)
		{
			break;
		}
	}

	return RetB;	
}


bool CTCPProcCtrl::UpdateSocket(SOCKET& sockConn)
{
	mSocket = sockConn;
	return true;
}

bool CTCPProcCtrl::SendMsg(unsigned char *pSendData, int dataLength)
{
	if(	NULL == pSendData )
	{
		SetErrorCode(ERR_POINTER_NULL);
		return false;
	}
	
	//����
	int totalFrameSize = dataLength;
	int leaveFrameSize = dataLength;
	int sendFrameSize = 0;
	int sendErrorTimes = 3;						//�趨Ϊ �ڳ���3��select���� Socketʱ������������, ���������
	unsigned char *pSendBuffer = pSendData;		//����ָ��
	int nCurrentSend = 0;

	while (leaveFrameSize)						//�����������û�н�����һ�η������
	{
		Sleep(50);
		AsynSend(mSocket,(char*)(pSendBuffer+sendFrameSize),leaveFrameSize,&nCurrentSend);
		sendFrameSize += nCurrentSend;
		leaveFrameSize = totalFrameSize - sendFrameSize;
		sendErrorTimes --;
		if ( 0 ==sendErrorTimes)
		{
			//SetErrorCode(ERR_TCPSEND_SOCKETOVERTIME);					//��������ʧ��
			return false;
		}
	}
	return true;
}

int CTCPProcCtrl::AsynSend(SOCKET RFIDSocket,char *buf,int nMaxSendLen,int *pSendLen)
{
	int nSendata = send(RFIDSocket,buf,nMaxSendLen,0);
	if( SOCKET_ERROR == nSendata )
	{
		SetErrorCode(ERR_TCPSEND_SOCKETERROR);
		return false;
	}
	*pSendLen = nSendata;
	return true;	
}

void CTCPProcCtrl::SetErrorCode(int nErrorCode,bool bCommandError /*= false*/)
{

}

