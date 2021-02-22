//////////////////////////////////////////////////////////////////////////

#pragma once


//************  编译设置，C# 与 C++等待时间不同
#define  CPLUSPLUS //开启这个编译for  C++
//#define  CSHARP  //开启这个编译for c#


#ifdef CPLUSPLUS //C++
#define TAG_REV_TIME 20
#define TAG_6BREAD_TIME 5000
#define TAG_6BWRITE_TIME 3000
#define TAG_6BLOCK_QUERY 4000
#define TAG_6CREAD_TIME 4000
#define TAG_6CWRITE_TIME 4000
#define TAG_6CSELECT_TIME 200
#else //C#
#define TAG_REV_TIME 100
#define TAG_6BREAD_TIME 500
#define TAG_6BWRITE_TIME 1000
#define TAG_6BLOCK_QUERY 1000
#define TAG_6CREAD_TIME 500
#define TAG_6CWRITE_TIME 1000

#endif


#define READER_PROUCTNAME_LEN 30

//**************


#define SAAT_610_PORT			7086			//定义端口
#define DATA_BUFFER			1024			//数据域最大宽度
#define CMD_DATA_BUFFER			1024				//数据域最大宽度
#define DATA_6CONCEREAD_LEN 14				//6C一次读取的长度
#define DATA_6CONCEWRITE_LEN 14				//6C一次写入的长度
#define SENDFRAME_MAXBUF	1024			//发送帧定义最大空间
#define REC_FRAME_MAXBUFF	8192			//接收帧的缓冲	
#define REC_FRAME_ONCE      256
#define COM_FRAME_ONCE		17
#define TCP_FRAME_ONCE		17
#define UDP_FRAME_ONCE		255
#define	FRAME_HEAD			0xAA			//帧头
#define FRAME_HEAD_REPLACE	0xAB			//帧头替换 0x55 <-> 0x56
#define FRAME_FRAME_REPLACE	0xAC			//帧替换   0x56 <-> 0x57
#define	FRAME_PRIORITY		0x20			//优先位 0010 0000
#define	FRAME_ANSWER		0x10			//应答帧 0001 0000
#define RECVFRAME_MAXBUF    256				//接收帧定义最大空间

//******************
#define SEND_WAIT 1000
#define RECV_WAIT 0
#define THREAD_RECV_WAIT 2000
#define SEND_BUFFER_SIZE 1024
#define API_RECV_BUFFER 1024
#define COMMAND_LEN 1
#define ANSWER_LEN 1
#define ANTENNA_LEN 1
#define API_SENDDATA_BUFF 1024
#define BYTE_BUFFER_SIZE 255
#define FRAME_WITHOUTBLENGTH 6
#define SIXB_DATALEN 224
#define READ_USERDATA_LEN 64
#define WRITE_USERDATA_LEN 32


//#define COM_STOP_READ 0x53 //单次已读完指令

//******************


#define COM_ONCE_WAIT 200 
#define CARD_MAX_BUFFER 2000


extern const char* mCopyright;

typedef unsigned char byte;




/**/
extern void printData(char *szAlert,unsigned char *pMsg,int nLen);



#include <string>
using namespace std;


enum ReadState
{
	READ_EPC,
	READ_TID,
	//added by haowenfeng in 2013-01-05
	READ_EPCTID,
	READ_UID,
	READ_EAS,
	READ_IDLE
};
enum PortType
{
	TCP_PORT,
	COM_PORT,
	USB_PORT,
	UDP_PORT,
};

