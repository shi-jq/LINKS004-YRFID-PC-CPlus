#include "StdAfx.h"
#include "WIRELESSRFIDAPIEXPORT.h"
#include "Global.h"
#include "RFIDReaderManager.h"

bool WIRELESS_RFID_API __stdcall WIRELESS_ApiInit(void** pHandle)
{
	CRFIDReaderServer *pNewReader =  CRFIDReaderManager::Instance()->CreateReader();
	if( NULL == pNewReader )
	{
		return false;
	}
	*pHandle = pNewReader;
	return true;
}

bool WIRELESS_RFID_API __stdcall WIRELESS_Quit(void** pHandle)
{
	if( NULL == *pHandle )
	{
		return false;
	}

	CRFIDReaderServer* pReader = (CRFIDReaderServer*)(*pHandle);
	pReader->Quit();
	if(CRFIDReaderManager::Instance()->CloseReader(pReader))
	{
		*pHandle = NULL;
		return true;
	}
	return false;
}


bool WIRELESS_RFID_API  __stdcall WIRELESS_StartServer(void* pHandle,char *pHostName,int nsocketPort,READER_CALLBACK pCallBack)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReaderServer* pReader = (CRFIDReaderServer*)pHandle;

	return 	pReader->StartListen(pHostName,nsocketPort,pCallBack);

}

bool WIRELESS_RFID_API  __stdcall WIRELESS_StopServer(void* pHandle)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReaderServer* pReader = (CRFIDReaderServer*)pHandle;

	return 	pReader->StopListen();
}

bool WIRELESS_RFID_API __stdcall WIRELESS_ClearReader(void* pHandle)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReaderServer* pReader = (CRFIDReaderServer*)pHandle;

	pReader->ClearAllReader();
	return true;

}


bool WIRELESS_RFID_API  __stdcall WIRELESS_CloseReader(void* pHandle,WirelessReaderInfo* pWirelessReaderInfo)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReaderServer* pReader = (CRFIDReaderServer*)pHandle;

	return 	pReader->CloseReader(pWirelessReaderInfo);
}

bool WIRELESS_RFID_API  __stdcall WIRELESS_SAATSysInfSet(void* pHandle,WirelessReaderInfo* pWirelessReaderInfo,unsigned char nType,unsigned char* pParm,int nLen)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReaderServer* pReader = (CRFIDReaderServer*)pHandle;

	return 	pReader->SAATSysInfSet(pWirelessReaderInfo,nType, pParm, nLen);
}


bool WIRELESS_RFID_API  __stdcall WIRELESS_SAAT_PowerOff(void *pHandle,
														 WirelessReaderInfo* pWirelessReaderInfo)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReaderServer* pReader = (CRFIDReaderServer*)pHandle;
	return pReader->PowerOff(pWirelessReaderInfo);
}


bool WIRELESS_RFID_API  __stdcall WIRELESS_SAAT_GetLastTime(void *pHandle,WirelessReaderInfo* pWirelessReaderInfo,unsigned long& nTime)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReaderServer* pReader = (CRFIDReaderServer*)pHandle;
	return pReader->GetLastTime(pWirelessReaderInfo,nTime);
}


bool WIRELESS_RFID_API  __stdcall WIRELESS_SAAT_SysInfQuery(void* pHandle ,
															WirelessReaderInfo* pWirelessReaderInfo,
															unsigned char nType)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReaderServer* pReader = (CRFIDReaderServer*)pHandle;

	return pReader->SAATSysInfQuery(pWirelessReaderInfo,nType);
}

bool WIRELESS_RFID_API  __stdcall WIRELESS_SAAT_RFParaSet(void* pHandle ,WirelessReaderInfo* pWirelessReaderInfo,unsigned char nType, unsigned char nParaLen,unsigned char* pPara)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReaderServer* pReader = (CRFIDReaderServer*)pHandle;
	return pReader->SAATRFParaSet(pWirelessReaderInfo,nType,nParaLen,pPara);
}

bool WIRELESS_RFID_API  __stdcall WIRELESS_SAAT_RFParaQuery(void* pHandle ,
															WirelessReaderInfo* pWirelessReaderInfo,
															unsigned char nType)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReaderServer* pReader = (CRFIDReaderServer*)pHandle;
	return pReader->SAATRFParaQuery(pWirelessReaderInfo,nType);
}

bool WIRELESS_RFID_API  __stdcall WIRELESS_SAAT_AntennaParmQuery(void* pHandle,
																 WirelessReaderInfo* pWirelessReaderInfo)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReaderServer* pReader = (CRFIDReaderServer*)pHandle;
	return pReader->SAATAntennaParmQuery(pWirelessReaderInfo);
}

