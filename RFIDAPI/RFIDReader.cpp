#include "StdAfx.h"
#include "RFIDReader.h"
#include "COMConn.h"
#include "TCPConn.h"
#include "USBConn.h"

CRFIDReader::CRFIDReader(void)
{
	m_ReadState = READ_IDLE;

	memset(m_szProductSN,0,READER_PROUCTNAME_LEN);


	m_CardIDBuffer.Init(CARD_MAX_BUFFER);
	m_DataProcss.InitDataPorc(this);
	m_bOpen = false;
	InitializeCriticalSection(&m_Critical);
}




bool CRFIDReader::InitCFG(CRFIDSystemCfg& cfg)
{
	m_sysCfg = cfg;
	return true;
}

CRFIDReader::~CRFIDReader(void)
{
	Close();
	DeleteCriticalSection(&m_Critical);
}


void CRFIDReader::SetErrorCode(int dwErrorCode,bool bCommandError )
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


void CRFIDReader::ClearErrorCode()
{
	DWORD dwErrorID = GetCurrentThreadId();
	typedef pair <DWORD, int> DW_Pair; 

	map<DWORD,int>::iterator itor = map_Error.find(dwErrorID);
	if( itor != map_Error.end() )
	{
		itor->second  = 0 ;
	}

}



void CRFIDReader::SetProuctSN(char* szName)
{
	memcpy(m_szProductSN,szName,strlen(szName));
}

char* CRFIDReader::GetProuctSN()
{
	return m_szProductSN;
}


bool CRFIDReader::Close(void)
{
	ClearErrorCode();

	if( !Stop() )
	{
	//	return false;
	}

/*
	ClearErrorCode();

	if( !m_bOpen )
	{
		return false;
	}

	bool bRet = false;
	unsigned char SendCommand = RFIDCommand[COM_CLOSE_CONN];//指令
	unsigned char pSendData[API_SENDDATA_BUFF];
	memset(pSendData,0,6);
	//*pSendData = nType;//数据内容
	//memset(++pSendData,0,6);
	//*(pSendData+1) = nPort;
	int nDataLen = 6;//数据内容长度

	CRFIDFrame InRFIDFrame;
	CRFrame& RFIDFrame = InRFIDFrame.RFIDOutFrame;
	do 
	{
		if( !SendNRevMsg(&SendCommand,pSendData,nDataLen,InRFIDFrame,3000) )
		{	
			break;
		}
		if( RFIDFrame.bData[0] != 0 ) //判断返回值 
		{
			SetErrorCode(RFIDFrame.bData[0],true);
			break;
		}
		bRet = true;
	} while (0);
	
		*/
	if(!m_DataProcss.Close())
	{
		return false;
	}
	m_bOpen = false;
	return true;


}


bool CRFIDReader::Stop(void)
{
	return PowerOff();
}



bool CRFIDReader::SetMsgResult(CRFrame& RFIDFrame)
{
	unsigned char nCommand = RFIDFrame.bCommand;

	if( nCommand == RFIDCommand[COM_YMAKE_TAGUPLOAD] ||
		nCommand == RFIDCommand[COM_SEND_HEART] )
	{
		if( !m_CardIDBuffer.Add(&RFIDFrame) )
		{
			m_CardIDBuffer.Clear();
		}
		return true;
	}

	
	return m_cmdBuffer.SetCmdResult(RFIDFrame);
}


bool CRFIDReader::GetCard(CRFrame& RFIDFrame,int nWaitTime)
{
	if( WAIT_OBJECT_0 != WaitForSingleObject(m_CardIDBuffer.GetSingle(),nWaitTime ) )
	{
		return false;
	}

	return m_CardIDBuffer.RemoveHead(RFIDFrame);

}


bool CRFIDReader::GetMsgResult(CRFIDFrame &pRevFrame,int nWaitTime )
{
	if( WAIT_OBJECT_0 != WaitForSingleObject(pRevFrame.m_revHandle,nWaitTime ) )
	{
		m_cmdBuffer.DelCmd(&pRevFrame);//把指针移除
		return false;
	}

	return m_cmdBuffer.DelCmd(&pRevFrame);

}

bool CRFIDReader::SAATSysInfSet (unsigned char nType,unsigned char* pParm,int nLen)
{
	ClearErrorCode();

	if( !m_bOpen )
	{
		return false;
	}


	if( 0 == nLen )
	{
		SetErrorCode(ERR_SIZE_ZERO);
		return false;
	}

	bool bRet = false;
	unsigned char SendCommand = RFIDCommand[COM_SYS_CFG];//指令
	unsigned char pSendData[API_SENDDATA_BUFF];			//数据内容
	*(pSendData) = nType;
	memcpy(pSendData+1,pParm,nLen);
	int nDataLen =  nLen +1;								//数据内容长度

	CRFIDFrame RFIDInOutFrame;
	CRFrame& RFIDFrame = RFIDInOutFrame.RFIDOutFrame;
	do 
	{
		if( !SendNRevMsg(&SendCommand,pSendData,nDataLen,RFIDInOutFrame) )
		{	
			break;
		}

		if( RFIDFrame.bData[0] != 0 )			 //判断返回值 
		{
			SetErrorCode(RFIDFrame.bData[0],true);
			break;
		}
		bRet = true;

	} while (0);

	return bRet;
}


bool CRFIDReader::SAATWorkModeSet (unsigned char nType)
{
	ClearErrorCode();

	if( !m_bOpen )
	{
		return false;
	}


	bool bRet = false;
	unsigned char SendCommand = RFIDCommand[COM_WORKMOD_CFG];//指令
	unsigned char pSendData[API_SENDDATA_BUFF];
	*pSendData = nType;//数据内容

	int nDataLen =  1;//数据内容长度

	CRFIDFrame RFIDInOutFrame;
	CRFrame& RFIDFrame = RFIDInOutFrame.RFIDOutFrame;

	do 
	{
		if( !SendNRevMsg(&SendCommand,pSendData,nDataLen,RFIDInOutFrame) )
		{	
			break;
		}

		if( RFIDFrame.bData[0] != 0 ) //判断返回值 
		{
			SetErrorCode(RFIDFrame.bData[0],true);
			break;
		}
		bRet = true;

	} while (0);

	return bRet;
}

bool CRFIDReader::SAATParmOp(unsigned char nType, unsigned char nStartAddrr, unsigned char nLen,  unsigned char *pData, unsigned char *pDataLen)
{
	ClearErrorCode();

	if( !m_bOpen )
	{
		return false;
	}

	if( NULL == pData )
	{
		SetErrorCode(ERR_POINTER_NULL);
		return false;
	}

	if( 0 == *pDataLen )
	{
		SetErrorCode(ERR_SIZE_ZERO);
		return false;
	}


	bool bRet = false;

	unsigned char SendCommand = RFIDCommand[COM_PARA_OP];//指令
	unsigned char pSendData[API_SENDDATA_BUFF];

	*pSendData = nType;		//数据内容
	*(pSendData+1) = nStartAddrr;//开始地址
	*(pSendData+2) = nLen;	//导入/导出长度

	int nTempLen = 0;
	switch (nType)
	{
	case 0x00:		//恢复系统参数表为出厂设置
		break;
	case 0x01:		//导入系统参数表
		memcpy(pSendData+3,pData,nLen);
		nTempLen = nLen;
		break;
	case 0x02:		//导出系统参数表
		break;
	}

	int nDataLen = 3 + nTempLen;//数据内容长度

	CRFIDFrame RFIDInOutFrame;
	CRFrame& RFIDFrame = RFIDInOutFrame.RFIDOutFrame;
	do 
	{
		if( !SendNRevMsg(&SendCommand,pSendData,nDataLen,RFIDInOutFrame,8000) )
		{	
			break;
		}
		
		/*if( !SendMsg(&SendCommand,pSendData,nDataLen) )
		{	
			break;
		}
		bRet = false;
		int j = 40;
		while(j--)
		{
			if (RevMsg(RFIDFrame,10))
			{
				OutputDebugString(L"recv power off recv succ \n");
				if(RFIDFrame.bCommand == RFIDCommand[COM_PARA_OP])
				{
					bRet = true;
					break;
				}
			}
			Sleep(80);
		}
		if( !bRet )
		{
			return false;
		}
*/

		if( RFIDFrame.bData[0] != 0 ) //判断返回值 
		{
			SetErrorCode(RFIDFrame.bData[0],true);
			break;
		}

		switch (nType)
		{
		case 0x00://恢复系统参数表为出厂设置
			bRet = true;
			break;
		case 0x01://导入系统参数表
			bRet = true;
			break;
		case 0x02://导出系统参数表
			{
				if( nLen > *pDataLen )
				{
					SetErrorCode(ERR_MOREDATA_NEED);
					bRet = false;
					break;
				}
				memcpy(pData,RFIDFrame.bData+1,nLen);
				bRet = true;
			}
			break;
		}	
	} while (0);

	return bRet;
}


bool CRFIDReader::SAATRFParaSet (unsigned char nType, unsigned char nParaLen,unsigned char* pPara)
{
	
	ClearErrorCode();

	if( !m_bOpen )
	{
		return false;
	}

	if( NULL == pPara )
	{
		SetErrorCode(ERR_POINTER_NULL);
		return false;
	}

	if( 0 == nParaLen )
	{
		SetErrorCode(ERR_SIZE_ZERO);
		return false;
	}

	bool bRet = false;

	unsigned char SendCommand = RFIDCommand[COM_CARRYWAVE_SET];//指令
	unsigned char pSendData[API_SENDDATA_BUFF];
	*pSendData = nType;//数据内容
	*(pSendData+1) = nParaLen;

	memcpy(pSendData+2,pPara,nParaLen);//这个长度也是数据长度
	int nDataLen = 2 + nParaLen;//数据内容长度

	CRFIDFrame RFIDInOutFrame;
	CRFrame& RFIDFrame = RFIDInOutFrame.RFIDOutFrame;
	do 
	{
		if( !SendNRevMsg(&SendCommand,pSendData,nDataLen,RFIDInOutFrame) )
		{	
			break;
		}

		if( RFIDFrame.bData[0] != 0 ) //判断返回值 
		{
			SetErrorCode(RFIDFrame.bData[0],true);
			break;
		}
		bRet = true;

	} while (0);


	return bRet;
}

bool CRFIDReader::SAATRFParaQuery (unsigned char nType,unsigned char* pPara, unsigned char *pLen)
{

	ClearErrorCode();

	if( !m_bOpen )
	{
		return false;
	}

	if( NULL == pPara || NULL == pLen)
	{
		SetErrorCode(ERR_POINTER_NULL);
		return false;
	}

	if( 0 == *pLen )
	{
		SetErrorCode(ERR_SIZE_ZERO);
		return false;
	}

	bool bRet = false;

	unsigned char SendCommand = RFIDCommand[COM_CARRYWAVE_QUERY];//指令
	unsigned char pSendData[API_SENDDATA_BUFF];
	*pSendData = nType;//数据内容
	int nDataLen = 1;//数据内容长度

	CRFIDFrame RFIDInOutFrame;
	CRFrame &RFIDFrame = RFIDInOutFrame.RFIDOutFrame;
	do 
	{
		if( !SendNRevMsg(&SendCommand,pSendData,nDataLen,RFIDInOutFrame) )
		{	
			break;
		}

		if( RFIDFrame.bData[0] != 0 ) //判断返回值 
		{
			SetErrorCode(RFIDFrame.bData[0],true);
			break;
		}
		int nRealDataLen = RFIDFrame.bLength - COMMAND_LEN - ANSWER_LEN;
		if( nRealDataLen < 0 )
		{
			SetErrorCode(ERR_DATALEN_LOZERO);
			break;
		}
		if( nRealDataLen > *pLen )
		{
			SetErrorCode(ERR_MOREDATA_NEED);
			break;
		}

		memcpy(pPara,RFIDFrame.bData+1,nRealDataLen);
		*pLen = nRealDataLen;

		bRet = true;

	} while (0);

	return bRet;
}


bool CRFIDReader::SAATCommunicatParaSet (unsigned char nType, unsigned char* pPara, unsigned char nLen)
{

	ClearErrorCode();

	if( !m_bOpen )
	{
		return false;
	}

	if( NULL == pPara )
	{
		SetErrorCode(ERR_POINTER_NULL);
		return false;
	}

	if( 0 == nLen )
	{
		SetErrorCode(ERR_SIZE_ZERO);
		return false;
	}

	bool bRet = false;

	unsigned char SendCommand = RFIDCommand[COM_COMMUNI_SET];//指令
	unsigned char pSendData[API_SENDDATA_BUFF];
	*pSendData = nType;//数据内容

	memcpy(pSendData+1,pPara,nLen);
	int nDataLen = 1 + nLen;//数据内容长度

	CRFIDFrame RFIDInOutFrame;
	CRFrame& RFIDFrame = RFIDInOutFrame.RFIDOutFrame;
	do 
	{
		if( !SendNRevMsg(&SendCommand,pSendData,nDataLen,RFIDInOutFrame) )
		{	
			break;
		}

		if( RFIDFrame.bData[0] != 0 ) //判断返回值 
		{
			SetErrorCode(RFIDFrame.bData[0],true);
			break;
		}
		bRet = true;

	} while (0);


	return bRet;
}

bool CRFIDReader::SAATCommunicatParaQuery (unsigned char nType, unsigned char* pPara,unsigned char *pLen)
{

	ClearErrorCode();

	if( !m_bOpen )
	{
		return false;
	}

	if( NULL == pPara || NULL == pLen)
	{
		SetErrorCode(ERR_POINTER_NULL);
		return false;
	}

	if( 0 == *pLen )
	{
		SetErrorCode(ERR_SIZE_ZERO);
		return false;
	}

	bool bRet = false;

	unsigned char SendCommand = RFIDCommand[COM_COMMUNI_QUERY];//指令
	unsigned char pSendData[API_SENDDATA_BUFF];
	*pSendData = nType;//数据内容
	int nDataLen = 1;//数据内容长度

	CRFIDFrame RFIDInOutFrame;
	CRFrame &RFIDFrame = RFIDInOutFrame.RFIDOutFrame;
	do 
	{
		if( !SendNRevMsg(&SendCommand,pSendData,nDataLen,RFIDInOutFrame) )
		{	
			break;
		}

		if( RFIDFrame.bData[0] != 0 ) //判断返回值 
		{
			SetErrorCode(RFIDFrame.bData[0],true);
			break;
		}
		int nRevDataLen = RFIDFrame.bLength;//调试时为17长度,即数据长度+指令长度
		int nRealDataLen = RFIDFrame.bLength - COMMAND_LEN - ANSWER_LEN;
		if( nRealDataLen < 0 )
		{
			SetErrorCode(ERR_DATALEN_LOZERO);
			break;
		}
		if( nRealDataLen > *pLen )
		{
			SetErrorCode(ERR_MOREDATA_NEED);
			break;
		}

		memcpy(pPara,RFIDFrame.bData+1,nRealDataLen);
		*pLen = nRealDataLen;
		bRet = true;

	} while (0);

	return bRet;
}


