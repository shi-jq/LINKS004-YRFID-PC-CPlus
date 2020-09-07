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

/*Ϊ�˵��Դ�ӡ����*/
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
//��λ��(PC��)����
//////////////////////////////////////////////////////////////////////////
const char* RFIDError[] = {
	"�����ɹ�",							//NO_ERR
	"Socket����ʧ��",					//ERR_INVALID_SOCKET
	"����ʧ��",							//ERR_CONNECT_FAIL
	"���ӳ�ʱ",							//ERR_CONNECT_OUTTIME
	"��������",							//ERR_CONNECT_CONNECTING
	"�ر�����ʧ��",						//ERR_CLOSE_FAIL
	"ѡ��socketʱ����",					//ERR_SOCKET_ERR
	"����ʧ��",							//ERR_TCPSEND_ERR
	"����֡��ʧ",						//ERR_FRAME_LOSE
	"����֡CRC16У�����",				//ERR_FRAME_CRC16
	"����δ���ӻ�����ʧЧ",				//ERR_COMHANDLE_INVALID
	"�������ݵ�����ʧ��",				//ERR_COMSEND_FAIL
	"��ȡ��������ʧ��",					//ERR_COMRECV_FAIL
	"���ڣ���ȡ֡ͷ����",				//ERR_COMRECVHEAD_FAIL
	"�򿪴���ʧ��",						//ERR_COMOPEN_FAIL
	"��ʼ���׽���ʧ��",					//ERR_INITSOCKET_FAIL
	"Set up com state����",				//ERR_SETCOM_STATE,
	"Set up com ����",					//ERR_SETUP_COM,
	"���� overlapread �¼����Ϊ��",	//ERR_OVERLAPREAD_NULL,
	"���� overlapwrite �¼����Ϊ��",	//ERR_OVERLLAPWRITE_NULL
	"TCP��������ʱsocket����",          //ERR_TCPRECV_SOCKETERROR
	"TCP�������ݳ�ʱ",                  //ERR_TCPSEND_SOCKETOVERTIME,	
	"TCP��������ʱsocket����",			//ERR_TCPSEND_SOCKETERROR,
	"TCP�������ݳ�ʱ",					//ERR_TCPSEND_SOCKETOVERTIME,
	"�ڴ���䲻��",						//ERR_MOREDATA_NEED
	"��δ���:��ָ��,δ�����ڴ�",		//ERR_POINTER_NULL	
	"��δ���:���볤��Ϊ0",					//ERR_SIZE_ZERO
	"���ó�ʱ,�����߳����ڶԶ�д�����в���", //ERR_OVER_NOSIGNED
	"��ʼ��ַ���ȴ���255",     //ERR_START_OVERFLOW
	"���ȴ���255",       //ERR_LEN_OVERFLOW
	"д6B��ǩ����ʱ,�������׵�ַ�����������ȴ���224�ֽ�", //ERR_SIXBWRITE_OVERFLOW
	"��6B��ǩ����ʱ,�������׵�ַ�����������ȳ���224�ֽ�", //ERR_SIXBREAD_OVERFLOW	
	"��6B��ǩ����ʱ,�������׵�ַ�����������ȳ���224�ֽ�", //ERR_SIXBDATA_OVERFLOW
	"GetCommState����", //ERR_GETCOM_STATE,//GetCommState����
	"GetCommTimeouts����", //ERR_GETCOM_TIMEOUT,//GetCommTimeouts����
	"SetCommTimeouts����", //ERR_SETCOM_TIMEOUT,//SetCommTimeouts����
	"�������ż��߳�ʧ��",//ERR_STARTREVTHREAD_FAIL,//�������ż��߳�ʧ��
	"��ʱδ�յ�����",//ERR_RECVTHREAD_OVERTIME //��ʱδ�յ�����
	"�յ����ż�����������С��0,�쳣",
	"дEPC�볤�Ȳ���12�ֽ�", //ERR_WRITE_EPCLEN
	"USB��������ʧ��",//ERR_USB_SEND
};

//////////////////////////////////////////////////////////////////////////
//RFIDָ�
//////////////////////////////////////////////////////////////////////////




