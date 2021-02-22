//////////////////////////////////////////////////////////////////////////

#pragma once

extern const char* mCopyright;
extern void printData(char *szAlert,unsigned char *pMsg,int nLen);

#include <string>
#include <comutil.h>
using namespace std;

#define CMD_DATA_BUFFER		1024				//数据域最大宽度
#define FRAME_WITHOUTBLENGTH	5				//帧头长度	
#define DATA_BUFFER			CMD_DATA_BUFFER-FRAME_WITHOUTBLENGTH//数据域最大宽度

#define SEND_WAIT 1000
#define MSG_MAX_BUFFER 2000

#define TAG_REV_TIME 100
#define BYTE_BUFFER_SIZE 255

#define TAG_6CREAD_TIME 500
#define COMMAND_LEN 1
#define ANSWER_LEN 1
#define ANTENNA_LEN 1
#define DATA_6CONCEREAD_LEN 14				//6C一次读取的长度
#define DATA_6CONCEWRITE_LEN 14				//6C一次写入的长度


#define SAAT_610_PORT			7086			//定义端口
#define CMD_DATA_BUFFER			1024				//数据域最大宽度
#define DATA_6CONCEREAD_LEN 14				//6C一次读取的长度
#define DATA_6CONCEWRITE_LEN 14				//6C一次写入的长度
#define SENDFRAME_MAXBUF	1024			//发送帧定义最大空间
#define REC_FRAME_MAXBUFF	8192			//接收帧的缓冲	
#define REC_FRAME_ONCE      256
#define COM_FRAME_ONCE		1024			//以前是17
#define TCP_FRAME_ONCE		1024*32				// 以前是 17 why 
#define UDP_FRAME_ONCE		255
#define	FRAME_HEAD			0xAA			//帧头
#define FRAME_HEAD_REPLACE	0xAB			//帧头替换 0x55 <-> 0x56
#define FRAME_FRAME_REPLACE	0xAC			//帧替换   0x56 <-> 0x57
#define	FRAME_PRIORITY		0x20			//优先位 0010 0000
#define	FRAME_ANSWER		0x10			//应答帧 0001 0000
#define RECVFRAME_MAXBUF    1024				//接收帧定义最大空间

#define TCP_FRAME_HEAD_LENGTH		6  // TCP 帧头长度

extern const unsigned short CRCTable[256];


#define API_SENDDATA_BUFF 1024

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


//////////////////////////////////////////////////////////////////////////
//上位机(PC机)错误集
//////////////////////////////////////////////////////////////////////////
extern const char* RFIDError[] ;
enum RFIDErrorCode {
	NO_ERR =0x500,			//"操作成功"
	ERR_NOT_CONNECT,		//端口未打开
	ERR_READING_NOTEXE,		//读卡状态中不可执行的指令
	ERR_COMMAND_EXEING,		//指令在执行当中
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
	ERR_OVER_FRAMELIST,
};


extern const unsigned short CRCTable[256];

typedef unsigned (WINAPI *PBEGINTHREADEX_THREADFUNC)(
	LPVOID lpThreadParameter
	);
typedef unsigned *PBEGINTHREADEX_THREADID;

