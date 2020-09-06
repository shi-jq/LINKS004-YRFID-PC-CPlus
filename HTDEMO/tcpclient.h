#pragma once
//#include <windows.h>
//#include <Winsock2.h>
#include <winsock.h>
class TcpClient
{
public:
	TcpClient(void);
	~TcpClient(void);
	bool OpenConn(int nPort,unsigned long ipAddr);
	bool Send( unsigned char *pSendData, int dataLength);
	int  AsynSend(SOCKET RFIDSocket,char *buf,int nMaxSendLen,int *pSendLen);
	int RevMsg(unsigned char *pRevMsg,
		int *pDataLen,
		int nWaitTime = 3000);
	bool UDPRecv(unsigned char* pRecv,int& nSize);
	bool AsynRec(SOCKET RFIDSocket,char *buf,int nMaxRecLen,int *pRecvLen);
	bool CloseConn() ;
	void CloseSocket();

private:
	SOCKET RFIDSocket;
	sockaddr_in RFIDSAddr;
	unsigned int mTcpport;
	bool m_bOpened;
};
