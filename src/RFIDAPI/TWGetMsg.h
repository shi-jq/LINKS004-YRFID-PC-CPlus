#pragma once
#include "igetmsginterface.h"

class CTWGetMsg :
	public IGetMsgInterface
{
public:
	CTWGetMsg(void);
public:
	virtual ~CTWGetMsg(void);
	virtual void GetErrorMsg(int nCode,string& strError) ;
private:
	map<int,wstring> m_mapError;
};
extern CErrorStruct errorTWMsg[];