bool CRFIDReader::SAATNetParaSet (unsigned char nType, unsigned char* pPara, unsigned char nLen)
{
	ClearErrorCode();

	if( !m_bOpen )
	{
		return false;
	}

	if( NULL == pPara )
	{
		SetErrorCode(ERR_POINTER_NULL);
		return false;
	}

	if( 0 == nLen )
	{
		SetErrorCode(ERR_SIZE_ZERO);
		return false;
	}

	bool bRet = false;
	/*
	*/
	unsigned char SendCommand = RFIDCommand[COM_NETPARA_SET];//指令
	unsigned char pSendData[API_SENDDATA_BUFF];
	*pSendData = nType;//数据内容

	memcpy(pSendData+1,pPara,nLen);
	int nDataLen = 1 + nLen;//数据内容长度

	CRFIDFrame RFIDInOutFrame;
	CRFrame &RFIDFrame = RFIDInOutFrame.RFIDOutFrame;
	do 
	{
		if( !SendNRevMsg(&SendCommand,pSendData,nDataLen,RFIDInOutFrame) )
		{	
			break;
		}

		if( RFIDFrame.bData[0] != 0 ) //判断返回值 
		{
			SetErrorCode(RFIDFrame.bData[0],true);
			break;
		}
		bRet = true;

	} while (0);
	return bRet;
}



bool CRFIDReader::SAATNetParaQuery (int nType, unsigned char* pPara,unsigned char *pLen)
{
	
	ClearErrorCode();

	if( !m_bOpen )
	{
		return false;
	}

	if( NULL == pPara || NULL == pLen)
	{
		SetErrorCode(ERR_POINTER_NULL);
		return false;
	}

	if( 0 == *pLen )
	{
		SetErrorCode(ERR_SIZE_ZERO);
		return false;
	}

	bool bRet = false;

	unsigned char SendCommand = RFIDCommand[COM_NETPARA_QUERY];//指令
	unsigned char pSendData[API_SENDDATA_BUFF];
	*pSendData = nType;//数据内容
	int nDataLen = 1;//数据内容长度

	CRFIDFrame RFIDInOutFrame;
	CRFrame& RFIDFrame = RFIDInOutFrame.RFIDOutFrame;
	do 
	{
		if( !SendNRevMsg(&SendCommand,pSendData,nDataLen,RFIDInOutFrame) )
		{	
			break;
		}

		if( RFIDFrame.bData[0] != 0 ) //判断返回值 
		{
			SetErrorCode(RFIDFrame.bData[0],true);
			break;
		}
		int nRealDataLen = RFIDFrame.bLength - COMMAND_LEN - ANSWER_LEN;
		if( nRealDataLen < 0 )
		{
			SetErrorCode(ERR_DATALEN_LOZERO);
			break;
		}
		if( nRealDataLen > *pLen )
		{
			SetErrorCode(ERR_MOREDATA_NEED);
			break;
		}

		memcpy(pPara,RFIDFrame.bData+1,nRealDataLen);
		*pLen = nRealDataLen;
		bRet = true;

	} while (0);

	return bRet;
}

bool CRFIDReader::SAATTagOpParaSet(unsigned char nType, unsigned char *pPara,unsigned char nLen)
{
	

	ClearErrorCode();

	if( !m_bOpen )
	{
		return false;
	}

	bool bRet = false;

	if( NULL == pPara   )
	{
		SetErrorCode(ERR_POINTER_NULL);
		return false;
	}
	/*
	*/
	unsigned char SendCommand = RFIDCommand[COM_TAG_SET];//指令
	unsigned char pSendData[API_SENDDATA_BUFF];
	*pSendData = nType;//数据内容
	//	*(pSendData+1) = pPara;
	memcpy(pSendData+1,pPara,nLen);
	int nDataLen = nLen + 1;//数据内容长度

	CRFIDFrame RFIDInOutFrame;
	CRFrame& RFIDFrame = RFIDInOutFrame.RFIDOutFrame;
	do 
	{
		if( !SendNRevMsg(&SendCommand,pSendData,nDataLen,RFIDInOutFrame) )
		{	
			break;
		}

		if( RFIDFrame.bData[0] != 0 ) //判断返回值 
		{
			SetErrorCode(RFIDFrame.bData[0],true);
			break;
		}
		bRet = true;

	} while (0);


	return bRet;
}


bool CRFIDReader::SAATTagOpParaQuery (unsigned char nType, unsigned char* pPara, unsigned char *pLen)
{
	
	ClearErrorCode();

	if( !m_bOpen )
	{
		return false;
	}

	if( NULL == pPara || NULL == pLen)
	{
		SetErrorCode(ERR_POINTER_NULL);
		return false;
	}

	if( 0 == *pLen )
	{
		SetErrorCode(ERR_SIZE_ZERO);
		return false;
	}

	bool bRet = false;

	unsigned char SendCommand = RFIDCommand[COM_TAG_QUERY];//指令
	unsigned char pSendData[API_SENDDATA_BUFF];
	*pSendData = nType;//数据内容
	int nDataLen = 1;//数据内容长度
	
	CRFIDFrame RFIDInOutFrame;
	CRFrame &RFIDFrame = RFIDInOutFrame.RFIDOutFrame;
	do 
	{
		if( !SendNRevMsg(&SendCommand,pSendData,nDataLen,RFIDInOutFrame) )
		{	
			break;
		}

		if( RFIDFrame.bData[0] != 0 ) //判断返回值 
		{
			SetErrorCode(RFIDFrame.bData[0],true);
			break;
		}
		int nRealDataLen = RFIDFrame.bLength - COMMAND_LEN - ANSWER_LEN;
		if( nRealDataLen < 0 )
		{
			SetErrorCode(ERR_DATALEN_LOZERO);
			break;
		}
		if( nRealDataLen > *pLen )
		{
			SetErrorCode(ERR_MOREDATA_NEED);
			break;
		}

		memcpy(pPara,RFIDFrame.bData+1,nRealDataLen);
		*pLen = nRealDataLen;
		bRet = true;

	} while (0);

	return bRet;
}



bool CRFIDReader::SAATExtendBroadParaSet (unsigned char nType, unsigned char pSendChunnel)
{
	
	ClearErrorCode();

	if( !m_bOpen )
	{
		return false;
	}

	bool bRet = false;
	/*
	*/
	unsigned char SendCommand = RFIDCommand[COM_EXTENDBOARD_SET];//指令
	unsigned char pSendData[API_SENDDATA_BUFF];
	*pSendData = nType;//数据内容
	*(pSendData+1) = pSendChunnel;
	*(pSendData+2) = 0x00;//保留
	int nDataLen = 3;//数据内容长度

	CRFIDFrame RFIDInOutFrame;
	CRFrame& RFIDFrame = RFIDInOutFrame.RFIDOutFrame;
	do 
	{
		if( !SendNRevMsg(&SendCommand,pSendData,nDataLen,RFIDInOutFrame) )
		{	
			break;
		}

		if( RFIDFrame.bData[0] != 0 ) //判断返回值 
		{
			SetErrorCode(RFIDFrame.bData[0],true);
			break;
		}
		bRet = true;

	} while (0);


	return bRet;
}


bool CRFIDReader::SAATExtendBroadParaQuery (unsigned char nType, char* pPara, unsigned char* pLen)
{

	ClearErrorCode();

	if( !m_bOpen )
	{
		return false;
	}

	if( NULL == pPara || NULL == pLen)
	{
		SetErrorCode(ERR_POINTER_NULL);
		return false;
	}

	if( 0 == *pLen )
	{
		SetErrorCode(ERR_SIZE_ZERO);
		return false;
	}

	bool bRet = false;

	unsigned char SendCommand = RFIDCommand[COM_NETPARA_QUERY];//指令
	unsigned char pSendData[API_SENDDATA_BUFF];
	*pSendData = nType;//数据内容
	int nDataLen = 1;//数据内容长度

	CRFIDFrame RFIDInOutFrame;
	CRFrame& RFIDFrame = RFIDInOutFrame.RFIDOutFrame;
	do 
	{
		if( !SendNRevMsg(&SendCommand,pSendData,nDataLen,RFIDInOutFrame) )
		{	
			break;
		}

		if( RFIDFrame.bData[0] != 0 ) //判断返回值 
		{
			SetErrorCode(RFIDFrame.bData[0],true);
			break;
		}
		int nCommandRealDataLen = RFIDFrame.bLength -1;	

		if( nCommandRealDataLen > *pLen ) //长度有一位用于判断返回值
		{
			SetErrorCode(ERR_MOREDATA_NEED);
			break;
		}
		memcpy(pPara,(void*)(RFIDFrame.bData+1),nCommandRealDataLen);
		*pLen = nCommandRealDataLen;
		bRet = true;


	} while (0);

	return bRet;
}


bool CRFIDReader::SAATTotalAntennaParmQuery (unsigned char *szAntennaPara,unsigned char *pLen)
{
	ClearErrorCode();

	if( !m_bOpen )
	{
		return false;
	}

	if( NULL == szAntennaPara || NULL == pLen)
	{
		SetErrorCode(ERR_POINTER_NULL);
		return false;
	}

	if( 0 == *pLen )
	{
		SetErrorCode(ERR_SIZE_ZERO);
		return false;
	}

	bool bRet = false;

	unsigned char SendCommand = RFIDCommand[COM_ANTENNA_QUERY];//指令
	unsigned char pSendData[API_SENDDATA_BUFF];
	int nDataLen = 0;//数据内容长度

	CRFIDFrame RFIDInOutFrame;
	CRFrame &RFIDFrame = RFIDInOutFrame.RFIDOutFrame;
	do 
	{
		if( !SendNRevMsg(&SendCommand,pSendData,nDataLen,RFIDInOutFrame) )
		{	
			break;
		}

		if( RFIDFrame.bData[0] != 0 ) //判断返回值 
		{
			SetErrorCode(RFIDFrame.bData[0],true);
			break;
		}


		int nRealDataLen = RFIDFrame.bLength - COMMAND_LEN - ANSWER_LEN;
		if( nRealDataLen < 0 )
		{
			SetErrorCode(ERR_DATALEN_LOZERO);
			break;
		}
		if( nRealDataLen > *pLen )
		{
			SetErrorCode(ERR_MOREDATA_NEED);
			break;
		}

		memcpy(szAntennaPara,RFIDFrame.bData+1,nRealDataLen);
		*pLen = nRealDataLen;
		bRet = true;
	} while (0);

	return bRet;
}


bool CRFIDReader::SAATAntennaParmQuery (unsigned char nAntenna,unsigned char * pAntennaEnable,unsigned char *pAntennaPower,unsigned char *pAntennaQueryTime )
{
	ClearErrorCode();

	if( !m_bOpen )
	{
		return false;
	}

	unsigned char AntennaPara[BYTE_BUFFER_SIZE];
	unsigned char nSize = BYTE_BUFFER_SIZE;


	if( NULL == pAntennaEnable || 
		NULL == pAntennaPower || 
		NULL == pAntennaQueryTime )
	{
		SetErrorCode(ERR_POINTER_NULL);
		return false;
	}


	if( !SAATTotalAntennaParmQuery(AntennaPara,&nSize) )
	{
		return false;
	}

	unsigned char bytePortEnable[4];
	unsigned char bytePower[4];
	unsigned char byteTimer[4];

	memcpy(bytePortEnable,AntennaPara,4);
	memcpy(bytePower,AntennaPara+4,4);
	memcpy(byteTimer,AntennaPara+8,4);


	//	nAntenna,int * pAntennaEnable,int *pAntennaPower,int  *pAntennaQueryTime

	*pAntennaEnable = bytePortEnable[nAntenna-1];
	*pAntennaPower = bytePower[nAntenna-1];
	*pAntennaQueryTime = byteTimer[nAntenna-1];

	//	*pAntennaPower = (*pAntennaPower) >> 1;//右移一位
	return true;
}


bool CRFIDReader::SAATAntennaParmSet(unsigned char *pPara,unsigned char nLen )
{
	ClearErrorCode();

	if( !m_bOpen )
	{
		return false;
	}

	if( NULL == pPara )
	{
		SetErrorCode(ERR_POINTER_NULL);
		return false;
	}

	if( 0 == nLen )
	{
		SetErrorCode(ERR_SIZE_ZERO);
		return false;
	}


	bool bRet = false;
	/*
	*/
	unsigned char SendCommand = RFIDCommand[COM_ANTENNA_SET];//指令
	unsigned char pSendData[API_SENDDATA_BUFF];
	memcpy(pSendData,pPara,nLen);
	int nDataLen = nLen;//数据内容长度

	CRFIDFrame RFIDInOutFrame;
	CRFrame &RFIDFrame = RFIDInOutFrame.RFIDOutFrame;
	do 
	{
		if( !SendNRevMsg(&SendCommand,pSendData,nDataLen,RFIDInOutFrame) )
		{	
			break;
		}

		if( RFIDFrame.bData[0] != 0 ) //判断返回值 
		{
			SetErrorCode(RFIDFrame.bData[0],true);
			break;
		}

		bRet = true;

	} while (0);

	return bRet;
}

bool CRFIDReader::SAATSetAntennaPortEnable (unsigned char nAntenna,unsigned char nEnable )
{
	ClearErrorCode();

	if( !m_bOpen )
	{
		return false;
	}

	unsigned char AntennaPara[BYTE_BUFFER_SIZE];
	unsigned char nSize = BYTE_BUFFER_SIZE;
	if( !SAATTotalAntennaParmQuery(AntennaPara,&nSize) )
	{
		return false;
	}
	*(AntennaPara+nAntenna-1) = nEnable;

	return SAATAntennaParmSet(AntennaPara,12);
}



