#include "UdpClient.h"
#include <string>
#pragma comment(lib,"Ws2_32.lib")
#include <Iphlpapi.h>
#pragma comment(lib, "Iphlpapi.lib")

#define UDP_FRAME_ONCE	255
#define UDP_PORT		5083
#define COM_FRAME_ONCE 1024

UdpClient::UdpClient(void)
{
	m_bOpened =false;
	mUdpport = UDP_PORT;
}

UdpClient::~UdpClient(void)
{
	CloseSocket();
}


//�첽����
bool UdpClient::OpenConn(int udpport,unsigned long mBroadcast)
{
	mUdpport = udpport;
	//����豸
	WSADATA wsaData;
	if( 0 != WSAStartup(MAKEWORD(2,2),&wsaData) )
	{		
		return false;
	}

	bool  optval = true;

	//����UDP socket
	RFIDSocket=socket(AF_INET,SOCK_DGRAM,0);

	if (RFIDSocket==INVALID_SOCKET)	
	{
		return false;
	}

	setsockopt(RFIDSocket, SOL_SOCKET, SO_BROADCAST, (char*)&optval, sizeof(optval));
	
	RFIDSAddr.sin_family=AF_INET;
	RFIDSAddr.sin_port=htons(mUdpport);
	RFIDSAddr.sin_addr.s_addr = mBroadcast;
	
	m_bOpened = true;
	return true;
}
//*********************************
//������:	�첽���ͺ���,��ʱʱ��1�� SEND_WAIT
//����˵��:	strErrorΪ���ش�����Ϣ
//����ֵ:	��
//***********************************
int UdpClient::AsynSend(SOCKET RFIDSocket,char *buf,int nMaxSendLen,int *pSendLen)
{
	int nRet = sendto(RFIDSocket, (LPSTR)buf,nMaxSendLen , 0, (SOCKADDR*)&RFIDSAddr, sizeof(RFIDSAddr));

	*pSendLen = nRet;

	return true;
}


bool UdpClient::Send(unsigned char *pSendData, int dataLength)
{
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



void UdpClient::CloseSocket()
{
	if( RFIDSocket != INVALID_SOCKET )
	{
		closesocket(RFIDSocket);
		RFIDSocket = INVALID_SOCKET;
	}
}



int  UdpClient::RevMsg(unsigned char *pRevMsg,unsigned char *pDataLen,int nWaitTime)
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
		//���ڽ���ʱ��,����
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
		if( nRecvDataLen > *pDataLen ) //�ڴ治�� 
		{			
			return -1;//ֱ�ӷ���
		}

		memcpy(pRevMsg,pForRev,revQty);
		bRet = true;
		break;

	} while(1);


	return nRecvDataLen;
}

bool UdpClient::UDPRecv(unsigned char* pRecv,int& nSize)
{
	if(!m_bOpened)
	{
		return false;
	}

	return AsynRec(RFIDSocket,(char*)pRecv,UDP_FRAME_ONCE,&nSize);

}

//***********************************
//������:	�첽���պ���,��ʱʱ��2�� RECV_WAIT
//����˵��:	strErrorΪ���ش�����Ϣ
//����ֵ:	��
//***********************************
bool  UdpClient::AsynRec(SOCKET RFIDSocket,char *buf,int nMaxRecLen,int *pRecvLen)
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
		if (!FD_ISSET(RFIDSocket,&fdread))					//���ڼ�����
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

bool UdpClient::CloseConn()
{
	CloseSocket();

	return true;
}
