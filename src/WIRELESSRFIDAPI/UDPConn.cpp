#include "StdAfx.h"
#include "UDPConn.h"
#include <process.h>
#include "RFIDReader.h"
#include "Global.h"


DWORD WINAPI StartUDPRevThread(LPVOID p)
{
	CUDPConn *pThis = (CUDPConn*)p;
	int nErrorTimes = 0;
	//收数据
	unsigned char pForRev[MAX_PATH] = {0};
	while( !pThis->m_bThExit )
	{
		memset(pForRev,0,MAX_PATH);
		int revQty = 0 ;
		if( !pThis->UDPRecv(pForRev,revQty) ) //200秒超时
		{
			Sleep(20);
		}

		nErrorTimes = 0 ; //有数据,则清错误次数
		if( pThis->mReader != NULL )
		{
			pThis->mReader->MsgProcess(pForRev,revQty);
		}	
	}

	CloseHandle(pThis->m_hThread);
	pThis->m_hThread = NULL;
	SetEvent(pThis->m_ThreadExitEvent);
	return 0;
}


CUDPConn::CUDPConn(CRFIDReader* pReader):
	ConnetBase(pReader)
{
	bExit = false;
	m_bOpened = false;
	m_hThread = NULL;
	m_bThExit = false;
	m_ThreadExitEvent = CreateEvent(NULL,FALSE,FALSE,NULL);
}

CUDPConn::~CUDPConn(void)
{
	CloseConn();
	if( NULL != m_ThreadExitEvent)
	{
		CloseHandle(m_ThreadExitEvent);
		m_ThreadExitEvent = NULL;
	}
}

bool CUDPConn::LoadConfig(char *pHostName,int nsocketPort)
{
	nSocketPort = nsocketPort;
	strHostName = pHostName;
	return true;
}

bool CUDPConn::StartRead()
{
	bool bRet = OpenConn();

	if (bRet)
	{
		bRet = Svr();
		if (!bRet)
		{
			ClosePort();
		}
	}

	return bRet;
}

bool CUDPConn::StopRead()
{
	return CloseConn();
}

bool CUDPConn::SendMsg(unsigned char *pSendData, int dataLength)
{
	if( !m_bOpened )
	{
		SetErrorCode(ERR_TCP_NOTOPEN);
		return false;
	}

	if(	NULL == pSendData )
	{
		SetErrorCode(ERR_POINTER_NULL);
		return false;
	}

	if( !Send(pSendData,dataLength) )
	{
		return false;
	}

	if( !Svr() )
	{
		return false;
	}

	return true;
}

bool CUDPConn::UDPRecv(unsigned char* pRecv,int& nSize)
{
	if(!m_bOpened)
	{
		SetErrorCode(ERR_TCP_NOTOPEN);
		return false;
	}

	return AsynRec(RFIDSocket,(char*)pRecv,UDP_FRAME_ONCE,&nSize);

}

bool CUDPConn::OpenConn()
{
	//检查设备
	WSADATA wsaData;
	if( 0 != WSAStartup(MAKEWORD(2,2),&wsaData) )
	{
		SetErrorCode(ERR_INITSOCKET_FAIL);
		return false;
	}

	//创建UDP socket
	RFIDSocket=socket(AF_INET,SOCK_DGRAM,0);

	if (RFIDSocket==INVALID_SOCKET)	
	{
		return false;
	}

	//sockaddr_in设置
	RFIDSAddr.sin_family=AF_INET;
	RFIDSAddr.sin_port=htons(nSocketPort);
	RFIDSAddr.sin_addr.s_addr=inet_addr(strHostName.c_str());


	m_bOpened = true;
	return true;
}

bool CUDPConn::Send(unsigned char *pSendData, int dataLength)
{
	//发包
	int totalFrameSize = dataLength;
	int leaveFrameSize = dataLength;
	int sendFrameSize = 0;
	int sendErrorTimes = 3;						//设定为 在出现3次select不到 Socket时结束程序运行, 跳向出错处理
	unsigned char *pSendBuffer = pSendData;		//发送指针
	int nCurrentSend = 0;

	while (leaveFrameSize)						//出现情况在于没有将数据一次发送完毕
	{
		Sleep(50);
		AsynSend(RFIDSocket,(char*)(pSendBuffer+sendFrameSize),leaveFrameSize,&nCurrentSend);
		sendFrameSize += nCurrentSend;
		leaveFrameSize = totalFrameSize - sendFrameSize;
		sendErrorTimes --;
		if ( 0 ==sendErrorTimes)
		{
			//SetErrorCode(ERR_TCPSEND_SOCKETOVERTIME);					//出错处理发送失败
			return false;
		}
	}
	return true;
}

bool CUDPConn::RevMsg(unsigned char *pRevMsg,unsigned char *pDataLen,int nWaitTime /*= 3000*/)
{
	if( 0 == nWaitTime)
	{
		nWaitTime +=3000;
	}

	unsigned char pForRev[COM_FRAME_ONCE];
	int revQty = 0;
	DWORD dwStart = GetTickCount();
	bool bRet = false;
	int nRecvDataLen = 0;

	do 
	{	
		//大于结束时间,结束
		if( GetTickCount() - dwStart >= ((DWORD)nWaitTime) ) 
		{
			break;
		}

		memset(pForRev,0,COM_FRAME_ONCE);

		UDPRecv(pForRev,revQty);
		//TRACE(_T("%d\n"),revQty);
		if( 0 == revQty )
		{
			Sleep(20);
			continue;
		}

		nRecvDataLen+=revQty;
		if( nRecvDataLen > *pDataLen ) //内存不够 
		{
			SetErrorCode(ERR_MOREDATA_NEED);
			return false;//直接返回
		}

		memcpy(pRevMsg,pForRev,revQty);
		bRet = true;
		break;

	} while(1);


	return bRet;
}

