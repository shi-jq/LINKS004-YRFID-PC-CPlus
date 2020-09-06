#include "StdAfx.h"
#include "ConnectCommon.h"
#include <comdef.h>
CConnectCommon::CConnectCommon(void)
{
	isConn = false;
	ClearPasBuffer();
	ResetFrame();
	ResetRFIDSystemCfg();
}

CConnectCommon::~CConnectCommon(void)
{
}

void CConnectCommon::LoadData(CRFIDSystemCfg& initSystemCfg)
{	
	RFIDSystemCfg = initSystemCfg;
}

bool CConnectCommon::OpenConn()
{
	return true;
}

bool CConnectCommon::CheckConnState(int maxWaitTime)
{
	return true;
}

bool CConnectCommon::SendMsg(unsigned char *pSendCommand, unsigned char *pSendData, int dataLength)
{
	return true;
}

bool CConnectCommon::RevMsg(CRFIDFrame &pRevFrame, int nWaitTime)
{
	return true;
}

bool CConnectCommon::SendNRevMsg(unsigned char *pSendCommand, unsigned char *pSendData, int dataLength, CRFIDFrame &pRevFrame,int nWaitTime)
{
	return true;
}

bool CConnectCommon::CloseConn()
{
	return true;
}

//////////////////////////////////////////////////////////////////////////
//函数名:	获取错误信息
//参数说明:	strError为返回错误信息
//返回值:	无
//////////////////////////////////////////////////////////////////////////
void CConnectCommon::GetError(string& strError)
{
	errorProc.GetErrorMsg(RFIDSystemCfg.strLanguageType,strError);
}

//////////////////////////////////////////////////////////////////////////
//函数名:	获取错误代码
//参数说明:	无
//返回值:	无
//////////////////////////////////////////////////////////////////////////
int  CConnectCommon::GetErrorCode()
{
	return errorProc.GetErrorCode();
}

//////////////////////////////////////////////////////////////////////////
//函数名:	CRC16计算值
//参数说明:	dataMsg 为计算值, crc 为已定义crc表中的数据
//返回值:	经计算的CRC16数据值
//////////////////////////////////////////////////////////////////////////
unsigned short CConnectCommon::CountCRC16( unsigned char dataMsg, unsigned short crc)
{
	return (crc << 8) ^ CRCTable [ ( crc >> 8 ) ^ dataMsg ];
}

//////////////////////////////////////////////////////////////////////////
//函数名:	数据包的CRC16计算值
//参数说明:	pMsg 数据包, msgLength 数据包长度
//返回值:	1个2字节CRC16验证数据
//////////////////////////////////////////////////////////////////////////

unsigned short CConnectCommon::CRC16 (unsigned char* pMsg, int msgLength)
{
	unsigned short CRCValue = 0;
	unsigned char *pTemp = pMsg;
	for (int tempi = 1 ;tempi < msgLength+1; ++tempi) //cxm fixed
	{
		CRCValue = CountCRC16( *(pTemp + tempi), CRCValue);
	}
	return CRCValue;
}

//////////////////////////////////////////////////////////////////////////
//函数名:	设定Frame的总线地址
//参数说明:	iframeAddr 外部出入设定的参数
//返回值:	无
//////////////////////////////////////////////////////////////////////////
void CConnectCommon::SetFrameAddr(unsigned char iframeAddr)
{
	frameAddr = iframeAddr;
}

//////////////////////////////////////////////////////////////////////////
//函数名:	设定帧优先级(分为优先帧 与 普通帧)
//参数说明:	priority 外部出入设定的参数,true表示为优先帧
//返回值:	无
//////////////////////////////////////////////////////////////////////////
void CConnectCommon::SetFramePriority(bool priority)
{
	if (priority)
		framePriority = FRAME_PRIORITY;
	else
		framePriority = 0;
}

