#include "StdAfx.h"
#include "CNGetMsg.h"
#include "../Global.h"

CErrorStruct errorCNMsg[] = 
{
	{0x0,L"操作成功"},
	{0x10,L"读写设备解码单元的软件版本错误"},
	{0x11,L"读写设备基带单板硬件版本号错误"},
	{0x12,L"读写设备射频单板硬件版本号错误"},
	{0x13,L"读写设备扩展单板硬件版本号错误"},
	{0x14,L"读写设备基带板启动自检失败"},
	{0x15,L"读写设备射频板启动自检失败"},
	{0x16,L"读写设备以太网启动自检失败"},
	{0x17,L"读写设备实时时钟启动自检失败"},
	{0x18,L"读写设备外部存储器启动自检失败"},
	{0x19,L"读写设备系统参数表自检错误"},
	{0x1F,L"未知类型的系统硬件错误"},
	{0x20,L"读写设备操作权限密码错误"},
	{0x21,L"使用了禁止或错误的天线端口号"},
	{0x22,L"当前读写设备处于测试模式"},
	{0x23,L"操作读写设备内部存储设备失败"},
	{0x24,L"当前读写设备正执行不可中断操作"},
	{0x25,L"读写设备运行错误，如程序运行出现非法操作"},
	{0x26,L"操作权限占用（已有另一高级用户已经连接）"},
	{0x2F,L"未知类型的读写设备操作错误"},
	{0x60,L"接收的指令或数据的帧结构不完整"},
	{0x61,L"接收的指令或数据的CRC校验错误"},
	{0x62,L"当前型号读写设备不支持该指令类型"},
	{0x63,L"当前型号读写设备不支持该标签协议"},
	{0x64,L"接收的指令中参数有错误"},
	{0x65,L"指令帧结构错误（缺少域或域结构错误）"},
	{0x66,L"读写设备接收到太多指令，暂时无法处理"},
	{0x6F,L"未知类型的数据传输类型错误"},
	{0xA0,L"标签无响应或射频范围内无标签"},
	{0xA1,L"该指令操作标签不支持"},
	{0xA2,L"该指令未被标签识别，如地址错误"},
	{0xA3,L"该选项不支持"},
	{0xA4,L"标签返回的未知错误码"},
	{0xA5,L"标签无法存取特定的块"},
	{0xA6,L"标签指定字节已经锁定，无法再次锁定"},
	{0xA7,L"标签指定字节已经锁定，内容无法改写"},
	{0xA8,L"标签执行字节数据写入操作失败"},
	{0xA9,L"标签执行字节锁定操作失败"},
	{0xAA,L"标签操作未完成，被上位机终止（如关载波）"},
	{0xAB,L"标签操作因干扰等原因未能全部完成"},
	{0xAC,L"标签返回CRC错误"},
	{0xAF,L"未知类型的ISO18000-6B标签操作错误"},
	{0xB0,L"标签无响应或射频范围内不存在标签"},
	{0xB1,L"要操作的标签存储区（Bank）不存在"},
	{0xB2,L"标签返回信息：标签操作地址溢出"},
	{0xB3,L"标签返回信息：操作存储区被锁定"},
	{0xB4,L"标签存取密码错误"},
	{0xB5,L"标签灭活密码错误"},
	{0XB6,L"操作未完成，被上位机终止（如关载波）"},
	{0xB7,L"要做读/写/锁数据区操作的标签未初始化"},
	{0xB8,L"读卡操作时发现未初始化标签。"},
	{0xB9,L"标签返回信息：未知类型错误"},
	{0xBA,L"标签返回信息：功率不足"},
	{0xBF,L"未知类型的ISO18000-6C标签操作错误"},
	{NO_ERR,L"操作成功"},						//NO_ERR
	{ERR_NOT_CONNECT,L"端口未打开"},
	{ERR_READING_NOTEXE,L"读卡状态中不可执行的指令"},
	{ERR_COMMAND_EXEING,L"指令在执行当中"},
	{ERR_INVALID_SOCKET,L"Socket创建失败"},					//ERR_INVALID_SOCKET
	{ERR_CONNECT_FAIL,L"连接失败"},							//ERR_CONNECT_FAIL
	{ERR_CONNECT_OUTTIME,L"连接超时"},							//ERR_CONNECT_OUTTIME
	{ERR_CONNECT_CONNECTING,L"正在连接"},							//ERR_CONNECT_CONNECTING
	{ERR_CLOSE_FAIL,L"关闭连接失败"},						//ERR_CLOSE_FAIL
	{ERR_SOCKET_ERR,L"选择socket时出错"},					//ERR_SOCKET_ERR
	{ERR_TCPSEND_ERR,L"发送失败"},							//ERR_TCPSEND_ERR
	{ERR_FRAME_LOSE,L"数据帧丢失"},						//ERR_FRAME_LOSE
	{ERR_FRAME_CRC16,L"数据帧CRC16校验出错"},				//ERR_FRAME_CRC16
	{ERR_COMHANDLE_INVALID,L"串口未连接或连接失效"},				//ERR_COMHANDLE_INVALID
	{ERR_COMSEND_FAIL,L"发送数据到串口失败"},				//ERR_COMSEND_FAIL
	{ERR_COMRECV_FAIL,L"收取串口数据失败"},					//ERR_COMRECV_FAIL
	{ERR_COMRECVHEAD_FAIL,L"串口：收取帧头错误"},				//ERR_COMRECVHEAD_FAIL
	{ERR_COMOPEN_FAIL,L"打开串口失败"},						//ERR_COMOPEN_FAIL
	{ERR_INITSOCKET_FAIL,L"初始化套接字失败"},					//ERR_INITSOCKET_FAIL
	{ERR_SETCOM_STATE,L"Set up com state出错"},				//ERR_SETCOM_STATE,
	{ERR_SETUP_COM,L"Set up com 出错"},					//ERR_SETUP_COM,
	{ERR_OVERLAPREAD_NULL,L"串口 overlapread 事件句柄为空"},	//ERR_OVERLAPREAD_NULL,
	{ERR_OVERLLAPWRITE_NULL,L"串口 overlapwrite 事件句柄为空"},	//ERR_OVERLLAPWRITE_NULL
	{ERR_TCPRECV_SOCKETERROR,L"TCP接收数据时socket出错"},          //ERR_TCPRECV_SOCKETERROR
	{ERR_TCPRECV_SOCKETOVERTIME,L"TCP接收数据超时"},                  //ERR_TCPSEND_SOCKETOVERTIME,	
	{ERR_TCPSEND_SOCKETERROR,L"TCP发送数据时socket出错"},			//ERR_TCPSEND_SOCKETERROR,
	{ERR_TCPSEND_SOCKETOVERTIME,L"TCP发送数据超时"},					//ERR_TCPSEND_SOCKETOVERTIME,
	{ERR_UDPRECV_SOCKETERROR,L"UDP接收数据时socket出错"},
	{ERR_UDPRECV_SOCKETOVERTIME,L"UDP接收数据超时" },
	{ERR_MOREDATA_NEED,L"内存分配不足"},						//ERR_MOREDATA_NEED
	{ERR_POINTER_NULL,L"入参错误:空指针,未分配内存"},		//ERR_POINTER_NULL	
	{ERR_SIZE_ZERO,L"入参错误:传入长度为0"},					//ERR_SIZE_ZERO
	{ERR_OVER_NOSIGNED,L"调用超时,其他线程正在对读写器进行操作"}, //ERR_OVER_NOSIGNED
	{ERR_START_OVERFLOW,L"起始地址长度大于255L"},     //ERR_START_OVERFLOW
	{ERR_LEN_OVERFLOW,L"长度大于255"},       //ERR_LEN_OVERFLOW
	{ERR_SIXBWRITE_OVERFLOW,L"写6B标签数据时,数据区首地址加数据区长度大于224字节"}, //ERR_SIXBWRITE_OVERFLOW
	{ERR_SIXBREAD_OVERFLOW,L"读6B标签数据时,数据区首地址加数据区长度超出224字节"}, //ERR_SIXBREAD_OVERFLOW	
	{ERR_SIXBLOGDATA_OVERFLOW,L"锁6B标签数据时,数据区首地址加数据区长度超出224字节"}, //ERR_SIXBDATA_OVERFLOW
	{ERR_GETCOM_STATE,L"GetCommState出错"}, //ERR_GETCOM_STATE,//GetCommState出错
	{ERR_GETCOM_TIMEOUT,L"GetCommTimeouts出错"} ,//ERR_GETCOM_TIMEOUT,//GetCommTimeouts出错
	{ERR_SETCOM_TIMEOUT,L"SetCommTimeouts出错"}, //ERR_SETCOM_TIMEOUT,//SetCommTimeouts出错
	{ERR_STARTREVTHREAD_FAIL,L"启动收信件线程失败"},//ERR_STARTREVTHREAD_FAIL,//启动收信件线程失败
	{ERR_RECVTHREAD_OVERTIME,L"超时未收到数据"},//ERR_RECVTHREAD_OVERTIME //超时未收到数据
	{ERR_DATALEN_LOZERO,L"收到的信件数据区长度小于0,异常"},
	{ERR_WRITE_EPCLEN,L"写EPC码长度不足12字节"}, //ERR_WRITE_EPCLEN
	{ERR_USB_SEND,L"USB发送数据失败"}//ERR_USB_SEND
};


CCNGetMsg::CCNGetMsg(void)
{
	typedef pair <int,wstring> Int_Pair;

	for( int i =0 ; i< sizeof(errorCNMsg)/sizeof(CErrorStruct);i++)
	{
		CErrorStruct t = errorCNMsg[i];
		m_mapError.insert(Int_Pair(t.nCode,t.szMsg));
	}

}

CCNGetMsg::~CCNGetMsg(void)
{
}





void CCNGetMsg::GetErrorMsg(int nCode,string& strError) 
{
	typedef pair <int, wstring> Int_Pair;
	map <int, wstring> :: const_iterator m1_RcIter;
	m1_RcIter = m_mapError.find( nCode );

	if ( m1_RcIter == m_mapError.end( ) )
	{
		strError ="未知错误";
		return;
	}

	const WCHAR *pError  = m_mapError[nCode].c_str();
	CHAR szGB2312[DATA_BUFFER] = {0};
	WideCharToMultiByte (CP_ACP, 0, pError, -1, szGB2312,DATA_BUFFER, NULL,NULL);
	strError = szGB2312;
//	strError =	m_mapError[nCode];
}


