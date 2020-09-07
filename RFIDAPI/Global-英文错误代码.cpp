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
	//OutputDebugString(bstrAlert);
	char szPara[10];
	_bstr_t strLetter("");
	for( int i = 0 ; i < nLen ; i++)
	{
		sprintf(szPara,"%02x ",*(pMsg+i));
		_bstr_t strPara = szPara;
		//OutputDebugString(strPara);
	    strLetter +=strPara;
	}
	//OutputDebugString(strLetter);
//	Wirte2HardDisk((char*)strLetter,"c:\\1.txt");
//	Wirte2HardDisk("\r\n","C:\\1.txt");
	//OutputDebugString(L"\n");
}


const unsigned short CRCTable[256] = {
	0x0000, 0x8005, 0x800f, 0x000a, 0x801b, 0x001e, 0x0014, 0x8011, 
	0x8033, 0x0036, 0x003c, 0x8039, 0x0028, 0x802d, 0x8027, 0x0022, 
	0x8063, 0x0066, 0x006c, 0x8069, 0x0078, 0x807d, 0x8077, 0x0072, 
	0x0050, 0x8055, 0x805f, 0x005a, 0x804b, 0x004e, 0x0044, 0x8041, 
	0x80c3, 0x00c6, 0x00cc, 0x80c9, 0x00d8, 0x80dd, 0x80d7, 0x00d2, 
	0x00f0, 0x80f5, 0x80ff, 0x00fa, 0x80eb, 0x00ee, 0x00e4, 0x80e1, 
	0x00a0, 0x80a5, 0x80af, 0x00aa, 0x80bb, 0x00be, 0x00b4, 0x80b1, 
	0x8093, 0x0096, 0x009c, 0x8099, 0x0088, 0x808d, 0x8087, 0x0082, 
	0x8183, 0x0186, 0x018c, 0x8189, 0x0198, 0x819d, 0x8197, 0x0192, 
	0x01b0, 0x81b5, 0x81bf, 0x01ba, 0x81ab, 0x01ae, 0x01a4, 0x81a1, 
	0x01e0, 0x81e5, 0x81ef, 0x01ea, 0x81fb, 0x01fe, 0x01f4, 0x81f1, 
	0x81d3, 0x01d6, 0x01dc, 0x81d9, 0x01c8, 0x81cd, 0x81c7, 0x01c2, 
	0x0140, 0x8145, 0x814f, 0x014a, 0x815b, 0x015e, 0x0154, 0x8151, 
	0x8173, 0x0176, 0x017c, 0x8179, 0x0168, 0x816d, 0x8167, 0x0162, 
	0x8123, 0x0126, 0x012c, 0x8129, 0x0138, 0x813d, 0x8137, 0x0132, 
	0x0110, 0x8115, 0x811f, 0x011a, 0x810b, 0x010e, 0x0104, 0x8101, 
	0x8303, 0x0306, 0x030c, 0x8309, 0x0318, 0x831d, 0x8317, 0x0312, 
	0x0330, 0x8335, 0x833f, 0x033a, 0x832b, 0x032e, 0x0324, 0x8321, 
	0x0360, 0x8365, 0x836f, 0x036a, 0x837b, 0x037e, 0x0374, 0x8371, 
	0x8353, 0x0356, 0x035c, 0x8359, 0x0348, 0x834d, 0x8347, 0x0342, 
	0x03c0, 0x83c5, 0x83cf, 0x03ca, 0x83db, 0x03de, 0x03d4, 0x83d1, 
	0x83f3, 0x03f6, 0x03fc, 0x83f9, 0x03e8, 0x83ed, 0x83e7, 0x03e2, 
	0x83a3, 0x03a6, 0x03ac, 0x83a9, 0x03b8, 0x83bd, 0x83b7, 0x03b2, 
	0x0390, 0x8395, 0x839f, 0x039a, 0x838b, 0x038e, 0x0384, 0x8381, 
	0x0280, 0x8285, 0x828f, 0x028a, 0x829b, 0x029e, 0x0294, 0x8291, 
	0x82b3, 0x02b6, 0x02bc, 0x82b9, 0x02a8, 0x82ad, 0x82a7, 0x02a2, 
	0x82e3, 0x02e6, 0x02ec, 0x82e9, 0x02f8, 0x82fd, 0x82f7, 0x02f2, 
	0x02d0, 0x82d5, 0x82df, 0x02da, 0x82cb, 0x02ce, 0x02c4, 0x82c1, 
	0x8243, 0x0246, 0x024c, 0x8249, 0x0258, 0x825d, 0x8257, 0x0252, 
	0x0270, 0x8275, 0x827f, 0x027a, 0x826b, 0x026e, 0x0264, 0x8261, 
	0x0220, 0x8225, 0x822f, 0x022a, 0x823b, 0x023e, 0x0234, 0x8231, 
	0x8213, 0x0216, 0x021c, 0x8219, 0x0208, 0x820d, 0x8207, 0x0202 
};

