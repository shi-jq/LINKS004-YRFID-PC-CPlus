#pragma once

class CheckTime
{
public:
	CheckTime(void);
	~CheckTime(void);

	static int CheckTimeout(unsigned int start, unsigned int hasElapsed);
	static unsigned long GetSysTickCount();
};
