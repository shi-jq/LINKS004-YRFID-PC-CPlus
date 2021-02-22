#include "StdAfx.h"
#include "ErrorMsgFactory.h"
#include "CNGetMsg.h"
#include "ENGetMsg.h"
#include "TWGetMsg.h"

//IFactoryConn* CErrorMsgFactory::instance = NULL;
CErrorMsgFactory::CErrorMsgFactory(void)
{
}

CErrorMsgFactory::~CErrorMsgFactory(void)
{
}

IGetMsgInterface* CErrorMsgFactory::ConcreteConn(string strType)
{
	if( strType == "cn" )
	{
		return new CCNGetMsg;
	}
	else if( strType == "tw" )
	{
		return new CTWGetMsg;
	}
	else if(  strType == "en" )
	{
		return new CENGetMsg;
	}
	else
	{
		return NULL;
	}

}

//IGetMsgInterface* ConcreteConn(string strType)		//创建连接实例
//{
//	if(instance == NULL)
//		instance = new CConcreteFactoryConn();
//	return instance;
//}