struct  CRFIDSystemCfg
{
	PortType nPortType;				//通讯模式，目前包括TCP/USB/COM
	string strHostName;				//本机的IP地址，仅在网络通讯模式下有效
	int nSocketPort;			    //网络SOCKET端口
	string strComNum;				//COM1－COM4 仅在COM通讯模式下有效
	int    nBaud;					//串口(USB口)通讯速率
	unsigned char nBusAddr;         //总线地址
	string strUSBNum;               //USB1-USB8  仅在USB通讯模式下有效
	unsigned char ucScanTimes;		//每次发送读卡指令后，读出器查询标签的次数
	unsigned char ucRetryTimes;		//没有扫描到标签，重新发送指令的次数。
	unsigned char ucRereadTimes;	//读标签重发指令次数
	unsigned char ucRewriteTimes;	//写标签重发指令次数
	unsigned char ucLeadInTotal;	//连接天线总数（1－4）
	unsigned char ucLeadInCtrl;		//天线控制方式（0：自动扫描所有天线端口,1~4仅对指定端口进行扫描）
	unsigned char ucSaveLog;		//是否保存调试记录日志（0：不存日志，1：保存日志）
	string ucLogFName;		//调试记录日志文件名
	string strLanguageType;
	CRFIDSystemCfg()
	{
		LCID lcid = GetSystemDefaultLCID();//特殊处理,其他语言用动态库名字命名
		strLanguageType = "en";
		switch( lcid )
		{
		case 0x804:
			strLanguageType ="cn";
			break;
		case 0x409:
			strLanguageType="en";
			break;
		case 0x404:
			strLanguageType="tw";
			break;
		}

	}
};


struct CRFrame 
{
	unsigned char bFrame;			//帧头 AAH
	unsigned char bAddrInfo;		//帧信息
	unsigned char bAddr;			//总线地址
	unsigned char bLength;			//数据长度  包括指令和数据的长度
	unsigned char bCommand;			//指令
	unsigned char bData[CMD_DATA_BUFFER];//数据域  +  CRC16校验
};

struct CRFIDFrame 
{
	 CRFrame RFIDInFrame;//发送的命令
	 CRFrame RFIDOutFrame;//接收的回应
	 HANDLE m_revHandle;//接收信号

	 CRFIDFrame()
	 {
		 memset(&RFIDInFrame,0,sizeof(CRFrame));
		 memset(&RFIDOutFrame,0,sizeof(CRFrame));
		 m_revHandle = NULL;
		 m_revHandle = CreateEvent(NULL,FALSE,FALSE,NULL);
	 }
	 

	 ~CRFIDFrame()
	 {
		 if( m_revHandle != NULL)
		 {
			CloseHandle( m_revHandle );
			m_revHandle = NULL;
			
		
		 }
	
	 }

	 void SetSigle()
	 {
		SetEvent( m_revHandle ); 
	 }

	 void CloseSigle()
	 {
		CloseHandle(m_revHandle);
		m_revHandle = NULL;
	 }
};

