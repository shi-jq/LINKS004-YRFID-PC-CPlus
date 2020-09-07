#include "StdAfx.h"
#include "Global.h"

#include "comdef.h"


DWORD Wirte2HardDisk(CHAR * pString, CHAR * pLogFile)
{
	HANDLE	hFile;
	int		nLen, nError;
	BOOL	bRetVal;
	DWORD	dwRetVal, dwLenWrite;
	if(pLogFile == NULL)
	{
		return - 1;
	}

	hFile = CreateFileA(pLogFile, GENERIC_WRITE, FILE_SHARE_WRITE | FILE_SHARE_READ,
		NULL, OPEN_ALWAYS, 0, NULL);
	if(hFile == INVALID_HANDLE_VALUE)
	{
		return -1;
	}
	nLen = (int)strlen(pString);
	dwRetVal = SetFilePointer(hFile, 0, 0, FILE_END);
	if(dwRetVal == 0xFFFFFFFF)
	{
		nError = ::GetLastError();
		if(nError != NO_ERROR)
		{
			CloseHandle(hFile);
			::SetLastError(nError);
			return -1;
		}
	}
	bRetVal = WriteFile(hFile, pString, nLen, &dwLenWrite, NULL);
	if(bRetVal == FALSE)
	{
		nError = ::GetLastError();
		CloseHandle(hFile);
		::SetLastError(nError);
		return -1;
	}
	CloseHandle(hFile);
	return dwLenWrite;
}

/*为了调试打印数据*/
void printData(char *szAlert,unsigned char *pMsg,int nLen)
{
	_bstr_t bstrAlert = szAlert;
	OutputDebugString(bstrAlert);
	char szPara[10];
	_bstr_t strLetter("");
	for( int i = 0 ; i < nLen ; i++)
	{
		sprintf(szPara,"%02x ",*(pMsg+i));
		_bstr_t strPara = szPara;
		OutputDebugString(strPara);
		strLetter +=strPara;
	}
	//OutputDebugString(strLetter);
	//	Wirte2HardDisk((char*)strLetter,"c:\\1.txt");
	//	Wirte2HardDisk("\r\n","C:\\1.txt");
	OutputDebugString(L"\r\n");
}