//////////////////////////////////////////////////////////////////////////
//函数名:	设定是否为回复帧
//参数说明:	answer 外部出入设定的参数,true表示为回复帧
//返回值:	无
//////////////////////////////////////////////////////////////////////////
void CConnectCommon::SetFrameAnswer(bool answer)
{
	if(answer)
		frameAnswer = FRAME_ANSWER;
	else
		frameAnswer = 0;
}

//////////////////////////////////////////////////////////////////////////
//函数名:	设定是否为回复帧
//参数说明:	answer 外部出入设定的参数,true表示为回复帧
//返回值:	无
//////////////////////////////////////////////////////////////////////////
void CConnectCommon::ClearPasBuffer()
{
	pasLength = 0;
	memset(pasBuffer, 0 , REC_FRAME_MAXBUFF);
}

//////////////////////////////////////////////////////////////////////////
//函数名:	数据帧重置函数
//参数说明:	无
//返回值:	无
//////////////////////////////////////////////////////////////////////////
void CConnectCommon::ResetFrame()
{
	frameAddr = 0x00;
	framePriority = 0x00;
	frameAnswer = 0x00;
	frameNum = 0x00;//cxm fix
		
}
//////////////////////////////////////////////////////////////////////////
//函数名:	RFID系统配置重置函数
//参数说明:	无
//返回值:	无
//////////////////////////////////////////////////////////////////////////
void CConnectCommon::ResetRFIDSystemCfg()
{
	RFIDSystemCfg.strPortType = "COM";				//通讯模式，目前包括TCP/USB/COM
	RFIDSystemCfg.strHostName = "192.168.0.211";	//本机的IP地址，仅在网络通讯模式下有效
	RFIDSystemCfg.nSocketPort = 7086;				//网络SOCKET端口
	RFIDSystemCfg.strComNum = "COM1";				//COM1－COM4 仅在COM通讯模式下有效
	RFIDSystemCfg.nBaud = 115200;					//串口(USB口)通讯速率
	RFIDSystemCfg.nBusAddr = 0x00;					//总线地址
	RFIDSystemCfg.strUSBNum = "USB1";               //USB1-USB8  仅在USB通讯模式下有效
	RFIDSystemCfg.ucScanTimes = 2;					//每次发送读卡指令后，读出器查询标签的次数
	RFIDSystemCfg.ucRetryTimes = 4;					//没有扫描到标签，重新发送指令的次数。
	RFIDSystemCfg.ucRereadTimes = 20;				//读标签重发指令次数
	RFIDSystemCfg.ucRewriteTimes = 20;				//写标签重发指令次数
	RFIDSystemCfg.ucLeadInTotal = 4;				//连接天线总数（1－4）
	RFIDSystemCfg.ucLeadInCtrl = 3;					//天线控制方式（0：自动扫描所有天线端口,1~4仅对指定端口进行扫描）
	RFIDSystemCfg.ucSaveLog = 0;					//是否保存调试记录日志（0：不存日志，1：保存日志）
	RFIDSystemCfg.ucLogFName = ".\\SAAT_RFID.LOG";		//调试记录日志文件名
}

