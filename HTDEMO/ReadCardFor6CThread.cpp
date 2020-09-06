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
	unsigned char nBit = 0;
	unsigned int  iIdCode;
	unsigned char nFlag = 0xFF;
	int nHighPTR = 0;
	int nLowPTR = 0;
	int nParam3 = 0;	
	int nAntenna = 0;

	while( !mIsStop )
	{
		if (!mReaderDllBase)
		{
			break;
		}

		int nRet = SAAT_YRevIDMsgDecRssiExpand(
			mReaderDllBase->m_hCom,
			&nFlag, &iIdCode,
			&nBit,
			&nHighPTR,
			&nLowPTR,
			&nParam3,
			&nAntenna);

		if( 1 == nRet/* && 0 != nLen*/  ) //读到卡,空卡要考虑
		{
			AnalysisCard(nFlag,iIdCode,nBit,nHighPTR,nLowPTR,nParam3,nAntenna);
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

	std::map<QString,CardFor6CInfo*>::iterator iter = mCardList.begin();
	for (; iter!= mCardList.end(); ++iter)
	{
		delete iter->second;
		iter->second = NULL;
	}	
	mCardList.clear();

	mCardLock.Unlock();
}

void ReadCardFor6CThread::GetCardList(std::map<QString,CardFor6CInfo*>& cardList)
{
	mCardLock.Lock();
	std::map<QString,CardFor6CInfo*>::iterator iter = mCardList.begin();
	for (;iter!=mCardList.end(); ++iter)
	{
		CardFor6CInfo* pCardInfo = new CardFor6CInfo();
		pCardInfo->m_szCardID = iter->second->m_szCardID;
		pCardInfo->m_szTagState = iter->second->m_szTagState;
		pCardInfo->m_szRssi = iter->second->m_szRssi;
		pCardInfo->m_otherInfo = iter->second->m_otherInfo;
		pCardInfo->m_szCurReadTime = iter->second->m_szCurReadTime;
		pCardInfo->m_nAntenna1Count = iter->second->m_nAntenna1Count;
		pCardInfo->m_nAntenna2Count = iter->second->m_nAntenna2Count;
		pCardInfo->m_nAntenna3Count = iter->second->m_nAntenna3Count;
		pCardInfo->m_nAntenna4Count = iter->second->m_nAntenna4Count;
		cardList.insert(
			std::map<QString,CardFor6CInfo*>::value_type(iter->first,pCardInfo));

	}

	mCardLock.Unlock();
}

CardFor6CInfo* ReadCardFor6CThread::GetCard(const QString& szCard)
{
	CardFor6CInfo*  pCardFor6CInfo = NULL;

	pCardFor6CInfo = FindCard(szCard);
	if (!pCardFor6CInfo)
	{
		pCardFor6CInfo = CreateCard(szCard);
	}
	
	return pCardFor6CInfo;
}

CardFor6CInfo* ReadCardFor6CThread::FindCard(const QString& szCard)
{
	std::map<QString,CardFor6CInfo*>::iterator iter = mCardList.find(szCard);
	if (iter != mCardList.end())
	{
		return iter->second;
	}
	return NULL;
}

CardFor6CInfo* ReadCardFor6CThread::CreateCard(const QString& szCard)
{
	if(szCard.isEmpty())
	{
		assert(false);
	}

	CardFor6CInfo* pCardFor6CInfo= new CardFor6CInfo();

	pCardFor6CInfo->m_szCardID = szCard;

	pCardFor6CInfo->m_nAntenna1Count = 0;
	pCardFor6CInfo->m_nAntenna2Count = 0;
	pCardFor6CInfo->m_nAntenna3Count = 0;
	pCardFor6CInfo->m_nAntenna4Count = 0;

	mCardList.insert(std::map<QString,CardFor6CInfo*>::value_type(szCard,pCardFor6CInfo));
	
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
									   unsigned char pBit, 
									   int nParam1, 
									   int nParam2,
									   int nParam3,
									   int nAntenna)
{

	mCardLock.Lock();
	QString cardStr = QString("%1").arg(pId);
	CardFor6CInfo* pCardFor6CInfo = NULL;
	pCardFor6CInfo = GetCard(cardStr);
	assert(pCardFor6CInfo);	

	pCardFor6CInfo->m_szCardID = cardStr;
	pCardFor6CInfo->m_szCurReadTime = QDateTime::currentDateTime().toString(QString("yyyy-MM-dd hh:mm:ss"));
	pCardFor6CInfo->m_szTagState = GetTagStateStr(nTagType,pId);
	pCardFor6CInfo->m_otherInfo = GetTagDescribe(nTagType,nParam1,nParam2,nParam3);
	pCardFor6CInfo->m_szRssi = GetTagRSSI(nTagType,nParam3);

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
			retStr += GET_TXT("IDCS_TAG_TYPE_TEMPERATURE");
			retStr += ",";
			retStr += GetTemperatureTagState(nTagState);
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

QString ReadCardFor6CThread::GetTagDescribe(int nTagType, int nParam1, int nParam2,int nParam3)
{
	QString retStr = "";
	switch (nTagType) {
		case 0x00:// 普通标签
			retStr += GetNarmalTagDescribe(nParam1, nParam2, nParam3);
			break;

		case 0x01:// 温度标签
			retStr += GetTemperatureTagDescribe(nParam1, nParam2, nParam3);
			break;

		case 0x02:// 激励标签
			retStr += GetInvigoratTagDescribe(nParam1, nParam2, nParam3);
			break;

		case 0x03:// 电流标签
			retStr += GetCurrentTagDescribe(nParam1, nParam2, nParam3);
			break;
		default:
			retStr += GetNarmalTagDescribe(nParam1, nParam2, nParam3);
			break;
	}

	return retStr;
}

QString ReadCardFor6CThread::GetNarmalTagDescribe(
	int nParam1, 
	int nParam2,
	int nParam3)
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
	int nParam1, 
	int nParam2,
	int nParam3)
{
	return GetNarmalTagDescribe(nParam1, nParam2, nParam3);
}

QString ReadCardFor6CThread::GetTagRSSI(int nTagType,int nParam3)
{
	QString retStr;	
	retStr = QString("%1").arg(nParam3);
	return retStr;
}

