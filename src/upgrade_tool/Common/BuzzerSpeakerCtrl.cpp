#include "BuzzerSpeakerCtrl.h"
#include <windows.h>

BuzzerSpeakerCtrl::BuzzerSpeakerCtrl(void)
{
}

BuzzerSpeakerCtrl::~BuzzerSpeakerCtrl(void)
{
}

void BuzzerSpeakerCtrl::OpenBuzzer()
{
	unsigned   int   freq_alert[]={ 6000,   0	}; 
	unsigned   int   time_alert[]={  //50,   60
		200};  
		m_iflag = 0;

	BuzzerPlay(freq_alert, time_alert); 
	 
}

void BuzzerSpeakerCtrl::OpenBuzzer(int time)
{
	unsigned   int   freq_alert[]={ 3500,   0	};
	unsigned   int   time_alert[1] = {0};
	time_alert[0] = time;
	BuzzerPlay(freq_alert, time_alert); 
}

void BuzzerSpeakerCtrl::BuzzerPlay(unsigned int * freq, unsigned int* time)
{
	int   i;  
	for(i=0;freq[i]!=0;i++)  
	{  
		BuzzerSpeaker(freq[i],   time[i]);  
	}  
}

int BuzzerSpeakerCtrl::BuzzerSpeaker(unsigned int freq,unsigned int delay)
{
	Beep(freq,delay);
	return 0;
}
