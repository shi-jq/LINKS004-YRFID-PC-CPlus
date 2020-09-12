#pragma once
#include "Global.h"
#include "IReader.h"
#include "IConnect.h"
#include "DataProc.h"
#include "CmdBuffer.h"
#include "BuffList.h"
#include "./language/MsgManager.h"

class CRFIDReader : IReader
{
public:
	CRFIDReader();
	~CRFIDReader();
	bool InitCom(int nComPort, int nBute);//��ʼ��COM
	bool InitTcp(void);//��ʼ��TCP
	bool InitUsb(void);//��ʼ��USB
	bool SAATHeartSend ();//�������
	bool TestHeart() ;//�������ͬ��
	bool InitCFG(CRFIDSystemCfg& cfg);//��ʼ��CRFIDSystemCfg
	bool Open(CRFIDSystemCfg& cfg);//�򿪶�д��
	bool Open();//�򿪶�д��
	bool Close(void);//�رն�д��
	bool Reconnect();//�������Ӷ�д��

	/***********************************ϵͳ��Ϣ����******************************************/
	bool SAATSysInfSet (unsigned char nType,unsigned char* pParm,int nLen);//ϵͳ��Ϣ����
	bool SAATSysInfQuery (unsigned char nType, unsigned char *pPara, unsigned char *pLen);//ϵͳ��Ϣ��ѯ
	bool SAATWorkModeSet (unsigned char nType);//����ģʽ����
	bool SAATParmOp(unsigned char nType, 
				unsigned char nStartAddrr, 
				unsigned char nLen, 
				unsigned char *pData,
				unsigned char *pDataLen);//ϵͳ���������
	bool SAATRFParaSet(unsigned char nType, unsigned char nParaLen,unsigned char* pPara);//�ز���������
	bool SAATRFParaQuery(unsigned char nType,unsigned char* pPara, unsigned char *pLen);// �ز�������ѯ
	bool SAATCommunicatParaSet (unsigned char nType, unsigned char* pPara, unsigned char nLen);//ͨѶ��������
	bool SAATCommunicatParaQuery (unsigned char nType, unsigned char* pPara,unsigned char *pLen);//ͨѶ������ѯ
	bool SAATNetParaSet (unsigned char nType, unsigned char* pPara, unsigned char nLen);//�����������
	bool SAATNetParaQuery (int nType, unsigned char* pPara,unsigned char *pLen);//���������ѯ
	bool SAATTagOpParaSet(unsigned char nType, unsigned char *pPara,unsigned char nLen);//��ǩ������������
	bool SAATTagOpParaQuery (unsigned char nType, unsigned char* pPara, unsigned char *pLen);//��ǩ����������ѯ
	bool SAATExtendBroadParaSet (unsigned char nType, unsigned char pSendChunnel);//��չ���������
	bool SAATExtendBroadParaQuery (unsigned char nType, char* pPara, unsigned char* pLen);//��չ�������ѯ
	bool SAATTotalAntennaParmQuery (unsigned char *szAntennaPara,unsigned char *pLen);//��Ƶ�˿ڲ�����ѯ
	bool SAATAntennaParmQuery (unsigned char nAntenna,
							unsigned char * pAntennaEnable,
							unsigned char *pAntennaPower,
							unsigned char *pAntennaQueryTime );//ָ����Ƶ�˿ڲ�����ѯ
	bool SAATAntennaParmSet(unsigned char *pPara,unsigned char nLen );//��Ƶ�˿ڲ�������
	bool SAATSetAntennaPortEnable (unsigned char nAntenna,unsigned char nEnable );//ָ����Ƶ�˿�ʹ������
	bool SAATSetAntennaPower (unsigned char nAntenna,unsigned char nPower );//ָ����Ƶ�˿ڹ�������
	bool SAATSetAntennaTime (unsigned char nAntenna,unsigned char nTime );//ָ����Ƶ�˿���ѯʱ������
	bool SAATYAntennaParmQuery(unsigned char* pPowerRecvPlus, unsigned char* p2401FreqSendPwr, unsigned char* pAttenuatorPower);
	bool PowerOff();//ֹͣ����
	bool Stop(void);//ֹͣ����
	void ClearErrorCode();//���������Ϣ
	void GetErrorMsg(char *szMsg,int nLen);// ��ȡ������Ϣ
	int	 GetErrorCode();//��ȡ�������
	bool SAATCarrierWaveOp(unsigned char nType, unsigned char  nPort);//�ز�����
	bool SAATIOOperate(unsigned char nPort,unsigned char nState);// IO�������
	bool SAATIOStateQuery(unsigned char *pState);//IO�����ѯ
	bool SAATReboot(unsigned char nMode);//������д��
	bool SAATReadingIOConfig (unsigned char nConfigBit);//����ָʾ����
	bool SAATReadingIOQuery (unsigned char* pConfigBit);//����ָʾ��ѯ
	bool SAATIOPulseWidthSet (unsigned char nIOPort,unsigned char nWidth);
	bool SAATIOPulseWidthQuery (unsigned char nIOPort,unsigned char* pWidth);
	/***********************************ϵͳ��Ϣ����******************************************/

