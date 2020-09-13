#include "ReadCardFor6CThread.h"
#include <QDateTime>
#include "Lock.h"
#include "appconfig.h"
#include <assert.h>
#include "readerdllbase.h"
#include "readermanager.h"
#include "RFIDAPIEXPORT.h"
#include "LanguageSrc.h"


ReadCardFor6CThread::ReadCardFor6CThread(ReaderDllBase* pReaderDllBase,
										 QObject *parent)
	:QThread(parent)
{
	mReaderDllBase = pReaderDllBase;
	mIsStop = true;
	mReadingType = 0;
}

ReadCardFor6CThread::~ReadCardFor6CThread(void)
{
	StopRead();
	clearCard();
}

bool ReadCardFor6CThread::StartRead(int readType)
{
	if(!mIsStop)
	{
		return false;
	}
	
	mReaderDllBase->SetState(STATE_READING);
	mReadingType = readType;
	mIsStop = false;
	clearCard();
	this->start();
	return true;
}

bool ReadCardFor6CThread::StopRead()
{
	if (mIsStop)
	{
		return true;
	}
	mIsStop = true;
	mExitEvent.WaitEvent(3000);	
	mReaderDllBase->SetState(STATE_CONNET);
	return true;
}

void ReadCardFor6CThread::run()
{
	unsigned int  iIdCode;
	unsigned char nFlag = 0xFF;
	int nParam1= 0;
	int nParam2 = 0;
	int nRssi = 0;	
	int nAntenna = 0;

	while( !mIsStop )
	{
		if (!mReaderDllBase)
		{
			break;
		}

		int nRet = SAAT_YRevIDMsgDecRssiExpand(
			mReaderDllBase->m_hCom,
			&nFlag,
			&iIdCode,
			&nRssi,
			&nAntenna,
			&nParam1, 
			&nParam2);

		if( 1 == nRet/* && 0 != nLen*/  ) //读到卡,空卡要考虑
		{
			AnalysisCard(nFlag,iIdCode, nParam1, nRssi,nAntenna);
		}
		else //未读到卡
		{
			this->msleep(300);
		}
	}  

	mExitEvent.SetEvent();
}

void ReadCardFor6CThread::clearCard()
{
	mCardLock.Lock();

	std::vector<CardFor6CInfo*>::iterator iter = mCardList.begin();
	for (; iter!= mCardList.end(); ++iter)
	{
		delete (*iter);
		(*iter) = NULL;
	}	
	mCardList.clear();

	mCardLock.Unlock();
}

void ReadCardFor6CThread::GetCardList(std::vector<CardFor6CInfo*>& cardList)
{
	mCardLock.Lock();
	std::vector<CardFor6CInfo*>::iterator iter = mCardList.begin();
	for (;iter!=mCardList.end(); ++iter)
	{
		CardFor6CInfo* pCardInfo = new CardFor6CInfo();
		pCardInfo->m_szCardID = (*iter)->m_szCardID;
		pCardInfo->m_szTagState = (*iter)->m_szTagState;
		pCardInfo->m_szRssi = (*iter)->m_szRssi;
		pCardInfo->m_otherInfo = (*iter)->m_otherInfo;
		pCardInfo->m_szCurReadTime = (*iter)->m_szCurReadTime;
		pCardInfo->m_nAntennaNo = (*iter)->m_nAntennaNo;
		pCardInfo->m_nAntennaCount = (*iter)->m_nAntennaCount;
		cardList.push_back(pCardInfo);
	}

	mCardLock.Unlock();
}

CardFor6CInfo* ReadCardFor6CThread::GetCard(const QString& szCard,int antenna)
{
	CardFor6CInfo*  pCardFor6CInfo = NULL;

	pCardFor6CInfo = FindCard(szCard, antenna);
	if (!pCardFor6CInfo)
	{
		pCardFor6CInfo = CreateCard(szCard, antenna);
	}
	
	return pCardFor6CInfo;
}

CardFor6CInfo* ReadCardFor6CThread::FindCard(const QString& szCard, int antenna)
{
	std::vector<CardFor6CInfo*>::iterator iter = mCardList.begin();
	for (; iter != mCardList.end(); ++iter)
	{
		CardFor6CInfo* pCard = *iter;
		if (pCard->m_nAntennaNo == antenna
			&& pCard->m_szCardID.compare(szCard) == 0 )
		{
			return pCard;
		}
	}

	return NULL;
}

CardFor6CInfo* ReadCardFor6CThread::CreateCard(const QString& szCard, int antenna)
{
	if(szCard.isEmpty())
	{
		assert(false);
	}

	CardFor6CInfo* pCardFor6CInfo= new CardFor6CInfo();

	pCardFor6CInfo->m_szCardID = szCard;

	pCardFor6CInfo->m_nAntennaNo= antenna;
	pCardFor6CInfo->m_nAntennaCount = 0;

	mCardList.push_back(pCardFor6CInfo);
	
	return pCardFor6CInfo;
}


