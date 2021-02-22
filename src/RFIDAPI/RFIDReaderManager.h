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
	bool LoadRFIDSystemCfg(CRFIDSystemCfg& cfg);//载入配置
	CRFIDReader* OpenReader();//打开Reader
	CRFIDReader* OpenReader(CRFIDSystemCfg& cfg);//打开Reader
	bool OpenReaderByObject(CRFIDReader* pNewReader);//打开Reader
	CRFIDReader* CRFIDReaderManager::CreateReader();//创建RFIDReader对象
	IReaderFactory *pReaderFactory;
	static CRFIDReaderManager* Instance();//单实例接口
	bool CloseReader(CRFIDReader* pReader);//关闭Reader
private://内部
	CRFIDReader* CheckReader(CRFIDReader* pReader);//检查是否存在Reader
	bool CheckReaderExit(CRFIDReader* pReader);//检查Reader是否存在管理当中
	bool AddReader(CRFIDReader* pReader);//增加Reader
	bool CloseOrgReader(CRFIDReader* pReader);//删除原先Reader
	map<CRFIDReader*,string> map_ReaderList;//Reader List
public:
	~CRFIDReaderManager(void);
private:
	static CRFIDReaderManager* RAID_ReaderManger;
	CRFIDSystemCfg m_sysCFG;
};
