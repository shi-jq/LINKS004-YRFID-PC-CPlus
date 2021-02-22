#pragma once
#include "Global.h"
#include "Lock.h"
#include "WIRELESSRFIDAPIEXPORT.h"

struct CRFIDFrame
{
	CRFrame RFIDInFrame;//发送的命令
	CRFrame RFIDOutFrame;//接收的回应
	CMyEvent m_revHandle;//接收信号
	CRFIDFrame();
	~CRFIDFrame();	
};
