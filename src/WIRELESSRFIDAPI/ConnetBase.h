#pragma once
class CRFIDReader;
class ConnetBase
{
public:
	ConnetBase(CRFIDReader* pReader);
	virtual ~ConnetBase(void);

	virtual bool StartRead();
	virtual bool StopRead();

	virtual bool SendMsg(unsigned char *pSendData, int dataLength);
	
	void SetErrorCode(int nErrorCode,bool bCommandError = false);//ÉèÖÃ´íÎóÂë
public:
	CRFIDReader* mReader;
};
