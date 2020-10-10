#include "StdAfx.h"
#include "RFIDReaderManager.h"

CRFIDReaderManager* CRFIDReaderManager::RAID_ReaderManger = NULL;

CRFIDReaderManager::CRFIDReaderManager(void)
{
	pReaderFactory = new CSAATReaderFactory();
}


bool CRFIDReaderManager::LoadRFIDSystemCfg(CRFIDSystemCfg& cfg)
{
	memcpy((void*)&m_sysCFG,(void*)&cfg,sizeof(CRFIDSystemCfg));
	return true;
}


CRFIDReaderManager::~CRFIDReaderManager(void)
{
	map_ReaderList.clear();
	if( NULL != pReaderFactory )
	{
		delete pReaderFactory;
		pReaderFactory = NULL;
	}
}


CRFIDReaderManager* CRFIDReaderManager::Instance()
{
	if(RAID_ReaderManger == NULL)
		RAID_ReaderManger = new CRFIDReaderManager();
	return RAID_ReaderManger;
}


CRFIDReader* CRFIDReaderManager::OpenReader()
{
	return OpenReader(m_sysCFG);

}



CRFIDReader* CRFIDReaderManager::CreateReader()
{	
	CRFIDReader* pNewReader = pReaderFactory->ConcreteConn();//创建Reader实例
	return pNewReader;
}

bool CRFIDReaderManager::OpenReaderByObject(CRFIDReader* pNewReader)
{
	//问题:如果原先的Reader已打开,这时候再申请一个对象打开读写器,而另一个读写器在断开状态(会自动重连),有可能会导致新对象
	//出现断线情况,不过这种情况只要对客户说明不要重复去调用SAAT_Open则没事(调用之前必须先关闭原先的对象)
	if( !pNewReader->Open() )//打开Reader
	{
		pNewReader->Close();
		delete pNewReader;
		pNewReader = NULL;
		return false;
	}

	//假设读写器不能保证每台序列号不一样,故不能关闭原先的
        bool c =CloseOrgReader(pNewReader);
//        if( !CloseOrgReader(pNewReader) ) //关闭原Reader
//        {
//                pNewReader->Close();
//                delete pNewReader;
//                pNewReader = NULL;
//                return false;
//        }

	AddReader(pNewReader);//增加Reader至列表
	return true;

}

CRFIDReader* CRFIDReaderManager::OpenReader(CRFIDSystemCfg& cfg)
{
	CRFIDReader* pNewReader = pReaderFactory->ConcreteConn();//创建Reader实例
	if( NULL == pNewReader )
	{
		return NULL;
	}

	//问题:如果原先的Reader已打开,这时候再申请一个对象打开读写器,而另一个读写器在断开状态(会自动重连),有可能会导致新对象
	//出现断线情况,不过这种情况只要对客户说明不要重复去调用SAAT_Open则没事(调用之前必须先关闭原先的对象)
	if( !pNewReader->Open(cfg) )//打开Reader
	{
		pNewReader->Close();
		delete pNewReader;
		pNewReader = NULL;
		return NULL;
	}

	//假设读写器不能保证每台序列号不一样,故不能关闭原先的
	//if( !CloseOrgReader(pNewReader) ) //关闭原Reader,
	//{
	//	pNewReader->Close();
	//	delete pNewReader;
	//	pNewReader = NULL;
	//	return NULL;
	//}

	AddReader(pNewReader);//增加Reader至列表
	
	return pNewReader;
	 
}




bool CRFIDReaderManager::AddReader(CRFIDReader* pReader)
{
	//typedef pair <string, CRFIDReader*> stringMap_Pair;
	//map_ReaderList.insert( stringMap_Pair(pReader->GetProuctSN(),pReader));
	typedef pair <CRFIDReader*, string> stringMap_Pair;
	map_ReaderList.insert(stringMap_Pair(pReader,""));
	return true;
}


//根据新Reader的指针获得Reader的序列号
CRFIDReader* CRFIDReaderManager::CheckReader(CRFIDReader* pReader)
{
	/*string strReaderName = pReader->GetProuctSN();

	map <string, CRFIDReader*> :: const_iterator m1_AcIter;
	m1_AcIter = map_ReaderList.find(strReaderName);
	if ( m1_AcIter == map_ReaderList.end( ) )
	{
		return NULL;
	}

	return m1_AcIter->second;*/
	return NULL;
}

bool CRFIDReaderManager::CheckReaderExit(CRFIDReader* pReader)
{
	map <CRFIDReader*,string > :: iterator m1_AcIter;
	m1_AcIter = map_ReaderList.find(pReader);
	if ( m1_AcIter == map_ReaderList.end( ) )
	{
		return false;
	}
	return true;
	
}
bool CRFIDReaderManager::CloseReader(CRFIDReader* pReader)
{
	/*string strReaderName = pReader->GetProuctSN();
	map <string, CRFIDReader*> :: iterator m1_AcIter;
	m1_AcIter = map_ReaderList.find(strReaderName);
	if ( m1_AcIter == map_ReaderList.end( ) )
	{
		return false;
	}

	if( !pReader->Close() )
	{
		return false;
	}

	delete pReader;
	map_ReaderList.erase(m1_AcIter);*/
	
	map <CRFIDReader*,string > :: iterator m1_AcIter;
	m1_AcIter = map_ReaderList.find(pReader);
	if ( m1_AcIter == map_ReaderList.end( ) )
	{
		return true;
	}

        if( !pReader->Close() )
        {
                return false;
        }

        delete pReader;
        map_ReaderList.erase(m1_AcIter);

	return true;
}

//关闭原Reader
bool CRFIDReaderManager::CloseOrgReader(CRFIDReader* pReader)
{
	CRFIDReader* pOrgReader = CheckReader(pReader);
	if( pOrgReader == NULL ) //没找到
	{
		return true;
	}
	return CloseReader(pReader);
}
