#pragma once
#include "Singleton.h"

class BuzzerSpeakerCtrl
{
	friend class CSingleton<BuzzerSpeakerCtrl>;
public:
	BuzzerSpeakerCtrl(void);
	~BuzzerSpeakerCtrl(void);

	void OpenBuzzer();

	void OpenBuzzer(int time);
private:
	unsigned int m_iflag;
	
private:
	void BuzzerPlay(unsigned int * freq, unsigned int* time);
	int BuzzerSpeaker(unsigned   int   freq,unsigned   int   delay);
};
