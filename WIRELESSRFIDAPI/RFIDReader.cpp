#include "StdAfx.h"
#include "RFIDReader.h"
#include <Winsock2.h>
#include<time.h>
#include "Global.h"
#include "ConnetCreater.h"

CRFIDReader::CRFIDReader(READERTYPE readerType,SOCKET& sockConn)
{
	
	mConnetBase = CSingleton<ConnetCreater>::GetInstance()->
		CreateTcpServerConnet(this,sockConn);

	Init();
}

CRFIDReader::CRFIDReader(READERTYPE readerType,char *pHostName,int nsocketPort)
{
	if (readerType == READER_TCP_CLIENT)
	{
		mConnetBase = CSingleton<ConnetCreater>::GetInstance()->
			CreateTcpClientConnet(this,pHostName,nsocketPort);
	}
	else if(readerType == READER_UDP)
	{
		mConnetBase = CSingleton<ConnetCreater>::GetInstance()->
			CreateUdpClientConnet(this,pHostName,nsocketPort);
	}
	else
	{
		mConnetBase = NULL;
	}
	
	Init();
}

CRFIDReader::CRFIDReader(READERTYPE readerType,unsigned char nBusAddr,char *pComNum,int nBaud)
{
	if (readerType == READER_COM)
	{
		mConnetBase = CSingleton<ConnetCreater>::GetInstance()->
			CreateComClientConnet(this,nBusAddr,pComNum,nBaud);
	}
	else if (readerType == READER_USB)
	{
		mConnetBase = CSingleton<ConnetCreater>::GetInstance()->
			CreateUsbClientConnet(this,nBusAddr,pComNum,nBaud);
	}
	else
	{
		mConnetBase = NULL;
	}
	
	Init();
}

void CRFIDReader::Init()
{
	m_DataProcss = new CDataProc(this);
	m_ReadState = READ_IDLE;	

	m_RecvMsgFrame = new CCmdBuffer(MSG_MAX_BUFFER);
	m_CardIDBuffer.Init(MSG_MAX_BUFFER);
	m_IOStateBuffer.Init(MSG_MAX_BUFFER);

	initLastTime();
}

CRFIDReader::~CRFIDReader(void)
{
	StopRead();
	if (mConnetBase)
	{
		delete mConnetBase;
		mConnetBase = NULL;
	}

	if (m_DataProcss)
	{
		delete m_DataProcss;
		m_DataProcss = NULL;
	}
}


bool CRFIDReader::StartRead()
{
	bool retB =	mConnetBase->StartRead();
	return retB;
}


bool CRFIDReader::StopRead()
{
	bool retB = mConnetBase->StopRead();
	return retB;
}


bool CRFIDReader::UpdateSocket(SOCKET& sockConn)
{
	bool retB = ((CTCPProcCtrl*)mConnetBase)->UpdateSocket(sockConn);
	return retB;
}

bool CRFIDReader::MsgProcess(unsigned char* revData,int revLength)
{
	return m_DataProcss->MsgProcess(revData,revLength);
}

bool CRFIDReader::SetMsgResult( CRFrame& RFIDFrame)
{	
	SYSTEMTIME sysTime;
	GetLocalTime(&sysTime);
	struct tm tmp;
	memset(&tmp,0,sizeof(tmp));
	tmp.tm_year=sysTime.wYear-1900;
	tmp.tm_mon=sysTime.wMonth-1;
	tmp.tm_mday=sysTime.wDay;
	tmp.tm_hour=sysTime.wHour;
	tmp.tm_min=sysTime.wMinute;
	tmp.tm_sec=sysTime.wSecond;
	tmp.tm_isdst = -1;				//必须为-1,否则在夏令时区会快一个小时
	mLastTime = mktime(&tmp);

	unsigned char nCommand = RFIDFrame.bCommand;

	if( nCommand == COM_YSEND_READID ||
		nCommand == COM_YMAKE_TAGUPLOAD )
	{
		if (RFIDFrame.bLength <= 3 )
		{
			return true;
		}

		//SendRFIDAck(RFIDFrame);

		if( !m_CardIDBuffer.Add(&RFIDFrame) )
		{
			m_CardIDBuffer.Clear();
		}
		return true;
	}

	if(nCommand == COM_SEND_HEART )
	{
		return true;
	}

	CRFrame* pCRFrame = new CRFrame();
	memcpy(pCRFrame,&RFIDFrame,sizeof(RFIDFrame));

	if( !m_RecvMsgFrame->AddEndFrame(pCRFrame) )
	{
		SetErrorCode(ERR_OVER_FRAMELIST);
		m_RecvMsgFrame->ClearAll();
	}
	
	return true;
}


int CRFIDReader::SendMsg(unsigned char pCommand,
						  unsigned char *pSendData, 
						  int dataLength)
{
	int nMsgID = -1;
	bool bRet  = false;
	m_Critical.Lock();
	do 
	{
		//装包	
		mForSendLen = 0;
		memset(mForSend,0,CMD_DATA_BUFFER);
		nMsgID = m_DataProcss->PackMsg(pCommand,pSendData,dataLength,mForSend,&mForSendLen);
	
		if( !m_DataProcss->SendMsg(pCommand,mForSend,mForSendLen) )//发送消息
		{
			break;
		}	

		bRet = true;
	}while (0);

	m_Critical.Unlock();
	if(!bRet)
	{
		nMsgID = -1;
	}
	return nMsgID;
}

bool CRFIDReader::SendData(unsigned char *pSendData, int dataLength)
{
	return mConnetBase->SendMsg(pSendData,dataLength);
}

