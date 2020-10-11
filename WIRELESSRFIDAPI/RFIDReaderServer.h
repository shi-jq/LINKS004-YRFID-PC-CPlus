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
	
	//��ʼ���������
	bool StartListen(char *pHostName,int nsocketPort,READER_CALLBACK pCallBack);
	//ֹͣ����
	bool StopListen();

	//���һ��TCP �ͻ���
	bool AddTcpCLient(char *pIpAddr,int nPort,READER_CALLBACK pCallBack);
	
	//���һ��Udp �ͻ���
	bool AddUdpCLient(char *pIpAddr,int nPort,READER_CALLBACK pCallBack);

	//���һ������ 
	bool AddComReader(unsigned char nBusAddr,char *pComNum,int nBaud,READER_CALLBACK pCallBack);

	//���һ��USB 
	bool AddUSBReader(unsigned char nBusAddr,char *pComNum,int nBaud,READER_CALLBACK pCallBack);

	void ClearAllReader();
	//�˳�
	bool Quit();

	bool CloseReader(WirelessReaderInfo*	pWirelessReaderInfo);
	void ClearErrorCode();//���������Ϣ
	void SetErrorCode(int nErrorCode,bool bCommandError = false);//���ô�����
	
	////����ָ��
	bool SendMsg(WirelessReaderInfo*	pWirelessReaderInfo,
		unsigned char pCommand,
		unsigned char *pSendData, 
		int dataLength);
	////��ȡ�ظ�����
	bool GetMsgResult(WirelessReaderInfo*	pWirelessReaderInfo,
		CRFrame &pRevFrame);//�õ����ؽ��

public:
	//��д������
	/***********************************ϵͳ��Ϣ����******************************************/
	bool SAATSysInfSet (WirelessReaderInfo* pWirelessReaderInfo,
		unsigned char nType,
		unsigned char* pParm,
		int nLen);//ϵͳ��Ϣ����
	
	bool SAATSysInfQuery (
		WirelessReaderInfo* pWirelessReaderInfo,
		unsigned char nType);//ϵͳ��Ϣ��ѯ

	bool SAATRFParaSet(
		WirelessReaderInfo* pWirelessReaderInfo,
		unsigned char nType, 
		unsigned char nParaLen,
		unsigned char* pPara);//�ز���������

	bool SAATRFParaQuery(
		WirelessReaderInfo* pWirelessReaderInfo,
		unsigned char nType);// �ز�������ѯ

	bool SAATAntennaParmQuery (WirelessReaderInfo* pWirelessReaderInfo);//ָ����Ƶ�˿ڲ�����ѯ
	
	bool SAATAntennaParmSet(WirelessReaderInfo* pWirelessReaderInfo,
		unsigned char *pPara,unsigned char nLen );//��Ƶ�˿ڲ�������

	bool SAATParmOp(
		WirelessReaderInfo* pWirelessReaderInfo,
		unsigned char nType, 
		unsigned char nStartAddrr, 
		unsigned char nLen, 
		unsigned char *pData,
		unsigned char *pDataLen,
		int* nMsgID);//ϵͳ���������

	bool SAATTagOpParaSet(WirelessReaderInfo* pWirelessReaderInfo,
		unsigned char nType,
		unsigned char *pPara,
		unsigned char nLen);//��ǩ������������
	
	bool SAATTagOpParaQuery (WirelessReaderInfo* pWirelessReaderInfo,
		unsigned char nType);//��ǩ����������ѯ

	bool SAATClearFlash(WirelessReaderInfo* pWirelessReaderInfo);//��flash����
	bool SAATFlashDataQuery(WirelessReaderInfo* pWirelessReaderInfo,
		unsigned char nOpType);//FLASH�洢���ݲ�ѯ
	bool SAATFlashTotalCountQuery (WirelessReaderInfo* pWirelessReaderInfo);//FLASH�洢����������ѯ

	bool SAATIOOperate(WirelessReaderInfo* pWirelessReaderInfo,
		unsigned char nPort,unsigned char nState);// IO�������

	bool SAATTotalAntennaParmQuery (WirelessReaderInfo* pWirelessReaderInfo);//��Ƶ�˿ڲ�����ѯ

	bool SAATYMakeTagUpLoadIDCode (WirelessReaderInfo* pWirelessReaderInfo,
		unsigned char nOpType,
		unsigned char nIDType);//�����ϴ�

	bool SAATYReadIDCode(WirelessReaderInfo* pWirelessReaderInfo,
		unsigned char nOpType,
		unsigned char nIDType,
		unsigned int nTagCount);//�����ϴ�

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
		unsigned char nType, unsigned char  nPort);//�ز�����
	
	bool GetLastTime(WirelessReaderInfo* pWirelessReaderInfo,unsigned long& nTime);

	bool SAATReadIOState(WirelessReaderInfo* pWirelessReaderInfo,unsigned char* pStateData, unsigned char* nStateLen);

	bool SAATHeartSend (WirelessReaderInfo* pWirelessReaderInfo);//�������

	bool SAATReboot(WirelessReaderInfo* pWirelessReaderInfo,unsigned char nMode);//������д��

	bool SAATReaderTimeQuery(WirelessReaderInfo* pWirelessReaderInfo);//��ѯ��д��ϵͳʱ��
	bool SAATSetReaderTime(WirelessReaderInfo* pWirelessReaderInfo,
		unsigned char *pPara,
		unsigned char nLen);//���ö�д��ϵͳʱ��

	bool SAATReadingIOConfig (WirelessReaderInfo* pWirelessReaderInfo,
		unsigned char nConfigBit);//����ָʾ����
	bool SAATReadingIOQuery (WirelessReaderInfo* pWirelessReaderInfo);//����ָʾ��ѯ
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
		WirelessReaderInfo* pWirelessReaderInfo);//���߲�����ѯ
	bool SAATYAntennaParmSet(
		WirelessReaderInfo* pWirelessReaderInfo,
		unsigned char *pPara,unsigned char nLen );//���߲�������

	bool SAATYRFParaSet (
		WirelessReaderInfo* pWirelessReaderInfo,
		unsigned char nType,
		unsigned char nPara);//�ز���������
	bool SAATYRFParaQuery (
		WirelessReaderInfo* pWirelessReaderInfo,
		unsigned char nType);//�ز�������ѯ

protected:
	//������д��,tcpServer ���ص�,�������Ķ�д��
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
	std::map<WirelessReaderInfo*,CRFIDReader*> mReaderList;  //���յ��Ķ�д���б�

	READER_CALLBACK mCallBack;
};
