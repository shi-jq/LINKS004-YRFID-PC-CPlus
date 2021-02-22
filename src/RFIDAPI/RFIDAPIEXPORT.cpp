#include "StdAfx.h"
#include "RFIDAPIEXPORT.h"
#include "Global.h"
#include "RFIDReaderManager.h"

//////////////////////////////////////////////////////////////////////////
//5.1.1 TCP参数初始化
//功能描述：通过参数传入，此函数用于计算机的以太网应用配置，初始化一个SOCKET，为建立基于以太网接口的连接做准备。
//函数原型：
//bool    SAAT_TCPInit (void** pHandle,char *pHostName,int nsocketPort)
//传入参数：
//pHandle			为保存打开的端口句柄
//pHostName			读写器IP地址
//nsocketPort		读写器TCP SOCKET端口，默认为7086
//返回值：true：操作成功；false：操作失败。
//////////////////////////////////////////////////////////////////////////
bool RFID_API __stdcall SAAT_TCPInit(void** pHandle,char *pHostName,int nsocketPort)
{
	CRFIDReader *pNewReader =  CRFIDReaderManager::Instance()->CreateReader();
	if( NULL == pNewReader )
	{
		return false;
	}
	CRFIDSystemCfg initSystemCfg;
	initSystemCfg.nPortType = TCP_PORT;
	initSystemCfg.strHostName = pHostName;
	initSystemCfg.nSocketPort = nsocketPort;

	if( !pNewReader->InitCFG(initSystemCfg) )
	{
		return false;
	}

	*pHandle = pNewReader;
	return true;
}

//////////////////////////////////////////////////////////////////////////
//5.1.2 COM口参数初始化
//功能描述：通过参数传入，此函数初始化指定计算机COM口，为建立基于串口连接做准备。
//函数原型：
//bool	SAAT_COMInit(void** pHandle,unsigned char nBusAddr,char *pComNum, int nBaud )
//传入参数：
//pHandle		为保存打开的端口句柄
//nBusAddr		为总线地址，默认为0
//pComNum		COM1－COM4 仅在COM通讯模式下有效 
//nBaud			串口通讯速率，默认为19200
//返回值：true：操作成功；false：操作失败。
//////////////////////////////////////////////////////////////////////////
bool RFID_API __stdcall SAAT_COMInit(void** pHandle,unsigned char nBusAddr,char *pComNum,int nBaud )
{
	CRFIDReader *pNewReader =  CRFIDReaderManager::Instance()->CreateReader();
	if( NULL == pNewReader )
	{
		return false;
	}
	CRFIDSystemCfg initSystemCfg;
	initSystemCfg.nPortType = COM_PORT;
	initSystemCfg.nBusAddr = nBusAddr;
	initSystemCfg.nBaud = nBaud;
	initSystemCfg.strComNum = pComNum;

	if( !pNewReader->InitCFG(initSystemCfg) )
	{
		return false;
	}

	*pHandle = pNewReader;
	return true;
}

//////////////////////////////////////////////////////////////////////////
//5.1.3 USB参数初始化
//功能描述：目前读写器的USB接口应用通过是通过串口虚拟的，因此USB接口的使用也要初始化COM口，此函数通过参数传入，初始化计算机COM口，为建立建立基于USB连接做准备。
//函数原型：
//bool	SAAT_USBInit(void** pHandle,unsigned char nBusAddr,char * pUSBNum,int nBaud )
//传入参数：
//pHandle		为保存打开的端口句柄
//nBusAddr		为总线地址，默认为0
//pUSBNum		COM1－COM4 (COM1-COM4是虚拟的串口，通信时转USB协议)仅在USB通讯模式下有效
//nBaud			USB口通讯速率,默认为152000
//返回值：true：操作成功；false：操作失败。
//////////////////////////////////////////////////////////////////////////
bool RFID_API __stdcall SAAT_USBInit(void** pHandle,unsigned char nBusAddr,char * pUSBNum,int nBaud )
{
	CRFIDReader *pNewReader =  CRFIDReaderManager::Instance()->CreateReader();
	if( NULL == pNewReader )
	{
		return false;
	}
	CRFIDSystemCfg initSystemCfg;
	initSystemCfg.nPortType = USB_PORT;
	initSystemCfg.nBusAddr = nBusAddr;
	initSystemCfg.nBaud = nBaud;
	initSystemCfg.strComNum = pUSBNum;

	if( !pNewReader->InitCFG(initSystemCfg) )
	{
		return false;
	}

	*pHandle = pNewReader;
	return true;
}


//////////////////////////////////////////////////////////////////////////
//5.1.4 UDP参数初始化
//功能描述：通过参数传入，此函数用于计算机的以太网应用配置，初始化一个SOCKET，为建立基于以太网接口的UDP连接做准备。
//函数原型：
//bool	SAAT_UDPInit (void** pHandle,char *pHostName,int nsocketPort)
//传入参数：
//pHandle			为保存打开的端口句柄
//pHostName			读写器IP地址
//nsocketPort		读写器UDP SOCKET端口，默认为7088
//返回值：true：操作成功；false：操作失败。
//////////////////////////////////////////////////////////////////////////
bool RFID_API __stdcall SAAT_UDPInit(void** pHandle,char *pHostName,int nsocketPort)
{
	CRFIDReader *pNewReader =  CRFIDReaderManager::Instance()->CreateReader();
	if( NULL == pNewReader )
	{
		return false;
	}
	CRFIDSystemCfg initSystemCfg;
	initSystemCfg.nPortType = UDP_PORT;
	initSystemCfg.strHostName = pHostName;
	initSystemCfg.nSocketPort = nsocketPort;

	if( !pNewReader->InitCFG(initSystemCfg) )
	{
		return false;
	}

	*pHandle = pNewReader;
	return true;
}


//////////////////////////////////////////////////////////////////////////
//5.1.5 建立连接
//功能描述：创建基于串口，USB口或者以太网接口或其他扩展接口之一的连接状态。
//函数原型：
//bool	SAAT_Open(void* pHandle)
//传入参数：
//pHandle	为已经初始化的端口句柄
//返回值：true：操作成功；false：操作失败。
//////////////////////////////////////////////////////////////////////////
bool RFID_API  __stdcall SAAT_Open(void* pHandle)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReader* pReader = (CRFIDReader*)pHandle;
	return (CRFIDReaderManager::Instance())->OpenReaderByObject(pReader);
}




//////////////////////////////////////////////////////////////////////////
//5.1.6 关闭连接
//功能描述：关闭已经建立的连接。
//函数原型：
//bool	SAAT_Close(void *pHandle)
//传入参数：
//pHandle	为打开的端口句柄
//返回值：true：操作成功；false：操作失败。
//////////////////////////////////////////////////////////////////////////
bool RFID_API  __stdcall SAAT_Close(void *pHandle)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReader* pReader = (CRFIDReader*)pHandle;
	
	return CRFIDReaderManager::Instance()->CloseReader(pReader);

}

//////////////////////////////////////////////////////////////////////////
//5.1.7 断开连接并重连
//功能描述：用于断开连接并重连。
//函数原型：
//bool	SAAT_Reconnect(void *pHandle)
//传入参数：
//pHandle	为打开的端口句柄
//返回值：true：操作成功；false：操作失败。
//////////////////////////////////////////////////////////////////////////
bool RFID_API  __stdcall SAAT_Reconnect(void* pHandle)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReader* pReader = (CRFIDReader*)pHandle;
	return pReader->Reconnect();

}

//////////////////////////////////////////////////////////////////////////
//5.1.8 心跳指令
//功能描述：该指令用于上位机和RFID设备之间建立基于以太网、串口、USB口等的通讯连接后检测物理接口的联通情况。上位机一般超过一定时间未接收到RFID设备的数据（如RFID设备等待读卡而当前射频范围内无卡），即可发送该指令要求RFID设备回应心跳包来检测通讯链路的连接状态和RFID设备的工作状态。
//函数原型：
//bool	SAAT_HeartSend (void *pHandle)
//传入参数：
//pHandle	为打开的端口句柄
//返回值：true：连接正常；false：连接断开。
//////////////////////////////////////////////////////////////////////////
bool RFID_API  __stdcall SAAT_HeartSend (void* pHandle)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReader* pReader = (CRFIDReader*)pHandle;
	return pReader->SAATHeartSend();
}

//////////////////////////////////////////////////////////////////////////
//5.2.1 系统信息设置
//功能描述：该函数用于设置读写器系统配置相关参数，如读写器的名称，读写器的权限密码等。
//函数原型：
//bool	SAAT_SysInfSet (void* pHandle ,unsigned char nType,unsigned char* pParm,unsigned char nLen)
//传入参数：
//pHandle		打开的端口句柄
//nType			系统信息配置类型
//类型			定义						长度 
//0				读写器名称					16字节
//1				读写器产品型号				4字节
//2				读写器出厂产品序列号		4字节
//3				读写器系统权限码			4字节
//pParm			系统参数
//nLen			系统参数长度
//返回值：true：操作成功；false：操作失败。
//////////////////////////////////////////////////////////////////////////
bool RFID_API  __stdcall SAAT_SysInfSet (void* pHandle ,unsigned char nType,unsigned char* pParm,int nLen)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReader* pReader = (CRFIDReader*)pHandle;
	return pReader->SAATSysInfSet(nType,pParm,nLen);
}

//////////////////////////////////////////////////////////////////////////
//5.2.2 系统信息查询
//功能描述：该函数用于查询读写器系统信息等参数，可查询类型见下面“信息类型”定义。
//函数原型：
//bool	SAAT_SysInfQuery (void* pHandle ,unsigned char nType, unsigned char *pPara, unsigned char *pLen)
//传入参数：
//pHandle		打开的端口句柄
//nType			要查询的信息类型（见说明）
//szPara		指向接收读写器参数数据内存的指针 
//pLen			pLen指向的内存长度
//返回值：true为操作成功, false为操作失败
//说明: nType（信息类型）定义描述：
//	nType           定义						长度
//	0x00			读写器名称					8字节
//	0x01			读写器产品型号				5字节
//	0x02  			读写器出厂产品序列号		8字节
//	0x03   			读写器处理器软件版本号		4字节
//	0x04   			读写器解码单元软件版本号	4字节
//	0x05  			基带电路硬件版本号			4字节
//	0x06			射频电路硬件版本号			4字节
//////////////////////////////////////////////////////////////////////////
bool RFID_API  __stdcall SAAT_SysInfQuery (void* pHandle ,unsigned char nType, unsigned char *pPara, unsigned char *pLen)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReader* pReader = (CRFIDReader*)pHandle;
	return pReader->SAATSysInfQuery(nType,pPara,pLen);
}

//////////////////////////////////////////////////////////////////////////
//5.2.3 工作模式配置
//功能描述：此函数用于配置读写器的工作模式。
//函数原型：
//bool	SAAT_WorkModeSet (void* pHandle ,unsigned nType)
//传入参数：
//pHandle		打开的端口句柄
//nType			要配置的工作模式
//工作模式      定义			说明
//0x00			主从模式    读写器在上位机的指令控制下执行标签操作；
//0x01			预置模式    读写器根据事先预置的指令执行标签操作；
//0x02			触发模式    读写器根据IO输入触发标签操作指令；
//0x03			定时模式    读写器根据系统时钟定时来执行标签操作。
//返回值：true：操作成功；false：操作失败。
//////////////////////////////////////////////////////////////////////////
bool RFID_API  __stdcall SAAT_WorkModeSet (void* pHandle ,unsigned char nType)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReader* pReader = (CRFIDReader*)pHandle;
	return pReader->SAATWorkModeSet(nType);
}

//////////////////////////////////////////////////////////////////////////
//5.2.4系统参数表操作
//功能描述：此函数用于操作读写器的参数表，包括传入或者传出读写器的系统参数表的全部或者某一段，此函数用于对大量读写器参数的快速查询或配置。
//函数原型：
//bool	SAAT_ParmOp (void* pHandle ,unsigned char nType, unsigned char nStartAddrr, unsigned char nLen,  unsigned char *pData, unsigned char *pDataLen)
//传入参数：
//pHandle		打开的端口句柄
//nType			参数表操作的操作模式（见说明）  
//nStartAddrr	指定操作读卡器参数表起始位置
//nLen			指定操作读卡器参数表长度
//pData			传入时为传入的数据, 传出时为传出的数据
//pDataLen		pData的长度
//返回值：true：操作成功；false：操作失败。
//说明:nType参数表操作的操作模式：
//0x00			恢复系统参数表为出厂设置
//0x01			传入系统参数表
//0x02			传出系统参数表
//注：操作模式为0x00时，起始地址和操作长度两项参数无意义。
//////////////////////////////////////////////////////////////////////////
bool RFID_API  __stdcall SAAT_ParmOp (void* pHandle ,unsigned char nType, unsigned char nStartAddrr, unsigned char nLen,  unsigned char *pData, unsigned char *pDataLen)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReader* pReader = (CRFIDReader*)pHandle;
	return pReader->SAATParmOp(nType,nStartAddrr,nLen,pData,pDataLen);
}

