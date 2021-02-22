
#include "StdAfx.h"
#include "ENGetMsg.h"
#include "../Global.h"

CErrorStruct errorENMsg[] = 
{
	{0x0,L"Successful operation"},
	{0x10,L"The FPGA/DSPsoftware version of Reader is error"},
	{0x11,L"Reader-based version of its zone plate hardware error"},
	{0x12,L"Reader hardware board the wrong version number"},
	{0x13,L"External Sigle board hardware version error"},
	{0x14,L"Based board Self-Test Error"},
	{0x15,L"RF board Self-Test Error"},
	{0x16,L"Ethernet error"},
	{0x17,L"real-time clock error"},
	{0x18,L"External error"},
	{0x19,L"System parameters error"},
	{0x1F,L"Belonging to a system error but readers can not determine the type of error or unknown"},
	{0x20,L"Operation code Error"},
	{0x21,L"Using the wrong antenna port number"},
	{0x22,L"The Reader is In Test mode"},
	{0x23,L"Internal storage area to read and write operation failed"},
	{0x24,L"Reader is the implementation of the current labeling operation"},
	{0x25,L"The reader Run wrong (such as illegal operation run )"},
	{0x26,L"Occupancy rights to operate (there is another user to connect and use the reader )"},
	{0x2F,L"Reader can not determine the type of error or unknown"},
	{0x60,L"To receive instructions or data is incomplete"},
	{0x61,L"To receive instructions or data CRC checksum error"},
	{0x62,L"Current models of reader does not support the type of command"},
	{0x63,L"Current models of reader does not support the tag agreements"},
	{0x64,L"Command parameter error"},
	{0x65,L"Command frame structure errors (the lack of domain)"},
	{0x66,L"Reader to receive too many orders, temporarily unable to deal with"},
	{0x6F,L"Belongs to but reading and writing data can not determine the type of error or unknown"},
	{0xA0,L"Tag-free radio frequency range of response or non-Tag"},
	{0xA1,L"The command is not supported"},
	{0xA2,L"The instructions are not identifiable, such as the format error"},
	{0xA3,L"The option is not supported"},
	{0xA4,L"Tag Return:Unknown error"},
	{0xA5,L"Unable to block access to specific"},
	{0xA6,L"Tag specified block is locked and can not re-lock"},
	{0xA7,L"Tag specified block has been locked, the contents can not be changed"},
	{0xA8,L"Tag failed to implement programming block"},
	{0xA9,L"Tags the failure of the implementation of block-lock operation"},
	{0xAA,L"Operation not completed by the host computer to terminate (such as customs amplifier)"},
	{0xAB,L"Operation failed due to interference with the completion of other reasons"},
	{0xAC,L"Tag return CRC error"},
	{0xAF,L"Belong to the scope of the reader can not determine the type or unknown error"},
	{0xB0,L"Tag does not exist or no response"},
	{0xB1,L"Operation memory is not exist"},
	{0xB2,L"Tag return information: the address Tag operation overflow"},
	{0xB3,L"Tag return message: Operation locked storage area"},
	{0xB4,L"Tag access PWD is wrong"},
	{0xB5,L"Tag kill PWD is wrong"},
	{0XB6,L"Operation not completed by the host computer to terminate (such as customs amplifier)"},
	{0xB7,L"Do read / write / lock data area of the Tag uninitialized operation"},
	{0xB8,L"Reader found an uninitialized Tag"},
	{0xB9,L"Tag return message: unknown type of error"},
	{0xBA,L"Tag to return to information: lack of power"},
	{0xBF,L"ISO18000-6C Tags are operating but the reader can not determine the type of error or unknown"},
	{NO_ERR,L"Successful operation"},						//NO_ERR
	{ERR_NOT_CONNECT,L"Not Connect to Reader"},
	{ERR_READING_NOTEXE,L"Reading card,can not executing the command"},
	{ERR_COMMAND_EXEING,L"Command is executing"},
	{ERR_INVALID_SOCKET,L"Socket creation failed"},					//ERR_INVALID_SOCKET
	{ERR_CONNECT_FAIL,L"Connection failed"},							//ERR_CONNECT_FAIL
	{ERR_CONNECT_OUTTIME,L"Connection Timeout"},							//ERR_CONNECT_OUTTIME
	{ERR_CONNECT_CONNECTING,L"Connecting"},							//ERR_CONNECT_CONNECTING
	{ERR_CLOSE_FAIL,L"Close connection failed"},						//ERR_CLOSE_FAIL
	{ERR_SOCKET_ERR,L"Opt-socket Error"},					//ERR_SOCKET_ERR
	{ERR_TCPSEND_ERR,L"Send failed"},							//ERR_TCPSEND_ERR
	{ERR_FRAME_LOSE,L"Loss frame"},						//ERR_FRAME_LOSE
	{ERR_FRAME_CRC16,L"CRC16 checksum error"},				//ERR_FRAME_CRC16
	{ERR_COMHANDLE_INVALID,L"Not connected or connecting serial failure"},				//ERR_COMHANDLE_INVALID
	{ERR_COMSEND_FAIL,L"Send data to serial port failed"},				//ERR_COMSEND_FAIL
	{ERR_COMRECV_FAIL,L"Failure to collect serial data"},					//ERR_COMRECV_FAIL
	{ERR_COMRECVHEAD_FAIL,L"Serial: collection header error"},				//ERR_COMRECVHEAD_FAIL
	{ERR_COMOPEN_FAIL,L"Open the serial failure"},						//ERR_COMOPEN_FAIL
	{ERR_INITSOCKET_FAIL,L"Socket initialization failure"},					//ERR_INITSOCKET_FAIL
	{ERR_SETCOM_STATE,L"Set up com state error"},				//ERR_SETCOM_STATE,
	{ERR_SETUP_COM,L"Set up com error"},					//ERR_SETUP_COM,
	{ERR_OVERLAPREAD_NULL,L"Overlapread serial event handler is empty"},	//ERR_OVERLAPREAD_NULL,
	{ERR_OVERLLAPWRITE_NULL,L"Overlapwrite serial event handler is empty"},	//ERR_OVERLLAPWRITE_NULL
	{ERR_TCPRECV_SOCKETERROR,L"TCP receive socket data error"},          //ERR_TCPRECV_SOCKETERROR
	{ERR_TCPRECV_SOCKETOVERTIME,L"TCP timeout receiving data"},                  //ERR_TCPSEND_SOCKETOVERTIME,	
	{ERR_TCPSEND_SOCKETERROR,L"TCP to send data socket error"},			//ERR_TCPSEND_SOCKETERROR,
	{ERR_TCPSEND_SOCKETOVERTIME,L"TCP send data timeout"},					//ERR_TCPSEND_SOCKETOVERTIME,
	{ERR_UDPRECV_SOCKETERROR,L"UDP receive socket data error"},
	{ERR_UDPRECV_SOCKETOVERTIME,L"UDP timeout receiving data" },
	{ERR_MOREDATA_NEED,L"Insufficient memory allocation"},						//ERR_MOREDATA_NEED
	{ERR_POINTER_NULL,L"Input Parameters error: null pointer, does not allocate memory"},		//ERR_POINTER_NULL	
	{ERR_SIZE_ZERO,L"Out Parameters error: the introduction length 0"},					//ERR_SIZE_ZERO
	{ERR_OVER_NOSIGNED,L"Call time out, the other thread is on the reader to carry out the operation"}, //ERR_OVER_NOSIGNED
	{ERR_START_OVERFLOW,L"Start Address is greater than the length of 255"},     //ERR_START_OVERFLOW
	{ERR_LEN_OVERFLOW,L"Length of more than 255"},       //ERR_LEN_OVERFLOW
	{ERR_SIXBWRITE_OVERFLOW,L"6B write tag data, the first address of data area plus the length of data area is greater than 224 bytes"}, //ERR_SIXBWRITE_OVERFLOW
	{ERR_SIXBREAD_OVERFLOW,L"Reading the tag data 6B, the first address of data area plus the length of data area in excess of 224 bytes"}, //ERR_SIXBREAD_OVERFLOW	
	{ERR_SIXBLOGDATA_OVERFLOW,L"The first address of data area plus the length of data area in excess of 224 bytes"}, //ERR_SIXBDATA_OVERFLOW
	{ERR_GETCOM_STATE,L"GetCommState error"}, //ERR_GETCOM_STATE,//GetCommState出错
	{ERR_GETCOM_TIMEOUT,L"GetCommTimeouts error"} ,//ERR_GETCOM_TIMEOUT,//GetCommTimeouts出错
	{ERR_SETCOM_TIMEOUT,L"SetCommTimeouts error"}, //ERR_SETCOM_TIMEOUT,//SetCommTimeouts出错
	{ERR_STARTREVTHREAD_FAIL,L"Failed to start collection of letters Thread"},//ERR_STARTREVTHREAD_FAIL,//启动收信件线程失败
	{ERR_RECVTHREAD_OVERTIME,L"Receive data Time-out"},//ERR_RECVTHREAD_OVERTIME //超时未收到数据
	{ERR_DATALEN_LOZERO,L"The letter received data length is less than 0, abnormal"},
	{ERR_WRITE_EPCLEN,L"EPC code to write less than 12 bytes in length"}, //ERR_WRITE_EPCLEN
	{ERR_USB_SEND,L"USB to send data failed"}//ERR_USB_SEND
};


CENGetMsg::CENGetMsg(void)
{
	typedef pair <int,wstring> Int_Pair;

	for( int i =0 ; i< sizeof(errorENMsg)/sizeof(CErrorStruct);i++)
	{
		CErrorStruct t = errorENMsg[i];
		m_mapError.insert(Int_Pair(t.nCode,t.szMsg));
	}

}

CENGetMsg::~CENGetMsg(void)
{
}





void CENGetMsg::GetErrorMsg(int nCode,string& strError) 
{
	typedef pair <int, wstring> Int_Pair;
	map <int, wstring> :: const_iterator m1_RcIter;
	m1_RcIter = m_mapError.find( nCode );

	if ( m1_RcIter == m_mapError.end( ) )
	{
		strError ="Unknown Error";
		return;
	}

	const WCHAR *pError  = m_mapError[nCode].c_str();
	CHAR szGB2312[DATA_BUFFER] = {0};
	WideCharToMultiByte (CP_ACP, 0, pError, -1, szGB2312,DATA_BUFFER, NULL,NULL);
	strError = szGB2312;

	//strError =	m_mapError[nCode];
}


