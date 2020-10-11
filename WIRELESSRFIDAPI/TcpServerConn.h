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
	//初始化tcp服务
	bool Init(char *pHostName,int nsocketPort,CRFIDReaderServer* pCRFIDReaderServer);
	bool Quit();		//退出tcp服务
	bool StartListen();	//开始监听
	bool StopListen();	//退出监听

public:
	bool Svr();				 //线程处理监听
	bool IsUserExit();		 //是否需要退出监听
	bool CloseThreadHandle();//关闭线程
private:
	bool StartThread();
	bool CloseThread();
	
	void SetErrorCode(int nErrorCode,bool bCommandError = false);//设置错误码
private:
	SOCKET mListenSock;
	SOCKADDR_IN mAddrClient;
	int mPort;
	string  mIpAddr;//ip地址
	
	volatile bool m_bThExit;
	HANDLE m_hThread;
	CMyEvent m_ThreadExitEvent;

	CRFIDReaderServer* mCRFIDReaderServer;
};
