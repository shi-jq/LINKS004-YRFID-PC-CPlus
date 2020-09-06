#pragma once
//#include <windows.h>
//#include <Winsock2.h>
#include <winsock.h>
class UdpClient
{
public:
	UdpClient(void);
	~UdpClient(void);
	bool OpenConn(int udpport,unsigned long mBroadcast);
	bool Send( unsigned char *pSendData, int dataLength);
	int  AsynSend(SOCKET RFIDSocket,char *buf,int nMaxSendLen,int *pSendLen);
	int RevMsg(unsigned char *pRevMsg,unsigned char *pDataLen,int nWaitTime = 3000);
	bool UDPRecv(unsigned char* pRecv,int& nSize);
	bool AsynRec(SOCKET RFIDSocket,char *buf,int nMaxRecLen,int *pRecvLen);
	bool CloseConn() ;
	void CloseSocket();

private:
	SOCKET RFIDSocket;
	sockaddr_in RFIDSAddr;
	unsigned int mUdpport;
	bool m_bOpened;
};
