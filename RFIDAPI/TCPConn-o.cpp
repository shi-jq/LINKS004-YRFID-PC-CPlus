#include "StdAfx.h"
#include "TCPConn.h"
#include "comdef.h"
#include <process.h>
CTCPConn::CTCPConn()
{
	LastSendframeNum = 0x00;
	m_RevEvent = CreateEvent(NULL,FALSE,FALSE,NULL);	
	bExit = false;
}

CTCPConn::~CTCPConn(void)
{
}

//////////////////////////////////////////////////////////////////////////
//������:	�����Ӻ���
//����˵��:	��
//����ֵ:	�򿪳ɹ�ʱ���� true,
//////////////////////////////////////////////////////////////////////////
bool CTCPConn::OpenConn()
{
	//����豸
	errorProc.ClearErrorCode();
//	struct protoent *ppe; cxm delete
	unsigned long ul = 0;
//	ppe=getprotobyname("TCP");cxm delete
	WSADATA wsaData;
	if( 0 != WSAStartup(MAKEWORD(2,2),&wsaData) )
	{
		errorProc.SetErrorCode(ERR_INITSOCKET_FAIL);
		return false;
	}
	/*if(WSAGetLastError() != 0)
	{
		return false;
	}*/
	//����TCP socket
	RFIDSocket=socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);

	if (RFIDSocket==INVALID_SOCKET)	
	{
		return false;
	}

	//sockaddr_in����
	RFIDSAddr.sin_family=AF_INET;
	RFIDSAddr.sin_port=htons(RFIDSystemCfg.nSocketPort);
	RFIDSAddr.sin_addr.s_addr=inet_addr(RFIDSystemCfg.strHostName.c_str());

	//����socketΪ������ģʽ,ulΪ0ֵ�Ļ�����ôsocket��������Ϊ����ģʽ
	// nonblocking mode 

	if(ioctlsocket(RFIDSocket,FIONBIO,(unsigned long*)&ul)==SOCKET_ERROR ) 
	{
		closesocket(RFIDSocket);
		errorProc.SetErrorCode( ERR_SOCKET_ERR );			//SOCKET����
		isConn = false;
		return false;
	}
	//��������
	int result=connect(RFIDSocket,(struct sockaddr *)&RFIDSAddr,sizeof(RFIDSAddr));
	if (result == 0)
		return isConn = true;
	else
	{
		errorProc.SetErrorCode( ERR_CONNECT_FAIL);		//����ʧ��
		return false;
	}
}

//////////////////////////////////////////////////////////////////////////
//������:	����״̬��⺯��
//����˵��:	maxWaitTime ����ӳ�
//����ֵ:	���� true Ϊ��������״̬
//////////////////////////////////////////////////////////////////////////
bool CTCPConn::CheckConnState(int maxWaitTime)
{
	errorProc.ClearErrorCode();
	if (!isConn) //cxm fix
	{
		errorProc.SetErrorCode( ERR_CONNECT_FAIL);		//����ʧ��
		return false;
	}
	fd_set fdconn;
	struct timeval rto;									// ��ʱ�趨
	int ret;

	rto.tv_sec = maxWaitTime / 1000; 					//�趨��ʱ��λ  Ϊ ��
	rto.tv_usec =(maxWaitTime % 1000)*1000;				//����

	//Always clear the conn set before calling select()
	FD_ZERO(&fdconn);

	// Add socket s to the conn set
	FD_SET(RFIDSocket,&fdconn);

	ret=select(0,NULL,&fdconn,NULL,&rto);
	if( -1 == ret )
	{
		errorProc.SetErrorCode(ERR_TCPSEND_SOCKETERROR);
		return false;
	}
	if( 0 == ret )
	{
		errorProc.SetErrorCode( ERR_CONNECT_OUTTIME);
		return false;
	}
	if( ret > 0 )
	{
		if(FD_ISSET(RFIDSocket,&fdconn))
		{
			return true;
		}
	}		
	return false;

}

