#pragma once
#include "Singleton.h"
#include "WIRELESSRFIDAPIEXPORT.h"
#include <wtypes.h>
#include <QString>
#include <QThread>
#include <map>
#include <QMutex>
#include "Lock.h"

#define WIRELESSRECV_HANDLE (CSingleton<WirelessRecvCtrl>::GetInstance()->m_hCom)

class WirelessRecvDlg;
class CWirelessEpcCardInfo;
class WirelessRecvProcThread;

class WirelessRecvCtrl
{
	friend class CSingleton<WirelessRecvCtrl>;
public:
	WirelessRecvCtrl(void);
	~WirelessRecvCtrl(void);
	//���ն�д��
	void recvReaderInfo(WirelessReaderInfo* pReaderInfo);
	//���ý���ָ��
	void SetpDlg(WirelessRecvDlg* pWirelessRecvDlg);
	void SetEnableAnalysisTime(bool isEnable);

	//����io��״̬
	void updateIOState(WirelessReaderInfo* pReaderInfo,QString& strState);
	void SaveCardStr(const QString& strState);
	void SetRevMsg(WirelessReaderInfo* pWirelessReaderInfo,int msgID,unsigned char bCommand,unsigned char* pData, int nLen);
	HANDLE m_hCom;//��д����handle 
	
	void StartRead(WirelessReaderInfo* pReaderInfo,int nReadType);
	void StopRead(WirelessReaderInfo* pReaderInfo);
	void DeleteRead(WirelessReaderInfo* pReaderInfo);
	void ClearAllTag(WirelessReaderInfo* pReaderInfo);
	void ClearAllRead();
	void GetCardInfoList(WirelessReaderInfo* pReaderInfo,std::map<QString,CWirelessEpcCardInfo*>& cardList);
private:
	WirelessRecvProcThread* GetReadThread(WirelessReaderInfo* pReaderInfo);
	WirelessRecvProcThread* FindReadThread(WirelessReaderInfo* pReaderInfo);
	WirelessRecvProcThread* CreateReadThread(WirelessReaderInfo* pReaderInfo);
	void DeleteReadThread(WirelessReaderInfo* pReaderInfo);

private:
	WirelessRecvDlg* mWirelessRecvDlg;
	bool mIsEnableAnalysisTime;

		
	std::map<QString,WirelessRecvProcThread*> mProcReadList;
};

/************************************************************************/
/*��                                                                      */
/************************************************************************/
class CWirelessEpcCardInfo
{
public:	
	CWirelessEpcCardInfo(){
		m_nAntenna1Count = 0;
		m_nAntenna2Count = 0;
		m_nAntenna3Count = 0;
		m_nAntenna4Count = 0;
	}
	~CWirelessEpcCardInfo(){}
public:
	QString m_szCardID;
	QString m_szTagState;
	QString m_szRssi;
	QString m_otherInfo;
	QString m_szCurReadTime;	
	unsigned int m_nAntenna1Count;
	unsigned int m_nAntenna2Count;
	unsigned int m_nAntenna3Count;
	unsigned int m_nAntenna4Count;
};

/************************************************************************/
/*�����߳�                                                                      */
/************************************************************************/
class WirelessRecvProcThread : public QThread
{
public:
	enum
	{
		READ_TYPE_EPC = 1,
		READ_TYPE_TID = 3,
		READ_TYPE_EPC_TID = 5,
	};
	WirelessRecvProcThread(bool isAnalysisTime);
	~WirelessRecvProcThread(void);
	//���ö�д����Ϣ
	void SetReaderInfo(WirelessRecvCtrl* pWirelessRecvCtrl,WirelessReaderInfo* pReaderInfo);
	bool startRead(int nReadType);//��ʼ����
	bool stopRead();//ֹͣ����
	void clearCard();//��տ�
	void SetAnalysisTime(bool bAnalysistime);

	//��ȡ���б�
	void GetCardInfoList(std::map<QString,CWirelessEpcCardInfo*>& cardList);
private:

	void run();

	bool AnalysisCard(
		unsigned char* nTime,
		unsigned char nTagType,
		unsigned int pId,
		int nRssi,
		int nParam1,
		int nParam2,
		int nAntenna);

	QString GetTagStateStr(unsigned char nTagType,int nTagState);
	QString GetNormalTagState(int nTagState); //��ͨ��ǩ
	QString GetTemperatureTagState(int nTagState);//�¶ȱ�ǩ
	QString GetInvigoratTagState(int nTagState);//������ǩ
	QString GetCurrentTagState(int nTagState);//������ǩ

	QString GetTagDescribe(int nTagType, int nParam1, int nParam2);
	QString GetNarmalTagDescribe(int nParam1, int nParam2);//��ͨ��ǩ
	QString GetTemperatureTagDescribe(int nParam1, int nParam2);//�¶ȱ�ǩ
	QString GetInvigoratTagDescribe(int nParam1, int nParam2);//������ǩ
	QString GetCurrentTagDescribe(int nParam1, int nParam2);//������ǩ

	QString GetTagRSSI(int nTagType,int nParam3);

	bool RecvMsg(CRFrame &pRevFrame);

	CWirelessEpcCardInfo* FindCardInfo(const QString& szCardID);
	CWirelessEpcCardInfo* CreateCardInfo(const QString& szCardID);

	CWirelessEpcCardInfo* GetCardInfo(const QString& szCardID);
	bool CheckTimeBuffEnable(unsigned char* btBuf,unsigned char nLen);
private:	
	int mReadingType;

	WirelessReaderInfo* mReaderInfo;
	WirelessRecvCtrl* mWirelessRecvCtrl;
	bool mIsEnableAnalysisTime;

	QString mOldIOStateStr;

	bool mIsStop;			
	CMyEvent mExitEvent;
	CLock mCardLock;	    
	std::map<QString,CWirelessEpcCardInfo*>  mCardList;

};