bool CRFIDReader::SAATSetAntennaPower (unsigned char nAntenna,unsigned char nPower )
{
	ClearErrorCode();

	if( !m_bOpen )
	{
		return false;
	}

	unsigned char AntennaPara[BYTE_BUFFER_SIZE];
	unsigned char nSize = BYTE_BUFFER_SIZE;
	if( !SAATTotalAntennaParmQuery(AntennaPara,&nSize) )
	{
		return false;
	}

	*(AntennaPara+4+nAntenna-1) = nPower;

	return SAATAntennaParmSet(AntennaPara,12);
}

bool CRFIDReader::SAATSetAntennaTime (unsigned char nAntenna,unsigned char nTime )
{
	ClearErrorCode();

	if( !m_bOpen )
	{
		return false;
	}

	unsigned char AntennaPara[BYTE_BUFFER_SIZE];
	unsigned char nSize = BYTE_BUFFER_SIZE;
	if( !SAATTotalAntennaParmQuery(AntennaPara,&nSize) )
	{
		return false;
	}
	*(AntennaPara+8+nAntenna-1) = nTime;

	return SAATAntennaParmSet(AntennaPara,12);
}

bool CRFIDReader::SAATYAntennaParmQuery(unsigned char* pPowerRecvPlus, unsigned char* p2401FreqSendPwr, unsigned char* pAttenuatorPower)
{
	ClearErrorCode();

	if (!m_bOpen)
	{
		return false;
	}

	unsigned char AntennaPara[BYTE_BUFFER_SIZE];
	unsigned char nSize = BYTE_BUFFER_SIZE;


	if (NULL == pPowerRecvPlus ||
		NULL == p2401FreqSendPwr ||
		NULL == pAttenuatorPower)
	{
		SetErrorCode(ERR_POINTER_NULL);
		return false;
	}


	if (!SAATTotalAntennaParmQuery(AntennaPara, &nSize))
	{
		return false;
	}

	unsigned char bytePortEnable[4];
	unsigned char bytePower[4];
	unsigned char byteTimer[4];

	memcpy(bytePortEnable, AntennaPara, 4);
	memcpy(bytePower, AntennaPara + 4, 4);
	memcpy(byteTimer, AntennaPara + 8, 4);


	//	nAntenna,int * pAntennaEnable,int *pAntennaPower,int  *pAntennaQueryTime

	*pPowerRecvPlus = bytePower[0];
	*p2401FreqSendPwr = bytePower[1];
	*pAttenuatorPower = bytePower[2];

	//	*pAntennaPower = (*pAntennaPower) >> 1;//右移一位
	return true;
}


bool CRFIDReader::SAATIOOperate(unsigned char nPort,unsigned char nState)
{
	ClearErrorCode();

	if( !m_bOpen )
	{
		return false;
	}

	CRFIDFrame InOutRFIDFrame;

	
	unsigned char SendCommand = RFIDCommand[COM_IO_OP];//指令
	unsigned char pSendData[API_SENDDATA_BUFF];
	*pSendData = nPort;//数据内容
	*(pSendData+1) = nState;
	int nDataLen = 1 + 1;//数据内容长度

	CRFIDFrame RFIDInOutFrame;
	CRFrame &RFIDFrame = RFIDInOutFrame.RFIDOutFrame;
	bool bRet = false;
	do 
	{

		/*if( !pConnect->SendMsg(&SendCommand,pSendData,nDataLen) )
		{	
		break;
		}*/

		if( !SendNRevMsg(&SendCommand,pSendData,nDataLen,RFIDInOutFrame) )
		{	
			break;
		}

		if( RFIDFrame.bData[0] != 0 ) //判断返回值 
		{
			SetErrorCode(RFIDFrame.bData[0],true);
			break;
		}

		bRet = true;

	} while (0);


	return bRet;
}


bool CRFIDReader::SAATIOStateQuery(unsigned char *pState)
{
	ClearErrorCode();

	if( !m_bOpen )
	{
		return false;
	}

	if( NULL == pState)
	{
		SetErrorCode(ERR_POINTER_NULL);
	}
	bool bRet = false;
	
	unsigned char SendCommand = RFIDCommand[COM_INPUT_QUERY];//指令
	unsigned char pSendData[API_SENDDATA_BUFF];
	int nDataLen = 0;//数据内容长度

	CRFIDFrame RFIDInOutFrame;
	CRFrame &RFIDFrame = RFIDInOutFrame.RFIDOutFrame;
	
	do 
	{
		if( !SendNRevMsg(&SendCommand,pSendData,nDataLen,RFIDInOutFrame) )
		{	
			break;
		}

		if( RFIDFrame.bData[0] != 0 ) //判断返回值 
		{
			SetErrorCode(RFIDFrame.bData[0],true);
			break;
		}
		int nCommandRealDataLen = RFIDFrame.bLength -1;	
		memcpy(pState,(void*)(RFIDFrame.bData+1),nCommandRealDataLen);
		bRet = true;

	} while (0);


	return bRet;
}


bool CRFIDReader::SAAT6BTagSelect (  unsigned char nType, unsigned char nStartAddr,
				  unsigned char nDataBite, unsigned char * Data )
{
	ClearErrorCode();

	if( !m_bOpen )
	{
		return false;
	}

	if( NULL == Data )
	{
		SetErrorCode(ERR_POINTER_NULL);
		return false;
	}

	unsigned char pSendData[DATA_BUFFER];
	unsigned char ucCommand = RFIDCommand[COM_6BSELECT_TAG];


	pSendData[0] = nType;
	pSendData[1] = nStartAddr;
	pSendData[2] = nDataBite;
	memcpy(pSendData + 3, Data, 8);
	CRFIDFrame revInOutFrame;
	CRFrame& revFrame = revInOutFrame.RFIDOutFrame;


	if ( SendNRevMsg( &ucCommand, pSendData, 8+3, revInOutFrame))
	{
		if(revFrame.bData[0] != 0)
		{
			SetErrorCode(revFrame.bData[0], true);
			return false;
		}
		else
			return true;
	}
	return false;
}


bool CRFIDReader::SAAT6BReadUIDCode (unsigned char nAntenna,unsigned char nType)
{
	ClearErrorCode();

	if( !m_bOpen )
	{
		return false;
	}

	unsigned char pSendData[DATA_BUFFER];
	unsigned char ucCommand = RFIDCommand[COM_6BREAD_UID];


	pSendData[0] = nAntenna;
	pSendData[1] = nType;

	CRFIDFrame RFIDInOutFrame;
	if ( SendMsg( &ucCommand, pSendData, 2,RFIDInOutFrame))
		return true;
	else
		return false;
}


int CRFIDReader::SAAT6BRevUIDMsg (unsigned char* nAntenna, unsigned char* pUIDData,
				  unsigned char* nUIDLen)
{
	
	ClearErrorCode();

	if( !m_bOpen )
	{
		return false;
	}

	if( NULL == nAntenna ||
		NULL == pUIDData ||
		NULL == nUIDLen)
	{
		SetErrorCode(ERR_POINTER_NULL);
		return 0;
	}

	if( 0 == nUIDLen)
	{
		SetErrorCode(ERR_SIZE_ZERO);
		return 0;
	}

	CRFrame revFrame;
	if ( GetCard(revFrame,TAG_REV_TIME))
	{

		if( revFrame.bCommand == RFIDCommand[COM_STOP_READ] ) //这里的指令变成53了
		{
			return -1;
		}

		if( revFrame.bCommand == RFIDCommand[COM_SEND_HEART] ) //心跳包
		{
			return 2;
		}
		if(revFrame.bData[0] != 0)
		{
			SetErrorCode(revFrame.bData[0], true);
			return 0;
		}
		else
		{
			*nAntenna = revFrame.bData[1];
			int nRealDataLen =  revFrame.bLength - 3;
			if( nRealDataLen < 1 )
			{
				SetErrorCode(ERR_DATALEN_LOZERO);
				return 0;
			}
			if( nRealDataLen > *nUIDLen )
			{
				SetErrorCode(ERR_MOREDATA_NEED);
				return 0;
			}

			//	OutputDebugString(L"proble memcpy start");
			//这个有可能是负值 
			memcpy (pUIDData, (void*)&revFrame.bData[2], nRealDataLen);
			//	OutputDebugString(L"proble memcpy exit");
			*nUIDLen = revFrame.bLength - 3;
			return 1;
		}
	}
	return 0;
		
}



bool CRFIDReader::SAAT6BReadUserData ( unsigned char nAntenna,unsigned char nType,unsigned char * pTagID,
				unsigned char nStartAddr,unsigned char nReadLen, unsigned char *pdata,unsigned char dataLen)
{
	ClearErrorCode();

	if( !m_bOpen )
	{
		return false;
	}

	if( NULL == pTagID || NULL == pdata)
	{
		SetErrorCode(ERR_POINTER_NULL);
		return false;
	}

	if( 0 == dataLen)
	{
		SetErrorCode(ERR_SIZE_ZERO);
		return false;
	}

	if( nReadLen > dataLen )
	{
		SetErrorCode(ERR_MOREDATA_NEED);
		return false;
	}

	if( nStartAddr + nReadLen > SIXB_DATALEN)
	{
		SetErrorCode(ERR_SIXBREAD_OVERFLOW);
		return false;
	}
	
	unsigned char pSendData[DATA_BUFFER];
	unsigned char ucCommand = RFIDCommand[COM_6BREADUSER_DATA];
	unsigned char btRollLen = READ_USERDATA_LEN;

	int nLeavenLen = nReadLen; //剩下的长度
	int nOnceReadLen = 0;
	int nWriteAddr = 0;//写入地址
	CRFIDFrame revInOutFrame;
	CRFrame& revFrame = revInOutFrame.RFIDOutFrame;

	while(0 !=nLeavenLen)
	{
		nOnceReadLen = nLeavenLen;
		if( nLeavenLen > btRollLen ) //余下长度 >64个字节
		{
			nOnceReadLen = btRollLen; //读 64个
		}

		memset( (unsigned char *)&revFrame, 0 , sizeof(revFrame));
		memset(pSendData , 0 , DATA_BUFFER);
		pSendData[0] = nAntenna;
		pSendData[1] = nType;
		memcpy(pSendData + 2, pTagID, 8);
		pSendData[10] = nStartAddr;
		pSendData[11] = nOnceReadLen;

		if ( !SendNRevMsg( &ucCommand, pSendData, 12, revInOutFrame, TAG_6BREAD_TIME))
		{
			return false;
		}

		int nRealDataLen = revFrame.bLength - COMMAND_LEN - ANSWER_LEN ;
		if( nRealDataLen < 0 )
		{
			SetErrorCode(ERR_DATALEN_LOZERO);
			return false;
		}

		if(revFrame.bData[0] != 0)
		{
			SetErrorCode(revFrame.bData[0], true);
			return false;
		}
		memcpy(pdata + nWriteAddr,revFrame.bData+2, nRealDataLen-1 );	//不包含天线端口
		//nStartAddr += btRollLen;			
		nLeavenLen = nLeavenLen - nOnceReadLen;//已读一次
		nStartAddr += nOnceReadLen;
		nWriteAddr += nOnceReadLen;
	}
	return true;
}


bool CRFIDReader::SAAT6BWriteUserData (unsigned char nAntenna,
					  unsigned char nType, 
					  unsigned char *pTagID,
					  unsigned char nStartAddr,
					  unsigned char *pValue, 
					  unsigned char *pLen)
{

	ClearErrorCode();

	if( !m_bOpen )
	{
		return false;
	}

	if( NULL == pTagID ||
		NULL == pValue ||
		NULL == pLen )
	{
		SetErrorCode(ERR_POINTER_NULL);
		return false;
	}

	if( 0 == *pLen)
	{
		SetErrorCode(ERR_SIZE_ZERO);
		return false;
	}

	if( nStartAddr + *pLen > SIXB_DATALEN )
	{
		SetErrorCode(ERR_SIXBWRITE_OVERFLOW);
		return false;
	}
	CRFIDFrame revInOutFrame;
	CRFrame& revFrame = revInOutFrame.RFIDOutFrame;

	unsigned char pSendData[DATA_BUFFER];
	unsigned char ucCommand = RFIDCommand[COM_6BWRITEUSER_DATA];
	unsigned char btRollLen = WRITE_USERDATA_LEN;

	int nLeavenLen = *pLen; //剩下的长度
	int nOnceWriteLen = 0;
	int nExpect2Write = *pLen;
	*pLen = 0;//清0
	while(0 !=nLeavenLen)
	{
		nOnceWriteLen = nLeavenLen;
		if( nLeavenLen > btRollLen ) //余下长度 >32个字节
		{
			nOnceWriteLen = btRollLen; //写 32个
		}

		memset( (unsigned char *)&revFrame, 0 , sizeof(revFrame));
		memset(pSendData , 0 , DATA_BUFFER);

		pSendData[0] = nAntenna;
		pSendData[1] = nType;
		memcpy(pSendData + 2, pTagID, 8);
		pSendData[10] = nStartAddr;
		pSendData[11] = nOnceWriteLen;
		memcpy(pSendData + 12, pValue + nExpect2Write - nLeavenLen, nOnceWriteLen);

		if ( !SendNRevMsg( &ucCommand, pSendData, nOnceWriteLen + 12, revInOutFrame,TAG_6BWRITE_TIME))
		{
			return false;
		}

		int nRealDataLen = revFrame.bLength - COMMAND_LEN - ANSWER_LEN ;
		if( nRealDataLen < 0 )
		{
			SetErrorCode(ERR_DATALEN_LOZERO);
			return false;
		}

		if(revFrame.bData[0] != 0)
		{
			SetErrorCode(revFrame.bData[0], true);
			return false;
		}
		nLeavenLen = nLeavenLen - nOnceWriteLen;//已读一次
		nStartAddr += nOnceWriteLen;
		*pLen +=nOnceWriteLen;//写入长度返回
	}
	return true;
}