//////////////////////////////////////////////////////////////////////////
//函数名:	数据打包函数
//参数说明:	pSendCommand 为指令指针, pSendData 为数据指针, dataLength 为数据的长度(不包括指令长), pForSend 为返回待发送的数据
//返回值:	打包后的实际数据长度
//////////////////////////////////////////////////////////////////////////
bool CConnectCommon::PackMsg(unsigned char *pSendCommand, unsigned char *pSendData, int dataLength , unsigned char *pForSend,int *pSendLen)
{

	++frameNum ;//帧序列号自增 初始为0,每发一次+1
	if (frameNum >= 16)
	{
		frameNum = 1;// 16时变为0
	}
	//数据打包
	memset( (unsigned char *)&sendFrame, 0 , sizeof(sendFrame));		//清空发送结构包
	sendFrame.bFrame = FRAME_HEAD;					//帧头 定义为 55H
	sendFrame.bAddr = RFIDSystemCfg.nBusAddr;//cxm fixed
	sendFrame.bAddrInfo = framePriority + frameAnswer + frameNum;	//控制字节 包括:优先级, 回复帧, 回复序列号
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
		if ( pFrameData[tempi] == FRAME_HEAD)				//帧数据中出现 0x55 的情况, 用0x56 + 0x56 2个字节代替
		{
			*pBuffer++ = FRAME_HEAD_REPLACE;
			*pBuffer++ = FRAME_HEAD_REPLACE;
			++forSendLength;
		}
		else
			if ( pFrameData[tempi] == FRAME_HEAD_REPLACE)	//出现 0x56 的情况, 用0x56 + 0x57 2字节代替
			{
				*pBuffer++ = FRAME_HEAD_REPLACE;
				*pBuffer++ = FRAME_FRAME_REPLACE;
				++forSendLength;
			}
			else
				*pBuffer++ = pFrameData[tempi] ;
	}

	memcpy(pForSend, pForSendBuffer, forSendLength);
	*pSendLen = forSendLength;
#if _DEBUG
	printData("\n打包完的数据:",pForSend,forSendLength);
#endif
	return true;
}

