#include "StdAfx.h"
#include "RFIDReaderManager.h"
#include "ConnetCreater.h"

CRFIDReaderManager* CRFIDReaderManager::RAID_ReaderManger = NULL;

CRFIDReaderManager::CRFIDReaderManager(void)
{
	pReaderFactory = new CSAATReaderFactory();
	CSingleton<ConnetCreater>::GetInstance()->Init();
}


CRFIDReaderManager::~CRFIDReaderManager(void)
{
	map_ReaderList.clear();
	if( NULL != pReaderFactory )
	{
		delete pReaderFactory;
		pReaderFactory = NULL;
	}
	CSingleton<ConnetCreater>::GetInstance()->Quit();
	CSingleton<ConnetCreater>::ReleaseInstance();
}


CRFIDReaderManager* CRFIDReaderManager::Instance()
{
	if(RAID_ReaderManger == NULL)
		RAID_ReaderManger = new CRFIDReaderManager();
	return RAID_ReaderManger;
}


CRFIDReaderServer* CRFIDReaderManager::CreateReader()
{	
	CRFIDReaderServer* pNewReader = pReaderFactory->ConcreteConn();//创建Reader实例
	AddReader(pNewReader);//增加Reader至列表
	return pNewReader;
}

bool CRFIDReaderManager::AddReader(CRFIDReaderServer* pReader)
{
	//typedef pair <string, CRFIDReaderServer*> stringMap_Pair;
	//map_ReaderList.insert( stringMap_Pair(pReader->GetProuctSN(),pReader));
	typedef pair <CRFIDReaderServer*, string> stringMap_Pair;
	map_ReaderList.insert(stringMap_Pair(pReader,""));
	return true;
}


//根据新Reader的指针获得Reader的序列号
CRFIDReaderServer* CRFIDReaderManager::CheckReader(CRFIDReaderServer* pReader)
{
	/*string strReaderName = pReader->GetProuctSN();

	map <string, CRFIDReaderServer*> :: const_iterator m1_AcIter;
	m1_AcIter = map_ReaderList.find(strReaderName);
	if ( m1_AcIter == map_ReaderList.end( ) )
	{
		return NULL;
	}

	return m1_AcIter->second;*/
	return NULL;
}

bool CRFIDReaderManager::CheckReaderExit(CRFIDReaderServer* pReader)
{
	map <CRFIDReaderServer*,string > :: iterator m1_AcIter;
	m1_AcIter = map_ReaderList.find(pReader);
	if ( m1_AcIter == map_ReaderList.end( ) )
	{
		return false;
	}
	return true;
	
}
bool CRFIDReaderManager::CloseReader(CRFIDReaderServer* pReader)
{
	map <CRFIDReaderServer*,string > :: iterator m1_AcIter;
	m1_AcIter = map_ReaderList.find(pReader);
	if ( m1_AcIter == map_ReaderList.end( ) )
	{
		return true;
	}

	delete pReader;
	pReader = NULL;
	map_ReaderList.erase(m1_AcIter);

	return true;
}
