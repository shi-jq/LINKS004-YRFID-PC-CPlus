#pragma once
#include "Global.h"
#include "TcpServerConn.h"
#include "Lock.h"
#include "RFIDReader.h"

class CRFIDReaderServer
{
	friend CTcpServerConn;
public:
	CRFIDReaderServer();
	~CRFIDReaderServer();
	
	//开始监听服务端
	bool StartListen(char *pHostName,int nsocketPort,READER_CALLBACK pCallBack);
	//停止监听
	bool StopListen();

	//添加一个TCP 客户端
	bool AddTcpCLient(char *pIpAddr,int nPort,READER_CALLBACK pCallBack);
	
	//添加一个Udp 客户端
	bool AddUdpCLient(char *pIpAddr,int nPort,READER_CALLBACK pCallBack);

	//添加一个串口 
	bool AddComReader(unsigned char nBusAddr,char *pComNum,int nBaud,READER_CALLBACK pCallBack);

	//添加一个USB 
	bool AddUSBReader(unsigned char nBusAddr,char *pComNum,int nBaud,READER_CALLBACK pCallBack);

	void ClearAllReader();
	//退出
	bool Quit();

	bool CloseReader(WirelessReaderInfo*	pWirelessReaderInfo);
	void ClearErrorCode();//清除错误信息
	void SetErrorCode(int nErrorCode,bool bCommandError = false);//设置错误码
	
	////发送指令
	bool SendMsg(WirelessReaderInfo*	pWirelessReaderInfo,
		unsigned char pCommand,
		unsigned char *pSendData, 
		int dataLength);
	////获取回复数据
	bool GetMsgResult(WirelessReaderInfo*	pWirelessReaderInfo,
		CRFrame &pRevFrame);//得到返回结果

public:
	//读写器操作
	/***********************************系统信息配置******************************************/
	bool SAATSysInfSet (WirelessReaderInfo* pWirelessReaderInfo,
		unsigned char nType,
		unsigned char* pParm,
		int nLen);//系统信息设置
	
	bool SAATSysInfQuery (
		WirelessReaderInfo* pWirelessReaderInfo,
		unsigned char nType);//系统信息查询

	bool SAATRFParaSet(
		WirelessReaderInfo* pWirelessReaderInfo,
		unsigned char nType, 
		unsigned char nParaLen,
		unsigned char* pPara);//载波参数配置

	bool SAATRFParaQuery(
		WirelessReaderInfo* pWirelessReaderInfo,
		unsigned char nType);// 载波参数查询

	bool SAATAntennaParmQuery (WirelessReaderInfo* pWirelessReaderInfo);//指定射频端口参数查询
	
	bool SAATAntennaParmSet(WirelessReaderInfo* pWirelessReaderInfo,
		unsigned char *pPara,unsigned char nLen );//射频端口参数配置

	bool SAATParmOp(
		WirelessReaderInfo* pWirelessReaderInfo,
		unsigned char nType, 
		unsigned char nStartAddrr, 
		unsigned char nLen, 
		unsigned char *pData,
		unsigned char *pDataLen,
		int* nMsgID);//系统参数表操作

	bool SAATTagOpParaSet(WirelessReaderInfo* pWirelessReaderInfo,
		unsigned char nType,
		unsigned char *pPara,
		unsigned char nLen);//标签操作参数配置
	
	bool SAATTagOpParaQuery (WirelessReaderInfo* pWirelessReaderInfo,
		unsigned char nType);//标签操作参数查询

	bool SAATClearFlash(WirelessReaderInfo* pWirelessReaderInfo);//清flash缓存
	bool SAATFlashDataQuery(WirelessReaderInfo* pWirelessReaderInfo,
		unsigned char nOpType);//FLASH存储数据查询
	bool SAATFlashTotalCountQuery (WirelessReaderInfo* pWirelessReaderInfo);//FLASH存储数据总数查询

	bool SAATIOOperate(WirelessReaderInfo* pWirelessReaderInfo,
		unsigned char nPort,unsigned char nState);// IO输出操作

	bool SAATTotalAntennaParmQuery (WirelessReaderInfo* pWirelessReaderInfo);//射频端口参数查询

	bool SAATYMakeTagUpLoadIDCode (WirelessReaderInfo* pWirelessReaderInfo,
		unsigned char nOpType,
		unsigned char nIDType);//主动上传

