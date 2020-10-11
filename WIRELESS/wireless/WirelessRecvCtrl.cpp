#include "WirelessRecvCtrl.h"
#include "wirelessrecv.h"
#include <QDateTime>
#include <assert.h>
#include "appconfig.h"
#include "LanguageSrc.h"

WirelessRecvCtrl::WirelessRecvCtrl(void)
{
	mIsEnableAnalysisTime = false;
	m_hCom = INVALID_HANDLE_VALUE;
	m_hCom = NULL;
}

WirelessRecvCtrl::~WirelessRecvCtrl(void)
{
	ClearAllRead();
	m_hCom = INVALID_HANDLE_VALUE;
	m_hCom = NULL;
}

void WirelessRecvCtrl::SetpDlg(WirelessRecvDlg* pWirelessRecvDlg)
{
	mWirelessRecvDlg = pWirelessRecvDlg;

}

void WirelessRecvCtrl::recvReaderInfo(WirelessReaderInfo* pReaderInfo)
{
	if(mWirelessRecvDlg)
	{
		mWirelessRecvDlg->RecvreaderInfo(pReaderInfo);
	}
}

void WirelessRecvCtrl::StartRead(WirelessReaderInfo* pReaderInfo,int nReadType)
{
	WirelessRecvProcThread* pThread = NULL;
	pThread = GetReadThread(pReaderInfo);
	if (pThread)
	{
		pThread->startRead(nReadType);
	}
}

WirelessRecvProcThread* WirelessRecvCtrl::GetReadThread(WirelessReaderInfo* pReaderInfo)
{
	WirelessRecvProcThread* pThread = NULL;
	pThread = FindReadThread(pReaderInfo);
	if (!pThread)
	{
		pThread = CreateReadThread(pReaderInfo);
	}
	return pThread;
}

WirelessRecvProcThread* WirelessRecvCtrl::FindReadThread(WirelessReaderInfo* pReaderInfo)
{
	WirelessRecvProcThread* pThread = NULL;
	std::map<QString,WirelessRecvProcThread*>::iterator iter = mProcReadList.begin();
	QString strFirst;
	for (; iter!=mProcReadList.end(); ++iter)
	{
		if (WIRELESS_IsNetReader(NULL,pReaderInfo))
		{
			strFirst = QString("%1:%2").arg(QString::fromUtf8((char*)pReaderInfo->bIpAddr)).arg(pReaderInfo->nPort);
		}
		else
		{
			strFirst = QString("%1:%2").arg(QString::fromUtf8((char*)pReaderInfo->bComNum)).arg(pReaderInfo->nBaud);
		}

		if (iter->first == strFirst) 
		{
			pThread = iter->second;
			break;
		}
	}

	return pThread;

}

WirelessRecvProcThread* WirelessRecvCtrl::CreateReadThread(WirelessReaderInfo* pReaderInfo)
{
	WirelessRecvProcThread* pThread = NULL;
	pThread = new WirelessRecvProcThread(mIsEnableAnalysisTime);
	pThread->SetReaderInfo(this,pReaderInfo);
	QString strFirst;
	if (WIRELESS_IsNetReader(NULL,pReaderInfo))
	{
		strFirst = QString("%1:%2").arg(QString::fromUtf8((char*)pReaderInfo->bIpAddr)).arg(pReaderInfo->nPort);
	}
	else
	{
		strFirst = QString("%1:%2").arg(QString::fromUtf8((char*)pReaderInfo->bComNum)).arg(pReaderInfo->nBaud);
	}
	
	
	mProcReadList.insert(
		std::map<QString,WirelessRecvProcThread*>::value_type(strFirst,pThread)
		);
	


	return pThread;
}