//////////////////////////////////////////////////////////////////////////
//5.2.5 载波参数配置
//功能描述：此函数用于配置读写器的射频载波的相关参数。
//函数原型：
//bool	SAAT_RFParaSet (void* pHandle ,unsigned char nType, int nParaLen,unsigned char* pPara)
//传入参数：
//pHandle		打开的端口句柄
//nType			设置的频率表的参数类型（定义见说明）
//nParaLen		设置的跳频表长度
//pPara			设置的频率表（定义见说明）
//返回值：true：操作成功；false：操作失败。
//说明：“参数类型”为要配置的载波参数类型，定义如下：
//0x00	跳频表
//“频率表”为读写器使用的跳频表数值，为1到16的频点号的组合，定义如下：
//0x00	920.625Mhz
//0x01	920.875Mhz
//0x02	921.125Mhz
//0x03	921.375Mhz
//0x04	921.625Mhz
//0x05	921.875Mhz
//0x06	922.125Mhz
//0x07	922.375Mhz
//0x08	922.625Mhz
//0x09	922.875Mhz
//0x0A	923.125Mhz
//0x0B	923.375Mhz
//0x0C	923.625Mhz
//0x0D	923.875Mhz
//0x0E	924.125Mhz
//0x0F	924.375Mhz
//////////////////////////////////////////////////////////////////////////
bool RFID_API  __stdcall SAAT_RFParaSet (void* pHandle ,unsigned char nType, unsigned char nParaLen,unsigned char* pPara)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReader* pReader = (CRFIDReader*)pHandle;
	return pReader->SAATRFParaSet(nType,nParaLen,pPara);
}

//////////////////////////////////////////////////////////////////////////
//5.2.6载波参数查询
//功能描述：此函数用于查询读写器的射频载波的参数配置。
//函数原型：
//bool	SAAT_RFParaQuery (void* pHandle , unsigned char nType, unsigned char* pPara, unsigned char *pLen)
//传入参数：
//pHandle  	打开的端口句柄
//nType		查询的载波参数参数类型, 定义同上节。
//pPara		返回的频率表参数
//pLen 		传入时为pPara的长度，传出时为频率表长度。
//返回值：true：操作成功；false：操作失败。
//////////////////////////////////////////////////////////////////////////
bool RFID_API  __stdcall SAAT_RFParaQuery (void* pHandle ,unsigned char nType,unsigned char* pPara, unsigned char *pLen)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReader* pReader = (CRFIDReader*)pHandle;
	return pReader->SAATRFParaQuery(nType,pPara,pLen);
}

//////////////////////////////////////////////////////////////////////////
//5.2.7 通讯参数配置
//功能描述：此函数用于配置串口等总线通讯参数。
//函数数原型：
//bool	SAAT_CommunicatParaSet (void* pHandle ,unsigned char nType, unsigned char* pPara, unsigned char nLen)
//传入参数：
//pHandle    	打开的端口句柄
//nType  	    配置的参数类型（定义见说明）
//pPara		    读写器的串行总线参数
//nLen		    pPara的长度
//返回值：true：操作成功；false为操作失败
//说明:nType配置的参数类型：
//0x00		串行总线设备地址
//0x01		RS-232总线速率
//0x02		RS-485总线速率
//串行总线设备地址定义当读写器使用多节点总线方式（如RS-485总线）时该读写器的设备节点号，即设备地址。该地址长度为1字节，取值为1到254，0x00和0xff为广播地址。
//RS-232总线速率：定义读写器RS-232串行总线的通讯速率，数据定义为：
//0x00		4800bps
//0x01		9600 bps
//0x02		19200 bps
//0x03		38400 bps
//0x04		57600 bps
//0x05		115200 bps	  
//RS-485总线速率：读写器RS-485串行总线的通讯速率，定义同RS-232串行总线相同。
//////////////////////////////////////////////////////////////////////////
bool RFID_API  __stdcall SAAT_CommunicatParaSet (void* pHandle ,unsigned char nType, unsigned char* pPara, unsigned char nLen)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReader* pReader = (CRFIDReader*)pHandle;
	return pReader->SAATCommunicatParaSet(nType,pPara,nLen);
}

//////////////////////////////////////////////////////////////////////////
//5.2.8 通讯参数查询
//功能描述：此函数用于查询读写器的串行总线的通讯参数。
//函数数原型：
//bool	SAAT_CommunicatParaQuery (void* pHandle ,int nType, unsigned char* pPara,unsigned char *pLen)
//传入参数：
//pHandle		打开的端口句柄
//nType			配置的参数类型（定义见说明）
//pPara			查询的读写器总线参数
//pLen			传入时为pPara长度，传出时为读写器总线参数长度。
//返回值：true：操作成功；false：操作失败。
//说明：nType的定义与上节相同。
//////////////////////////////////////////////////////////////////////////
bool RFID_API  __stdcall SAAT_CommunicatParaQuery (void* pHandle ,unsigned char nType, unsigned char* pPara,unsigned char *pLen)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReader* pReader = (CRFIDReader*)pHandle;
	return pReader->SAATCommunicatParaQuery(nType,pPara,pLen);
}

//////////////////////////////////////////////////////////////////////////
//5.2.9 网络参数配置
//功能描述：此函数用于配置读写器的IP地址等以太网相关参数。
//函数数原型：
//bool	SAAT_NetParaSet (void* pHandle ,unsigned char nType, unsigned char* pPara, unsigned char nLen)
//传入参数：
//pHandle     	打开的端口句柄
//nType			为配置的参数类型（定义见说明）
//pPara		    配置的以太网参数数据（定义见说明）
//nLen	        pPara长度
//返回值：true：操作成功；false：操作失败。
//说明:nType “类型”为配置的参数类型：
//0x01			MAC地址
//0x02			IP地址
//0x03			TCP SOCKET端口号
//0x04			UDP SOCKET端口号
//*IP配置 该项配置以太网IP的相关参数，共12字节，依次包括4字节IP地址、4字节掩码、4字节默认网关。目前不兼容IPV6格式。
//*SOCKET端口号 上位机与读写器通过以太网通讯时使用套接字，该项参数此函数用于读写器识别上位机应用程序，读写器默认的套接字端口号为8086。当用户以太网网络系统中该端口被防火墙屏蔽或者被其他应用程序占用，可以使用该函数修改端口号为可用或合法的，建议用户谨慎使用！
//////////////////////////////////////////////////////////////////////////
bool RFID_API  __stdcall SAAT_NetParaSet (void* pHandle ,unsigned char nType, unsigned char* pPara, unsigned char nLen)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReader* pReader = (CRFIDReader*)pHandle;
	return pReader->SAATNetParaSet(nType,pPara,nLen);
}

//////////////////////////////////////////////////////////////////////////
//5.2.10 网络参数查询
//功能描述：此函数用于查询读写器的IP 地址等以太网相关配置参数。
//函数数原型：
//bool	SAAT_NetParaQuery(void* pHandle ,int nType, unsigned char* pPara,unsigned char *pLen)
//传入参数：
//pHandle 	打开的端口句柄
//nType		为查询参数类型（定义见说明）
//pPara		读写器返回的网络参数数据
//pLen		传入时为pPara长度，传出时为实际返回长度
//返回值：true：操作成功； false：操作失败。
//说明:nType为查询参数类型，定义同上节相同。
//0x01			MAC地址
//0x02			IP地址
//0x03			TCP SOCKET端口号
//0x04			UDP SOCKET端口号
//////////////////////////////////////////////////////////////////////////
bool RFID_API  __stdcall SAAT_NetParaQuery (void* pHandle ,int nType, unsigned char* pPara,unsigned char *pLen)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReader* pReader = (CRFIDReader*)pHandle;
	return pReader->SAATNetParaQuery(nType,pPara,pLen);
}

//////////////////////////////////////////////////////////////////////////
//5.2.11 标签操作参数配置
//功能描述：此函数用于配置读写器做标签的读写等操作时使用的相关参数。
//函数数原型：
//bool	SAAT_TagOpParaSet (void* pHandle ,unsigned char nType, unsigned char *pPara,unsigned char nLen)
//传入参数：
//pHandle		打开的端口句柄
//nType  	    为配置的参数类型（定义见说明）
//pPara			配置的标签操作参数
//nLen			为pPara长度
//返回值：true：操作成功；false：操作失败。
//说明:nType 为配置的参数类型，包括：
//类型			说明							返回信息长度 
//0x10			默认Q值            					1字节
//0x11			选择参数（BANK/地址/掩码/数据）		N字节
//0x13   		默认EPC码的长度   	    			1字节
//（下面为ISO18K-6B标签的参数设置）
//0x21 		选择参数（类型/地址/掩码/数据）			N字节
//////////////////////////////////////////////////////////////////////////
bool RFID_API  __stdcall SAAT_TagOpParaSet(void* pHandle ,unsigned char nType, unsigned char *pPara,unsigned char nLen)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReader* pReader = (CRFIDReader*)pHandle;
	return pReader->SAATTagOpParaSet(nType,pPara,nLen);
}

//////////////////////////////////////////////////////////////////////////
//5.2.12 标签操作参数查询
//功能描述：此函数用于配置读写器对标签做读写等操作的参数。
///函数原型：
//bool	SAAT_TagOpParaQuery (void* pHandle ,unsigned char nType, unsigned char* pPara, unsigned char *pLen)
//传入参数：
//pHandle		打开的端口句柄
//nType			为配置的参数类型（定义见说明）
//pPara			指向保存配置的参数的内存指针
//Len			传入时为pPara长度，传出时为标签操作参数长度
//返回值：true：操作成功；false：操作失败。
//说明：nType 为配置的参数类型，定义与上节相同。
//////////////////////////////////////////////////////////////////////////
bool RFID_API  __stdcall SAAT_TagOpParaQuery (void* pHandle ,unsigned char nType, unsigned char* pPara, unsigned char *pLen)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReader* pReader = (CRFIDReader*)pHandle;
	return pReader->SAATTagOpParaQuery(nType,pPara,pLen);
}


//////////////////////////////////////////////////////////////////////////
//5.2.13 扩展板参数配置
//功能描述：此函数用于配置扩展板参数
//函数原型：
//bool	SAAT_ExtendBroadParaSet (void* pHandle ,unsigned char nType, unsigned char pSendChunnel)
//传入参数：
//pHandle		打开的端口句柄
//nType			配置的标签操作参数类型
//0				IO输出操作
//1				IO输入操作
//pSendChunnel	配置的标签操作参数
//返回值：true：操作成功；false：操作失败。
//////////////////////////////////////////////////////////////////////////
bool RFID_API  __stdcall SAAT_ExtendBroadParaSet (void* pHandle ,unsigned char nType, unsigned char pSendChunnel)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReader* pReader = (CRFIDReader*)pHandle;
	return pReader->SAATExtendBroadParaSet(nType,pSendChunnel);
}

//////////////////////////////////////////////////////////////////////////
//5.2.14 扩展板参数查询
//功能描述：此函数用于查询扩展板参数
//函数原型：
//bool	SAAT_ExtendBroadParaQuery (void* pHandle ,unsigned char nType, char* pPara, unsigned char* pLen)
//传入参数：
//pHandle  	打开的端口句柄
//nType		配置的标签操作参数类型
//0			IO输出操作
//1			IO输入操作
//pPara		查询的参数
//pLen		传入时为pPara长度，传出时为查询的参数长度
//返回值： true：操作成功；false：操作失败。
//////////////////////////////////////////////////////////////////////////
bool RFID_API  __stdcall SAAT_ExtendBroadParaQuery (void* pHandle ,unsigned char nType, char* pPara, unsigned char* pLen)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReader* pReader = (CRFIDReader*)pHandle;
	return pReader->SAATExtendBroadParaQuery(nType,pPara,pLen);
}

//////////////////////////////////////////////////////////////////////////
//5.2.15 射频端口参数查询
//功能描述：此函数用于查询读写器的射频端口参数。
//函数原型：
//bool	SAAT_TotalAntennaParmQuery(void* pHandle,unsigned char *szAntennaPara,unsigned char *pLen)
//传入参数：
//pHandle			打开的端口句柄
//szAntennaPara 	全部射频端口参数（定义见说明）
//pLen				传入时为szAntennaPara长度，传出时为全部射频端口参数长度。
///返回值：true：操作成功；false：操作失败。
//说明：全部射频端口参数包含：
//端口使能	4字节	天线端口使能
//输出功率	4字节	天线端口输出功率
//轮询时间	4字节	天线端口轮询时间
//“端口使能” 配置参数长度为4个字节，依次为天线1～4的使能配置，0x00为禁止，0x01为允许。
//“输出功率”配置参数长度为4个字节，依次为天线1～4的端口输出功率参数，(0x00~0x0A)，数据定义为:
//0x00	20.0(dBm)
//0x01	21.0(dBm)
//0x02	22.0(dBm) 
//0x03	23.0(dBm)
//0x04	24.0(dBm)
//0x05	25.0(dBm)
//0x06	26.0(dBm)
//0x07	27.0(dBm) 
//0x08	28.0(dBm)
//0x09	29.0(dBm)
//0x0A	30.0(dBm)
//“轮询时间””配置参数长度为4个字节，依次为天线1～4的端口轮询时间参数，即当轮询模式时该端口的工作时间，工作时间=时间参数 X 100ms。
//////////////////////////////////////////////////////////////////////////
bool RFID_API  __stdcall SAAT_TotalAntennaParmQuery (void* pHandle,unsigned char *szAntennaPara,unsigned char *pLen)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReader* pReader = (CRFIDReader*)pHandle;
	return pReader->SAATTotalAntennaParmQuery(szAntennaPara,pLen);
}

