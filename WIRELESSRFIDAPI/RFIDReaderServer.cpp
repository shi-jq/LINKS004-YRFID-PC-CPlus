#include "StdAfx.h"
#include <assert.h>
#include "RFIDReaderServer.h"

CRFIDReaderServer::CRFIDReaderServer(void)
{
	mCTcpServerConn = NULL;
	mCallBack = NULL;
}

CRFIDReaderServer::~CRFIDReaderServer(void)
{
	Quit();
}	

bool CRFIDReaderServer::CreateReaderThread(SOCKET& sockConn,const SOCKADDR_IN&  socktAddr)
{
	char* cIpaddr = inet_ntoa(socktAddr.sin_addr);
	int nPort = socktAddr.sin_port;

	CRFIDReader* pCRFIDReader = NULL;
	WirelessReaderInfo* pWirelessReaderInfo = NULL;
	//��ȡ��д��ָ��
	pCRFIDReader=GetTcpRFIDReader(READER_TCP_SERVER,(unsigned char*)cIpaddr,nPort);
	
	if (!pCRFIDReader)
	{
		if (!mCallBack)
		{
			return false;
		}
		//���Ϊ���򴴽�
		pWirelessReaderInfo = new WirelessReaderInfo();
		pWirelessReaderInfo->ReaderType = READER_TCP_SERVER;
		std::string strIpaddr = cIpaddr;
		memcpy(pWirelessReaderInfo->bIpAddr,strIpaddr.c_str(),strIpaddr.size());
		pWirelessReaderInfo->nPort = nPort;

		pCRFIDReader = new CRFIDReader(READER_TCP_SERVER,sockConn);	
		AddReaderList(pWirelessReaderInfo,pCRFIDReader);	
		bool bRet = false;		
		try
		{
			bRet = mCallBack(this,pWirelessReaderInfo);
		}		
		catch (...)
		{
			SetErrorCode(0xff,false);
		}

		if (bRet)
		{
			//��ʼ��������
			if (!pCRFIDReader->StartRead())
			{
				assert(false);
			}
		}
		else
		{
			//����ص�����������,��ɾ�������д��
			DeleteReader(pCRFIDReader);
			pCRFIDReader = NULL;
		}
		
	}
	else
	{
		//��Ϊ�������socket
		pCRFIDReader->UpdateSocket(sockConn);
	}
	return true;
}

CRFIDReader* CRFIDReaderServer::GetTcpRFIDReader(int readerType,unsigned char* strIpadd,int nPort)
{
	CRFIDReader* pReader = NULL;
	mReadListLock.Lock();
	std::map<WirelessReaderInfo*,CRFIDReader*>::iterator ipIter = mReaderList.begin();
	for (; ipIter!=mReaderList.end(); ++ipIter)
	{
		if((strcmp((char *)&(ipIter->first->bIpAddr),(char *)strIpadd) == 0)
			&&(ipIter->first->ReaderType == readerType)
			&&(ipIter->first->nPort == nPort))

		{
			pReader = ipIter->second;
			break;
		}
	}

	mReadListLock.Unlock();
	return pReader;
}

CRFIDReader* CRFIDReaderServer::GetRFIDReader(WirelessReaderInfo* pWirelessReaderInfo)
{
	assert(pWirelessReaderInfo);
	if (pWirelessReaderInfo->ReaderType == READER_TCP_CLIENT
		||pWirelessReaderInfo->ReaderType == READER_TCP_SERVER 
		||pWirelessReaderInfo->ReaderType == READER_UDP )
	{
		return GetTcpRFIDReader(pWirelessReaderInfo->ReaderType,pWirelessReaderInfo->bIpAddr,pWirelessReaderInfo->nPort);
	}
	else
	{
		return GetComRFIDReader(pWirelessReaderInfo->ReaderType,pWirelessReaderInfo->bComNum,pWirelessReaderInfo->nBaud);
	}
	return NULL;
}

CRFIDReader* CRFIDReaderServer::GetComRFIDReader(int readerType,unsigned char* strComNum,int nBaud)
{
	CRFIDReader* pReader = NULL;
	mReadListLock.Lock();
	std::map<WirelessReaderInfo*,CRFIDReader*>::iterator pIter = mReaderList.begin();
	for (; pIter!=mReaderList.end(); ++pIter)
	{
		if((strcmp((char *)&(pIter->first->bComNum),(char *)strComNum) == 0 )
			&& pIter->first->ReaderType == readerType)
		{
			pReader = pIter->second;
			break;
		}
	}

	mReadListLock.Unlock();
	return pReader;
}

bool CRFIDReaderServer::StartListen(char *pHostName,int nsocketPort,READER_CALLBACK pCallBack)
{
	if (mCTcpServerConn)
	{
		return false;
	}
	mCTcpServerConn = new CTcpServerConn();
	mCTcpServerConn->Init(pHostName, nsocketPort,this);

	if (mCallBack == NULL)
	{
		mCallBack = pCallBack;
	}
	bool bRet =  mCTcpServerConn->StartListen();
	if (!bRet)
	{
		delete mCTcpServerConn;
		mCTcpServerConn = NULL;
	}

	return bRet;
}

bool CRFIDReaderServer::StopListen()
{
	if (!mCTcpServerConn)
	{
		return false;
	}

	bool retB = mCTcpServerConn->StopListen();
	ClearAllReader();

	delete mCTcpServerConn;
	mCTcpServerConn = NULL;

	return retB;
}

bool CRFIDReaderServer::Quit()
{
	bool retB = true;
	if (mCTcpServerConn)
	{
		retB = mCTcpServerConn->Quit();
		ClearAllReader();
		delete mCTcpServerConn;
		mCTcpServerConn = NULL;
	}

	return retB;
}

void CRFIDReaderServer::AddReaderList(WirelessReaderInfo* pWirelessReaderInfo,CRFIDReader* pCRFIDReader)
{
	mReadListLock.Lock();
	mReaderList[pWirelessReaderInfo] = pCRFIDReader;
	mReadListLock.Unlock();
}

void CRFIDReaderServer::DeleteReader(WirelessReaderInfo* pWirelessReaderInfo)
{
	mReadListLock.Lock();
	std::map<WirelessReaderInfo*,CRFIDReader*>::iterator iter = mReaderList.begin();
	for (; iter!= mReaderList.end(); ++iter)
	{
		
		if((strcmp((char *)&(iter->first->bIpAddr),(char *)pWirelessReaderInfo->bIpAddr) == 0)			
			&&(iter->first->nPort == pWirelessReaderInfo->nPort))
		{
			delete iter->second;		
			iter->second = NULL;
			delete iter->first;		
			mReaderList.erase(iter);
			break;
		}
	}
	mReadListLock.Unlock();
}

