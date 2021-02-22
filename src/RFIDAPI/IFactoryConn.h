//////////////////////////////////////////////////////////////////////////
//RFIDAPI 底层服务1.0
//设计者：
//开发日期：2008－8－25
//说明： 本程序主要为RFIDAPI提供底层服务，包括指令发送，数据接收及查错处理
//
//////////////////////////////////////////////////////////////////////////
#pragma once
#include "IConnect.h"
class IFactoryConn		//工厂指针
{
public:
	IFactoryConn(void);
	virtual IConnect* ConcreteConn(int nType) = 0;
public:
	virtual ~IFactoryConn(void);

};
