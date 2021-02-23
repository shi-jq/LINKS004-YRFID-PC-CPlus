#include "tcpclient.h"
#include <string>
#pragma comment(lib,"Ws2_32.lib")
#include <Iphlpapi.h>
#pragma comment(lib, "Iphlpapi.lib")

#define TCP_FRAME_ONCE	255
#define TCP_PORT		69


TcpClient::TcpClient(void)
{
	m_bOpened =false;
	mTcpport = TCP_PORT;
}

TcpClient::~TcpClient(void)
{
	CloseSocket();
}


//异步连接
bool TcpClient::OpenConn(int nPort,unsigned long ipAddr)
{
	mTcpport = nPort;
	//检查设备
	WSADATA wsaData;
	if( 0 != WSAStartup(MAKEWORD(2,2),&wsaData) )
	{		
		return false;
	}

	//创建tcp socket
	RFIDSocket=socket(AF_INET,SOCK_DGRAM,0);

	if (RFIDSocket==INVALID_SOCKET)	
	{
		return false;
	}


	RFIDSAddr.sin_family=AF_INET;
	RFIDSAddr.sin_port=htons(mTcpport);
	RFIDSAddr.sin_addr.s_addr = ipAddr;
	
	m_bOpened = true;
	return true;
}
//*********************************
//函数名:	异步发送函数,超时时间1秒 SEND_WAIT
//参数说明:	strError为返回错误信息
//返回值:	无
//***********************************
int TcpClient::AsynSend(SOCKET RFIDSocket,char *buf,int nMaxSendLen,int *pSendLen)
{
	int nRet = sendto(RFIDSocket, (LPSTR)buf,nMaxSendLen , 0, (SOCKADDR*)&RFIDSAddr, sizeof(RFIDSAddr));

	*pSendLen = nRet;

	return true;
}


bool TcpClient::Send(unsigned char *pSendData, int dataLength)
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
			return false;
		}
	}
	return true;
}



void TcpClient::CloseSocket()
{
	if( RFIDSocket != INVALID_SOCKET )
	{
		closesocket(RFIDSocket);
		RFIDSocket = INVALID_SOCKET;
	}
}



int  TcpClient::RevMsg(unsigned char *pRevMsg,int *pDataLen,int nWaitTime)
{
	if( 0 == nWaitTime)
	{
		nWaitTime +=3000;
	}

	unsigned char pForRev[TCP_FRAME_ONCE];
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

		memset(pForRev,0,TCP_FRAME_ONCE);

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
			return -1;//直接返回
		}

		memcpy(pRevMsg,pForRev,revQty);
		bRet = true;
		break;

	} while(1);


	return nRecvDataLen;
}

bool TcpClient::UDPRecv(unsigned char* pRecv,int& nSize)
{
	if(!m_bOpened)
	{
		return false;
	}

	return AsynRec(RFIDSocket,(char*)pRecv,TCP_FRAME_ONCE,&nSize);

}

//***********************************
//函数名:	异步接收函数,超时时间2秒 RECV_WAIT
//参数说明:	strError为返回错误信息
//返回值:	无
//***********************************
bool  TcpClient::AsynRec(SOCKET RFIDSocket,char *buf,int nMaxRecLen,int *pRecvLen)
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
		return false;
	case 0:  		
		return false;
	default:  
		if (!FD_ISSET(RFIDSocket,&fdread))					//不在集合中
		{  
			return false;		
		}  

		SOCKADDR_IN addrClient;
		int nSize = sizeof(addrClient);

		int nReadData = recvfrom(RFIDSocket,buf,nMaxRecLen,0,(SOCKADDR*)&addrClient,&nSize);
		if( SOCKET_ERROR == nReadData )
		{		
			return false;
		}
		*pRecvLen = nReadData;
		return true;
	}
}

bool TcpClient::CloseConn()
{
	CloseSocket();

	return true;
}
