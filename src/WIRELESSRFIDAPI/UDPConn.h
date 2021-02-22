#pragma once
#include "Global.h"
#include <windows.h>
#include <Winsock2.h>
#include "ConnetBase.h"

class CRFIDReader;
class CUDPConn	:
	public ConnetBase
{
public:
	CUDPConn(CRFIDReader* pReader);
	
	~CUDPConn(void);

	bool LoadConfig(char *pHostName,int nsocketPort);
	bool StartRead();
	bool StopRead();
	bool SendMsg(unsigned char *pSendData, int dataLength);

	bool UDPRecv(unsigned char* pRecv,int& nSize);
private:	
	bool OpenConn() ;	
	bool Send( unsigned char *pSendData, int dataLength);
	bool RevMsg(unsigned char *pRevMsg,unsigned char *pDataLen,int nWaitTime = 3000);
	bool AsynRec(SOCKET RFIDSocket,char *buf,int nMaxRecLen,int *pRecvLen);
	int  AsynRec_Wait(SOCKET RFIDSocket,
		char *buf,
		int nMaxRecLen,
		int nWaitTime,
		int *pRecvLen);
	int  AsynSend(SOCKET RFIDSocket,char *buf,int nMaxSendLen,int *pSendLen);
	bool SendRawData(unsigned char* szData,int nLen);

	bool CloseConn() ;
	bool ClosePort() ;
	bool CloseThread();

	bool Svr();

	void CloseSocket();

public:
	bool   bExit;
	bool m_bOpened;
	volatile bool m_bThExit;

	HANDLE m_hThread;
	HANDLE m_ThreadExitEvent;

private:
	SOCKET RFIDSocket;
	sockaddr_in RFIDSAddr;

	string strHostName;
	int nSocketPort;
};
