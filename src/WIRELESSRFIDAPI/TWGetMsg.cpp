#include "StdAfx.h"
#include "TWGetMsg.h"

#include "Global.h"

CErrorStruct errorTWMsg[] = 
{
	{0x0,L"操作成功"},
	{0x10,L"讀寫設備解碼單元的軟體版本錯誤"},
	{0x11,L"讀寫設備基帶單板硬體版本號錯誤"},
	{0x12,L"讀寫設備射頻單板硬體版本號錯誤"},
	{0x13,L"讀寫設備擴展單板硬體版本號錯誤"},
	{0x14,L"讀寫設備基帶板啟動自檢失敗"},
	{0x15,L"讀寫設備射頻板啟動自檢失敗"},
	{0x16,L"讀寫設備乙太網啟動自檢失敗"},
	{0x17,L"讀寫設備即時時鐘啟動自檢失敗"},
	{0x18,L"讀寫設備外部記憶體啟動自檢失敗"},
	{0x19,L"讀寫設備系統參數表自檢錯誤"},
	{0x1F,L"未知類型的系統硬體錯誤"},
	{0x20,L"讀寫設備操作許可權密碼錯誤"},
	{0x21,L"使用了禁止或錯誤的天線埠號"},
	{0x22,L"當前讀寫設備處於測試模式"},
	{0x23,L"操作讀寫設備內部存儲設備失敗"},
	{0x24,L"當前讀寫設備正執行不可中斷操作"},
	{0x25,L"讀寫設備運行錯誤，如程式運行出現非法操作"},
	{0x26,L"操作許可權佔用（已有另一高級用戶已經連接）"},
	{0x2F,L"未知類型的讀寫設備操作錯誤"},
	{0x60,L"接收的指令或資料的幀結構不完整"},
	{0x61,L"接收的指令或資料的CRC校驗錯誤"},
	{0x62,L"當前型號讀寫設備不支援該指令類型"},
	{0x63,L"當前型號讀寫設備不支援該標籤協定"},
	{0x64,L"接收的指令中參數有錯誤"},
	{0x65,L"指令幀結構錯誤（缺少域或域結構錯誤）"},
	{0x66,L"讀寫設備接收到太多指令，暫時無法處理"},
	{0x6F,L"未知類型的資料傳輸類型錯誤"},
	{0xA0,L"標籤無響應或射頻範圍內無標籤"},
	{0xA1,L"該指令操作標籤不支援"},
	{0xA2,L"該指令未被標籤識別，如位址錯誤"},
	{0xA3,L"該選項不支援"},
	{0xA4,L"標籤返回的未知錯誤碼"},
	{0xA5,L"標籤無法存取特定的塊"},
	{0xA6,L"標籤指定位元組已經鎖定，無法再次鎖定"},
	{0xA7,L"標籤指定位元組已經鎖定，內容無法改寫"},
	{0xA8,L"標籤執行位元組資料寫入操作失敗"},
	{0xA9,L"標籤執行位元組鎖定操作失敗"},
	{0xAA,L"標籤操作未完成，被上位機終止（如關載波）"},
	{0xAB,L"標籤操作因干擾等原因未能全部完成"},
	{0xAC,L"標籤返回CRC錯誤"},
	{0xAF,L"未知類型的ISO18000-6B標籤操作錯誤"},
	{0xB0,L"標籤無響應或射頻範圍內不存在標籤"},
	{0xB1,L"要操作的標籤存儲區（Bank）不存在"},
	{0xB2,L"標籤返回資訊：標籤操作位址溢出"},
	{0xB3,L"標籤返回資訊：操作存儲區被鎖定"},
	{0xB4,L"標籤存取密碼錯誤"},
	{0xB5,L"標籤滅活密碼錯誤"},
	{0XB6,L"操作未完成，被上位機終止（如關載波）"},
	{0xB7,L"要做讀/寫/鎖資料區操作的標籤未初始化"},
	{0xB8,L"讀卡操作時發現未初始化標籤。"},
	{0xB9,L"標籤返回資訊：未知類型錯誤"},
	{0xBA,L"標籤返回資訊：功率不足"},
	{0xBF,L"未知類型的ISO18000-6C標籤操作錯誤"},
	{NO_ERR,L"操作成功"},						//NO_ERR
	{ERR_INVALID_SOCKET,L"Socket創建失敗"},					//ERR_INVALID_SOCKET
	{ERR_CONNECT_FAIL,L"連接失敗"},							//ERR_CONNECT_FAIL
	{ERR_CONNECT_OUTTIME,L"連接超時"},							//ERR_CONNECT_OUTTIME
	{ERR_CONNECT_CONNECTING,L"正在連接"},							//ERR_CONNECT_CONNECTING
	{ERR_CLOSE_FAIL,L"關閉連接失敗"},						//ERR_CLOSE_FAIL
	{ERR_SOCKET_ERR,L"選擇socket時出錯"},					//ERR_SOCKET_ERR
	{ERR_TCPSEND_ERR,L"發送失敗"},							//ERR_TCPSEND_ERR
	{ERR_FRAME_LOSE,L"資料幀丟失"},						//ERR_FRAME_LOSE
	{ERR_FRAME_CRC16,L"資料幀CRC16校驗出錯"},				//ERR_FRAME_CRC16
	{ERR_COMHANDLE_INVALID,L"串口未連接或連接失效"},				//ERR_COMHANDLE_INVALID
	{ERR_COMSEND_FAIL,L"發送資料到串口失敗"},				//ERR_COMSEND_FAIL
	{ERR_COMRECV_FAIL,L"收取串口數據失敗"},					//ERR_COMRECV_FAIL
	{ERR_COMRECVHEAD_FAIL,L"串口：收取幀頭錯誤"},				//ERR_COMRECVHEAD_FAIL
	{ERR_COMOPEN_FAIL,L"打開串口失敗"},						//ERR_COMOPEN_FAIL
	{ERR_INITSOCKET_FAIL,L"初始化套接字失敗"},					//ERR_INITSOCKET_FAIL
	{ERR_SETCOM_STATE,L"Set up com state出錯"},				//ERR_SETCOM_STATE,
	{ERR_SETUP_COM,L"Set up com 出錯"},					//ERR_SETUP_COM,
	{ERR_OVERLAPREAD_NULL,L"串口overlapread 事件控制碼為空"},	//ERR_OVERLAPREAD_NULL,
	{ERR_OVERLLAPWRITE_NULL,L"串口overlapwrite 事件控制碼為空"},	//ERR_OVERLLAPWRITE_NULL
	{ERR_TCPRECV_SOCKETERROR,L"TCP接收資料時socket出錯"},          //ERR_TCPRECV_SOCKETERROR
	{ERR_TCPRECV_SOCKETOVERTIME,L"TCP接收資料超時"},                  //ERR_TCPSEND_SOCKETOVERTIME,	
	{ERR_TCPSEND_SOCKETERROR,L"TCP發送資料時socket出錯"},			//ERR_TCPSEND_SOCKETERROR,
	{ERR_TCPSEND_SOCKETOVERTIME,L"TCP發送資料超時"},					//ERR_TCPSEND_SOCKETOVERTIME,
	{ERR_MOREDATA_NEED,L"記憶體分配不足"},						//ERR_MOREDATA_NEED
	{ERR_POINTER_NULL,L"入參錯誤:空指標,未分配記憶體"},		//ERR_POINTER_NULL	
	{ERR_SIZE_ZERO,L"入參錯誤:傳入長度為"},					//ERR_SIZE_ZERO
	{ERR_OVER_NOSIGNED,L"調用超時,其他線程正在對讀寫器進行操作"}, //ERR_OVER_NOSIGNED
	{ERR_START_OVERFLOW,L"起始位址長度大於"},     //ERR_START_OVERFLOW
	{ERR_LEN_OVERFLOW,L"長度大於"},       //ERR_LEN_OVERFLOW
	{ERR_SIXBWRITE_OVERFLOW,L"寫B標籤資料時,資料區首位址加數據區長度大於位元組"}, //ERR_SIXBWRITE_OVERFLOW
	{ERR_SIXBREAD_OVERFLOW,L"讀B標籤資料時,資料區首位址加數據區長度超出位元組"}, //ERR_SIXBREAD_OVERFLOW	
	{ERR_SIXBLOGDATA_OVERFLOW,L"鎖B標籤資料時,資料區首位址加數據區長度超出位元組"}, //ERR_SIXBDATA_OVERFLOW
	{ERR_GETCOM_STATE,L"GetCommState出錯"}, //ERR_GETCOM_STATE,//GetCommState出錯
	{ERR_GETCOM_TIMEOUT,L"GetCommTimeouts出錯"} ,//ERR_GETCOM_TIMEOUT,//GetCommTimeouts出錯
	{ERR_SETCOM_TIMEOUT,L"SetCommTimeouts出錯"}, //ERR_SETCOM_TIMEOUT,//SetCommTimeouts出錯
	{ERR_STARTREVTHREAD_FAIL,L"啟動收信件線程失敗"},//ERR_STARTREVTHREAD_FAIL,//啟動收信件線程失敗
	{ERR_RECVTHREAD_OVERTIME,L"超時未收到資料"},//ERR_RECVTHREAD_OVERTIME //超時未收到資料
	{ERR_DATALEN_LOZERO,L"收到的信件資料區長度小於,異常"},
	{ERR_WRITE_EPCLEN,L"寫EPC碼長度不足位元組"}, //ERR_WRITE_EPCLEN
	{ERR_USB_SEND,L"USB發送資料失敗"}//ERR_USB_SEND
};


CTWGetMsg::CTWGetMsg(void)
{
	typedef pair <int,wstring> Int_Pair;

	for( int i =0 ; i< sizeof(errorTWMsg)/sizeof(CErrorStruct);i++)
	{
		CErrorStruct t = errorTWMsg[i];
		m_mapError.insert(Int_Pair(t.nCode,t.szMsg));
	}

}

CTWGetMsg::~CTWGetMsg(void)
{
}





void CTWGetMsg::GetErrorMsg(int nCode,string& strError) 
{
	typedef pair <int, wstring> Int_Pair;
	map <int, wstring> :: const_iterator m1_RcIter;
	m1_RcIter = m_mapError.find( nCode );

	if ( m1_RcIter == m_mapError.end( ) )
	{
		strError ="未知錯誤";
		return;
	}

	const WCHAR *pError  = m_mapError[nCode].c_str();
	CHAR szGB2312[DATA_BUFFER] = {0};
	WideCharToMultiByte (CP_ACP, 0, pError, -1, szGB2312,DATA_BUFFER, NULL,NULL);
	strError = szGB2312;
	//strError =	m_mapError[nCode];
}