const unsigned char RFIDCommand[256] = {
	0x00,            //ϵͳ��Ϣ����
	0x01,            //ϵͳ��Ϣ����
	0x02,			//����ģʽ����
	0x03,			//����ģʽ��ѯ
	0x0A,           //ϵͳ���Կ���
	0x10,			//���������
	0x11,           //��Ƶ�˿ڲ�������
	0x12,			//��Ƶ�˿ڲ�����ѯ
	0x13,			//COM_CARRYWAVE_SET,		//�ز���������
	0x14,			//COM_CARRYWAVE_QUERY,		//�ز�������ѯ
	0x15,			//COM_COMMUNI_SET,			//ͨ�Ų�������
	0x16,			//COM_COMMUNI_QUERY,		//ͨ�Ų�����ѯ
	0x17,			//COM_NETPARA_SET,			//�����������				
	0x18,			//COM_NETPARA_QUERY,		//���������ѯ
	0X19,										//��ǩ������������
	0x1A,										//��ǩ����������ѯ
	0x1B,										//��չ���������
	0x1C,			//��չ�������ѯ
	0x20,           //�ز�����ָ��
	0x21,           //�������ָ��
	0x22,			//�����ѯָ��
	0x23,			//READING_IO_CONFIG		����ָʾ����ָ��
	0x24,			//READING_IO_QUERY		����ָʾ��ѯָ��
	0x25,			//COM_IO_PULSESET			����ָʾ��������
	0x26,			//COM_IO_PULSEQUERY			����ָʾ�����ѯ
	0x2A,			//����ָ��
	0x50,			//COM_OPEN_CONN //������
	0x51,           //COM_CLOSE_CONN //�ر�����
	0x53,   //COM_STOP_READ        //ֹͣ����
	0x58,           //COM_SEND_HEART        //������
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
	0x80,			//COM_6BSELECT_TAG,			//6B��ǩѡ������
	0x81,			//COM_6BREAD_UID,			//6B��ȡUID������
	0x82,			//COM_6BREADUSER_DATA,		//6B����ǩ����
	0x83,			//COM_6BWRITEUSER_DATA,		//6Bд��ǩ����
	0x84,			//COM_6BLOCK_TAGDATA,		//6B����ǩ����
	0x85,           //COM_6BLOCK_QUERY //
	0x90,			//COM_6CSELECT_EPCTAG,		//6C��ǩѡ��
	0x91,			//COM_6CREAD_EPC,			//6C��EPC��
	0x92,			//COM_6CREAD_TID,			//6C��TID��
	0x9F,			//COM_6CREAD_EPCTID,		//6C��ȡEPCTID��
	0x93,			//COM_6CWRITE_EPCDATA,		//6CдEPC����
	0x94,			//COM_6CREADUSER_DATA,		//6C���û�������
	0x95,			//COM_6CWRITEUSER_DATA,		//6Cд�û�������
	0x96,			//COM_6CBLOCKWRITE_DATA,	//��дBank����
	0x97,			//COM_6CBLOCKCLEAR_DATA,	//���Bank����
	0x98,			//COM_6CACCESSPWD_CFG,		//���÷�������
	0x99,			//COM_6CDESTORYPWD_CFG,		//������������ָ��
	0x9A,			//COM_6CLOCK_TAGCFG,		//��ǩ��״̬����
	0x9B,			//COM_DESTORY_TAG,			//��ǩ���ָ��
	0x9C,			//COM_EASFLAG_CFG,			//EAS��־����ָ��
	0x9D,			//COM_EAS_ENABLE			//EAS��ع�������ָ��
	0xB0,			//READER_TIME_SET,				//��д��ʱ������
	0xB1,			//READER_TIME_QUERY,			//��д��ʱ���ѯ
	0xB2,			//READER_FLASHDATA_QUERY,		//FLASH���ݲ�ѯ
	0xB3,			//READER_FLASHDATACOUNT_QUERY //FLASH���ݱ�ǩ����ѯ
	0xB4,			//READER_FLASHCLEAR         //FLASH����
	0xC0,			//COM_GPRS_SET,				//GPRS����
	0xC1,			//COM_GPRS_QUERY,			//GPRS��ѯ
	0xC2,			//COM_WIFI_SET,				//WIFI����
	0xC3,			//COM_WIFI_QUERY,			//WIFI��ѯ
	0xC4,			//COM_WIFI_TRANS_REST		//WIFI����͸�����߸�λ
}; 

const char* mCopyright = "2.0";





