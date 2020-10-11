#pragma once
#include "Global.h"
#include <map>
using namespace std;

#include "IDataProc.h"
class IConnect //通讯接口类
{
public:
	IConnect();
	virtual void InitConnect(IDataProc * pDataProc) = 0;//初始化IDataProc指针
	void SetErrorCode(int nErrorCode,bool bCommandError = false);//设置错误码

	IDataProc *m_pDataPrcoessInterface;//数据处理接口
	void *pHandle;
private:
	
public:
	virtual ~IConnect(void);
};
