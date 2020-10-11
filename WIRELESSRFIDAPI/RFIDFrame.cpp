#include "StdAfx.h"
#include "RFIDFrame.h"

CRFIDFrame::CRFIDFrame(void)
{
	memset(&RFIDInFrame,0,sizeof(CRFrame));
	memset(&RFIDOutFrame,0,sizeof(CRFrame));
}


CRFIDFrame::~CRFIDFrame(void)
{

}

