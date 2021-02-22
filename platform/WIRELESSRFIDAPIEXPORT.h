/***********************************************************************
* Module:  WIRELESSRFIDAPIEXPORT.h 
* Author:  
* Modified: 2016年9月1日 14:23:09
* Purpose: 
***********************************************************************/
#pragma once

#ifndef  _WIRELESS_RFIDEXPORT_H
#define  _WIRELESS_RFIDEXPORT_H

#ifdef WIRELESS_RFIDAPI_EXPORTS
#define WIRELESS_RFID_API __declspec( dllexport )
#else
#define WIRELESS_RFID_API __declspec( dllimport )
#endif

extern "C"
{
	//////////////////////////////////////////////////////////////////////////
	//命令定义
	//描述：定义发送给读写器的指令。		
	//////////////////////////////////////////////////////////////////////////
	typedef enum {
		COM_SYS_CFG						= (0x00),//系统信息配置
		COM_SYS_QUERY					= (0x01),//系统信息查询
		COM_WORKMOD_CFG					= (0x02),//工作模式配置
		COM_WORKMOD_QUERY				= (0x03),//工作模式查询
		COM_TEST_CONTROL				= (0x0A),//系统测试控制
		COM_PARA_OP						= (0x10),//参数表操作
		COM_ANTENNA_SET					= (0x11),//射频端口参数配置
		COM_ANTENNA_QUERY				= (0x12),//射频端口参数查询
		COM_CARRYWAVE_SET				= (0x13),//载波参数配置
		COM_CARRYWAVE_QUERY				= (0x14),//载波参数查询
		COM_COMMUNI_SET					= (0x15),//通信参数配置
		COM_COMMUNI_QUERY				= (0x16),//通信参数查询
		COM_NETPARA_SET					= (0x17),//网络参数配置
		COM_NETPARA_QUERY				= (0x18),//网络参数查询
		COM_TAG_SET						= (0x19),//标签操作参数配置
		COM_TAG_QUERY					= (0x1A),//标签操作参数查询
		COM_EXTENDBOARD_SET				= (0x1B),//扩展板参数配置
		COM_EXTENDBOARD_QUERY			= (0x1C),//扩展板参数查询
		COM_ANTENNA_SET_EX				= (0x1E),//有源天线参数扩展设置
		COM_ANTENNA_QUERY_EX			= (0x1F),//有源天线参数扩展查询
		COM_CARRY_OP					= (0x20),//载波操作指令
		COM_IO_OP						= (0x21),//输出操作指令
		COM_INPUT_QUERY					= (0x22),//输入查询指令
		READING_IO_CONFIG				= (0x23),//读卡指示配置指令
		READING_IO_QUERY				= (0x24),//读卡指示查询指令
		COM_IO_PULSESET					= (0x25),//读卡指示脉冲配置
		COM_IO_PULSEQUERY				= (0x26),//读卡指示脉冲查询
		COM_READER_REBOOT				= (0x2A),//重启指令
		COM_OPEN_CONN					= (0x50),//打开连接
		COM_CLOSE_CONN					= (0x51),//关闭连接
		COM_STOP_READ					= (0x53),//停止读卡
		COM_SEND_HEART					= (0x58), //心跳包
		WIRELESS_RFID_IO_STATE			= (0x59),//无线接收IO口状态包
		COM_YSEND_READID				= (0x61),//有源读卡指令
		COM_YMAKE_TAGUPLOAD				= (0x62),//接收标签自动上传数据 
		COM_YSTOP						= (0x6F),//0x6F有源停止读卡 
		COM_6BSELECT_TAG				= (0x80),//6B标签选择命令
		COM_6BREAD_UID					= (0x81),//6B读取UID码命令
		COM_6BREADUSER_DATA				= (0x82),//6B读标签数据
		COM_6BWRITEUSER_DATA			= (0x83),//6B写标签数据
		COM_6BLOCK_TAGDATA				= (0x84),//6B锁标签数据
		COM_6BLOCK_QUERY				= (0x85), //6B锁标签查询),
		COM_6CSELECT_EPCTAG				= (0x90),//6C标签选择
		COM_6CREAD_EPC					= (0x91),//6C读EPC码
		COM_6CREAD_TID					= (0x92),//6C读TID码
		COM_6CREAD_EPCTID				= (0x9F),//6C读EPC+TID码
		COM_6CWRITE_EPCDATA				= (0x93),//6C写EPC数据
		COM_6CREADUSER_DATA				= (0x94),//6C读用户数据区
		COM_6CWRITEUSER_DATA			= (0x95),//6C写用户数据区
		COM_6CBLOCKWRITE_DATA			= (0x96),//块写Bank数据
		COM_6CBLOCKCLEAR_DATA			= (0x97),//块擦Bank数据
		COM_6CACCESSPWD_CFG				= (0x98),//配置访问密码
		COM_6CDESTORYPWD_CFG			= (0x99),//设置销毁密码指令
		COM_6CLOCK_TAGCFG				= (0x9A),//标签锁状态配置
		COM_DESTORY_TAG					= (0x9B),//标签灭活指令
		COM_EASFLAG_CFG					= (0x9C),//EAS标志配置指令
		COM_EAS_ENABLE					= (0x9D),//EAS监控功能设置指令
		READER_TIME_SET					= (0xB0),//读写器时间设置
		READER_TIME_QUERY				= (0xB1),//读写器时间查询
		READER_FLASHDATA_QUERY			= (0xB2),//FLASH数据查询
		READER_FLASHDATACOUNT_QUERY		= (0xB3),//FLASH数据标签数查询
		READER_FLASHCLEAR				= (0xB4),//清FLASH数据
		COM_GPRS_SET					= (0xC0),//GPRS设置
		COM_GPRS_QUERY					= (0xC1),//GPRS查询
		COM_WIFI_SET					= (0xC2),//WIFI设置
		COM_WIFI_QUERY					= (0xC3),//WIFI查询
		COM_WIFI_TRANS_REST				= (0xC4),//WIFI进入透传或者复位

		R2000_LOG_OPER					= (0xE0), // R2000 开启/关闭日志
		R2000_LOG_MESSAGE				= (0xE1),// R2000 错误消息 主动上传
		R2000_UPDATA_FILE				= (0xE2),// R2000 模块升级 传递 文件名
		WIRELESS_RFID_ACK				= (0xd0),//无线接收ack包
		WIRELESS_RFID_ACK_2				= (0xd1),//无线接收数据回复包
		WIRELESS_RFID_IO_STATE_ACK		= (0xd2),//无线接收IO口状态 回复包
		WIRELESS_RFID_Heart_ACK			= (0xd3),//无线接收IO口状态 回复包
	} WIRELESS_RFIDCommandCode;

	//////////////////////////////////////////////////////////////////////////
	//读写器的连接类型定义
	//描述：定义与读写器通信的类型。
	//READER_TCP_SERVER:读写器为TCP客户端，PC端为TCP服务端方式连接
	//READER_TCP_CLIENT:读写器为TCP服务端，PC端为TCP客户端方式连接
	//READER_COM:通过串口连接读写器
	//READER_USB:通过usb口连接读写器
	//READER_UDP:通过udp，PC作为客户端连接读写器
	//////////////////////////////////////////////////////////////////////////
	enum READERTYPE
	{
		READER_TCP_SERVER = 0,
		READER_TCP_CLIENT,
		READER_COM,
		READER_USB,
		READER_UDP
	};

	//////////////////////////////////////////////////////////////////////////
	//读写器的信息
	//描述：调用tcp服务器启动或者添加添加客户端后，如果连接成功由回调函数返回的读写器信息。
	//ReaderType:读写器连接的类型，详细定义见READERTYPE
	//nBusAddr:总线地址
	//bIpAddr:连接的IP地址
	//bComNum:读写器 COM1－COM4 仅在COM,USB通讯模式下有效 
	//nBaud:串口（USB口）波特率
	//nPort:网络连接端口
	//////////////////////////////////////////////////////////////////////////
	struct WirelessReaderInfo
	{
		int ReaderType;
		unsigned char nBusAddr;
		unsigned char bIpAddr[32];	
		unsigned char bComNum[32];	
		unsigned int nBaud;			
		unsigned int nPort;				
	};
 
	//////////////////////////////////////////////////////////////////////////
	//读写器帧结构
	//描述：与读写器交互的数据结构。
	//bFrame:帧头 55H
	//bAddrInfo:帧信息，用于区别帧序
	//bAddr:总线地址
	//bLength:数据长度  包括指令和数据的长度
	//bCommand:指令
	//bData:数据域  +  CRC16校验
	//////////////////////////////////////////////////////////////////////////
	struct CRFrame 
	{
		unsigned char bFrame;			
		unsigned char bAddrInfo;		
		unsigned char bAddr;			
		unsigned char bLength;			
		unsigned char bCommand;			
		unsigned char bData[256];   
	};

	
	//////////////////////////////////////////////////////////////////////////
	//连接成功回调函数
	//描述：调用tcp服务器启动或者添加添加客户端的参数，回调函数用来回调连接成功的读写器信息。
	//pHandle:实例化的对象句柄
	//pReaderInfo:读写器信息	
	//////////////////////////////////////////////////////////////////////////
	typedef bool (__cdecl *READER_CALLBACK)(
		void*		pHandle,				//服务的句柄
		WirelessReaderInfo*    pReaderInfo	//接收的读写器对象
		);

	//////////////////////////////////////////////////////////////////////////
	//API初始化
	//描述：初始化API。
	//pHandle:实例化的对象句柄，传入空的地址即可，返回实例化后的对象地址	
	//////////////////////////////////////////////////////////////////////////
	bool WIRELESS_RFID_API __stdcall WIRELESS_ApiInit(void** pHandle);

	//////////////////////////////////////////////////////////////////////////
	//API退出
	//描述：退出API。
	//pHandle:由WIRELESS_ApiInit实例化的对象句柄,内部进行释放内存，并退出API	
	//////////////////////////////////////////////////////////////////////////
	bool WIRELESS_RFID_API __stdcall WIRELESS_Quit(void** pHandle);


	//////////////////////////////////////////////////////////////////////////
	//开始监听tcp服务
	//描述：开始监听tcp服务,创建一个TCP服务，监听端口，如果有连接调用回调函数。
	//pHandle:由WIRELESS_ApiInit实例化的对象句柄
	//pHostName:监听的IP地址
	//nsocketPort:监听端口
	//pCallBack:回调函数
	//////////////////////////////////////////////////////////////////////////
	bool WIRELESS_RFID_API  __stdcall WIRELESS_StartServer(
		void* pHandle,
		char *pHostName,
		int nsocketPort,
		READER_CALLBACK pCallBack);

	//////////////////////////////////////////////////////////////////////////
	//停止监听tcp服务
	//描述：停止监听tcp服务。停止监听后，
	//已经连接的读写器（包括串口、usb口、tcp客户端、tcp服务端、udp客户端）将全部断开
	//pHandle:由WIRELESS_ApiInit实例化的对象句柄
	//////////////////////////////////////////////////////////////////////////
	bool WIRELESS_RFID_API  __stdcall WIRELESS_StopServer(void* pHandle);

	
	//////////////////////////////////////////////////////////////////////////
	//关闭单个读写器
	//描述：关闭单个读写器
	//pHandle:由WIRELESS_ApiInit实例化的对象句柄
	//pWirelessReaderInfo:进行操作的读写器
	//////////////////////////////////////////////////////////////////////////
	bool WIRELESS_RFID_API  __stdcall WIRELESS_CloseReader(
		void* pHandle,
		WirelessReaderInfo* pWirelessReaderInfo);	


	//////////////////////////////////////////////////////////////////////////
	//添加一个tcp客户端连接
	//描述：添加一个tcp客户端连接
	//pHandle:由WIRELESS_ApiInit实例化的对象句柄
	//pIpAddr:连接的IP地址
	//nTcpPort:连接端口
	//pCallBack:回调函数
	//////////////////////////////////////////////////////////////////////////
	bool WIRELESS_RFID_API  __stdcall WIRELESS_AddTcpClient(
		void* pHandle,
		char *pIpAddr,
		int nTcpPort,
		READER_CALLBACK pCallBack);
	
	//////////////////////////////////////////////////////////////////////////
	//添加一个连接串口的读写器
	//描述：添加一个连接串口的读写器
	//pHandle:由WIRELESS_ApiInit实例化的对象句柄
	//nBusAddr:总线地址
	//pComNum:串口号
	//nBaud:波特率
	//pCallBack:回调函数
	//////////////////////////////////////////////////////////////////////////
	bool WIRELESS_RFID_API  __stdcall WIRELESS_AddCOMReader(
		void* pHandle,
		unsigned char nBusAddr,
		char *pComNum,
		int nBaud ,
		READER_CALLBACK pCallBack);
	
	//////////////////////////////////////////////////////////////////////////
	//添加一个连接USB的读写器
	//描述：添加一个连接USB的读写器
	//pHandle:由WIRELESS_ApiInit实例化的对象句柄
	//nBusAddr:总线地址
	//pComNum:USB号（虚拟串口号）
	//nBaud:波特率
	//pCallBack:回调函数
	//////////////////////////////////////////////////////////////////////////
	bool WIRELESS_RFID_API  __stdcall WIRELESS_AddUSBReader(
		void* pHandle,
		unsigned char nBusAddr,
		char *pComNum,
		int nBaud ,
		READER_CALLBACK pCallBack);

	//////////////////////////////////////////////////////////////////////////
	//添加一个连接UDP的读写器
	//描述：添加一个连接UDP的读写器
	//pHandle:由WIRELESS_ApiInit实例化的对象句柄
	//pIpAddr:连接的IP地址
	//nUdpPort:连接端口
	//pCallBack:回调函数
	//////////////////////////////////////////////////////////////////////////
	bool WIRELESS_RFID_API  __stdcall WIRELESS_AddUDPReader(
		void* pHandle,
		char *pIpAddr,
		int nUdpPort ,
		READER_CALLBACK pCallBack);


	//////////////////////////////////////////////////////////////////////////
	//判断是否是网络连接
	//描述：判断是否是网络连接,包括TCP客户端、TCP服务端、UDP连接
	//pHandle:由WIRELESS_ApiInit实例化的对象句柄	
	//pWirelessReaderInfo:进行操作的读写器
	//////////////////////////////////////////////////////////////////////////
	bool WIRELESS_RFID_API	__stdcall WIRELESS_IsNetReader(
		void* pHandle,
		WirelessReaderInfo* pWirelessReaderInfo);

	//////////////////////////////////////////////////////////////////////////
	//清空断开所有读写器连接
	//描述：清空断开所有读写器连接
	//pHandle:由WIRELESS_ApiInit实例化的对象句柄	
	//////////////////////////////////////////////////////////////////////////
	bool WIRELESS_RFID_API  __stdcall WIRELESS_ClearReader(
		void* pHandle);
	
	//////////////////////////////////////////////////////////////////////////
	//发送指令
	//描述：发送指令
	//pHandle:由WIRELESS_ApiInit实例化的对象句柄	
	//pWirelessReaderInfo：进行操作的读写器
	//pCommand:指令，参考命令定义
	//pSendData:发送的数据，数据组织可参考协议手册
	//dataLength:发送的数据长度
	//////////////////////////////////////////////////////////////////////////
	bool WIRELESS_RFID_API  __stdcall WIRELESS_SendMsg(
		void* pHandle,
		WirelessReaderInfo*	pWirelessReaderInfo,
		unsigned char pCommand,
		unsigned char *pSendData, 
		int dataLength);

	////获取回复数据
	bool WIRELESS_RFID_API  __stdcall WIRELESS_GetMsgResult(
		void* pHandle,
		WirelessReaderInfo*	pWirelessReaderInfo,
		CRFrame &pRevFrame);//得到返回结果
	
	
	//系统设置
	bool WIRELESS_RFID_API  __stdcall WIRELESS_SAATSysInfSet(
		void* pHandle,
		WirelessReaderInfo* pWirelessReaderInfo,
		unsigned char nType,
		unsigned char* pParm,
		int nLen);


	//////////////////////////////////////////////////////////////////////////
	//5.2.2 系统信息查询
	//功能描述：该函数用于查询读写器系统信息等参数，可查询类型见下面“信息类型”定义。
	//传入参数：
	//pHandle		打开的端口句柄
	//nType			要查询的信息类型（见说明）
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
	bool WIRELESS_RFID_API  __stdcall WIRELESS_SAAT_SysInfQuery (
		void* pHandle ,
		WirelessReaderInfo* pWirelessReaderInfo,
		unsigned char nType);

	//////////////////////////////////////////////////////////////////////////
	//5.3.1 停止读卡
	//功能描述：此函数用于通知读写器停止当前执行的任何标签操作相关指令。
	//函数原型：
	//bool	SAAT_PowerOff(void *pHandle);
	//传入参数：
	//pHandle		打开的端口句柄	 
	//返回值：true：操作成功；false：操作失败。
	//////////////////////////////////////////////////////////////////////////
	bool WIRELESS_RFID_API  __stdcall WIRELESS_SAAT_PowerOff(void *pHandle,
		WirelessReaderInfo* pWirelessReaderInfo);

	
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
	bool WIRELESS_RFID_API  __stdcall WIRELESS_SAAT_ParmOp (
		void* pHandle ,
		WirelessReaderInfo* pWirelessReaderInfo,
		unsigned char nType,
		unsigned char nStartAddrr, 
		unsigned char nLen,  
		unsigned char *pData, 
		unsigned char *pDataLen,
		int *nMsgID);


	//////////////////////////////////////////////////////////////////////////
	//5.2.5 载波参数配置
	//功能描述：此函数用于配置读写器的射频载波的相关参数。
	//函数原型：
	//bool	WIRELESS_SAAT_YRFParaSet (void* pHandle ,unsigned char nType, int nParaLen)
	//传入参数：
	//pHandle		打开的端口句柄
	//nType			设置的频率表的参数类型（定义见说明）
	//nParaLen		pPara的长度
	//pPara			设置的频率表（定义见说明）
	//返回值：true：操作成功；false：操作失败。
	//说明：“参数类型”为要配置的载波参数类型，定义如下：
	//0x00	跳频表
	//“频率表”为读写器使用的跳频表数值，为1到16的频点号的组合。
	//////////////////////////////////////////////////////////////////////////
	bool WIRELESS_RFID_API  __stdcall WIRELESS_SAAT_YRFParaSet (
		void* pHandle ,
		WirelessReaderInfo* pWirelessReaderInfo,
		unsigned char nType, 
		unsigned char nParaLen);

	//////////////////////////////////////////////////////////////////////////
	//5.2.6载波参数查询
	//功能描述：此函数用于查询读写器的射频载波的参数配置。
	//函数原型：
	//bool	WIRELESS_SAAT_YRFParaQuery (void* pHandle , unsigned char nType)
	//传入参数：
	//pHandle  	打开的端口句柄
	//nType		查询的载波参数参数类型, 定义同上节。
	//pPara		返回的频率表参数
	//pLen 		传入时为pPara的长度，传出时为频率表长度。
	//返回值：true：操作成功；false：操作失败。
	//////////////////////////////////////////////////////////////////////////
	bool WIRELESS_RFID_API  __stdcall WIRELESS_SAAT_YRFParaQuery (
		void* pHandle ,
		WirelessReaderInfo* pWirelessReaderInfo,
		unsigned char nType);


	//////////////////////////////////////////////////////////////////////////
	// 7.4 Flash缓存计数查询
	//功能：缓存计数查询
	//参数：
	//		pHandle :	打开的端口句柄
	//		pPara:		
	//		pLen:		总计数
	//返回值： true为操作成功, false为操作失败
	//////////////////////////////////////////////////////////////////////////
	bool WIRELESS_RFID_API  __stdcall WIRELESS_SAAT_FlashTotalCountQuery (void* pHandle ,
		WirelessReaderInfo* pWirelessReaderInfo);

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
	bool WIRELESS_RFID_API  __stdcall WIRELESS_SAAT_FlashDataQuery (void* pHandle ,
		WirelessReaderInfo* pWirelessReaderInfo,
		unsigned char nOpType);

	//////////////////////////////////////////////////////////////////////////
	// 7.6 Flash缓存数据清除
	//功能：缓存计数查询
	//参数：
	//		pHandle :	打开的端口句柄
	//返回值： true为操作成功, false为操作失败
	//////////////////////////////////////////////////////////////////////////
	bool WIRELESS_RFID_API __stdcall WIRELESS_SAAT_ClearFlash (
		void* pHandle ,
		WirelessReaderInfo* pWirelessReaderInfo);


	//////////////////////////////////////////////////////////////////////////
	//5.2.11 标签操作参数配置
	//功能描述：此函数用于配置读写器做标签的读写等操作时使用的相关参数。
	//传入参数：
	//		pHandle :	打开的端口句柄
	//		nType: 		“类型”为配置的参数类型，包括：
	//				区域	类型 		定义	说明
	//				所有ID	全选		0X00	要求ID值射频范围内全部标签响应查询指令
	//				基本ID	等于		0X01	要求ID值等于匹配数据的标签响应查询指令
	//				基本ID	不等于		0X02	要求ID值不等于匹配数据的标签响应查询指令
	//				基本ID	大于		0X03	要求ID值大于匹配数据的标签响应查询指令
	//				基本ID	小于		0X04	要求ID值小于匹配数据的标签响应查询指令
	//				扩展ID	等于		0X11	要求ID值等于匹配数据的标签响应查询指令
	//				扩展ID	不等于		0X12	要求ID值不等于匹配数据的标签响应查询指令
	//				扩展ID	大于		0X13	要求ID值大于匹配数据的标签响应查询指令
	//				扩展ID	小于		0X14	要求ID值小于匹配数据的标签响应查询指令
	//		pPara: 		"匹配数据"为标签的ID号
	//		nLen:		匹配数据的长度
	//////////////////////////////////////////////////////////////////////////
	bool WIRELESS_RFID_API  __stdcall WIRELESS_SAAT_TagOpParaSet(
		void* pHandle ,
		WirelessReaderInfo* pWirelessReaderInfo,
		unsigned char nType,
		unsigned char *pPara,
		unsigned char nLen);

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
	bool WIRELESS_RFID_API  __stdcall WIRELESS_SAAT_TagOpParaQuery (
		void* pHandle ,
		WirelessReaderInfo* pWirelessReaderInfo,
		unsigned char nType);


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
	bool WIRELESS_RFID_API  __stdcall WIRELESS_SAAT_IOOperate(
		void* pHandle,
		WirelessReaderInfo* pWirelessReaderInfo,
		unsigned char nPort,unsigned char nState);

	
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
	bool WIRELESS_RFID_API  __stdcall WIRELESS_SAAT_Reading_IOConfig (void* pHandle,WirelessReaderInfo* pWirelessReaderInfo,unsigned char nConfigBit);


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
	bool WIRELESS_RFID_API  __stdcall WIRELESS_SAAT_Reading_IOQuery (
		void* pHandle,
		WirelessReaderInfo* pWirelessReaderInfo);



	//////////////////////////////////////////////////////////////////////////
	//5.3.8 读卡指示脉冲宽度配置
	//功能描述：此函数用于配置读卡时IO输出脉冲的宽度
	//函数原型：
	//bool	SAAT_IOPulseWidthSet (void* pHandle,unsigned char nIOPort,unsigned char nWidth)
	//传入参数：
	//pHandle		打开的端口句柄	
	//nIOPort：		配置的IO端口(0-4):端口0是蜂鸣器,端口1到端口4是IO端口
	//nWidth：		脉冲宽度(单位为100ms)
	//返回值：true：操作成功；false：操作失败。
	//////////////////////////////////////////////////////////////////////////
	bool WIRELESS_RFID_API  __stdcall WIRELESS_SAAT_IOPulseWidthSet (void* pHandle,WirelessReaderInfo* pWirelessReaderInfo,unsigned char nIOPort,unsigned char nWidth);


	//////////////////////////////////////////////////////////////////////////
	//5.3.9 读卡指示脉冲宽度查询
	//功能描述：此函数用于查询读卡时IO输出脉冲的宽度
	//函数原型：
	//bool	SAAT_IOPulseWidthQuery (void* pHandle,unsigned char nIOPort,unsigned char* pWidth)
	//传入参数：
	//pHandle		打开的端口句柄	
	//nIOPort：		查询的IO端口(0-4):端口0是蜂鸣器,端口1到端口4是IO端口
	//pWidth：		脉冲宽度(单位为100ms)
	//返回值：true：操作成功；false：操作失败。
	//////////////////////////////////////////////////////////////////////////
	bool WIRELESS_RFID_API  __stdcall WIRELESS_SAAT_IOPulseWidthQuery (
		void* pHandle,
		WirelessReaderInfo* pWirelessReaderInfo,
		unsigned char nIOPort);


	bool WIRELESS_RFID_API  __stdcall WIRELESS_SAAT_GetLastTime(void *pHandle,WirelessReaderInfo* pWirelessReaderInfo,unsigned long& nTime);


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
	bool WIRELESS_RFID_API  __stdcall WIRELESS_SAAT_Reboot (
		void* pHandle,
		WirelessReaderInfo* pWirelessReaderInfo,
		unsigned char nMode);

	//////////////////////////////////////////////////////////////////////////
	// 7.2 读写器时间设置
	//功能：用于设置读写器时间
	//参数：
	//		pHandle :	打开的端口句柄
	//		pPara:		读写器返回的读写器时间数据
	//		pLen:		参数数据长度
	//返回值： true为操作成功, false为操作失败
	//////////////////////////////////////////////////////////////////////////
	bool WIRELESS_RFID_API  __stdcall WIRELESS_SAAT_SetReaderTime (
		void* pHandle ,
		WirelessReaderInfo* pWirelessReaderInfo,
		unsigned char* pPara,unsigned char nLen);

	//////////////////////////////////////////////////////////////////////////
	// 7.3 读写器时间查询
	//功能：用于查询读写器时间
	//参数：
	//		pHandle :	打开的端口句柄
	//		pPara:		读写器返回的读写器时间数据
	//		pLen:		参数数据长度
	//返回值： true为操作成功, false为操作失败
	//////////////////////////////////////////////////////////////////////////
	bool WIRELESS_RFID_API  __stdcall WIRELESS_SAAT_ReaderTimeQuery (
		void* pHandle, 
		WirelessReaderInfo* pWirelessReaderInfo);

	bool WIRELESS_RFID_API  __stdcall WIRELESS_SAAT_YReadIDCode ( 
		void *pHandle,
		WirelessReaderInfo* pWirelessReaderInfo,
		unsigned char nOpType,
		unsigned char nIDType,
		unsigned int nTagCount);

	bool WIRELESS_RFID_API  __stdcall WIRELESS_SAAT_YMakeTagUpLoadIDCode ( 
		void *pHandle,
		WirelessReaderInfo* pWirelessReaderInfo,
		unsigned char nOpType,
		unsigned char nIDType);

	int WIRELESS_RFID_API  __stdcall WIRELESS_SAAT_YRevIDMsgDecRssiExpand(
		void *pHandle,
		WirelessReaderInfo* pWirelessReaderInfo,
		unsigned char* nTime,
		unsigned char* nTagType,
		unsigned int* pId,
		int* nRssi,
		int* nAntenna,
		int* nParam1,
		int* nParam2);

	//////////////////////////////////////////////////////////////////////////
	//5.9 有源射频端口参数配置
	//功能：用于配置有源读写器的参数表的射频端口参数
	//参数：
	//		pHandle:	打开的端口句柄
	//		pPara:		配置读写器的参数表的射频端口参数 
	//		nLen: 		参数长度, 12字节
	//返回值： true为操作成功, false为操作失败
	//////////////////////////////////////////////////////////////////////////
	bool WIRELESS_RFID_API  __stdcall WIRELESS_SAAT_YAntennaParmSet(
		void* pHandle ,
		WirelessReaderInfo* pWirelessReaderInfo,
		unsigned char *pPara,
		unsigned char nLen );

	//////////////////////////////////////////////////////////////////////////
	//6.0 有源射频端口参数查询
	//功能：用于查询有源读写器的参数表的射频端口参数
	//参数：
	//		pHandle:			打开的端口句柄
	//		pPowerRecvPlus:		功放接收增益
	//				0x02:	高增益
	//				0x03:	低增益
	//		p2401FreqSendPwr:	2401射频器件发送功率
	//				0x00:	-18DB
	//				0x01:	-12DB
	//				0x02:	-6DB
	//				0x03:	0DB
	//		pAttenuatorPower:	射频衰减器功率
	//				0x00:	0DB
	//				0x01:	-1DB
	//				0x02:	-2DB
	//				0x03:	-3DB
	//				0x04:	-4DB
	//				0x05:	-5DB
	//				0x06:	-6DB
	//				0x07:	-7DB
	//返回值： true为操作成功, false为操作失败
	//////////////////////////////////////////////////////////////////////////
	bool WIRELESS_RFID_API  __stdcall WIRELESS_SAAT_YAntennaParmQuery(
		void* pHandle,
		WirelessReaderInfo* pWirelessReaderInfo);


	bool WIRELESS_RFID_API __stdcall WIRELESS_SAAT_YAntennaPort_EXSet(
		void* pHandle,
		WirelessReaderInfo* pWirelessReaderInfo,
		unsigned int nPortEnable,
		unsigned int nPollTime,
		unsigned int nParam); 

	bool WIRELESS_RFID_API __stdcall WIRELESS_SAAT_YAntennaPort_EXQuery(
		void* pHandle,
		WirelessReaderInfo* pWirelessReaderInfo); 

};
#endif