void WirelessRecvCtrl::GetCardInfoList(WirelessReaderInfo* pReaderInfo,std::map<QString,CWirelessEpcCardInfo*>& cardList)
{
	if (pReaderInfo == NULL)
	{
		return;
	}
	QString strFirst;
	if (WIRELESS_IsNetReader(NULL,pReaderInfo))
	{
		strFirst = QString("%1:%2").arg(QString::fromUtf8((char*)pReaderInfo->bIpAddr)).arg(pReaderInfo->nPort);
	}
	else
	{
		strFirst = QString("%1:%2").arg(QString::fromUtf8((char*)pReaderInfo->bComNum)).arg(pReaderInfo->nBaud);
	}

	std::map<QString,WirelessRecvProcThread*>::iterator iter = mProcReadList.find(strFirst);	
	if (iter != mProcReadList.end())
	{
		iter->second->GetCardInfoList(cardList);
	}	
}

void WirelessRecvCtrl::StopRead(WirelessReaderInfo* pReaderInfo)
{
	WirelessRecvProcThread* pThread = NULL;
	pThread = FindReadThread(pReaderInfo);
	if (pThread)
	{
		pThread->stopRead();
	}
}

void WirelessRecvCtrl::DeleteRead(WirelessReaderInfo* pReaderInfo)
{
	WirelessRecvProcThread* pThread = NULL;
	pThread = FindReadThread(pReaderInfo);
	if (pThread)
	{
		pThread->stopRead();
		DeleteReadThread(pReaderInfo);
	}
}

void WirelessRecvCtrl::DeleteReadThread(WirelessReaderInfo* pReaderInfo)
{
	
	std::map<QString,WirelessRecvProcThread*>::iterator iter = mProcReadList.begin();
	QString strFirst;
	for (; iter!=mProcReadList.end(); ++iter)
	{

		if (WIRELESS_IsNetReader(NULL,pReaderInfo))
		{
			strFirst = QString("%1:%2").arg(QString::fromUtf8((char*)pReaderInfo->bIpAddr)).arg(pReaderInfo->nPort);
		}
		else
		{
			strFirst = QString("%1:%2").arg(QString::fromUtf8((char*)pReaderInfo->bComNum)).arg(pReaderInfo->nBaud);
		}

		if (iter->first == strFirst)
		{
			iter->second->stopRead();
			delete iter->second;
			iter->second = NULL;
			mProcReadList.erase(iter);
			break;
		}
	}
}

void WirelessRecvCtrl::ClearAllTag(WirelessReaderInfo* pReaderInfo)
{
	WirelessRecvProcThread* pThread = NULL;
	pThread = FindReadThread(pReaderInfo);
	if (pThread)
	{
		pThread->clearCard();
		
	}
}

void WirelessRecvCtrl::ClearAllRead()
{
	WirelessRecvProcThread* pThread = NULL;
	std::map<QString,WirelessRecvProcThread*>::iterator iter = mProcReadList.begin();
	for (; iter!=mProcReadList.end(); ++iter)
	{
		pThread = iter->second;
		pThread->stopRead();
		delete pThread;
		pThread = NULL;		
	}
	mProcReadList.clear();
}

void WirelessRecvCtrl::updateIOState(WirelessReaderInfo* pReaderInfo,QString& strState)
{
	if(mWirelessRecvDlg)
	{
		mWirelessRecvDlg->RecvIOState(pReaderInfo,strState);
	}
}

void WirelessRecvCtrl::SetEnableAnalysisTime(bool isEnable)
{
	mIsEnableAnalysisTime = isEnable;

	std::map<QString,WirelessRecvProcThread*>::iterator iter = mProcReadList.begin();
	for (; iter!=mProcReadList.end(); ++iter)
	{
		iter->second->SetAnalysisTime(isEnable);
	}
}

void WirelessRecvCtrl::SaveCardStr(const QString& strState)
{
	if(mWirelessRecvDlg)
	{
		mWirelessRecvDlg->SaveCardInfo(strState);
	}
}

