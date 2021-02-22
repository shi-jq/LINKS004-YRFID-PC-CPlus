#pragma once
#include "CmdBuffer.h"
#include "IConnect.h"
#include "IDataProc.h"

class CDataProc :IDataProc
{
public:
	CDataProc(void);
	void InitDataPorc(IReader* ReaderInterface) ;//初始化IReader指针
	bool Open(CRFIDSystemCfg& cfg);//打开
	bool Close();//关闭
	bool ClosePort();//关闭端口
	bool Reconect();
	bool PackMsg(unsigned char *pSendCommand, unsigned char *pSendData, int dataLength,CRFIDFrame &pRevFrame, unsigned char *pForSend,int *pSendLen);//打包数据
	bool SendMsg(unsigned char *pSendCommand, unsigned char *pSendData, int dataLength, CRFIDFrame &pRevFrame);//发送数据
	bool RevMsg(unsigned char *pRevMsg,unsigned char *pDataLen,int nWaitTime); //接收数据
	bool GetMsgResult(CRFIDFrame &pRevFrame,int nWaitTime );//得到返回结果
	IConnect* ConcreteConn(CRFIDSystemCfg& cfg);//创建数据通讯类接口
	unsigned short CountCRC16( unsigned char dataMsg, unsigned short crc);//CRC校验
	unsigned short CRC16 (unsigned char* pMsg, int msgLength);
	bool TestHeart() ;//掉线检测
	void SetErrorCode(int nErrorCode,bool bCommandError = false);//设置错误码
	bool SendRawData(unsigned char* szData,int nLen);
	bool RevRawData(unsigned char* szData,unsigned char* pLen, int nWaitTime);
private:
	IConnect * m_pConnect;
	int m_frameNum;
	int m_framePriority;
	int m_frameAnswer;
	CRFIDSystemCfg m_RFIDSystemCfg;
	IReader *pReader;
	bool m_Open;
public:	
	CRFrame m_revFrame;
	int m_pasLength;
	bool MsgProcess(unsigned char* revData,int revLength);
	bool UnPackMsg(unsigned char* revData,int revLength);
	unsigned char m_pasBuffer[REC_FRAME_MAXBUFF];
public:
	~CDataProc(void);
};
