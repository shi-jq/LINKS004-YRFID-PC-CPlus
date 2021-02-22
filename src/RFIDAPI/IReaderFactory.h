#pragma once

#include "RFIDReader.h"
class IReaderFactory
{
public:
	IReaderFactory(void);
	virtual CRFIDReader* ConcreteConn() = 0;
public:
	virtual ~IReaderFactory(void);
};