const unsigned short CRCTable[256] = {
	0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50a5, 0x60c6, 0x70e7,
	0x8108, 0x9129, 0xa14a, 0xb16b, 0xc18c, 0xd1ad, 0xe1ce, 0xf1ef,
	0x1231, 0x0210, 0x3273, 0x2252, 0x52b5, 0x4294, 0x72f7, 0x62d6,
	0x9339, 0x8318, 0xb37b, 0xa35a, 0xd3bd, 0xc39c, 0xf3ff, 0xe3de,
	0x2462, 0x3443, 0x0420, 0x1401, 0x64e6, 0x74c7, 0x44a4, 0x5485,
	0xa56a, 0xb54b, 0x8528, 0x9509, 0xe5ee, 0xf5cf, 0xc5ac, 0xd58d,
	0x3653, 0x2672, 0x1611, 0x0630, 0x76d7, 0x66f6, 0x5695, 0x46b4,
	0xb75b, 0xa77a, 0x9719, 0x8738, 0xf7df, 0xe7fe, 0xd79d, 0xc7bc,
	0x48c4, 0x58e5, 0x6886, 0x78a7, 0x0840, 0x1861, 0x2802, 0x3823,
	0xc9cc, 0xd9ed, 0xe98e, 0xf9af, 0x8948, 0x9969, 0xa90a, 0xb92b,
	0x5af5, 0x4ad4, 0x7ab7, 0x6a96, 0x1a71, 0x0a50, 0x3a33, 0x2a12,
	0xdbfd, 0xcbdc, 0xfbbf, 0xeb9e, 0x9b79, 0x8b58, 0xbb3b, 0xab1a,
	0x6ca6, 0x7c87, 0x4ce4, 0x5cc5, 0x2c22, 0x3c03, 0x0c60, 0x1c41,
	0xedae, 0xfd8f, 0xcdec, 0xddcd, 0xad2a, 0xbd0b, 0x8d68, 0x9d49,
	0x7e97, 0x6eb6, 0x5ed5, 0x4ef4, 0x3e13, 0x2e32, 0x1e51, 0x0e70,
	0xff9f, 0xefbe, 0xdfdd, 0xcffc, 0xbf1b, 0xaf3a, 0x9f59, 0x8f78,
	0x9188, 0x81a9, 0xb1ca, 0xa1eb, 0xd10c, 0xc12d, 0xf14e, 0xe16f,
	0x1080, 0x00a1, 0x30c2, 0x20e3, 0x5004, 0x4025, 0x7046, 0x6067,
	0x83b9, 0x9398, 0xa3fb, 0xb3da, 0xc33d, 0xd31c, 0xe37f, 0xf35e,
	0x02b1, 0x1290, 0x22f3, 0x32d2, 0x4235, 0x5214, 0x6277, 0x7256,
	0xb5ea, 0xa5cb, 0x95a8, 0x8589, 0xf56e, 0xe54f, 0xd52c, 0xc50d,
	0x34e2, 0x24c3, 0x14a0, 0x0481, 0x7466, 0x6447, 0x5424, 0x4405,
	0xa7db, 0xb7fa, 0x8799, 0x97b8, 0xe75f, 0xf77e, 0xc71d, 0xd73c,
	0x26d3, 0x36f2, 0x0691, 0x16b0, 0x6657, 0x7676, 0x4615, 0x5634,
	0xd94c, 0xc96d, 0xf90e, 0xe92f, 0x99c8, 0x89e9, 0xb98a, 0xa9ab,
	0x5844, 0x4865, 0x7806, 0x6827, 0x18c0, 0x08e1, 0x3882, 0x28a3,
	0xcb7d, 0xdb5c, 0xeb3f, 0xfb1e, 0x8bf9, 0x9bd8, 0xabbb, 0xbb9a,
	0x4a75, 0x5a54, 0x6a37, 0x7a16, 0x0af1, 0x1ad0, 0x2ab3, 0x3a92,
	0xfd2e, 0xed0f, 0xdd6c, 0xcd4d, 0xbdaa, 0xad8b, 0x9de8, 0x8dc9,
	0x7c26, 0x6c07, 0x5c64, 0x4c45, 0x3ca2, 0x2c83, 0x1ce0, 0x0cc1,
	0xef1f, 0xff3e, 0xcf5d, 0xdf7c, 0xaf9b, 0xbfba, 0x8fd9, 0x9ff8,
	0x6e17, 0x7e36, 0x4e55, 0x5e74, 0x2e93, 0x3eb2, 0x0ed1, 0x1ef0
};