//////////////////////////////////////////////////////////////////////////
//5.2.16 指定射频端口参数查询
//功能描述：此函数用于查询读写器的参数表的射频相关参数。
//函数原型：
//bool	SAAT_AntennaParmQuery (void* pHandle, unsigned char nAntenna, unsigned char * pAntennaEnable, unsigned char *pAntennaPower, unsigned char *pAntennaQueryTime )
//传入参数：
//pHandle			打开的端口句柄
//nAntenna			要进行配置的天线端口号
//nAntennaEnable	天线端口使能,0x00为禁止,0x01为允许
//nAntennaPower		输出功率,单位为dBm，数据定义为:
//					0x00	20.0(dBm)
//					0x01	21.0(dBm)
//					0x02	22.0(dBm) 
//					0x03	23.0(dBm)
//					0x04	24.0(dBm)
//					0x05	25.0(dBm)
//					0x06	26.0(dBm)
//					0x07	27.0(dBm) 
//					0x08	28.0(dBm)
//					0x09	29.0(dBm)
//					0x0A	30.0(dBm)
//nAntennaQueryTime  轮循模式时，该端口占用的工作时间，单位为毫秒。
//返回值： true：操作成功；false：操作失败。
//////////////////////////////////////////////////////////////////////////
bool RFID_API  __stdcall SAAT_AntennaParmQuery (void* pHandle,unsigned char nAntenna,unsigned char * pAntennaEnable,unsigned char *pAntennaPower,unsigned char *pAntennaQueryTime )
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReader* pReader = (CRFIDReader*)pHandle;
	return pReader->SAATAntennaParmQuery(nAntenna,pAntennaEnable,pAntennaPower,pAntennaQueryTime);
}

//////////////////////////////////////////////////////////////////////////
//5.2.17 射频端口参数配置
//功能描述：此函数用于配置读写器的参数表的射频端口参数。
//函数原型：
//bool	SAAT_AntennaParmSet(void* pHandle ,unsigned char *pPara,unsigned char nLen )
//传入参数：
//pHandle		打开的端口句柄
//pPara		    配置读写器的参数表的射频端口参数（定义见说明）。 
//nLen 		    参数长度, 一般为12字节。
//返回值：true：操作成功；false：操作失败。
//说明：全部射频端口参数包含：
//端口使能	4字节	天线端口使能
//输出功率	4字节	天线端口输出功率
//轮询时间	4字节	天线端口轮询时间
//“端口使能”配置参数长度为4个字节，依次为天线1～4的使能配置，0x00为禁止，0x01为允许。
//“输出功率”配置参数长度为4个字节，依次为天线1～4的端口输出功率参数(0x00~0x0A)，数据定义为：
//0x00	20.0(dBm)
//0x01	21.0(dBm)
//0x02	22.0(dBm) 
//0x03	23.0(dBm)
//0x04	24.0(dBm)
//0x05	25.0(dBm)
//0x06	26.0(dBm)
//0x07	27.0(dBm) 
//0x08	28.0(dBm)
//0x09	29.0(dBm)
//0x0A	30.0(dBm)
//“轮询时间”配置参数长度为4个字节，依次为天线1～4的端口轮询时间参数，即当轮询模式时该端口的工作时间，工作时间=时间参数 X 100ms。
//////////////////////////////////////////////////////////////////////////
bool  RFID_API  __stdcall SAAT_AntennaParmSet(void* pHandle ,unsigned char *pPara,unsigned char nLen )
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReader* pReader = (CRFIDReader*)pHandle;
	return pReader->SAATAntennaParmSet(pPara,nLen );
}

//////////////////////////////////////////////////////////////////////////
//5.2.18 指定射频端口使能配置
//功能描述：此函数用于配置读写器指定射频端口使能。
//函数原型：
//bool	SAAT_SetAntennaPortEnable (void* pHandle, unsigned char nAntenna, unsigned char nEnable )
//传入参数：
//pHandle		打开的端口句柄
//nAntenna		要进行配置的天线端口号
//nEnable		使能设置
//0x00			为禁止
//0x01			为允许
//返回值：true：操作成功；false为操作失败。
//////////////////////////////////////////////////////////////////////////
bool RFID_API  __stdcall SAAT_SetAntennaPortEnable (void* pHandle,unsigned char nAntenna,unsigned char nEnable )
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReader* pReader = (CRFIDReader*)pHandle;
	return pReader->SAATSetAntennaPortEnable(nAntenna,nEnable );
}

//////////////////////////////////////////////////////////////////////////
//5.2.19 指定射频端口功率配置
//功能描述：此函数用于配置读写器的指定射频端口功率。
//函数原型：
//bool	SAAT_SetAntennaPower (void* pHandle,unsigned char nAntenna,unsigned char nPower )
//传入参数：
//pHandle		打开的端口句柄
//nAntenna		射频端口号 1－4
//nPower		设置功率的数值(0x00~0x0A), 数据定义为：
//				0x00	20.0(dBm)
//				0x01	21.0(dBm)
//				0x02	22.0(dBm) 
//				0x03	23.0(dBm)
//				0x04	24.0(dBm)
//				0x05	25.0(dBm)
//				0x06	26.0(dBm)
//				0x07	27.0(dBm) 
//				0x08	28.0(dBm)
//				0x09	29.0(dBm)
//				0x0A	30.0(dBm)
//返回值： true：操作成功；false：操作失败。
//////////////////////////////////////////////////////////////////////////
bool RFID_API  __stdcall SAAT_SetAntennaPower (void* pHandle,unsigned char nAntenna,unsigned char nPower )
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReader* pReader = (CRFIDReader*)pHandle;
	return pReader->SAATSetAntennaPower(nAntenna,nPower );
}

//////////////////////////////////////////////////////////////////////////
//5.2.20 指定射频端口轮询时间配置
//功能描述：此函数用于配置读写器的各个射频端口的轮询时间，可以根据各个端口的重要程度以及读卡需求来设置不同的轮询时间，从而优化系统。
//函数原型：
//bool	SAAT_SetAntennaTime (void* pHandle,unsigned char nAntenna,unsigned char nTime )
//传入参数：
//pHandle		打开的端口句柄
//nAntenna   	射频端口号1-4
//nTime		    设置轮询时间(0x00~0x64), 工作时间=轮询时间 * 100ms，如设置轮询时间为200ms,则nTime 设置为0x02。
//返回值： true：操作成功；false：操作失败。
//////////////////////////////////////////////////////////////////////////
bool RFID_API  __stdcall SAAT_SetAntennaTime (void* pHandle,unsigned char nAntenna,unsigned char nTime )
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReader* pReader = (CRFIDReader*)pHandle;
	return pReader->SAATSetAntennaTime(nAntenna,nTime );
}

//////////////////////////////////////////////////////////////////////////
//5.3.1 停止读卡
//功能描述：此函数用于通知读写器停止当前执行的任何标签操作相关指令。
//函数原型：
//bool	SAAT_PowerOff(void *pHandle);
//传入参数：
//pHandle		打开的端口句柄	 
//返回值：true：操作成功；false：操作失败。
//////////////////////////////////////////////////////////////////////////
bool RFID_API  __stdcall SAAT_PowerOff(void *pHandle)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReader *pReader = (CRFIDReader *)pHandle;
	return pReader->PowerOff();
}

bool RFID_API STDCALL SAAT_YPowerOff(void* pHandle)
{
	if (NULL == pHandle)
	{
		return false;
	}

	CRFIDReader *pReader = (CRFIDReader *)pHandle;
	return pReader->PowerOff();
}

//////////////////////////////////////////////////////////////////////////
//5.3.2 载波操作
//功能描述：此函数用于控制读写器的载波，打开载波并由指定射频端口输出或者停止载波输出。
//由射频识别的原理可知，当读写器进行标签操作时要求读写器一直有载波输出，用以为标签提供工作的能量，此函数即用于控制载波的开启和关闭。但在实际应用中，读写器在执行标签操作时会自动打开载波并在完成标签操作后自动关闭。因此该函数用户一般应用中不需使用。
//函数原型：
//bool	SAAT_CarrierWaveOp(void* pHandle ,unsigned char nType, unsigned char  nPort)
//传入参数：
//pHandle	打开的端口句柄
//nType		载波操作模式
//0x00		打开
//0x01		关闭
//nPort		打开的载波端口 1－4
//返回值：true：操作成功；false：操作失败。
//////////////////////////////////////////////////////////////////////////
bool RFID_API  __stdcall SAAT_CarrierWaveOp(void* pHandle ,unsigned char nType, unsigned char  nPort)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReader* pReader = (CRFIDReader*)pHandle;
	return pReader->SAATCarrierWaveOp(nType,nPort);
}

//////////////////////////////////////////////////////////////////////////
//5.3.3 IO输出操作
//功能描述：此函数用于控制读写器的多路IO输出端口的操作。
//函数原型：
//bool	SAAT_IOOperate(void* pHandle,unsigned char nPort,unsigned char nState)
//传入参数：
//pHandle	打开的端口句柄	
//nPort		要操作的IO输出端口号 1－4
//0x00    	所有端口
//0x01    	端口1
//0x02		端口2
//0x03		端口3
//0x04		端口4
//nState	IO输出电平状态（定义见说明）
//返回值：true：操作成功；false：操作失败。
//说明:nState输出状态：   
//0x00    指定IO切换为低电平状态
//0x01    指定IO切换为高电平状态  
//0x02    指定IO输出10毫秒正脉冲信号
//0x03    指定IO输出10毫秒负脉冲信号
//////////////////////////////////////////////////////////////////////////
bool RFID_API  __stdcall SAAT_IOOperate(void* pHandle,unsigned char nPort,unsigned char nState)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReader* pReader = (CRFIDReader*)pHandle;
	return pReader->SAATIOOperate(nPort,nState);

}

//////////////////////////////////////////////////////////////////////////
//5.3.4 IO输入查询
//功能描述：此函数用于查询读写器的IO输入接口的状态。
//函数原型：
//bool	SAAT_IOStateQuery(void* pHandle,unsigned char *pState)
//传入参数：
//pHandle		打开的端口句柄
//pState		输入端口的电平状态指针
//返回值：true：操作成功；false：操作失败。
//说明：端口状态以一字节来表示
//位	Bit7	Bit 6	Bit 5	Bit 4	Bit 3	Bit 2	Bit 1	Bit 0
//定义	保留	保留	保留	保留	保留	保留	端口2	端口1
//端口状态：0   低电平
//1   高电平
//////////////////////////////////////////////////////////////////////////
bool RFID_API  __stdcall SAAT_IOStateQuery(void* pHandle,unsigned char *pState)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReader* pReader = (CRFIDReader*)pHandle;
	return pReader->SAATIOStateQuery(pState);
}

bool RFID_API STDCALL SAAT_YReadIDCode(void* pHandle, unsigned char nOpType, unsigned char nIDType, unsigned int nTagCount)
{
	return false;
}

bool RFID_API STDCALL SAAT_YMakeTagUpLoadIDCode(void* pHandle, unsigned char nOpType, unsigned char nIDType)
{
	if (NULL == pHandle)
	{
		return false;
	}

	CRFIDReader* pReader = (CRFIDReader*)pHandle;
	return pReader->SAATYMakeTagUpLoadIDCode(nOpType, nIDType);
}

bool RFID_API STDCALL SAAT_YEASRegSet(void* pHandle, unsigned char nOpType, unsigned char nIDType, unsigned char* pCodeID, unsigned char* pTagPwd, unsigned char nSetMode, unsigned char nFlagBit)
{
	return false;
}

bool RFID_API STDCALL SAAT_YEASRegQuery(void* pHandle, unsigned char nOpType, unsigned char nIDType, unsigned char* pIDCode, unsigned char* pTagPwd, unsigned char* pIDType, unsigned char* pEASIDCode, unsigned char* pFlagBit)
{
	return false;
}

bool RFID_API STDCALL SAAT_YEASMonitorEnable(void* pHandle, unsigned char nOpType, unsigned char nIDType, unsigned char nEasBit)
{
	return false;
}

int RFID_API STDCALL SAAT_YRevEASIDMsg(void* pHandle, unsigned char* pIDData, unsigned char* pIDLen, unsigned char* pBit)
{
	return 0;
}

bool RFID_API STDCALL SAAT_YAntennaPowerSet(void* pHandle, unsigned char nPower)
{
	return false;
}

bool RFID_API STDCALL SAAT_YAntennaPowerQuery(void* pHandle, unsigned char* pPower)
{
	return false;
}

bool RFID_API STDCALL SAAT_YWriteEIDCode(void* pHandle, unsigned char nOpMode, unsigned char* pIDCode, unsigned char* pAccessPWD, unsigned char* pWriteEIDData)
{
	return false;
}