void CRFIDReaderServer::DeleteReader(CRFIDReader* pCRFIDReader)
{
	mReadListLock.Lock();
	std::map<WirelessReaderInfo*,CRFIDReader*>::iterator iter = mReaderList.begin();
	for (; iter!= mReaderList.end(); ++iter)
	{
		if (iter->second == pCRFIDReader)
		{
			delete iter->second;		
			iter->second = NULL;
			delete iter->first;			
			mReaderList.erase(iter);
			break;
		}
	}
	mReadListLock.Unlock();
}

bool CRFIDReaderServer::CloseReader(WirelessReaderInfo* pWirelessReaderInfo)
{
	if (pWirelessReaderInfo == NULL)
	{
		return false;
	}
	DeleteReader(pWirelessReaderInfo);
	return true;
}

void CRFIDReaderServer::ClearAllReader()
{
	mReadListLock.Lock();
	std::map<WirelessReaderInfo*,CRFIDReader*>::iterator iter = mReaderList.begin();
	for (; iter!= mReaderList.end(); ++iter)
	{
		delete iter->second;
		iter->second = NULL;
		delete iter->first;
	}
	mReaderList.clear();
	mReadListLock.Unlock();
}

bool CRFIDReaderServer::SAATSysInfSet(WirelessReaderInfo* pWirelessReaderInfo,
									  unsigned char nType,
									  unsigned char* pParm,
									  int nLen)
{
	ClearErrorCode();
	CRFIDReader* pCRFIDReader = GetRFIDReader(pWirelessReaderInfo);
	if(!pCRFIDReader)
	{
		return false;
	}

	if( 0 == nLen )
	{
		SetErrorCode(ERR_SIZE_ZERO);
		return false;
	}

	bool bRet = false;
	unsigned char SendCommand = COM_SYS_CFG;//ָ��
	unsigned char pSendData[API_SENDDATA_BUFF];			//��������
	*(pSendData) = nType;
	memcpy(pSendData+1,pParm,nLen);
	int nDataLen =  nLen +1;								//�������ݳ���

	do 
	{
		if( pCRFIDReader->SendMsg(SendCommand,pSendData,nDataLen) < 0)
		{	
			break;
		}

		bRet = true;

	} while (0);

	return bRet;
}

void CRFIDReaderServer::ClearErrorCode()
{

}

void CRFIDReaderServer::SetErrorCode(int nErrorCode,bool bCommandError /*= false*/)
{

}

bool CRFIDReaderServer::PowerOff(WirelessReaderInfo* pWirelessReaderInfo)
{
	ClearErrorCode();
	
	CRFIDReader* pCRFIDReader = GetRFIDReader(pWirelessReaderInfo);
	if(!pCRFIDReader)
	{
		return false;
	}

	if( !YPowerOff(pWirelessReaderInfo) ) 
	{
		return false;
	}

	pCRFIDReader->SetReadState(READ_IDLE);
	return true;
}

bool CRFIDReaderServer::SAATCarrierWaveOp(WirelessReaderInfo* pWirelessReaderInfo,
										  unsigned char nType,
										  unsigned char nPort)
{
	ClearErrorCode();

	CRFIDReader* pCRFIDReader = GetRFIDReader(pWirelessReaderInfo);
	if(!pCRFIDReader)
	{
		return false;
	}

	bool bRet = false;
	unsigned char SendCommand = COM_CARRY_OP;//ָ��
	unsigned char pSendData[API_SENDDATA_BUFF];
	*pSendData = nType;//��������
	*(pSendData+1) = nPort;
	int nDataLen = 1 + 1;//�������ݳ���
	do 
	{
		if( pCRFIDReader->SendMsg(SendCommand,pSendData,nDataLen) <0)
		{	
			break;
		}
		bRet = true;

	} while (0);


	return bRet;
}

bool CRFIDReaderServer::GetLastTime(WirelessReaderInfo* pWirelessReaderInfo,unsigned long& nTime)
{
	CRFIDReader* pCRFIDReader = GetRFIDReader(pWirelessReaderInfo);
	if(!pCRFIDReader)
	{
		return false;
	}

	if(!pCRFIDReader->CheckTimeOut())
	{
		SAATHeartSend(pWirelessReaderInfo);
	}

	nTime = pCRFIDReader->GetLastTime();

	return true;
}

bool CRFIDReaderServer::SAATSysInfQuery(WirelessReaderInfo* pWirelessReaderInfo,
										unsigned char nType)
{
	ClearErrorCode();
	CRFIDReader* pCRFIDReader = GetRFIDReader(pWirelessReaderInfo);
	if(!pCRFIDReader)
	{
		return false;
	}

	unsigned char SendCommand = COM_SYS_QUERY;
	unsigned char pSendData = nType;
	int nDataLen = 1;//������,ֻ��ָ��,Ϊ0

	bool bRet = false;
	do 
	{
		if( pCRFIDReader->SendMsg(SendCommand,&pSendData,nDataLen) <0)
		{	
			break;
		}		
		bRet = true;
	} while (0);

	return bRet;
}

bool CRFIDReaderServer::SAATRFParaSet(WirelessReaderInfo* pWirelessReaderInfo,
									  unsigned char nType, 
									  unsigned char nParaLen,
									  unsigned char* pPara)
{
	ClearErrorCode();

	CRFIDReader* pCRFIDReader = GetRFIDReader(pWirelessReaderInfo);
	if(!pCRFIDReader)
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

	unsigned char SendCommand = COM_CARRYWAVE_SET;//ָ��
	unsigned char pSendData[API_SENDDATA_BUFF];
	*pSendData = nType;//��������
	*(pSendData+1) = nParaLen;

	memcpy(pSendData+2,pPara,nParaLen);//�������Ҳ�����ݳ���
	int nDataLen = 2 + nParaLen;//�������ݳ���

	do 
	{
		if( pCRFIDReader->SendMsg(SendCommand,pSendData,nDataLen)<0 )
		{	
			break;
		}
		bRet = true;

	} while (0);


	return bRet;
}

