﻿#include "StdAfx.h"
#include "TCPConn.h"
#include "comdef.h"
#include <process.h>
CTCPConn::CTCPConn()
{
	bExit = false;
	m_bOpened = false;
	m_hThread = NULL;
	m_bThExit = false;
	m_ThreadExitEvent = CreateEvent(NULL,FALSE,FALSE,NULL);

	m_nHeartTime = 6000;
	RFIDSocket = INVALID_SOCKET;

}

void CTCPConn::InitConnect(IDataProc * pDataProc) 
{
	m_pDataPrcoessInterface = pDataProc;
}

CTCPConn::~CTCPConn(void)
{
	if( NULL != m_ThreadExitEvent)
	{
		CloseHandle(m_ThreadExitEvent);
		m_ThreadExitEvent = NULL;
	}
}


void CTCPConn::LoadData(CRFIDSystemCfg& initSystemCfg) 
{
	m_RFIDSystemCfg = initSystemCfg;
}

void CTCPConn::CloseSocket()
{
	if( RFIDSocket != INVALID_SOCKET )
	{
		closesocket(RFIDSocket);
		RFIDSocket = INVALID_SOCKET;
	}
}

//异步连接
bool CTCPConn::OpenConn()
{
	//检查设备
	WSADATA wsaData;
	if( 0 != WSAStartup(MAKEWORD(2,2),&wsaData) )
	{
		SetErrorCode(ERR_INITSOCKET_FAIL);
		return false;
	}

	//创建TCP socket
	RFIDSocket=socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);

	if (RFIDSocket==INVALID_SOCKET)	
	{
		return false;
	}

	//sockaddr_in设置
	RFIDSAddr.sin_family=AF_INET;
	RFIDSAddr.sin_port=htons(m_RFIDSystemCfg.nSocketPort);
	RFIDSAddr.sin_addr.s_addr=inet_addr(m_RFIDSystemCfg.strHostName.c_str());

	//设置socket为非锁定模式,ul为0值的话，那么socket将被设置为锁定模式
	unsigned long ul = 1;
	if( SOCKET_ERROR == ioctlsocket(RFIDSocket,FIONBIO,(unsigned long*)&ul) ) 
	{
		CloseSocket();
		SetErrorCode( ERR_SOCKET_ERR );			//SOCKET出错
		m_bOpened = false;
		return false;
	}


	//创建连接
	int result=connect(RFIDSocket,(struct sockaddr *)&RFIDSAddr,sizeof(RFIDSAddr));
	if( -1 != result )
	{
		m_bOpened = true;
		return true;
	}

	int len = sizeof(int);
	int nError = -1;

	timeval tm;
	tm.tv_sec = 1;
	tm.tv_usec = 0;

	fd_set set;
	FD_ZERO(&set);
	FD_SET(RFIDSocket, &set);
	int nRet = select(RFIDSocket/*+1*/, NULL, &set, NULL, &tm) ;

	switch (nRet)
	{
	case -1:  
		CloseSocket();
		SetErrorCode(ERR_CONNECT_FAIL);
		return false;
	case 0:  
		CloseSocket();
		SetErrorCode(ERR_CONNECT_FAIL);
		return false;
	default:  
		if (!FD_ISSET(RFIDSocket,&set))					//不在集合中
		{  
			CloseSocket();
			SetErrorCode(ERR_TCPRECV_SOCKETERROR);
			return false;	
		}  
		break;
	}

	m_bOpened = true;
	return true;
}




int  CTCPConn::AsynRec_Wait(SOCKET RFIDSocket,
							char *buf,
							int nMaxRecLen,
							int nWaitTime,
							int *pRecvLen)
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
		SetErrorCode(ERR_TCPRECV_SOCKETERROR);
		return -1;
	case 0:  
		SetErrorCode(ERR_TCPRECV_SOCKETOVERTIME);
		return 0;
	default:  
		if (!FD_ISSET(RFIDSocket,&fdread))					//不在集合中
		{  
			SetErrorCode(ERR_TCPRECV_SOCKETERROR);
			return 0;		
		}  

		int nReadData = recv(RFIDSocket,buf,nMaxRecLen,0);
		if( SOCKET_ERROR == nReadData )
		{
			SetErrorCode(ERR_TCPRECV_SOCKETERROR);
			return -1;
		}
		*pRecvLen = nReadData;
		return 1;
	}
}

bool  CTCPConn::RevMsg(unsigned char *pRevMsg,unsigned char *pDataLen,int nWaitTime)
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

		TCPRecv(pForRev,revQty);
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

//////////////////////////////////////////////////////////////////////////
//函数名:	连接状态检测函数
//参数说明:	maxWaitTime 最大延迟
//返回值:	返回 true 为处在连接状态
//////////////////////////////////////////////////////////////////////////
bool CTCPConn::CheckConnState()
{
	return true;

}