//////////////////////////////////////////////////////////////////////////
//������:	����֡���ͺ���
//����˵��:	pSendCommand ����ָ��, pSendData ��������, dataLength ���ݳ���
//����ֵ:	true Ϊ���ͳɹ�
//////////////////////////////////////////////////////////////////////////
bool CTCPConn::SendMsg(unsigned char *pSendCommand, unsigned char *pSendData, int dataLength)
{
	errorProc.ClearErrorCode();
	if( NULL == pSendCommand ||
		NULL == pSendData )
	{
		errorProc.SetErrorCode(ERR_POINTER_NULL);
		return false;
	}

	ClearPasBuffer();
	//װ��
	unsigned char pForSend[SENDFRAME_MAXBUF];
	int totalFrameSize = 0;
	if(! PackMsg(pSendCommand, pSendData, dataLength, pForSend,&totalFrameSize) )
	{
		return false;
	}
	
	//����
	int leaveFrameSize = totalFrameSize;
	int sendFrameSize = 0;
	int sendErrorTimes = 3;						//�趨Ϊ �ڳ���3��select���� Socketʱ������������, ���������
	unsigned char *pSendBuffer = pForSend;		//����ָ��
	int nCurrentSend = 0;

	while (leaveFrameSize)						//�����������û�н�����һ�η������
	{
		Sleep(50);
		AsynSend(RFIDSocket,(char*)(pSendBuffer+sendFrameSize),leaveFrameSize,&nCurrentSend);
		sendFrameSize += nCurrentSend;
		leaveFrameSize = totalFrameSize - sendFrameSize;
		sendErrorTimes --;
		if ( 0 ==sendErrorTimes)
		{
			//errorProc.SetErrorCode(ERR_TCPSEND_SOCKETOVERTIME);					//��������ʧ��
			return false;
		}
	}
	return true;
}


DWORD WINAPI CTCPConn::StartRevThread(LPVOID lParam)
{
	CTCPConn * pThis = (CTCPConn*)lParam;
	unsigned char pForRev[REC_FRAME_ONCE];
	int revQty = 0;
	int revErrorTimes = 10;			
	while(!pThis->bExit)
	{
		memset(pForRev,0,REC_FRAME_ONCE);
		pThis->AsynRec(pThis->RFIDSocket,(char*)pForRev,REC_FRAME_ONCE,&revQty);

		printData("\n���յ�ԭʼ����:",pForRev,revQty);
		//���, trueʱ��ʾ�ѽ����ݰ�����д��revFrame, false ��ʾ���ݰ�������
		if( !pThis->UnpackMsg( pForRev, revQty))				
		{
			OutputDebugString(L"�����հ�");
			continue;
		}
		printData("���������:",(LPBYTE)&(pThis->revFrame),pThis->revFrame.bLength+6);
		if (pThis->frameNum == (pThis->revFrame.bAddrInfo & 0x0f) )		//�ҵ��ظ�֡ cxm fix
		{	
			SetEvent(pThis->m_RevEvent);
			break;
		}

		OutputDebugString(L"֡ͷ����\n");
		if (pThis->revFrame.bFrame == 0 && (-- revErrorTimes == 0) )	//֡ͷΪ0 ʱ��ʾû���ٽ��ܵ��κ�������, ���ʾ֡��ʧ
		{
			pThis->errorProc.SetErrorCode(ERR_FRAME_LOSE);			//������֡��ʧ
			break;
		}
		//Sleep(pThis->nWaitTime / 10);
		Sleep(50);
	}

	return 0;
}