//////////////////////////////////////////////////////////////////////////
//函数名:	数据解包函数
//参数说明:	revData 为接收到需要做解包操作的数据, revLength 为接收到数据的长度
//返回值:	true 表示返回1个完整的数据帧, 若数据有丢失,则表示返回1个空帧, false 表示返回的是1个不完整的帧,需继续等待接收数据,再做解包
//////////////////////////////////////////////////////////////////////////
//bool CConnectCommon::UnpackMsg(unsigned char * revData, int revLength)
//{
//	int nCurPasBufferLen = 0;										//当前pasBuffer中的数据长度
//	int revHead = 0;
//	int nextHead = 0;
//	unsigned char *pRevData = (unsigned char*)&revFrame;		//设定指针 指向接收的结构体
//	// 解包,当前buffer里面没有无数据
//	if ( pasLength == 0)										//不存在过去数据包
//	{
//		for ( revHead = 0; revHead < revLength; ++revHead)
//		{
//			if (revData[revHead] == FRAME_HEAD)					//检查到新接收到的数据中包含帧头, 表示有新的帧数据包被接收
//				break;
//		}
//		if(revHead != revLength) //如果在此次收包过程中找到帧头
//		{
//			memcpy(pasBuffer, revData + revHead, revLength - revHead);	//由于不存在有过去的数据包, 所以新接收到的数据在帧头前的数据			
//			nCurPasBufferLen = revLength - revHead;						//可认为垃圾数据, 不再做处理
//		}
//		else//新接收的数据包若无帧头, 可认为是垃圾数据,所以不再处理
//		{
//			memset((unsigned char*)&revFrame, 0 , sizeof(revFrame));
//			return true;
//		}															
//	}						
//	else//当前buffer里面有数据(存在过去包)
//	{
//		if ( pasLength + revLength > REC_FRAME_MAXBUFF)	//这种应不可能出现,revLength 限制一次接256个
//		{
//			memcpy(pasBuffer+pasLength, revData, REC_FRAME_MAXBUFF - pasLength);
//			nCurPasBufferLen = REC_FRAME_MAXBUFF;
//		}
//		else//应该执行下面语句,把新接收的数据存入pasBuffer
//		{
//			memcpy(pasBuffer+pasLength, revData, revLength);
//			nCurPasBufferLen = pasLength + revLength;
//		}
//	}
//
//	for (nextHead = 1; nextHead < nCurPasBufferLen; ++nextHead)			//查找pasBuffer中是否存在多个帧, 并找到第2个帧头的位置
//	{
//		if ( pasBuffer[nextHead] == FRAME_HEAD)
//			break;
//	}
//	// 数据转换 并存入 接收结构体
//	//OutputDebugString(L"data convert\n");
//	int nFixLen = 0;//cxm BugFix: 这个用来保存经常转换后实际收到的数据长度
//	/*
//	因为在收取中,0x56 0x56 会被转换成0x 5!0x56,0x57会被转换成0x56,故实际长度故为转换后长度
//	如果 要读6B卡时,读13个字节,而这些字节恰好是0x55,即(0x56,0x56),那么要收26个字节,并不是13个字节
//	*/
//	int tempj = 0;
//	for (tempj = 0; tempj < nextHead - 1; ++tempj)//例:收到一个完整数据为23时,nextHead=23,此地tempj范围[0-21],注意有对[tempj+1]的访问,数据22最后写入?
//	{
//		// 0x56 0x56转换成0x55
//		if( pasBuffer[tempj] == FRAME_HEAD_REPLACE && pasBuffer[tempj + 1] == FRAME_HEAD_REPLACE ) 
//		{
//			++tempj;
//			*pRevData ++ = FRAME_HEAD;
//		}
//		else
//		{
//			//0x56 0x57转换成0x56
//			if( pasBuffer[tempj] == FRAME_HEAD_REPLACE && pasBuffer[tempj + 1] == FRAME_FRAME_REPLACE ) 
//			{
//				++tempj;
//				*pRevData ++ = FRAME_HEAD_REPLACE;
//			}
//			else
//				*pRevData ++ = pasBuffer[tempj];
//		}
//		nFixLen ++;//cxm FixBug:循环了一次则进行了一次转换,revFrame 实际接收的长度
//	}
//	/*
//	举例如收到23个字节,pasBuffer为[0-22]
//	0 1 2 3 4 ... 21 22 23 24
//	A:如果在tempj为21时,pasBuffer[tempj]为0x55,pasBuffer[tempj+1] = pasBuffer[22] 为0x55,即么pasBuffer[22]的值已经被转换了
//		再在这里 pRevData = pasBuffer[nextHead-1] = pasBuffer[22] 不对了,pRevData已 ++ 
//	B:如果tempj为21时,pasBuffer[tempj]为0x45,pasBuffer[tempj+1]为0x08(任意数,总之不是特殊转换0,循环中tempj值未变,还是21,下一次循环前
//	值变为22,不符合条件,循环未执行,此时用*pRevData = pasBuffer[nextHead-1] = pasBuffer[22]正常 
//	*/
//	//*pRevData = pasBuffer[nextHead - 1];//cmx Buf fix:这里有问题
//	if( tempj == nextHead ) //证明最后面是0x55,0x55 或者0x55,0x56
//	{
//
//	}
//	else//如果不是
//	{
//		*pRevData = pasBuffer[tempj];
//		nFixLen++;
//	}
//
//	
//	//以上操作已将原来在pasbuffer的数据和新接收到在revData中的数据一起放入revFrame中
//
//	//OutputDebugString(L"data exit\n");
//	//对pasBuffer 和 pasLength 做处理
//	unsigned char moveBuffer[REC_FRAME_MAXBUFF];
//	if (nextHead != nCurPasBufferLen)	//刷新pasBuffer, 若存在多帧情况,则移除第1帧, 将后面的数据向前移动, 否则直接刷新pasBuffer为0;
//
//	{	
//		memcpy (moveBuffer, pasBuffer + nextHead , nCurPasBufferLen - nextHead);
//		memset(pasBuffer, 0, nCurPasBufferLen);
//		memcpy(pasBuffer, moveBuffer,  nCurPasBufferLen - nextHead);
//		pasLength = nCurPasBufferLen - nextHead;
//	}
//	else//只有1帧的情况
//	{
//		if (revFrame.bLength == 0 )	//1.当原来的revFrame中的长度域bLength还没有数据
//		{
//			//if(revLength == 0)//若再无数据作解包时,
//			//{	//直接刷新pasBuffer,即丢弃原来的数据
//			//	memset((unsigned char*)&revFrame, 0 , sizeof(revFrame));
//			//	memset(pasBuffer, 0, nCurPasBufferLen);
//			//	pasLength = 0;
//			//	return true;//返回一个空的数据帧,在调用函数检查revFrame.bFrame是否为 0 
//			//}	
//			//else														
//			{
//				pasLength = nCurPasBufferLen;//数据包还没接受完,更新此次收取后pasLenth的长度
//				return false;
//			}
//		}
//#ifdef _DEBUG
//		char szTemp[10];
//		itoa(revFrame.bLength,szTemp,10);
//		_bstr_t bstrCurPassBufferLen = szTemp;
//		OutputDebugString(L"要收取的数据长度:");
//		OutputDebugString(bstrCurPassBufferLen);
//		OutputDebugString(L"\n");
//
//		itoa(nFixLen- FRAME_WITHOUTBLENGTH,szTemp,10);
//		bstrCurPassBufferLen = szTemp;
//		OutputDebugString(L"已收取的实际数据长度:");
//		OutputDebugString(bstrCurPassBufferLen);
//		OutputDebugString(L"\n");
//		
//#endif
//	//	if (revFrame.bLength != 0 && revFrame.bLength > nCurPasBufferLen - FRAME_WITHOUTBLENGTH) //帧头为 1字节, 控制域为 3字节, CRC16为 2字节 6 = 1+3+2
//		if (revFrame.bLength != 0 && revFrame.bLength > nFixLen - FRAME_WITHOUTBLENGTH) //cxm FixBug
//		{																//2.在pasBuffer中的数据不满足1个包的情况下
//			//if (revLength == 0)											//若再无数据作解包时,
//			//{															//直接刷新pasBuffer,即丢弃原来的数据
//			//	memset((unsigned char*)&revFrame, 0 , sizeof(revFrame));
//			//	memset(pasBuffer, 0, nCurPasBufferLen);
//			//	pasLength = 0;
//			//	return true;											//返回一个空的数据帧,在调用函数检查revFrame.bFrame是否为 0 
//			//}															//,确认是否为 空帧 ,
//			//else														//数据包还没接受完
//			{
//				pasLength = nCurPasBufferLen;//数据包还没接受完,更新此次收取后pasLenth的长度
//				return false;
//			}
//		}
//		else//3.正好接收完1个数据包
//		{
//			memset(&revFrame.bCommand + revFrame.bLength + 2, 0, DATA_BUFFER - revFrame.bLength - 2);	//清除有效信息长度之后的垃圾信息
//			memset(pasBuffer, 0, nCurPasBufferLen);
//			pasLength = 0;//把这个置于0,因为 这里只有一帧(看if条件),已经收完了 
//		}
//
//	}
//#if _DEBUG
//	LPBYTE pTest = (LPBYTE)&revFrame;
//	printData("CRC验证前数据:",pTest,revFrame.bLength +FRAME_WITHOUTBLENGTH);
//#endif
//	//经过以上处理,当前得到的revFrame是一个完整的包
//	//CRC16校验
//	unsigned short CRCValue = 0;					//CRC校验算法, 保存在帧尾2字节
//	CRCValue = CRC16( (unsigned char*)(&revFrame), revFrame.bLength + 5);//帧头不要
//	if(CRCValue != 0 )	//错误的时候返回为1个空帧
//	{
//		memset((unsigned char*)&revFrame, 0 , sizeof(CRFIDFrame));
//	}
//	return true;
//}


//////////////////////////////////////////////////////////////////////////
//函数名:	数据解包函数
//参数说明:	revData 为接收到需要做解包操作的数据, revLength 为接收到数据的长度
//返回值:	true 表示返回1个完整的数据帧, 若数据有丢失,则表示返回1个空帧, false 表示返回的是1个不完整的帧,需继续等待接收数据,再做解包
//////////////////////////////////////////////////////////////////////////
bool CConnectCommon::UnpackMsg(unsigned char * revData, int revLength)
{	
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
			return true;
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
		memset((unsigned char*)&revFrame, 0 , sizeof(CRFIDFrame));

	return true;
}