//////////////////////////////////////////////////////////////////////////
//RFIDAPI �ײ����1.0
//����ߣ�
//�������ڣ�2008��8��25
//˵���� ��������ҪΪRFIDAPI�ṩ�ײ���񣬰���ָ��ͣ����ݽ��ռ������
//
//////////////////////////////////////////////////////////////////////////
#pragma once
#include "IConnect.h"
class IFactoryConn		//����ָ��
{
public:
	IFactoryConn(void);
	virtual IConnect* ConcreteConn(int nType) = 0;
public:
	virtual ~IFactoryConn(void);

};
