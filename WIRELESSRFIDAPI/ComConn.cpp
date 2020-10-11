#include "StdAfx.h"
#include "ComConn.h"
#include "RFIDReader.h"
#include <process.h>
#include <comdef.h>

DWORD WINAPI StartCOMRevThread(LPVOID p)
{
	COMConn *pThis = (COMConn*)p;
	int nErrorTimes = 0;
	unsigned char pForRev[COM_FRAME_ONCE] = {0};
	bool bRet =false;
	while( !pThis->m_bThExit )
	{
		
		int revQty = 0 ;
		memset(pForRev,0,COM_FRAME_ONCE);
		if( !pThis->ComRecv(pForRev,revQty) ) //200秒超时
		{
		}
		
		if( pThis->mReader != NULL )
		{
			bRet = pThis->mReader->MsgProcess(pForRev,revQty);
		}	

		if (!bRet)
		{
			Sleep(50);
		}
	}

	CloseHandle(pThis->m_hThread);
	pThis->m_hThread = NULL;
	SetEvent(pThis->m_ThreadExitEvent);
	return 0;
}

COMConn::COMConn(CRFIDReader* pReader)
	:ConnetBase(pReader)
{
	bExit = false;
	m_bOpened = false;
	m_hThread = NULL;
	m_bThExit = false;
	m_ThreadExitEvent = CreateEvent(NULL,FALSE,FALSE,NULL);

}

COMConn::~COMConn(void)
{
	CloseConn();
	if( NULL != m_ThreadExitEvent)
	{
		CloseHandle(m_ThreadExitEvent);
		m_ThreadExitEvent = NULL;
	}
}


void COMConn::LoadData(
					   unsigned char nBusAddr,
					   char *strComNum,int nBaud)
{
	mStrComNum = strComNum;
	mBaud = nBaud;
	mBusAddr = nBusAddr;
}


bool COMConn::StartRead()
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
bool COMConn::StopRead()
{
	return CloseConn();
}

bool COMConn::SendMsg(unsigned char *pSendData, int dataLength)
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

bool COMConn::ComRecv(unsigned char* pRecv,int& nSize)
{
	nSize = 0;
	if(!m_bOpened||pHandle == INVALID_HANDLE_VALUE)
	{
		return false;
	}

	DWORD dwOldMask = 0;

	BOOL   bReadStatus;   
	DWORD dwBytesRead = 0;

	DWORD dwBytesTransferred;
	GetOverlappedResult(pHandle, &m_OverlappedRead, &dwBytesTransferred, FALSE);
	m_OverlappedRead.Offset +=dwBytesRead;   

	dwBytesRead = COM_FRAME_ONCE;  
	bReadStatus = ReadFile(pHandle,pRecv,dwBytesRead,&dwBytesRead,&m_OverlappedRead);   
	if(bReadStatus && 0 != dwBytesRead )
	{   
		nSize = dwBytesRead;
		return true;
	}   
	else if( GetLastError() == ERROR_IO_PENDING )
	{
		if( WaitForSingleObject(m_OverlappedRead.hEvent,INFINITE) )
		{
			dwBytesRead = 0; 
			return false;	 
		}

		GetOverlappedResult(pHandle,&m_OverlappedWrite,&dwBytesRead,FALSE);   
		m_OverlappedRead.Offset +=dwBytesRead;   
		nSize = dwBytesRead;
		return true;
	}

	return false;

}

