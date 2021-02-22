#pragma once
#include "Global.h"
#include <map>
using namespace std;
class CCmdBuffer
{
public:
	CCmdBuffer(void);
	bool CheckCmdExist(unsigned char nCommand);
	bool AddCmd(CRFIDFrame* RFIDFrame);
	bool DelCmd(CRFIDFrame* RFIDFrame);
	bool SetCmdResult(CRFrame& RFIDFrame);
	map<int,CRFIDFrame*> m_CommandList;
private:
	CRITICAL_SECTION m_critial;
public:
	~CCmdBuffer(void);
};