//////////////////////////////////////////////////////////////////////////
//上位机(PC机)错误集
//////////////////////////////////////////////////////////////////////////
const char* RFIDError[] = {
	"操作成功",							//NO_ERR
	"Socket创建失败",					//ERR_INVALID_SOCKET
	"连接失败",							//ERR_CONNECT_FAIL
	"连接超时",							//ERR_CONNECT_OUTTIME
	"正在连接",							//ERR_CONNECT_CONNECTING
	"关闭连接失败",						//ERR_CLOSE_FAIL
	"选择socket时出错",					//ERR_SOCKET_ERR
	"发送失败",							//ERR_TCPSEND_ERR
	"数据帧丢失",						//ERR_FRAME_LOSE
	"数据帧CRC16校验出错",				//ERR_FRAME_CRC16
	"串口未连接或连接失效",				//ERR_COMHANDLE_INVALID
	"发送数据到串口失败",				//ERR_COMSEND_FAIL
	"收取串口数据失败",					//ERR_COMRECV_FAIL
	"串口：收取帧头错误",				//ERR_COMRECVHEAD_FAIL
	"打开串口失败",						//ERR_COMOPEN_FAIL
	"初始化套接字失败",					//ERR_INITSOCKET_FAIL
	"Set up com state出错",				//ERR_SETCOM_STATE,
	"Set up com 出错",					//ERR_SETUP_COM,
	"串口 overlapread 事件句柄为空",	//ERR_OVERLAPREAD_NULL,
	"串口 overlapwrite 事件句柄为空",	//ERR_OVERLLAPWRITE_NULL
	"TCP接收数据时socket出错",          //ERR_TCPRECV_SOCKETERROR
	"TCP接收数据超时",                  //ERR_TCPSEND_SOCKETOVERTIME,	
	"TCP发送数据时socket出错",			//ERR_TCPSEND_SOCKETERROR,
	"TCP发送数据超时",					//ERR_TCPSEND_SOCKETOVERTIME,
	"内存分配不足",						//ERR_MOREDATA_NEED
	"入参错误:空指针,未分配内存",		//ERR_POINTER_NULL	
	"入参错误:传入长度为0",					//ERR_SIZE_ZERO
	"调用超时,其他线程正在对读写器进行操作", //ERR_OVER_NOSIGNED
	"起始地址长度大于255",     //ERR_START_OVERFLOW
	"长度大于255",       //ERR_LEN_OVERFLOW
	"写6B标签数据时,数据区首地址加数据区长度大于224字节", //ERR_SIXBWRITE_OVERFLOW
	"读6B标签数据时,数据区首地址加数据区长度超出224字节", //ERR_SIXBREAD_OVERFLOW	
	"锁6B标签数据时,数据区首地址加数据区长度超出224字节", //ERR_SIXBDATA_OVERFLOW
	"GetCommState出错", //ERR_GETCOM_STATE,//GetCommState出错
	"GetCommTimeouts出错", //ERR_GETCOM_TIMEOUT,//GetCommTimeouts出错
	"SetCommTimeouts出错", //ERR_SETCOM_TIMEOUT,//SetCommTimeouts出错
	"启动收信件线程失败",//ERR_STARTREVTHREAD_FAIL,//启动收信件线程失败
	"超时未收到数据",//ERR_RECVTHREAD_OVERTIME //超时未收到数据
	"收到的信件数据区长度小于0,异常",
	"写EPC码长度不足12字节", //ERR_WRITE_EPCLEN
	"USB发送数据失败",//ERR_USB_SEND
};

//////////////////////////////////////////////////////////////////////////
//RFID指令集
//////////////////////////////////////////////////////////////////////////




