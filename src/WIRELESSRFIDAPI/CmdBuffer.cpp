#include "StdAfx.h"
#include "CmdBuffer.h"

CCmdBuffer::CCmdBuffer(int nMaxMsg)
{
	InitializeCriticalSection(&m_critial);
	if (nMaxMsg < 0)
	{
		mMaxMsg = 0;	
	}
	else
	{
		mMaxMsg = nMaxMsg;	
	}
}

CCmdBuffer::~CCmdBuffer(void)
{
	ClearAll();
	DeleteCriticalSection(&m_critial);
}


bool CCmdBuffer::AddEndFrame(CRFrame* pFrame)
{
	EnterCriticalSection(&m_critial);
	if (mMaxMsg < m_FrameList.size())
	{
		LeaveCriticalSection(&m_critial);
		return false;
	}

	m_FrameList.push_back(pFrame);
	LeaveCriticalSection(&m_critial);
	return true;
}


CRFrame* CCmdBuffer::RemoveBeginFrame()
{
	CRFrame* pCRFrame = NULL;
	EnterCriticalSection(&m_critial);	
	list<CRFrame*>::iterator iter= m_FrameList.begin();
	if (iter == m_FrameList.end())
	{
		LeaveCriticalSection(&m_critial);
		return pCRFrame;
	}	
	pCRFrame = *iter;
	m_FrameList.erase(iter);	
	LeaveCriticalSection(&m_critial);
	return pCRFrame;
}

void CCmdBuffer::ClearAll()
{	
	EnterCriticalSection(&m_critial);	
	list<CRFrame*>::iterator iter= m_FrameList.begin();
	for (; iter!=m_FrameList.end(); ++iter)
	{
		delete *iter;
	}
	m_FrameList.clear();
	LeaveCriticalSection(&m_critial);
}

int CCmdBuffer::GetFrameCount()
{
	int nCount = 0;
	EnterCriticalSection(&m_critial);	
	nCount = m_FrameList.size();
	LeaveCriticalSection(&m_critial);

	return nCount;
}

