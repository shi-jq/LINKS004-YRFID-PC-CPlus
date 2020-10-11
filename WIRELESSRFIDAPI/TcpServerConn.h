#pragma once
#include <Winsock2.h>
#include <string>
#include "Lock.h"
using namespace std;
class CRFIDReaderServer;
class CTcpServerConn
{
public:
	CTcpServerConn(void);
	~CTcpServerConn(void);
	//��ʼ��tcp����
	bool Init(char *pHostName,int nsocketPort,CRFIDReaderServer* pCRFIDReaderServer);
	bool Quit();		//�˳�tcp����
	bool StartListen();	//��ʼ����
	bool StopListen();	//�˳�����

public:
	bool Svr();				 //�̴߳������
	bool IsUserExit();		 //�Ƿ���Ҫ�˳�����
	bool CloseThreadHandle();//�ر��߳�
private:
	bool StartThread();
	bool CloseThread();
	
	void SetErrorCode(int nErrorCode,bool bCommandError = false);//���ô�����
private:
	SOCKET mListenSock;
	SOCKADDR_IN mAddrClient;
	int mPort;
	string  mIpAddr;//ip��ַ
	
	volatile bool m_bThExit;
	HANDLE m_hThread;
	CMyEvent m_ThreadExitEvent;

	CRFIDReaderServer* mCRFIDReaderServer;
};
