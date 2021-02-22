#include "StdAfx.h"
#include "COMConn.h"
#include <comdef.h>
#include <process.h>


CCOMConn::CCOMConn(void)
{
	m_ThreadExitEvent = CreateEvent(NULL,FALSE,FALSE,NULL);


	memset(&m_OverlappedRead, 0, sizeof(OVERLAPPED));   
	memset(&m_OverlappedWrite, 0,sizeof(OVERLAPPED));
	m_bThExit = false;
	m_hThread = NULL;
	m_nHeartTime = 6000;

	pHandle = INVALID_HANDLE_VALUE;

}

void CCOMConn::InitConnect(IDataProc * pDataProc) 
{
	m_pDataPrcoessInterface = pDataProc;
}



CCOMConn::~CCOMConn(void)
{
	CloseConn();//关闭链接

	if( NULL != m_OverlappedRead.hEvent   )
	{
		CloseHandle(m_OverlappedRead.hEvent);
		m_OverlappedRead.hEvent = NULL;
	}
	if( NULL != m_OverlappedWrite.hEvent )
	{
		CloseHandle(m_OverlappedWrite.hEvent);
		m_OverlappedWrite.hEvent = NULL;
	}

	if( NULL != m_ThreadExitEvent)
	{
		
		CloseHandle(m_ThreadExitEvent);
		m_ThreadExitEvent = NULL;
	}

	if( INVALID_HANDLE_VALUE != pHandle  )
	{
		CloseHandle(pHandle);
		pHandle = INVALID_HANDLE_VALUE;
	}
}

void CCOMConn::LoadData(CRFIDSystemCfg& initSystemCfg) 
{
	m_RFIDSystemCfg = initSystemCfg;
}

bool CCOMConn::OpenConn() 
{
	_bstr_t bstrPort = _bstr_t("\\\\.\\") + m_RFIDSystemCfg.strComNum.c_str();
	this->nBaud = m_RFIDSystemCfg.nBaud;
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
	dcb.BaudRate=nBaud;   
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

bool CCOMConn::RevMsg(unsigned char *pRevMsg,unsigned char *pDataLen,int nWaitTime)
{
	if( 0 == nWaitTime)
	{
		nWaitTime +=3000;
	}

	unsigned char pForRev[COM_FRAME_ONCE];
	int revQty = 0;
	DWORD dwStart = GetTickCount();
	bool bRet = false;
	int nRecvDataLen = 0;

	do 
	{	
		//大于结束时间,结束
		if( GetTickCount() - dwStart >= ((DWORD)nWaitTime) ) 
		{
			break;
		}

		memset(pForRev,0,COM_FRAME_ONCE);

		ComRecv(pForRev,revQty);
		//TRACE(_T("%d\n"),revQty);
		if( 0 == revQty )
		{
			Sleep(20);
			continue;
		}

		nRecvDataLen+=revQty;
		if( nRecvDataLen > *pDataLen ) //内存不够 
		{
			SetErrorCode(ERR_MOREDATA_NEED);
			return false;//直接返回
		}

		memcpy(pRevMsg,pForRev,revQty);
		bRet = true;
		break;

	} while(1);


	return bRet;
}


bool CCOMConn::SendMsg(unsigned char *pSendData, int dataLength)
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

bool CCOMConn::ComSend(unsigned char* pByte,int nSize)
{
	bool bRet = true;
	for( int i = 0 ; i < nSize ; i++)
	{
		if( !WriteCommByte(*(pByte+i)) )
		{
			bRet = false;
			break;
		}

	}
	return bRet;
}


bool CCOMConn::WriteCommByte(unsigned char ucByte)   
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


void CCOMConn::SetHeartTime(int nHeartTime) 
{
	m_nHeartTime = nHeartTime;
}

bool CCOMConn::ComRecv(unsigned char* pRecv,int& nSize)
{
	//	COMSTAT   ComStat;   
	/*COMSTAT   ComStat;   
	DWORD dwErrorFlags;
	ClearCommError(pHandle,&dwErrorFlags,&ComStat);   
	if(!ComStat.cbInQue)  
	{
	return false;
	}*/

	nSize = 0;
	if(!m_bOpened||pHandle == INVALID_HANDLE_VALUE)
	{
		return false;
	}

	

	DWORD dwOldMask = 0;
	/*if (!GetCommMask(pHandle, &dwOldMask))
	{
		return false;
	}*/
	//if( !SetCommMask(pHandle,EV_RXCHAR))
	//{
	//	return false;
	//}


	BOOL   bReadStatus;   
	DWORD dwBytesRead = 0;
	//DWORD dwErrorFlags = 0;

	//DWORD dwEvtMask;

	//if (WaitCommEvent(pHandle, &dwEvtMask, &m_OverlappedRead))  //成功
	//{
	//	if (dwEvtMask & EV_DSR) 
	//	{
	//		// To do.
	//	}
	//}
	//else
	//{
	//	if (WaitForSingleObject(m_OverlappedRead.hEvent, COM_ONCE_WAIT) != WAIT_OBJECT_0)
	//	{
	//		return false;
	//	}
	//}

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

DWORD WINAPI StartCOMRevThread(LPVOID p)
{
	CCOMConn *pThis = (CCOMConn*)p;
	int nErrorTimes = 0;
	while( !pThis->m_bThExit )
	{
			//收数据
			unsigned char pForRev[MAX_PATH];
			int revQty = 0 ;
			if( !pThis->ComRecv(pForRev,revQty) ) //200秒超时
			{
				
				//OutputDebugString(L"没收到数据\r\n");
				//nErrorTimes++;
				//if( nErrorTimes == (pThis->m_nHeartTime/COM_ONCE_WAIT) )//6秒没有数据
				//{
				//	if( pThis->m_pDataPrcoessInterface->TestHeart() )  //正常在线
				//	{
				//		nErrorTimes = 0;//置ErrorTimes
				//	}
				//}
				//else
				//{
				//	continue;
				//}
				Sleep(20);
			}
		//	else//如果有数据
		//	{
				//nErrorTimes = 0 ; //有数据,则清错误次数
				if( pThis->m_pDataPrcoessInterface != NULL )
				{
					pThis->m_pDataPrcoessInterface->MsgProcess(pForRev,revQty);
				}	
		//	}
			
	}

	CloseHandle(pThis->m_hThread);
	pThis->m_hThread = NULL;
	SetEvent(pThis->m_ThreadExitEvent);
	return 0;
}

bool CCOMConn::Svr()
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




bool CCOMConn::CheckConnState( )
{
	return true;
}

//bool CCOMConn::SendNRevMsg(unsigned char *pSendCommand, unsigned char *pSendData, int dataLength, CRFIDFrame &pRevFrame,int nWaitTime )
//{
//	ClearErrorCode();
//
//	if( NULL == pSendCommand ||
//		NULL == pSendData )
//	{
//		SetErrorCode(ERR_POINTER_NULL);
//		return false;
//	}
//
//	if(!SendMsg( pSendData, dataLength))
//	{
//		return false;
//	}
//
//	return RevMsg(pRevFrame,nWaitTime);
//
//}

bool CCOMConn::ClosePort()
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


bool CCOMConn::CloseThread()
{
	m_bThExit = true; //关闭线程
	if( m_hThread != NULL )
	{
		WaitForSingleObject(m_ThreadExitEvent,INFINITE);
	}
	return true;
}


bool CCOMConn::CloseConn()
{
	CloseThread();//关闭线程
	return ClosePort();//关闭端口
	
}





bool CCOMConn::SendRawData(unsigned char* szData,int nLen) 
{
	return ComSend(szData,nLen);
}