bool  WIRELESS_RFID_API  __stdcall WIRELESS_SAAT_AntennaParmSet(void* pHandle ,
																WirelessReaderInfo* pWirelessReaderInfo,
																unsigned char *pPara,
																unsigned char nLen)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReaderServer* pReader = (CRFIDReaderServer*)pHandle;
	return pReader->SAATAntennaParmSet(pWirelessReaderInfo,pPara,nLen );
}

bool WIRELESS_RFID_API  __stdcall WIRELESS_SAAT_ParmOp(void* pHandle ,
													   WirelessReaderInfo* pWirelessReaderInfo,
													   unsigned char nType,
													   unsigned char nStartAddrr, 
													   unsigned char nLen, 
													   unsigned char *pData,
													   unsigned char *pDataLen,
													   int *nMsgID)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReaderServer* pReader = (CRFIDReaderServer*)pHandle;
	return pReader->SAATParmOp(pWirelessReaderInfo,nType,nStartAddrr,
		nLen,pData,pDataLen,nMsgID);
}

bool WIRELESS_RFID_API  __stdcall WIRELESS_SAAT_FlashTotalCountQuery(
	void* pHandle ,
	WirelessReaderInfo* pWirelessReaderInfo)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReaderServer* pReader = (CRFIDReaderServer*)pHandle;
	return pReader->SAATFlashTotalCountQuery(pWirelessReaderInfo);
}

bool WIRELESS_RFID_API  __stdcall WIRELESS_SAAT_FlashDataQuery(void* pHandle,
															   WirelessReaderInfo* pWirelessReaderInfo ,
															   unsigned char nOpType)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReaderServer* pReader = (CRFIDReaderServer*)pHandle;
	return pReader->SAATFlashDataQuery(pWirelessReaderInfo,nOpType);
}

bool WIRELESS_RFID_API __stdcall WIRELESS_SAAT_ClearFlash(void* pHandle,
														  WirelessReaderInfo* pWirelessReaderInfo)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReaderServer* pReader = (CRFIDReaderServer*)pHandle;
	return pReader->SAATClearFlash(pWirelessReaderInfo);
}

bool WIRELESS_RFID_API  __stdcall WIRELESS_SAAT_TagOpParaSet(void* pHandle ,
															 WirelessReaderInfo* pWirelessReaderInfo,
															 unsigned char nType,
															 unsigned char *pPara,
															 unsigned char nLen)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReaderServer* pReader = (CRFIDReaderServer*)pHandle;
	return pReader->SAATTagOpParaSet(pWirelessReaderInfo,nType,pPara,nLen);
}

bool WIRELESS_RFID_API  __stdcall WIRELESS_SAAT_TagOpParaQuery(void* pHandle ,
															   WirelessReaderInfo* pWirelessReaderInfo,
															   unsigned char nType)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReaderServer* pReader = (CRFIDReaderServer*)pHandle;
	return pReader->SAATTagOpParaQuery(pWirelessReaderInfo,nType);
}

bool WIRELESS_RFID_API  __stdcall WIRELESS_SAAT_IOOperate(void* pHandle,
														  WirelessReaderInfo* pWirelessReaderInfo,
														  unsigned char nPort,unsigned char nState)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReaderServer* pReader = (CRFIDReaderServer*)pHandle;
	return pReader->SAATIOOperate(pWirelessReaderInfo,nPort,nState);
}


bool WIRELESS_RFID_API  __stdcall WIRELESS_SAAT_IO_STATE(void* pHandle,
														 WirelessReaderInfo* pWirelessReaderInfo,
														 unsigned char* pStateData,
														 unsigned char* nStateLen)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReaderServer* pReader = (CRFIDReaderServer*)pHandle;
	return pReader->SAATReadIOState(pWirelessReaderInfo,pStateData,nStateLen);

}

bool WIRELESS_RFID_API  __stdcall WIRELESS_AddTcpClient(void* pHandle,char *pIpAddr,int nTcpPort,READER_CALLBACK pCallBack)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReaderServer* pReader = (CRFIDReaderServer*)pHandle;

	return pReader->AddTcpCLient(pIpAddr,nTcpPort,pCallBack);
}

bool WIRELESS_RFID_API  __stdcall WIRELESS_AddCOMReader(void* pHandle,unsigned char nBusAddr,char *pComNum,int nBaud ,READER_CALLBACK pCallBack)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReaderServer* pReader = (CRFIDReaderServer*)pHandle;

	return pReader->AddComReader(nBusAddr,pComNum,nBaud,pCallBack);
}

