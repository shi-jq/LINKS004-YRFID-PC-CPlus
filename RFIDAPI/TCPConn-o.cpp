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
//函数名:	打开连接函数
//参数说明:	无
//返回值:	打开成功时返回 true,
//////////////////////////////////////////////////////////////////////////
bool CTCPConn::OpenConn()
{
	//检查设备
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
	//创建TCP socket
	RFIDSocket=socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);

	if (RFIDSocket==INVALID_SOCKET)	
	{
		return false;
	}

	//sockaddr_in设置
	RFIDSAddr.sin_family=AF_INET;
	RFIDSAddr.sin_port=htons(RFIDSystemCfg.nSocketPort);
	RFIDSAddr.sin_addr.s_addr=inet_addr(RFIDSystemCfg.strHostName.c_str());

	//设置socket为非锁定模式,ul为0值的话，那么socket将被设置为锁定模式
	// nonblocking mode 

	if(ioctlsocket(RFIDSocket,FIONBIO,(unsigned long*)&ul)==SOCKET_ERROR ) 
	{
		closesocket(RFIDSocket);
		errorProc.SetErrorCode( ERR_SOCKET_ERR );			//SOCKET出错
		isConn = false;
		return false;
	}
	//创建连接
	int result=connect(RFIDSocket,(struct sockaddr *)&RFIDSAddr,sizeof(RFIDSAddr));
	if (result == 0)
		return isConn = true;
	else
	{
		errorProc.SetErrorCode( ERR_CONNECT_FAIL);		//连接失败
		return false;
	}
}

//////////////////////////////////////////////////////////////////////////
//函数名:	连接状态检测函数
//参数说明:	maxWaitTime 最大延迟
//返回值:	返回 true 为处在连接状态
//////////////////////////////////////////////////////////////////////////
bool CTCPConn::CheckConnState(int maxWaitTime)
{
	errorProc.ClearErrorCode();
	if (!isConn) //cxm fix
	{
		errorProc.SetErrorCode( ERR_CONNECT_FAIL);		//连接失败
		return false;
	}
	fd_set fdconn;
	struct timeval rto;									// 超时设定
	int ret;

	rto.tv_sec = maxWaitTime / 1000; 					//设定超时单位  为 秒
	rto.tv_usec =(maxWaitTime % 1000)*1000;				//毫秒

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
//函数名:	数据帧发送函数
//参数说明:	pSendCommand 发送指令, pSendData 发送数据, dataLength 数据长度
//返回值:	true 为发送成功
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
	//装包
	unsigned char pForSend[SENDFRAME_MAXBUF];
	int totalFrameSize = 0;
	if(! PackMsg(pSendCommand, pSendData, dataLength, pForSend,&totalFrameSize) )
	{
		return false;
	}
	
	//发包
	int leaveFrameSize = totalFrameSize;
	int sendFrameSize = 0;
	int sendErrorTimes = 3;						//设定为 在出现3次select不到 Socket时结束程序运行, 跳向出错处理
	unsigned char *pSendBuffer = pForSend;		//发送指针
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
			//errorProc.SetErrorCode(ERR_TCPSEND_SOCKETOVERTIME);					//出错处理发送失败
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

		printData("\n接收到原始数据:",pForRev,revQty);
		//解包, true时表示已将数据包完整写入revFrame, false 表示数据包不完整
		if( !pThis->UnpackMsg( pForRev, revQty))				
		{
			OutputDebugString(L"继续收包");
			continue;
		}
		printData("解包后数据:",(LPBYTE)&(pThis->revFrame),pThis->revFrame.bLength+6);
		if (pThis->frameNum == (pThis->revFrame.bAddrInfo & 0x0f) )		//找到回复帧 cxm fix
		{	
			SetEvent(pThis->m_RevEvent);
			break;
		}

		OutputDebugString(L"帧头不对\n");
		if (pThis->revFrame.bFrame == 0 && (-- revErrorTimes == 0) )	//帧头为0 时表示没有再接受到任何数据了, 则表示帧丢失
		{
			pThis->errorProc.SetErrorCode(ERR_FRAME_LOSE);			//出错处理帧丢失
			break;
		}
		//Sleep(pThis->nWaitTime / 10);
		Sleep(50);
	}

	return 0;
}