void CRFIDReader::SetErrorCode(int dwErrorCode,bool bCommandError /*= false*/)
{
	DWORD dwErrorID = GetCurrentThreadId();
	typedef pair <DWORD, int> DW_Pair; 

	map<DWORD,int>::iterator itor = map_Error.find(dwErrorID);
	if( itor != map_Error.end() )
	{
		itor->second = dwErrorCode;

	}
	map_Error.insert( DW_Pair(dwErrorID,dwErrorCode) );
}

bool CRFIDReader::GetRecvMsg(CRFrame& RFIDFrame)
{
	CRFrame* pCRFrame = m_RecvMsgFrame->RemoveBeginFrame();
	if (pCRFrame)
	{
		memcpy(&RFIDFrame,pCRFrame,sizeof(CRFrame));
		delete pCRFrame;
		pCRFrame = NULL;
		return true;
	}

	return false;
}

bool CRFIDReader::SetReadState(ReadState state)
{	
	m_ReadState = state;
	return true;
}


bool CRFIDReader::SendRFIDAck(CRFrame& RFIDFrame)
{
	if ( dynamic_cast<CTCPProcCtrl*>(mConnetBase) == NULL )
	{
		return true;
	}
	unsigned char pSendData[2];
	unsigned char ucCommand =  WIRELESS_RFID_ACK;
	unsigned int sendLen = RFIDFrame.bLength+6;
	pSendData[0] = ((sendLen>>8)&0xff);
	pSendData[1] = ((sendLen)&0xff);
	if ( !SendMsg( ucCommand, pSendData, 2))
	{
		return false;
	}

	return true;
}


bool CRFIDReader::SendRFIDIOStateAck(CRFrame& RFIDFrame)
{
	if ( dynamic_cast<CTCPProcCtrl*>(mConnetBase) == NULL )
	{
		return true;
	}
	unsigned char pSendData[DATA_BUFFER];
	unsigned char ucCommand =  WIRELESS_RFID_IO_STATE_ACK;
	unsigned int sendLen = RFIDFrame.bLength-1;
	memcpy(pSendData,RFIDFrame.bData,sendLen);

	if ( !SendMsg( ucCommand, pSendData, sendLen))
	{
		return false;
	}

	return true;
}


int CRFIDReader::GetErrorCode()
{	
	DWORD dwErrorID = GetCurrentThreadId();
	typedef pair <DWORD, int> DW_Pair; 

	map<DWORD,int>::const_iterator itor = map_Error.find(dwErrorID);
	if( itor != map_Error.end() )
	{
		return itor->second ;
	}

	return 0;
}

bool CRFIDReader::GetCard(CRFrame& RFIDFrame,int nWaitTime )
{
	/*if( WAIT_OBJECT_0 != WaitForSingleObject(m_CardIDBuffer.GetSingle(),nWaitTime ) )
	{
		return false;
	}

	return m_CardIDBuffer.RemoveHead(RFIDFrame);*/

	if (m_CardIDBuffer.Length() > 0)
	{
		return	 m_CardIDBuffer.RemoveHead(RFIDFrame);
	}

	return false;
}


bool CRFIDReader::GetIOState(CRFrame& RFIDFrame,int nWaitTime)
{
	if (m_IOStateBuffer.Length() > 0)
	{
		return	 m_IOStateBuffer.RemoveHead(RFIDFrame);
	}
	
	return false;
}


void CRFIDReader::initLastTime()
{
	SYSTEMTIME sysTime;
	GetLocalTime(&sysTime);
	struct tm tmp;
	memset(&tmp,0,sizeof(tmp));
	tmp.tm_year=sysTime.wYear-1900;
	tmp.tm_mon=sysTime.wMonth-1;
	tmp.tm_mday=sysTime.wDay;
	tmp.tm_hour=sysTime.wHour;
	tmp.tm_min=sysTime.wMinute;
	tmp.tm_sec=sysTime.wSecond;
	tmp.tm_isdst = -1;				//必须为-1,否则在夏令时区会快一个小时
	mLastTime = mktime(&tmp);
}

bool CRFIDReader::SendRFIDHeartStateAck(CRFrame& RFIDFrame)
{
	if ( dynamic_cast<CTCPProcCtrl*>(mConnetBase) == NULL )
	{
		return true;
	}
	unsigned char pSendData[DATA_BUFFER];
	unsigned char ucCommand =  WIRELESS_RFID_Heart_ACK;
	unsigned int sendLen = RFIDFrame.bLength-1;
	memcpy(pSendData,RFIDFrame.bData,sendLen);

	if ( !SendMsg( ucCommand, pSendData, sendLen))
	{
		return false;
	}

	return true;
}

bool CRFIDReader::CheckTimeOut()
{
	SYSTEMTIME sysTime;
	GetLocalTime(&sysTime);
	struct tm tmp;
	memset(&tmp,0,sizeof(tmp));
	tmp.tm_year=sysTime.wYear-1900;
	tmp.tm_mon=sysTime.wMonth-1;
	tmp.tm_mday=sysTime.wDay;
	tmp.tm_hour=sysTime.wHour;
	tmp.tm_min=sysTime.wMinute;
	tmp.tm_sec=sysTime.wSecond;
	tmp.tm_isdst = -1;				//必须为-1,否则在夏令时区会快一个小时
	unsigned long  nowTime = mktime(&tmp);
	if(nowTime - mLastTime > 3)
	{
		return false;
	}

	return true;
}

