#pragma once
#include "igetmsginterface.h"

class CENGetMsg :
	public IGetMsgInterface
{
public:
	CENGetMsg(void);
public:
	virtual ~CENGetMsg(void);
	virtual void GetErrorMsg(int nCode,string& strError) ;
private:
	map<int,wstring> m_mapError;
};
extern CErrorStruct errorENMsg[];

