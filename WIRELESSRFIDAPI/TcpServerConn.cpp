#include "StdAfx.h"
#include "TcpServerConn.h"
#include "RFIDReaderServer.h"
#include <process.h>

DWORD WINAPI StartServerThread(LPVOID p)
{
	CTcpServerConn *pThis = (CTcpServerConn*)p;

	while( !pThis->IsUserExit() )
	{
		if (!pThis->Svr())
		{
			Sleep(500);
		}		
	}

	pThis->CloseThreadHandle();	
	return 0;
}


CTcpServerConn::CTcpServerConn(void)
{
	m_hThread = NULL;
	m_bThExit = false;


	mListenSock = INVALID_SOCKET;
	mPort = 0;
	mCRFIDReaderServer = NULL;
}

CTcpServerConn::~CTcpServerConn(void)
{
	Quit();
}

bool CTcpServerConn::Init(char *pHostName,int nsocketPort,CRFIDReaderServer* pCRFIDReaderServer)
{
	mListenSock = INVALID_SOCKET;	
	mCRFIDReaderServer = pCRFIDReaderServer;
	mPort = nsocketPort;
	mIpAddr = pHostName;
	return true;
}

bool CTcpServerConn::Quit()
{
	StopListen();
	mCRFIDReaderServer = NULL;

	return true;
}

bool CTcpServerConn::StartListen()
{
	if (m_hThread)
	{
		return false;
	}

	WSADATA wsaData;
    if (WSAStartup(0x0202, &wsaData)!=0)
    {
        return false;
    }
    mListenSock =socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

	if (mListenSock == INVALID_SOCKET)
	{
		WSACleanup();
		return false;
	}

	//设置socket为非锁定模式,ul为0值的话，那么socket将被设置为锁定模式
	//*
	unsigned long ul = 1;
	if( SOCKET_ERROR == ioctlsocket(mListenSock,FIONBIO,(unsigned long*)&ul) ) 
	{
		closesocket(mListenSock);	
		SetErrorCode( ERR_SOCKET_ERR );			//SOCKET出错	
		return false;
	}
	//*/

    SOCKADDR_IN addrSrv;
    addrSrv.sin_addr.S_un.S_addr=inet_addr(mIpAddr.c_str());
    addrSrv.sin_family=AF_INET;
    addrSrv.sin_port=htons(mPort);
	int bindRet = bind(mListenSock,(SOCKADDR*)&addrSrv,sizeof(SOCKADDR)) ;
	if(bindRet == SOCKET_ERROR)
	{
		closesocket(mListenSock);	
		return false;
	}

    if (listen(mListenSock,5) == SOCKET_ERROR)
    {

    }

	return StartThread();
}

bool CTcpServerConn::StopListen()
{
	closesocket(mListenSock);
	mListenSock = INVALID_SOCKET;
	CloseThread();	
	return true;
}

bool CTcpServerConn::StartThread()
{
	if( NULL == m_hThread )
	{
		m_bThExit = false;
		m_hThread = (HANDLE)_beginthreadex(NULL,
			0,
			(PBEGINTHREADEX_THREADFUNC)StartServerThread,
			(LPVOID)this,
			0,
			NULL);
		if (NULL == m_hThread)
		{
			SetErrorCode(ERR_STARTREVTHREAD_FAIL);
			return false;
		}	
		return true;
	}
	
	return false;
}


bool CTcpServerConn::CloseThread()
{
	if( m_hThread != NULL )
	{	
		m_bThExit = true; //关闭线程
		m_ThreadExitEvent.WaitEvent(5000);
		m_hThread  = NULL;
	}
	return true;
}

bool CTcpServerConn::IsUserExit()
{
	return m_bThExit;
}

bool CTcpServerConn::CloseThreadHandle()
{
	bool retB = (CloseHandle(m_hThread) == TRUE);
	m_hThread = NULL;
	m_ThreadExitEvent.SetEvent();
	return retB;
}

void CTcpServerConn::SetErrorCode(int nErrorCode,bool bCommandError /*= false*/)
{

}

bool CTcpServerConn::Svr()
{
	fd_set rfds;
	timeval timevalue;
	FD_ZERO(&rfds);
	FD_SET(mListenSock, &rfds);
	int retval = select(FD_SETSIZE, &rfds, NULL, NULL, &timevalue);
	int len=sizeof(SOCKADDR);	
	SOCKET sockConn = accept(mListenSock,(SOCKADDR*)&mAddrClient,&len);
	if(sockConn != SOCKET_ERROR)
	{
		mCRFIDReaderServer->CreateReaderThread(sockConn,mAddrClient);
		return true;
	}	
	return false;
}