bool COMConn::OpenConn()
{
	_bstr_t bstrPort = _bstr_t("\\\\.\\") + mStrComNum.c_str();
	//this->mBaud = m_RFIDSystemCfg.nBaud;
	DCB   dcb;    
	pHandle= CreateFile(
		bstrPort,
		GENERIC_READ|GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL|FILE_FLAG_OVERLAPPED,
		NULL);

	if( pHandle ==   INVALID_HANDLE_VALUE   )
	{
		DWORD nErrorCode = GetLastError();
		SetErrorCode(ERR_COMOPEN_FAIL);
		return false;
	}

	memset(&m_OverlappedRead, 0, sizeof(OVERLAPPED));   
	memset(&m_OverlappedWrite, 0,sizeof(OVERLAPPED));   

	COMMTIMEOUTS   CommTimeOuts;   
	CommTimeOuts.ReadIntervalTimeout   =   0xFFFFFFFF;   
	CommTimeOuts.ReadTotalTimeoutMultiplier   =   0;   
	CommTimeOuts.ReadTotalTimeoutConstant   =   0;   
	CommTimeOuts.WriteTotalTimeoutMultiplier   =   0;   
	CommTimeOuts.WriteTotalTimeoutConstant   =   0; //以前是5000  
	SetCommTimeouts(pHandle,&CommTimeOuts);   

	m_OverlappedRead.hEvent = CreateEvent(NULL,TRUE,FALSE,NULL);   
	m_OverlappedWrite.hEvent = CreateEvent( NULL,TRUE,FALSE,NULL);   

	dcb.DCBlength   =   sizeof(   DCB   );   
	GetCommState(pHandle,&dcb);   
	dcb.BaudRate=mBaud;   
	dcb.ByteSize=8;   

	bool bRet = false;
	do 
	{
		if( !SetCommState(pHandle,&dcb ) )
		{
			SetErrorCode(ERR_SETCOM_STATE);
			break;
		}
		if( !SetupComm(pHandle,RECVFRAME_MAXBUF,RECVFRAME_MAXBUF))
		{
			SetErrorCode(ERR_SETUP_COM);
			break;
		}
		if( m_OverlappedWrite.hEvent == NULL)
		{
			SetErrorCode(ERR_OVERLAPREAD_NULL);
			break;
		}
		if( m_OverlappedWrite.hEvent == NULL)
		{
			SetErrorCode(ERR_OVERLLAPWRITE_NULL);
			break;
		}

		bRet = true;
	} while (0);

	if( !bRet )
	{
		SetErrorCode(ERR_COMOPEN_FAIL);
		DWORD   dwError   =   GetLastError();   
		if(m_OverlappedRead.hEvent != NULL)
		{
			CloseHandle(   m_OverlappedRead.hEvent   ); 
			m_OverlappedRead.hEvent = NULL;
		}
		if(m_OverlappedWrite.hEvent != NULL   )
		{
			CloseHandle(   m_OverlappedWrite.hEvent   ); 
			m_OverlappedWrite.hEvent  = NULL;
		}

		CloseHandle(pHandle);   
		return false;
	}

	m_bOpened = true;
	return true;
}

bool COMConn::WriteCommByte(unsigned char ucByte)
{
	BOOL   bWriteStat;   
	DWORD   dwBytesWritten;   

	bWriteStat = WriteFile(pHandle,(char*)&ucByte,1,&dwBytesWritten,&m_OverlappedWrite); 
	if( bWriteStat ) //立即返回 已写成功
	{
		return true;
	}
	else if( GetLastError()== ERROR_IO_PENDING )
	{   
		if(WaitForSingleObject(m_OverlappedWrite.hEvent,SEND_WAIT))
		{			
			dwBytesWritten = 0;  
			return false;
		} 

		GetOverlappedResult(pHandle,&m_OverlappedWrite,&dwBytesWritten,FALSE);   
		m_OverlappedWrite.Offset+=dwBytesWritten;   
		return true;

	} 

	return false;
}

bool COMConn::ComSend(unsigned char* ucByte,int nSize)
{
	bool bRet = true;
	for( int i = 0 ; i < nSize ; i++)
	{
		if( !WriteCommByte(*(ucByte+i)) )
		{
			bRet = false;
			break;
		}

	}
	return bRet;
}

bool COMConn::Svr()
{
	if( NULL == m_hThread )
	{
		m_bThExit = false;
		m_hThread = (HANDLE)_beginthreadex(NULL,
			0,
			(PBEGINTHREADEX_THREADFUNC)StartCOMRevThread,
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

bool COMConn::SendRawData(unsigned char* szData,int nLen)
{
	return ComSend(szData,nLen);
}

bool COMConn::CloseConn()
{
	CloseThread();//关闭线程
	return ClosePort();//关闭端口
}

bool COMConn::ClosePort()
{
	if( !m_bOpened || pHandle == INVALID_HANDLE_VALUE )
	{
		return true;
	}

	if(m_OverlappedRead.hEvent != NULL   )
	{
		CloseHandle(m_OverlappedRead.hEvent);  
		m_OverlappedRead.hEvent = NULL;
	}
	if(m_OverlappedWrite.hEvent != NULL)
	{
		CloseHandle(m_OverlappedWrite.hEvent);  
		m_OverlappedWrite.hEvent = NULL;
	}

	if( pHandle != INVALID_HANDLE_VALUE )
	{
		CloseHandle(pHandle);
		pHandle = INVALID_HANDLE_VALUE;
	}

	m_bOpened   =   FALSE;   

	return true;
}

bool COMConn::CloseThread()
{
	m_bThExit = true; //关闭线程
	if( m_hThread != NULL )
	{
		WaitForSingleObject(m_ThreadExitEvent,INFINITE);
	}
	return true;
}
