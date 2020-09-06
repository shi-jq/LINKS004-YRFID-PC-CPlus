#pragma once
#include "CmdBuffer.h"
#include "IConnect.h"
#include "IDataProc.h"

class CDataProc :IDataProc
{
public:
	CDataProc(void);
	void InitDataPorc(IReader* ReaderInterface) ;//��ʼ��IReaderָ��
	bool Open(CRFIDSystemCfg& cfg);//��
	bool Close();//�ر�
	bool ClosePort();//�رն˿�
	bool Reconect();
	bool PackMsg(unsigned char *pSendCommand, unsigned char *pSendData, int dataLength,CRFIDFrame &pRevFrame, unsigned char *pForSend,int *pSendLen);//�������
	bool SendMsg(unsigned char *pSendCommand, unsigned char *pSendData, int dataLength, CRFIDFrame &pRevFrame);//��������
	bool RevMsg(unsigned char *pRevMsg,unsigned char *pDataLen,int nWaitTime); //��������
	bool GetMsgResult(CRFIDFrame &pRevFrame,int nWaitTime );//�õ����ؽ��
	IConnect* ConcreteConn(CRFIDSystemCfg& cfg);//��������ͨѶ��ӿ�
	unsigned short CountCRC16( unsigned char dataMsg, unsigned short crc);//CRCУ��
	unsigned short CRC16 (unsigned char* pMsg, int msgLength);
	bool TestHeart() ;//���߼��
	void SetErrorCode(int nErrorCode,bool bCommandError = false);//���ô�����
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
