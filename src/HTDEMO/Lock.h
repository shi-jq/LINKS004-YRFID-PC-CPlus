#pragma once
#include <Windows.h>

class CLock
{
public:
	CLock(void);
	~CLock(void);
	void Lock();
	void Unlock();
private:
	CRITICAL_SECTION  m_Section;
};

class CMyEvent
{
public:
	CMyEvent(bool bManualReset = FALSE);
	~CMyEvent();

public:
	bool SetEvent();
	bool ResetEvent();
	UINT WaitEvent(UINT timeout);
	operator HANDLE(){return m_hObject;};
public:  //为了实现 WaitForMultipleObjects， 由 private改为public
	HANDLE m_hObject;
};

class CMySemaphore
{
private:
	HANDLE m_hObject;

public:
	CMySemaphore(UINT lInitCount, UINT lMaxCount = 0x7FFFFFFF);
	~CMySemaphore(void);
	bool lock(UINT dwTimeout); //减少一个信号，如果已有信号为零，则等待
	bool unlock(void);    //增加一个信号
	bool unlock(UINT lReleaseCount,UINT* lpPreviousCount = NULL);
};

inline UINT WaitForSingleObject(CMyEvent *hEvent, UINT dwMilliseconds)
{
	return hEvent->WaitEvent(dwMilliseconds);
}

UINT WaitForMultipleObjects(UINT nCount, const CMyEvent** lpEvents, bool fWaitAll, UINT dwMilliseconds);

//命名锁
class CNameLock
{
public:
	CNameLock(const char *szName);
	~CNameLock(void);

	void Lock(void);
	void Unlock(void);

private:
	HANDLE m_hLock;
};

/**************************************************************************************************************************/
//#endif // _LOCK_H_
