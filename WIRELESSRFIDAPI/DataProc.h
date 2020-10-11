#pragma once
#include "CmdBuffer.h"
#include "IConnect.h"
#include "Global.h"

class CRFIDReader;

class CDataProc 
{
public:
	bool MsgProcess(unsigned char* revData,int revLength);
	bool UnPackMsg(unsigned char* revData,int revLength);
	int PackMsg(unsigned char pSendCommand, 
		unsigned char *pSendData,
		int dataLength,
		unsigned char *pForSend,
		int *pSendLen);//打包数据
	bool SendMsg(unsigned char pSendCommand, 
		unsigned char *pSendData, 
		int dataLength);
public:	
	CDataProc(CRFIDReader *pReader);
	~CDataProc(void);
private:
	CRFIDReader *mReader;
	CRFrame m_revFrame;
	int m_pasLength;
	unsigned char m_pasBuffer[REC_FRAME_MAXBUFF];

	int m_frameNum;
	int m_framePriority;
	int m_frameAnswer;
	int m_BusAddr;
private:
	unsigned short CountCRC16( unsigned char dataMsg, unsigned short crc);//CRC校验
	unsigned short CRC16 (unsigned char* pMsg, int msgLength);
};