DWORD WINAPI StartTCPRevThread(LPVOID p)
{
	CTCPConn *pThis = (CTCPConn*)p;
	int nErrorTimes = 0;
	while( !pThis->m_bThExit )
	{
		//收数据
		unsigned char pForRev[MAX_PATH];
		int revQty = 0 ;
		if( !pThis->TCPRecv(pForRev,revQty) ) //200秒超时
		{
		}

		nErrorTimes = 0 ; //有数据,则清错误次数
		if( pThis->m_pDataPrcoessInterface != NULL )
		{
			pThis->m_pDataPrcoessInterface->MsgProcess(pForRev,revQty);
		}	
	}

	CloseHandle(pThis->m_hThread);
	pThis->m_hThread = NULL;
	SetEvent(pThis->m_ThreadExitEvent);
	return 0;
}


bool CTCPConn::Svr()
{
	if( NULL == m_hThread )
	{
		m_bThExit = false;
		m_hThread = (HANDLE)_beginthreadex(NULL,
			0,
			(PBEGINTHREADEX_THREADFUNC)StartTCPRevThread,
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

bool CTCPConn::Send(unsigned char *pSendData, int dataLength)
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


//////////////////////////////////////////////////////////////////////////
//函数名:	数据帧发送函数
//参数说明:	pSendCommand 发送指令, pSendData 发送数据, dataLength 数据长度
//返回值:	true 为发送成功
//////////////////////////////////////////////////////////////////////////
bool CTCPConn::SendMsg(unsigned char *pSendData, int dataLength)
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



//***********************************
//函数名:	异步接收函数,超时时间2秒 RECV_WAIT
//参数说明:	strError为返回错误信息
//返回值:	无
//***********************************
bool  CTCPConn::AsynRec(SOCKET RFIDSocket,char *buf,int nMaxRecLen,int *pRecvLen)
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
		SetErrorCode(ERR_TCPRECV_SOCKETERROR);
		return false;
	case 0:  
		SetErrorCode(ERR_TCPRECV_SOCKETOVERTIME);
		return false;
	default:  
		if (!FD_ISSET(RFIDSocket,&fdread))					//不在集合中
		{  
			SetErrorCode(ERR_TCPRECV_SOCKETERROR);
			return false;		
		}  

		int nReadData = recv(RFIDSocket,buf,nMaxRecLen,0);
		if( SOCKET_ERROR == nReadData )
		{
			SetErrorCode(ERR_TCPRECV_SOCKETERROR);
			return false;
		}
		*pRecvLen = nReadData;
		return true;
	}
}


//////////////////////////////////////////////////////////////////////////
//函数名:	数据帧接收函数
//参数说明:	
//返回值:	true接收成功
//////////////////////////////////////////////////////////////////////////




bool CTCPConn::TCPRecv(unsigned char* pRecv,int& nSize)
{
	if(!m_bOpened)
	{
		SetErrorCode(ERR_TCP_NOTOPEN);
		return false;
	}

	return AsynRec(RFIDSocket,(char*)pRecv,TCP_FRAME_ONCE,&nSize);

}


//bool CTCPConn::SendNRevMsg(unsigned char *pSendCommand, unsigned char *pSendData, int dataLength, CRFIDFrame &pRevFrame,int nWaitTime )
//{
//	ClearErrorCode();
//
//	if( NULL == pSendCommand ||
//		NULL == pSendData )
//	{
//		SetErrorCode(ERR_POINTER_NULL);
//		return false;
//	}
//
//	if(!SendMsg( pSendData, dataLength))
//	{
//		return false;
//	}
//
//	return RevMsg(pRevFrame,nWaitTime);
//
//}

bool CTCPConn::ClosePort()
{
	CloseSocket();
	//int result = closesocket(RFIDSocket);				//关闭Socket
	//if (result == 0)
	//{
	//	m_bOpened = false;
	//	return true;
	//}
	//else
	//{
	//	SetErrorCode(ERR_CLOSE_FAIL);
	//	return false;
	//} 

	return true;
}


//////////////////////////////////////////////////////////////////////////
//函数名:	关闭连接函数
//参数说明:	无
//返回值:	无
//////////////////////////////////////////////////////////////////////////
bool CTCPConn::CloseConn()
{
	CloseThread();//关闭线程

	return ClosePort();//关闭端口
	
}


bool CTCPConn::CloseThread()
{
	m_bThExit = true; //关闭线程
	if( m_hThread != NULL )
	{
		WaitForSingleObject(m_ThreadExitEvent,INFINITE);
	}
	return true;
}


//*********************************
//函数名:	异步发送函数,超时时间1秒 SEND_WAIT
//参数说明:	strError为返回错误信息
//返回值:	无
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
		SetErrorCode(ERR_TCPSEND_SOCKETERROR);
		return false;
	case 0:  
		SetErrorCode(ERR_TCPSEND_SOCKETOVERTIME);
		return false;
	default:  
		if (!FD_ISSET(RFIDSocket,&fdwrite))//不在集合中
		{  
			SetErrorCode(ERR_TCPSEND_SOCKETERROR);
			return false;		
		}  

		int nSendata = send(RFIDSocket,buf,nMaxSendLen,0);
		if( SOCKET_ERROR == nSendata )
		{
			SetErrorCode(ERR_TCPSEND_SOCKETERROR);
			return false;
		}
		*pSendLen = nSendata;
		return true;
	}
}


bool CTCPConn::SendRawData(unsigned char* szData,int nLen) 
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





void CTCPConn::SetHeartTime(int nHeartTime) 
{
	m_nHeartTime = nHeartTime;
}