void WirelessRecvCtrl::SetRevMsg(WirelessReaderInfo*pWirelessReaderInfo,int msgID,unsigned char bCommand,unsigned char* pData, int nLen)
{
	if(mWirelessRecvDlg)
	{
		mWirelessRecvDlg->SetRevMsg(pWirelessReaderInfo,msgID,bCommand,pData,nLen);
	}
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
WirelessRecvProcThread::WirelessRecvProcThread(bool isAnalysisTime)
{
	mIsEnableAnalysisTime = isAnalysisTime;
	mReadingType = 1;
	mIsStop = true;
}

WirelessRecvProcThread::~WirelessRecvProcThread(void)
{
	stopRead();
}

void WirelessRecvProcThread::run()
{
	int nRssi = 0;
	unsigned int  iIdCode;
	unsigned char nFlag = 0xFF;
	int nParam1 = 0;
	int nParam2 = 0;	
	int nAntenna = 0;
	unsigned char nTime[7];

	CRFrame pRevFrame;

	while( !mIsStop )
	{
		//OutputDebugStringA(QString("0-%1\n").arg(GetTickCount()).toUtf8().data());
		RecvMsg(pRevFrame);//处理消息

		int nRet = WIRELESS_SAAT_YRevIDMsgDecRssiExpand(
			mWirelessRecvCtrl->m_hCom,
			mReaderInfo,
			nTime,
			&nFlag, &iIdCode,
			&nRssi,
			&nAntenna,
			&nParam1,
			&nParam2);

		if( 1 == nRet/* && 0 != nLen*/  ) //读到卡,空卡要考虑
		{
			AnalysisCard(nTime,nFlag,iIdCode,nRssi, nParam1, nParam2,nAntenna);
		}
		else //未读到卡
		{
			Sleep(5);
		}
	}  

	mExitEvent.SetEvent();
}

bool WirelessRecvProcThread::startRead(int nReadType)
{
	if (mIsStop == false)
	{
		return true;
	}
	mReadingType = nReadType;
	mIsStop = false;
	this->start();
	return true;
}

bool WirelessRecvProcThread::stopRead()
{
	if (mIsStop == true)
	{
		return true;
	}
	mIsStop = true;
	this->quit();
	mExitEvent.WaitEvent(0xffffffff);
	clearCard();
	this->wait();
	return true;
}

void WirelessRecvProcThread::clearCard()
{
	mCardLock.Lock();

	std::map<QString,CWirelessEpcCardInfo*>::iterator iter = mCardList.begin();
	for (; iter!= mCardList.end(); ++iter)
	{
		delete iter->second;
		iter->second = NULL;
	}	
	mCardList.clear();

	mCardLock.Unlock();
}

void WirelessRecvProcThread::GetCardInfoList(std::map<QString,CWirelessEpcCardInfo*>& cardList)
{
	if (mIsStop == true)
	{
		return;
	}
	mCardLock.Lock();
	std::map<QString,CWirelessEpcCardInfo*>::iterator iter
		= mCardList.begin();
	for (; iter!= mCardList.end(); ++iter)
	{
		CWirelessEpcCardInfo* pCWirelessEpcCardInfo = new CWirelessEpcCardInfo();
		pCWirelessEpcCardInfo->m_szCardID = iter->second->m_szCardID;
		pCWirelessEpcCardInfo->m_szTagState = iter->second->m_szTagState;
		pCWirelessEpcCardInfo->m_szRssi = iter->second->m_szRssi;
		pCWirelessEpcCardInfo->m_otherInfo = iter->second->m_otherInfo;
		pCWirelessEpcCardInfo->m_szCurReadTime = iter->second->m_szCurReadTime;
		pCWirelessEpcCardInfo->m_szCurReadTime = iter->second->m_szCurReadTime;
		pCWirelessEpcCardInfo->m_nAntenna1Count = iter->second->m_nAntenna1Count;
		pCWirelessEpcCardInfo->m_nAntenna2Count = iter->second->m_nAntenna2Count;
		pCWirelessEpcCardInfo->m_nAntenna3Count = iter->second->m_nAntenna3Count;
		pCWirelessEpcCardInfo->m_nAntenna4Count = iter->second->m_nAntenna4Count;

		cardList[iter->first] = pCWirelessEpcCardInfo;
	}	
	mCardLock.Unlock();
}


void WirelessRecvProcThread::SetReaderInfo(WirelessRecvCtrl* pWirelessRecvCtrl,WirelessReaderInfo* pReaderInfo)
{
	mWirelessRecvCtrl = pWirelessRecvCtrl;
	mReaderInfo = pReaderInfo;
}

CWirelessEpcCardInfo* WirelessRecvProcThread::FindCardInfo(const QString& strCard)
{

	CWirelessEpcCardInfo* pCWirelessEpcCardInfo = NULL;
	std::map<QString,CWirelessEpcCardInfo*>::iterator iter = 
		mCardList.find(strCard);
	if (iter != mCardList.end())
	{
		pCWirelessEpcCardInfo = iter->second;
	}

	return pCWirelessEpcCardInfo;
}


CWirelessEpcCardInfo* WirelessRecvProcThread::GetCardInfo(const QString& szCardID)
{
	CWirelessEpcCardInfo* pCWirelessEpcCardInfo = NULL;

	pCWirelessEpcCardInfo = FindCardInfo(szCardID);	

	if (!pCWirelessEpcCardInfo)
	{
		pCWirelessEpcCardInfo = CreateCardInfo(szCardID);
	}

	return pCWirelessEpcCardInfo;
}

CWirelessEpcCardInfo* WirelessRecvProcThread::CreateCardInfo(const QString& szCardID)
{
	CWirelessEpcCardInfo* pCWirelessEpcCardInfo= new CWirelessEpcCardInfo();

	pCWirelessEpcCardInfo->m_szCardID = szCardID;

	pCWirelessEpcCardInfo->m_nAntenna1Count = 0;
	pCWirelessEpcCardInfo->m_nAntenna2Count = 0;
	pCWirelessEpcCardInfo->m_nAntenna3Count = 0;
	pCWirelessEpcCardInfo->m_nAntenna4Count = 0;

	mCardList.insert(std::map<QString,CWirelessEpcCardInfo*>::value_type(szCardID,pCWirelessEpcCardInfo));
	
	return pCWirelessEpcCardInfo;
}


bool WirelessRecvProcThread::RecvMsg(CRFrame &pRevFrame)
{
	bool bRet =false;
	bRet = WIRELESS_GetMsgResult(
		mWirelessRecvCtrl->m_hCom,
		mReaderInfo,
		pRevFrame);

	if ( bRet && mWirelessRecvCtrl)
	{
		mWirelessRecvCtrl->SetRevMsg(mReaderInfo,pRevFrame.bAddrInfo,pRevFrame.bCommand,pRevFrame.bData,pRevFrame.bLength-1);
	}

	return bRet;
}

bool WirelessRecvProcThread::CheckTimeBuffEnable(unsigned char* btBuf,unsigned char nLen)
{
	if (nLen <= 6)
	{
		return false;
	}

	QString("%1").arg(btBuf[nLen-1],2,16,QLatin1Char('0')).toInt();
	
	if (btBuf[nLen-1] >= 0xA0 ||  ((btBuf[nLen-1]&0x0f) >= 0x0A) )
	{
		return false;
	}

	if (btBuf[nLen-2] >= 0x13 ||  ((btBuf[nLen-2]&0x0f) >= 0x0A) )
	{
		return false;
	}

	if (btBuf[nLen-3] >= 0x32 ||  ((btBuf[nLen-3]&0x0f) >= 0x0A) )
	{
		return false;
	}

	if (btBuf[nLen-4] >= 0x08 ||  ((btBuf[nLen-4]&0x0f) >= 0x0A) )
	{
		return false;
	}

	if (btBuf[nLen-5] >= 0x25 ||  ((btBuf[nLen-5]&0x0f) >= 0x0A) )
	{
		return false;
	}

	if (btBuf[nLen-6] >= 0x61 ||  ((btBuf[nLen-6]&0x0f) >= 0x0A) )
	{
		return false;
	}
	
	if (btBuf[nLen-7] >= 0x61 ||  ((btBuf[nLen-7]&0x0f) >= 0x0A) )
	{
		return false;
	}

	return true;
}

void WirelessRecvProcThread::SetAnalysisTime(bool bAnalysistime)
{
	mIsEnableAnalysisTime = bAnalysistime;
}

bool WirelessRecvProcThread::AnalysisCard(unsigned char* nTime,
										  unsigned char nTagType,
										  unsigned int pId,
										  int  nRssi,
										  int nParam1, 
										  int nParam2, 
										  int nAntenna)
{
	mCardLock.Lock();
	QString cardStr = QString("%1").arg(pId);
	CWirelessEpcCardInfo* pCardFor6CInfo = NULL;
	pCardFor6CInfo = GetCardInfo(cardStr);
	assert(pCardFor6CInfo);	

	pCardFor6CInfo->m_szCardID = cardStr;
	int nYear = QString("%1").arg(nTime[6],2,16,QLatin1Char('0')).toInt();	
	if(nYear >= 70)
	{
		nYear+=1900;
	}
	else
	{
		nYear+=2000;
	}
	pCardFor6CInfo->m_szCurReadTime = QString("%1-%2-%3 %4:%5:%6")
		.arg(nYear)
		.arg(nTime[5],2,16,QLatin1Char('0'))
		.arg(nTime[4],2,16,QLatin1Char('0'))
		.arg(nTime[2],2,16,QLatin1Char('0'))
		.arg(nTime[1],2,16,QLatin1Char('0'))
		.arg(nTime[0],2,16,QLatin1Char('0'));
	pCardFor6CInfo->m_szTagState = GetTagStateStr(nTagType, nParam1);
	pCardFor6CInfo->m_otherInfo = GetTagDescribe(nTagType,nParam1,nParam2);
	pCardFor6CInfo->m_szRssi = GetTagRSSI(nTagType,nRssi);

	if (nAntenna == 1)
	{
		pCardFor6CInfo->m_nAntenna1Count++;
	}
	else if (nAntenna == 2)
	{
		pCardFor6CInfo->m_nAntenna2Count++;
	}
	else if (nAntenna == 3)
	{
		pCardFor6CInfo->m_nAntenna3Count++;
	}
	else if (nAntenna == 4)
	{
		pCardFor6CInfo->m_nAntenna4Count++;
	}	
	else
	{
		pCardFor6CInfo->m_nAntenna1Count++;
	}
	mCardLock.Unlock();

	return true;
}	

QString WirelessRecvProcThread::GetTagStateStr(unsigned char nTagType,int nTagState)
{
	QString retStr ;
	switch (nTagType) {
		case 0x00:
			retStr += GET_TXT("IDCS_TAG_NORMAL");
			retStr += ",";
			retStr += GetNormalTagState(nTagState);
			break;

		case 0x01:
			retStr += GET_TXT("IDCS_TAG_NORMAL");
			retStr += ",";
			retStr += GetNormalTagState(nTagState);
			break;

		case 0x02:
			retStr += GET_TXT("IDCS_TAG_TYPE_INVIGORAT");
			retStr += ",";
			retStr += GetInvigoratTagState(nTagState);
			break;

		case 0x03:// 电流标签
			retStr += GET_TXT("IDCS_TAG_TYPE_CURRENT");
			retStr += ",";
			retStr += GetCurrentTagState(nTagState);

			break;
		default:
			retStr += GET_TXT("IDCS_TAG_NORMAL");
			retStr += ",";
			retStr += GetNormalTagState(nTagState);
			break;
	}

	return retStr;
}

QString WirelessRecvProcThread::GetNormalTagState(int nTagState)
{

	QString retStr = "";

	if (0 != (nTagState & 0x01)) // 低压
	{
		if (retStr.length() == 0) {
			retStr += ",";
		}

		retStr += GET_TXT("IDCS_TAG_STATE_LOW_TENSION");
	}

	if (0 != ((nTagState >> 1) & 0x01)) // 防拆
	{
		if (retStr.length() == 0) {
			retStr += ",";
		}

		retStr += GET_TXT("IDCS_TAG_STATE_BACKOUT");
	}

	if (retStr.length() == 0) {
		retStr += GET_TXT("IDCS_TAG_STATE_NORMAL");
	}

	return retStr;
}

QString WirelessRecvProcThread::GetTemperatureTagState(int nTagState)
{
	return GetNormalTagState(nTagState);
}

QString WirelessRecvProcThread::GetInvigoratTagState(int nTagState)
{
	return GetNormalTagState(nTagState);
}

QString WirelessRecvProcThread::GetCurrentTagState(int nTagState)
{
	QString retStr = "";
	if (0 == (nTagState & 0x07)) // 正常
	{
		retStr += GET_TXT("IDCS_TAG_STATE_NORMAL");
	} 
	else 
	{
		if (0x01 == (nTagState & 0x01)) // 过载
		{
			if (!retStr.isEmpty())
			{
				retStr += ",";
			}
			// "拆除告警"
			retStr += GET_TXT("IDCS_TAG_STATE_BACKOUT");
			
		}

		if (0x02 == (nTagState & 0x02))// 掉电 低压
		{
			if (!retStr.isEmpty())
			{
				retStr += ",";
			}
			// "电池低压"
			retStr +=  GET_TXT("IDCS_TAG_STATE_LOW_TENSION");
		}

		if (0x04 == (nTagState & 0x04))// 过载 掉电 低压
		{
			if (!retStr.isEmpty())
			{
				retStr += ",";
			}
			// "标签故障"
			retStr += GET_TXT("IDCS_TAG_TAG_STATE_TROUBLE");
		}

		if (0x08 == (nTagState & 0x08))// 电流过载
		{
			if (!retStr.isEmpty())
			{
				retStr += ",";
			}
			// " 电流过载"
			retStr += GET_TXT("IDCS_TAG_STATE_CURRENT_OVERLOAD");
		}
	}

	return retStr;
}	

QString WirelessRecvProcThread::GetTagDescribe(int nTagType, int nParam1, int nParam2)
{
	QString retStr = "";
	switch (nTagType) {
		case 0x00:// 普通标签
			retStr += GetNarmalTagDescribe(nParam1, nParam2);
			break;

		case 0x01:// 温度标签
			retStr += GetNarmalTagDescribe(nParam1, nParam2);
			break;

		case 0x02:// 激励标签
			retStr += GetInvigoratTagDescribe(nParam1, nParam2);
			break;

		case 0x03:// 电流标签
			retStr += GetCurrentTagDescribe(nParam1, nParam2);
			break;
		default:
			retStr += GetNarmalTagDescribe(nParam1, nParam2);
			break;
	}

	return retStr;
}

QString WirelessRecvProcThread::GetNarmalTagDescribe(
	int nParam1, 
	int nParam2)
{
	return GET_TXT("IDCS_TAG_DESCRIBE_NULL");
}

QString WirelessRecvProcThread::GetTemperatureTagDescribe(
	int nParam1, 
	int nParam2)
{
	QString retStr = "";
		/*
		 * 总共16位：15至1位共是15位是有符号的整数温度 0位是小数部分，如果为0，小数部分为0；如果为1，整数部分无论正负都加上0.5
		 */
		retStr += GET_TXT("IDCS_AXES_NO");

		retStr += ":";
		retStr += QString("%1").arg(nParam1);
		retStr += ",";

		double dTemperature = 0;
		dTemperature = (nParam2 >> 1) + 0.5 * (nParam2 & 1);

		retStr += GET_TXT("IDCS_TEMPERATURE");

		retStr += ":";
		retStr +=QString("%1").arg(dTemperature);

		return retStr;
}

QString WirelessRecvProcThread::GetInvigoratTagDescribe(
	int nParam1, 
	int nParam2)
{
	QString retStr = "";

		/*
		 * 地址/场强
		 */
		retStr += GET_TXT("IDCS_ADDRESS");

		retStr += ":";
		retStr += QString("%1").arg(nParam1);
		retStr += ",";

		retStr += GET_TXT("IDCS_RSSI");

		retStr += ":";
		retStr += ("" + nParam2);

		return retStr;
}

QString WirelessRecvProcThread::GetCurrentTagDescribe(
	int nParam1, 
	int nParam2)
{
	return GetNarmalTagDescribe(nParam1, nParam2);
}

QString WirelessRecvProcThread::GetTagRSSI(int nTagType,int nParam3)
{
	QString retStr;	
	retStr = QString("%1").arg(nParam3);
	return retStr;
}

