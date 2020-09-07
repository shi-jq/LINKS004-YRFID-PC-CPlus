#pragma once
#include "IGetMsgInterface.h"

class CErrorMsgFactory
{
public:
	CErrorMsgFactory(void);
public:
	virtual ~CErrorMsgFactory(void);
	IGetMsgInterface* ConcreteConn(string strType);		//创建连接实例
//private:
//	static IGetMsgInterface* instance;
};
