#pragma once
#include "IReader.h"

class IDataProc
{
public:
	IDataProc(void);
	virtual void InitDataPorc(IReader* ReaderInterface) = 0;//��ʼ��IReaderָ��
	virtual bool MsgProcess(unsigned char* revData,int revLength) = 0 ;//��Ϣ�������
	virtual bool TestHeart() = 0;//���߼��
	virtual void SetErrorCode(int nErrorCode,bool bCommandError = false) = 0;//���ô�����
public:
	virtual ~IDataProc(void);
};
