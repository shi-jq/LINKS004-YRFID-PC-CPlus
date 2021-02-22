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

	//会new 需要外部进行释放内存
	ConnetBase*  CreateTcpServerConnet(CRFIDReader* pReader,SOCKET& sockConn);
	//tcp客户端的
	ConnetBase*  CreateTcpClientConnet(CRFIDReader* pReader,char *pHostName,int nsocketPort);
	
	//udp客户端的
	ConnetBase*  CreateUdpClientConnet(CRFIDReader* pReader,char *pHostName,int nsocketPort);

	//com
	ConnetBase*  CreateComClientConnet(CRFIDReader* pReader,unsigned char nBusAddr,char *pComNum,int nBaud);
	//usb
	ConnetBase*  CreateUsbClientConnet(CRFIDReader* pReader,unsigned char nBusAddr,char *pComNum,int nBaud);

	ConnetCreater(void);
	~ConnetCreater(void);

private:
	
};
