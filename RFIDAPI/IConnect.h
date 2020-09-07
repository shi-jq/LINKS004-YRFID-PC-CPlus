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
	virtual void SetHeartTime(int nHeartTime) = 0;
	virtual void LoadData(CRFIDSystemCfg& initSystemCfg) = 0;//初始化参数
	virtual bool OpenConn() = 0;//打开连接
	virtual bool CheckConnState() = 0;//connState 为 0 表示连接打开,返回true
	virtual bool SendMsg(unsigned char *pSendData, int dataLength) = 0;
	virtual bool RevMsg(unsigned char *pRevMsg,unsigned char *pDataLen,int nWaitTime) = 0;
	virtual bool CloseConn() = 0;//关闭连接
	virtual bool ClosePort() = 0;//关闭端口
	virtual bool CloseThread() = 0;//用于传输AT指令而关闭串口接收线程
	void SetErrorCode(int nErrorCode,bool bCommandError = false);//设置错误码
	IDataProc *m_pDataPrcoessInterface;//数据处理接口
	void *pHandle;
private:
	
public:
	virtual ~IConnect(void);
};
