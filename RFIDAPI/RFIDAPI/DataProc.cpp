#include "StdAfx.h"
#include "DataProc.h"
#include "COMConn.h"
#include "USBConn.h"
#include "TCPConn.h"
#include "UDPConn.h"


CDataProc::CDataProc()
{
	m_pConnect = NULL;
	pReader = NULL;
	m_frameNum = 0;
	m_framePriority = 0;
	m_frameAnswer = 0;
	m_pasLength = 0;
	m_Open = false;
}

CDataProc::~CDataProc(void)
{
	Close();

	if( NULL != m_pConnect   )
	{
		m_pConnect->CloseConn();
		delete m_pConnect;
		m_pConnect = NULL;
	}
}


void CDataProc::SetErrorCode(int nErrorCode,bool bCommandError )
{
	if( NULL != pReader)
	{
		pReader->SetErrorCode(nErrorCode);
	}
}

void CDataProc::InitDataPorc(IReader* ReaderInterface) 
{
	if( NULL == pReader)
	{
		pReader = ReaderInterface;
	}
}



//////////////////////////////////////////////////////////////////////////
//函数名:	CRC16计算值
//参数说明:	dataMsg 为计算值, crc 为已定义crc表中的数据
//返回值:	经计算的CRC16数据值
//////////////////////////////////////////////////////////////////////////
unsigned short CDataProc::CountCRC16( unsigned char dataMsg, unsigned short crc)
{
	return (crc << 8) ^ CRCTable [ ( crc >> 8 ) ^ dataMsg ];
}


//////////////////////////////////////////////////////////////////////////
//函数名:	数据包的CRC16计算值
//参数说明:	pMsg 数据包, msgLength 数据包长度
//返回值:	1个2字节CRC16验证数据
//////////////////////////////////////////////////////////////////////////

unsigned short CDataProc::CRC16 (unsigned char* pMsg, int msgLength)
{
	unsigned short CRCValue = 0xffff;
	unsigned char *pTemp = pMsg;
	for (int tempi = 1 ;tempi < msgLength+1; ++tempi) //cxm fixed
	{
		CRCValue = CountCRC16( *(pTemp + tempi), CRCValue);
	}
	return CRCValue;
}


bool CDataProc::PackMsg(unsigned char *pSendCommand, 
						unsigned char *pSendData,
						int dataLength,
						CRFIDFrame &pRevFrame,
						unsigned char *pForSend,
						int *pSendLen)
{
	if( !m_Open )
	{
		return false;
	}

	

	CRFrame &sendFrame = pRevFrame.RFIDInFrame;

	//数据打包
	memset( (unsigned char *)&sendFrame, 0 , sizeof(sendFrame));		//清空发送结构包
	sendFrame.bFrame = FRAME_HEAD;					//帧头 定义为 AA   jxd修改
	sendFrame.bAddr = m_RFIDSystemCfg.nBusAddr;//cxm fixed
	sendFrame.bAddrInfo = m_framePriority + m_frameAnswer + m_frameNum;	//控制字节 包括:优先级, 回复帧, 回复序列号
	sendFrame.bLength = dataLength + 1;				//长度域为 数据长度 + 指令(1字节)
	sendFrame.bCommand = *pSendCommand;				//操作指令
	memcpy(sendFrame.bData, pSendData, dataLength);

	unsigned short CRCValue = 0;					//CRC校验算法, 保存在帧尾2字节
	CRCValue = CRC16( (unsigned char*)&sendFrame, dataLength + 4);//帧头不要,控制域为3
	sendFrame.bData[dataLength] = (char)((CRCValue >> 8) & 0xff);
	sendFrame.bData[dataLength + 1] = (char)(CRCValue & 0xff);

	//帧数据转换
	unsigned char pForSendBuffer[SENDFRAME_MAXBUF];
	unsigned char *pBuffer = pForSendBuffer + 1;			//不包括帧头
	unsigned char *pFrameData = (unsigned char*)&sendFrame;
	int forSendLength = dataLength + 7;						//帧头为 1字节, 控制域为 3字节, 指令为 1字节, CRC16为 2字节  7 = 1+3+1+2;

	pForSendBuffer[0] = FRAME_HEAD;
	for (int tempi = 1 ; tempi < dataLength + 7; ++tempi)
	{
		if ( pFrameData[tempi] == FRAME_HEAD)				//帧数据中出现 0xAA 的情况, 用0xAB + 0xAB 2个字节代替
		{
			*pBuffer++ = FRAME_HEAD_REPLACE;
			*pBuffer++ = FRAME_HEAD_REPLACE;
			++forSendLength;
		}
		else
		{
			if ( pFrameData[tempi] == FRAME_HEAD_REPLACE)	//出现 0xAB 的情况, 用0xAB + 0xAC 2字节代替
			{
				*pBuffer++ = FRAME_HEAD_REPLACE;
				*pBuffer++ = FRAME_FRAME_REPLACE;
				++forSendLength;
			}
			else
			{
				*pBuffer++ = pFrameData[tempi] ;
			}
		}
	}

	memcpy(pForSend, pForSendBuffer, forSendLength);
	*pSendLen = forSendLength;

	++m_frameNum;//帧序列号自增 初始为0,每发一次+1
	if (m_frameNum >= 16)
	{
		m_frameNum = 0;// 16时变为0
	}

	return true;
}

