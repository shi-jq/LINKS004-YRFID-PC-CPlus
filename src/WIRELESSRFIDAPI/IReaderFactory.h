#pragma once

#include "RFIDReaderServer.h"
class IReaderFactory
{
public:
	IReaderFactory(void);
	virtual CRFIDReaderServer* ConcreteConn() = 0;
public:
	virtual ~IReaderFactory(void);
};
