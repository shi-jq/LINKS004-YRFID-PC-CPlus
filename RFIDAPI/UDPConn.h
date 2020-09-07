#pragma once
#include "iconnect.h"
#include <windows.h>
#include <Winsock2.h>

class CUDPConn	:
	public IConnect
{
public:
	CUDPConn(void);
	void LoadData(CRFIDSystemCfg& initSystemCfg) ;
	void InitConnect(IDataProc * pDataProc) ;
	bool OpenConn() ;	
	bool Send( unsigned char *pSendData, int dataLength);
	//bool RevMsg(CRFIDFrame &pRevFrame, int nWaitTime = 3000);
	bool RevMsg(unsigned char *pRevMsg,unsigned char *pDataLen,int nWaitTime = 3000);
	bool AsynRec(SOCKET RFIDSocket,char *buf,int nMaxRecLen,int *pRecvLen);
	int  AsynRec_Wait(SOCKET RFIDSocket,
		char *buf,
		int nMaxRecLen,
		int nWaitTime,
		int *pRecvLen);
	int  AsynSend(SOCKET RFIDSocket,char *buf,int nMaxSendLen,int *pSendLen);
	bool SendRawData(unsigned char* szData,int nLen);
	bool SendMsg(unsigned char *pSendData, int dataLength);
	bool UDPRecv(unsigned char* pRecv,int& nSize);
	bool   bExit;
	bool m_bOpened;
	void CloseSocket();
	bool CloseConn() ;
	bool ClosePort() ;
	bool CloseThread();
	volatile bool m_bThExit;
	IDataProc *m_pDataPrcoessInterface;//数据处理接口
	HANDLE m_hThread;
	HANDLE m_ThreadExitEvent;
	bool Svr();
	void SetHeartTime(int nHeartTime) ;
	bool CheckConnState();
private:
	int m_nHeartTime;
	SOCKET RFIDSocket;
	CRFIDSystemCfg m_RFIDSystemCfg;


	sockaddr_in RFIDSAddr;
public:
	~CUDPConn(void);
};
