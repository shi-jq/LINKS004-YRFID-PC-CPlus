#include "StdAfx.h"
#include "ConnetCreater.h"
#include "TCPProcCtrl.h"
#include "RFIDReader.h"
#include "TCPConn.h"
#include "ComConn.h"
#include "USBConn.h"
#include "UDPConn.h"

ConnetCreater::ConnetCreater(void)
{
}

ConnetCreater::~ConnetCreater(void)
{

}

bool ConnetCreater::Init()
{
	return true;
}

bool ConnetCreater::Quit()
{
	return true;
}

ConnetBase* ConnetCreater::CreateTcpServerConnet(CRFIDReader* pReader,SOCKET& sockConn)
{
	CTCPProcCtrl* pCTCPProcCtrl = new CTCPProcCtrl(pReader);
	pCTCPProcCtrl->UpdateSocket(sockConn);
	return pCTCPProcCtrl;
}

ConnetBase* ConnetCreater::CreateTcpClientConnet(CRFIDReader* pReader,char *pHostName,int nsocketPort)
{
	CTCPConn* pCTCPConn = new CTCPConn(pReader);
	pCTCPConn->LoadConfig(pHostName,nsocketPort);
	return pCTCPConn;
}

ConnetBase* ConnetCreater::CreateComClientConnet(CRFIDReader* pReader,unsigned char nBusAddr,char *pComNum,int nBaud)
{
	COMConn* pCOMConn = new COMConn(pReader);
	pCOMConn->LoadData(nBusAddr,pComNum,nBaud);
	return pCOMConn;
}

ConnetBase* ConnetCreater::CreateUsbClientConnet(CRFIDReader* pReader,unsigned char nBusAddr,char *pComNum,int nBaud)
{
	CUSBConn* pCUSBConn = new CUSBConn(pReader);
	pCUSBConn->LoadData(nBusAddr,pComNum,nBaud);
	return pCUSBConn;
}

ConnetBase* ConnetCreater::CreateUdpClientConnet(CRFIDReader* pReader,char *pHostName,int nsocketPort)
{
	CUDPConn* pCUDPConn = new CUDPConn(pReader);
	pCUDPConn->LoadConfig(pHostName,nsocketPort);
	return pCUDPConn;
}