bool RFID_API __stdcall SAAT_YReadUserData(void* pHandle, unsigned char nOpMode, unsigned char nIDCodeType, unsigned char* pIDCode, unsigned char* pTagPwd, unsigned char nBank, unsigned char nStartAddr, unsigned char* pReadData, int* pReadLen, unsigned int nWaitTime)
{
	return false;
}

bool RFID_API __stdcall SAAT_YWriteUserData(void* pHandle, unsigned char nOpMode, unsigned char nIDCodeType, unsigned char* pIDCode, unsigned char* pTagPwd, unsigned char nBank, unsigned char nStartAddr, unsigned char* pWriteData, int nWriteLen, unsigned int nWaitTime)
{
	return false;
}

bool RFID_API STDCALL SAAT_YAccessPWDSet(void* pHandle, unsigned char nOpMode, unsigned char nIDType, unsigned char* pIDCode, unsigned char* pOrgPWD, unsigned char* pNewPWD)
{
	return false;
}

bool RFID_API STDCALL SAAT_YCFGPWDSet(void* pHandle, unsigned char nOpMode, unsigned char nIDType, unsigned char* pIDCode, unsigned char* pOrgPWD, unsigned char* pNewPWD)
{
	return false;
}

bool RFID_API STDCALL SAAT_YTagOp(void* pHandle, unsigned char nOpMode, unsigned char nIDType, unsigned char* pIDCode, unsigned char* pTagPWD, unsigned char nTagOpType, unsigned short nStartAddr, unsigned char nDataLen)
{
	return false;
}

bool RFID_API STDCALL SAAT_YTagParmSet(void* pHandle, unsigned char nOpType, unsigned char nIDType, unsigned char* pIDCode, unsigned char* pTagPwd, unsigned char nAntennaPower, unsigned char nAntennaFrequency, unsigned char nHoppingMode)
{
	return false;
}

bool RFID_API STDCALL SAAT_WCommunicatParaQuery(void* pHandle, unsigned char nType, unsigned char* pPara, unsigned char* pLen)
{
	return false;
}

//////////////////////////////////////////////////////////////////////////
//5.3.5 重启读写器
//功能描述：此函数用于重新启动读写器。
//函数原型：
//bool	SAAT_Reboot(void* pHandle,unsigned char nMode)
//传入参数：
//pHandle		打开的端口句柄	
//nMode			操作模式
//0x00  普通模式
//0x01  BOOT重启模式，启动后RFID设备将发送BOOT指令
//返回值：true：操作成功；false：操作失败。
//////////////////////////////////////////////////////////////////////////
bool RFID_API  __stdcall SAAT_Reboot (void* pHandle,unsigned char nMode)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReader* pReader = (CRFIDReader*)pHandle;
	return pReader->SAATReboot (nMode);
}

bool RFID_API STDCALL SAAT_YTagParmQuery(void* pHandle, unsigned char nOpType, unsigned char nIDType, unsigned char* pIDCode, unsigned char* nTagPwd, unsigned char* pAntennaPower, unsigned char* pAntennaFrequency, unsigned char* pHoppingMode)
{
	return false;
}

//////////////////////////////////////////////////////////////////////////
//5.3.6 读卡指示配置
//功能描述：此函数用于配置RFID设备的蜂鸣器等指示设备的工作状态。
//函数原型：
//bool	SAAT_Reading_IOConfig (void* pHandle,unsigned char nConfigBit)
//传入参数：
//pHandle		打开的端口句柄	
//nConfigBit：	配置参数
//Bit7	Bit6	Bit5	Bit4	Bit3	Bit2	Bit1	Bit0
//保留	保留	保留	IO输出4	IO输出3	IO输出2	IO输出1	蜂鸣器
//设备对应比特值为
//0 ：禁止
//1 ：使能    
//* IO端口使能状态，电源输出型端口输出电流，继电器输出型端口闭合。
//* 输出使能信号为脉冲，时间为100mS。
//返回值：true：操作成功；false：操作失败。
//////////////////////////////////////////////////////////////////////////
bool RFID_API  __stdcall SAAT_Reading_IOConfig (void* pHandle,unsigned char nConfigBit)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReader* pReader = (CRFIDReader*)pHandle;
	return pReader->SAATReadingIOConfig (nConfigBit);
}

//////////////////////////////////////////////////////////////////////////
//5.3.7 读卡指示查询
//功能描述：此函数用于查询RFID设备的蜂鸣器等指示设备的工作状态。
//函数原型：
//bool	SAAT_Reading_IOQuery (void* pHandle,unsigned char* pConfigBit)
//传入参数：
//pHandle		打开的端口句柄	
//pConfigBit：	查询参数
//Bit7	Bit6	Bit5	Bit4	Bit3	Bit2	Bit1	Bit0
//保留	保留	保留	IO输出4	IO输出3	IO输出2	IO输出1	蜂鸣器
//设备对应比特值为
//0 ：禁止
//1 ：使能    
//* IO端口使能状态，电源输出型端口输出电流，继电器输出型端口闭合。
//* 输出使能信号为脉冲，时间为100mS。
//返回值：true：操作成功；false：操作失败。
//////////////////////////////////////////////////////////////////////////
bool RFID_API  __stdcall SAAT_Reading_IOQuery (void* pHandle,unsigned char* pConfigBit)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReader* pReader = (CRFIDReader*)pHandle;
	return pReader->SAATReadingIOQuery (pConfigBit);
}

//////////////////////////////////////////////////////////////////////////
//5.3.8 读卡指示脉冲宽度配置
//功能描述：此函数用于配置读卡时IO输出脉冲的宽度
//函数原型：
//bool	SAAT_IOPulseWidthSet (void* pHandle,unsigned char nIOPort,unsigned char nWidth)
//传入参数：
//pHandle		打开的端口句柄	
//nIOPort：		配置的IO端口:端口1到端口4
//nWidth：		脉冲宽度(单位为100ms)
//返回值：true：操作成功；false：操作失败。
//////////////////////////////////////////////////////////////////////////
bool RFID_API  __stdcall SAAT_IOPulseWidthSet (void* pHandle,unsigned char nIOPort,unsigned char nWidth)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReader* pReader = (CRFIDReader*)pHandle;
	return pReader->SAATIOPulseWidthSet (nIOPort,nWidth);
}

//////////////////////////////////////////////////////////////////////////
//5.3.9 读卡指示脉冲宽度查询
//功能描述：此函数用于查询读卡时IO输出脉冲的宽度
//函数原型：
//bool	SAAT_IOPulseWidthQuery (void* pHandle,unsigned char nIOPort,unsigned char* pWidth)
//传入参数：
//pHandle		打开的端口句柄	
//nIOPort：		查询的IO端口:端口1到端口4
//pWidth：		脉冲宽度(单位为100ms)
//返回值：true：操作成功；false：操作失败。
//////////////////////////////////////////////////////////////////////////
bool RFID_API  __stdcall SAAT_IOPulseWidthQuery (void* pHandle,unsigned char nIOPort,unsigned char* pWidth)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReader* pReader = (CRFIDReader*)pHandle;
	return pReader->SAATIOPulseWidthQuery (nIOPort,pWidth);
}

bool RFID_API STDCALL SAAT_YTagWorkModeSet(void* pHandle, unsigned char nOpType, unsigned char nIDType, unsigned char* pIDCode, unsigned char* pTagPwd, unsigned char nWorkMode, unsigned char nUpLoadIDType, unsigned short nSleepTime, unsigned char nSleepInterval)
{
	return false;
}


//////////////////////////////////////////////////////////////////////////
//5.4.1 标签选择参数配置
//功能描述： 此函数用来设置读写器对ISO18000-6B标签执行操作时使用的选择参数，读写器将在下一次对ISO18000-6B标签的操作中使用该选择参数，实现对多张ISO18000-6B标签中具有相同性质（UID码或者数据的某几个字节等于，不等于，大于或小于设置的数据）的某一类或某一张标签做选择性操作。
//函数原型：
//bool	SAAT_6BTagSelect ( void* pHandle, unsigned char nType, unsigned char nStartAddr, unsigned char nDataBite, unsigned char * Data )
//传入参数：
//pHandle		打开的端口句柄
//nType			为匹配类型（定义见说明）
//nStartAddr	为匹配数据的起始字节地址
//nDataBite		为匹配掩码
//Data			为8字节进行匹配的数据	
//返回值：true：操作成功；false：操作失败。
//////////////////////////////////////////////////////////////////////////
bool RFID_API  __stdcall  SAAT_6BTagSelect ( void* pHandle, unsigned char nType, unsigned char nStartAddr,
											unsigned char nDataBite, unsigned char * Data )
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReader* pReader = (CRFIDReader*)pHandle;
	return pReader->SAAT6BTagSelect(nType,nStartAddr,nDataBite,Data );

	return true;
}

//////////////////////////////////////////////////////////////////////////
//5.4.2 读标签UID码
//功能描述：该函数向读写器发送“读取ISO18000-6B标签UID码”指令。
//函数原型：
//bool	SAAT_6BReadUIDCode (void *pHandle,unsigned char nAntenna,unsigned char nType)
//传入参数：
//pHandle	打开的端口句柄
//nAntenna	为读取操作使用的天线号天线号(0为天线轮循，1为天线1，2为天线2，3为天线3，4为天线4)
//nType		为操作模式
//返回值：	true：操作成功；false：操作失败。
//说明:nType操作模式：
//0x00	单次读取模式,  读写器将只执行一次读取操作并将所读取到的所有标签UID码依次全部返回给上位机，之后读卡器将自动停止读卡操作。 
//0x01	循环读取模式，读写器将读取到的所有的标签UID码全部一次返回给上位机，读卡器将自动继续执行该项读卡操作，直到上位机下发"停止操作"命令后才停止读标签。
//////////////////////////////////////////////////////////////////////////
bool RFID_API  __stdcall  SAAT_6BReadUIDCode (void *pHandle,unsigned char nAntenna,unsigned char nType)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReader* pReader = (CRFIDReader*)pHandle;
	return pReader->SAAT6BReadUIDCode(nAntenna,nType );

}

//////////////////////////////////////////////////////////////////////////
//5.4.3 接收标签UID码
//功能描述：该函数启动接收操作接收读写器返回的标签UID码。 
//函数原型：
//int	SAAT_6BRevUIDMsg (void *pHandle, unsigned char* nAntenna, unsigned char* pUIDData, unsigned char* nUIDLen)
//传入参数：
//pHandle 	    打开的端口句柄
//nAntenna   	为读写器读取到UID码的天线号
//pUIDData	    为读取到的UID码数据
//nUIDLen	    传入时为pUIDData长度，传出时为UID数据长度（为8）
//返回值： 0：未接收到UID码；1：接收到UID码。
//////////////////////////////////////////////////////////////////////////
int  RFID_API  __stdcall SAAT_6BRevUIDMsg (void *pHandle, unsigned char* nAntenna, unsigned char* pUIDData,
										   unsigned char* nUIDLen)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReader* pReader = (CRFIDReader*)pHandle;
	return pReader->SAAT6BRevUIDMsg(nAntenna,pUIDData,nUIDLen);
}

//////////////////////////////////////////////////////////////////////////
//5.4.4 读标签数据区数据
//功能描述：此函数用于读取标签数据区的数据。
//函数原型：
//bool	SAAT_6BReadUserData ( void *pHandle ,unsigned char nAntenna,unsigned char nType,unsigned char * pTagID, unsigned char nStartAddr,unsigned char nReadLen, unsigned char *pdata, unsigned char dataLen)
//传入参数：
//pHandle		打开的端口句柄
//nAntenna		为读取操作使用的天线号
//nType			为操作模式，此处设为0
//pTagID		为要读取的标签的8字节UID码
//nStartAddr	为要读取数据区的首地址
//nReadLen		为要读取的数据长度
//pdata			为存放读到的数据的缓冲区指针
//dataLen		为pdata的长度
//返回值：true：操作成功；false：操作失败。
//说明：
//该指令要求读写器读取指定标签的数据区内指定的一段数据内容并返回给上位机。
//该指令为单标签操作指令，必须要在“标签UID”参数填写指定操作的标签的UID码。
//读取标签"数据首地址"取值范围为0x00到数据区的最后一字节地址，"数据长度"取值范围为1到标签的数据区总长度，并且要求满足"数据区首地址" +"数据区长度"不超出标签的最大地址。
//ISO18000-6B协议定义读写器执行数据区读取操作时每次最多读取8字节，若要读取更多字节，需执行多次操作。本API中已经对读长数据的情况自动做截断读取，所以用户不需要再做多次读取的工作。建议为每次读64字节。
//目前通用的ISO18000-6B标签的数据区为224字节，因此该域最大值为224，用户使用该功能前最好向标签供应商咨询标签数据区的长度参数。
//////////////////////////////////////////////////////////////////////////
bool RFID_API  __stdcall SAAT_6BReadUserData ( void *pHandle ,unsigned char nAntenna,unsigned char nType,unsigned char * pTagID,
											  unsigned char nStartAddr,unsigned char nReadLen, unsigned char *pdata,unsigned char dataLen)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReader* pReader = (CRFIDReader*)pHandle;
	return pReader->SAAT6BReadUserData(nAntenna,nType,pTagID,nStartAddr,nReadLen,pdata,dataLen);
}