/*
void ReadCardFor6CThread::AddCardBuff(unsigned char nAntenna, unsigned char* btBuf1,unsigned char nLen1, unsigned char* btBuf2,unsigned char nLen2)
{
	QString szTmp,szEpcId,szTid;
	szEpcId.clear();
	for( int i = 0 ; i < nLen1 ; i++ )
	{	
		szEpcId +=QString("%1").arg(btBuf1[i],2,16,QLatin1Char('0')).toUpper();
	}

	if( nLen1 == 0 )
	{
		szEpcId = "";
	}
	szTid.clear();
	for( int i = 0 ; i < nLen2 ; i++ )
	{
		szTid += QString("%1").arg(btBuf2[i],2,16,QLatin1Char('0')).toUpper();		
	}

	mCardLock.Lock();
	CardFor6CInfo* pCardFor6CInfo = NULL;
	pCardFor6CInfo = GetCard(szEpcId,szTid);
	assert(pCardFor6CInfo);	

	pCardFor6CInfo->m_szEPC = szEpcId;
	pCardFor6CInfo->m_szTID = szTid;
	pCardFor6CInfo->m_szCurReadTime = QDateTime::currentDateTime().toString(QString("yyyy-MM-dd hh:mm:ss"));

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
	mCardLock.Unlock();
}
//*/


void ReadCardFor6CThread::SetReader(ReaderDllBase* pReaderDllBase)
{
	mReaderDllBase = pReaderDllBase;
}


bool ReadCardFor6CThread::AnalysisCard(
	unsigned char nTagType,
	unsigned int pId,
	int nParam1, 
	int nRssi, int nAntenna)
{
	mCardLock.Lock();
	QString cardStr = QString("%1").arg(pId);
	CardFor6CInfo* pCardFor6CInfo = NULL;
	pCardFor6CInfo = GetCard(cardStr, nAntenna);
	assert(pCardFor6CInfo);
	pCardFor6CInfo->m_szCardID = cardStr;
	pCardFor6CInfo->m_szCurReadTime = QDateTime::currentDateTime().toString(QString("yyyy-MM-dd hh:mm:ss"));
	pCardFor6CInfo->m_szTagState = GetTagStateStr(nTagType, nParam1);
	pCardFor6CInfo->m_otherInfo = GetTagDescribe(nTagType, nParam1);
	pCardFor6CInfo->m_szRssi = GetTagRSSI(nTagType, nRssi);

	pCardFor6CInfo->m_nAntennaNo = nAntenna;
	pCardFor6CInfo->m_nAntennaCount++;
	
	mCardLock.Unlock();

	return true;
}

QString ReadCardFor6CThread::GetTagStateStr(unsigned char nTagType,int nTagState)
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

QString ReadCardFor6CThread::GetNormalTagState(int nTagState)
{
	QString retStr = "";

	if (0 != (nTagState & 0x01)) // 低压
	{
		if (retStr.length() == 0) {
			retStr += ",";
		}

		retStr += GET_TXT("IDCS_TAG_STATE_LOW_TENSION");
	}

	if (0 != ((nTagState>>1) & 0x01)) // 防拆
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

QString ReadCardFor6CThread::GetTemperatureTagState(int nTagState)
{
	return GetNormalTagState(nTagState);
}

QString ReadCardFor6CThread::GetInvigoratTagState(int nTagState)
{
	return GetNormalTagState(nTagState);
}

QString ReadCardFor6CThread::GetCurrentTagState(int nTagState)
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

QString ReadCardFor6CThread::GetTagDescribe(int nTagType, int nParam)
{
	QString retStr = "";
	switch (nTagType) {
		case 0x01:// 普通标签
			retStr += GetNarmalTagDescribe(nParam);
			break;
		default:
			retStr += GetNarmalTagDescribe(nParam);
			break;
	}

	return retStr;
}

QString ReadCardFor6CThread::GetNarmalTagDescribe(
	int nParam1)
{
	return GET_TXT("IDCS_TAG_DESCRIBE_NULL");
}

QString ReadCardFor6CThread::GetTemperatureTagDescribe(
	int nParam1, 
	int nParam2,
	int nParam3)
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

QString ReadCardFor6CThread::GetInvigoratTagDescribe(
	int nParam1, 
	int nParam2,
	int nParam3)
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

QString ReadCardFor6CThread::GetCurrentTagDescribe(
	int nParam1)
{
	return GetNarmalTagDescribe(nParam1);
}

QString ReadCardFor6CThread::GetTagRSSI(int nTagType,int nParam3)
{
	QString retStr;	
	retStr = QString("%1").arg(nParam3);
	return retStr;
}

