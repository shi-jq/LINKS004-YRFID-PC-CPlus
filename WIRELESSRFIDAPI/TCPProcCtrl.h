#pragma once
#include "Global.h"
#include <Winsock2.h>
#include "DataProc.h"
#include "WIRELESSRFIDAPIEXPORT.h"
#include "Lock.h"
#include "ConnetBase.h"

class CRFIDReader;
class CTCPProcCtrl: public ConnetBase
{
public:
	CTCPProcCtrl(CRFIDReader* pReader);
	~CTCPProcCtrl(void);

	bool UpdateSocket(SOCKET& sockConn);
	bool StartRead();
	bool StopRead();

	bool SendMsg(unsigned char *pSendData, int dataLength);

public:
	bool Svr();				 //�̴߳������
	bool IsUserExit();		 //�Ƿ���Ҫ�˳�����
	bool CloseThreadHandle();//�ر��߳�

private:
	bool StartThread();
	bool CloseThread();
	void SetErrorCode(int nErrorCode,bool bCommandError = false);//���ô�����
	int  AsynSend(SOCKET RFIDSocket,char *buf,int nMaxSendLen,int *pSendLen);

private:
	volatile bool m_bThExit;
	HANDLE m_hThread;
	CMyEvent m_ThreadExitEvent;

	SOCKET mSocket;	//socket
	CDataProc*  m_pDataPrcoessInterface;

	char pForRev[1024];//���յĻ�������

};
