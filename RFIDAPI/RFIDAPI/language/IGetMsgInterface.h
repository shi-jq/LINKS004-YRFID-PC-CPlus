#pragma once
#include <string>
#include <map>
using namespace std;


struct CErrorStruct
{
	int nCode;
	WCHAR *szMsg;
};

class IGetMsgInterface
{
public:
	IGetMsgInterface(void);
public:
	virtual ~IGetMsgInterface(void);
	virtual void GetErrorMsg(int nCode,string& strError) = 0;
};
