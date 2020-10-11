//////////////////////////////////////////////////////////////////////////

#pragma once

extern const char* mCopyright;
extern void printData(char *szAlert,unsigned char *pMsg,int nLen);

#include <string>
#include <comutil.h>
using namespace std;

#define CMD_DATA_BUFFER		1024				//�����������
#define FRAME_WITHOUTBLENGTH	5				//֡ͷ����	
#define DATA_BUFFER			CMD_DATA_BUFFER-FRAME_WITHOUTBLENGTH//�����������

#define SEND_WAIT 1000
#define MSG_MAX_BUFFER 2000

#define TAG_REV_TIME 100
#define BYTE_BUFFER_SIZE 255

#define TAG_6CREAD_TIME 500
#define COMMAND_LEN 1
#define ANSWER_LEN 1
#define ANTENNA_LEN 1
#define DATA_6CONCEREAD_LEN 14				//6Cһ�ζ�ȡ�ĳ���
#define DATA_6CONCEWRITE_LEN 14				//6Cһ��д��ĳ���


#define SAAT_610_PORT			7086			//����˿�
#define CMD_DATA_BUFFER			1024				//�����������
#define DATA_6CONCEREAD_LEN 14				//6Cһ�ζ�ȡ�ĳ���
#define DATA_6CONCEWRITE_LEN 14				//6Cһ��д��ĳ���
#define SENDFRAME_MAXBUF	1024			//����֡�������ռ�
#define REC_FRAME_MAXBUFF	8192			//����֡�Ļ���	
#define REC_FRAME_ONCE      256
#define COM_FRAME_ONCE		1024			//��ǰ��17
#define TCP_FRAME_ONCE		1024*32				// ��ǰ�� 17 why 
#define UDP_FRAME_ONCE		255
#define	FRAME_HEAD			0xAA			//֡ͷ
#define FRAME_HEAD_REPLACE	0xAB			//֡ͷ�滻 0x55 <-> 0x56
#define FRAME_FRAME_REPLACE	0xAC			//֡�滻   0x56 <-> 0x57
#define	FRAME_PRIORITY		0x20			//����λ 0010 0000
#define	FRAME_ANSWER		0x10			//Ӧ��֡ 0001 0000
#define RECVFRAME_MAXBUF    1024				//����֡�������ռ�

#define TCP_FRAME_HEAD_LENGTH		6  // TCP ֡ͷ����

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
//��λ��(PC��)����
//////////////////////////////////////////////////////////////////////////
extern const char* RFIDError[] ;
enum RFIDErrorCode {
	NO_ERR =0x500,			//"�����ɹ�"
	ERR_NOT_CONNECT,		//�˿�δ��
	ERR_READING_NOTEXE,		//����״̬�в���ִ�е�ָ��
	ERR_COMMAND_EXEING,		//ָ����ִ�е���
	ERR_INVALID_SOCKET,		//"Socket����ʧ��"
	ERR_CONNECT_FAIL,		//"����ʧ��"
	ERR_CONNECT_OUTTIME,	//"���ӳ�ʱ"
	ERR_CONNECT_CONNECTING,	//"��������"
	ERR_CLOSE_FAIL,			//"�ر�����ʧ��"
	ERR_SOCKET_ERR,			//"ѡ��socketʱ����"
	ERR_TCPSEND_ERR,		//"����ʧ��"
	ERR_FRAME_LOSE,			//"����֡��ʧ"
	ERR_FRAME_CRC16,		//"����֡CRC16У�����"
	ERR_COMHANDLE_INVALID,	//"����δ���ӻ�����ʧЧ"
	ERR_COMSEND_FAIL,		//"�������ݵ�����ʧ��"
	ERR_COMRECV_FAIL,		//"��ȡ��������ʧ��"
	ERR_COMRECVHEAD_FAIL,	//"���ڣ���ȡ֡ͷ����"
	ERR_COMOPEN_FAIL,		//"�򿪴���ʧ��"
	ERR_INITSOCKET_FAIL,	//"��ʼ���׽���ʧ��"
	ERR_TCP_NOTOPEN,		//SOCKET�˿�δ��
	ERR_COM_NOTOPEN,		//����δ��
	ERR_USB_NOTOPEN,		//USB��δ��
	ERR_SETCOM_STATE,		//"Set up com state����"
	ERR_SETUP_COM,			//"Set up com ����"
	ERR_OVERLAPREAD_NULL,	//"���� overlapread �¼����Ϊ��"
	ERR_OVERLLAPWRITE_NULL,	//"���� overlapwrite �¼����Ϊ��"
	ERR_TCPRECV_SOCKETERROR,//"TCP��������ʱsocket����"
	ERR_TCPRECV_SOCKETOVERTIME,//"TCP�������ݳ�ʱ" 
	ERR_TCPSEND_SOCKETERROR,//"TCP��������ʱsocket����"
	ERR_TCPSEND_SOCKETOVERTIME,//"TCP�������ݳ�ʱ"
	ERR_UDPRECV_SOCKETERROR,//"UDP��������ʱsocket����"
	ERR_UDPRECV_SOCKETOVERTIME,//"UDP�������ݳ�ʱ" 
	ERR_MOREDATA_NEED,		//"�ڴ���䲻��"
	ERR_POINTER_NULL,		//"��δ���:��ָ��,δ�����ڴ�"
	ERR_SIZE_ZERO,			//"��δ���:����Ϊ0"
	ERR_OVER_NOSIGNED,		//"���ó�ʱ,�����߳����ڶԶ�д�����в���"
	ERR_START_OVERFLOW,     //��ʼ��ַ���ȴ���255
	ERR_LEN_OVERFLOW,       //���ȴ���255
	ERR_SIXBWRITE_OVERFLOW,    //д6B��ǩ����ʱ,�������׵�ַ�����������ȴ���224�ֽ�
	ERR_SIXBREAD_OVERFLOW,		//��6B��ǩ����ʱ,�������׵�ַ�����������ȳ���224�ֽ�
	ERR_SIXBLOGDATA_OVERFLOW,      //��6B��ǩ����ʱ,�������׵�ַ�����������ȳ���224�ֽ�
	ERR_GETCOM_STATE,//GetCommState����
	ERR_GETCOM_TIMEOUT,//GetCommTimeouts����
	ERR_SETCOM_TIMEOUT,//SetCommTimeouts����
	ERR_STARTREVTHREAD_FAIL,//���������̳߳���
	ERR_RECVTHREAD_OVERTIME, //��ʱδ�յ�����
	ERR_DATALEN_LOZERO,
	ERR_WRITE_EPCLEN, //дEPC�볤�Ȳ���12�ֽ�
	ERR_USB_SEND,//USB��������ʧ��
	ERR_OVER_FRAMELIST,
};


extern const unsigned short CRCTable[256];

typedef unsigned (WINAPI *PBEGINTHREADEX_THREADFUNC)(
	LPVOID lpThreadParameter
	);
typedef unsigned *PBEGINTHREADEX_THREADID;

