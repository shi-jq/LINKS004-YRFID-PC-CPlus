#include "StdAfx.h"
#include "CmdBuffer.h"

CCmdBuffer::CCmdBuffer(void)
{
	InitializeCriticalSection(&m_critial);
	
}

CCmdBuffer::~CCmdBuffer(void)
{
	DeleteCriticalSection(&m_critial);
}


bool CCmdBuffer::SetCmdResult(CRFrame& RFIDFrame)
{	
	EnterCriticalSection(&m_critial);

	int frameNum = (RFIDFrame.bAddrInfo & 0x0f) ;	
	int nCommand = RFIDFrame.bCommand ;
	map<int,CRFIDFrame*>::iterator itor = m_CommandList.find( RFIDFrame.bCommand );
	if( itor == m_CommandList.end() )
	{
		LeaveCriticalSection(&m_critial);
		return false;
	}

	CRFIDFrame* pInFrame = itor->second;

	if( ( RFIDFrame.bAddrInfo&0x0f) != (pInFrame->RFIDInFrame.bAddrInfo&0x0f) )
	{
		LeaveCriticalSection(&m_critial);
		return false;
	}

	//OutputDebugString(L"ÉèÖÃÐÅºÅ");
	memcpy((void*)&pInFrame->RFIDOutFrame,(void*)&RFIDFrame,sizeof(CRFrame));
	
	pInFrame->SetSigle();
	LeaveCriticalSection(&m_critial);
	return true;
}

bool CCmdBuffer::CheckCmdExist(unsigned char nCommand)
{
	EnterCriticalSection(&m_critial);

	map<int,CRFIDFrame*>::const_iterator itor = m_CommandList.find( nCommand );
	if( itor == m_CommandList.end() )
	{
		LeaveCriticalSection(&m_critial);
		return false;
	}

	LeaveCriticalSection(&m_critial);
	return true;
}

bool CCmdBuffer::AddCmd(CRFIDFrame* RFIDFrame)
{
	EnterCriticalSection(&m_critial);

	map<int,CRFIDFrame*>::iterator itor = m_CommandList.find( RFIDFrame->RFIDInFrame.bCommand );
	if( itor != m_CommandList.end() )
	{
		LeaveCriticalSection(&m_critial);
		return false;
	}

	//char szBuffer[MAX_PATH];
	//memcpy(szBuffer,0,MAX_PATH);
	//sprintf_s(szBuffer,"%d-%d",RFIDFrame->bCommand,);

	typedef pair <int, CRFIDFrame*> Int_Pair; 
	m_CommandList.insert(Int_Pair(RFIDFrame->RFIDInFrame.bCommand,RFIDFrame));

	LeaveCriticalSection(&m_critial);
	return true;
}


bool CCmdBuffer::DelCmd(CRFIDFrame* RFIDFrame)
{
	EnterCriticalSection(&m_critial);
	map<int,CRFIDFrame*>::iterator itor = m_CommandList.find( RFIDFrame->RFIDInFrame.bCommand );
	if( itor == m_CommandList.end() )
	{
		LeaveCriticalSection(&m_critial);
		return true;
	}

	itor->second->CloseSigle();

	m_CommandList.erase(itor);
	LeaveCriticalSection(&m_critial);
	return true;
}

 