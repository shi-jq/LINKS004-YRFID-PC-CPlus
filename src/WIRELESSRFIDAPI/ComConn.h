#pragma once
#include "Global.h"
#include "ConnetBase.h"

class CRFIDReader;
class COMConn :
	public ConnetBase
{
public:
	COMConn(CRFIDReader* pReader);
	~COMConn(void);
	void LoadData(unsigned char nBusAddr,char *pComNum,int nBaud);
	bool StartRead();
	bool StopRead();
	bool SendMsg(unsigned char *pSendData, int dataLength);

	bool ComRecv(unsigned char* pRecv,int& nSize);
private:
	bool OpenConn() ;
	bool WriteCommByte(unsigned char ucByte);
	bool ComSend(unsigned char* ucByte,int nSize);
	bool Svr();
	bool SendRawData(unsigned char* szData,int nLen) ;

	bool CloseConn();
	bool ClosePort();
	bool CloseThread();
public:
	bool   bExit;
	bool m_bOpened;
	volatile bool m_bThExit;

	HANDLE m_hThread;
	HANDLE m_ThreadExitEvent;

private:
	OVERLAPPED   m_OverlappedRead,m_OverlappedWrite; 

	string mStrComNum;
	int    mBaud;
	unsigned char mBusAddr;

	void *pHandle;

};