bool CRFIDReader::SAAT6BTagLock (unsigned char nAntenna, unsigned char nType,
								 unsigned char *pTagID, unsigned char nStartAddrr,  unsigned char nLen)
{

	ClearErrorCode();

	if( !m_bOpen )
	{
		return false;
	}

	if( NULL == pTagID )
	{
		SetErrorCode(ERR_POINTER_NULL);
		return false;

	}

	if( 0 == nLen)
	{
		SetErrorCode(ERR_SIZE_ZERO);
		return false;
	}

	if( nStartAddrr +nLen > SIXB_DATALEN) 
	{
		SetErrorCode(ERR_SIXBLOGDATA_OVERFLOW);
		return false;
	}
	CRFIDFrame revInOutFrame;
	CRFrame& revFrame = revInOutFrame.RFIDOutFrame;
	unsigned char pSendData[DATA_BUFFER];
	unsigned char ucCommand = RFIDCommand[COM_6BLOCK_TAGDATA];

	pSendData[0] = nAntenna;
	pSendData[1] = nType;
	memcpy(pSendData + 2, pTagID, 8);
	pSendData[10] = nStartAddrr;
	pSendData[11] = nLen;

	if ( SendNRevMsg( &ucCommand, pSendData, 12, revInOutFrame))
	{
		if(revFrame.bData[0] != 0)
		{
			SetErrorCode(revFrame.bData[0], true);
			return false;
		}
		else
			return true;
	}
	return false;
}


bool CRFIDReader::SAAT6BTagLockQuery (unsigned char nAntenna, 
					 unsigned char *pTagID, unsigned char nStartAddr,  unsigned char nLen,unsigned char *pData,unsigned char nDataLen)
{
	
	ClearErrorCode();

	if( !m_bOpen )
	{
		return false;
	}

	if( NULL == pTagID || NULL == pData)
	{
		SetErrorCode(ERR_POINTER_NULL);
		return false;

	}

	if( 0 == nLen)
	{
		SetErrorCode(ERR_SIZE_ZERO);
		return false;
	}

	if( nLen > nDataLen )
	{
		SetErrorCode(ERR_MOREDATA_NEED);
		return false;
	}

	if( nStartAddr +nLen > SIXB_DATALEN) 
	{
		SetErrorCode(ERR_SIXBLOGDATA_OVERFLOW);
		return false;
	}

	int nLeavenLen = nLen; //剩下的长度
	int nOnceReadLen = 0;
	int nWriteAddr = 0;//写入地址
	CRFIDFrame revInOutFrame;
	CRFrame& revFrame = revInOutFrame.RFIDOutFrame;
	while(0 !=nLeavenLen)
	{
		nOnceReadLen = nLeavenLen;
		if( nLeavenLen > READ_USERDATA_LEN ) //余下长度 >64个字节
		{
			nOnceReadLen = READ_USERDATA_LEN; //读 64个
		}
		unsigned char pSendData[DATA_BUFFER];
		unsigned char ucCommand = RFIDCommand[COM_6BLOCK_QUERY];

		pSendData[0] = nAntenna;
		pSendData[1] = 0x01;
		memcpy(pSendData + 2, pTagID, 8);
		pSendData[10] = nStartAddr;
		pSendData[11] = nOnceReadLen;

		if ( !SendNRevMsg( &ucCommand, pSendData, 12, revInOutFrame,TAG_6BLOCK_QUERY))
		{
			return false;
		}

		if(revFrame.bData[0] != 0)
		{
			SetErrorCode(revFrame.bData[0], true);
			return false;
		}

		memcpy(pData+nWriteAddr,(void*)&revFrame.bData[2],nLen); //bData[1]为天线端口?
		nLeavenLen = nLeavenLen - nOnceReadLen;//已读一次
		nStartAddr += nOnceReadLen;
		nWriteAddr += nOnceReadLen;
	}
	return true;
}


bool CRFIDReader::SAATYMakeTagUpLoadIDCode(unsigned char nOpType, unsigned char nIDType)
{
	ClearErrorCode();

	if (!m_bOpen)
	{
		return false;
	}

	unsigned char pSendData[DATA_BUFFER];
	unsigned char ucCommand = RFIDCommand[COM_YMAKE_TAGUPLOAD];

	pSendData[0] = nOpType;
	pSendData[1] = nIDType;

	CRFIDFrame RFIDInOutFrame;
	if (SendMsg(&ucCommand, pSendData, 2, RFIDInOutFrame))
		return true;
	else
		return false;
}

int CRFIDReader::SAATYRevIDMsgDecRssiExpand(
	unsigned char* nTagType, 
	unsigned int* pId,	
	int* nRSSI,
	int* nAntenna,
	int* nParam1, 
	int* nParam2)
{
	ClearErrorCode();

	if (!m_bOpen)
	{
		return -1;
	}

	if (NULL == nTagType ||
		NULL == pId ||
		NULL == nParam1 ||
		NULL == nRSSI ||
		NULL == nAntenna)
	{
		SetErrorCode(ERR_POINTER_NULL);
		return 0;
	}

	CRFIDFrame revInOutFrame;
	CRFrame& revFrame = revInOutFrame.RFIDOutFrame;

	if (GetCard(revFrame, TAG_REV_TIME))
	{

		if (revFrame.bCommand == RFIDCommand[COM_STOP_READ]) //这里的指令变成53了
		{
			return -1;
		}

		if (revFrame.bCommand == RFIDCommand[COM_SEND_HEART]) //心跳包
		{
			return 2;
		}

		if (revFrame.bData[0] != 0)
		{
			SetErrorCode(revFrame.bData[0], true);
			return 0;
		}
		else
		{
			if (revFrame.bLength <= 2)
			{
				return 2;
			}

			*nTagType = (uint8_t)(revFrame.bData[1]);
			*nRSSI = 0xFFFFFF00;
			*nRSSI += (revFrame.bData[2]);			
			*pId = (revFrame.bData[3] << 24)
				+ (revFrame.bData[4] << 16 )
				+ (revFrame.bData[5] << 8) 
				+ (revFrame.bData[6]);				
			
			*nParam1 = (revFrame.bData[7]);

			if (revFrame.bLength > 9)
			{
				*nAntenna = (revFrame.bData[8]);
			}
			else 
			{
				*nAntenna = 1;
			}

			if (revFrame.bLength >= 13 )
			{
				*nParam2 = (revFrame.bData[9] << 24)
					+ (revFrame.bData[10] << 16)
					+ (revFrame.bData[11] << 8)
					+ (revFrame.bData[12]);
			}
			else
			{
				*nParam2 = 0;
			}
		
		
			return 1;
		}
	}
	return 0;
}

bool CRFIDReader::SAATYAntennaPortEXQuery(unsigned int* nPortEnable, 
	unsigned int* nPollTime, unsigned int* nParam)
{
	ClearErrorCode();

	if (!m_bOpen)
	{
		return false;
	}

	if (NULL == nPortEnable || NULL == nPollTime || NULL == nParam)
	{
		SetErrorCode(ERR_POINTER_NULL);
		return false;
	}

	bool bRet = false;

	unsigned char SendCommand = RFIDCommand[COM_ANTENNA_QUERY_EX];//指令
	unsigned char pSendData[API_SENDDATA_BUFF];
	int nDataLen = 0;//数据内容长度

	CRFIDFrame RFIDInOutFrame;
	CRFrame &RFIDFrame = RFIDInOutFrame.RFIDOutFrame;
	do
	{
		if (!SendNRevMsg(&SendCommand, pSendData, nDataLen, RFIDInOutFrame))
		{
			break;
		}

		if (RFIDFrame.bData[0] != 0) //判断返回值 
		{
			SetErrorCode(RFIDFrame.bData[0], true);
			break;
		}


		int nRealDataLen = RFIDFrame.bLength - COMMAND_LEN - ANSWER_LEN;
		if (nRealDataLen < 8)
		{
			SetErrorCode(ERR_DATALEN_LOZERO);
			break;
		}		

		*nPortEnable = (RFIDFrame.bData[1] << 24)
			+ (RFIDFrame.bData[2] << 16)
			+ (RFIDFrame.bData[3] << 8)
			+ (RFIDFrame.bData[4]);

		*nPollTime = (RFIDFrame.bData[5] << 24)
			+ (RFIDFrame.bData[6] << 16)
			+ (RFIDFrame.bData[7] << 8)
			+ (RFIDFrame.bData[8]);

		if (nRealDataLen >= 12)
		{
			*nParam = (RFIDFrame.bData[9] << 24)
				+ (RFIDFrame.bData[10] << 16)
				+ (RFIDFrame.bData[11] << 8)
				+ (RFIDFrame.bData[12]);
		}
		else 
		{
			*nParam = 0;
		}

	

		bRet = true;
	} while (0);

	return bRet;
}

bool CRFIDReader::SAATYAntennaPortEXSet(unsigned int nPortEnable, unsigned int nPollTime, unsigned int nParam)
{
	ClearErrorCode();

	if (!m_bOpen)
	{
		return false;
	}

	bool bRet = false;
	/*
	*/
	unsigned char SendCommand = RFIDCommand[COM_ANTENNA_SET_EX];//指令
	unsigned char pSendData[API_SENDDATA_BUFF];
	pSendData[0] = (nPortEnable >> 24) & 0xff;
	pSendData[1] = (nPortEnable >> 16) & 0xff;
	pSendData[2] = (nPortEnable >> 8 ) & 0xff;
	pSendData[3] = nPortEnable & 0xff;

	pSendData[4] = (nPollTime >> 24) & 0xff;
	pSendData[5] = (nPollTime >> 16) & 0xff;
	pSendData[6] = (nPollTime >> 8) & 0xff;
	pSendData[7] = nPollTime & 0xff;

	pSendData[8] = (nParam >> 24) & 0xff;
	pSendData[9] = (nParam >> 16) & 0xff;
	pSendData[10] = (nParam >> 8) & 0xff;
	pSendData[11] = nParam & 0xff;

	int nDataLen = 12;//数据内容长度

	CRFIDFrame RFIDInOutFrame;
	CRFrame &RFIDFrame = RFIDInOutFrame.RFIDOutFrame;
	do
	{
		if (!SendNRevMsg(&SendCommand, pSendData, nDataLen, RFIDInOutFrame))
		{
			break;
		}

		if (RFIDFrame.bData[0] != 0) //判断返回值 
		{
			SetErrorCode(RFIDFrame.bData[0], true);
			break;
		}

		bRet = true;

	} while (0);

	return bRet;
}

bool CRFIDReader::SAAT6CTagSelect ( unsigned char nBank ,unsigned short nStartAddr,unsigned char MaskBit, 
										   unsigned char *Data ,unsigned char Datalength,unsigned char nSessionZone,
										   unsigned char nActiveFlag, unsigned char nCutFlag )
{
	ClearErrorCode();

	if( !m_bOpen )
	{
		return false;
	}

	if( NULL == Data )
	{
		SetErrorCode(ERR_POINTER_NULL);
		return false;
	}
	CRFIDFrame revInOutFrame;
	CRFrame& revFrame = revInOutFrame.RFIDOutFrame;

	unsigned char pSendData[DATA_BUFFER];
	unsigned char ucCommand = RFIDCommand[COM_6CSELECT_EPCTAG];


	pSendData[0] = nBank;
	//pSendData[1] = nStartAddr;
	pSendData[1] = HIBYTE(nStartAddr);
	pSendData[2] = LOBYTE(nStartAddr);
	pSendData[3] = MaskBit;
	memcpy(pSendData + 4, Data, Datalength);
	pSendData[Datalength + 4] = nSessionZone;
	pSendData[Datalength + 5] = nActiveFlag;
	pSendData[Datalength + 6] = nCutFlag;

	if ( SendNRevMsg( &ucCommand, pSendData, Datalength+7, revInOutFrame,TAG_6CSELECT_TIME))
	{
		if(revFrame.bData[0] != 0)
		{
			SetErrorCode(revFrame.bData[0], true);
			return false;
		}
		else
			return true;
	}
	return false;
}


bool CRFIDReader::SAAT6CReadTIDCode ( unsigned char nAntenna, unsigned char nType, unsigned int nTagCount)
{
	
	ClearErrorCode();

	if( !m_bOpen )
	{
		return false;
	}

	unsigned char pSendData[DATA_BUFFER];
	unsigned char ucCommand = RFIDCommand[COM_6CREAD_TID];

	pSendData[0] = nAntenna;
	pSendData[1] = nType;

	unsigned int ucScanTimes = 0;
	if (nTagCount > 16384) //预计读标签数...如果大于16384 则扫描15次
	{
		ucScanTimes = 15;
	}
	else if (nTagCount <= 1)
	{
		ucScanTimes = 0;
	}
	else 
	{
		while (nTagCount /= 2) //在(1 到 16384]
		{
			ucScanTimes++;
		}
		ucScanTimes++;
	}

	pSendData[2] = ucScanTimes;
	CRFIDFrame revFrame;
	if ( SendMsg( &ucCommand, pSendData, 3,revFrame))
		return true;
	else
		return false;
}

int CRFIDReader::SAAT6CRevTIDMsg (unsigned char* nAntenna, unsigned char* pTIDData, unsigned char* nTIDLen)
{
	ClearErrorCode();

	if( !m_bOpen )
	{
		return false;
	}

	if( NULL == nAntenna ||
		NULL == pTIDData ||
		NULL == nTIDLen)
	{
		SetErrorCode(ERR_POINTER_NULL);
		return 0;
	}

	if( 0 == *nTIDLen )
	{
		SetErrorCode(ERR_SIZE_ZERO);
		return 0;
	}

	CRFIDFrame revInOutFrame;
	CRFrame& revFrame = revInOutFrame.RFIDOutFrame;

	if ( GetCard(revFrame,TAG_REV_TIME))
	{

		if( revFrame.bCommand == RFIDCommand[COM_STOP_READ]) //这里的指令变成53了
		{
			return -1;
		}

		if( revFrame.bCommand == RFIDCommand[COM_SEND_HEART]) //心跳包
		{
			return 2;
		}

		if(revFrame.bData[0] != 0)
		{
			SetErrorCode(revFrame.bData[0], true);
			return 0;
		}
		else
		{
			*nAntenna = revFrame.bData[1];
			int nRealDataLen = revFrame.bLength - 3;
			if( nRealDataLen < 1 )
			{
				SetErrorCode(ERR_DATALEN_LOZERO);
				return 0;
			}
			if( nRealDataLen > *nTIDLen )
			{
				SetErrorCode(ERR_MOREDATA_NEED);
				return 0;
			}
			memcpy (pTIDData, &revFrame.bData[2], revFrame.bLength - 3);
			*nTIDLen = revFrame.bLength - 3;
			return 1;
		}
	}
	return 0;
}



