#pragma once

#include "IReaderFactory.h"
#include "SAATReaderFactory.h"
#include <map>
#include <string>
using namespace std;

class CRFIDReaderManager
{
public://�ⲿ
	CRFIDReaderManager(void); 
	bool LoadRFIDSystemCfg(CRFIDSystemCfg& cfg);//��������
	CRFIDReader* OpenReader();//��Reader
	CRFIDReader* OpenReader(CRFIDSystemCfg& cfg);//��Reader
	bool OpenReaderByObject(CRFIDReader* pNewReader);//��Reader
	CRFIDReader* CRFIDReaderManager::CreateReader();//����RFIDReader����
	IReaderFactory *pReaderFactory;
	static CRFIDReaderManager* Instance();//��ʵ���ӿ�
	bool CloseReader(CRFIDReader* pReader);//�ر�Reader
private://�ڲ�
	CRFIDReader* CheckReader(CRFIDReader* pReader);//����Ƿ����Reader
	bool CheckReaderExit(CRFIDReader* pReader);//���Reader�Ƿ���ڹ�����
	bool AddReader(CRFIDReader* pReader);//����Reader
	bool CloseOrgReader(CRFIDReader* pReader);//ɾ��ԭ��Reader
	map<CRFIDReader*,string> map_ReaderList;//Reader List
public:
	~CRFIDReaderManager(void);
private:
	static CRFIDReaderManager* RAID_ReaderManger;
	CRFIDSystemCfg m_sysCFG;
};
