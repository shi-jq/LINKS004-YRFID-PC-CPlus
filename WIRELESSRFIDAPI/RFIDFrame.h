#pragma once
#include "Global.h"
#include "Lock.h"
#include "WIRELESSRFIDAPIEXPORT.h"

struct CRFIDFrame
{
	CRFrame RFIDInFrame;//���͵�����
	CRFrame RFIDOutFrame;//���յĻ�Ӧ
	CMyEvent m_revHandle;//�����ź�
	CRFIDFrame();
	~CRFIDFrame();	
};
