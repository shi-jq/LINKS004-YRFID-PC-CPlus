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
	CRFIDReader* pNewReader = pReaderFactory->ConcreteConn();//����Readerʵ��
	return pNewReader;
}

bool CRFIDReaderManager::OpenReaderByObject(CRFIDReader* pNewReader)
{
	//����:���ԭ�ȵ�Reader�Ѵ�,��ʱ��������һ������򿪶�д��,����һ����д���ڶϿ�״̬(���Զ�����),�п��ܻᵼ���¶���
	//���ֶ������,�����������ֻҪ�Կͻ�˵����Ҫ�ظ�ȥ����SAAT_Open��û��(����֮ǰ�����ȹر�ԭ�ȵĶ���)
	if( !pNewReader->Open() )//��Reader
	{
		pNewReader->Close();
		delete pNewReader;
		pNewReader = NULL;
		return false;
	}

	//�����д�����ܱ�֤ÿ̨���кŲ�һ��,�ʲ��ܹر�ԭ�ȵ�
        bool c =CloseOrgReader(pNewReader);
//        if( !CloseOrgReader(pNewReader) ) //�ر�ԭReader
//        {
//                pNewReader->Close();
//                delete pNewReader;
//                pNewReader = NULL;
//                return false;
//        }

	AddReader(pNewReader);//����Reader���б�
	return true;

}

CRFIDReader* CRFIDReaderManager::OpenReader(CRFIDSystemCfg& cfg)
{
	CRFIDReader* pNewReader = pReaderFactory->ConcreteConn();//����Readerʵ��
	if( NULL == pNewReader )
	{
		return NULL;
	}

	//����:���ԭ�ȵ�Reader�Ѵ�,��ʱ��������һ������򿪶�д��,����һ����д���ڶϿ�״̬(���Զ�����),�п��ܻᵼ���¶���
	//���ֶ������,�����������ֻҪ�Կͻ�˵����Ҫ�ظ�ȥ����SAAT_Open��û��(����֮ǰ�����ȹر�ԭ�ȵĶ���)
	if( !pNewReader->Open(cfg) )//��Reader
	{
		pNewReader->Close();
		delete pNewReader;
		pNewReader = NULL;
		return NULL;
	}

	//�����д�����ܱ�֤ÿ̨���кŲ�һ��,�ʲ��ܹر�ԭ�ȵ�
	//if( !CloseOrgReader(pNewReader) ) //�ر�ԭReader,
	//{
	//	pNewReader->Close();
	//	delete pNewReader;
	//	pNewReader = NULL;
	//	return NULL;
	//}

	AddReader(pNewReader);//����Reader���б�
	
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


//������Reader��ָ����Reader�����к�
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

//�ر�ԭReader
bool CRFIDReaderManager::CloseOrgReader(CRFIDReader* pReader)
{
	CRFIDReader* pOrgReader = CheckReader(pReader);
	if( pOrgReader == NULL ) //û�ҵ�
	{
		return true;
	}
	return CloseReader(pReader);
}