//////////////////////////////////////////////////////////////////////////
//5.4.5 写标签数据
//功能描述：此函数用于向标签的数据区写入数据。
//函数原型：
//bool	SAAT_6BWriteUserData (void* pHandle, unsigned char nAntenna, unsigned char nType, unsigned char *pTagID, unsigned char nStartAddrr, unsigned char *pValue, unsigned char *nLen)
//传入参数：
//pHandle		打开的端口句柄
//nAntenna		为写入操作使用的天线号1-4
//nType			为操作模式，此处设为0
//pTagID		为要写入标签的8字节UID码
//nStartAddr 	为要写入数据区的首地址（大于0x08）
//pValue 		为要写入的数据
//nLen			传入时为pValue长度，传出时为实际写入的数据长度
//返回值：true：操作成功；false：操作失败。
//*ISO18000-6B协议定义标签的头8字节为UID，一般在出厂时已经锁定，不可写入。
//*ISO18000-6B协议定义读写器执行数据区写入操作时每次最多写入4字节，若要写入更多字节，需执行多次写操作。本API中已经对写入长数据的情况自动做截断后分次写入，所以用户不需要再做多次读取的工作。但因为长时间操作受干扰的概率增大，建议每次写入64字节。
//////////////////////////////////////////////////////////////////////////
bool RFID_API  __stdcall SAAT_6BWriteUserData (void* pHandle,
											   unsigned char nAntenna,
											   unsigned char nType, 
											   unsigned char *pTagID,
											   unsigned char nStartAddr,
											   unsigned char *pValue, 
											   unsigned char *pLen)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReader* pReader = (CRFIDReader*)pHandle;
	return pReader->SAAT6BWriteUserData(nAntenna,nType,pTagID,nStartAddr,pValue,pLen);
	return true;
}

//////////////////////////////////////////////////////////////////////////
//5.4.6 锁定标签数据区
//功能描述：此函数用于对标签数据执行非可逆的锁定操作。被锁定的数据区数据将不能再被改写或者解除锁定状态。
//函数原型：
//bool	SAAT_6BTagLock (void* pHandle, unsigned char nAntenna, unsigned char nType, unsigned char *pTagID, unsigned char nStartAddrr,  unsigned char nLen)
//传入参数：
//pHandle		打开的端口句柄
//nAntenna		为锁定操作使用的天线号。
//nType			为锁定操作模式，0x00 为锁定。
//pTagID		为要写入标签的8字节UID码
//nStartAddrr	为要锁定数据区的首地址 ，8~224字节
//nLen 	为要锁定数据区的数据长度, “长度+起始地址”不应超出标签最大长度。
//返回值：true：操作成功；false：操作失败。
//说明：该指令控制读写器进行数据区的锁定操作。
//目前通用的ISO18000-6B标签的数据区为224字节，因此该域最大值为224，用户使用该功能前最好向标签供应商咨询标签数据区的长度参数。
//////////////////////////////////////////////////////////////////////////
bool RFID_API  __stdcall SAAT_6BTagLock (void* pHandle, unsigned char nAntenna, unsigned char nType,
										 unsigned char *pTagID, unsigned char nStartAddr,  unsigned char nLen)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReader* pReader = (CRFIDReader*)pHandle;
	return pReader->SAAT6BTagLock(nAntenna,nType,pTagID,nStartAddr,nLen);
	return true;
}


//////////////////////////////////////////////////////////////////////////
//5.4.7 查询标签数据区锁状态
//功能描述：此函数用于对标签数据锁状态进行查询
//函数原型：
//bool	SAAT_6BTagLockQuery (void* pHandle, unsigned char nAntenna, unsigned char * pTagID, unsigned char nStartAddrr,  unsigned char nLen, unsigned char *pData, unsigned char nDataLen)
//传入参数：
//pHandle		打开的端口句柄
//nAntenna		为查询操作使用的天线号
//pTagID		为8字节的标签ID号
//nStartAddrr	为查询数据区的首地址 ,8~224字节
//nLen 	为要查询数据区的数据长度, “长度+起始地址”不应超出标签最大长度。
//返回值：true：操作成功；false：操作失败。
//////////////////////////////////////////////////////////////////////////
bool RFID_API  __stdcall SAAT_6BTagLockQuery (void* pHandle, unsigned char nAntenna, 
											  unsigned char *pTagID, unsigned char nStartAddr,  unsigned char nLen,unsigned char *pData,unsigned char nDataLen)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReader* pReader = (CRFIDReader*)pHandle;
	return pReader->SAAT6BTagLockQuery(nAntenna,pTagID,nStartAddr,nLen,pData,nDataLen);
}

//////////////////////////////////////////////////////////////////////////
//5.5.1 标签选择参数设置
//功能描述：此函数用来设置读写器对ISO18000-6C标签执行操作时使用的选择参数，读写器将在下一次对ISO18000-6C标签的操作中使用该选择参数，实现对多张ISO18000-6C标签中具有相同性质（EPC码，TID码或者用户数据区的某几个字节等于设置的数据）的某一类或某一张标签做选择性操作。
//函数原型：
//bool	SAAT_6CTagSelect (  void *pHandle, unsigned char nBank ,unsigned char nStartAddr,unsigned char MaskBit, unsigned char *Data ,unsigned char Datalength,unsigned char nSessionZone, unsigned char nActiveFlag, unsigned char nCutFlag )
//传入参数：
//pHandle		打开的端口句柄
//nBank			指定匹配的数据区Bank
//nStartAddr	指定匹配的Bank数据的数据起始地址
//MaskBit       指定匹配数据的匹配比特数
//Data 		    指定匹配数据
//Datalength	匹配数据长度
//nSessionZone	指定匹配数据的会话区
//nActiveFlag	指定匹配数据的活动标志
//nCutFlag:		指定匹配数据是否使用截断标志
//返回值：true：操作成功；false：操作失败。
//////////////////////////////////////////////////////////////////////////
bool RFID_API  __stdcall SAAT_6CTagSelect (  void *pHandle, unsigned char nBank ,unsigned short nStartAddr,unsigned char MaskBit, 
										   unsigned char *Data ,unsigned char Datalength,unsigned char nSessionZone,
										   unsigned char nActiveFlag, unsigned char nCutFlag )
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReader* pReader = (CRFIDReader*)pHandle;
	return pReader->SAAT6CTagSelect(nBank,nStartAddr,MaskBit,Data,Datalength,nSessionZone,nActiveFlag,nCutFlag);
}

//////////////////////////////////////////////////////////////////////////
//5.5.2 读取标签EPC码
//功能描述：此函数用于命令读写器执行“读取EPC码指令”。
//函数原型：
//bool	SAAT_6CReadEPCCode ( void *pHandle,unsigned char nAntenna, unsigned char nType, unsigned char nTagCount)
//传入参数：
//pHandle		打开的端口句柄
//nAntenna		为读取操作使用的天线号(0为天线轮循，1为天线1，2为天线2，3为天线3，4为天线4)
//nType			为操作模式
//00：对同一个标签的EPC码读写器只向上位机返回一次，并要求上位机接收后给予读写器"返回数据确认"。
//01"：读写器将读取到的所有的标签EPC码全部上传到上位机并不要求上位机接收后给予读写器"返回数据确认"，直到上位机下发"关功放"命令后才停止读标签EPC码，一般使用此操作模式。
//nTagCount    为同时预计读取标签数, 预计工作环境中一次需要同时读取的最大标签数，设计为到250张，实际读取数超过500张
//返回值：true：操作成功；false：操作失败。
//////////////////////////////////////////////////////////////////////////
bool RFID_API  __stdcall SAAT_6CReadEPCCode ( void *pHandle,unsigned char nAntenna, unsigned char nType,
											 unsigned int nTagCount)
{
	CRFIDReader* pReader = (CRFIDReader*)pHandle;
	pReader->SAAT6CReadEPCCode(nAntenna,nType,nTagCount);
	return true;
}

//////////////////////////////////////////////////////////////////////////
//5.5.3 接收EPC码
//功能描述：此函数用于接收读写器返回的EPC码，可能会有多个EPC码被返回。
//函数原型：
//int	SAAT_6CRevEPCMsg (void *pHandle, unsigned char* nAntenna, unsigned char* pEPCData, unsigned char* nEPCLen)
//传入参数：
//pHandle 	   打开的端口句柄
//nAntenna	   为读写器读取到EPC码的天线号
//pEPCData	   为读写器返回的EPC码数据 
//nEPCLen	   传入时为pEPCData长度，传出时为EPC数据长度，一般为12。
//返回值： 0：未接收到EPC码；1：接收到EPC码。
//////////////////////////////////////////////////////////////////////////
int  RFID_API  __stdcall SAAT_6CRevEPCMsg (void *pHandle, unsigned char* nAntenna, unsigned char* pEPCData,
										   unsigned char* nEPCLen)
{
	CRFIDReader* pReader = (CRFIDReader*)pHandle;
	return pReader->SAAT6CRevEPCMsg(nAntenna,pEPCData,nEPCLen);
}


//////////////////////////////////////////////////////////////////////////
//5.5.4 读标签TID码
//功能描述：此函数用于命令读写器读取“标签TID码”。
//函数原型：
//bool	SAAT_6CReadTIDCode ( void *pHandle,unsigned char nAntenna, unsigned char nType, unsigned char nTagCount)
//参数:
//pHandle		打开的端口句柄
//nAntenna		为读取操作使用的天线号(0为天线轮循，1为天线1，2为天线2，3为天线3，4为天线4)
//nType			为操作模式
//00：对同一个标签的TID码读写器只向上位机返回一次，并要求上位机接收后给予读写器"返回数据确认"。
//01"：读写器将读取到的所有的标签TID码全部上传到上位机并不要求上位机接收后给予读写器"返回数据确认"，直到上位机下发"关功放"命令后才停止读标签TID码，一般使用此操作模式。
//nTagCount    为同时预计读取标签数, 预计工作环境中一次需要同时读取的最大标签数，设计为到250张，实际读取数超过500张
//返回值：true：操作成功；false：操作失败。
//说明：
//EPC协议规定EPCClass1Gen2的标签TID Bank为默认为4个双字节（words）大小，即64bit。但TID在EPC集成应用中已经有边缘化的趋势，有些厂家TID Bank只有两个双字节，甚至有些厂家标签取消了TID Bank，读写器底层会支持不同长度的TID码。
//////////////////////////////////////////////////////////////////////////
bool RFID_API  __stdcall  SAAT_6CReadTIDCode ( void *pHandle,unsigned char nAntenna, unsigned char nType, unsigned int nTagCount)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReader* pReader = (CRFIDReader*)pHandle;
	return pReader->SAAT6CReadTIDCode(nAntenna,nType,nTagCount);

	return true;
}

//////////////////////////////////////////////////////////////////////////
//5.5.5 接收标签TID码
//功能描述：此函数用于接收读写器返回的ISO18000-6C标签TID码。
//函数原型：
//int	SAAT_6CRevTIDMsg (void *pHandle, unsigned char* nAntenna, unsigned char* pTIDData, unsigned char* nTIDLen)
//传入参数：
//pHandle		打开的端口句柄
//nAntenna		为读写器读取到TID码的天线号
//pTIDData		为读写器返回的TID数据 
//nTIDLen		传入时为pTIDData长度，传出时为TID数据长度
//返回值： 0：未接收到TID码；1：接收到TID码。
//////////////////////////////////////////////////////////////////////////
int  RFID_API  __stdcall SAAT_6CRevTIDMsg (void *pHandle, unsigned char* nAntenna, unsigned char* pTIDData, unsigned char* nTIDLen)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReader* pReader = (CRFIDReader*)pHandle;
	return pReader->SAAT6CRevTIDMsg(nAntenna,pTIDData,nTIDLen);
}

//////////////////////////////////////////////////////////////////////////
//5.5.6 写EPC码
//功能描述：此函数用于写EPC码。
//函数原型：
//bool	SAAT_6CWriteEPCCode ( void* pHandle, unsigned char nAntenna, unsigned char nType, unsigned char *pAccessPWD, unsigned char *pWriteData, unsigned char nLen )
//传入参数：
//pHandle		打开的端口句柄
//nAntenna		为标签操作时使用的天线端口号1-4
//nType			为操作模式，此项为0x00
//pAccessPWD	为要操作标签的访问密码,默认密码为4字节0
//pWriteData	为写入标签的EPC码的数据
//nLen			为写入标签的pWriteData长度
//返回值：true：操作成功；false：操作失败。
//说明：该指令用于向标签写入EPC码。
//EPC码的长度：设置标签的EPC码长度，单位为双字节（words），取值范围根据EPC协议为0x00~32H（设为00时将EPC标签初始化为空标签）。EPC global组织规定标签EPC码默认为6个双字节。
//EPC协议要求写标签的EPC数据必须按双字节长度的倍数连续写入，为减小写入操作的复杂性，读写器设计中对EPC数据写入的首地址只支持从EPC码的起始位置开始，不支持修改EPC码的中间某个数据。
//不同厂家/型号的标签的EPC数据区的长度会有差别，因此如果 “EPC数据长度”超出EPC数据区的最大长度。写操作将失败并返回相应错误代码。
//写标签时必须明确指明天线端口。
//////////////////////////////////////////////////////////////////////////
bool RFID_API  __stdcall  SAAT_6CWriteEPCCode ( void* pHandle,
											   unsigned char nAntenna,
											   unsigned char nType,
											   unsigned char *pAccessPWD,
											   unsigned char *pWriteData,
											   unsigned char nLen )
{

	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReader* pReader = (CRFIDReader*)pHandle;
	return pReader->WriteEPCCode(nAntenna,nType,pAccessPWD,pWriteData,nLen);
}