bool CRFIDReaderServer::SAATRFParaQuery(WirelessReaderInfo* pWirelessReaderInfo,
										unsigned char nType)
{
	ClearErrorCode();

	CRFIDReader* pCRFIDReader = GetRFIDReader(pWirelessReaderInfo);
	if(!pCRFIDReader)
	{
		return false;
	}
	
	bool bRet = false;
	unsigned char SendCommand = COM_CARRYWAVE_QUERY;//ָ��
	unsigned char pSendData[API_SENDDATA_BUFF];
	*pSendData = nType;//��������
	int nDataLen = 1;//�������ݳ���

	do 
	{
		if( pCRFIDReader->SendMsg(SendCommand,pSendData,nDataLen) <0)
		{	
			break;
		}
		bRet = true;

	} while (0);

	return bRet;
}

bool CRFIDReaderServer::SAATAntennaParmQuery(WirelessReaderInfo* pWirelessReaderInfo)
{
	ClearErrorCode();

	CRFIDReader* pCRFIDReader = GetRFIDReader(pWirelessReaderInfo);
	if(!pCRFIDReader)
	{
		return false;
	}

	if( !SAATTotalAntennaParmQuery(pWirelessReaderInfo) )
	{
		return false;
	}

	return true;
}

bool CRFIDReaderServer::SAATAntennaParmSet(WirelessReaderInfo* pWirelessReaderInfo,
										   unsigned char *pPara,unsigned char nLen)
{
	ClearErrorCode();

	CRFIDReader* pCRFIDReader = GetRFIDReader(pWirelessReaderInfo);
	if(!pCRFIDReader)
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
	unsigned char SendCommand = COM_ANTENNA_SET;//ָ��
	unsigned char pSendData[API_SENDDATA_BUFF];
	memcpy(pSendData,pPara,nLen);
	int nDataLen = nLen;//�������ݳ���

	do 
	{
		if( pCRFIDReader->SendMsg(SendCommand,pSendData,nDataLen) <0)
		{	
			break;
		}

		bRet = true;

	} while (0);

	return bRet;
}

bool CRFIDReaderServer::SAATTotalAntennaParmQuery(
	WirelessReaderInfo* pWirelessReaderInfo )
{
	ClearErrorCode();

	CRFIDReader* pCRFIDReader = GetRFIDReader(pWirelessReaderInfo);
	if(!pCRFIDReader)
	{
		return false;
	}

	bool bRet = false;

	unsigned char SendCommand = COM_ANTENNA_QUERY;//ָ��
	unsigned char pSendData[API_SENDDATA_BUFF];
	int nDataLen = 0;//�������ݳ���

	do 
	{
		if( pCRFIDReader->SendMsg(SendCommand,pSendData,nDataLen) <0)
		{	
			break;
		}
		bRet = true;
	} while (0);

	return bRet;
}

bool CRFIDReaderServer::SAATParmOp(WirelessReaderInfo* pWirelessReaderInfo, 
								   unsigned char nType, 
								   unsigned char nStartAddrr,
								   unsigned char nLen, 
								   unsigned char *pData,
								   unsigned char *pDataLen,
								   int* nMsgID)
{
	ClearErrorCode();

	CRFIDReader* pCRFIDReader = GetRFIDReader(pWirelessReaderInfo);
	if(!pCRFIDReader)
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

	unsigned char SendCommand = COM_PARA_OP;//ָ��
	unsigned char pSendData[API_SENDDATA_BUFF];

	*pSendData = nType;		//��������
	*(pSendData+1) = nStartAddrr;//��ʼ��ַ
	*(pSendData+2) = nLen;	//����/��������

	int nTempLen = 0;
	switch (nType)
	{
	case 0x00:		//�ָ�ϵͳ������Ϊ��������
		break;
	case 0x01:		//����ϵͳ������
		memcpy(pSendData+3,pData,nLen);
		nTempLen = nLen;
		break;
	case 0x02:		//����ϵͳ������
		break;
	}

	int nDataLen = 3 + nTempLen;//�������ݳ���
	do 
	{
		
		int  msgID = pCRFIDReader->SendMsg(SendCommand,pSendData,nDataLen);
		if (nMsgID != NULL)
		{
			*nMsgID = msgID;
		}

		if( msgID <0)
		{	
			break;
		}
		
		bRet = true;		
	} while (0);

	return bRet;
}

bool CRFIDReaderServer::SAATTagOpParaSet(WirelessReaderInfo* pWirelessReaderInfo,
										 unsigned char nType, 
										 unsigned char *pPara,
										 unsigned char nLen)
{
	
	ClearErrorCode();

	CRFIDReader* pCRFIDReader = GetRFIDReader(pWirelessReaderInfo);
	if(!pCRFIDReader)
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
	unsigned char SendCommand = COM_TAG_SET;//ָ��
	unsigned char pSendData[API_SENDDATA_BUFF];
	*pSendData = nType;//��������
	memcpy(pSendData+1,pPara,nLen);
	int nDataLen = nLen + 1;//�������ݳ���
	do 
	{
		if( pCRFIDReader->SendMsg(SendCommand,pSendData,nDataLen) <0)
		{	
			break;
		}

		bRet = true;

	} while (0);


	return bRet;
}

bool CRFIDReaderServer::SAATClearFlash(WirelessReaderInfo* pWirelessReaderInfo)
{
	ClearErrorCode();

	CRFIDReader* pCRFIDReader = GetRFIDReader(pWirelessReaderInfo);
	if(!pCRFIDReader)
	{
		return false;
	}

	unsigned char SendCommand = READER_FLASHCLEAR;//ָ��
	unsigned char pSendData[API_SENDDATA_BUFF];
	int nDataLen = 0;//�������ݳ���

	bool bRet = false;
	do 
	{
		if( pCRFIDReader->SendMsg(SendCommand,pSendData,nDataLen)<0 )
		{	
			break;
		}

		bRet = true;

	} while (0);

	return bRet;
}

bool CRFIDReaderServer::SAATFlashDataQuery(WirelessReaderInfo* pWirelessReaderInfo,
										   unsigned char nOpType)
{
	ClearErrorCode();

	CRFIDReader* pCRFIDReader = GetRFIDReader(pWirelessReaderInfo);
	if(!pCRFIDReader)
	{
		return false;
	}

	unsigned char SendCommand = READER_FLASHDATA_QUERY;//ָ��
	unsigned char pSendData[API_SENDDATA_BUFF];
	*pSendData = nOpType;
	int nDataLen = 1;//�������ݳ���

	bool bRet = false;
	do 
	{
		if( pCRFIDReader->SendMsg(SendCommand,pSendData,nDataLen) <0)
		{	
			break;
		}

		bRet = true;

	} while (0);

	return bRet;
}

