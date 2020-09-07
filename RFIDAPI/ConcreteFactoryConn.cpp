#include "StdAfx.h"
#include "ConcreteFactoryConn.h"
#include "TCPConn.h"
#include "USBConn.h"
#include "COMConn.h"

IFactoryConn* CConcreteFactoryConn::instance = NULL;

CConcreteFactoryConn::CConcreteFactoryConn(void)
{
}

CConcreteFactoryConn::~CConcreteFactoryConn(void)
{
	
}


IFactoryConn* CConcreteFactoryConn::Instance()
{
	if(instance == NULL)
		instance = new CConcreteFactoryConn();
	return instance;
}

IConnect* CConcreteFactoryConn::ConcreteConn(int nType)
{
	switch (nType)
	{
	case TCPINIT:
		return new CTCPConn;
	case COMINIT:
		return new CCOMConn;
	case USBINIT:
		return new CUSBConn;
	}
	return NULL;
}