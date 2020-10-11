#include "StdAfx.h"
#include "ConnetBase.h"
#include "RFIDReader.h"



ConnetBase::ConnetBase(CRFIDReader* pReader)
{
	mReader = pReader;
}

ConnetBase::~ConnetBase(void)
{
}

bool ConnetBase::StartRead()
{
	return false;
}

bool ConnetBase::StopRead()
{
	return  false;
}

bool ConnetBase::SendMsg(unsigned char *pSendData, int dataLength)
{
	return false;
}

void ConnetBase::SetErrorCode(int nErrorCode,bool bCommandError /*= false*/)
{
	if( mReader != NULL )
	{
		mReader->SetErrorCode(nErrorCode);
	}
}	
