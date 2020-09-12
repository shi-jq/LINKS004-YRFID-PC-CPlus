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
	bool InitCom(int nComPort, int nBute);//初始化COM
	bool InitTcp(void);//初始化TCP
	bool InitUsb(void);//初始化USB
	bool SAATHeartSend ();//心跳检测
	bool TestHeart() ;//心跳检测同上
	bool InitCFG(CRFIDSystemCfg& cfg);//初始化CRFIDSystemCfg
	bool Open(CRFIDSystemCfg& cfg);//打开读写器
	bool Open();//打开读写器
	bool Close(void);//关闭读写器
	bool Reconnect();//重新连接读写器

	/***********************************系统信息配置******************************************/
	bool SAATSysInfSet (unsigned char nType,unsigned char* pParm,int nLen);//系统信息设置
	bool SAATSysInfQuery (unsigned char nType, unsigned char *pPara, unsigned char *pLen);//系统信息查询
	bool SAATWorkModeSet (unsigned char nType);//工作模式配置
	bool SAATParmOp(unsigned char nType, 
				unsigned char nStartAddrr, 
				unsigned char nLen, 
				unsigned char *pData,
				unsigned char *pDataLen);//系统参数表操作
	bool SAATRFParaSet(unsigned char nType, unsigned char nParaLen,unsigned char* pPara);//载波参数配置
	bool SAATRFParaQuery(unsigned char nType,unsigned char* pPara, unsigned char *pLen);// 载波参数查询
	bool SAATCommunicatParaSet (unsigned char nType, unsigned char* pPara, unsigned char nLen);//通讯参数配置
	bool SAATCommunicatParaQuery (unsigned char nType, unsigned char* pPara,unsigned char *pLen);//通讯参数查询
	bool SAATNetParaSet (unsigned char nType, unsigned char* pPara, unsigned char nLen);//网络参数配置
	bool SAATNetParaQuery (int nType, unsigned char* pPara,unsigned char *pLen);//网络参数查询
	bool SAATTagOpParaSet(unsigned char nType, unsigned char *pPara,unsigned char nLen);//标签操作参数配置
	bool SAATTagOpParaQuery (unsigned char nType, unsigned char* pPara, unsigned char *pLen);//标签操作参数查询
	bool SAATExtendBroadParaSet (unsigned char nType, unsigned char pSendChunnel);//扩展板参数配置
	bool SAATExtendBroadParaQuery (unsigned char nType, char* pPara, unsigned char* pLen);//扩展板参数查询
	bool SAATTotalAntennaParmQuery (unsigned char *szAntennaPara,unsigned char *pLen);//射频端口参数查询
	bool SAATAntennaParmQuery (unsigned char nAntenna,
							unsigned char * pAntennaEnable,
							unsigned char *pAntennaPower,
							unsigned char *pAntennaQueryTime );//指定射频端口参数查询
	bool SAATAntennaParmSet(unsigned char *pPara,unsigned char nLen );//射频端口参数配置
	bool SAATSetAntennaPortEnable (unsigned char nAntenna,unsigned char nEnable );//指定射频端口使能配置
	bool SAATSetAntennaPower (unsigned char nAntenna,unsigned char nPower );//指定射频端口功率配置
	bool SAATSetAntennaTime (unsigned char nAntenna,unsigned char nTime );//指定射频端口轮询时间配置
	bool SAATYAntennaParmQuery(unsigned char* pPowerRecvPlus, unsigned char* p2401FreqSendPwr, unsigned char* pAttenuatorPower);
	bool PowerOff();//停止读卡
	bool Stop(void);//停止读卡
	void ClearErrorCode();//清除错误信息
	void GetErrorMsg(char *szMsg,int nLen);// 获取出错信息
	int	 GetErrorCode();//获取出错代码
	bool SAATCarrierWaveOp(unsigned char nType, unsigned char  nPort);//载波操作
	bool SAATIOOperate(unsigned char nPort,unsigned char nState);// IO输出操作
	bool SAATIOStateQuery(unsigned char *pState);//IO输入查询
	bool SAATReboot(unsigned char nMode);//重启读写器
	bool SAATReadingIOConfig (unsigned char nConfigBit);//读卡指示配置
	bool SAATReadingIOQuery (unsigned char* pConfigBit);//读卡指示查询
	bool SAATIOPulseWidthSet (unsigned char nIOPort,unsigned char nWidth);
	bool SAATIOPulseWidthQuery (unsigned char nIOPort,unsigned char* pWidth);
	/***********************************系统信息配置******************************************/

	/***********************************6B操作************************************************/
	bool SAAT6BTagSelect ( unsigned char nType,
							unsigned char nStartAddr,
							unsigned char nDataBite,
							unsigned char * Data );//标签选择参数配置
	bool SAAT6BReadUIDCode (unsigned char nAntenna,unsigned char nType);//读标签UID码
	int SAAT6BRevUIDMsg ( unsigned char* nAntenna, unsigned char* pUIDData,unsigned char* nUIDLen);//接收标签UID码
	bool SAAT6BReadUserData ( unsigned char nAntenna,
		unsigned char nType,
		unsigned char * pTagID,
		unsigned char nStartAddr,
		unsigned char nReadLen,
		unsigned char *pdata,
		unsigned char dataLen);//读标签数据区数据
	bool SAAT6BWriteUserData (unsigned char nAntenna,
		unsigned char nType, 
		unsigned char *pTagID,
		unsigned char nStartAddr,
		unsigned char *pValue, 
		unsigned char *pLen);//写标签数据
	bool SAAT6BTagLock (unsigned char nAntenna, 
		unsigned char nType,
		unsigned char *pTagID, 
		unsigned char nStartAddrr,
		unsigned char nLen);//锁定标签数据区
	bool SAAT6BTagLockQuery (unsigned char nAntenna, 
		unsigned char *pTagID, 
		unsigned char nStartAddr,
		unsigned char nLen,
		unsigned char *pData,
		unsigned char nDataLen);//查询标签数据区锁状态
	/***********************************6B操作************************************************/


	bool SAATYMakeTagUpLoadIDCode(unsigned char nOpType, unsigned char nIDType);
	int SAATYRevIDMsgDecRssiExpand(unsigned char* nTagType,
		unsigned int* pId, 
		int* nRssi, 
		int* nAntenna, 
		int* nParam1,
		int* nParam2);


	/***********************************6C操作************************************************/
	bool SAAT6CTagSelect ( unsigned char nBank ,unsigned short nStartAddr,unsigned char MaskBit, 
		unsigned char *Data ,unsigned char Datalength,unsigned char nSessionZone,
		unsigned char nActiveFlag, unsigned char nCutFlag );//标签选择参数设置
	bool SAAT6CReadEPCCode( unsigned char nAntenna, unsigned char nType,unsigned int nTagCount);//读取标签EPC码
	int  SAAT6CRevEPCMsg(unsigned char* nAntenna, unsigned char* pEPCData, unsigned char* nEPCLen);//接收EPC码
	bool SAAT6CReadTIDCode ( unsigned char nAntenna, unsigned char nType, unsigned int nTagCount);//读标签TID码
	int SAAT6CRevTIDMsg (unsigned char* nAntenna, unsigned char* pTIDData, unsigned char* nTIDLen);//接收标签TID码
	bool SAAT6CReadEPCTIDCode( unsigned char nAntenna, unsigned char nType,unsigned int nTagCount);//读取标签EPC码
	int  SAAT6CRevEPCTIDMsg(unsigned char* nAntenna, unsigned char* pEPCData, unsigned char* nEPCLen,
		unsigned char* pTIDData, unsigned char* nTIDLen);//同时接收EPC+TID码
	bool WriteEPCCode(unsigned char nAntenna,
		unsigned char nType,
		unsigned char *pAccessPWD, 
		unsigned char *pWriteData,
		unsigned char nLen);//写EPC码
	bool SAAT6CReadUserData ( unsigned char nAntenna, 
		unsigned int StartAddr,
		unsigned int nToReadLen,
		unsigned int nWaitTime,
		unsigned char * UserData,
		unsigned int* pDataLen);//读用户数据区
	bool SAAT6CWriteUserData (unsigned char nAntenna, 
		unsigned char nType,  
		unsigned char *pAccessPWD,
		unsigned int  nStartAddr,
		unsigned int nWaitTime,
		unsigned char *pWriteData, 
		unsigned int *pToWriteLen);//写用户数据区
	bool SAAT6CWriteBankData (unsigned char nAntenna, 
								unsigned char nType, 
								unsigned char *pAccessPWD,
								unsigned char nBank,  
								unsigned char *pWriteData, 
								unsigned char nLen);//块写Bank数据
	bool SAAT6CClearBankData (unsigned char nAntenna, unsigned char nType, unsigned char *pAccessPWD,
		unsigned char nBank, unsigned char nStartAddr, unsigned char nLen);//块擦Bank数据
	bool SAAT6CAccessPWDSet (unsigned char nAntenna, 
							unsigned char nType, 
							unsigned char *pOrgPWD, 
							unsigned char *pNewPWD);//配置访问密码
	bool SAAT6CDestroyPWDSet ( unsigned char nAntenna,
		unsigned char nType, 
		unsigned char *pAccessPWD, 
		unsigned char *pDestroyPWD );//更改销毁密码
	bool SAAT6CTagLock (unsigned char nAntenna,
		unsigned char *pAccessPWD, 
		unsigned char nType,
		unsigned char nBank);//标签锁状态配置
	bool SAAT6CTagKill (unsigned char nAntenna,
		unsigned char *pDestroyPWD,
		unsigned char *pEPC, 
		int nEPCLen);//标签销毁
	bool SAAT6CEASFlagSet (unsigned char nAntenna, 
		unsigned char nType,
		unsigned char* pAccessPwd, 
		int nEASFlag);//EAS标志位配置
	bool SAAT6CEASMonitorEnable (unsigned char nAntenna,unsigned char nSetEAS);//启动EAS监控
	int SAAT6CRevEasMsg (unsigned char* nAntenna, unsigned char* pEasData,
		unsigned char* nEasLen);
	/***********************************6C操作************************************************/

	/***********************************集成模块指令******************************************/
	bool SAATGPRSParaSet (unsigned char nType, unsigned char* pPara, unsigned char nLen);
	bool SAATGPRSParaQuery (int nType, unsigned char* pPara,unsigned char *pLen);
	bool SAATWIFIParaSet (unsigned char nType, unsigned char* pPara, unsigned char nLen);
	bool SAATWIFIParaQuery (int nType, unsigned char* pPara,unsigned char *pLen);
	/***********************************集成模块指令******************************************/

	bool SAATCopyright(char* copyright);//API版本信息查询
	bool SAATSetLanguageType (char* szType);//设置API动态库语言类型
	bool SAATSysTest(unsigned char nType,unsigned char nAntenna, unsigned char *pTestParm, unsigned char nLen);

	bool SendNRevMsg(unsigned char *pSendCommand, 
		unsigned char *pSendData, 
		int dataLength,
		CRFIDFrame &pRevFrame,
		int nWaitTime = 3000);//收发数据
	char* GetProuctSN();//得到序列号
	void SetProuctSN(char* szName);//设置序列号
	IConnect* CRFIDReader::ConcreteConn(CRFIDSystemCfg& cfg);//创建CRFIDReader对象
	bool SetMsgResult(CRFrame& RFIDFrame);//设置返回结果
	bool CheckMsg(unsigned char nCommand);//检测命令
	bool SendMsg(unsigned char *pCommand,unsigned char *pSendData, int dataLength,CRFIDFrame &pRevFrame);//发送命令
	bool GetMsgResult(CRFIDFrame &pRevFrame,int nWaitTime = 3000);//得到返回结果
	void SetErrorCode (int iErrorCode,bool bCommandError = false);//设置错误码
	bool CheckIsReadCardCommand(unsigned char nCommand);//检查是否读卡指令
	bool GetCard(CRFrame& RFIDFrame,int nWaitTime);//获取当前卡号	
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
		unsigned char nLen);//底层写EPC码
	bool SAAT6CRawReadUserData ( unsigned char nAntenna, unsigned int StartAddr,
		unsigned char nToReadLen, unsigned char * UserData,unsigned int* pDataLen);//底层读6C数据

	bool SAAT6CRawWriteUserData (unsigned char nAntenna, 
		unsigned char nType,  
		unsigned char *pAccessPWD,
		unsigned int  nStartAddr,
		unsigned char *pWriteData, 
		unsigned char *pLen);////底层写6C数据
	map<DWORD,int> map_Error;
	bool m_bOpen;
	char m_szProductSN[READER_PROUCTNAME_LEN];
	CDataProc m_DataProcss;
	CCmdBuffer m_cmdBuffer;
	CBuffList<CRFrame> m_CardIDBuffer;
	
	int m_nErrorCode;
	bool m_bCommandError;
	ReadState m_ReadState;
	//CRFIDFrame m_ReadCardFrame;//发送读卡帧保存
	CRITICAL_SECTION m_Critical;
	CRFIDSystemCfg m_sysCfg;

public:
	bool SAATClearFlash();//清flash缓存
	bool SAATFlashDataQuery(unsigned char nOpType, unsigned char* pPara, unsigned char *pLen);//FLASH存储数据查询
	bool SAATFlashTotalCountQuery (unsigned char* pPara,unsigned char *pLen);//FLASH存储数据总数查询

	bool SAATReaderTimeQuery(unsigned char *pPara, unsigned char *pLen);//查询读写器系统时间
	bool SAATSetReaderTime(unsigned char *pPara, unsigned char nLen);//设置读写器系统时间
	
};
