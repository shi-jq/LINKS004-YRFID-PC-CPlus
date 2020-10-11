#include "StdAfx.h"
#include "SAATReaderFactory.h"

CSAATReaderFactory::CSAATReaderFactory(void)
{
}

CSAATReaderFactory::~CSAATReaderFactory(void)
{
}


CRFIDReaderServer* CSAATReaderFactory::ConcreteConn()
{
	return (new CRFIDReaderServer);
}