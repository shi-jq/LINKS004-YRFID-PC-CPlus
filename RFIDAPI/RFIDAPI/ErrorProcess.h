//////////////////////////////////////////////////////////////////////////
//RFIDAPI �ײ����1.0
//����ߣ�
//�������ڣ�2008��8��25
//˵���� ��������ҪΪRFIDAPI�ṩ�ײ���񣬰���ָ��ͣ����ݽ��ռ������
//
//////////////////////////////////////////////////////////////////////////
#pragma once
#include "MsgManager.h"
#include <string>
using namespace std;
class CErrorProcess				//��������
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