//////////////////////////////////////////////////////////////////////////
//������:	����֡���պ���
//����˵��:	pRevFrame���յ�����֡����CRFIDFrame��
//����ֵ:	true���ճɹ�
//////////////////////////////////////////////////////////////////////////
#ifdef CPLUSPLUS 
bool CTCPConn::RevMsg(CRFIDFrame &pRevFrame, int nWaitTime )
{
	unsigned char pForRev[REC_FRAME_ONCE];
	int revQty = 0;
	int revErrorTimes = 100;							//�����ڽ��յ�3�β��ǻظ�֡ʱ������������, ��ʾ֡�Ѷ�ʧ

	bool bResult = false;
	do 
	{
		-- revErrorTimes ;
		AsynRec(RFIDSocket,(char*)pForRev,REC_FRAME_ONCE,&revQty);
		if( 0 != revQty )
		{
			printData("���յ�ԭʼ����:",pForRev,revQty);
		}
		if( !UnpackMsg( pForRev, revQty) )				//���, trueʱ��ʾ�ѽ����ݰ�����д��revFrame, false ��ʾ���ݰ�������
		{
			if( 0 == revQty )
			{
				Sleep(nWaitTime / 100);	
			}
			continue;
		}
		//printData("���������:",pForRev,revQty);
		if (revFrame.bFrame == 0 && ( revErrorTimes == 0) )	//֡ͷΪ0 ʱ��ʾû���ٽ��ܵ��κ�������, ���ʾ֡��ʧ
		{
			errorProc.SetErrorCode(ERR_FRAME_LOSE);			//������֡��ʧ
			return false;
		}

		if (frameNum == (revFrame.bAddrInfo & 0x0f))
		{
			bResult = true;
			break;
		}
		Sleep(nWaitTime / 100);
	} while(revErrorTimes);
	printData("���������:",(unsigned char *)&revFrame,revFrame.bLength+6);

	if (revErrorTimes == 0)
	{
		ClearPasBuffer();
		memset((unsigned char*)&revFrame, 0 , sizeof(revFrame));
		errorProc.SetErrorCode(ERR_RECVTHREAD_OVERTIME);
		bResult = false;
	}
	pRevFrame = revFrame;						
	return bResult;
}
#else
bool CTCPConn::RevMsg(CRFIDFrame &pRevFrame, int nWaitTime )
{
	//errorProc.ClearErrorCode();
	//memset((void*)&pRevFrame,0,sizeof(revFrame));
	//bool bRet = false;
	//HANDLE m_hThread = (HANDLE)_beginthreadex(NULL,
	//	0,
	//	(PBEGINTHREADEX_THREADFUNC)StartRevThread,
	//	(LPVOID)this,
	//	0,
	//	NULL);
	//if (NULL == m_hThread)
	//{
	//	errorProc.SetErrorCode(ERR_STARTREVTHREAD_FAIL);
	//	return false;
	//}	
	////nWaitTime  �ȴ�ʱ�䣬һ��Ϊ2���ղ����������˳�
	////���ع���̫����2���ӻ����տ�����Ϣ��2���ղ��꣬�����˳���buffer����գ��ᱻ��Ϊ�ر�ʧ�ܣ���Ӧ��Ϊ5��
	//if( WAIT_OBJECT_0 == WaitForSingleObject(m_RevEvent,nWaitTime))
	//{
	//	memcpy((void*)&pRevFrame,(void*)&revFrame,sizeof(revFrame));
	//	return true;
	//}
	//errorProc.SetErrorCode(ERR_RECVTHREAD_OVERTIME);
	//bExit = true;
	//return false;

	unsigned char pForRev[REC_FRAME_ONCE];
	int revQty = 0;
	int revErrorTimes = nWaitTime;							//�����ڽ��յ�3�β��ǻظ�֡ʱ������������, ��ʾ֡�Ѷ�ʧ

	bool bResult = false;
	do 
	{
		AsynRec(RFIDSocket,(char*)pForRev,REC_FRAME_ONCE,&revQty);
		if( 0 != revQty )
		{
			printData("���յ�ԭʼ����:",pForRev,revQty);
		}
		if( !UnpackMsg( pForRev, revQty) )				//���, trueʱ��ʾ�ѽ����ݰ�����д��revFrame, false ��ʾ���ݰ�������
		{
			if( 0 == revQty )
			{
				Sleep(1);	
			}
			continue;
		}
		//printData("���������:",pForRev,revQty);
		if (revFrame.bFrame == 0 && ( revErrorTimes == 0) )	//֡ͷΪ0 ʱ��ʾû���ٽ��ܵ��κ�������, ���ʾ֡��ʧ
		{
			errorProc.SetErrorCode(ERR_FRAME_LOSE);			//������֡��ʧ
			return false;
		}

		if (frameNum == (revFrame.bAddrInfo & 0x0f))
		{
			bResult = true;
			break;
		}
		Sleep(1);
	} while(revErrorTimes--);
	printData("���������:",(unsigned char *)&revFrame,revFrame.bLength+6);
	
	if (revErrorTimes == 0)
	{
		ClearPasBuffer();
		memset((unsigned char*)&revFrame, 0 , sizeof(revFrame));
		errorProc.SetErrorCode(ERR_RECVTHREAD_OVERTIME);
		bResult = false;
	}
	pRevFrame = revFrame;						//���϶�,����ʱ�����޸�
	return bResult;
}
#endif
//////////////////////////////////////////////////////////////////////////
//������:	����֡��������պ���
//����˵��:	pSendCommand ����ָ��, pSendData ��������, dataLength ���ݳ���,pRevFrame���յ�����֡����CRFIDFrame��
//����ֵ:	true�����ɹ�
//////////////////////////////////////////////////////////////////////////
bool CTCPConn::SendNRevMsg(unsigned char *pSendCommand, unsigned char *pSendData, int dataLength, CRFIDFrame &pRevFrame,int nWaitTime)
{
	errorProc.ClearErrorCode();
	//int nTime;
	if(SendMsg(pSendCommand, pSendData, dataLength))
		return RevMsg(pRevFrame,nWaitTime);
	else
		return false;
}