bool CRFIDReader::SAAT6CRawReadUserData ( unsigned char nAntenna, unsigned int StartAddr,
												 unsigned char nToReadLen, unsigned char * UserData,unsigned int* pDataLen)
{
	ClearErrorCode();

	if( !m_bOpen )
	{
		return false;
	}

	if( NULL == pDataLen)
		return false;

	if( NULL == UserData )
		return false;

	if( *pDataLen < nToReadLen )
		return false;

	CRFIDFrame revInOutFrame;
	CRFrame& revFrame = revInOutFrame.RFIDOutFrame;
	unsigned char pSendData[MAX_PATH];
	unsigned char ucCommand = RFIDCommand[COM_6CREADUSER_DATA];

	pSendData[0] = nAntenna;

	WORD wLen = LOWORD(StartAddr);
	pSendData[1] = HIBYTE(wLen);
	pSendData[2] = LOBYTE(wLen);
	//memcpy(pSendData+1, StartAddr, 2);
	//pSendData[1] = StartAddr;
	pSendData[3] = nToReadLen;

	if ( SendNRevMsg( &ucCommand, pSendData, 4, revInOutFrame, TAG_6CREAD_TIME))
	{
		unsigned int nRealDataLen = revFrame.bLength - COMMAND_LEN - ANSWER_LEN;
		if( nRealDataLen < 0 )
		{
			SetErrorCode(ERR_DATALEN_LOZERO);
			return false;
		}
		if( *pDataLen < nRealDataLen* 2)
		{
			SetErrorCode(ERR_MOREDATA_NEED);
			return false;
		}

		if(revFrame.bData[0] != 0)
		{
			SetErrorCode(revFrame.bData[0], true);
			return false;
		}
		else
		{
			memcpy(UserData, revFrame.bData + 2, nToReadLen*2);//读2个就是4，因为是双字读 +1个天线端口
			*pDataLen = nToReadLen;
			return true;
		}
	}

	return false;
}


bool CRFIDReader::SAAT6CReadUserData ( unsigned char nAntenna, 
					 unsigned int StartAddr,
					 unsigned int nToReadLen,
					 unsigned int nWaitTime,
					 unsigned char * UserData,
					 unsigned int* pDataLen)
{

	ClearErrorCode();

	if( !m_bOpen )
	{
		return false;
	}

	if(  NULL == pDataLen)
		return false;

	if( NULL == UserData )
		return false;

	if( *pDataLen < nToReadLen )
		return false;

	unsigned int nLeavenLen = nToReadLen; //剩下的长度
	unsigned int nOnceReadLen = 0;//一次读取的长度
	unsigned int nReadAddr = StartAddr;//当前要读的地址
	unsigned int nLocalUserDataIndex = 0;//下一次读取的数据将写入地址偏移

	unsigned char szTempData[MAX_PATH];
	unsigned int nReadLen =0 ;

	if( nWaitTime == 0 )
	{
		nWaitTime+=1000;
	}

	DWORD dwStart = GetTickCount();
	DWORD dwEnd = GetTickCount() + nWaitTime;
	while(0 != nLeavenLen && GetTickCount() <= dwEnd )
	{
		nOnceReadLen = nLeavenLen;
		if( nLeavenLen > DATA_6CONCEREAD_LEN ) //余下长度 >14个字节
		{
			nOnceReadLen = DATA_6CONCEREAD_LEN; //读 14个
		}

		unsigned nReadLen = MAX_PATH;
		if( !SAAT6CRawReadUserData(nAntenna, 
			nReadAddr,
			nOnceReadLen,
			szTempData,
			&nReadLen) )
		{
			continue;//读取失败,继续
		}

		memcpy(UserData+nLocalUserDataIndex,szTempData,nReadLen*2);
		nReadAddr += nReadLen;
		nLeavenLen = nLeavenLen - nReadLen;
		nLocalUserDataIndex += nReadLen*2;

		////读取少了,跳出
		if( nReadLen != nOnceReadLen )
		{	
			break;
		}
	}

	*pDataLen = nToReadLen - nLeavenLen;
	if( nToReadLen == nLeavenLen )
	{
		return false;
	}

	return true;//只要有读到就认为是成功
}

bool CRFIDReader::SAAT6CRawWriteUserData (unsigned char nAntenna, 
												  unsigned char nType,  
												  unsigned char *pAccessPWD,
												  unsigned int  nStartAddr,
												  unsigned char *pWriteData, 
												  unsigned char *pLen)
{
	ClearErrorCode();

	if( !m_bOpen )
	{
		return false;
	}

	if( NULL == pAccessPWD ||
		NULL == pWriteData ||
		NULL == pLen) 
	{
		SetErrorCode(ERR_POINTER_NULL);
		return false;
	}

	if( 0 == *pLen)
	{
		SetErrorCode(ERR_SIZE_ZERO);
		return false;
	}

	CRFIDFrame revInOutFrame;
	CRFrame& revFrame = revInOutFrame.RFIDOutFrame;

	unsigned char pSendData[MAX_PATH];
	unsigned char ucCommand = RFIDCommand[COM_6CWRITEUSER_DATA];

	pSendData[0] = nAntenna;
	pSendData[1] = nType;
	memcpy(pSendData + 2, pAccessPWD, 4);

	WORD wAddr = LOWORD(nStartAddr);
	pSendData[6] = HIBYTE(wAddr);
	pSendData[7] = LOBYTE(wAddr);
	//memcpy(pSendData + 6, nStartAddr, 2);
	/*pSendData[6] = nStartAddr;*/
	pSendData[8] = *pLen;

	memcpy(pSendData + 9, pWriteData, *pLen*2);
	if ( SendNRevMsg( &ucCommand, pSendData, (*pLen*2) + 9, revInOutFrame,TAG_6CWRITE_TIME))
	{
		if(revFrame.bData[0] != 0)
		{
			SetErrorCode(revFrame.bData[0], true);
			return false;
		}
		else
			return true;
	}
	return false;
}


bool CRFIDReader::SAAT6CWriteUserData (unsigned char nAntenna, 
					  unsigned char nType,  
					  unsigned char *pAccessPWD,
					  unsigned int  nStartAddr,
					  unsigned int nWaitTime,
					  unsigned char *pWriteData, 
					  unsigned int *pToWriteLen)
{
	ClearErrorCode();

	if( !m_bOpen )
	{
		return false;
	}

	if( NULL == pAccessPWD ||
		NULL == pWriteData ||
		NULL == pToWriteLen) 
	{
		SetErrorCode(ERR_POINTER_NULL);
		return false;
	}

	if( 0 == *pToWriteLen)
	{
		SetErrorCode(ERR_SIZE_ZERO);
		return false;
	}

	if( nWaitTime == 0 )
	{
		nWaitTime += 1000;
	}

	int nToWriteLen = *pToWriteLen;
	int nLeavenLen = *pToWriteLen; //剩下要写入的长度
	unsigned char nOnceWriteLen = 0;//一次写入的长度
	int nWriteAddr = nStartAddr;//当前要写入地址
	int nLocalUserAddr = 0;

	DWORD dwStart = GetTickCount();
	DWORD dwEnd = dwStart + nWaitTime;

	while(0 !=nLeavenLen && GetTickCount() <= dwEnd )
	{
		if( nLeavenLen > DATA_6CONCEWRITE_LEN ) //余下长度 >11个字节
		{
			nOnceWriteLen = DATA_6CONCEWRITE_LEN; //写11个
		}
		else
		{
			nOnceWriteLen = (unsigned char)nLeavenLen;//不会大于 DATA_6CONCEWRITE_LEN
		}

		if( !SAAT6CRawWriteUserData (nAntenna, 
			nType,  
			pAccessPWD,
			nWriteAddr,
			pWriteData+nLocalUserAddr, 
			&nOnceWriteLen) )
		{
			continue;
		}

		nLocalUserAddr+=nOnceWriteLen*2;//双字节
		nWriteAddr += nOnceWriteLen;
		nLeavenLen = nLeavenLen - nOnceWriteLen;
	}

	*pToWriteLen = nToWriteLen - nLeavenLen;
	if( nToWriteLen == nLeavenLen )
	{
		return false;
	}

	return true;//只要有写入就认为是成功
}


bool CRFIDReader::SAAT6CWriteBankData (unsigned char nAntenna, unsigned char nType, unsigned char *pAccessPWD,
					  unsigned char nBank,  unsigned char *pWriteData, unsigned char nLen)
{
	return true;
}


bool CRFIDReader::SAAT6CClearBankData (unsigned char nAntenna, unsigned char nType, unsigned char *pAccessPWD,
					  unsigned char nBank, unsigned char nStartAddr, unsigned char nLen)
{
	return true;
}

bool CRFIDReader::SAAT6CAccessPWDSet (unsigned char nAntenna, unsigned char nType, unsigned char *pOrgPWD, unsigned char *pNewPWD)
{

	ClearErrorCode();

	if( !m_bOpen )
	{
		return false;
	}

	if( NULL == pOrgPWD || NULL == pNewPWD) 
	{
		SetErrorCode(ERR_POINTER_NULL);
		return false;
	}

	CRFIDFrame revInOutFrame;
	CRFrame &revFrame = revInOutFrame.RFIDOutFrame;
	unsigned char pSendData[DATA_BUFFER];
	unsigned char ucCommand = RFIDCommand[COM_6CACCESSPWD_CFG];


	pSendData[0] = nAntenna;
	pSendData[1] = nType;
	memcpy(pSendData + 2, pOrgPWD, 4);
	memcpy(pSendData + 6, pNewPWD, 4);

	if ( SendNRevMsg( &ucCommand, pSendData, 10, revInOutFrame))
	{
		if(revFrame.bData[0] != 0)
		{
			SetErrorCode(revFrame.bData[0], true);
			return false;
		}
		else
			return true;
	}
	return false;
}


bool CRFIDReader::SAAT6CDestroyPWDSet ( unsigned char nAntenna,unsigned char nType, unsigned char *pAccessPWD, unsigned char *pDestroyPWD )
{

	ClearErrorCode();

	if( !m_bOpen )
	{
		return false;
	}

	if( NULL == pAccessPWD || NULL == pDestroyPWD) 
	{
		SetErrorCode(ERR_POINTER_NULL);
		return false;
	}



	CRFIDFrame revInOutFrame;
	CRFrame& revFrame = revInOutFrame.RFIDOutFrame;
	unsigned char pSendData[DATA_BUFFER];
	unsigned char ucCommand = RFIDCommand[COM_6CDESTORYPWD_CFG];


	pSendData[0] = nAntenna;
	pSendData[1] = nType;
	memcpy(pSendData + 2, pAccessPWD, 4);
	memcpy(pSendData + 6, pDestroyPWD, 4);

	if ( SendNRevMsg( &ucCommand, pSendData, 10, revInOutFrame))
	{
		if(revFrame.bData[0] != 0)
		{
			SetErrorCode(revFrame.bData[0], true);
			return false;
		}
		else
			return true;
	}
	return false;
}


bool CRFIDReader::SAAT6CTagLock ( unsigned char nAntenna, unsigned char *pAccessPWD, unsigned char nType,
				unsigned char nBank)
{
	
	ClearErrorCode();

	if( !m_bOpen )
	{
		return false;
	}

	if( NULL == pAccessPWD )
	{
		SetErrorCode(ERR_POINTER_NULL);
		return false;
	}

	CRFIDFrame revInOutFrame;
	CRFrame& revFrame = revInOutFrame.RFIDOutFrame;
 
	unsigned char pSendData[DATA_BUFFER];
	unsigned char ucCommand = RFIDCommand[COM_6CLOCK_TAGCFG];


	pSendData[0] = nAntenna;
	memcpy(pSendData + 1, pAccessPWD, 4);
	pSendData[5] = nType;
	pSendData[6] = nBank;

	if ( SendNRevMsg( &ucCommand, pSendData, 7, revInOutFrame))
	{
		if(revFrame.bData[0] != 0)
		{
			SetErrorCode(revFrame.bData[0], true);
			return false;
		}
		else
			return true;
	}
	return false;
}


bool CRFIDReader::SAAT6CTagKill (unsigned char nAntenna,unsigned char *pDestroyPWD,
				unsigned char *pEPC, int nEPCLen)
{
	ClearErrorCode();

	if( !m_bOpen )
	{
		return false;
	}

	if( NULL == pDestroyPWD || NULL == pEPC )
	{
		SetErrorCode(ERR_POINTER_NULL);
		return false;
	}

	if( 0 == nEPCLen )
	{
		return false;
	}

	CRFIDFrame revInOutFrame;
	CRFrame& revFrame = revInOutFrame.RFIDOutFrame;
	unsigned char pSendData[DATA_BUFFER];
	unsigned char ucCommand = RFIDCommand[COM_DESTORY_TAG];


	pSendData[0] = nAntenna;
	memcpy(pSendData + 1, pDestroyPWD, 4);
	memcpy(pSendData + 5, pEPC, nEPCLen);

	if ( SendNRevMsg( &ucCommand, pSendData, nEPCLen + 5, revInOutFrame))
	{
		if(revFrame.bData[0] != 0)
		{
			SetErrorCode(revFrame.bData[0], true);
			return false;
		}
		else
			return true;
	}
	return false;
}


bool CRFIDReader::SAAT6CEASFlagSet (unsigned char nAntenna, unsigned char nType,unsigned char* pAccessPwd,  int nEASFlag)
{
	ClearErrorCode();

	if( !m_bOpen )
	{
		return false;
	}

	CRFIDFrame revInOutFrame;
	CRFrame& revFrame = revInOutFrame.RFIDOutFrame;

	unsigned char pSendData[DATA_BUFFER];
	unsigned char ucCommand = RFIDCommand[COM_EASFLAG_CFG];

	if( NULL == pAccessPwd )
	{
		SetErrorCode(ERR_POINTER_NULL);
		return false;
	}

	pSendData[0] = nAntenna;
	pSendData[1] = nType;
	memcpy(pSendData + 2, pAccessPwd, 4);
	pSendData[6] = nEASFlag;

	if ( SendNRevMsg( &ucCommand, pSendData, 7, revInOutFrame))
	{
		if(revFrame.bData[0] != 0)
		{
			SetErrorCode(revFrame.bData[0], true);
			return false;
		}
		else
			return true;
	}
	return false;
}


