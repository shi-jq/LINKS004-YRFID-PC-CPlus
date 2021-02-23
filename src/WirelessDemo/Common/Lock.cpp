#include "StdAfx.h"
#include "Lock.h"
#include "assert.h"
//================== CLock =======================
CLock::CLock(void)
{
	InitializeCriticalSection(&m_Section);
}

CLock::~CLock(void)
{
	DeleteCriticalSection(&m_Section);
}

void CLock::Lock()
{
	EnterCriticalSection(&m_Section);
}

void CLock::Unlock()
{
	LeaveCriticalSection(&m_Section);
}


//===================== CMyEvent ===========================
CMyEvent::CMyEvent(bool bManualReset)
{
	m_hObject=CreateEvent(NULL,bManualReset,FALSE,NULL);
}

CMyEvent::~CMyEvent()
{
	CloseHandle(m_hObject);
}

bool CMyEvent::SetEvent()
{
	return !!::SetEvent(m_hObject);
}

bool CMyEvent::ResetEvent()
{
	return !!::ResetEvent(m_hObject);
}

UINT CMyEvent::WaitEvent(UINT timeout)
{
	return WaitForSingleObject(m_hObject,timeout);
}

//=================== CMySemaphore ================================
CMySemaphore::CMySemaphore(UINT lInitCount, UINT lMaxCount)
{
	assert(lMaxCount > 0);
	m_hObject = CreateSemaphore(NULL,lInitCount,lMaxCount,NULL);
	assert(m_hObject != INVALID_HANDLE_VALUE);
}

CMySemaphore::~CMySemaphore(void)
{
	if (m_hObject != INVALID_HANDLE_VALUE)
	{
		CloseHandle(m_hObject);
	}
}

bool CMySemaphore::lock(UINT dwTimeout)
{
	if (m_hObject != INVALID_HANDLE_VALUE)
	{
		return WaitForSingleObject(m_hObject, dwTimeout) == WAIT_OBJECT_0;
	}

	return false;
}

bool CMySemaphore::unlock(void)
{
	return unlock(1, NULL);
}

bool CMySemaphore::unlock(UINT lReleaseCount, UINT* lpPreviousCount)
{
	if (m_hObject != INVALID_HANDLE_VALUE)
	{
		return !!ReleaseSemaphore(m_hObject, lReleaseCount, (LPLONG)lpPreviousCount);
	}

	return false;
}

UINT WaitForMultipleObjects(UINT nCount, const CMyEvent** lpEvents, bool fWaitAll, UINT dwMilliseconds)
{
	HANDLE *lpHandls = new HANDLE[nCount];
	UINT dwRet;
	for (int i=0; i<(int)nCount; i++) lpHandls[i] = lpEvents[i]->m_hObject;
	dwRet = ::WaitForMultipleObjects(nCount, (const HANDLE*)lpHandls, fWaitAll, dwMilliseconds);
	delete [] lpHandls;
	return dwRet;
}


CNameLock::CNameLock(const char *szName)
{
	m_hLock = ::CreateMutexA(NULL, FALSE, szName);
}

CNameLock::~CNameLock(void)
{
	::CloseHandle(m_hLock);
}

void CNameLock::Lock(void)
{
	::WaitForSingleObject(m_hLock, INFINITE);
}

void CNameLock::Unlock(void)
{
	::ReleaseMutex(m_hLock);
}