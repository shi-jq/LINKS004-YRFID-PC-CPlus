#pragma once

#include "Global.h"
class IReader
{
public:
	IReader(void);
	virtual bool Open(CRFIDSystemCfg& cfg) = 0;//打开连接
	virtual bool Stop(void) = 0;//停止
	virtual bool Close(void) = 0 ;//关闭连接
	virtual bool TestHeart() = 0 ;//状态检测
	virtual bool SetMsgResult(CRFrame& RFIDFrame) = 0;//设置返回结果
	virtual void SetErrorCode(int nErrorCode,bool bCommandError = false) = 0;//设置错误码
	virtual int  GetErrorCode() = 0 ;//得到错误码
	virtual void GetErrorMsg(char *szMsg,int nLen) = 0 ;//得到错误信息
	virtual void ClearErrorCode() = 0;//清除错误信息
public:
	virtual ~IReader(void);
};
