#pragma once

#include "IReaderFactory.h"
#include "SAATReaderFactory.h"
#include <map>
#include <string>
using namespace std;

class CRFIDReaderManager
{
public://外部
	CRFIDReaderManager(void); 


	CRFIDReaderServer* CRFIDReaderManager::CreateReader();//创建RFIDReader对象
	IReaderFactory *pReaderFactory;
	static CRFIDReaderManager* Instance();//单实例接口
	bool CloseReader(CRFIDReaderServer* pReader);//关闭Reader
private://内部
	CRFIDReaderServer* CheckReader(CRFIDReaderServer* pReader);//检查是否存在Reader
	bool CheckReaderExit(CRFIDReaderServer* pReader);//检查Reader是否存在管理当中
	bool AddReader(CRFIDReaderServer* pReader);//增加Reader
	
	map<CRFIDReaderServer*,string> map_ReaderList;//Reader List
public:
	~CRFIDReaderManager(void);
private:
	static CRFIDReaderManager* RAID_ReaderManger;
	//CRFIDSystemCfg m_sysCFG;
};
