#pragma once
#include "Global.h"
#include "WIRELESSRFIDAPIEXPORT.h"
#include <list>
using namespace std;
class CCmdBuffer
{
public:
	CCmdBuffer(int nMaxMsg);
	~CCmdBuffer(void);

	bool AddEndFrame(CRFrame* pFrame);
	CRFrame* RemoveBeginFrame();
	void ClearAll();
	int GetFrameCount();
private:
	CRITICAL_SECTION m_critial;
	list<CRFrame*> m_FrameList;
	int mMaxMsg;
};
