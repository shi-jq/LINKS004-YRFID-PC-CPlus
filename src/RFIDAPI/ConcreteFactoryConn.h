//////////////////////////////////////////////////////////////////////////
//RFIDAPI 底层服务1.0
//设计者：
//开发日期：2008－8－25
//说明： 本程序主要为RFIDAPI提供底层服务，包括指令发送，数据接收及查错处理
//
//////////////////////////////////////////////////////////////////////////
#pragma once
#include "IFactoryConn.h"
#include "IConnect.h"

class CConcreteFactoryConn :	public IFactoryConn				//实例工厂
{
public:
	CConcreteFactoryConn(void);
	IFactoryConn* Instance();						//加入单件模式，以保证处理模式上仅存在1个工厂类
    //IConnect* ConcreteConn(int nType);		//创建连接实例
public:
	~CConcreteFactoryConn(void);
protected:
	
private:
	static IFactoryConn* instance;
};
