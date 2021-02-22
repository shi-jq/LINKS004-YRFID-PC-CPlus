#pragma once
#include "ireaderfactory.h"

class CSAATReaderFactory :
	public IReaderFactory
{
public:
	CSAATReaderFactory(void);
	CRFIDReader* ConcreteConn();
public:
	~CSAATReaderFactory(void);
};
