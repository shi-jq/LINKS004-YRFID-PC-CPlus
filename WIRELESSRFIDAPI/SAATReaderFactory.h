#pragma once
#include "ireaderfactory.h"

class CSAATReaderFactory :
	public IReaderFactory
{
public:
	CSAATReaderFactory(void);
	CRFIDReaderServer* ConcreteConn();
public:
	~CSAATReaderFactory(void);
};