	/***********************************6B����************************************************/
	bool SAAT6BTagSelect ( unsigned char nType,
							unsigned char nStartAddr,
							unsigned char nDataBite,
							unsigned char * Data );//��ǩѡ���������
	bool SAAT6BReadUIDCode (unsigned char nAntenna,unsigned char nType);//����ǩUID��
	int SAAT6BRevUIDMsg ( unsigned char* nAntenna, unsigned char* pUIDData,unsigned char* nUIDLen);//���ձ�ǩUID��
	bool SAAT6BReadUserData ( unsigned char nAntenna,
		unsigned char nType,
		unsigned char * pTagID,
		unsigned char nStartAddr,
		unsigned char nReadLen,
		unsigned char *pdata,
		unsigned char dataLen);//����ǩ����������
	bool SAAT6BWriteUserData (unsigned char nAntenna,
		unsigned char nType, 
		unsigned char *pTagID,
		unsigned char nStartAddr,
		unsigned char *pValue, 
		unsigned char *pLen);//д��ǩ����
	bool SAAT6BTagLock (unsigned char nAntenna, 
		unsigned char nType,
		unsigned char *pTagID, 
		unsigned char nStartAddrr,
		unsigned char nLen);//������ǩ������
	bool SAAT6BTagLockQuery (unsigned char nAntenna, 
		unsigned char *pTagID, 
		unsigned char nStartAddr,
		unsigned char nLen,
		unsigned char *pData,
		unsigned char nDataLen);//��ѯ��ǩ��������״̬
	/***********************************6B����************************************************/


	bool SAATYMakeTagUpLoadIDCode(unsigned char nOpType, unsigned char nIDType);
	int SAATYRevIDMsgDecRssiExpand(unsigned char* nTagType,
		unsigned int* pId, 
		int* nRssi, 
		int* nAntenna, 
		int* nParam1,
		int* nParam2);


	/***********************************6C����************************************************/
	bool SAAT6CTagSelect ( unsigned char nBank ,unsigned short nStartAddr,unsigned char MaskBit, 
		unsigned char *Data ,unsigned char Datalength,unsigned char nSessionZone,
		unsigned char nActiveFlag, unsigned char nCutFlag );//��ǩѡ���������
	bool SAAT6CReadEPCCode( unsigned char nAntenna, unsigned char nType,unsigned int nTagCount);//��ȡ��ǩEPC��
	int  SAAT6CRevEPCMsg(unsigned char* nAntenna, unsigned char* pEPCData, unsigned char* nEPCLen);//����EPC��
	bool SAAT6CReadTIDCode ( unsigned char nAntenna, unsigned char nType, unsigned int nTagCount);//����ǩTID��
	int SAAT6CRevTIDMsg (unsigned char* nAntenna, unsigned char* pTIDData, unsigned char* nTIDLen);//���ձ�ǩTID��
	bool SAAT6CReadEPCTIDCode( unsigned char nAntenna, unsigned char nType,unsigned int nTagCount);//��ȡ��ǩEPC��
	int  SAAT6CRevEPCTIDMsg(unsigned char* nAntenna, unsigned char* pEPCData, unsigned char* nEPCLen,
		unsigned char* pTIDData, unsigned char* nTIDLen);//ͬʱ����EPC+TID��
	bool WriteEPCCode(unsigned char nAntenna,
		unsigned char nType,
		unsigned char *pAccessPWD, 
		unsigned char *pWriteData,
		unsigned char nLen);//дEPC��
	bool SAAT6CReadUserData ( unsigned char nAntenna, 
		unsigned int StartAddr,
		unsigned int nToReadLen,
		unsigned int nWaitTime,
		unsigned char * UserData,
		unsigned int* pDataLen);//���û�������
	bool SAAT6CWriteUserData (unsigned char nAntenna, 
		unsigned char nType,  
		unsigned char *pAccessPWD,
		unsigned int  nStartAddr,
		unsigned int nWaitTime,
		unsigned char *pWriteData, 
		unsigned int *pToWriteLen);//д�û�������
	bool SAAT6CWriteBankData (unsigned char nAntenna, 
								unsigned char nType, 
								unsigned char *pAccessPWD,
								unsigned char nBank,  
								unsigned char *pWriteData, 
								unsigned char nLen);//��дBank����
	bool SAAT6CClearBankData (unsigned char nAntenna, unsigned char nType, unsigned char *pAccessPWD,
		unsigned char nBank, unsigned char nStartAddr, unsigned char nLen);//���Bank����
	bool SAAT6CAccessPWDSet (unsigned char nAntenna, 
							unsigned char nType, 
							unsigned char *pOrgPWD, 
							unsigned char *pNewPWD);//���÷�������
	bool SAAT6CDestroyPWDSet ( unsigned char nAntenna,
		unsigned char nType, 
		unsigned char *pAccessPWD, 
		unsigned char *pDestroyPWD );//������������
	bool SAAT6CTagLock (unsigned char nAntenna,
		unsigned char *pAccessPWD, 
		unsigned char nType,
		unsigned char nBank);//��ǩ��״̬����
	bool SAAT6CTagKill (unsigned char nAntenna,
		unsigned char *pDestroyPWD,
		unsigned char *pEPC, 
		int nEPCLen);//��ǩ����
	bool SAAT6CEASFlagSet (unsigned char nAntenna, 
		unsigned char nType,
		unsigned char* pAccessPwd, 
		int nEASFlag);//EAS��־λ����
	bool SAAT6CEASMonitorEnable (unsigned char nAntenna,unsigned char nSetEAS);//����EAS���
	int SAAT6CRevEasMsg (unsigned char* nAntenna, unsigned char* pEasData,
		unsigned char* nEasLen);
	/***********************************6C����************************************************/