//////////////////////////////////////////////////////////////////////////
//5.5.7 读用户数据区
//功能描述：该函数读取ISO18000-6C标签的用户区（User Bank）数据。
//函数原型：
//bool	SAAT_6CReadUserData ( void* pHandle, unsigned char nAntenna, unsigned int StartAddr, unsigned int nToReadLen, unsigned int nWaitTime ,unsigned char * UserData,unsigned char* pDataLen)
//传入参数：	
//pHandle		打开的端口句柄
//nAntenna		为标签操作时使用的天线端口号1-4
//StartAddr		为读取标签数据区的首地址
//nLength		为读取标签数据区的数据长度，双字读写，长度为1则读取2字节，长度为2读取4字节，如此类推
//nWaitTime		为读取数据超时时间（以毫秒为单位，如一秒为1000）
//UserData		为读取到的数据区数据
//pDataLen		传入时为UserData长度,传出时为读取到的数据区长度
//返回值：true：操作成功；false：操作失败。
//说明：该指令此函数用于设置读写器的标签操作的相关参数。
//不同厂家标签的用户数据区的大小可能会不同，因此读数据取时应参考标签的数据手册，并且保证：“用户数据区首地址”+“用户数据区长度”不应超出用户数据区最大值，否则标签操作将失败并返回相应错误代码。
//有些厂家标签没有用户数据区，当执行此操作时，标签也将返回错误代码。
//////////////////////////////////////////////////////////////////////////
bool RFID_API  __stdcall SAAT_6CReadUserData ( void* pHandle, 
											  unsigned char nAntenna, 
											  unsigned int StartAddr,
											  unsigned int nToReadLen,
											  unsigned int nWaitTime,
											  unsigned char * UserData,
											  unsigned int* pDataLen)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReader* pReader = (CRFIDReader*)pHandle;
	return pReader->SAAT6CReadUserData(nAntenna,StartAddr,nToReadLen,nWaitTime,UserData,pDataLen);
}

//////////////////////////////////////////////////////////////////////////
//5.5.8 写用户数据区
//功能描述：此函数用来写ISO18000-6C标签的用户数据区（USER Bank）数据。
//函数原型：
//bool	SAAT_6CWriteUserData (void* pHandle,  unsigned char nAntenna,  unsigned char nType,  unsigned char *pAccessPWD, unsigned int  nStartAddr,unsigned int nWaitTime, unsigned char *pWriteData,  unsigned int *pToWriteLen)
//传入参数：
//pHandle		打开的端口句柄
//nAntenna		为标签操作时使用的天线端口号1-4
//nType			为操作类型，此项为0
//pAccessPWD	为要操作标签的访问密码,默认密码为4字节0
//nStartAddr	为写入数据的首地址
//nWaitTime		为写入数据超时时间（以毫秒为单位，如一秒为1000）
//pWriteData	为写入标签的用户数据区的数据
//pToWriteLen	输入时为写入标签的用户数据区的长度,输出时为实际写入标签用户数据区的长度,以word（双字节）为单位
//返回值：true：操作成功；false：操作失败。
//////////////////////////////////////////////////////////////////////////
bool RFID_API  __stdcall SAAT_6CWriteUserData (void* pHandle,  
											   unsigned char nAntenna, 
											   unsigned char nType,  
											   unsigned char *pAccessPWD,
											   unsigned int  nStartAddr,
											   unsigned int nWaitTime,
											   unsigned char *pWriteData, 
											   unsigned int *pToWriteLen)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReader* pReader = (CRFIDReader*)pHandle;
	return pReader->SAAT6CWriteUserData (nAntenna, nType,  pAccessPWD,nStartAddr,nWaitTime,pWriteData, pToWriteLen);
}

//////////////////////////////////////////////////////////////////////////
//5.5.9 块写Bank数据
//功能描述：此函数用来块写ISO18000-6C标签的Bank数据。
//函数原型：
//bool	SAAT_6CWriteBankData (void* pHandle, unsigned char nAntenna, unsigned char nType, unsigned char *pAccessPWD, unsigned char nBank,  unsigned char *pWriteData, unsigned char nLen)
//传入参数： 
//pHandle		打开的端口句柄
//nAntenna		为标签操作时使用的天线端口号1-4。
//nType			为操作类型，默认为0
//pAccessPWD	为要操作标签的访问密码,默认密码为4字节0
//nBank			为写入标签数据的Bank
//pWriteData	为写入标签的用户数据区的数据
//nLen			为写入标签的用户数据区的长度
//返回值：true：操作成功；false：操作失败。
//////////////////////////////////////////////////////////////////////////
bool RFID_API  __stdcall SAAT_6CWriteBankData (void* pHandle, unsigned char nAntenna, unsigned char nType, unsigned char *pAccessPWD,
											   unsigned char nBank,  unsigned char *pWriteData, unsigned char nLen)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReader* pReader = (CRFIDReader*)pHandle;
	return pReader->SAAT6CWriteBankData (nAntenna, nType,  pAccessPWD,nBank,pWriteData,nLen);
}

//////////////////////////////////////////////////////////////////////////
//5.5.10 块擦Bank数据
//功能描述：此函数用来块擦除ISO18000-6C标签的Bank数据。
//函数原型：
//bool	SAAT_6CClearBankData (void* pHandle, unsigned char nAntenna, unsigned char nType, unsigned char *pAccessPWD, unsigned char nBank, unsigned char nStartAddr, unsigned char nLen)
//传入参数： 
//pHandle		打开的端口句柄
//nAntenna		为标签操作时使用的天线端口号1-4
//nType			为操作类型，默认为0x00
//pAccessPWD	为要操作标签的访问密码,默认密码为字节
//nBank			为写入标签数据的Bank
//nStartAddr	为擦除标签的数据区的首地址
//nLen			为擦除标签的数据区的长度
//返回值： true：操作成功；false：操作失败。
//////////////////////////////////////////////////////////////////////////
bool RFID_API  __stdcall SAAT_6CClearBankData (void* pHandle, unsigned char nAntenna, unsigned char nType, unsigned char *pAccessPWD,
											   unsigned char nBank, unsigned char nStartAddr, unsigned char nLen)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReader* pReader = (CRFIDReader*)pHandle;
	return pReader->SAAT6CClearBankData (nAntenna, nType,  pAccessPWD,nBank,nStartAddr,nLen);
}

//////////////////////////////////////////////////////////////////////////
//5.5.11 配置访问密码
//功能描述：此函数用于设置ISO18000-6C标签的访问密码。
//函数原型：
//bool	SAAT_6CAccessPWDSet (void *pHandle, unsigned char nAntenna, unsigned char nType, unsigned char *pOrgPWD, unsigned char *pNewPWD)
//传入参数：
//pHandle		打开的端口句柄
//nAntenna		为标签操作时使用的天线端口号1-4
//nType			为操作类型，此项为0
//pOrgPWD		为4字节原访问密码，出厂默认为4字节0。
//pNewPWD		为4字节新访问密码
//返回值：true：操作成功；false：操作失败。
//说明：
//标签出厂默认的访问密码为4字节0。
//如果密码所在Bank未锁定，全零的密码也可执行写操作（细节参见EPC协议）。
//////////////////////////////////////////////////////////////////////////
bool RFID_API  __stdcall SAAT_6CAccessPWDSet (void *pHandle, unsigned char nAntenna, unsigned char nType, unsigned char *pOrgPWD, 
											  unsigned char *pNewPWD)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReader* pReader = (CRFIDReader*)pHandle;
	return pReader->SAAT6CAccessPWDSet (nAntenna, nType,  pOrgPWD,pNewPWD);
}

//////////////////////////////////////////////////////////////////////////
//5.5.12 更改销毁密码
//功能描述：此函数用于更改ISO18000-6C标签的销毁密码。
//函数原型：
//bool	SAAT_6CDestroyPWDSet (void *pHandle, unsigned char nAntenna, unsigned char *pAccessPWD, unsigned char nType, unsigned char *pDestroyPWD )
//传入参数： 
//pHandle		打开的端口句柄
//nAntenna 		标签操作时使用的天线端口号1-4
//pAccessPWD	标签访问密码，4字节
//nType 		为操作类型此项为0
//pDestroyPWD	标签4字节销毁密码
//返回值：true：操作成功；false：操作失败。
//说明：
//访问密码：要进行操作的标签的访问密码。如果要更改的销毁密码区已被锁定，则更改销毁密码时必须使用正确的访问密码。
//新销毁密码：要设置的标签的新的销毁密码，出厂时默认的销毁密码为8个零。
//EPC协议规定标签在执行销毁操作时其销毁密码必须为非零。
//如果密码所在Bank未锁定，全零的密码也可执行写操作（细节参见EPC协议）。
//////////////////////////////////////////////////////////////////////////
bool RFID_API  __stdcall SAAT_6CDestroyPWDSet (void *pHandle, unsigned char nAntenna,unsigned char nType, unsigned char *pAccessPWD, 
											   unsigned char *pDestroyPWD )
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReader* pReader = (CRFIDReader*)pHandle;
	return pReader->SAAT6CDestroyPWDSet (nAntenna, nType,  pAccessPWD,pDestroyPWD);
}

//////////////////////////////////////////////////////////////////////////
//5.5.13 标签锁状态配置
//功能描述：函数用于设置标签的锁状态。
//函数原型：
//bool	SAAT_6CTagLock (void *pHandle, unsigned char nAntenna, unsigned char *pAccessPWD, unsigned char nType, unsigned char nBank)
//传入参数：
//pHandle 		打开的端口句柄
//nAntenna		标签操作时使用的天线端口号1-4
//pAccessPWD	标签访问密码（4字节）
//nType			锁操作类型	，定义见说明。
//nBank			执行锁操作的Bank，定义见说明。
//返回值：true：操作成功；false为操作失败。
//说明：
//Bank类型：ISO18000-6C标签的每个Bank都可以被单独进行锁操作，设置为不同的锁状态，在操作中要求指出要进行锁操作的Bank。
//代码			 定义	
//0x00			所有Bank
//0x01 			TID Bank
//0x02			EPC Bank
//0x03			USER Bank
//0x04			访问密码区
//0x05			销毁密码区
//锁操作类型：ISO18000-6C协议定义标签可以有4种锁操作。
//代码			定义
//0x00 			锁定
//0x01			解锁
//0x02 			永久锁定
//0x03 			永久开放
//※	EPC标签的TID区在出厂时已被写入TID码并且设置不可逆的永久锁定，因此执行“所有Bank”的解锁操作时不会执行TID区的解锁。
//////////////////////////////////////////////////////////////////////////
bool RFID_API  __stdcall  SAAT_6CTagLock (void *pHandle, unsigned char nAntenna, unsigned char *pAccessPWD, unsigned char nType,
										  unsigned char nBank)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReader* pReader = (CRFIDReader*)pHandle;
	return pReader->SAAT6CTagLock (nAntenna, pAccessPWD,  nType,nBank);
}

//////////////////////////////////////////////////////////////////////////
//5.5.14 标签销毁
//功能描述：此函数用于对标签进行销毁（KILL，又译灭活）操作。
//函数原型：
//bool	SAAT_6CKillTag (void *pHandle, unsigned char nAntenna,unsigned char *pDestroyPWD, unsigned char *pEPC, int nEPCLen)
//传入参数：
//pHandle		打开的端口句柄
//nAntenna		标签操作时使用的天线端口号1-4 
//pDestroyPWD	标签的销毁密码（4字节）
//pEpc			要销毁标签的EPC码
//nEPCLen		EPC长度，一般为12
//返回值：true：操作成功；false：操作失败。
//说明：
//因灭活指令为不可逆转操作，为防止对其他标签做误操作，该指令应附加一个EPC编码域，读写器在EPC码与读取标签的EPC码匹配时才执行灭活操作。如果该域不存在，则对读到的标签进行灭活。
//EPC码的长度依据不同信号的标签是有区别的，默认为12字节。
//标签的灭活密码出厂默认值为“00000000”，但协议规定标签在执行灭活操作前必须将灭活密码改为非零值。
//////////////////////////////////////////////////////////////////////////
bool RFID_API  __stdcall SAAT_6CTagKill (void *pHandle, unsigned char nAntenna,unsigned char *pDestroyPWD,
										 unsigned char *pEPC, int nEPCLen)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReader* pReader = (CRFIDReader*)pHandle;
	return pReader->SAAT6CTagKill (nAntenna, pDestroyPWD,  pEPC,nEPCLen);
}