bool WIRELESS_RFID_API  __stdcall WIRELESS_AddUSBReader(void* pHandle,unsigned char nBusAddr,char *pComNum,int nBaud ,READER_CALLBACK pCallBack)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReaderServer* pReader = (CRFIDReaderServer*)pHandle;

	return pReader->AddUSBReader(nBusAddr,pComNum,nBaud,pCallBack);

}

bool WIRELESS_RFID_API  __stdcall WIRELESS_AddUDPReader(void* pHandle,char *pIpAddr,int nUdpPort ,READER_CALLBACK pCallBack)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReaderServer* pReader = (CRFIDReaderServer*)pHandle;

	return pReader->AddUdpCLient(pIpAddr,nUdpPort,pCallBack);
}

bool WIRELESS_RFID_API  __stdcall WIRELESS_SAAT_Reboot(void* pHandle,
													   WirelessReaderInfo* pWirelessReaderInfo,
													   unsigned char nMode)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReaderServer* pReader = (CRFIDReaderServer*)pHandle;
	return pReader->SAATReboot(pWirelessReaderInfo,nMode);
}

bool WIRELESS_RFID_API  __stdcall WIRELESS_SAAT_SetReaderTime(void* pHandle ,
															  WirelessReaderInfo* pWirelessReaderInfo,
															  unsigned char* pPara,unsigned char nLen)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReaderServer* pReader = (CRFIDReaderServer*)pHandle;
	return pReader->SAATSetReaderTime(pWirelessReaderInfo,pPara, nLen);
}

bool WIRELESS_RFID_API  __stdcall WIRELESS_SAAT_ReaderTimeQuery(void* pHandle, 
																WirelessReaderInfo* pWirelessReaderInfo)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReaderServer* pReader = (CRFIDReaderServer*)pHandle;
	return pReader->SAATReaderTimeQuery(pWirelessReaderInfo);	
}

bool WIRELESS_RFID_API	__stdcall WIRELESS_IsNetReader(void* pHandle,WirelessReaderInfo* pWirelessReaderInfo)
{
	if (pWirelessReaderInfo->ReaderType == READER_TCP_SERVER
		|| pWirelessReaderInfo->ReaderType == READER_TCP_CLIENT
		|| pWirelessReaderInfo->ReaderType == READER_UDP)
	{
		return true;
	}
	else if ( pWirelessReaderInfo->ReaderType == READER_COM
		|| pWirelessReaderInfo->ReaderType == READER_USB)
	{
		return false;
	}

	return false;
}

bool WIRELESS_RFID_API  __stdcall WIRELESS_SAAT_Reading_IOConfig(void* pHandle,WirelessReaderInfo* pWirelessReaderInfo,unsigned char nConfigBit)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReaderServer* pReader = (CRFIDReaderServer*)pHandle;
	return pReader->SAATReadingIOConfig (pWirelessReaderInfo,nConfigBit);
}

bool WIRELESS_RFID_API  __stdcall WIRELESS_SAAT_Reading_IOQuery(void* pHandle,
																WirelessReaderInfo* pWirelessReaderInfo)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReaderServer* pReader = (CRFIDReaderServer*)pHandle;
	return pReader->SAATReadingIOQuery (pWirelessReaderInfo);
}

bool WIRELESS_RFID_API  __stdcall WIRELESS_SAAT_IOPulseWidthSet(void* pHandle,WirelessReaderInfo* pWirelessReaderInfo,unsigned char nIOPort,unsigned char nWidth)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReaderServer* pReader = (CRFIDReaderServer*)pHandle;
	return pReader->SAATIOPulseWidthSet (pWirelessReaderInfo,nIOPort,nWidth);
}	

bool WIRELESS_RFID_API  __stdcall WIRELESS_SAAT_IOPulseWidthQuery(void* pHandle,
																  WirelessReaderInfo* pWirelessReaderInfo,
																  unsigned char nIOPort)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReaderServer* pReader = (CRFIDReaderServer*)pHandle;
	return pReader->SAATIOPulseWidthQuery (pWirelessReaderInfo,nIOPort);
}

bool WIRELESS_RFID_API  __stdcall WIRELESS_SendMsg(void* pHandle,
												   WirelessReaderInfo* pWirelessReaderInfo, 
												   unsigned char pCommand, 
												   unsigned char *pSendData, 
												   int dataLength)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReaderServer* pReader = (CRFIDReaderServer*)pHandle;
	return pReader->SendMsg(pWirelessReaderInfo,pCommand,pSendData,dataLength);
}

