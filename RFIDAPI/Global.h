//////////////////////////////////////////////////////////////////////////

#pragma once


//************  �������ã�C# �� C++�ȴ�ʱ�䲻ͬ
#define  CPLUSPLUS //�����������for  C++
//#define  CSHARP  //�����������for c#


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


#define SAAT_610_PORT			7086			//����˿�
#define DATA_BUFFER			1024			//�����������
#define CMD_DATA_BUFFER			1024				//�����������
#define DATA_6CONCEREAD_LEN 14				//6Cһ�ζ�ȡ�ĳ���
#define DATA_6CONCEWRITE_LEN 14				//6Cһ��д��ĳ���
#define SENDFRAME_MAXBUF	1024			//����֡�������ռ�
#define REC_FRAME_MAXBUFF	8192			//����֡�Ļ���	
#define REC_FRAME_ONCE      256
#define COM_FRAME_ONCE		17
#define TCP_FRAME_ONCE		17
#define UDP_FRAME_ONCE		255
#define	FRAME_HEAD			0xAA			//֡ͷ
#define FRAME_HEAD_REPLACE	0xAB			//֡ͷ�滻 0x55 <-> 0x56
#define FRAME_FRAME_REPLACE	0xAC			//֡�滻   0x56 <-> 0x57
#define	FRAME_PRIORITY		0x20			//����λ 0010 0000
#define	FRAME_ANSWER		0x10			//Ӧ��֡ 0001 0000
#define RECVFRAME_MAXBUF    256				//����֡�������ռ�

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


//#define COM_STOP_READ 0x53 //�����Ѷ���ָ��

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
	PortType nPortType;				//ͨѶģʽ��Ŀǰ����TCP/USB/COM
	string strHostName;				//������IP��ַ����������ͨѶģʽ����Ч
	int nSocketPort;			    //����SOCKET�˿�
	string strComNum;				//COM1��COM4 ����COMͨѶģʽ����Ч
	int    nBaud;					//����(USB��)ͨѶ����
	unsigned char nBusAddr;         //���ߵ�ַ
	string strUSBNum;               //USB1-USB8  ����USBͨѶģʽ����Ч
	unsigned char ucScanTimes;		//ÿ�η��Ͷ���ָ��󣬶�������ѯ��ǩ�Ĵ���
	unsigned char ucRetryTimes;		//û��ɨ�赽��ǩ�����·���ָ��Ĵ�����
	unsigned char ucRereadTimes;	//����ǩ�ط�ָ�����
	unsigned char ucRewriteTimes;	//д��ǩ�ط�ָ�����
	unsigned char ucLeadInTotal;	//��������������1��4��
	unsigned char ucLeadInCtrl;		//���߿��Ʒ�ʽ��0���Զ�ɨ���������߶˿�,1~4����ָ���˿ڽ���ɨ�裩
	unsigned char ucSaveLog;		//�Ƿ񱣴���Լ�¼��־��0��������־��1��������־��
	string ucLogFName;		//���Լ�¼��־�ļ���
	string strLanguageType;
	CRFIDSystemCfg()
	{
		LCID lcid = GetSystemDefaultLCID();//���⴦��,���������ö�̬����������
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
	unsigned char bFrame;			//֡ͷ AAH
	unsigned char bAddrInfo;		//֡��Ϣ
	unsigned char bAddr;			//���ߵ�ַ
	unsigned char bLength;			//���ݳ���  ����ָ������ݵĳ���
	unsigned char bCommand;			//ָ��
	unsigned char bData[CMD_DATA_BUFFER];//������  +  CRC16У��
};

