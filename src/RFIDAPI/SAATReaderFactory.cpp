#include "StdAfx.h"
#include "SAATReaderFactory.h"

CSAATReaderFactory::CSAATReaderFactory(void)
{
}

CSAATReaderFactory::~CSAATReaderFactory(void)
{
}


CRFIDReader* CSAATReaderFactory::ConcreteConn()
{

	return (new CRFIDReader);
}