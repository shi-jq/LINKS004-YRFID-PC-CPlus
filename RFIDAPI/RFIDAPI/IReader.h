#pragma once

#include "Global.h"
class IReader
{
public:
	IReader(void);
	virtual bool Open(CRFIDSystemCfg& cfg) = 0;//������
	virtual bool Stop(void) = 0;//ֹͣ
	virtual bool Close(void) = 0 ;//�ر�����
	virtual bool TestHeart() = 0 ;//״̬���
	virtual bool SetMsgResult(CRFrame& RFIDFrame) = 0;//���÷��ؽ��
	virtual void SetErrorCode(int nErrorCode,bool bCommandError = false) = 0;//���ô�����
	virtual int  GetErrorCode() = 0 ;//�õ�������
	virtual void GetErrorMsg(char *szMsg,int nLen) = 0 ;//�õ�������Ϣ
	virtual void ClearErrorCode() = 0;//���������Ϣ
public:
	virtual ~IReader(void);
};
