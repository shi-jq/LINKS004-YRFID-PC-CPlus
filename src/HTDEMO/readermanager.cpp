#include "readermanager.h"
#include "readerdllbase.h"

ReaderManager::ReaderManager()
{
	mCurReader = NULL;
	mCurStrInfo.clear();
}

bool ReaderManager::Initial()
{
	ClearAllReader();
	return true;
}

void ReaderManager::Quit()
{
	ClearAllReader();
}

ReaderDllBase* ReaderManager::GetReader()
{
	return mCurReader;
}

bool ReaderManager::DeleteReader(const QString& strInfo)
{
	std::map<QString,ReaderDllBase*>::iterator iter = mReaderMap.find(strInfo);
	if (iter != mReaderMap.end())
	{
		if (!iter->second->CloseReader())
		{
			return false;
		}

		if(mCurReader == iter->second)
		{
			mCurReader = NULL;
			mCurStrInfo.clear();
		}

		delete iter->second;
		mReaderMap.erase(iter);
	}

	return true;
}

ReaderDllBase* ReaderManager::FindReader(const QString& strInfo)
{
	std::map<QString,ReaderDllBase*>::iterator iter = mReaderMap.find(strInfo);
	if (iter != mReaderMap.end())
	{
		return iter->second;
	}

	return NULL;
}

ReaderDllBase* ReaderManager::SetCurReader(const QString& strInfo)
{
	ReaderDllBase*  pReaderDllBase = FindReader(strInfo);
	if (pReaderDllBase)
	{	
		mCurReader =  pReaderDllBase ;
		mCurStrInfo = strInfo;
	}

	return mCurReader;
}

void ReaderManager::ClearAllReader()
{
	std::map<QString,ReaderDllBase*>::iterator iter = mReaderMap.begin();
	for (; iter!=mReaderMap.end(); ++iter)
	{
		iter->second->CloseReader();
		delete iter->second;
	}	
	mReaderMap.clear();
	mCurReader = NULL;
	mCurStrInfo.clear();
}

ReaderDllBase* ReaderManager::CreateReader(const QString& strInfo)
{
	ReaderDllBase* pReaderDllBase = new ReaderDllBase();

	mReaderMap[strInfo] = pReaderDllBase;

	return pReaderDllBase;
}

QString ReaderManager::GetReaderStrInfo()
{
	return mCurStrInfo;
}

ReaderManager::~ReaderManager()
{

}

void ReaderManager::GetConnectReaderMap(std::map<QString,ReaderDllBase*>& readerMap)
{
	std::map<QString,ReaderDllBase*>::iterator iter = mReaderMap.begin();
	for (; iter!=mReaderMap.end(); ++iter)
	{
		if (iter->second->GetState() == STATE_CONNET)
		{
			readerMap[iter->first] = iter->second;
		}	
	}	
}

