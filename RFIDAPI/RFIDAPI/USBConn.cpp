#include "StdAfx.h"
#include "USBConn.h"
#include <comdef.h>
#include <process.h>

CUSBConn::CUSBConn(void)
{
	m_ThreadExitEvent = CreateEvent(NULL,FALSE,FALSE,NULL);
	m_bThExit = false;
	m_hThread = NULL;
	m_nHeartTime = 6000;
	pHandle = INVALID_HANDLE_VALUE;
}

void CUSBConn::InitConnect(IDataProc * pDataProc) 
{
	m_pDataPrcoessInterface = pDataProc;
}



CUSBConn::~CUSBConn(void)
{
	CloseConn();//关闭链接

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

void CUSBConn::LoadData(CRFIDSystemCfg& initSystemCfg) 
{
	m_RFIDSystemCfg = initSystemCfg;
}

bool CUSBConn::OpenConn() 
{
	this->nBaud = m_RFIDSystemCfg.nBaud;
	_bstr_t bstrPort = _bstr_t("\\\\.\\") + m_RFIDSystemCfg.strComNum.c_str();

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

		mDCB.BaudRate=this->nBaud;
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

bool  CUSBConn::RevMsg(unsigned char *pRevMsg,unsigned char *pDataLen,int nWaitTime)
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

bool CUSBConn::ComSend(unsigned char* pByte,int nSize)
{
	DWORD dWritten =0 ;
	int nRet = WriteFile(pHandle,pByte,nSize,&dWritten,NULL);
	if ( 0 != nRet && 0 != dWritten )
	{
		return true;
	}

	return false;
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


void CUSBConn::SetHeartTime(int nHeartTime) 
{
	m_nHeartTime = nHeartTime;
}

bool CUSBConn::ComRecv(unsigned char* pRecv,int& nSize)
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

DWORD WINAPI StartUSBRevThread(LPVOID p)
{
	CUSBConn *pThis = (CUSBConn*)p;
	int nErrorTimes = 0;
	while( !pThis->m_bThExit )
	{
		
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




bool CUSBConn::CheckConnState( )
{
	return true;
}

//bool CUSBConn::SendNRevMsg(unsigned char *pSendCommand, unsigned char *pSendData, int dataLength, CRFIDFrame &pRevFrame,int nWaitTime )
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


bool CUSBConn::CloseConn()
{
	CloseThread();//关闭线程
	return ClosePort();//关闭端口

}





bool CUSBConn::SendRawData(unsigned char* szData,int nLen) 
{
	return ComSend(szData,nLen);
}