	bool SAATYReadIDCode(WirelessReaderInfo* pWirelessReaderInfo,
		unsigned char nOpType,
		unsigned char nIDType,
		unsigned int nTagCount);//被动上传

	int  SAATYRevIDMsgDecRssiExpand(
		WirelessReaderInfo* pWirelessReaderInfo,
		unsigned char* nTime,
		unsigned char* nTagType,
		unsigned int* pId,
		int* nRssi,
		int* nAntenna,
		int* nParam1,
		int* nParam2);


	bool PowerOff(WirelessReaderInfo* pWirelessReaderInfo);

	bool YPowerOff(WirelessReaderInfo* pWirelessReaderInfo);

	bool SAATCarrierWaveOp(WirelessReaderInfo* pWirelessReaderInfo,
		unsigned char nType, unsigned char  nPort);//载波操作
	
	bool GetLastTime(WirelessReaderInfo* pWirelessReaderInfo,unsigned long& nTime);

	bool SAATReadIOState(WirelessReaderInfo* pWirelessReaderInfo,unsigned char* pStateData, unsigned char* nStateLen);

	bool SAATHeartSend (WirelessReaderInfo* pWirelessReaderInfo);//心跳检测

	bool SAATReboot(WirelessReaderInfo* pWirelessReaderInfo,unsigned char nMode);//重启读写器

	bool SAATReaderTimeQuery(WirelessReaderInfo* pWirelessReaderInfo);//查询读写器系统时间
	bool SAATSetReaderTime(WirelessReaderInfo* pWirelessReaderInfo,
		unsigned char *pPara,
		unsigned char nLen);//设置读写器系统时间

	bool SAATReadingIOConfig (WirelessReaderInfo* pWirelessReaderInfo,
		unsigned char nConfigBit);//读卡指示配置
	bool SAATReadingIOQuery (WirelessReaderInfo* pWirelessReaderInfo);//读卡指示查询
	bool SAATIOPulseWidthSet (WirelessReaderInfo* pWirelessReaderInfo,
		unsigned char nIOPort,
		unsigned char nWidth);
	
	bool SAATIOPulseWidthQuery (WirelessReaderInfo* pWirelessReaderInfo,
		unsigned char nIOPort);

	bool SAATYAntennaPortEXSet(WirelessReaderInfo* pWirelessReaderInfo,
		unsigned int nPortEnable,
		unsigned int nPollTime,
		unsigned int nParam); 
	bool SAATYAntennaPortEXQuery(WirelessReaderInfo* pWirelessReaderInfo); 

	bool SAATYAntennaParmQuery(
		WirelessReaderInfo* pWirelessReaderInfo);//天线参数查询
	bool SAATYAntennaParmSet(
		WirelessReaderInfo* pWirelessReaderInfo,
		unsigned char *pPara,unsigned char nLen );//天线参数设置

	bool SAATYRFParaSet (
		WirelessReaderInfo* pWirelessReaderInfo,
		unsigned char nType,
		unsigned char nPara);//载波参数设置
	bool SAATYRFParaQuery (
		WirelessReaderInfo* pWirelessReaderInfo,
		unsigned char nType);//载波参数查询

protected:
	//创建读写器,tcpServer 返回的,监听到的读写器
	bool CreateReaderThread(SOCKET& sockConn,const SOCKADDR_IN& socktAddr);
	
private:
	CRFIDReader* GetComRFIDReader(int readerType,unsigned  char* strComNum,int nBaud);
	CRFIDReader* GetTcpRFIDReader(int readerType,unsigned  char* strIpadd,int nPort);
	CRFIDReader* GetRFIDReader(WirelessReaderInfo* pWirelessReaderInfo);
	void AddReaderList(WirelessReaderInfo* pWirelessReaderInfo,CRFIDReader* pCRFIDReader);
	void DeleteReader(WirelessReaderInfo* pWirelessReaderInfo);
	void DeleteReader(CRFIDReader* pCRFIDReader);
	

	byte C10Convert16(byte a);
private:
	CTcpServerConn*  mCTcpServerConn;

	//ConnetCreater* mConnetCreater;

	CLock mReadListLock;
	std::map<WirelessReaderInfo*,CRFIDReader*> mReaderList;  //接收到的读写器列表

	READER_CALLBACK mCallBack;
};
