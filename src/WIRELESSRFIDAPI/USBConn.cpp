#include "StdAfx.h"
#include "USBConn.h"
#include "RFIDReader.h"
#include <process.h>
#include <comdef.h>

DWORD WINAPI StartUSBRevThread(LPVOID p)
{
	CUSBConn *pThis = (CUSBConn*)p;
	int nErrorTimes = 0;
	unsigned char pForRev[MAX_PATH] = {0};
	while( !pThis->m_bThExit )
	{
		int revQty = 0 ;
		memset(pForRev,0,MAX_PATH);
		if( !pThis->ComRecv(pForRev,revQty) ) //200秒超时
		{
			Sleep(20);
		}
		
		if( pThis->mReader != NULL )
		{
			pThis->mReader->MsgProcess(pForRev,revQty);
		}		

	}

	CloseHandle(pThis->m_hThread);
	pThis->m_hThread = NULL;
	SetEvent(pThis->m_ThreadExitEvent);
	return 0;
}

CUSBConn::CUSBConn(CRFIDReader* pReader)
	:ConnetBase(pReader)
{
	bExit = false;
	m_bOpened = false;
	m_hThread = NULL;
	m_bThExit = false;
	m_ThreadExitEvent = CreateEvent(NULL,FALSE,FALSE,NULL);
}

CUSBConn::~CUSBConn(void)
{
	CloseConn();
	if( NULL != m_ThreadExitEvent)
	{
		CloseHandle(m_ThreadExitEvent);
		m_ThreadExitEvent = NULL;
	}
}

void CUSBConn::LoadData(unsigned char nBusAddr,char *pComNum,int nBaud)
{
	mStrComNum = pComNum;
	mBaud = nBaud;
	mBusAddr = nBusAddr;
}

bool CUSBConn::StartRead()
{
	bool bRet = OpenConn();

	if (bRet)
	{
		bRet = Svr();
		if (!bRet)
		{
			ClosePort();
		}
	}

	return bRet;
}

bool CUSBConn::StopRead()
{
	return CloseConn();
}

bool CUSBConn::SendMsg(unsigned char *pSendData, int dataLength)
{
	if( !m_bOpened )
	{
		SetErrorCode(ERR_NOT_CONNECT);
		return false;
	}


	if(	NULL == pSendData ||
		0 == dataLength )
	{
		SetErrorCode(ERR_POINTER_NULL);
		return false;
	}

	if( !ComSend(pSendData,dataLength) )
	{
		return false;
	}

	if( !Svr() )
	{
		return false;
	}

	return true;
}

bool CUSBConn::ComRecv(unsigned char* pRecv,int& nSize)
{
	nSize = 0;
	if(!m_bOpened||pHandle == INVALID_HANDLE_VALUE)
	{
		return false;
	}

	DWORD dwOldMask = 0;

	BOOL   bReadStatus;   
	DWORD dwBytesRead = 0;

	dwBytesRead = 255;  
	bReadStatus = ReadFile(pHandle,pRecv,dwBytesRead,&dwBytesRead,NULL);   
	if(bReadStatus)
	{   
		nSize = dwBytesRead;
		return true;
	}   
	SetErrorCode(ERR_FRAME_LOSE);
	return false;
}

bool CUSBConn::OpenConn()
{
	
	_bstr_t bstrPort = _bstr_t("\\\\.\\") + mStrComNum.c_str();

	pHandle = CreateFile(bstrPort, 
		GENERIC_WRITE|GENERIC_READ,
		NULL,
		NULL,
		OPEN_EXISTING,
		NULL,
		NULL);
	if( pHandle == INVALID_HANDLE_VALUE)
	{
		DWORD nErrorCode = GetLastError();
		SetErrorCode(ERR_COMOPEN_FAIL);
		return false;
	}

	bool bRet = false;
	do 
	{
		DCB    mDCB;
		if( !GetCommState(pHandle,&mDCB) )
		{
			SetErrorCode(ERR_GETCOM_STATE);
			break;
		}

		mDCB.BaudRate=this->mBaud;
		mDCB.ByteSize=8;
		mDCB.Parity=NOPARITY;
		if( !SetCommState(pHandle,&mDCB) )
		{
			SetErrorCode(ERR_SETCOM_STATE);
			break;
		}

		COMMTIMEOUTS ctout;
		if( !GetCommTimeouts(pHandle,&ctout) )
		{
			SetErrorCode(ERR_GETCOM_TIMEOUT);
			break;
		}

		ctout.ReadIntervalTimeout=MAXDWORD;
		ctout.ReadTotalTimeoutConstant=0;
		ctout.ReadTotalTimeoutMultiplier=0;
		if( !SetCommTimeouts(pHandle,&ctout) )
		{
			SetErrorCode(ERR_SETCOM_TIMEOUT);
			break;
		}
		bRet = true;
	}while(0);

	if( !bRet)
	{
		CloseHandle(pHandle);
		return false;
	}

	m_bOpened = true;
	return true;
}

bool CUSBConn::WriteCommByte(unsigned char ucByte)
{
	BOOL   bWriteStat;   
	DWORD   dwBytesWritten;   

	bWriteStat = WriteFile(pHandle,(char*)&ucByte,1,&dwBytesWritten,NULL); 
	if ( 0 != bWriteStat && 0 != dwBytesWritten )
	{
		return true;
	}

	return false;
}

bool CUSBConn::ComSend(unsigned char* ucByte,int nSize)
{
	DWORD dWritten =0 ;
	int nRet = WriteFile(pHandle,ucByte,nSize,&dWritten,NULL);
	if ( 0 != nRet && 0 != dWritten )
	{
		return true;
	}

	return false;
}

bool CUSBConn::Svr()
{
	if( NULL == m_hThread )
	{
		m_bThExit = false;
		m_hThread = (HANDLE)_beginthreadex(NULL,
			0,
			(PBEGINTHREADEX_THREADFUNC)StartUSBRevThread,
			(LPVOID)this,
			0,
			NULL);
		if (NULL == m_hThread)
		{
			SetErrorCode(ERR_STARTREVTHREAD_FAIL);
			return false;
		}	
	}
	return true;
}

bool CUSBConn::SendRawData(unsigned char* szData,int nLen)
{
	return ComSend(szData,nLen);
}

bool CUSBConn::CloseConn()
{
	CloseThread();//关闭线程
	return ClosePort();//关闭端口
}

bool CUSBConn::ClosePort()
{
	if( !m_bOpened ||
		pHandle==INVALID_HANDLE_VALUE )
	{
		return true;
	}

	CloseHandle(pHandle);

	m_bOpened   =   FALSE;   
	pHandle   =   NULL;  

	return true;
}

bool CUSBConn::CloseThread()
{
	m_bThExit = true; //关闭线程
	if( m_hThread != NULL )
	{
		WaitForSingleObject(m_ThreadExitEvent,INFINITE);
	}
	return true;
}