bool CRFIDReaderServer::SAATFlashTotalCountQuery(WirelessReaderInfo* pWirelessReaderInfo)
{
	ClearErrorCode();

	CRFIDReader* pCRFIDReader = GetRFIDReader(pWirelessReaderInfo);
	if(!pCRFIDReader)
	{
		return false;
	}

	unsigned char SendCommand = READER_FLASHDATACOUNT_QUERY;//ָ��
	unsigned char pSendData[API_SENDDATA_BUFF];
	int nDataLen = 0;//�������ݳ���
	bool bRet = false;
	do 
	{
		if( pCRFIDReader->SendMsg(SendCommand,pSendData,nDataLen) <0)
		{	
			break;
		}
		bRet = true;

	} while (0);

	return bRet;
}

bool CRFIDReaderServer::SAATTagOpParaQuery(WirelessReaderInfo* pWirelessReaderInfo,
										   unsigned char nType)
{

	ClearErrorCode();

	CRFIDReader* pCRFIDReader = GetRFIDReader(pWirelessReaderInfo);
	if(!pCRFIDReader)
	{
		return false;
	}

	bool bRet = false;

	unsigned char SendCommand = COM_TAG_QUERY;//ָ��
	unsigned char pSendData[API_SENDDATA_BUFF];
	*pSendData = nType;//��������
	int nDataLen = 1;//�������ݳ���
	do 
	{
		if( pCRFIDReader->SendMsg(SendCommand,pSendData,nDataLen)<0 )
		{	
			break;
		}

		bRet = true;

	} while (0);

	return bRet;
}

bool CRFIDReaderServer::SAATIOOperate(WirelessReaderInfo* pWirelessReaderInfo,
									  unsigned char nPort,unsigned char nState)
{
	ClearErrorCode();

	CRFIDReader* pCRFIDReader = GetRFIDReader(pWirelessReaderInfo);
	if(!pCRFIDReader)
	{
		return false;
	}

	unsigned char SendCommand = COM_IO_OP;//ָ��
	unsigned char pSendData[API_SENDDATA_BUFF];
	*pSendData = nPort;//��������
	*(pSendData+1) = nState;
	int nDataLen = 1 + 1;//�������ݳ���


	bool bRet = false;
	do 
	{
		if( pCRFIDReader->SendMsg(SendCommand,pSendData,nDataLen)<0 )
		{	
			break;
		}
		bRet = true;

	} while (0);


	return bRet;
}

bool CRFIDReaderServer::SAATReadIOState(WirelessReaderInfo* pWirelessReaderInfo,
										unsigned char* pStateData, 
										unsigned char* nStateLen)
{
	ClearErrorCode();

	CRFIDReader* pCRFIDReader = GetRFIDReader(pWirelessReaderInfo);
	if(!pCRFIDReader)
	{
		return false;
	}

	if( NULL == pStateData || NULL == nStateLen)
	{
		SetErrorCode(ERR_POINTER_NULL);
		return false;
	}

	if( 10 > *nStateLen )
	{
		SetErrorCode(ERR_SIZE_ZERO);
		return false;
	}

	bool bRet = false;
	CRFrame revFrame;

	if ( pCRFIDReader->GetIOState(revFrame))
	{
		if( revFrame.bData[0] != 0 ) //�жϷ���ֵ 
		{
			SetErrorCode(revFrame.bData[0],true);
			return bRet;
		}
		
		memcpy(pStateData,revFrame.bData+1,10);
		*nStateLen = 10;
			
		bRet = true;
	}
	return bRet;
}

bool CRFIDReaderServer::AddTcpCLient(char *pIpAddr,int nPort,READER_CALLBACK pCallBack)
{
	CRFIDReader* pCRFIDReader = NULL;
	WirelessReaderInfo* pWirelessReaderInfo = NULL;
	//��ȡ��д��ָ��
	pCRFIDReader=GetTcpRFIDReader(READER_TCP_CLIENT,(unsigned char*)pIpAddr,nPort);

	if (!pCRFIDReader)
	{
		if (!pCallBack)
		{
			return false;
		}
		//���Ϊ���򴴽�
		pWirelessReaderInfo = new WirelessReaderInfo();
		pWirelessReaderInfo->ReaderType = READER_TCP_CLIENT;
		std::string strIpaddr = pIpAddr;
		memcpy(pWirelessReaderInfo->bIpAddr,strIpaddr.c_str(),sizeof(strIpaddr));
		pWirelessReaderInfo->nPort = nPort;

		pCRFIDReader = new CRFIDReader(READER_TCP_CLIENT,pIpAddr,nPort);	
		AddReaderList(pWirelessReaderInfo,pCRFIDReader);	

		//��ʼ��������
		if (!pCRFIDReader->StartRead())
		{
			//assert(false);
			DeleteReader(pCRFIDReader);
			return false;
		}

		if (!pCallBack(this,pWirelessReaderInfo))
		{
			//����ص�����������,��ɾ�������д��
			DeleteReader(pCRFIDReader);
			pCRFIDReader = NULL;
		}		
	}
	else
	{
		return false;
	}
	return true;
}


bool CRFIDReaderServer::AddComReader(
									 unsigned char nBusAddr,char *pComNum,
									 int nBaud,READER_CALLBACK pCallBack)
{
	CRFIDReader* pCRFIDReader = NULL;
	WirelessReaderInfo* pWirelessReaderInfo = NULL;
	//��ȡ��д��ָ��
	pCRFIDReader=GetComRFIDReader(READER_COM,(unsigned char*)pComNum,nBaud);

	if (!pCRFIDReader)
	{
		if (!pCallBack)
		{
			return false;
		}
		//���Ϊ���򴴽�
		pWirelessReaderInfo = new WirelessReaderInfo();
		pWirelessReaderInfo->ReaderType = READER_COM;
		std::string strComNum = pComNum;
		memcpy(pWirelessReaderInfo->bComNum,strComNum.c_str(),sizeof(strComNum));
		pWirelessReaderInfo->nBaud = nBaud;

		pCRFIDReader = new CRFIDReader(READER_COM,nBusAddr,pComNum,nBaud);	
		AddReaderList(pWirelessReaderInfo,pCRFIDReader);	

		//��ʼ��������
		if (!pCRFIDReader->StartRead())
		{
			//assert(false);
			DeleteReader(pCRFIDReader);
			return false;
		}

		if (!pCallBack(this,pWirelessReaderInfo))
		{
			//����ص�����������,��ɾ�������д��
			DeleteReader(pCRFIDReader);
			pCRFIDReader = NULL;
		}		
	}
	else
	{
		return false;
	}
	return true;
}