//////////////////////////////////////////////////////////////////////////
//RFID指令集
//////////////////////////////////////////////////////////////////////////
enum RFIDCommandCode {
	COM_SYS_CFG,			//系统信息配置
	COM_SYS_QUERY,			//系统信息查询
	COM_WORKMOD_CFG,		//工作模式配置
	COM_WORKMOD_QUERY,		//工作模式查询
	COM_TEST_CONTROL,		//系统测试控制
	COM_PARA_OP,			//参数表操作
	COM_ANTENNA_SET,		//射频端口参数配置
	COM_ANTENNA_QUERY,		//射频端口参数查询
	COM_CARRYWAVE_SET,		//载波参数配置
	COM_CARRYWAVE_QUERY,	//载波参数查询
	COM_COMMUNI_SET,		//通信参数配置
	COM_COMMUNI_QUERY,		//通信参数查询
	COM_NETPARA_SET,		//网络参数配置
	COM_NETPARA_QUERY,		//网络参数查询
	COM_TAG_SET,			//标签操作参数配置
	COM_TAG_QUERY,			//标签操作参数查询
	COM_EXTENDBOARD_SET,	//扩展板参数配置
	COM_EXTENDBOARD_QUERY,	//扩展板参数查询
	COM_ANTENNA_SET_EX,		//射频端口参数配置-扩展的
	COM_ANTENNA_QUERY_EX,	//射频端口参数查询-扩展的
	COM_CARRY_OP,           //载波操作指令
	COM_IO_OP,				//输出操作指令
	COM_INPUT_QUERY,		//输入查询指令
	READING_IO_CONFIG,		//读卡指示配置指令
	READING_IO_QUERY,		//读卡指示查询指令
	COM_IO_PULSESET,		//0x25读卡指示脉冲配置
	COM_IO_PULSEQUERY,		//0x26	读卡指示脉冲查询
	COM_READER_REBOOT,		//重启指令
	COM_OPEN_CONN,			//打开连接
	COM_CLOSE_CONN,			//关闭连接
	COM_STOP_READ,          //0x53停止读卡
	COM_SEND_HEART,         //心跳包 0x58,  
	COM_SELECTTAG_SET,
	COM_YSEND_READID,
	COM_YMAKE_TAGUPLOAD,
	COM_YCHK_EID,
	COM_YREAD_USRDATA,
	COM_YWRITE_USRDATA,
	COM_YSET_ACCESSPWD,
	COM_YSET_CFGPWD,
	COM_YDATA_LOG,
	COM_YEAS_SET,
	COM_YQUERY_EASFLAG,
	COM_YEAS_MON,
	COM_YSTOP,
	COM_YTAGCFG_SET,
	COM_YTAGCFG_QUERY,
	COM_YTAGWORKMODE_SET,
	COM_YTAGWORKMODE_QUERY,
	COM_YTAGFATSET,
	COM_YTAGFATQUERY,
	COM_YTAGINITTOFAT,
	COM_YTAGSENSORQUERY,
	COM_YTAGIOQUERY,
	COM_YTAGIOOUT,
	COM_6BSELECT_TAG,		//6B标签选择命令
	COM_6BREAD_UID,			//6B读取UID码命令
	COM_6BREADUSER_DATA,	//6B读标签数据
	COM_6BWRITEUSER_DATA,	//6B写标签数据
	COM_6BLOCK_TAGDATA,		//6B锁标签数据
	COM_6BLOCK_QUERY,		//6B锁标签查询,
	COM_6CSELECT_EPCTAG,	//6C标签选择
	COM_6CREAD_EPC,			//6C读EPC码
	COM_6CREAD_TID,			//6C读TID码
	COM_6CREAD_EPCTID,		//6C读EPC+TID码
	COM_6CWRITE_EPCDATA,	//6C写EPC数据
	COM_6CREADUSER_DATA,	//6C读用户数据区
	COM_6CWRITEUSER_DATA,	//6C写用户数据区
	COM_6CBLOCKWRITE_DATA,	//块写Bank数据
	COM_6CBLOCKCLEAR_DATA,	//块擦Bank数据
	COM_6CACCESSPWD_CFG,	//配置访问密码
	COM_6CDESTORYPWD_CFG,	//设置销毁密码指令
	COM_6CLOCK_TAGCFG,		//标签锁状态配置
	COM_DESTORY_TAG,		//标签灭活指令
	COM_EASFLAG_CFG,		//EAS标志配置指令
	COM_EAS_ENABLE,		//EAS监控功能设置指令
	READER_TIME_SET,		//读写器时间设置
	READER_TIME_QUERY,		//读写器时间查询
	READER_FLASHDATA_QUERY,	//FLASH数据查询
	READER_FLASHDATACOUNT_QUERY, //FLASH数据标签数查询
	READER_FLASHCLEAR,		//清FLASH数据

	COM_GPRS_SET,		//GPRS设置
	COM_GPRS_QUERY,		//GPRS查询
	COM_WIFI_SET,		//WIFI设置
	COM_WIFI_QUERY,		//WIFI查询
	COM_WIFI_TRANS_REST, //WIFI进入透传或者复位

	COM_YRF_SET,
	COM_YRF_QUERY,
};



extern const unsigned char RFIDCommand[256];

//////////////////////////////////////////////////////////////////////////
//上位机(PC机)错误集
//////////////////////////////////////////////////////////////////////////