	/***********************************����ģ��ָ��******************************************/
	bool SAATGPRSParaSet (unsigned char nType, unsigned char* pPara, unsigned char nLen);
	bool SAATGPRSParaQuery (int nType, unsigned char* pPara,unsigned char *pLen);
	bool SAATWIFIParaSet (unsigned char nType, unsigned char* pPara, unsigned char nLen);
	bool SAATWIFIParaQuery (int nType, unsigned char* pPara,unsigned char *pLen);
	/***********************************����ģ��ָ��******************************************/

	bool SAATCopyright(char* copyright);//API�汾��Ϣ��ѯ
	bool SAATSetLanguageType (char* szType);//����API��̬����������
	bool SAATSysTest(unsigned char nType,unsigned char nAntenna, unsigned char *pTestParm, unsigned char nLen);

	bool SendNRevMsg(unsigned char *pSendCommand, 
		unsigned char *pSendData, 
		int dataLength,
		CRFIDFrame &pRevFrame,
		int nWaitTime = 3000);//�շ�����
	char* GetProuctSN();//�õ����к�
	void SetProuctSN(char* szName);//�������к�
	IConnect* CRFIDReader::ConcreteConn(CRFIDSystemCfg& cfg);//����CRFIDReader����
	bool SetMsgResult(CRFrame& RFIDFrame);//���÷��ؽ��
	bool CheckMsg(unsigned char nCommand);//�������
	bool SendMsg(unsigned char *pCommand,unsigned char *pSendData, int dataLength,CRFIDFrame &pRevFrame);//��������
	bool GetMsgResult(CRFIDFrame &pRevFrame,int nWaitTime = 3000);//�õ����ؽ��
	void SetErrorCode (int iErrorCode,bool bCommandError = false);//���ô�����
	bool CheckIsReadCardCommand(unsigned char nCommand);//����Ƿ����ָ��
	bool GetCard(CRFrame& RFIDFrame,int nWaitTime);//��ȡ��ǰ����	
	CMsgManager msgError;
	bool SAATRawSendData(unsigned char *pSendData, unsigned char nLen);
	bool SAATRawRevData(unsigned char *pRecvData, unsigned char* pLen,int nWaitTime);
	bool SAATRawSendAndRevData(void* pHandle , 
							unsigned char *pSendData,
							unsigned char nLen,
							unsigned char *pRecvData,
							unsigned char *pLen,
							unsigned char nWaitTime);
	bool SAATEnterTrans(unsigned char nType);
	bool SAATResetWifiBaund();
protected:
private:
	bool WriteEPCCode_Raw(unsigned char nAntenna,
		unsigned char nType,
		unsigned char *pAccessPWD, 
		unsigned char *pWriteData,
		unsigned char nLen);//�ײ�дEPC��
	bool SAAT6CRawReadUserData ( unsigned char nAntenna, unsigned int StartAddr,
		unsigned char nToReadLen, unsigned char * UserData,unsigned int* pDataLen);//�ײ��6C����

	bool SAAT6CRawWriteUserData (unsigned char nAntenna, 
		unsigned char nType,  
		unsigned char *pAccessPWD,
		unsigned int  nStartAddr,
		unsigned char *pWriteData, 
		unsigned char *pLen);////�ײ�д6C����
	map<DWORD,int> map_Error;
	bool m_bOpen;
	char m_szProductSN[READER_PROUCTNAME_LEN];
	CDataProc m_DataProcss;
	CCmdBuffer m_cmdBuffer;
	CBuffList<CRFrame> m_CardIDBuffer;
	
	int m_nErrorCode;
	bool m_bCommandError;
	ReadState m_ReadState;
	//CRFIDFrame m_ReadCardFrame;//���Ͷ���֡����
	CRITICAL_SECTION m_Critical;
	CRFIDSystemCfg m_sysCfg;

public:
	bool SAATClearFlash();//��flash����
	bool SAATFlashDataQuery(unsigned char nOpType, unsigned char* pPara, unsigned char *pLen);//FLASH�洢���ݲ�ѯ
	bool SAATFlashTotalCountQuery (unsigned char* pPara,unsigned char *pLen);//FLASH�洢����������ѯ

	bool SAATReaderTimeQuery(unsigned char *pPara, unsigned char *pLen);//��ѯ��д��ϵͳʱ��
	bool SAATSetReaderTime(unsigned char *pPara, unsigned char nLen);//���ö�д��ϵͳʱ��
	
};
