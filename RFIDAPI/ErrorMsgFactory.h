#pragma once
#include "IGetMsgInterface.h"

class CErrorMsgFactory
{
public:
	CErrorMsgFactory(void);
public:
	virtual ~CErrorMsgFactory(void);
	IGetMsgInterface* ConcreteConn(string strType);		//��������ʵ��
//private:
//	static IGetMsgInterface* instance;
};