//////////////////////////////////////////////////////////////////////////
//上位机(PC机)错误集
//////////////////////////////////////////////////////////////////////////
const char* RFIDError[] = {
	"Operate successful",							//NO_ERR
	"Failed to create socket",					//ERR_INVALID_SOCKET
	"Failed connect",							//ERR_CONNECT_FAIL
	"Timeout connect",							//ERR_CONNECT_OUTTIME
	"Connecting...",							//ERR_CONNECT_CONNECTING
	"Failed to close the connect",						//ERR_CLOSE_FAIL
	"Error in select socket",					//ERR_SOCKET_ERR
	"Failed to send",							//ERR_TCPSEND_ERR
	"Lost the data frame",						//ERR_FRAME_LOSE
	"Wrong with the CRC16 to data frame",				//ERR_FRAME_CRC16
	"Not connect the COM or connect COM failed",				//ERR_COMHANDLE_INVALID
	"Failed to send the COM data",				//ERR_COMSEND_FAIL
	"Failed to receive the COM data",					//ERR_COMRECV_FAIL
	"COM: wrong with the received frame head",				//ERR_COMRECVHEAD_FAIL
	"Open COM failed",						//ERR_COMOPEN_FAIL
	"Init socket failed",					//ERR_INITSOCKET_FAIL
	"Set up com state error",				//ERR_SETCOM_STATE,
	"Set up com error",					//ERR_SETUP_COM,
	"Null handler with the COM overlapread event",	//ERR_OVERLAPREAD_NULL,
	"Null handler with the COM overlapwrite event",	//ERR_OVERLLAPWRITE_NULL
	"Error in socket receive data via TCP",          //ERR_TCPRECV_SOCKETERROR
	"Timeout with receive data via TCP",                  //ERR_TCPSEND_SOCKETOVERTIME,	
	"Error in socket send data via TCP",			//ERR_TCPSEND_SOCKETERROR,
	"Timeout with send data via TCP",					//ERR_TCPSEND_SOCKETOVERTIME,
	"Occuppyed Memory space is not enough ",						//ERR_MOREDATA_NEED
	"Null pointer, there is no memory space occuppyed with  input parameter",		//ERR_POINTER_NULL	
	"Wrong with Input parameter length 0",					//ERR_SIZE_ZERO
	"Timeout in call, the read device is occupyed", //ERR_OVER_NOSIGNED
	"The start address is not less than 255",     //ERR_START_OVERFLOW
	"The length is more than 255",       //ERR_LEN_OVERFLOW
	"First of data field plus length of data field is more than 224 bits when write 6B label", //ERR_SIXBWRITE_OVERFLOW
	"First of data field plus length of data field is more than 224 bits when read 6B label", //ERR_SIXBREAD_OVERFLOW	
	"First of data field plus length of data field is more than 224 bits when lock 6B label", //ERR_SIXBDATA_OVERFLOW
	"GetCommState error", //ERR_GETCOM_STATE,//GetCommState出错
	"GetCommTimeouts error", //ERR_GETCOM_TIMEOUT,//GetCommTimeouts出错
	"SetCommTimeouts error", //ERR_SETCOM_TIMEOUT,//SetCommTimeouts出错
	"Failed to start up the receive mail thread ",//ERR_STARTREVTHREAD_FAIL,//启动收信件线程失败
	"Timeout to receive the data",//ERR_RECVTHREAD_OVERTIME //超时未收到数据
	"abnormal occur, the data field length is less than 0",
	"The length of write EPC code is less than 12bits", //ERR_WRITE_EPCLEN
	"Failed to send message via USB",//ERR_USB_SEND
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
	0x50,			//COM_OPEN_CONN //打开连接
	0x51,           //COM_CLOSE_CONN //关闭连接
	0x53,   //COM_STOP_READ        //停止读卡
	0x58,           //COM_SEND_HEART        //心跳包
	0x80,			//COM_6BSELECT_TAG,			//6B标签选择命令
	0x81,			//COM_6BREAD_UID,			//6B读取UID码命令
	0x82,			//COM_6BREADUSER_DATA,		//6B读标签数据
	0x83,			//COM_6BWRITEUSER_DATA,		//6B写标签数据
	0x84,			//COM_6BLOCK_TAGDATA,		//6B锁标签数据
	0x85,           //COM_6BLOCK_QUERY //
	0x90,			//COM_6CSELECT_EPCTAG,		//6C标签选择
	0x91,			//COM_6CREAD_EPC,			//6C读EPC码
	0x92,			//COM_6CREAD_TID,			//6C读TID码
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
	0x9D			//COM_EAS_ENABLE			//EAS监控功能设置指令
}; 


