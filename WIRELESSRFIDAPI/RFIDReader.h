#pragma once
#include "Global.h"
#include <Winsock2.h>
#include "DataProc.h"
#include "WIRELESSRFIDAPIEXPORT.h"
#include "Lock.h"
#include "TCPProcCtrl.h"
#include "BuffList.h"
#include "CmdBuffer.h"

class CRFIDReader
{
public:
	CRFIDReader(READERTYPE readerType,SOCKET& sockConn); // tcp server  
	CRFIDReader(READERTYPE readerType,char *pHostName,int nsocketPort); // tcp Client
	CRFIDReader(READERTYPE readerType,unsigned char nBusAddr,char *pComNum,int nBaud); // com Client

	void Init();

	~CRFIDReader();
	bool UpdateSocket(SOCKET& sockConn);

	bool StartRead();
	bool StopRead();
	
	//��ȡ�ظ�����Ϣ
	bool GetRecvMsg(CRFrame& RFIDFrame);	
	
	bool GetIOState(CRFrame& RFIDFrame,int nWaitTime = 0);
	//��ȡ��ǰ����
	bool GetCard(CRFrame& RFIDFrame,int nWaitTime = 0);

	//�����Ϣ���
	bool SetMsgResult( CRFrame& RFIDFrame);
	//��������
	bool MsgProcess(unsigned char* revData,int revLength);

	//���ô�����
	void SetErrorCode(int nErrorCode,
		bool bCommandError = false);
	//��ȡ�������
	int	 GetErrorCode();
	//������Ϣ
	int SendMsg(unsigned char pCommand,
		unsigned char *pSendData, 
		int dataLength);//��������
	
	//�������ݵ�ͨ������
	bool SendData(unsigned char *pSendData, int dataLength);

	bool SendRFIDAck(CRFrame& RFIDFrame);

	bool SendRFIDIOStateAck(CRFrame& RFIDFrame);
	bool SendRFIDHeartStateAck(CRFrame& RFIDFrame);

	unsigned long  GetLastTime()
	{
		return mLastTime;
	};


	bool CheckTimeOut();

	bool SetReadState(ReadState state);

private:

	void initLastTime();

	READERTYPE mReaderType;
	CDataProc*  m_DataProcss;
	ConnetBase* mConnetBase;

	CBuffList<CRFrame> m_IOStateBuffer; //IO״̬�б�
	CBuffList<CRFrame> m_CardIDBuffer;  //���б�

	CCmdBuffer* m_RecvMsgFrame;	//ָ��

	ReadState m_ReadState;
	
	unsigned long mLastTime;

	CLock m_Critical;	//send lock
	unsigned char mForSend[CMD_DATA_BUFFER];
	int mForSendLen;

	map<DWORD,int> map_Error;
};