bool CRFIDReader::SAAT6CEASMonitorEnable (unsigned char nAntenna,unsigned char nSetEAS)
{	
	ClearErrorCode();

	if( !m_bOpen )
	{
		return false;
	}

	CRFIDFrame Frame;
	/*CRFrame& revFrame = Frame.RFIDOutFrame;*/

	unsigned char pSendData[DATA_BUFFER];
	unsigned char ucCommand = RFIDCommand[COM_EAS_ENABLE];

	pSendData[0] = nAntenna;
	pSendData[1] = nSetEAS;

	if ( SendMsg( &ucCommand, pSendData, 2, Frame))
	{
		/*if(revFrame.bData[0] != 0)
		{
			SetErrorCode(revFrame.bData[0], true);
			return false;
		}
		else*/
			return true;
	}
	return false;
}

int CRFIDReader::SAAT6CRevEasMsg (unsigned char* nAntenna, unsigned char* pEasData,
								  unsigned char* nEasLen)
{
	ClearErrorCode();

	if( !m_bOpen )
	{
		return false;
	}

	if( NULL == nAntenna ||
		NULL == pEasData ||
		NULL == nEasLen)
	{
		SetErrorCode(ERR_POINTER_NULL);
		return 0;
	}

	if( 0 == nEasLen)
	{
		SetErrorCode(ERR_SIZE_ZERO);
		return 0;
	}

	CRFrame revFrame;
	if ( GetCard(revFrame,TAG_REV_TIME))
	{

		if( revFrame.bCommand == RFIDCommand[COM_STOP_READ] ) //这里的指令变成53了
		{
			return -1;
		}

		if( revFrame.bCommand == RFIDCommand[COM_SEND_HEART] ) //心跳包
		{
			return 2;
		}
		if(revFrame.bData[0] != 0)
		{
			SetErrorCode(revFrame.bData[0], true);
			return 0;
		}
		else
		{
			*nAntenna = revFrame.bData[1];
			int nRealDataLen =  revFrame.bLength - 3;
			if( nRealDataLen < 1 )
			{
				SetErrorCode(ERR_DATALEN_LOZERO);
				return 0;
			}
			if( nRealDataLen > *nEasLen )
			{
				SetErrorCode(ERR_MOREDATA_NEED);
				return 0;
			}

			memcpy (pEasData, (void*)&revFrame.bData[2], nRealDataLen);
			*nEasLen = revFrame.bLength - 3;
			return 1;
		}
	}
	return 0;

}

bool CRFIDReader::SAATCopyright(char* copyright)
{

	strcpy(copyright, mCopyright);
	return true;	
}

bool CRFIDReader::SAATSetLanguageType (char* szType)
{
	this->m_sysCfg.strLanguageType = szType;
	return true;
}


bool CRFIDReader::SAATReboot(unsigned char nMode)
{
	ClearErrorCode();

	if( !m_bOpen )
	{
		return false;
	}

	bool bRet = false;
	unsigned char SendCommand = RFIDCommand[COM_READER_REBOOT];//指令
	unsigned char pSendData[API_SENDDATA_BUFF];
	*pSendData = nMode;//数据内容
	int nDataLen = 1;//数据内容长度

	CRFIDFrame RFIDInOutFrame;
	CRFrame& RFIDFrame = RFIDInOutFrame.RFIDOutFrame;
	do 
	{
		if( !SendNRevMsg(&SendCommand,pSendData,nDataLen,RFIDInOutFrame) )
		{	
			break;
		}

		if( RFIDFrame.bData[0] != 0 ) //判断返回值 
		{
			SetErrorCode(RFIDFrame.bData[0],true);
			break;
		}
		bRet = true;

	} while (0);

	return bRet;

}

bool CRFIDReader::SAATReadingIOConfig (unsigned char nConfigBit)
{
	ClearErrorCode();

	if( !m_bOpen )
	{
		return false;
	}

	bool bRet = false;
	unsigned char SendCommand = RFIDCommand[READING_IO_CONFIG];//指令 23
	unsigned char pSendData[API_SENDDATA_BUFF];
	*pSendData = nConfigBit;//数据内容
	int nDataLen = 1;//数据内容长度

	CRFIDFrame RFIDInOutFrame;
	CRFrame& RFIDFrame = RFIDInOutFrame.RFIDOutFrame;
	do 
	{
		if( !SendNRevMsg(&SendCommand,pSendData,nDataLen,RFIDInOutFrame) )
		{	
			break;
		}

		if( RFIDFrame.bData[0] != 0 ) //判断返回值 
		{
			SetErrorCode(RFIDFrame.bData[0],true);
			break;
		}
		bRet = true;

	} while (0);

	return bRet;
}


bool CRFIDReader::SAATReadingIOQuery (unsigned char* pConfigBit)
{
	ClearErrorCode();

	if( !m_bOpen )
	{
		return false;
	}

	if( NULL == pConfigBit)
	{
		SetErrorCode(ERR_POINTER_NULL);
	}
	bool bRet = false;

	unsigned char SendCommand = RFIDCommand[READING_IO_QUERY];//指令
	unsigned char pSendData[API_SENDDATA_BUFF];
	int nDataLen = 0;//数据内容长度

	CRFIDFrame RFIDInOutFrame;
	CRFrame &RFIDFrame = RFIDInOutFrame.RFIDOutFrame;

	do 
	{
		if( !SendNRevMsg(&SendCommand,pSendData,nDataLen,RFIDInOutFrame) )
		{	
			break;
		}

		if( RFIDFrame.bData[0] != 0 ) //判断返回值 
		{
			SetErrorCode(RFIDFrame.bData[0],true);
			break;
		}
		*pConfigBit = RFIDFrame.bData[1];
		bRet = true;

	} while (0);


	return bRet;
}


bool CRFIDReader::SAATIOPulseWidthSet (unsigned char nIOPort,unsigned char nWidth)
{
	ClearErrorCode();

	if( !m_bOpen )
	{
		return false;
	}

	
	bool bRet = false;

	unsigned char SendCommand = RFIDCommand[COM_IO_PULSESET];//指令  25
	unsigned char pSendData[API_SENDDATA_BUFF];
	pSendData[0] = nIOPort;
	pSendData[1] = nWidth;
	int nDataLen = 2;//数据内容长度

	CRFIDFrame RFIDInOutFrame;
	CRFrame &RFIDFrame = RFIDInOutFrame.RFIDOutFrame;

	do 
	{
		if( !SendNRevMsg(&SendCommand,pSendData,nDataLen,RFIDInOutFrame) )
		{	
			break;
		}

		if( RFIDFrame.bData[0] != 0 ) //判断返回值 
		{
			SetErrorCode(RFIDFrame.bData[0],true);
			break;
		}
		bRet = true;

	} while (0);


	return bRet;
}
bool CRFIDReader::SAATIOPulseWidthQuery (unsigned char nIOPort,unsigned char* pWidth)
{
	ClearErrorCode();

	if( !m_bOpen )
	{
		return false;
	}

	if( NULL == pWidth)
	{
		SetErrorCode(ERR_POINTER_NULL);
	}
	bool bRet = false;

	unsigned char SendCommand = RFIDCommand[COM_IO_PULSEQUERY];//指令  26
	unsigned char pSendData[API_SENDDATA_BUFF];
	pSendData[0] = nIOPort;

	int nDataLen = 1;//数据内容长度

	CRFIDFrame RFIDInOutFrame;
	CRFrame &RFIDFrame = RFIDInOutFrame.RFIDOutFrame;

	do 
	{
		if( !SendNRevMsg(&SendCommand,pSendData,nDataLen,RFIDInOutFrame) )
		{	
			break;
		}

		if( RFIDFrame.bData[0] != 0 ) //判断返回值 
		{
			SetErrorCode(RFIDFrame.bData[0],true);
			break;
		}
		* pWidth = RFIDFrame.bData[1];
		bRet = true;

	} while (0);


	return bRet;
}
bool CRFIDReader::SAATSysTest(unsigned char nType,unsigned char nAntenna, unsigned char *pTestParm, unsigned char nLen)
{	

	ClearErrorCode();

	if( !m_bOpen )
	{
		return false;
	}

	if( NULL == pTestParm )
	{
		SetErrorCode(ERR_POINTER_NULL);
		return false;
	}

	bool bRet = false;
	unsigned char SendCommand = RFIDCommand[COM_TEST_CONTROL];//指令
	unsigned char pSendData[API_SENDDATA_BUFF];
	*pSendData = nType;//数据内容
	*(pSendData+1) = nAntenna;
	memcpy(pSendData+2,pTestParm,nLen);
	int nDataLen = 2 + nLen;//数据内容长度

	CRFIDFrame RFIDInOutFrame;
	CRFrame& RFIDFrame = RFIDInOutFrame.RFIDOutFrame;
	do 
	{
		if( !SendNRevMsg(&SendCommand,pSendData,nDataLen,RFIDInOutFrame) )
		{	
			break;
		}

		if( RFIDFrame.bData[0] != 0 ) //判断返回值 
		{
			SetErrorCode(RFIDFrame.bData[0],true);
			break;
		}
		bRet = true;

	} while (0);

	return bRet;
}




bool CRFIDReader::SAATHeartSend ()
{
	
	ClearErrorCode();

	if( !m_bOpen )
	{
		return false;
	}

	bool bRet = false;


	unsigned char SendCommand = RFIDCommand[COM_SEND_HEART];//指令
	unsigned char pSendData[API_SENDDATA_BUFF];

	int nDataLen =  0;//数据内容长度

	CRFIDFrame RFIDInOutFrame;
	CRFrame &RFIDFrame = RFIDInOutFrame.RFIDOutFrame;
	do 
	{
		if(!SendNRevMsg(&SendCommand,pSendData,nDataLen,RFIDInOutFrame) )
		{	
			break;
		}

		if( RFIDFrame.bData[0] != 0 ) //判断返回值 
		{
			SetErrorCode(RFIDFrame.bData[0],true);
			break;
		}
		bRet = true;

	} while (0);

	return bRet;
}

bool CRFIDReader::SAAT6CReadEPCCode( unsigned char nAntenna, unsigned char nType,unsigned int nTagCount)
{
	ClearErrorCode();

	if( !m_bOpen )
	{
		return false;
	}

	unsigned char pSendData[DATA_BUFFER];
	unsigned char ucCommand = RFIDCommand[COM_6CREAD_EPC];

	pSendData[0] = nAntenna;
	pSendData[1] = nType;

	unsigned char ucScanTimes = 0;
	if (nTagCount > 16384) //预计读标签数...如果大于16384 则扫描15次
	{
		ucScanTimes = 15;
	}
	else if (nTagCount <= 1)
	{
		ucScanTimes = 0;
	}
	else 
	{
		while (nTagCount /= 2) //在(1 到 16384]
		{
			ucScanTimes++;
		}
		ucScanTimes++;
	}

	pSendData[2] = ucScanTimes;
	CRFIDFrame Frame;

	if ( !SendMsg( &ucCommand, pSendData, 3,Frame))
	{
		return false;
	}

	return true;
}


int CRFIDReader::SAAT6CRevEPCMsg(unsigned char* nAntenna, unsigned char* pEPCData, unsigned char* nEPCLen)
{

	if( NULL == nAntenna ||
		NULL == pEPCData ||
		NULL == nEPCLen )
	{
		SetErrorCode(ERR_POINTER_NULL);
		return 0;
	}

	if( 0 == *nEPCLen )
	{
		SetErrorCode(ERR_SIZE_ZERO);
		return 0;
	}


	CRFrame revFrame;
	if ( GetCard(revFrame,TAG_REV_TIME))
	{
		
		if( revFrame.bCommand == RFIDCommand[COM_STOP_READ]) //这里的指令变成53了
		{
			return -1;
		}

		if( revFrame.bCommand == RFIDCommand[COM_SEND_HEART]) //心跳包
		{
			return 2;
		}

		if(revFrame.bData[0] == 0x0B) //读不到卡
		{
			//continue;
		}
		if(revFrame.bData[0] != 0)
		{
			SetErrorCode(revFrame.bData[0], true);
			return 0;
		}
		else
		{
			int nRealDataLen = revFrame.bLength - 3;
			if( nRealDataLen < 1 )
			{
				SetErrorCode(ERR_DATALEN_LOZERO);
				return 0;
			}
			*nAntenna = revFrame.bData[1];
			memcpy (pEPCData, &revFrame.bData[2], nRealDataLen);
			*nEPCLen = revFrame.bLength - 3;
			return 1;
		}
	}
	return 0;
}




//判断是否在读卡状态下能识别的指令
bool CRFIDReader::CheckMsg(unsigned char nCommand)
{
	if( nCommand == RFIDCommand[COM_SEND_HEART] || //心跳包指令
		nCommand == RFIDCommand[COM_IO_OP] || //IO指令
		nCommand == RFIDCommand[COM_CARRY_OP] || //停止指令
		nCommand == RFIDCommand[COM_INPUT_QUERY] ||
		nCommand == RFIDCommand[COM_EAS_ENABLE] ||
		nCommand == RFIDCommand[COM_YSTOP])
	{
		return true;
	}

	SetErrorCode(ERR_READING_NOTEXE);
	return false;
}	


bool CRFIDReader::Reconnect()
{
	
	ClearErrorCode();

	if( !m_DataProcss.Reconect() )
	{
		return false;
	}

	//停止读卡指令
	m_bOpen = true;
	if( !PowerOff() )
	{
		m_bOpen = false;
		return false;
	}


	//if(!m_DataProcss.Close())
	//{
	//	return false;
	//}

	//if( !Open() ) //重打开
	//{
	//	m_DataProcss.Close();
	//	return false;
	//}

	return true;
}

bool CRFIDReader::TestHeart() 
{
	return SAATHeartSend();
}

bool CRFIDReader::CheckIsReadCardCommand(unsigned char nCommand)
{
	bool bRet = false;
	if( nCommand == RFIDCommand[COM_YMAKE_TAGUPLOAD])
	{
		bRet = true;
	}

	return bRet;
}


