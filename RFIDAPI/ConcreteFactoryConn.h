//////////////////////////////////////////////////////////////////////////
//RFIDAPI �ײ����1.0
//����ߣ�
//�������ڣ�2008��8��25
//˵���� ��������ҪΪRFIDAPI�ṩ�ײ���񣬰���ָ��ͣ����ݽ��ռ������
//
//////////////////////////////////////////////////////////////////////////
#pragma once
#include "IFactoryConn.h"
#include "IConnect.h"

class CConcreteFactoryConn :	public IFactoryConn				//ʵ������
{
public:
	CConcreteFactoryConn(void);
	IFactoryConn* Instance();						//���뵥��ģʽ���Ա�֤����ģʽ�Ͻ�����1��������
	IConnect* ConcreteConn(int nType);		//��������ʵ��
public:
	~CConcreteFactoryConn(void);
protected:
	
private:
	static IFactoryConn* instance;
};