//////////////////////////////////////////////////////////////////////////
//������:	�ر����Ӻ���
//����˵��:	��
//����ֵ:	��
//////////////////////////////////////////////////////////////////////////
bool CTCPConn::CloseConn()
{
	errorProc.ClearErrorCode();

	int result = closesocket(RFIDSocket);				//�ر�Socket
	WSACleanup();
	if (result == 0)
	{
		isConn = false;
		return true;
	}
	else
	{
		errorProc.SetErrorCode(ERR_CLOSE_FAIL);
		return false;
	}
}

//////////////////////////////////////////////////////////////////////////
//������:	��ȡ������Ϣ
//����˵��:	strErrorΪ���ش�����Ϣ
//����ֵ:	��
//////////////////////////////////////////////////////////////////////////
void CTCPConn::GetError(string& strError)
{
	errorProc.GetErrorMsg(strError);
}

//////////////////////////////////////////////////////////////////////////
//������:	��ȡ�������
//����˵��:	��
//����ֵ:	��
//////////////////////////////////////////////////////////////////////////
int CTCPConn::GetErrorCode()
{
	return errorProc.GetErrorCode();
}

//***********************************
//������:	�첽���պ���,��ʱʱ��2�� RECV_WAIT
//����˵��:	strErrorΪ���ش�����Ϣ
//����ֵ:	��
//***********************************
bool  CTCPConn::AsynRec(SOCKET RFIDSocket,char *buf,int nMaxRecLen,int *pRecvLen)
{
	
	*pRecvLen = 0;//

	fd_set fdread;
	struct timeval rto; // for receive data timeout setup

	rto.tv_sec = 0; 	//set timeout interval
	rto.tv_usec = SEND_WAIT;

	//Always clear the read set before calling select()
	FD_ZERO(&fdread);

	// Add socket s to the read set
	FD_SET(RFIDSocket,&fdread);
	int nRet = select(0,&fdread,NULL,NULL,&rto);
	switch (nRet)
	{
	case -1:  
		errorProc.SetErrorCode(ERR_TCPRECV_SOCKETERROR);
		return false;
	case 0:  
		errorProc.SetErrorCode(ERR_TCPRECV_SOCKETOVERTIME);
		return false;
	default:  
		if (!FD_ISSET(RFIDSocket,&fdread))					//���ڼ�����
		{  
			errorProc.SetErrorCode(ERR_TCPRECV_SOCKETERROR);
			return false;		
		}  

		int nReadData = recv(RFIDSocket,buf,nMaxRecLen,0);
		if( SOCKET_ERROR == nReadData )
		{
			errorProc.SetErrorCode(ERR_TCPRECV_SOCKETERROR);
			return false;
		}
		*pRecvLen = nReadData;
		return true;
	}
}

//*********************************
//������:	�첽���ͺ���,��ʱʱ��1�� SEND_WAIT
//����˵��:	strErrorΪ���ش�����Ϣ
//����ֵ:	��
//***********************************
int CTCPConn::AsynSend(SOCKET RFIDSocket,char *buf,int nMaxSendLen,int *pSendLen)
{
	fd_set fdwrite;
	struct timeval rto; // for receive data timeout setup
//	int ret;

	rto.tv_sec = 1; 	//set timeout interval
	rto.tv_usec = SEND_WAIT;     //200;

	//Always clear the read set before calling select()
	FD_ZERO(&fdwrite);

	// Add socket s to the read set
	FD_SET(RFIDSocket,&fdwrite);

	int nRet = select(0,NULL,&fdwrite,NULL,&rto);
	switch (nRet)
	{
	case -1:  
		errorProc.SetErrorCode(ERR_TCPSEND_SOCKETERROR);
		return false;
	case 0:  
		errorProc.SetErrorCode(ERR_TCPSEND_SOCKETOVERTIME);
		return false;
	default:  
		if (!FD_ISSET(RFIDSocket,&fdwrite))//���ڼ�����
		{  
			errorProc.SetErrorCode(ERR_TCPSEND_SOCKETERROR);
			return false;		
		}  

		int nSendata = send(RFIDSocket,buf,nMaxSendLen,0);
		if( SOCKET_ERROR == nSendata )
		{
			errorProc.SetErrorCode(ERR_TCPSEND_SOCKETERROR);
			return false;
		}
		*pSendLen = nSendata;
		return true;
	}
}

void CTCPConn::SetErrorCode(int nCode,bool isCommandError)
{
	errorProc.SetErrorCode(nCode,isCommandError);
}