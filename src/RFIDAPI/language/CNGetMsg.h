#pragma once
#include "igetmsginterface.h"

class CCNGetMsg :
	public IGetMsgInterface
{
public:
	CCNGetMsg(void);
public:
	virtual~CCNGetMsg(void);
	virtual void GetErrorMsg(int nCode,string& strError) ;
private:
	map<int,wstring> m_mapError;
};
extern CErrorStruct errorCNMsg[];
