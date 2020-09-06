#pragma once
#include "IReader.h"

class IDataProc
{
public:
	IDataProc(void);
	virtual void InitDataPorc(IReader* ReaderInterface) = 0;//初始化IReader指针
	virtual bool MsgProcess(unsigned char* revData,int revLength) = 0 ;//消息解包处理
	virtual bool TestHeart() = 0;//掉线检测
	virtual void SetErrorCode(int nErrorCode,bool bCommandError = false) = 0;//设置错误码
public:
	virtual ~IDataProc(void);
};
