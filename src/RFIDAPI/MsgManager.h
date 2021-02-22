#pragma once
#include <string>
#include <map>
using namespace std;
#include "IGetMsgInterface.h"
class CMsgManager
{
public:
	CMsgManager(void);
	void CMsgManager::GetErrorMessage(string strType,int nCode,string& strMessage);
public:
	virtual ~CMsgManager(void);
private:
	map<string,IGetMsgInterface*> mapLanguage;
};