bool CUDPConn::AsynRec(SOCKET RFIDSocket,char *buf,int nMaxRecLen,int *pRecvLen)
{
	*pRecvLen = 0;//

	fd_set fdread;
	struct timeval rto; // for receive data timeout setup

	rto.tv_sec = 0; 	//set timeout interval
	rto.tv_usec = 1000;

	//Always clear the read set before calling select()
	FD_ZERO(&fdread);

	// Add socket s to the read set
	FD_SET(RFIDSocket,&fdread);
	int nRet = select(0,&fdread,NULL,NULL,&rto);
	switch (nRet)
	{
	case -1:  
		SetErrorCode(ERR_UDPRECV_SOCKETERROR);
		return false;
	case 0:  
		SetErrorCode(ERR_UDPRECV_SOCKETOVERTIME);
		return false;
	default:  
		if (!FD_ISSET(RFIDSocket,&fdread))					//不在集合中
		{  
			SetErrorCode(ERR_UDPRECV_SOCKETERROR);
			return false;		
		}  

		SOCKADDR_IN addrClient;
		int nSize = sizeof(addrClient);

		int nReadData = recvfrom(RFIDSocket,buf,nMaxRecLen,0,(SOCKADDR*)&addrClient,&nSize);
		if( SOCKET_ERROR == nReadData )
		{
			SetErrorCode(ERR_UDPRECV_SOCKETERROR);
			return false;
		}
		*pRecvLen = nReadData;
		return true;
	}
}

int CUDPConn::AsynRec_Wait(SOCKET RFIDSocket, char *buf, int nMaxRecLen, int nWaitTime, int *pRecvLen)
{
	*pRecvLen = 0;//

	fd_set fdread;
	struct timeval rto; // for receive data timeout setup

	rto.tv_sec = 0; 	//下面单位是微秒
	rto.tv_usec = nWaitTime * 1000;//转化为微秒

	//Always clear the read set before calling select()
	FD_ZERO(&fdread);

	// Add socket s to the read set
	FD_SET(RFIDSocket,&fdread);
	int nRet = select(0,&fdread,NULL,NULL,&rto);
	switch (nRet)
	{
	case -1:  
		SetErrorCode(ERR_UDPRECV_SOCKETERROR);
		return -1;
	case 0:  
		SetErrorCode(ERR_UDPRECV_SOCKETOVERTIME);
		return 0;
	default:  
		if (!FD_ISSET(RFIDSocket,&fdread))					//不在集合中
		{  
			SetErrorCode(ERR_UDPRECV_SOCKETERROR);
			return 0;		
		}  

		SOCKADDR_IN addrClient;
		int nSize = sizeof(addrClient);

		int nReadData = recvfrom(RFIDSocket,buf,nMaxRecLen,0,(SOCKADDR*)&addrClient,&nSize);
		if( SOCKET_ERROR == nReadData )
		{
			SetErrorCode(ERR_UDPRECV_SOCKETERROR);
			return -1;
		}
		*pRecvLen = nReadData;
		return 1;
	}
}

int CUDPConn::AsynSend(SOCKET RFIDSocket,char *buf,int nMaxSendLen,int *pSendLen)
{
	int nRet = sendto(RFIDSocket, (LPSTR)buf,nMaxSendLen , 0, (SOCKADDR*)&RFIDSAddr, sizeof(RFIDSAddr));

	*pSendLen = nRet;

	return true;	
}

bool CUDPConn::SendRawData(unsigned char* szData,int nLen)
{
	//发包
	int leaveFrameSize = nLen;
	int totalFrameSize = nLen;
	int sendFrameSize = 0;
	int sendErrorTimes = 3;						//设定为 在出现3次select不到 Socket时结束程序运行, 跳向出错处理
	unsigned char *pSendBuffer = szData;		//发送指针
	int nCurrentSend = 0;

	while (leaveFrameSize)						//出现情况在于没有将数据一次发送完毕
	{
		Sleep(50);
		AsynSend(RFIDSocket,(char*)(pSendBuffer+sendFrameSize),leaveFrameSize,&nCurrentSend);
		sendFrameSize += nCurrentSend;
		leaveFrameSize = totalFrameSize - sendFrameSize;
		sendErrorTimes --;
		if ( 0 ==sendErrorTimes)
		{
			//SetErrorCode(ERR_TCPSEND_SOCKETOVERTIME);					//出错处理发送失败
			return false;
		}
	}
	return true;
}

bool CUDPConn::CloseConn()
{
	CloseThread(); //关闭线程

	return ClosePort();//关闭端口
}

bool CUDPConn::ClosePort()
{
	CloseSocket();	

	return true;
}

bool CUDPConn::CloseThread()
{
	m_bThExit = true; //关闭线程
	if( m_hThread != NULL )
	{
		WaitForSingleObject(m_ThreadExitEvent,INFINITE);
	}
	return true;
}

bool CUDPConn::Svr()
{
	if( NULL == m_hThread )
	{
		m_bThExit = false;
		m_hThread = (HANDLE)_beginthreadex(NULL,
			0,
			(PBEGINTHREADEX_THREADFUNC)StartUDPRevThread,
			(LPVOID)this,
			0,
			NULL);
		if (NULL == m_hThread)
		{
			SetErrorCode(ERR_STARTREVTHREAD_FAIL);
			return false;
		}	
	}
	return true;
}

void CUDPConn::CloseSocket()
{
	if( RFIDSocket != INVALID_SOCKET )
	{
		closesocket(RFIDSocket);
		RFIDSocket = INVALID_SOCKET;
	}
}


