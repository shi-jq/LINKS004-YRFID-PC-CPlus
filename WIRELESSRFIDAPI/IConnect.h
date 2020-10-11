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
	void SetErrorCode(int nErrorCode,bool bCommandError = false);//���ô�����

	IDataProc *m_pDataPrcoessInterface;//���ݴ���ӿ�
	void *pHandle;
private:
	
public:
	virtual ~IConnect(void);
};