//////////////////////////////////////////////////////////////////////////
//5.5.15 EAS标志位配置
//功能描述：此函数用于设置标签的EAS标志。
//函数原型：
//bool	SAAT_6CEASFlagSet (void *pHandle, unsigned char nAntenna, unsigned char nType, unsigned char* pAccessPwd,  int nEASFlag)
//传入参数： 
//pHandle 		打开的端口句柄
//nAntenna		标签操作时使用的天线端口号1-4
//nType			ESA设置操作模式
//pAccessPwd 	标签访问密码；
//nEASFlag		EAS标志配置
//0             取消EAS比特位
//1             设置EAS比特位
//返回值：true：操作成功；false：操作失败。
//说明：该功能需要标签支持，目前NXP某些型号标签支持，细节请咨询标签的提供商。
//////////////////////////////////////////////////////////////////////////
bool RFID_API  __stdcall SAAT_6CEASFlagSet (void *pHandle, unsigned char nAntenna, unsigned char nType,
											unsigned char* pAccessPwd,  int nEASFlag)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReader* pReader = (CRFIDReader*)pHandle;
	return pReader->SAAT6CEASFlagSet (nAntenna, nType,pAccessPwd,nEASFlag);
}

//////////////////////////////////////////////////////////////////////////
//5.5.16 启动EAS监控
//功能描述：此函数命令读写器启动或者停止执行EAS监控功能。
//函数原型：
//bool	SAAT_6CEASMonitorEnable (void *pHandle, unsigned char nAntenna, unsigned char nSetEAS)
//传入参数： 
//pHandle 		打开的端口句柄
//nAntenna		标签操作时使用的天线端口号1-4
//nSetEAS		EAS监控操作控制
//0x00  -> 读写器结束EAS监控
//0x01  -> 读写器启动EAS监控
//返回值：true：操作成功；false：操作失败。
//////////////////////////////////////////////////////////////////////////
bool  RFID_API  __stdcall SAAT_6CEASMonitorEnable (void *pHandle, unsigned char nAntenna,unsigned char nSetEAS)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReader* pReader = (CRFIDReader*)pHandle;
	return pReader->SAAT6CEASMonitorEnable (nAntenna, nSetEAS);
}


//////////////////////////////////////////////////////////////////////////
//5.5.17 监控EAS信息标志位
//功能描述：该函数检测EAS标记位 
//函数原型：
//int  SAAT_6CRevEasMsg (void *pHandle, unsigned char* nAntenna, unsigned char* pData, unsigned char* nLen)
//传入参数：
//pHandle 	    打开的端口句柄
//nAntenna   	为读写器读取到UID码的天线号
//pData	    为读取到EAS数据位
//nLen	    传入的数据区长度，传出为EAS数据长度
//返回值： 0：未接收到EAS信息；1：接收到EAS信息
//////////////////////////////////////////////////////////////////////////
int  RFID_API  __stdcall SAAT_6CRevEasMsg (void *pHandle, unsigned char* nAntenna, unsigned char* pData,
										   unsigned char* nLen)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReader* pReader = (CRFIDReader*)pHandle;
	return pReader->SAAT6CRevEasMsg(nAntenna,pData,nLen);
}


//////////////////////////////////////////////////////////////////////////
//5.6.1 API版本信息查询
//功能描述：此函数用来查询当前使用API的版本信息。
//函数原型：
//bool	SAAT_Copyright (void *pHandle, char* copyright)
//传入参数： 
//pHandle 		打开的端口句柄
//copyright		版本信息
//返回值：true：操作成功；false：操作失败。
//////////////////////////////////////////////////////////////////////////
bool RFID_API __stdcall SAAT_Copyright(void** pHandle, char* copyright)
{
	/*if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReader* pReader = (CRFIDReader*)pHandle;
	return pReader->SAATCopyright (copyright);*/
	strcpy(copyright, mCopyright);
	return true;
}



//////////////////////////////////////////////////////////////////////////
//5.6.2 设置API动态库语言类型
//功能描述：此函数用来设置API动态库语言类型。
//函数原型：
//bool   SAAT_SetLanguageType (void *pHandle, char* szType)
//传入参数： 
//pHandle 		打开的端口句柄
//szType		语言类型,cn为简体中文,tw为繁体中文,en为英语
//返回值：true：操作成功；false：操作失败。
//////////////////////////////////////////////////////////////////////////
bool RFID_API  __stdcall SAAT_SetLanguageType (void* pHandle,char* szType)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReader* pReader = (CRFIDReader*)pHandle;
	return pReader->SAATSetLanguageType (szType);
}


//////////////////////////////////////////////////////////////////////////
//5.6.3 获取出错信息
//功能描述：此函数用于获得读写器返回出错信息
//函数原型：
//bool	SAAT_GetErrorMessage(void *pHandle,char *szMsg, int nLen);
//传入参数：
//pHandle		打开的端口句柄	 
//szMsg			返回错误信息
//nLen			szMsg缓冲区的长度
//返回值：true：操作成功；false：操作失败。
//////////////////////////////////////////////////////////////////////////
bool RFID_API  __stdcall SAAT_GetErrorMessage(void *pHandle,char *szMsg, int nLen)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReader* pReader = (CRFIDReader*)pHandle;
	pReader->GetErrorMsg (szMsg,nLen);
	return true;
}


//////////////////////////////////////////////////////////////////////////
//5.6.4 获取出错代码
//功能描述：此函数用于获得读写器返回出错代码
//函数原型：
//bool	SAAT_GetErrorCode (void *pHandle,int *pCode);
//传入参数：
//pHandle		打开的端口句柄	 
//pCode			返回错误代码
//返回值：true：操作成功；false：操作失败。
//////////////////////////////////////////////////////////////////////////
bool RFID_API  __stdcall SAAT_GetErrorCode(void *pHandle,int *pCode)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReader* pReader = (CRFIDReader*)pHandle;
	*pCode = pReader->GetErrorCode();

	return true;
}


//////////////////////////////////////////////////////////////////////////
//5.7.2 GPRS模块参数配置
//功能描述：此函数用于配置GPRS模块参数。
//函数数原型：
//bool	SAAT_GPRSParaSet (void* pHandle ,unsigned char nType, unsigned char* pPara, unsigned char nLen)
//传入参数：
//pHandle    	打开的端口句柄
//nType  	    配置的参数类型（定义见说明）
//pPara		    配置的GPRS模块参数数据
//nLen		    pPara的长度
//返回值：true：操作成功；false为操作失败
//说明: 
//0x00			GPRS模块串口通信波特率
//0x01			IP地址
//0x02			端口号
//0x03			TCP/UDP通信方式选择
//设置的参数: 
//波特率:
//0x00			4800
//0x01			9600
//0x02			19200
//0x03			38400
//0x04			57600
//0x05			115200
//IP地址为4字节，不包含子网掩码及网关参数
//端口号2字节
//////////////////////////////////////////////////////////////////////////
bool RFID_API  __stdcall SAAT_GPRSParaSet (void* pHandle,unsigned char nType, unsigned char* pPara, unsigned char nLen)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReader* pReader = (CRFIDReader*)pHandle;
	return pReader->SAATGPRSParaSet (nType,pPara,nLen);
}

//////////////////////////////////////////////////////////////////////////
//5.7.1 GPRS模块参数查询
//功能描述：此函数用于查询GPRS模块参数。
//函数原型：
//bool	SAAT_GPRSParaQuery(void* pHandle ,int nType, unsigned char* pPara,unsigned char *pLen)
//传入参数：
//pHandle 	打开的端口句柄
//nType 	   为查询参数类型（定义见说明）
//pPara		读写器返回的GPRS模块参数数据
//pLen		传入时为pPara长度，传出时为实际返回长度
//返回值：true：操作成功； false：操作失败。
//说明: 
//0x00			GPRS模块串口通信波特率
//0x01			IP地址
//0x02			端口号
//0x03			TCP/UDP通信方式选择
//类型返回: 
//波特率:
//0x00			4800
//0x01			9600
//0x02			19200
//0x03			38400
//0x04			57600
//0x05			115200
//IP地址为4字节，不包含子网掩码及网关参数
//端口号2字节
//////////////////////////////////////////////////////////////////////////
bool RFID_API  __stdcall SAAT_GPRSParaQuery (void* pHandle,int nType, unsigned char* pPara,unsigned char *pLen)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReader* pReader = (CRFIDReader*)pHandle;
	return pReader->SAATGPRSParaQuery (nType,pPara,pLen);
}


//////////////////////////////////////////////////////////////////////////
//5.7.2 WIFI模块参数配置
//功能描述：此函数用于配置WIFI模块参数。
//函数数原型：
//bool	SAAT_WIFIParaSet (void* pHandle ,unsigned char nType, unsigned char* pPara, unsigned char nLen)
//传入参数：
//pHandle    	打开的端口句柄
//nType  	    配置的参数类型（定义见说明）
//pPara		    配置的WIFI模块参数数据
//nLen		    pPara的长度
//返回值：true：操作成功；false为操作失败
//说明: 
//0x00			WIFI模块串口通信波特率
//0x01			MAC地址
//0x02			IP地址
//0x03			TCP端口号
//0x04			UDP端口号
//类型返回: 
//波特率:
//0x00			4800
//0x01			9600
//0x02			19200
//0x03			38400
//0x04			57600
//0x05			115200
//IP地址为12字节，包含子网掩码及网关参数
//端口号2字节
//////////////////////////////////////////////////////////////////////////
bool RFID_API  __stdcall SAAT_WIFIParaSet (void* pHandle,unsigned char nType, unsigned char* pPara, unsigned char nLen)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReader* pReader = (CRFIDReader*)pHandle;
	return pReader->SAATWIFIParaSet (nType,pPara,nLen);
}


//////////////////////////////////////////////////////////////////////////
//5.7.3 WIFI模块参数查询
//功能描述：此函数用于查询WIFI模块参数。
//函数原型：
//bool	SAAT_WIFIParaQuery(void* pHandle ,int nType, unsigned char* pPara,unsigned char *pLen)
//传入参数：
//pHandle 	打开的端口句柄
//nType 	   为查询参数类型（定义见说明）
//pPara		读写器返回的WIFI模块参数数据
//pLen		传入时为pPara长度，传出时为实际返回长度
//返回值：true：操作成功； false：操作失败。
//说明: 
//0x00			WIFI模块串口通信波特率
//0x01			MAC地址
//0x02			IP地址
//0x03			TCP端口号
//0x04			UDP端口号
//类型返回: 
//波特率:
//0x00			4800
//0x01			9600
//0x02			19200
//0x03			38400
//0x04			57600
//0x05			115200
//IP地址为12字节，包含子网掩码及网关参数
//端口号2字节
//////////////////////////////////////////////////////////////////////////
bool RFID_API  __stdcall SAAT_WIFIParaQuery (void* pHandle,int nType, unsigned char* pPara,unsigned char *pLen)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReader* pReader = (CRFIDReader*)pHandle;
	return pReader->SAATWIFIParaQuery (nType,pPara,pLen);
}
/***********************************集成模块指令******************************************/


//////////////////////////////////////////////////////////////////////////
//读写器系统测试
//功能：用于测试读写器
//参数：
//	pHandle:		打开的端口句柄
//	nType ：	测试模式
//	pTestParm: 	测试模式参数
//	nLen:			测试模式参数的长度
//测试模式:
//		0x00	 退出测试模式；
//		0x01	读写器进入老化测试模式，持续自动开关功放各10秒的操作；
//		0x02	读写器进入调制度测量模式，射频端口输出40KHz占空比50%的方波调制信号；
//		0x03	读写器进入输出功率和输出频率测量模式，读写器输出指定功率，频率在规定范围内扫描；
//		0x04	读写器进入射频板闭环测试模式，发送测试收据并在接受回路接收，测试射频板环路是否正常。           
//		0x05	读写器进入模拟读卡模式，当接收到读UID或EPC码指令时不真正执行读卡操作，而是直接返回随机生成的卡号；	
//返回值： true为操作成功, false为操作失败
//////////////////////////////////////////////////////////////////////////
bool RFID_API  __stdcall SAAT_SysTest(void* pHandle ,unsigned char nType,unsigned char nAntenna, unsigned char *pTestParm, unsigned char nLen)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReader* pReader = (CRFIDReader*)pHandle;
	return pReader->SAATSysTest (nType,nAntenna,pTestParm,nLen);
}

//////////////////////////////////////////////////////////////////////////

bool RFID_API STDCALL SAAT_YTagWorkModeQuery(void* pHandle, unsigned char nOpType, unsigned char nIDType, unsigned char* pIDCode, unsigned char* pTagPwd, unsigned char* pWorkMode, unsigned char* pUpLoadIDType, unsigned short* pSleepTime, unsigned char* pSleepInterval, unsigned char* pBatteryVoltage, unsigned char* pRemainingCapacity)
{
	return false;
}

bool RFID_API STDCALL SAAT_YTagFatorySet(void* pHandle, unsigned char nOpType, unsigned char nIDType, unsigned char* pIDCode, unsigned char* pTagPwd, unsigned char nTagType, unsigned char nHardWareVersion, unsigned char nSoftWareVersion, unsigned char nBatteryConfiguration, unsigned char nNominalCapacity)
{
	return false;
}

bool RFID_API STDCALL SAAT_YTagFatoryQuery(void* pHandle, unsigned char nOpType, unsigned char nIDType, unsigned char* pIDCode, unsigned char* pTagPwd, unsigned char* pTagType, unsigned char* pHardWareVersion, unsigned char* pSoftWareVersion, unsigned char* pBatteryConfiguration, unsigned char* pNominalCapacity)
{
	return false;
}