const char* RFIDSystemErrorMsg[ERR_COMMSYS_UNKNOW - ERR_COMMSYS_START+1] = {
	"Wrong with the software version of FPGA/DSP",	//ERR_COMMSYS_SOFTCOPYRIGHT = 0x01
	"Wrong with the hardware version of baseband",			//ERR_COMMSYS_BASECOPYRIGHT
	"Wrong with the hardware version of redio frequency board",			//ERR_COMMSYS_RADIOCOPYRIGHT
	"Failed to selftest in system parameter table of read device",					//ERR_COMMSYS_SYSTEMPARA
	"Failed to selftest in baseband of read device",					//ERR_COMMSYS_FPGACHECK
	"Failed to Selftest in Redio frequency board of device",					//ERR_COMMSYS_RADIOCHECK
	"Ethernet of the read device check failed",					//ERR_COMMSYS_NETCHECK
	"The realtime clock of read device check failed",				//ERR_COMMSYS_TIMECHECK
	"The external memory of read device check failed",				//ERR_COMMSYS_SAVECHECK
	"",
	"",
	"",
	"",
	"",
	"",
	"Unknow error or the error belongs to system and cann`t be identified by the read device"
	//////////////////////保留//////////////////////////////////////////////////
};
//RFIDSystemErrorMsg[ERR_COMMSYS_UNKNOW] = "属于该范围但读写器无法判断或未知类型错误";	//ERR_COMMSYS_UNKNOW = 0x0F


const char* RFIDOperErrorMsg[ERR_COMOPER_UNKNOW - ERR_COMMOPER_PWDERR + 1] = {
	"Operation PWD is wrong",					//ERR_COMMOPER_PWDERR = 0x11 
	"Used the wrong antenna port",					//ERR_COMMOPER_ANTENNA
	"Device is in the test mode now",				//ERR_COMMOPER_TESTING
	"Write/read the memory failed",					//ERR_COMMOPER_FLASH
	"The device is being operate the label",				//ERR_COMMOPER_DOINGTAG
	"The device work wrong(maybe do wrong operation)",//ERR_COMMOPER_OPERATE
	"Authority been occupyed(someone is using the device)",//ERR_COMMOPER_OUTACCESS
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"Unkonw error or the error in the operation cann`t be identified by the read device"
	
	//////////////////////保留//////////////////////////////////////////////////
};
//RFIDOperErrorMsg[ERR_COMOPER_UNKNOW - ERR_COMMOPER_PWDERR] = "属于该范围但读写器无法判断或未知类型错误";//ERR_COMOPER_UNKNOW = 0x1F	

