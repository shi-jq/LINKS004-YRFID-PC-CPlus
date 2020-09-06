#ifndef READER_MANAGER_H
#define READER_MANAGER_H
#include <map>
#include "Singleton.h"
#include "readerdllbase.h"

class ReaderManager
{
	friend class CSingleton<ReaderManager>;
public:
	ReaderManager();
	~ReaderManager();
	bool Initial();//////³õÊ¼»¯
	void Quit();//////ÍË³ö 
	ReaderDllBase* SetCurReader(const QString& strInfo);
	ReaderDllBase* GetReader();
	QString GetReaderStrInfo();
	void ClearAllReader();

	ReaderDllBase* FindReader(const QString& strInfo);
	bool DeleteReader(const QString& strInfo);
	ReaderDllBase* CreateReader(const QString& strInfo);
	
	void GetConnectReaderMap(std::map<QString,ReaderDllBase*>& readerMap);
private:
	ReaderDllBase* mCurReader;
	QString mCurStrInfo;
	std::map<QString,ReaderDllBase*> mReaderMap;
	
};

#endif // READER_MANAGER_H