const unsigned char RFIDCommand[256] = {
	0x00,            //系统信息配置
	0x01,            //系统信息配置
	0x02,			//工作模式配置
	0x03,			//工作模式查询
	0x0A,           //系统测试控制
	0x10,			//参数表操作
	0x11,           //射频端口参数配置
	0x12,			//射频端口参数查询
	0x13,			//COM_CARRYWAVE_SET,		//载波参数配置
	0x14,			//COM_CARRYWAVE_QUERY,		//载波参数查询
	0x15,			//COM_COMMUNI_SET,			//通信参数配置
	0x16,			//COM_COMMUNI_QUERY,		//通信参数查询
	0x17,			//COM_NETPARA_SET,			//网络参数配置				
	0x18,			//COM_NETPARA_QUERY,		//网络参数查询
	0X19,										//标签操作参数配置
	0x1A,										//标签操作参数查询
	0x1B,										//扩展板参数配置
	0x1C,			//扩展板参数查询
	0x20,           //载波操作指令
	0x21,           //输出操作指令
	0x22,			//输入查询指令
	0x23,			//READING_IO_CONFIG		读卡指示配置指令
	0x24,			//READING_IO_QUERY		读卡指示查询指令
	0x25,			//COM_IO_PULSESET			读卡指示脉冲配置
	0x26,			//COM_IO_PULSEQUERY			读卡指示脉冲查询
	0x2A,			//重启指令
	0x50,			//COM_OPEN_CONN //打开连接
	0x51,           //COM_CLOSE_CONN //关闭连接
	0x53,   //COM_STOP_READ        //停止读卡
	0x58,           //COM_SEND_HEART        //心跳包
	0x60,//COM_SELECTTAG_SET
	0x61,//COM_YSEND_READID
	0x62,//COM_YMAKE_TAGUPLOAD
	0x63,//COM_YCHK_EID
	0x64,//COM_YREAD_USRDATA
	0x65,//COM_YWRITE_USRDATA
	0x68,//COM_YSET_ACCESSPWD
	0x69,//COM_YSET_CFGPWD
	0x6A,//COM_YDATA_LOG
	0x6B,//COM_YEAS_SET
	0x6C,//COM_YQUERY_EASFLAG
	0x6D,//COM_YEAS_MON
	0x6F,//COM_YSTOP
	0x71,//COM_YTAGCFG_SET
	0x72,//COM_YTAGCFG_QUERY
	0x73,//COM_YTAGWORKMODE_SET
	0x74,//COM_YTAGWORKMODE_QUERY
	0x75,//COM_YTAGFATSET
	0x76,//COM_YTAGFATQUERY
	0x77,//COM_YTAGINITTOFAT
	0x78,//COM_YTAGSENSORQUERY
	0x79,//COM_YTAGIOQUERY
	0x7A,//COM_YTAGIOOUT
	0x80,			//COM_6BSELECT_TAG,			//6B标签选择命令
	0x81,			//COM_6BREAD_UID,			//6B读取UID码命令
	0x82,			//COM_6BREADUSER_DATA,		//6B读标签数据
	0x83,			//COM_6BWRITEUSER_DATA,		//6B写标签数据
	0x84,			//COM_6BLOCK_TAGDATA,		//6B锁标签数据
	0x85,           //COM_6BLOCK_QUERY //
	0x90,			//COM_6CSELECT_EPCTAG,		//6C标签选择
	0x91,			//COM_6CREAD_EPC,			//6C读EPC码
	0x92,			//COM_6CREAD_TID,			//6C读TID码
	0x9F,			//COM_6CREAD_EPCTID,		//6C读取EPCTID码
	0x93,			//COM_6CWRITE_EPCDATA,		//6C写EPC数据
	0x94,			//COM_6CREADUSER_DATA,		//6C读用户数据区
	0x95,			//COM_6CWRITEUSER_DATA,		//6C写用户数据区
	0x96,			//COM_6CBLOCKWRITE_DATA,	//块写Bank数据
	0x97,			//COM_6CBLOCKCLEAR_DATA,	//块擦Bank数据
	0x98,			//COM_6CACCESSPWD_CFG,		//配置访问密码
	0x99,			//COM_6CDESTORYPWD_CFG,		//设置销毁密码指令
	0x9A,			//COM_6CLOCK_TAGCFG,		//标签锁状态配置
	0x9B,			//COM_DESTORY_TAG,			//标签灭活指令
	0x9C,			//COM_EASFLAG_CFG,			//EAS标志配置指令
	0x9D,			//COM_EAS_ENABLE			//EAS监控功能设置指令
	0xB0,			//READER_TIME_SET,				//读写器时间设置
	0xB1,			//READER_TIME_QUERY,			//读写器时间查询
	0xB2,			//READER_FLASHDATA_QUERY,		//FLASH数据查询
	0xB3,			//READER_FLASHDATACOUNT_QUERY //FLASH数据标签数查询
	0xB4,			//READER_FLASHCLEAR         //FLASH数据
	0xC0,			//COM_GPRS_SET,				//GPRS设置
	0xC1,			//COM_GPRS_QUERY,			//GPRS查询
	0xC2,			//COM_WIFI_SET,				//WIFI设置
	0xC3,			//COM_WIFI_QUERY,			//WIFI查询
	0xC4,			//COM_WIFI_TRANS_REST		//WIFI进入透传或者复位
}; 

const char* mCopyright = "2.0";