bool CDataProc::Reconect()
{
	m_pConnect->CloseConn();
	return m_pConnect->OpenConn();
}

bool CDataProc::Open(CRFIDSystemCfg& cfg)
{
	if( m_Open )
	{
		return true;
	}

	ConcreteConn(cfg);
	m_pConnect->LoadData(cfg);

	if( ! m_pConnect->OpenConn() ) //先打开连接
	{
		return false;
	}

	memcpy((void*)&m_RFIDSystemCfg,(void*)&cfg,sizeof(m_RFIDSystemCfg));


	m_pConnect->InitConnect(this);//初始化连接指针

	m_Open = true;

	return true;
}


bool CDataProc::TestHeart() 
{
	if( !m_Open )
	{
		return false;
	}

	pReader->TestHeart();
	return true;
}


bool CDataProc::ClosePort()
{
	if( !m_Open ) //未打开
	{
		return true;
	}

	return m_pConnect->ClosePort();
}


bool CDataProc::Close()
{
	if( !m_pConnect->CloseConn() )
	{
		return false;
	}

	m_Open = false;
	return true;
}



IConnect* CDataProc::ConcreteConn(CRFIDSystemCfg& cfg)
{
	switch (cfg.nPortType)
	{
	case TCP_PORT:
		return ( m_pConnect = new CTCPConn );
		break;
	case COM_PORT:
		return ( m_pConnect = new CCOMConn );
		break;
	case USB_PORT:
		return ( m_pConnect =new CUSBConn );
	case UDP_PORT:
		return ( m_pConnect =new CUDPConn );
		break;
	default:
		break;
	}
	return NULL;
}


bool CDataProc::SendMsg(unsigned char *pSendCommand, unsigned char *pSendData, int dataLength, CRFIDFrame &pRevFrame)
{
	
	if( !m_Open ) //未打开
	{
		return false;
	}

	if( !m_pConnect->SendMsg(pSendData,dataLength) )
	{
		return false;
	}

	return true;


}

bool CDataProc::SendRawData(unsigned char* szData,int nLen)
{
	if( !m_Open ) //未打开
	{
		return false;
	}
	m_pConnect->CloseThread();
	return m_pConnect->SendMsg(szData,nLen);
}