extern const char* RFIDError[] ;
enum RFIDErrorCode {
	NO_ERR =0x500,					//"操作成功"
	ERR_NOT_CONNECT,//端口未打开
	ERR_READING_NOTEXE,		//读卡状态中不可执行的指令
	ERR_COMMAND_EXEING,			//指令在执行当中
	ERR_INVALID_SOCKET,		//"Socket创建失败"
	ERR_CONNECT_FAIL,		//"连接失败"
	ERR_CONNECT_OUTTIME,	//"连接超时"
	ERR_CONNECT_CONNECTING,	//"正在连接"
	ERR_CLOSE_FAIL,			//"关闭连接失败"
	ERR_SOCKET_ERR,			//"选择socket时出错"
	ERR_TCPSEND_ERR,		//"发送失败"
	ERR_FRAME_LOSE,			//"数据帧丢失"
	ERR_FRAME_CRC16,		//"数据帧CRC16校验出错"
	ERR_COMHANDLE_INVALID,	//"串口未连接或连接失效"
	ERR_COMSEND_FAIL,		//"发送数据到串口失败"
	ERR_COMRECV_FAIL,		//"收取串口数据失败"
	ERR_COMRECVHEAD_FAIL,	//"串口：收取帧头错误"
	ERR_COMOPEN_FAIL,		//"打开串口失败"
	ERR_INITSOCKET_FAIL,	//"初始化套接字失败"
	ERR_TCP_NOTOPEN,		//SOCKET端口未打开
	ERR_COM_NOTOPEN,		//串口未打开
	ERR_USB_NOTOPEN,		//USB口未打开
	ERR_SETCOM_STATE,		//"Set up com state出错"
	ERR_SETUP_COM,			//"Set up com 出错"
	ERR_OVERLAPREAD_NULL,	//"串口 overlapread 事件句柄为空"
	ERR_OVERLLAPWRITE_NULL,	//"串口 overlapwrite 事件句柄为空"
	ERR_TCPRECV_SOCKETERROR,//"TCP接收数据时socket出错"
	ERR_TCPRECV_SOCKETOVERTIME,//"TCP接收数据超时" 
	ERR_TCPSEND_SOCKETERROR,//"TCP发送数据时socket出错"
	ERR_TCPSEND_SOCKETOVERTIME,//"TCP发送数据超时"
	ERR_UDPRECV_SOCKETERROR,//"UDP接收数据时socket出错"
	ERR_UDPRECV_SOCKETOVERTIME,//"UDP接收数据超时" 
	ERR_MOREDATA_NEED,		//"内存分配不足"
	ERR_POINTER_NULL,		//"入参错误:空指针,未分配内存"
	ERR_SIZE_ZERO,			//"入参错误:长度为0"
	ERR_OVER_NOSIGNED,		//"调用超时,其他线程正在对读写器进行操作"
	ERR_START_OVERFLOW,     //起始地址长度大于255
	ERR_LEN_OVERFLOW,       //长度大于255
	ERR_SIXBWRITE_OVERFLOW,    //写6B标签数据时,数据区首地址加数据区长度大于224字节
	ERR_SIXBREAD_OVERFLOW,		//读6B标签数据时,数据区首地址加数据区长度超出224字节
	ERR_SIXBLOGDATA_OVERFLOW,      //锁6B标签数据时,数据区首地址加数据区长度超出224字节
	ERR_GETCOM_STATE,//GetCommState出错
	ERR_GETCOM_TIMEOUT,//GetCommTimeouts出错
	ERR_SETCOM_TIMEOUT,//SetCommTimeouts出错
	ERR_STARTREVTHREAD_FAIL,//启动收信线程出错
	ERR_RECVTHREAD_OVERTIME, //超时未收到数据
	ERR_DATALEN_LOZERO,
	ERR_WRITE_EPCLEN, //写EPC码长度不足12字节
	ERR_USB_SEND,//USB发送数据失败
};




extern const unsigned short CRCTable[256];


typedef bool(WINAPI *RECVBACKPROCFUN)(unsigned char* btMsg,int nLen);

typedef unsigned (WINAPI *PBEGINTHREADEX_THREADFUNC)(
	LPVOID lpThreadParameter
	);
typedef unsigned *PBEGINTHREADEX_THREADID;

typedef bool(WINAPI *RECVRFAMERECVPROCFUN)(CRFrame& Frame);