bool CRFIDReaderServer::SAATHeartSend(WirelessReaderInfo* pWirelessReaderInfo)
{
	ClearErrorCode();

	CRFIDReader* pCRFIDReader = GetRFIDReader(pWirelessReaderInfo);
	if(!pCRFIDReader)
	{
		return false;
	}

	unsigned char SendCommand = COM_SEND_HEART;//ָ��
	unsigned char pSendData[1];
	int nDataLen =  0;//�������ݳ���

	bool bRet = false;
	do 
	{
		if(pCRFIDReader->SendMsg(SendCommand,pSendData,nDataLen) <0)
		{	
			break;
		}

		bRet = true;

	} while (0);
	return bRet;
}

bool CRFIDReaderServer::AddUSBReader(unsigned char nBusAddr,char *pComNum,int nBaud,READER_CALLBACK pCallBack)
{
	CRFIDReader* pCRFIDReader = NULL;
	WirelessReaderInfo* pWirelessReaderInfo = NULL;
	//��ȡ��д��ָ��
	pCRFIDReader=GetComRFIDReader(READER_USB,(unsigned char*)pComNum,nBaud);

	if (!pCRFIDReader)
	{
		if (!pCallBack)
		{
			return false;
		}
		//���Ϊ���򴴽�
		pWirelessReaderInfo = new WirelessReaderInfo();
		pWirelessReaderInfo->ReaderType = READER_USB;
		std::string strComNum = pComNum;
		memcpy(pWirelessReaderInfo->bComNum,strComNum.c_str(),sizeof(strComNum));
		pWirelessReaderInfo->nBaud = nBaud;

		pCRFIDReader = new CRFIDReader(READER_USB,nBusAddr,pComNum,nBaud);	
		AddReaderList(pWirelessReaderInfo,pCRFIDReader);	

		//��ʼ��������
		if (!pCRFIDReader->StartRead())
		{
			//assert(false);
			DeleteReader(pCRFIDReader);
			pCRFIDReader = NULL;
			return false;
		}

		if(!SAATHeartSend(pWirelessReaderInfo))
		{
			DeleteReader(pCRFIDReader);
			pCRFIDReader = NULL;
			return false;
		}

		if (!pCallBack(this,pWirelessReaderInfo))
		{
			//����ص�����������,��ɾ�������д��
			DeleteReader(pCRFIDReader);
			pCRFIDReader = NULL;
		}		
	}
	else
	{
		return false;
	}
	return true;
}

bool CRFIDReaderServer::AddUdpCLient(char *pIpAddr,int nPort,READER_CALLBACK pCallBack)
{
	CRFIDReader* pCRFIDReader = NULL;
	WirelessReaderInfo* pWirelessReaderInfo = NULL;
	//��ȡ��д��ָ��
	pCRFIDReader=GetTcpRFIDReader(READER_UDP,(unsigned char*)pIpAddr,nPort);

	if (!pCRFIDReader)
	{
		if (!pCallBack)
		{
			return false;
		}
		//���Ϊ���򴴽�
		pWirelessReaderInfo = new WirelessReaderInfo();
		pWirelessReaderInfo->ReaderType = READER_UDP;
		std::string strIpaddr = pIpAddr;
		memcpy(pWirelessReaderInfo->bIpAddr,strIpaddr.c_str(),sizeof(strIpaddr));
		pWirelessReaderInfo->nPort = nPort;

		pCRFIDReader = new CRFIDReader(READER_UDP,pIpAddr,nPort);	
		AddReaderList(pWirelessReaderInfo,pCRFIDReader);	

		//��ʼ��������
		if (!pCRFIDReader->StartRead())
		{
			//assert(false);
			DeleteReader(pCRFIDReader);
			return false;
		}

		if (!pCallBack(this,pWirelessReaderInfo))
		{
			//����ص�����������,��ɾ�������д��
			DeleteReader(pCRFIDReader);
			pCRFIDReader = NULL;
		}		
	}
	else
	{
		return false;
	}
	return true;
}

bool CRFIDReaderServer::SendMsg(WirelessReaderInfo* pWirelessReaderInfo, unsigned char pCommand, unsigned char *pSendData, int dataLength)
{
	ClearErrorCode();

	CRFIDReader* pCRFIDReader = GetRFIDReader(pWirelessReaderInfo);
	if(!pCRFIDReader)
	{
		return false;
	}

	return (pCRFIDReader->SendMsg(pCommand,pSendData,dataLength) >= 0);
}

bool CRFIDReaderServer::GetMsgResult(WirelessReaderInfo* pWirelessReaderInfo, CRFrame &pRevFrame)
{
	CRFIDReader* pCRFIDReader = GetRFIDReader(pWirelessReaderInfo);
	if(!pCRFIDReader)
	{
		return false;
	}

	return pCRFIDReader->GetRecvMsg(pRevFrame);
}


bool CRFIDReaderServer::SAATReboot(WirelessReaderInfo* pWirelessReaderInfo,unsigned char nMode)
{
	ClearErrorCode();

	CRFIDReader* pCRFIDReader = GetRFIDReader(pWirelessReaderInfo);
	if(!pCRFIDReader)
	{
		return false;
	}

	bool bRet = false;
	unsigned char SendCommand = COM_READER_REBOOT;//ָ��
	unsigned char pSendData[API_SENDDATA_BUFF];
	*pSendData = nMode;//��������
	int nDataLen = 1;//�������ݳ���

	do 
	{
		if( pCRFIDReader->SendMsg(SendCommand,pSendData,nDataLen) <0)
		{	
			break;
		}

		bRet = true;

	} while (0);

	return bRet;
}