struct CRFIDFrame 
{
	 CRFrame RFIDInFrame;//���͵�����
	 CRFrame RFIDOutFrame;//���յĻ�Ӧ
	 HANDLE m_revHandle;//�����ź�

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
//RFIDָ�
//////////////////////////////////////////////////////////////////////////
enum RFIDCommandCode {
	COM_SYS_CFG,			//ϵͳ��Ϣ����
	COM_SYS_QUERY,			//ϵͳ��Ϣ��ѯ
	COM_WORKMOD_CFG,		//����ģʽ����
	COM_WORKMOD_QUERY,		//����ģʽ��ѯ
	COM_TEST_CONTROL,		//ϵͳ���Կ���
	COM_PARA_OP,			//���������
	COM_ANTENNA_SET,		//��Ƶ�˿ڲ�������
	COM_ANTENNA_QUERY,		//��Ƶ�˿ڲ�����ѯ
	COM_CARRYWAVE_SET,		//�ز���������
	COM_CARRYWAVE_QUERY,	//�ز�������ѯ
	COM_COMMUNI_SET,		//ͨ�Ų�������
	COM_COMMUNI_QUERY,		//ͨ�Ų�����ѯ
	COM_NETPARA_SET,		//�����������
	COM_NETPARA_QUERY,		//���������ѯ
	COM_TAG_SET,			//��ǩ������������
	COM_TAG_QUERY,			//��ǩ����������ѯ
	COM_EXTENDBOARD_SET,	//��չ���������
	COM_EXTENDBOARD_QUERY,	//��չ�������ѯ
	COM_ANTENNA_SET_EX,		//��Ƶ�˿ڲ�������-��չ��
	COM_ANTENNA_QUERY_EX,	//��Ƶ�˿ڲ�����ѯ-��չ��
	COM_CARRY_OP,           //�ز�����ָ��
	COM_IO_OP,				//�������ָ��
	COM_INPUT_QUERY,		//�����ѯָ��
	READING_IO_CONFIG,		//����ָʾ����ָ��
	READING_IO_QUERY,		//����ָʾ��ѯָ��
	COM_IO_PULSESET,		//0x25����ָʾ��������
	COM_IO_PULSEQUERY,		//0x26	����ָʾ�����ѯ
	COM_READER_REBOOT,		//����ָ��
	COM_OPEN_CONN,			//������
	COM_CLOSE_CONN,			//�ر�����
	COM_STOP_READ,          //0x53ֹͣ����
	COM_SEND_HEART,         //������ 0x58,  
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
	COM_6BSELECT_TAG,		//6B��ǩѡ������
	COM_6BREAD_UID,			//6B��ȡUID������
	COM_6BREADUSER_DATA,	//6B����ǩ����
	COM_6BWRITEUSER_DATA,	//6Bд��ǩ����
	COM_6BLOCK_TAGDATA,		//6B����ǩ����
	COM_6BLOCK_QUERY,		//6B����ǩ��ѯ,
	COM_6CSELECT_EPCTAG,	//6C��ǩѡ��
	COM_6CREAD_EPC,			//6C��EPC��
	COM_6CREAD_TID,			//6C��TID��
	COM_6CREAD_EPCTID,		//6C��EPC+TID��
	COM_6CWRITE_EPCDATA,	//6CдEPC����
	COM_6CREADUSER_DATA,	//6C���û�������
	COM_6CWRITEUSER_DATA,	//6Cд�û�������
	COM_6CBLOCKWRITE_DATA,	//��дBank����
	COM_6CBLOCKCLEAR_DATA,	//���Bank����
	COM_6CACCESSPWD_CFG,	//���÷�������
	COM_6CDESTORYPWD_CFG,	//������������ָ��
	COM_6CLOCK_TAGCFG,		//��ǩ��״̬����
	COM_DESTORY_TAG,		//��ǩ���ָ��
	COM_EASFLAG_CFG,		//EAS��־����ָ��
	COM_EAS_ENABLE,		//EAS��ع�������ָ��
	READER_TIME_SET,		//��д��ʱ������
	READER_TIME_QUERY,		//��д��ʱ���ѯ
	READER_FLASHDATA_QUERY,	//FLASH���ݲ�ѯ
	READER_FLASHDATACOUNT_QUERY, //FLASH���ݱ�ǩ����ѯ
	READER_FLASHCLEAR,		//��FLASH����

	COM_GPRS_SET,		//GPRS����
	COM_GPRS_QUERY,		//GPRS��ѯ
	COM_WIFI_SET,		//WIFI����
	COM_WIFI_QUERY,		//WIFI��ѯ
	COM_WIFI_TRANS_REST, //WIFI����͸�����߸�λ

	COM_YRF_SET,
	COM_YRF_QUERY,
};



extern const unsigned char RFIDCommand[256];

//////////////////////////////////////////////////////////////////////////
//��λ��(PC��)����
//////////////////////////////////////////////////////////////////////////


extern const char* RFIDError[] ;
enum RFIDErrorCode {
	NO_ERR =0x500,					//"�����ɹ�"
	ERR_NOT_CONNECT,//�˿�δ��
	ERR_READING_NOTEXE,		//����״̬�в���ִ�е�ָ��
	ERR_COMMAND_EXEING,			//ָ����ִ�е���
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
};




extern const unsigned short CRCTable[256];


typedef bool(WINAPI *RECVBACKPROCFUN)(unsigned char* btMsg,int nLen);

typedef unsigned (WINAPI *PBEGINTHREADEX_THREADFUNC)(
	LPVOID lpThreadParameter
	);
typedef unsigned *PBEGINTHREADEX_THREADID;

typedef bool(WINAPI *RECVRFAMERECVPROCFUN)(CRFrame& Frame);