//注意: 同上

const char* RFIDDioErrorMsg[ERR_IO_UNKNOW - ERR_IO_UNFULL + 1] = {
	"Not complete with the receive statement or data",					//ERR_IO_UNFULL = 0x20
	"Wrong with the receive statement or CRC checksum",			//ERR_IO_CRC
	"Not support the statement for current type device",			//ERR_IO_TYPENONSUPPORT
	"Not support the protocol for current type device",		//ERR_IO_TAGNONSUPPORT
	"Wrong with the parameter in statement",						//ERR_IO_PARA
	"Wrong with the frame in Statement",				//ERR_IO_FRAME
	"Not support the statement",						//ERR_IO_TYPE
	"Too more statement to process for the device",	//ERR_IO_OUTOPER
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"Unkonw error or the error occur in the transmit cann`t be identified by the read device"
};
//RFIDDioErrorMsg[ERR_IO_UNKNOW - ERR_IO_UNFULL] = "属于该范围但读写器无法判断或未知类型错误";//ERR_IO_UNKNOW = 0x2F


//RFIDEPCErrorMsg[ERR_EPC_UNKNOW - ERR_EPC_NOTAG] = "属于该范围但读写器无法判断或未知类型错误";//ERR_EPC_UNKNOW = 0x6F

//注意: 同上

const char* RFID6BErrorMsg[ERR_6B_UNKNOW - ERR_6B_OUTRESPONSE + 1] = {
	"Label no respond or there is no label in scope",			//ERR_6B_OUTRESPONSE = 0x90
	"Not support the statement",							//ERR_6B_NONSUPPORT
	"Not identify the statement, the format maybe worng",			//ERR_6B_FORMAT
	"Not support the item",							//ERR_6B_OPTIONNONSUP
	"Unknow error",								//ERR_6B_UNKNOWERR
	"Cann`t operate the special block",						//ERR_6B_RWBANK
	"Cann`t lock the block because it`s been locked",		//ERR_6B_HADLOCK
	"Cann`t modify the data as the operation block locked",		//ERR_6B_DATAHADLOCK
	"Program block failed",				//ERR_6B_BANKOPER
	"Lock block failed",				//ERR_6B_BANKLOCK
	"Operation has been stoped",	//ERR_6B_OPERUNFINISH
	"Operation not finish as the reason disturbed",				//ERR_6B_OPERUNFINISHBYDIS
	"CRC value returned by label is wrong ",						//ERR_6B_RCR
	"",
	"",
	"Unkonw error or the error belongs to label but cann`t be identified by the read device"
};
//RFID6BErrorMsg[ERR_6B_UNKNOW - ERR_6B_OUTRESPONSE] = "属于该范围但读写器无法判断或未知类型错误";//ERR_6B_UNKNOW = 0x9F

//注意: 同上

const char* RFIDEPCErrorMsg[ERR_EPC_UNKNOW - ERR_EPC_NOTAG + 1] = {
	"Label no respond or not exist",					//ERR_EPC_NOTAG = 0x60
	"Operation memory is not exist",						//ERR_EPC_NOSAVEADDR
	"Return value from label: operation address is overflow",		//ERR_EPC_OVERADDR
	"Return value from label: operation memory is locked",		//ERR_EPC_LOCK
	"Label access PWD is wrong",	
	"Label kill PWD is wrong",//ERR_EPC_ACCESSPWD
	"Operation has been stoped",						//ERR_EPC_DESTROYPWD
	"The label which being read, write or lock not initialize",	//ERR_EPC_OPERUNFINISH
	"Not initialize label when read device",	//ERR_EPC_UNINIT
	"Return value from label: unknow error",				//ERR_EPC_UNINITTAG
	"Return value from label: power low",			//ERR_EPC_UNKNOWTYPE
	"",				//ERR_EPC_LACKPOWER
	"",
	"",
	"",
	"Unkonw error or the error belongs to ISO18000-6C label but cann`t be identified by the read device"
};
const char* mCopyright = "1.0.3";