bool WIRELESS_RFID_API  __stdcall WIRELESS_GetMsgResult(void* pHandle,
														WirelessReaderInfo* pWirelessReaderInfo,
														CRFrame &pRevFrame)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReaderServer* pReader = (CRFIDReaderServer*)pHandle;
	return pReader->GetMsgResult(pWirelessReaderInfo,pRevFrame);
}

bool WIRELESS_RFID_API  __stdcall WIRELESS_SAAT_YRFParaSet(
	void* pHandle , 
	WirelessReaderInfo* pWirelessReaderInfo,
	unsigned char nType, 
	unsigned char nParaLen)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReaderServer* pReader = (CRFIDReaderServer*)pHandle;
	return pReader->SAATYRFParaSet(
		pWirelessReaderInfo,
		nType,nParaLen);

}

bool WIRELESS_RFID_API  __stdcall WIRELESS_SAAT_YRFParaQuery(
	void* pHandle ,
	WirelessReaderInfo* pWirelessReaderInfo, 
	unsigned char nType)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReaderServer* pReader = (CRFIDReaderServer*)pHandle;
	return pReader->SAATYRFParaQuery(
		pWirelessReaderInfo,
		nType);
}

int WIRELESS_RFID_API  __stdcall WIRELESS_SAAT_YRevIDMsgDecRssiExpand(
	void *pHandle,
	WirelessReaderInfo* pWirelessReaderInfo,
	unsigned char* nTime,
	unsigned char* nTagType,
	unsigned int* pId,
	int* nRssi,
	int* nAntenna,
	int* nParam1,
	int* nParam2)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReaderServer* pReader = (CRFIDReaderServer*)pHandle;
	return pReader->SAATYRevIDMsgDecRssiExpand(pWirelessReaderInfo,nTime,nTagType, pId, nRssi, nAntenna, nParam1, nParam2);
}

bool WIRELESS_RFID_API  __stdcall WIRELESS_SAAT_YMakeTagUpLoadIDCode(
	void *pHandle, 
	WirelessReaderInfo* pWirelessReaderInfo,
	unsigned char nOpType,
	unsigned char nIDType)
{
	if( NULL == pHandle )
	{
		return false;
	}
	CRFIDReaderServer* pReader = (CRFIDReaderServer*)pHandle;
	return pReader->SAATYMakeTagUpLoadIDCode (pWirelessReaderInfo,nOpType,nIDType);
}

bool WIRELESS_RFID_API  __stdcall WIRELESS_SAAT_YReadIDCode(
	void *pHandle, 
	WirelessReaderInfo* pWirelessReaderInfo,
	unsigned char nOpType,
	unsigned char nIDType, 
	unsigned int nTagCount)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReaderServer* pReader = (CRFIDReaderServer*)pHandle;
	return pReader->SAATYReadIDCode (pWirelessReaderInfo,nOpType, nIDType, nTagCount);
}

bool WIRELESS_RFID_API  __stdcall WIRELESS_SAAT_YAntennaParmSet(
	void* pHandle , 
	WirelessReaderInfo* pWirelessReaderInfo, 
	unsigned char *pPara,
	unsigned char nLen)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReaderServer* pReader = (CRFIDReaderServer*)pHandle;
	return pReader->SAATYAntennaParmSet (
		pWirelessReaderInfo,
		pPara,nLen);

}

bool WIRELESS_RFID_API  __stdcall WIRELESS_SAAT_YAntennaParmQuery(
	void* pHandle,
	WirelessReaderInfo* pWirelessReaderInfo)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReaderServer* pReader = (CRFIDReaderServer*)pHandle;
	return pReader->SAATYAntennaParmQuery (pWirelessReaderInfo);
}

bool WIRELESS_RFID_API __stdcall WIRELESS_SAAT_YAntennaPort_EXSet(void* pHandle,
																  WirelessReaderInfo* pWirelessReaderInfo, 
																  unsigned int nPortEnable, 
																  unsigned int nPollTime,
																  unsigned int nParam)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReaderServer* pReader = (CRFIDReaderServer*)pHandle;
	return pReader->SAATYAntennaPortEXSet (pWirelessReaderInfo,nPortEnable,nPollTime,nParam);
}

bool WIRELESS_RFID_API __stdcall WIRELESS_SAAT_YAntennaPort_EXQuery(void* pHandle, 
																	WirelessReaderInfo* pWirelessReaderInfo)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReaderServer* pReader = (CRFIDReaderServer*)pHandle;
	return pReader->SAATYAntennaPortEXQuery (pWirelessReaderInfo);
}


