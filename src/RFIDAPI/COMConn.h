﻿#pragma once
#include "iconnect.h"

class CCOMConn :
	public IConnect
{
public:
	CCOMConn(void);
	void LoadData(CRFIDSystemCfg& initSystemCfg);
	bool OpenConn();
	bool CheckConnState( );
	bool ComRecv(unsigned char* pRecv,int& nSize);
	bool SendMsg(unsigned char *pSendData, int dataLength);
	//bool RevMsg(CRFIDFrame &pRevFrame, int nWaitTime = 3000);
	bool RevMsg(unsigned char *pRevMsg,unsigned char *pDataLen,int nWaitTime = 3000);
	bool CloseConn();
	bool WriteCommByte(unsigned char ucByte);
	bool ComSend(unsigned char* ucByte,int nSize);
	bool Svr();
	bool SendRawData(unsigned char* szData,int nLen) ;
	void InitConnect(IDataProc * pDataProc) ;
	void SetHeartTime(int nHeartTime) ;
	bool ClosePort();
	bool CloseThread();

	OVERLAPPED   m_OverlappedRead,m_OverlappedWrite;   
	bool   m_bOpened;   
	int   nPort ;
	int   nBaud;
	HANDLE m_RevEvent;
	volatile bool   m_bThExit;
	CRFIDSystemCfg m_RFIDSystemCfg;
	HANDLE m_hThread;
	HANDLE m_ThreadExitEvent;
	int m_nHeartTime ;

	
private:
public:
	~CCOMConn(void);
};