bool CRFIDReaderServer::SAATReaderTimeQuery(WirelessReaderInfo* pWirelessReaderInfo)
{
	ClearErrorCode();

	CRFIDReader* pCRFIDReader = GetRFIDReader(pWirelessReaderInfo);
	if(!pCRFIDReader)
	{
		return false;
	}

	unsigned char SendCommand = READER_TIME_QUERY;//ָ��
	unsigned char pSendData[API_SENDDATA_BUFF];
	int nDataLen = 0;//�������ݳ���

	bool bRet = false;
	do 
	{
		if( pCRFIDReader->SendMsg(SendCommand,pSendData,nDataLen) <0)
		{	
			break;
		}	
		bRet = true;

	} while (0);

	return bRet;
}

bool CRFIDReaderServer::SAATSetReaderTime(WirelessReaderInfo* pWirelessReaderInfo,
										  unsigned char *pPara, 
										  unsigned char nLen)
{
	ClearErrorCode();

	CRFIDReader* pCRFIDReader = GetRFIDReader(pWirelessReaderInfo);
	if(!pCRFIDReader)
	{
		return false;
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

	unsigned char SendCommand = READER_TIME_SET;//ָ��
	unsigned char pSendData[API_SENDDATA_BUFF];
	memcpy(pSendData,pPara,nLen);
	int nDataLen =  nLen;//�������ݳ���

	bool bRet = false;
	do 
	{
		if( pCRFIDReader->SendMsg(SendCommand,pSendData,nDataLen) <0)
		{	
			break;
		}
		
		bRet = true;

	} while (0);

	return bRet;
}

bool CRFIDReaderServer::SAATReadingIOConfig(WirelessReaderInfo* pWirelessReaderInfo,
											unsigned char nConfigBit)
{
	ClearErrorCode();

	CRFIDReader* pCRFIDReader = GetRFIDReader(pWirelessReaderInfo);
	if(!pCRFIDReader)
	{
		return false;
	}

	bool bRet = false;
	unsigned char SendCommand = READING_IO_CONFIG;//ָ�� 23
	unsigned char pSendData[API_SENDDATA_BUFF];
	*pSendData = nConfigBit;//��������
	int nDataLen = 1;//�������ݳ���

	do 
	{
		if( pCRFIDReader->SendMsg(SendCommand,
			pSendData,nDataLen)<0 )
		{	
			break;
		}

		bRet = true;

	} while (0);

	return bRet;
}

bool CRFIDReaderServer::SAATReadingIOQuery(WirelessReaderInfo* pWirelessReaderInfo)
{
	ClearErrorCode();

	CRFIDReader* pCRFIDReader = GetRFIDReader(pWirelessReaderInfo);
	if(!pCRFIDReader)
	{
		return false;
	}

	bool bRet = false;
	unsigned char SendCommand = READING_IO_QUERY;//ָ��
	unsigned char pSendData[API_SENDDATA_BUFF];
	int nDataLen = 0;//�������ݳ���

	do 
	{
		if( pCRFIDReader->SendMsg(SendCommand,pSendData,nDataLen) <0)
		{	
			break;
		}

		bRet = true;

	} while (0);


	return bRet;
}

bool CRFIDReaderServer::SAATIOPulseWidthSet(WirelessReaderInfo* pWirelessReaderInfo,
											unsigned char nIOPort,unsigned char nWidth)
{
	ClearErrorCode();

	CRFIDReader* pCRFIDReader = GetRFIDReader(pWirelessReaderInfo);
	if(!pCRFIDReader)
	{
		return false;
	}

	bool bRet = false;
	unsigned char SendCommand = COM_IO_PULSESET;//ָ��  25
	unsigned char pSendData[API_SENDDATA_BUFF];
	pSendData[0] = nIOPort;
	pSendData[1] = nWidth;
	int nDataLen = 2;//�������ݳ���

	do 
	{
		if( pCRFIDReader->SendMsg(SendCommand,pSendData,nDataLen) <0)
		{	
			break;
		}

		bRet = true;

	} while (0);
	return bRet;
}

bool CRFIDReaderServer::SAATIOPulseWidthQuery(WirelessReaderInfo* pWirelessReaderInfo,
											  unsigned char nIOPort)
{
	ClearErrorCode();

	CRFIDReader* pCRFIDReader = GetRFIDReader(pWirelessReaderInfo);
	if(!pCRFIDReader)
	{
		return false;
	}

	bool bRet = false;
	unsigned char SendCommand = COM_IO_PULSEQUERY;//ָ��  26
	unsigned char pSendData[API_SENDDATA_BUFF];
	pSendData[0] = nIOPort;

	int nDataLen = 1;//�������ݳ���

	do 
	{
		if( pCRFIDReader->SendMsg(SendCommand,pSendData,nDataLen) <0)
		{	
			break;
		}

		bRet = true;

	} while (0);


	return bRet;
}

bool CRFIDReaderServer::SAATYMakeTagUpLoadIDCode(WirelessReaderInfo* pWirelessReaderInfo, unsigned char nOpType, unsigned char nIDType)
{
	ClearErrorCode();

	CRFIDReader* pCRFIDReader = GetRFIDReader(pWirelessReaderInfo);
	if(!pCRFIDReader)
	{
		return false;
	}


	unsigned char pSendData[API_SENDDATA_BUFF];
	unsigned char ucCommand = COM_YMAKE_TAGUPLOAD;

	pSendData[0] = nOpType;
	pSendData[1] = nIDType;

	if ( !pCRFIDReader->SendMsg( ucCommand, pSendData, 2))
	{
		return false;
	}

	return true;
}

bool CRFIDReaderServer::SAATYReadIDCode(WirelessReaderInfo* pWirelessReaderInfo, unsigned char nOpType, unsigned char nIDType, unsigned int nTagCount)
{
	ClearErrorCode();

	CRFIDReader* pCRFIDReader = GetRFIDReader(pWirelessReaderInfo);
	if(!pCRFIDReader)
	{
		return false;
	}

	unsigned char pSendData[API_SENDDATA_BUFF];
	unsigned char ucCommand = COM_YSEND_READID;

	pSendData[0] = nOpType;
	pSendData[1] = nTagCount;
	pSendData[2] = nIDType;

	if ( !pCRFIDReader->SendMsg( ucCommand, pSendData, 3))
	{
		return false;
	}

	return true;
}

byte CRFIDReaderServer::C10Convert16(byte a)
{
	char szTemp[10];
	ZeroMemory(szTemp,10);
	itoa(a,szTemp,10);
	szTemp[2] =0x00;

	byte uutt[4] ={0x00,0x00,0x00,0x00};
	sscanf_s(szTemp,"%02X",uutt);
	byte btTTT = uutt[0];
	return btTTT;
}

int CRFIDReaderServer::SAATYRevIDMsgDecRssiExpand(
	WirelessReaderInfo* pWirelessReaderInfo,
	unsigned char* nTime,
	unsigned char* nTagType,
	unsigned int* pId,
	int* nRssi,
	int* nAntenna,
	int* nParam1,
	int* nParam2)
{
	ClearErrorCode();

	CRFIDReader* pCRFIDReader = GetRFIDReader(pWirelessReaderInfo);
	if(!pCRFIDReader)
	{
		return 0;
	}

	if( NULL == nTagType ||
		NULL == pId ||
		NULL == nRssi ||
		NULL == nParam1 ||
		NULL == nParam2 ||
		NULL == nAntenna ||
		NULL == nTime)
	{
		SetErrorCode(ERR_POINTER_NULL);
		return 0;
	}
	//55 03 01 1c  62 00 00 00 00 00 03 ed  8d e3   
	//49 15 03 05 02 01 70   c0 f0 50 20  02 01 01 5d  02 01 01 04 4b
	CRFrame revFrame;
	if ( pCRFIDReader->GetCard(revFrame))
	{
		if( revFrame.bCommand == COM_YSTOP )
		{
			return -1;
		}
		if( revFrame.bCommand == COM_SEND_HEART ) //������
		{
			return 2;
		}
		if(revFrame.bData[0] != 0)
		{
			SetErrorCode(revFrame.bData[0], true);
			return 0;
		}
		int timeLen = 7;

		if (revFrame.bLength <= timeLen+2)
		{
			return 2;
		}
		
		*nTagType = (uint8_t)(revFrame.bData[1]);
		*nRssi = 0xFFFFFF00;
		*nRssi += (revFrame.bData[2]);
		*pId = (revFrame.bData[3] << 24)
			+ (revFrame.bData[4] << 16)
			+ (revFrame.bData[5] << 8)
			+ (revFrame.bData[6]);

		*nParam1 = (revFrame.bData[7]);

		if (revFrame.bLength > 9 + timeLen)
		{
			*nAntenna = (revFrame.bData[8]);
		}
		else
		{
			*nAntenna = 1;
		}

		if (revFrame.bLength >= (13 + timeLen))
		{
			*nParam2 = (revFrame.bData[9] << 24)
				+ (revFrame.bData[10] << 16)
				+ (revFrame.bData[11] << 8)
				+ (revFrame.bData[12]);
		}
		if (revFrame.bLength >= 10 + timeLen)
		{
			nTime[6] = revFrame.bData[15];
			nTime[5] = revFrame.bData[14];
			nTime[4] = revFrame.bData[13];
			nTime[3] = revFrame.bData[12];
			nTime[2] = revFrame.bData[11];
			nTime[1] = revFrame.bData[10];
			nTime[0] = revFrame.bData[9];
		}
		else
		{
			*nParam2 = 0;
		}


		return 1;

		//int nRealDataLen = revFrame.bLength - 2;
		//if( nRealDataLen < (8) )
		//{
		//	SetErrorCode(ERR_DATALEN_LOZERO);
		//	return 0;
		//}	

		//int nStart = 0;
		//if (pWirelessReaderInfo->ReaderType == READER_TCP_SERVER)
		//{
		//	//nStart = 7;				
		//}
		//
		//if(nRealDataLen >= (19+nStart))
		//{
		//	if (pWirelessReaderInfo->ReaderType == READER_TCP_SERVER)
		//	{
		//		memcpy(nTime,revFrame.bData+9,7);			
		//	}
		//	else
		//	{
		//		SYSTEMTIME sysTime;
		//		GetLocalTime(&sysTime);
		//		
		//		nTime[6] =C10Convert16(sysTime.wYear%100);
		//		nTime[5] =C10Convert16(sysTime.wMonth-1);
		//		nTime[4] =C10Convert16(sysTime.wDay);
		//		nTime[3] =C10Convert16(sysTime.wDayOfWeek);
		//		nTime[2] =C10Convert16(sysTime.wHour);
		//		nTime[1] =C10Convert16(sysTime.wMinute);
		//		nTime[0] =C10Convert16(sysTime.wSecond);
		//		//����Ϊ-1,����������ʱ�����һ��Сʱ				
		//	}

		//	*pId = (revFrame.bData[5] << 24) + 
		//		(revFrame.bData[6] << 16) + 
		//		(revFrame.bData[7] << 8) + 
		//		revFrame.bData[8];
		//	*pBit = revFrame.bData[9+nStart];
		//	*nTagType = revFrame.bData[10+nStart];//��ǩ��־ 0xF0��ʾ��ͨ��ǩ��0xF1��ʾ�¶ȱ�ǩ��0xF2��ʾ������ǩ
		//	*nParam1 = revFrame.bData[11+nStart];//�¶ȸ�λ or ������ַ
		//	*nParam2 = revFrame.bData[12+nStart];//�¶ȵ�λ or ��ǿǿ��	
		//	if((revFrame.bData[10+nStart] & 0xf0) == 0xf0 
		//		&& revFrame.bData[13+nStart] > 0 
		//		&&  revFrame.bData[14+nStart] == 0x01
		//		&&  revFrame.bData[15+nStart] > 0)
		//	{
		//		*nParam3 = revFrame.bData[16+nStart];
		//		*nAntenna = revFrame.bData[19+nStart];
		//	}
		//	else
		//	{
		//		*nParam3 = 0;
		//		*nAntenna = 0;
		//	}		
		//}	
		//else
		//{
		//	SYSTEMTIME sysTime;
		//	GetLocalTime(&sysTime);

		//	nTime[6] =C10Convert16(sysTime.wYear%100);
		//	nTime[5] =C10Convert16(sysTime.wMonth-1);
		//	nTime[4] =C10Convert16(sysTime.wDay);
		//	nTime[3] =C10Convert16(sysTime.wDayOfWeek);
		//	nTime[2] =C10Convert16(sysTime.wHour);
		//	nTime[1] =C10Convert16(sysTime.wMinute);
		//	nTime[0] =C10Convert16(sysTime.wSecond);

		//	*pId = (revFrame.bData[1] << 24) + 
		//		(revFrame.bData[2] << 16) + 
		//		(revFrame.bData[3] << 8) + 
		//		revFrame.bData[4];
		//	*pBit = revFrame.bData[9];
		//	*nTagType = 0x01;//��ǩ��־ 0x01��ʾ�¶ȱ�ǩ
		//	*nParam1 = (revFrame.bData[5]<<8) + revFrame.bData[6];//���
		//	*nParam2 = (revFrame.bData[7]<<8) + revFrame.bData[8];//�¶�
		//	*nParam3 = 0;
		//	*nAntenna = 0;
		//}	
		//	
		//return 1;		
	}

	return 0;
}


bool CRFIDReaderServer::SAATYAntennaPortEXSet(WirelessReaderInfo* pWirelessReaderInfo,unsigned int nPortEnable,unsigned int nPollTime,unsigned int nParam)
{
	ClearErrorCode();

	CRFIDReader* pCRFIDReader = GetRFIDReader(pWirelessReaderInfo);
	if(!pCRFIDReader)
	{
		return false;
	}

	bool bRet = false;

	unsigned char SendCommand = COM_ANTENNA_SET_EX;//ָ��
	unsigned char pSendData[12];

	pSendData[0] = (BYTE)((0xff000000&nPortEnable) >> 24 );
	pSendData[1] = (BYTE)((0xff0000&nPortEnable) >> 16 );
	pSendData[2] = (BYTE)((0xff00&nPortEnable) >> 8 );
	pSendData[3] = (BYTE)(0xff&nPortEnable);

	pSendData[4] = (BYTE)((0xff000000&nPollTime) >> 24 );
	pSendData[5] = (BYTE)((0xff0000&nPollTime) >> 16 );
	pSendData[6] = (BYTE)((0xff00&nPollTime) >> 8 );
	pSendData[7] = (BYTE)(0xff&nPollTime);

	pSendData[8] = (BYTE)((0xff000000&nParam) >> 24 );
	pSendData[9] = (BYTE)((0xff0000&nParam) >> 16 );
	pSendData[10] = (BYTE)((0xff00&nParam) >> 8 );
	pSendData[11] = (BYTE)(0xff&nParam);

	int nDataLen = 12;//�������ݳ���
	do 
	{
		if( !pCRFIDReader->SendMsg(SendCommand,pSendData,nDataLen) )
		{	
			break;
		}
		
		bRet = true;
		break;

	} while (0);

	return bRet;
}

bool CRFIDReaderServer::SAATYAntennaPortEXQuery(WirelessReaderInfo* pWirelessReaderInfo)
{
	ClearErrorCode();

	CRFIDReader* pCRFIDReader = GetRFIDReader(pWirelessReaderInfo);
	if(!pCRFIDReader)
	{
		return false;
	}
	unsigned char SendCommand = COM_ANTENNA_QUERY_EX;//ָ��
	unsigned char pSendData[1];
	int nDataLen = 0 ;

	bool bRet = false;
	do 
	{
		if( !pCRFIDReader->SendMsg(SendCommand,pSendData,nDataLen) )
		{	
			break;
		}		

		bRet = true;

	} while (0);

	return bRet;
}

bool CRFIDReaderServer::SAATYAntennaParmQuery(WirelessReaderInfo* pWirelessReaderInfo)
{
	ClearErrorCode();

	CRFIDReader* pCRFIDReader = GetRFIDReader(pWirelessReaderInfo);
	if(!pCRFIDReader)
	{
		return false;
	}

	if( !SAATTotalAntennaParmQuery(pWirelessReaderInfo) )
		return false;

	return true;
}

bool CRFIDReaderServer::SAATYAntennaParmSet(WirelessReaderInfo* pWirelessReaderInfo, 
											unsigned char *pPara,
											unsigned char nLen)
{
	ClearErrorCode();

	CRFIDReader* pCRFIDReader = GetRFIDReader(pWirelessReaderInfo);
	if(!pCRFIDReader)
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

	unsigned char SendCommand = COM_ANTENNA_SET;//ָ��
	unsigned char pSendData[API_SENDDATA_BUFF];
	memcpy(pSendData, pPara, nLen);
	int nDataLen = nLen;//�������ݳ���

	if( !pCRFIDReader->SendMsg(SendCommand,pSendData,nDataLen) )
		return false;	

	return true;
}

bool CRFIDReaderServer::SAATYRFParaSet(
									  WirelessReaderInfo* pWirelessReaderInfo, 
									  unsigned char nType, 
									  unsigned char nPara)
{
	ClearErrorCode();

	CRFIDReader* pCRFIDReader = GetRFIDReader(pWirelessReaderInfo);
	if(!pCRFIDReader)
	{
		return false;
	}

	if ( nPara<0x00 || nPara > 0x17 )
	{
		SetErrorCode(ERR_SIZE_ZERO);
		return false;
	}

	unsigned char SendCommand = COM_CARRYWAVE_SET;//ָ��
	unsigned char pSendData[3];
	*pSendData = nType;//��������
	*(pSendData+1) = 0x01;
	*(pSendData+2) = nPara;
	int nDataLen = 3;//�������ݳ���

	if( !pCRFIDReader->SendMsg(SendCommand,pSendData,nDataLen) )
		return false;

	return true;
}

bool CRFIDReaderServer::SAATYRFParaQuery(WirelessReaderInfo* pWirelessReaderInfo, unsigned char nType)
{
	ClearErrorCode();

	CRFIDReader* pCRFIDReader = GetRFIDReader(pWirelessReaderInfo);
	if(!pCRFIDReader)
	{
		return false;
	}

	unsigned char SendCommand = COM_CARRYWAVE_QUERY;//ָ��
	unsigned char pSendData[4];
	*pSendData = nType;//��������
	memset(pSendData+1,0,3);
	int nDataLen = 4;//�������ݳ���

	if( !pCRFIDReader->SendMsg(SendCommand,pSendData,nDataLen) )
		return false;
	
	return true;
}

bool CRFIDReaderServer::YPowerOff(WirelessReaderInfo* pWirelessReaderInfo)
{
	ClearErrorCode();

	CRFIDReader* pCRFIDReader = GetRFIDReader(pWirelessReaderInfo);
	if(!pCRFIDReader)
	{
		return false;
	}

	unsigned char SendCommand = COM_YSTOP;//ָ��
	unsigned char pSendData[1];
	int nDataLen = 0;//�������ݳ���

	bool bRet = false;
	do 
	{
		if( !pCRFIDReader->SendMsg(SendCommand,pSendData,nDataLen) )
		{	
			break;
		}
	
		bRet = true;

	} while (0);

	return bRet;
}

