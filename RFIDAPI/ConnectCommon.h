#pragma once
#include "iconnect.h"
#include "IConnect.h"
#include "Global.h"
class CConnectCommon :public IConnect
{
public:
	CConnectCommon(void);
	void LoadData(CRFIDSystemCfg& initSystemCfg);
	bool OpenConn();
	bool CheckConnState(int maxWaitTime);
	bool SendMsg(unsigned char *pSendCommand, unsigned char *pSendData, int dataLength);
	bool RevMsg(CRFIDFrame &pRevFrame, int nWaitTime = 3000);
	bool SendNRevMsg(unsigned char *pSendCommand, unsigned char *pSendData, int dataLength, CRFIDFrame &pRevFrame,int nWaitTime = 3000);
	bool CloseConn();
	void ClearPasBuffer();
	void GetError(string& strError);
	int  GetErrorCode();			//�õ��������
	unsigned short CRC16 (unsigned char* pMsg, int msgLength);

	void SetFrameAddr(unsigned char iframeAddr);
	void SetFramePriority(bool priority);
	void SetFrameAnswer(bool answer);
	void ResetRFIDSystemCfg();
	void ResetFrame();

public:
	~CConnectCommon(void);

private:
	unsigned short CountCRC16( unsigned char dataMsg, unsigned short crc);

protected:

	CErrorProcess errorProc;
	CRFIDFrame sendFrame;
	CRFIDFrame revFrame;
	CRFIDSystemCfg RFIDSystemCfg;
	bool isConn;
	unsigned char frameNum;			//֡���к�  0 - f   //cxm fix
	unsigned char frameAddr;
	unsigned char framePriority;				//�Ƿ�����
	unsigned char frameAnswer;					//�Ƿ�Ӧ��֡
	RFIDErrorCode errorCode;

	unsigned char pasBuffer[REC_FRAME_MAXBUFF];
	int pasLength;

	bool PackMsg(unsigned char *sendCommand, unsigned char *sendData, int dataLength, unsigned char *pForSend,int *pSendLen);//���
	bool UnpackMsg(unsigned char * revData, int revLength);													//���

};