//////////////////////////////////////////////////////////////////////////
//函数名:	数据帧接收函数
//参数说明:	pRevFrame接收的数据帧存在CRFIDFrame中
//返回值:	true接收成功
//////////////////////////////////////////////////////////////////////////
#ifdef CPLUSPLUS 
bool CTCPConn::RevMsg(CRFIDFrame &pRevFrame, int nWaitTime )
{
	unsigned char pForRev[REC_FRAME_ONCE];
	int revQty = 0;
	int revErrorTimes = 100;							//定义在接收到3次并非回复帧时结束函数操作, 表示帧已丢失

	bool bResult = false;
	do 
	{
		-- revErrorTimes ;
		AsynRec(RFIDSocket,(char*)pForRev,REC_FRAME_ONCE,&revQty);
		if( 0 != revQty )
		{
			printData("接收到原始数据:",pForRev,revQty);
		}
		if( !UnpackMsg( pForRev, revQty) )				//解包, true时表示已将数据包完整写入revFrame, false 表示数据包不完整
		{
			if( 0 == revQty )
			{
				Sleep(nWaitTime / 100);	
			}
			continue;
		}
		//printData("解包后数据:",pForRev,revQty);
		if (revFrame.bFrame == 0 && ( revErrorTimes == 0) )	//帧头为0 时表示没有再接受到任何数据了, 则表示帧丢失
		{
			errorProc.SetErrorCode(ERR_FRAME_LOSE);			//出错处理帧丢失
			return false;
		}

		if (frameNum == (revFrame.bAddrInfo & 0x0f))
		{
			bResult = true;
			break;
		}
		Sleep(nWaitTime / 100);
	} while(revErrorTimes);
	printData("解包后数据:",(unsigned char *)&revFrame,revFrame.bLength+6);

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
	////nWaitTime  等待时间，一般为2秒收不到数据则退出
	////但关功放太慢，2秒钟还在收卡的信息，2秒收不完，这里退出，buffer被清空，会被认为关闭失败，故应设为5秒
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
	int revErrorTimes = nWaitTime;							//定义在接收到3次并非回复帧时结束函数操作, 表示帧已丢失

	bool bResult = false;
	do 
	{
		AsynRec(RFIDSocket,(char*)pForRev,REC_FRAME_ONCE,&revQty);
		if( 0 != revQty )
		{
			printData("接收到原始数据:",pForRev,revQty);
		}
		if( !UnpackMsg( pForRev, revQty) )				//解包, true时表示已将数据包完整写入revFrame, false 表示数据包不完整
		{
			if( 0 == revQty )
			{
				Sleep(1);	
			}
			continue;
		}
		//printData("解包后数据:",pForRev,revQty);
		if (revFrame.bFrame == 0 && ( revErrorTimes == 0) )	//帧头为0 时表示没有再接受到任何数据了, 则表示帧丢失
		{
			errorProc.SetErrorCode(ERR_FRAME_LOSE);			//出错处理帧丢失
			return false;
		}

		if (frameNum == (revFrame.bAddrInfo & 0x0f))
		{
			bResult = true;
			break;
		}
		Sleep(1);
	} while(revErrorTimes--);
	printData("解包后数据:",(unsigned char *)&revFrame,revFrame.bLength+6);
	
	if (revErrorTimes == 0)
	{
		ClearPasBuffer();
		memset((unsigned char*)&revFrame, 0 , sizeof(revFrame));
		errorProc.SetErrorCode(ERR_RECVTHREAD_OVERTIME);
		bResult = false;
	}
	pRevFrame = revFrame;						//不肯定,测试时再做修改
	return bResult;
}
#endif
//////////////////////////////////////////////////////////////////////////
//函数名:	数据帧发送与接收函数
//参数说明:	pSendCommand 发送指令, pSendData 发送数据, dataLength 数据长度,pRevFrame接收的数据帧存在CRFIDFrame中
//返回值:	true操作成功
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
//函数名:	关闭连接函数
//参数说明:	无
//返回值:	无
//////////////////////////////////////////////////////////////////////////
bool CTCPConn::CloseConn()
{
	errorProc.ClearErrorCode();

	int result = closesocket(RFIDSocket);				//关闭Socket
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
//函数名:	获取错误信息
//参数说明:	strError为返回错误信息
//返回值:	无
//////////////////////////////////////////////////////////////////////////
void CTCPConn::GetError(string& strError)
{
	errorProc.GetErrorMsg(strError);
}

//////////////////////////////////////////////////////////////////////////
//函数名:	获取错误代码
//参数说明:	无
//返回值:	无
//////////////////////////////////////////////////////////////////////////
int CTCPConn::GetErrorCode()
{
	return errorProc.GetErrorCode();
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
		if (!FD_ISSET(RFIDSocket,&fdread))					//不在集合中
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
		errorProc.SetErrorCode(ERR_TCPSEND_SOCKETERROR);
		return false;
	case 0:  
		errorProc.SetErrorCode(ERR_TCPSEND_SOCKETOVERTIME);
		return false;
	default:  
		if (!FD_ISSET(RFIDSocket,&fdwrite))//不在集合中
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