bool CDataProc::RevRawData(unsigned char* szData,unsigned char* pLen, int nWaitTime)
{
	if( !m_Open ) //未打开
	{
		return false;
	}
	if( 0 == nWaitTime)
	{
		nWaitTime +=3000;
	}
	m_pConnect->CloseThread();
	return m_pConnect->RevMsg(szData, pLen, nWaitTime);
}
bool CDataProc::UnPackMsg(unsigned char* revData,int revLength)
{
	if( !m_Open ) //未打开
	{
		return false;
	}

	int &pasLength = m_pasLength; //使用引用,不改变原先代码
	CRFrame &revFrame = m_revFrame;
	unsigned char *pasBuffer = m_pasBuffer;

	if (revLength + pasLength == 0 )
		return false;

	int nCurPasBufferLen = 0;							//当前pasBuffer中的数据长度
	int revHead = 0;
	int nextHead = 0;

	//1.更新当前要解包的数据缓冲区，将新收到数据放入存储缓冲区中
	//----------------------------------------------------------------------------------------------------------------------------
	if (pasLength == 0)	//不存在过去数据包
	{
		for ( revHead = 0; revHead < revLength; ++revHead)
		{
			if (revData[revHead] == FRAME_HEAD)			//检查到新接收到的数据中包含帧头, 表示有新的帧数据包被接收
				break;
		}

		if(revHead != revLength) //如果在此次收包过程中找到帧头
		{
			memcpy(pasBuffer, revData + revHead, revLength - revHead);//将新接收到的数据且已识别为帧头后的数据拷贝到当前存储缓冲区			
			nCurPasBufferLen = revLength - revHead;			//更新当前存储缓冲区长度
		}
		else//新接收的数据包若无帧头，认为是垃圾数据，丢弃不处理
		{
			memset((unsigned char*)&revFrame, 0 , sizeof(revFrame));
			return false;
		}
	}																
	else//当前buffer里面有数据(存在过去包)
	{
		if ( pasLength + revLength > REC_FRAME_MAXBUFF)	//当前缓冲区不够大时，丢弃多余数据
		{//冲掉所有数据，重新接收
			for ( revHead = 0; revHead < revLength; ++revHead)
			{
				if (revData[revHead] == FRAME_HEAD)
					break;
			}
			if(revHead != revLength)
			{
				memset(pasBuffer,0,REC_FRAME_MAXBUFF);
				pasLength = 0;
				memcpy(pasBuffer, revData + revHead, revLength - revHead);		
				nCurPasBufferLen = revLength - revHead;
			}
			/*memcpy(pasBuffer+pasLength, revData, REC_FRAME_MAXBUFF - pasLength);
			nCurPasBufferLen = REC_FRAME_MAXBUFF;*/
		}
		else//应该执行下面语句,把新接收的数据存入pasBuffer
		{
			memcpy(pasBuffer+pasLength, revData, revLength);
			nCurPasBufferLen = pasLength + revLength;
		}
	}

	/*char dbgbuffer[64];
	sprintf(dbgbuffer, "单次收到数据：%d字节，\t当前存储缓冲区中共有数据：%d字节\n", revLength, nCurPasBufferLen);
	OutputDebugString((_bstr_t)dbgbuffer);*/

	//2.查找pasBuffer中是否存在多个帧, 并找到第2个帧头的位置，目的是如果没有找到第二帧帧头，说明存储缓冲区中可能只有一帧，或者一帧都不全
	//----------------------------------------------------------------------------------------------------------------------------
	for (nextHead = 1; nextHead < nCurPasBufferLen; ++nextHead)			
	{
		if ( pasBuffer[nextHead] == FRAME_HEAD)
			break;
	}

	//3.解析数据 并将处理后数据存入接收结构体，将原来在pasbuffer的数据和新接收到在revData中的数据一起放入revFrame中
	//----------------------------------------------------------------------------------------------------------------------------
	//cxm BugFix: 这个用来保存经常转换后实际收到的数据长度
	//因为在收取中:
	//0x56 0x56会被转换成0x55
	//0x56 0x57会被转换成0x56，故实际长度故为转换后长度
	//如果 要读6B卡时,读13个字节,而这些字节恰好是0x55,即(0x56,0x56),那么要收26个字节,并不是13个字节
	//
	int nFixLen = 0;

	unsigned char *pRevData = (unsigned char*)&revFrame;//设定指针 指向接收的结构体
	int tempj = 0;
	//例:收到一个完整数据为23时,nextHead=23,此地tempj范围[0-21],注意有对[tempj+1]的访问,数据22最后写入?

	// 转换数据 并将处理后数据存入接收结构体
	for (tempj = 0; tempj < nextHead - 1; ++tempj)
	{
		// 0x56 0x56转换成0x55
		if( pasBuffer[tempj] == FRAME_HEAD_REPLACE && pasBuffer[tempj + 1] == FRAME_HEAD_REPLACE ) 
		{
			++tempj;
			*pRevData ++ = FRAME_HEAD;
		}
		//0x56 0x57转换成0x56
		else if( pasBuffer[tempj] == FRAME_HEAD_REPLACE && pasBuffer[tempj + 1] == FRAME_FRAME_REPLACE ) 
		{
			++tempj;
			*pRevData ++ = FRAME_HEAD_REPLACE;
		}			
		else
			*pRevData ++ = pasBuffer[tempj];

		nFixLen ++;//cxm FixBug:循环了一次则进行了一次转换,revFrame 实际接收的长度
	}
	/*
	举例如收到23个字节，pasBuffer为[0-22]
	0 1 2 3 4 ... 21 22 23 24
	A:如果在tempj为21时,pasBuffer[tempj]为0x55,pasBuffer[tempj+1] = pasBuffer[22] 为0x55,即么pasBuffer[22]的值已经被转换了
	再在这里 pRevData = pasBuffer[nextHead-1] = pasBuffer[22] 不对了,pRevData已 ++ 
	B:如果tempj为21时,pasBuffer[tempj]为0x45,pasBuffer[tempj+1]为0x08(任意数,总之不是特殊转换0,循环中tempj值未变,还是21,下一次循环前
	值变为22,不符合条件,循环未执行,此时用*pRevData = pasBuffer[nextHead-1] = pasBuffer[22]正常 
	*/
	//*pRevData = pasBuffer[nextHead - 1];//cmx Buf fix:这里有问题
	if( tempj != nextHead ) //证明最后面不是0x55,0x55 或者0x55,0x56
	{
		*pRevData = pasBuffer[tempj];
		nFixLen++;
	}

	//4.整理数据缓冲区中其它数据，若存在多帧情况,则移除第1帧, 将后面的数据向前移动, 否则直接刷新pasBuffer为0
	//----------------------------------------------------------------------------------------------------------------------------
	unsigned char moveBuffer[REC_FRAME_MAXBUFF];
	if (nextHead != nCurPasBufferLen)	
	{	
		pasLength = nCurPasBufferLen - nextHead;
		memcpy (moveBuffer, pasBuffer + nextHead , pasLength);
		memset(pasBuffer, 0, nCurPasBufferLen);
		memcpy(pasBuffer, moveBuffer,  pasLength);
	}
	else//只有1帧的情况
	{
		if (revFrame.bLength == 0 )	//原来的revFrame中的长度域bLength还没有数据
		{
			pasLength = nCurPasBufferLen;//数据包还没接受完,更新此次收取后pasLenth的长度
			return false;
		}

		if (revFrame.bLength != 0 && revFrame.bLength > nFixLen - FRAME_WITHOUTBLENGTH) //cxm FixBug
		{	
			pasLength = nCurPasBufferLen;//数据包还没接受完,更新此次收取后pasLenth的长度
			return false;
		}
		else//3.正好接收完1个数据包
		{
			memset(&revFrame.bCommand + revFrame.bLength + 2, 0, DATA_BUFFER - revFrame.bLength - 2);	//清除有效信息长度之后的垃圾信息
			memset(pasBuffer, 0, nCurPasBufferLen);
			pasLength = 0;//把这个置于0,因为 这里只有一帧(看if条件),已经收完了 
		}
	}

	//5.经过以上处理,当前得到的revFrame是一个完整的包，校验接收数据帧中数据
	//----------------------------------------------------------------------------------------------------------------------------
	if( CRC16( (unsigned char*)(&revFrame), revFrame.bLength + 5) != 0 )	//错误的时候返回为1个空帧
	{
		memset((unsigned char*)&revFrame, 0 , sizeof(CRFIDFrame));
		return false;
	}


	//printData("接收到数据",(unsigned char*)&revFrame,revFrame.bLength + 5);
	return true;
}



bool CDataProc::MsgProcess(unsigned char* revData,int revLength)
{
	
	if( !m_Open ) //未打开
	{
		return false;
	}

	if( UnPackMsg(revData,revLength) )
	{
		if( pReader != NULL )
		{
			/*OutputDebugString(L"接收到数据:");
			char szPara[MAX_PATH];
			sprintf(szPara,"%02x ",m_revFrame.bCommand);
			OutputDebugString(L"\r\n");
			_bstr_t strPara = szPara;
			OutputDebugString(strPara);*/
			pReader->SetMsgResult(m_revFrame);
		}
	}
	

	return true;
}