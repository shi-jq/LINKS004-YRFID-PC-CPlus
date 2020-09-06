#pragma once
#include "Global.h"
#include <map>
using namespace std;

#include "IDataProc.h"
class IConnect //ͨѶ�ӿ���
{
public:
	IConnect();
	virtual void InitConnect(IDataProc * pDataProc) = 0;//��ʼ��IDataProcָ��
	virtual void SetHeartTime(int nHeartTime) = 0;
	virtual void LoadData(CRFIDSystemCfg& initSystemCfg) = 0;//��ʼ������
	virtual bool OpenConn() = 0;//������
	virtual bool CheckConnState() = 0;//connState Ϊ 0 ��ʾ���Ӵ�,����true
	virtual bool SendMsg(unsigned char *pSendData, int dataLength) = 0;
	virtual bool RevMsg(unsigned char *pRevMsg,unsigned char *pDataLen,int nWaitTime) = 0;
	virtual bool CloseConn() = 0;//�ر�����
	virtual bool ClosePort() = 0;//�رն˿�
	virtual bool CloseThread() = 0;//���ڴ���ATָ����رմ��ڽ����߳�
	void SetErrorCode(int nErrorCode,bool bCommandError = false);//���ô�����
	IDataProc *m_pDataPrcoessInterface;//���ݴ���ӿ�
	void *pHandle;
private:
	
public:
	virtual ~IConnect(void);
};
