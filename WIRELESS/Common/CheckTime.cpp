#include <windows.h>
#include "CheckTime.h"

CheckTime::CheckTime(void)
{
}

CheckTime::~CheckTime(void)
{
}

int CheckTime::CheckTimeout(unsigned int start, unsigned int hasElapsed)
{
	unsigned long now;
	unsigned long deadline = start + hasElapsed;
	int rc = 0;

	now = GetSysTickCount();

	if (deadline < start)
	{
		// adding the deadline time made a wrap-
		// deadline is past IF: 
		//      (deadline <= now < start)
		if ((now >= deadline) && (now < start))
			rc = 1;
	}
	else if (now >= deadline)
	{
		rc = 1;
	}
	else if (now < start)
		rc = 1;

	return rc;
}

unsigned long CheckTime::GetSysTickCount()
{
	return GetTickCount();
}