bool CRFIDReader::SendMsg(unsigned char* pCommand,unsigned char *pSendData, int dataLength,CRFIDFrame &pRevFrame)
{
	
	bool bRet  = false;
	EnterCriticalSection(&m_Critical);
	do 
	{
		
		if( m_ReadState != READ_IDLE )	//读卡状态只接收心跳包指令,IO指令,停止指令
		{
			if( !CheckMsg(* pCommand) )//检查是否在读卡状态能运行的指令
			{
				break;
			}
		}

		if( m_cmdBuffer.CheckCmdExist(*pCommand) )//指令是否在运行当中
		{
			SetErrorCode(ERR_COMMAND_EXEING);
			break;
		}

		//装包
		unsigned char pForSend[SENDFRAME_MAXBUF];
		int totalFrameSize = 0;
		if( !m_DataProcss.PackMsg(pCommand,pSendData,dataLength,pRevFrame,pForSend,&totalFrameSize) )
		{
			break;
		}

		if( !CheckIsReadCardCommand( *pCommand ) )//是否读卡指令
		{
			if( !m_cmdBuffer.AddCmd(&pRevFrame) )//增加到命令序列
			{
				break;
			}
		}

		if( !m_DataProcss.SendMsg(pCommand,pForSend,totalFrameSize,pRevFrame) )//发送消息
		{
			if( !CheckIsReadCardCommand( *pCommand ) )//是否读卡指令
			{
				if( !m_cmdBuffer.DelCmd(&pRevFrame) )
				{
					break;
				}
			}
		}

		//是否读卡命令 这里直接赋值，导致handle泄漏，故操作有handle的结构体小心
		if( *pCommand== RFIDCommand[COM_YMAKE_TAGUPLOAD] )
		{
			//memcpy((void*)&m_ReadCardFrame,(void*)&pRevFrame,sizeof(CRFIDFrame));
			m_ReadState = READ_EPC;
			m_CardIDBuffer.Clear();
		}

		bRet = true;
	}while (0);

	LeaveCriticalSection(&m_Critical);
	return bRet;
}


bool CRFIDReader::SendNRevMsg(unsigned char *pSendCommand, unsigned char *pSendData, int dataLength, CRFIDFrame &pRevFrame,int nWaitTime )
{
	if( !SendMsg(pSendCommand,pSendData,dataLength,pRevFrame) )	
	{
		return false;
	}

	if( !GetMsgResult(pRevFrame,nWaitTime) )
	{
		SetErrorCode(ERR_RECVTHREAD_OVERTIME);
		return false;
	}

	return true;
}


bool CRFIDReader::SAATCarrierWaveOp(unsigned char nType, unsigned char  nPort)
{
	
	ClearErrorCode();

	if( !m_bOpen )
	{
		return false;
	}

	bool bRet = false;
	unsigned char SendCommand = RFIDCommand[COM_CARRY_OP];//指令
	unsigned char pSendData[API_SENDDATA_BUFF];
	*pSendData = nType;//数据内容
	*(pSendData+1) = nPort;
	int nDataLen = 1 + 1;//数据内容长度

	CRFIDFrame InRFIDFrame;
	CRFrame& RFIDFrame = InRFIDFrame.RFIDOutFrame;
	do 
	{
		if( !SendNRevMsg(&SendCommand,pSendData,nDataLen,InRFIDFrame,3000) )
		{	
			break;
		}

		if( RFIDFrame.bData[0] != 0 ) //判断返回值 
		{
			SetErrorCode(RFIDFrame.bData[0],true);
			break;
		}
		bRet = true;

	} while (0);


	return bRet;
}

void CRFIDReader::GetErrorMsg(char *szMsg,int nLen)
{
	string strError;
	int errorCode = GetErrorCode();
	msgError.GetErrorMessage(m_sysCfg.strLanguageType,errorCode,strError);
	strcpy(szMsg,strError.c_str());

}

bool CRFIDReader::PowerOff()
{
	ClearErrorCode();

	if (!m_bOpen)
	{
		return false;
	}

	bool bRet = false;
	unsigned char SendCommand = RFIDCommand[COM_YSTOP];//指令
	unsigned char pSendData[API_SENDDATA_BUFF];
	int nDataLen = 0;//数据内容长度

	CRFIDFrame InRFIDFrame;
	CRFrame& RFIDFrame = InRFIDFrame.RFIDOutFrame;
	do
	{
		if (!SendNRevMsg(&SendCommand, pSendData, nDataLen, InRFIDFrame, 3000))
		{
			break;
		}

		if (RFIDFrame.bData[0] != 0) //判断返回值 
		{
			SetErrorCode(RFIDFrame.bData[0], true);
			break;
		}

	
		bRet = true;

	} while (0);

	m_ReadState = READ_IDLE;
	return bRet;
}

bool CRFIDReader::WriteEPCCode(unsigned char nAntenna,
								   unsigned char nType,
								   unsigned char *pAccessPWD, 
								   unsigned char *pWriteData,
								   unsigned char nLen)
{
	/*bool bRet = false;
	DWORD dwStart = GetTickCount();
	DWORD dwEnd = dwStart + 3000;
	while(	GetTickCount() < dwEnd )
	{
		if( WriteEPCCode_Raw(nAntenna,nType,pAccessPWD,pWriteData,nLen))
		{
			bRet = true;
			break;
		}
	}
	return bRet;*/
	return  WriteEPCCode_Raw(nAntenna,nType,pAccessPWD,pWriteData,nLen);
}

bool CRFIDReader::WriteEPCCode_Raw(unsigned char nAntenna,
							   unsigned char nType,
							   unsigned char *pAccessPWD, 
							   unsigned char *pWriteData,
							   unsigned char nLen)
{
	ClearErrorCode();

	if( !m_bOpen )
	{
		return false;
	}

	if( NULL == pAccessPWD ||
		NULL == pWriteData )
	{
		SetErrorCode(ERR_POINTER_NULL);
		return false;
	}

	if( 0 == nLen )
	{
		SetErrorCode(ERR_SIZE_ZERO);
		return false;
	}

	CRFIDFrame InOutRFIDFrame;
	CRFrame &RFIDFrame = InOutRFIDFrame.RFIDOutFrame;

	unsigned char pSendData[DATA_BUFFER];
	unsigned char ucCommand = RFIDCommand[COM_6CWRITE_EPCDATA];


	pSendData[0] = nAntenna;
	pSendData[1] = nType;
	memcpy(pSendData + 2, pAccessPWD, 4);
	pSendData[6] = nLen/2;
	memcpy(pSendData + 7, pWriteData, nLen);//实际发 2*6个数据
	if ( !SendNRevMsg( &ucCommand, pSendData, nLen + 7, InOutRFIDFrame))
	{
		return false;
	}

	if(RFIDFrame.bData[0] != 0)
	{
		SetErrorCode(RFIDFrame.bData[0], true);
		return false;
	}

	return true;

}

bool CRFIDReader::SAATSysInfQuery (unsigned char nType, unsigned char *pPara, unsigned char *pLen)
{
	ClearErrorCode();

	if( !m_bOpen )
	{
		return false;
	}

	if( NULL == pPara || NULL == pLen )
	{
		SetErrorCode(ERR_POINTER_NULL);
		return false;
	}

	if( 0 == *pLen )
	{
		SetErrorCode(ERR_SIZE_ZERO);
		return false;
	}

	unsigned char SendCommand = RFIDCommand[COM_SYS_QUERY];
	unsigned char pSendData = nType;
	int nDataLen = 1;//无数据,只有指令,为0
	CRFIDFrame InOutRFIDFrame;
	CRFrame &RFIDFrame = InOutRFIDFrame.RFIDOutFrame;
	bool bRet = false;
	
	do 
	{
		if( !SendNRevMsg(&SendCommand,&pSendData,nDataLen,InOutRFIDFrame) )
		{	
			break;
		}
		
		if( RFIDFrame.bData[0] != 0 ) //检验操作状态,成功为0
		{
			SetErrorCode(RFIDFrame.bData[0],true);
			break;
		}

		//55 05 00 11 01 00 53 41 54 54 2d 46 38 30 35 b6
		int nRevDataLen = RFIDFrame.bLength;//调试时为17长度,即数据长度+指令长度
		int nRealDataLen = RFIDFrame.bLength - COMMAND_LEN - ANSWER_LEN;
		if( nRealDataLen < 0 )
		{
			SetErrorCode(ERR_DATALEN_LOZERO);
			break;
		}

		if( nRealDataLen > *pLen )
		{
			SetErrorCode(ERR_MOREDATA_NEED);
			break;
		}

		memcpy(pPara,RFIDFrame.bData+1,nRealDataLen);
		*pLen = nRealDataLen;
		bRet = true;
	} while (0);


	return bRet;
}

bool CRFIDReader::Open()
{
	ClearErrorCode();

	if( !m_DataProcss.Open(m_sysCfg) )
	{	
		return false;
	}

/*
	bool bRet = false;
	unsigned char SendCommand = RFIDCommand[COM_OPEN_CONN];//指令
	unsigned char pSendData[API_SENDDATA_BUFF];
	memset(pSendData,0,6);
	//*pSendData = nType;//数据内容
	//memset(++pSendData,0,6);
	//*(pSendData+1) = nPort;
	int nDataLen = 6;//数据内容长度

	CRFIDFrame InRFIDFrame;
	CRFrame& RFIDFrame = InRFIDFrame.RFIDOutFrame;
	do 
	{
		if( !SendNRevMsg(&SendCommand,pSendData,nDataLen,InRFIDFrame,3000) )
		{	
			break;
		}
		if( RFIDFrame.bData[0] != 0 ) //判断返回值 
		{
			SetErrorCode(RFIDFrame.bData[0],true);
			break;
		}
		bRet = true;
	} while (0);

*/

	//停止读卡指令
	m_bOpen = true;
	if( !PowerOff() )
	{
		m_bOpen = false;
		m_DataProcss.Close();
		return false;
	}

	return true;
}

bool CRFIDReader::Open(CRFIDSystemCfg& cfg)
{
	ClearErrorCode();

	if( !m_DataProcss.Open(cfg) )
	{	
		return false;
	}

	//停止读卡指令
	m_bOpen = true;
	if( !PowerOff() )
	{
		m_bOpen = false;
		m_DataProcss.Close();
		return false;
	}


	//unsigned char nType = 0x02;
	//unsigned char szPara[200];
	//unsigned char nLen = 200;
	//ZeroMemory(szPara,200);
	//if( !SysInfQuery(nType,szPara,&nLen)) //查询读写器系列号
	//{
	//	return false;
	//}

	//SetProuctSN((char*)szPara);//设置读写器序列号
	//m_bOpen = true;

	return true;
}

bool CRFIDReader::SAATGPRSParaSet (unsigned char nType, unsigned char* pPara, unsigned char nLen)
{
	ClearErrorCode();

	if( !m_bOpen )
	{
		return false;
	}

	if( NULL == pPara )
	{
		SetErrorCode(ERR_POINTER_NULL);
		return false;
	}

	if( 0 == nLen )
	{
		SetErrorCode(ERR_SIZE_ZERO);
		return false;
	}

	bool bRet = false;
	/*
	*/
	unsigned char SendCommand = RFIDCommand[COM_GPRS_SET];//指令
	unsigned char pSendData[API_SENDDATA_BUFF];
	*pSendData = nType;//数据内容

	memcpy(pSendData+1,pPara,nLen);
	int nDataLen = 1 + nLen;//数据内容长度

	CRFIDFrame RFIDInOutFrame;
	CRFrame &RFIDFrame = RFIDInOutFrame.RFIDOutFrame;
	do 
	{
		if( !SendNRevMsg(&SendCommand,pSendData,nDataLen,RFIDInOutFrame,7000) )
		{	
			break;
		}

		if( RFIDFrame.bData[0] != 0 ) //判断返回值 
		{
			SetErrorCode(RFIDFrame.bData[0],true);
			break;
		}
		bRet = true;

	} while (0);
	return bRet;
}


bool CRFIDReader::SAATGPRSParaQuery (int nType, unsigned char* pPara,unsigned char *pLen)
{

	ClearErrorCode();

	if( !m_bOpen )
	{
		return false;
	}

	if( NULL == pPara || NULL == pLen)
	{
		SetErrorCode(ERR_POINTER_NULL);
		return false;
	}

	if( 0 == *pLen )
	{
		SetErrorCode(ERR_SIZE_ZERO);
		return false;
	}

	bool bRet = false;

	unsigned char SendCommand = RFIDCommand[COM_GPRS_QUERY];//指令
	unsigned char pSendData[API_SENDDATA_BUFF];
	*pSendData = nType;//数据内容
	int nDataLen = 1;//数据内容长度

	CRFIDFrame RFIDInOutFrame;
	CRFrame& RFIDFrame = RFIDInOutFrame.RFIDOutFrame;
	do 
	{
		if( !SendNRevMsg(&SendCommand,pSendData,nDataLen,RFIDInOutFrame,7000) )
		{	
			break;
		}

		if( RFIDFrame.bData[0] != 0 ) //判断返回值 
		{
			SetErrorCode(RFIDFrame.bData[0],true);
			break;
		}
		int nRealDataLen = RFIDFrame.bLength - COMMAND_LEN - ANSWER_LEN;
		if( nRealDataLen < 0 )
		{
			SetErrorCode(ERR_DATALEN_LOZERO);
			break;
		}
		if( nRealDataLen > *pLen )
		{
			SetErrorCode(ERR_MOREDATA_NEED);
			break;
		}

		memcpy(pPara,RFIDFrame.bData+1,nRealDataLen);
		*pLen = nRealDataLen;
		bRet = true;

	} while (0);

	return bRet;
}
bool CRFIDReader::SAATWIFIParaSet (unsigned char nType, unsigned char* pPara, unsigned char nLen)
{
	ClearErrorCode();

	if( !m_bOpen )
	{
		return false;
	}

	if( NULL == pPara )
	{
		SetErrorCode(ERR_POINTER_NULL);
		return false;
	}

	if( 0 == nLen )
	{
		SetErrorCode(ERR_SIZE_ZERO);
		return false;
	}

	bool bRet = false;
	/*
	*/
	unsigned char SendCommand = RFIDCommand[COM_WIFI_SET];//指令
	unsigned char pSendData[API_SENDDATA_BUFF];
	*pSendData = nType;//数据内容

	memcpy(pSendData+1,pPara,nLen);
	int nDataLen = 1 + nLen;//数据内容长度

	CRFIDFrame RFIDInOutFrame;
	CRFrame &RFIDFrame = RFIDInOutFrame.RFIDOutFrame;
	do 
	{
		if( !SendNRevMsg(&SendCommand,pSendData,nDataLen,RFIDInOutFrame) )
		{	
			break;
		}

		if( RFIDFrame.bData[0] != 0 ) //判断返回值 
		{
			SetErrorCode(RFIDFrame.bData[0],true);
			break;
		}
		bRet = true;

	} while (0);
	return bRet;
}


