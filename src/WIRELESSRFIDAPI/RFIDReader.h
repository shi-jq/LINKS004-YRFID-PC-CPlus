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
	
	//获取回复的消息
	bool GetRecvMsg(CRFrame& RFIDFrame);	
	
	bool GetIOState(CRFrame& RFIDFrame,int nWaitTime = 0);
	//获取当前卡号
	bool GetCard(CRFrame& RFIDFrame,int nWaitTime = 0);

	//添加消息结果
	bool SetMsgResult( CRFrame& RFIDFrame);
	//接收数据
	bool MsgProcess(unsigned char* revData,int revLength);

	//设置错误码
	void SetErrorCode(int nErrorCode,
		bool bCommandError = false);
	//获取出错代码
	int	 GetErrorCode();
	//发送消息
	int SendMsg(unsigned char pCommand,
		unsigned char *pSendData, 
		int dataLength);//发送命令
	
	//发送数据到通信连接
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

	CBuffList<CRFrame> m_IOStateBuffer; //IO状态列表
	CBuffList<CRFrame> m_CardIDBuffer;  //卡列表

	CCmdBuffer* m_RecvMsgFrame;	//指令

	ReadState m_ReadState;
	
	unsigned long mLastTime;

	CLock m_Critical;	//send lock
	unsigned char mForSend[CMD_DATA_BUFFER];
	int mForSendLen;

	map<DWORD,int> map_Error;
};
