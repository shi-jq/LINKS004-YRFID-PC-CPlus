#pragma once
#include "Singleton.h"
#include <Winsock2.h>

class ConnetBase;
class CRFIDReader;
class ConnetCreater
{
	friend class CSingleton<ConnetCreater>;
public:
	bool Init();
	bool Quit();

	//��new ��Ҫ�ⲿ�����ͷ��ڴ�
	ConnetBase*  CreateTcpServerConnet(CRFIDReader* pReader,SOCKET& sockConn);
	//tcp�ͻ��˵�
	ConnetBase*  CreateTcpClientConnet(CRFIDReader* pReader,char *pHostName,int nsocketPort);
	
	//udp�ͻ��˵�
	ConnetBase*  CreateUdpClientConnet(CRFIDReader* pReader,char *pHostName,int nsocketPort);

	//com
	ConnetBase*  CreateComClientConnet(CRFIDReader* pReader,unsigned char nBusAddr,char *pComNum,int nBaud);
	//usb
	ConnetBase*  CreateUsbClientConnet(CRFIDReader* pReader,unsigned char nBusAddr,char *pComNum,int nBaud);

	ConnetCreater(void);
	~ConnetCreater(void);

private:
	
};
