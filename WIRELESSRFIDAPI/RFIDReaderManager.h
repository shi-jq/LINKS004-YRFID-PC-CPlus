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


	CRFIDReaderServer* CRFIDReaderManager::CreateReader();//����RFIDReader����
	IReaderFactory *pReaderFactory;
	static CRFIDReaderManager* Instance();//��ʵ���ӿ�
	bool CloseReader(CRFIDReaderServer* pReader);//�ر�Reader
private://�ڲ�
	CRFIDReaderServer* CheckReader(CRFIDReaderServer* pReader);//����Ƿ����Reader
	bool CheckReaderExit(CRFIDReaderServer* pReader);//���Reader�Ƿ���ڹ�����
	bool AddReader(CRFIDReaderServer* pReader);//����Reader
	
	map<CRFIDReaderServer*,string> map_ReaderList;//Reader List
public:
	~CRFIDReaderManager(void);
private:
	static CRFIDReaderManager* RAID_ReaderManger;
	//CRFIDSystemCfg m_sysCFG;
};
