#include "readerdllbase.h"
#include "RFIDAPIEXPORT.h"
#include "appconfig.h"
#include "LanguageSrc.h"

ReaderDllBase::ReaderDllBase()
{
	m_hCom = INVALID_HANDLE_VALUE;
    //(void *)m_hCom = NULL;
	mState = STATE_DISABLE;
}

bool ReaderDllBase::ConnetReader()
{
	bool bResult = false;
	if (mState == STATE_DISABLE )
	{
		if (mLinkInfo.mconnetType == Connet_TCP)
		{
			bResult = SAAT_TCPInit(
				&m_hCom,
				mLinkInfo.mIpAddr.toUtf8().data(),
				mLinkInfo.nPort);
		}		
		else if (mLinkInfo.mconnetType == Connet_COM)
		{

			bResult = SAAT_COMInit(
				&m_hCom,
				0x00,
				mLinkInfo.mComStr.toUtf8().data(),
				mLinkInfo.nBaudRate);
		}
		else if (mLinkInfo.mconnetType == Connet_USB)
		{

			bResult = SAAT_USBInit(
				&m_hCom,
				0x00,
				mLinkInfo.mComStr.toUtf8().data(),
				mLinkInfo.nBaudRate);
		}
		else if (mLinkInfo.mconnetType == Connet_UDP)
		{

			bResult = SAAT_UDPInit(
				&m_hCom,
				mLinkInfo.mIpAddr.toUtf8().data(),
				mLinkInfo.nPort);
		}
	}

	if (bResult)
	{
		bResult = SAAT_Open(m_hCom); 
	}

	if(bResult)
	{
		mState = STATE_CONNET;		
	}
	else
	{		
		mState = STATE_DISABLE;	
	}	

	return bResult;
}

bool ReaderDllBase::CloseReader()
{
	SAAT_Close(m_hCom);
	m_hCom = INVALID_HANDLE_VALUE;
	mState = STATE_DISABLE;
	return true;
}

bool ReaderDllBase::CheckState(int readerState)
{
	return mState == readerState;
}

bool ReaderDllBase::SetState(int readerState)
{
	mState = readerState;
	return true;
}

int ReaderDllBase::GetState()
{
	return mState;
}

void ReaderDllBase::SetTcpConnetInfo(const QString ipAddr,int nPort)
{
	mLinkInfo.nPort = nPort;
	mLinkInfo.mIpAddr = ipAddr;
	mLinkInfo.mconnetType = Connet_TCP;
}

void ReaderDllBase::SetComConnetInfo(const QString ComStr,int nBaudRate)
{
	mLinkInfo.mconnetType = Connet_COM;
	mLinkInfo.mComStr = ComStr;
	mLinkInfo.nBaudRate = nBaudRate;

}

bool ReaderDllBase::StopRead()
{
	return false;
}

bool ReaderDllBase::ApiCopyright(char* copyright)
{
	return SAAT_Copyright(&m_hCom,copyright);
}

void ReaderDllBase::SetUdpConnetInfo(const QString ipAddr,int nPort)
{
	mLinkInfo.nPort = nPort;
	mLinkInfo.mIpAddr = ipAddr;
	mLinkInfo.mconnetType = Connet_UDP;
}

void ReaderDllBase::SetUsbConnetInfo(const QString ComStr,int nBaudRate)
{
	mLinkInfo.mconnetType = Connet_USB;
	mLinkInfo.mComStr = ComStr;
	mLinkInfo.nBaudRate = nBaudRate;
}

int ReaderDllBase::GetErrorCode()
{
	int nCode = 0;
	SAAT_GetErrorCode(m_hCom,&nCode);
	return nCode;
}

ReaderDllBase::~ReaderDllBase()
{
	m_hCom = INVALID_HANDLE_VALUE;
    m_hCom = NULL;
}

ReaderLinkInfo ReaderDllBase::GetLinkInfo()
{
	return mLinkInfo;
}

bool ReaderDllBase::GetReaderType(QString &ReaderType)
{	
	if (!this->CheckState(STATE_CONNET))
	{	
		return false;
	}
	int index = 1;
	bool bRet = false;
	unsigned char btParams[BYTE_BUFFER_SIZE];
	unsigned char size = BYTE_BUFFER_SIZE;
	ZeroMemory(btParams,BYTE_BUFFER_SIZE);

	bRet = SAAT_SysInfQuery(this->m_hCom,
		index,
		btParams,
		&size);

	if (bRet)
	{
		ReaderType = QString::fromUtf8((char*)btParams);
	}

	return bRet;
}

QString ReaderDllBase::GetStateStr()
{
	switch(mState)
	{
	case  STATE_DISABLE:
		return GET_TXT("IDCS_NO_LINK");
		break;
	case STATE_DISCONNET:
		return GET_TXT("IDCS_NO_LINK");
		break;
	case STATE_CONNET:
		return GET_TXT("IDCS_LINKED");
		break;
	case STATE_READING:
		return GET_TXT("IDCS_READING");
		break;
	default:
		break;
	}

	return QString("");
}