bool CRFIDReader::SAATWIFIParaQuery (int nType, unsigned char* pPara,unsigned char *pLen)
{

	ClearErrorCode();

	if( !m_bOpen )
	{
		return false;
	}

	if( NULL == pPara || NULL == pLen)
	{
		SetErrorCode(ERR_POINTER_NULL);
		return false;
	}

	if( 0 == *pLen )
	{
		SetErrorCode(ERR_SIZE_ZERO);
		return false;
	}

	bool bRet = false;

	unsigned char SendCommand = RFIDCommand[COM_WIFI_QUERY];//指令
	unsigned char pSendData[API_SENDDATA_BUFF];
	*pSendData = nType;//数据内容
	int nDataLen = 1;//数据内容长度

	CRFIDFrame RFIDInOutFrame;
	CRFrame& RFIDFrame = RFIDInOutFrame.RFIDOutFrame;
	do 
	{
		if( !SendNRevMsg(&SendCommand,pSendData,nDataLen,RFIDInOutFrame) )
		{	
			break;
		}

		if( RFIDFrame.bData[0] != 0 ) //判断返回值 
		{
			SetErrorCode(RFIDFrame.bData[0],true);
			break;
		}
		int nRealDataLen = RFIDFrame.bLength - COMMAND_LEN - ANSWER_LEN;
		if( nRealDataLen < 0 )
		{
			SetErrorCode(ERR_DATALEN_LOZERO);
			break;
		}
		if( nRealDataLen > *pLen )
		{
			SetErrorCode(ERR_MOREDATA_NEED);
			break;
		}

		memcpy(pPara,RFIDFrame.bData+1,nRealDataLen);
		*pLen = nRealDataLen;
		bRet = true;

	} while (0);

	return bRet;
}


bool CRFIDReader::SAATRawSendData(unsigned char *pSendData, unsigned char nLen)
{
	ClearErrorCode();

	if( !m_bOpen )
	{
		return false;
	}

	if( NULL == pSendData )
	{
		SetErrorCode(ERR_POINTER_NULL);
		return false;
	}

	/*if( 0 == nLen )
	{
	pConnect->SetErrorCode(ERR_SIZE_ZERO);
	return false;
	}*/

	return m_DataProcss.SendRawData(pSendData,nLen);
}

bool CRFIDReader::SAATRawRevData(unsigned char *pRecvData, unsigned char* pLen, int nWaitTime)
{
	ClearErrorCode();

	if( !m_bOpen )
	{
		return false;
	}

	if( NULL == pRecvData || pLen == NULL )
	{
		SetErrorCode(ERR_POINTER_NULL);
		return false;
	}

	/*if( 0 == nLen )
	{
	pConnect->SetErrorCode(ERR_SIZE_ZERO);
	return false;
	}*/

	return m_DataProcss.RevRawData(pRecvData,pLen,nWaitTime);
}

bool CRFIDReader::SAATEnterTrans (unsigned char nType)
{

	ClearErrorCode();

	if( !m_bOpen )
	{
		return false;
	}

	bool bRet = false;

	unsigned char SendCommand = RFIDCommand[COM_WIFI_TRANS_REST];//指令
	unsigned char pSendData[API_SENDDATA_BUFF];
	*pSendData = nType;//数据内容
	int nDataLen = 1;//数据内容长度

	CRFIDFrame RFIDInOutFrame;
	CRFrame &RFIDFrame = RFIDInOutFrame.RFIDOutFrame;
	do 
	{
		if( !SendNRevMsg(&SendCommand,pSendData,nDataLen,RFIDInOutFrame) )
		{	
			break;
		}

		if( RFIDFrame.bData[0] != 0 ) //判断返回值 
		{
			SetErrorCode(RFIDFrame.bData[0],true);
			break;
		}
		bRet = true;

	} while (0);
	return bRet;
}

bool CRFIDReader::SAATResetWifiBaund()
{

	ClearErrorCode();

	if( !m_bOpen )
	{
		return false;
	}

	bool bRet = false;

	unsigned char SendCommand = RFIDCommand[COM_WIFI_TRANS_REST];//指令
	unsigned char pSendData[API_SENDDATA_BUFF];
	*pSendData = 0xFD;//数据内容
	int nDataLen = 1;//数据内容长度

	CRFIDFrame RFIDInOutFrame;
	CRFrame &RFIDFrame = RFIDInOutFrame.RFIDOutFrame;
	do 
	{
		if( !SendNRevMsg(&SendCommand,pSendData,nDataLen,RFIDInOutFrame) )
		{	
			break;
		}

		if( RFIDFrame.bData[0] != 0 ) //判断返回值 
		{
			SetErrorCode(RFIDFrame.bData[0],true);
			break;
		}
		bRet = true;

	} while (0);
	return bRet;
}

bool CRFIDReader::SAAT6CReadEPCTIDCode( unsigned char nAntenna, unsigned char nType,unsigned int nTagCount)
{
	ClearErrorCode();

	if( !m_bOpen )
	{
		return false;
	}

	unsigned char pSendData[DATA_BUFFER];
	unsigned char ucCommand = RFIDCommand[COM_6CREAD_EPCTID];

	pSendData[0] = nAntenna;
	pSendData[1] = nType;

	unsigned char ucScanTimes = 0;
	if (nTagCount > 16384) //预计读标签数...如果大于16384 则扫描15次
	{
		ucScanTimes = 15;
	}
	else if (nTagCount <= 1)
	{
		ucScanTimes = 0;
	}
	else 
	{
		while (nTagCount /= 2) //在(1 到 16384]
		{
			ucScanTimes++;
		}
		ucScanTimes++;
	}

	pSendData[2] = ucScanTimes;
	CRFIDFrame Frame;

	if ( !SendMsg( &ucCommand, pSendData, 3, Frame))
	{
		return false;
	}

	return true;
}

int  CRFIDReader::SAAT6CRevEPCTIDMsg(unsigned char* nAntenna, unsigned char* pEPCData, unsigned char* nEPCLen,
						unsigned char* pTIDData, unsigned char* nTIDLen)
{
	if( NULL == nAntenna ||
		NULL == pEPCData ||
		NULL == nEPCLen )
	{
		SetErrorCode(ERR_POINTER_NULL);
		return 0;
	}

	if( 0 == *nEPCLen )
	{
		SetErrorCode(ERR_SIZE_ZERO);
		return 0;
	}


	CRFrame revFrame;
	if ( GetCard(revFrame,TAG_REV_TIME))
	{

		if( revFrame.bCommand == RFIDCommand[COM_STOP_READ]) //这里的指令变成53了
		{
			return -1;
		}

		if( revFrame.bCommand == RFIDCommand[COM_SEND_HEART]) //心跳包
		{
			return 2;
		}

		if(revFrame.bData[0] == 0x0B) //读不到卡
		{
			//continue;
		}
		if(revFrame.bData[0] != 0)
		{
			SetErrorCode(revFrame.bData[0], true);
			return 0;
		}
		else
		{
			int nRealDataLen = revFrame.bLength - 3;
			if( nRealDataLen < 1 )
			{
				SetErrorCode(ERR_DATALEN_LOZERO);
				return 0;
			}

			*nAntenna = revFrame.bData[1];

			*nEPCLen = revFrame.bData[2];
			memcpy (pEPCData, &revFrame.bData[4], *nEPCLen);

			*nTIDLen = revFrame.bData[3];
			//added by haowenfeng in 2013-01-05 将pEPCData改成pTIDData
			memcpy (pTIDData, &revFrame.bData[4+*nEPCLen], *nTIDLen);
			return 1;
		}
	}

	return 0;
}

bool CRFIDReader::SAATFlashTotalCountQuery(unsigned char* pPara, unsigned char *pLen)
{
	ClearErrorCode();

	if( !m_bOpen )
	{
		return true;
	}
	if( NULL == pPara || NULL == pLen )
	{
		SetErrorCode(ERR_POINTER_NULL);
		return false;
	}
	if( 0 == *pLen )
	{
		SetErrorCode(ERR_SIZE_ZERO);
		return false;
	}

	unsigned char SendCommand = RFIDCommand[READER_FLASHDATACOUNT_QUERY];//指令
	unsigned char pSendData[API_SENDDATA_BUFF];
	int nDataLen = 0;//数据内容长度

	CRFIDFrame RFIDInOutFrame;
	CRFrame& RFIDFrame = RFIDInOutFrame.RFIDOutFrame;
	bool bRet = false;
	do 
	{
		if( !SendNRevMsg(&SendCommand,pSendData,nDataLen,RFIDInOutFrame,10*1000) )
		{	
			break;
		}

		if( RFIDFrame.bData[0] != 0 ) //判断返回值 
		{
			SetErrorCode(RFIDFrame.bData[0],true);
			break;
		}

		int nRealDataLen = RFIDFrame.bLength - COMMAND_LEN - ANSWER_LEN;
		if( nRealDataLen < 0 )
		{
			SetErrorCode(ERR_DATALEN_LOZERO);
			break;
		}
		if( nRealDataLen > *pLen )
		{
			SetErrorCode(ERR_MOREDATA_NEED);
			break;
		}

		memcpy(pPara,RFIDFrame.bData+1,nRealDataLen);
		*pLen = nRealDataLen;
		bRet = true;

	} while (0);

	return bRet;
}

bool CRFIDReader::SAATFlashDataQuery(unsigned char nOpType, unsigned char* pPara, unsigned char *pLen)
{
	ClearErrorCode();

	if( !m_bOpen )
	{
		return true;
	}
	if( NULL == pPara || NULL == pLen )
	{
		SetErrorCode(ERR_POINTER_NULL);
		return false;
	}
	if( 0 == *pLen )
	{
		SetErrorCode(ERR_SIZE_ZERO);
		return false;
	}

	unsigned char SendCommand = RFIDCommand[READER_FLASHDATA_QUERY];//指令
	unsigned char pSendData[API_SENDDATA_BUFF];
	*pSendData = nOpType;
	int nDataLen = 1;//数据内容长度

	CRFIDFrame RFIDInOutFrame;
	CRFrame& RFIDFrame = RFIDInOutFrame.RFIDOutFrame;
	bool bRet = false;
	do 
	{
		if( !SendNRevMsg(&SendCommand,pSendData,nDataLen,RFIDInOutFrame,3000) )
		{	
			break;
		}

		if( RFIDFrame.bData[0] != 0 ) //判断返回值 
		{
			SetErrorCode(RFIDFrame.bData[0],true);
			break;
		}

		int nRealDataLen = RFIDFrame.bLength - COMMAND_LEN - ANSWER_LEN;
		if( nRealDataLen < 0 )
		{
			SetErrorCode(ERR_DATALEN_LOZERO);
			break;
		}
		if( nRealDataLen > *pLen )
		{
			SetErrorCode(ERR_MOREDATA_NEED);
			break;
		}

		memcpy(pPara,RFIDFrame.bData+1,nRealDataLen);
		*pLen = nRealDataLen;
		bRet = true;

	} while (0);

	return bRet;
}

bool CRFIDReader::SAATClearFlash()
{
	ClearErrorCode();

	if( !m_bOpen )
	{
		return true;
	}

	unsigned char SendCommand = RFIDCommand[READER_FLASHCLEAR];//指令
	unsigned char pSendData[API_SENDDATA_BUFF];
	int nDataLen = 0;//数据内容长度

	CRFIDFrame RFIDInOutFrame;
	CRFrame& RFIDFrame = RFIDInOutFrame.RFIDOutFrame;//yyz 2012.2.23 修改bug
	bool bRet = false;
	do 
	{
		if( !SendNRevMsg(&SendCommand,pSendData,nDataLen,RFIDInOutFrame,2*60*1000) )
		{	
			break;
		}

		if( RFIDFrame.bData[0] != 0 ) //判断返回值 
		{
			SetErrorCode(RFIDFrame.bData[0],true);
			break;
		}

		bRet = true;

	} while (0);

	return bRet;
}

bool CRFIDReader::SAATReaderTimeQuery(unsigned char *pPara, unsigned char *pLen)
{
	ClearErrorCode();

	if( !m_bOpen )
	{
		return true;
	}
	if( NULL == pPara || NULL == pLen )
	{
		SetErrorCode(ERR_POINTER_NULL);
		return false;
	}
	if( 0 == *pLen )
	{
		SetErrorCode(ERR_SIZE_ZERO);
		return false;
	}

	unsigned char SendCommand = RFIDCommand[READER_TIME_QUERY];//指令
	unsigned char pSendData[API_SENDDATA_BUFF];
	int nDataLen = 0;//数据内容长度

	CRFIDFrame RFIDInOutFrame;
	CRFrame& RFIDFrame = RFIDInOutFrame.RFIDOutFrame;
	bool bRet = false;
	do 
	{
		if( !SendNRevMsg(&SendCommand,pSendData,nDataLen,RFIDInOutFrame,3000) )
		{	
			break;
		}
		int nRealDataLen = RFIDFrame.bLength - COMMAND_LEN - ANSWER_LEN;
		if( RFIDFrame.bData[0] != 0 ) //判断返回值 
		{
			SetErrorCode(RFIDFrame.bData[0],true);
			break;
		}

		memcpy(pPara,RFIDFrame.bData+1,nRealDataLen);
		*pLen = nRealDataLen;
		bRet = true;

	} while (0);

	return bRet;
}


bool CRFIDReader::SAATSetReaderTime(unsigned char *pPara, unsigned char nLen)
{
	ClearErrorCode();

	if( !m_bOpen )
	{
		return true;
	}
	if( NULL == pPara)
	{
		SetErrorCode(ERR_POINTER_NULL);
		return false;
	}
	if( 0 == nLen )
	{
		SetErrorCode(ERR_SIZE_ZERO);
		return false;
	}

	unsigned char SendCommand = RFIDCommand[READER_TIME_SET];//指令
	unsigned char pSendData[API_SENDDATA_BUFF];
	memcpy(pSendData,pPara,nLen);
	int nDataLen =  nLen;//数据内容长度

	CRFIDFrame RFIDInOutFrame;
	CRFrame& RFIDFrame = RFIDInOutFrame.RFIDOutFrame;
	bool bRet = false;
	do 
	{
		if( !SendNRevMsg(&SendCommand,pSendData,nDataLen,RFIDInOutFrame,3000) )
		{	
			break;
		}
		if( RFIDFrame.bData[0] != 0 ) //判断返回值 
		{
			SetErrorCode(RFIDFrame.bData[0],true);
			break;
		}

		bRet = true;

	} while (0);

	return bRet;
}