bool RFID_API STDCALL SAAT_YTagResetToFatory(void* pHandle, unsigned char nOpType, unsigned char nIDType, unsigned char* pIDCode, unsigned char* nTagPwd)
{
	return false;
}

bool RFID_API STDCALL SAAT_YAntennaParmSet(void* pHandle, unsigned char* pPara, unsigned char nLen)
{
	if (NULL == pHandle)
	{
		return false;
	}

	CRFIDReader* pReader = (CRFIDReader*)pHandle;
	return pReader->SAATAntennaParmSet(pPara, nLen);
}

bool RFID_API STDCALL SAAT_YAntennaParmQuery(void* pHandle, unsigned char* pPowerRecvPlus, unsigned char* p2401FreqSendPwr, unsigned char* pAttenuatorPower)
{
	if (NULL == pHandle)
	{
		return false;
	}

	CRFIDReader* pReader = (CRFIDReader*)pHandle;
	return pReader->SAATYAntennaParmQuery(pPowerRecvPlus, p2401FreqSendPwr, pAttenuatorPower);
}

bool RFID_API STDCALL SAAT_YRFParaSet(void* pHandle, unsigned char nType, unsigned char nPara)
{
	if (NULL == pHandle)
	{
		return false;
	}
	CRFIDReader* pReader = (CRFIDReader*)pHandle;
	nType = 0;
	char nParaLen = 1;
	return pReader->SAATRFParaSet(nType, nParaLen, &nPara);
}

bool RFID_API STDCALL SAAT_YRFParaQuery(void* pHandle, unsigned char nType, unsigned char* pPara)
{
	if (NULL == pHandle)
	{
		return false;
	}
	//bool SAATRFParaQuery(unsigned char nType, unsigned char* pPara, unsigned char* pLen);// 载波参数查询
	CRFIDReader* pReader = (CRFIDReader*)pHandle;
	nType = 0;
	char nParaLen = 1;
	unsigned char pLen = 5;
	return pReader->SAATRFParaQuery(nType, pPara, &pLen);
}

bool RFID_API STDCALL SAAT_YCarrierWaveOp(void* pHandle, unsigned char nType)
{
	return false;
}

bool RFID_API STDCALL SAAT_YBuzzerSet(void* pHandle, unsigned char nPara)
{
	return false;
}

bool RFID_API STDCALL SAAT_YBuzzerQuery(void* pHandle, unsigned char* pPara)
{
	return false;
}

bool RFID_API STDCALL SAAT_SetLangId(void* pHandle, unsigned char nLangId)
{
	return false;
}

//读写器系统测试用函数
//功能：直接发送底层数据(也可用于测试读写器对读卡垃圾数据处理能力)
//参数：
//	pHandle:		打开的端口句柄
//	pTestParm: 		测试参数
//	nLen:			测试参数的长度	
//返回值： true为操作成功, false为操作失败
//////////////////////////////////////////////////////////////////////////
bool RFID_API  __stdcall SAAT_RawSendData(void* pHandle , unsigned char *pSendData, unsigned char nLen)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReader* pReader = (CRFIDReader*)pHandle;
	return pReader->SAATRawSendData(pSendData,nLen);
	
}

//直接收取底层数据
//功能：直接收取底层数据
//参数：
//	pHandle:		打开的端口句柄
//	pTestParm: 		发送数据
//	nLen:			数据长度	
//	nWaitTime       超时时间
//返回值： true为操作成功, false为操作失败
//////////////////////////////////////////////////////////////////////////
bool RFID_API  __stdcall SAAT_RawRevData(void* pHandle , unsigned char *pRecvData, unsigned char* pLen,int nWaitTime)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReader* pReader = (CRFIDReader*)pHandle;
	return pReader->SAATRawRevData(pRecvData,pLen,nWaitTime);
}

//直接发送并收取底层数据
//功能：直接发送并收取底层数据
//参数：
//	pHandle:		打开的端口句柄
//	pSendData: 		发送数据
//	nLen:			发送数据长度	
//  pRecvData		接收数据
//	pLen			接收数据长度
//  nWaitTime       超时时间
//返回值： true为操作成功, false为操作失败
//////////////////////////////////////////////////////////////////////////
bool RFID_API  __stdcall SAAT_RawSendAndRevData(void* pHandle , 
												unsigned char *pSendData,
												unsigned char nLen,
												unsigned char *pRecvData,
												unsigned char *pLen,
												unsigned char nWaitTime)
{
	return true;
}

bool RFID_API __stdcall SAAT_YTagSelect(void* pHandle, unsigned char nOpEnable, unsigned char nMatchType, unsigned char* MatchData, unsigned char nLenth)
{
	return false;
}

//////////////////////////////////////////////////////////////////////////
//读写器配置进入透传模式用函数（WIFI设备调用）
//功能：读写器配置进入透传模式
//参数：
//	pHandle:		打开的端口句柄
//	nType: 			类型参数参数 0x00-WIFI  0xFD 复位波特率SAAT_ResetWifiBaund
//返回值： true为操作成功, false为操作失败
//////////////////////////////////////////////////////////////////////////
bool RFID_API  __stdcall SAAT_EnterTrans(void* pHandle ,unsigned char nType)
{
	if( NULL == pHandle )
		return false;

	CRFIDReader* pReader = (CRFIDReader*)pHandle;
	return pReader->SAATEnterTrans(nType);
}

//////////////////////////////////////////////////////////////////////////
//读取标签EPC+TID码
//功能描述：此函数用于命令读写器执行“读取EPC码和TID码指令”
//函数原型：
//bool	SAAT_6CReadEPCTIDCode ( void *pHandle,unsigned char nAntenna, unsigned char nType, unsigned char nTagCount)
//传入参数：
//pHandle		打开的端口句柄
//nAntenna		为读取操作使用的天线号(0为天线轮循，1为天线1，2为天线2，3为天线3，4为天线4)
//nType			为操作模式
//00：对同一个标签的EPC码读写器只向上位机返回一次，并要求上位机接收后给予读写器"返回数据确认"。
//01"：读写器将读取到的所有的标签EPC码全部上传到上位机并不要求上位机接收后给予读写器"返回数据确认"，直到上位机下发"关功放"命令后才停止读标签EPC码，一般使用此操作模式。
//nTagCount    为同时预计读取标签数, 预计工作环境中一次需要同时读取的最大标签数，设计为到250张，实际读取数超过500张
//返回值：true：操作成功；false：操作失败。
//////////////////////////////////////////////////////////////////////////
bool RFID_API  __stdcall SAAT_6CReadEPCTIDCode ( void *pHandle,unsigned char nAntenna, unsigned char nType, unsigned int nTagCount)
{
	if( NULL == pHandle )
		return false;

	CRFIDReader* pReader = (CRFIDReader*)pHandle;
	pReader->SAAT6CReadEPCTIDCode(nAntenna, nType, nTagCount);

	return true;
}

//////////////////////////////////////////////////////////////////////////
//接收EPC+TID码
//功能描述：此函数用于接收读写器返回的EPC码和TID码
//函数原型：
//int	SAAT_6CRevEPCTIDMsg (void *pHandle, unsigned char* nAntenna, 
//			unsigned char* pEPCData, unsigned char* nEPCLen,
//			unsigned char* pTIDData, unsigned char* nTIDLen)
//传入参数：
//pHandle 	   打开的端口句柄
//nAntenna	   为读写器读取到EPC码的天线号
//pEPCData	   为读写器返回的EPC码数据 
//nEPCLen	   传入时为pEPCData长度，传出时为EPC数据长度，一般为12。
//pTIDData	   为读写器返回的EPC码数据 
//nTIDLen	   传入时为pEPCData长度，传出时为EPC数据长度，一般为12。
//返回值： 0：未接收到EPC码；1：接收到EPC码。
//////////////////////////////////////////////////////////////////////////
int  RFID_API  __stdcall SAAT_6CRevEPCTIDMsg (void *pHandle, unsigned char* nAntenna, 
											  unsigned char* pEPCData, unsigned char* nEPCLen, 
											  unsigned char* pTIDData, unsigned char* nTIDLen)
{
	if( NULL == pHandle )
		return 0;

	CRFIDReader* pReader = (CRFIDReader*)pHandle;
	return pReader->SAAT6CRevEPCTIDMsg(nAntenna,pEPCData,nEPCLen,pTIDData,nTIDLen);
}




//////////////////////////////////////////////////////////////////////////
// 7.2 读写器时间设置
//功能：用于设置读写器时间
//参数：
//		pHandle :	打开的端口句柄
//		pPara:		读写器返回的读写器时间数据
//		pLen:		参数数据长度
//返回值： true为操作成功, false为操作失败
//////////////////////////////////////////////////////////////////////////
bool RFID_API  __stdcall SAAT_SetReaderTime (void* pHandle ,unsigned char* pPara,unsigned char nLen)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReader* pReader = (CRFIDReader*)pHandle;
	return pReader->SAATSetReaderTime(pPara, nLen);
}


//////////////////////////////////////////////////////////////////////////
//7.3 查询器时间查询
//功能：用于查询读写器时间
//参数：
//		pHandle :	打开的端口句柄
//		pPara:		读写器返回的读写器时间数据
//		pLen:		参数数据长度
//返回值： true为操作成功, false为操作失败
//////////////////////////////////////////////////////////////////////////
bool RFID_API  __stdcall SAAT_ReaderTimeQuery (void* pHandle, unsigned char* pPara,unsigned char *pLen)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReader* pReader = (CRFIDReader*)pHandle;
	return pReader->SAATReaderTimeQuery(pPara, pLen);
}


//////////////////////////////////////////////////////////////////////////
// 7.4 Flash缓存计数查询
//功能：缓存计数查询
//参数：
//		pHandle :	打开的端口句柄
//		pPara:		
//		pLen:		总计数
//返回值： true为操作成功, false为操作失败
//////////////////////////////////////////////////////////////////////////
bool RFID_API __stdcall SAAT_FlashTotalCountQuery (void* pHandle, unsigned char* pPara, unsigned char *pLen)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReader* pReader = (CRFIDReader*)pHandle;
	return pReader->SAATFlashTotalCountQuery(pPara, pLen);
}

//////////////////////////////////////////////////////////////////////////
// 7.5 Flash缓存数据查询
//功能：缓存计数查询
//参数：
//		pHandle :	打开的端口句柄
//		nOpType :
//		pPara:	
//		pLen:		总计数
//返回值： true为操作成功, false为操作失败
//////////////////////////////////////////////////////////////////////////
bool RFID_API __stdcall SAAT_FlashDataQuery(void* pHandle , unsigned char nOpType, unsigned char* pPara, unsigned char *pLen)
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReader* pReader = (CRFIDReader*)pHandle;
	return pReader->SAATFlashDataQuery(nOpType, pPara, pLen);
}

//////////////////////////////////////////////////////////////////////////
// 7.6 Flash缓存数据清除
//功能：缓存计数查询
//参数：
//		pHandle :	打开的端口句柄
//返回值： true为操作成功, false为操作失败
//////////////////////////////////////////////////////////////////////////
bool RFID_API __stdcall SAAT_ClearFlash (void* pHandle )
{
	if( NULL == pHandle )
	{
		return false;
	}

	CRFIDReader* pReader = (CRFIDReader*)pHandle;
	return pReader->SAATClearFlash();
}


bool RFID_API STDCALL SAAT_WCommunicatParaSet(void* pHandle, unsigned char nType, unsigned char* pPara, unsigned char nLen)
{
	return false;
}

int RFID_API STDCALL SAAT_YRevIDMsgDecRssiExpand(void* pHandle,
	unsigned char* nTagType, unsigned int* pId, 
	int* nRssi, int* nAntenna, 
	int* nParam1,
	int* nParam2)
{
	if (NULL == pHandle)
	{
		return -1;
	}

	CRFIDReader* pReader = (CRFIDReader*)pHandle;
	return pReader->SAATYRevIDMsgDecRssiExpand( nTagType, pId,  nRssi,  nAntenna,nParam1,nParam2);
}

bool RFID_API STDCALL SAAT_YAntennaPort_EXSet(void* pHandle, 
	unsigned int nPortEnable,
	unsigned int nPollTime,
	unsigned int nParam)
{
	if (NULL == pHandle)
	{
		return false;
	}

	CRFIDReader* pReader = (CRFIDReader*)pHandle;
	return pReader->SAATYAntennaPortEXSet(nPortEnable, nPollTime, nParam);
}

bool RFID_API STDCALL SAAT_YAntennaPort_EXQuery(void* pHandle, unsigned int* nPortEnable, unsigned int* nPollTime, unsigned int* nParam)
{
	if (NULL == pHandle)
	{
		return false;
	}

	CRFIDReader* pReader = (CRFIDReader*)pHandle;
	return pReader->SAATYAntennaPortEXQuery(nPortEnable, nPollTime, nParam);
}

bool RFID_API STDCALL SAAT_Updata(void* pHandle, unsigned char nType, int nFileLen, unsigned char* pCRC32, unsigned char nFileNameLen, unsigned char* pFileName)
{
	return false;
}

