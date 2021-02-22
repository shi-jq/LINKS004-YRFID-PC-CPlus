//////////////////////////////////////////////////////////////////////////
//RFIDAPI 底层服务1.0
//设计者：
//开发日期：2008－8－25
//说明： 本程序主要为RFIDAPI提供底层服务，包括指令发送，数据接收及查错处理
//
//////////////////////////////////////////////////////////////////////////
#pragma once
#include "MsgManager.h"
#include <string>
using namespace std;
class CErrorProcess				//错误处理类
{
public:
	CErrorProcess();
public:
	~CErrorProcess(void);
	
public:
	int GetErrorCode ();
	void SetErrorCode (int errorCode, bool isCommandError = false);
	//void SetErrCommandCode(int errorCommandCode);
	void GetErrorMsg (string strType,string& strError);
	void ClearErrorCode();
	
protected:
private:
	int errorCode;
	bool isCommandError;
	CMsgManager msgError;

};
