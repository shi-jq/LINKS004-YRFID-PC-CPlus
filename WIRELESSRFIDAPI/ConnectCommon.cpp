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
//������:	��ȡ������Ϣ
//����˵��:	strErrorΪ���ش�����Ϣ
//����ֵ:	��
//////////////////////////////////////////////////////////////////////////
void CConnectCommon::GetError(string& strError)
{
	errorProc.GetErrorMsg(RFIDSystemCfg.strLanguageType,strError);
}

//////////////////////////////////////////////////////////////////////////
//������:	��ȡ�������
//����˵��:	��
//����ֵ:	��
//////////////////////////////////////////////////////////////////////////
int  CConnectCommon::GetErrorCode()
{
	return errorProc.GetErrorCode();
}

//////////////////////////////////////////////////////////////////////////
//������:	CRC16����ֵ
//����˵��:	dataMsg Ϊ����ֵ, crc Ϊ�Ѷ���crc���е�����
//����ֵ:	�������CRC16����ֵ
//////////////////////////////////////////////////////////////////////////
unsigned short CConnectCommon::CountCRC16( unsigned char dataMsg, unsigned short crc)
{
	return (crc << 8) ^ CRCTable [ ( crc >> 8 ) ^ dataMsg ];
}

//////////////////////////////////////////////////////////////////////////
//������:	���ݰ���CRC16����ֵ
//����˵��:	pMsg ���ݰ�, msgLength ���ݰ�����
//����ֵ:	1��2�ֽ�CRC16��֤����
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
//������:	�趨Frame�����ߵ�ַ
//����˵��:	iframeAddr �ⲿ�����趨�Ĳ���
//����ֵ:	��
//////////////////////////////////////////////////////////////////////////
void CConnectCommon::SetFrameAddr(unsigned char iframeAddr)
{
	frameAddr = iframeAddr;
}

//////////////////////////////////////////////////////////////////////////
//������:	�趨֡���ȼ�(��Ϊ����֡ �� ��ͨ֡)
//����˵��:	priority �ⲿ�����趨�Ĳ���,true��ʾΪ����֡
//����ֵ:	��
//////////////////////////////////////////////////////////////////////////
void CConnectCommon::SetFramePriority(bool priority)
{
	if (priority)
		framePriority = FRAME_PRIORITY;
	else
		framePriority = 0;
}

//////////////////////////////////////////////////////////////////////////
//������:	�趨�Ƿ�Ϊ�ظ�֡
//����˵��:	answer �ⲿ�����趨�Ĳ���,true��ʾΪ�ظ�֡
//����ֵ:	��
//////////////////////////////////////////////////////////////////////////
void CConnectCommon::SetFrameAnswer(bool answer)
{
	if(answer)
		frameAnswer = FRAME_ANSWER;
	else
		frameAnswer = 0;
}

//////////////////////////////////////////////////////////////////////////
//������:	�趨�Ƿ�Ϊ�ظ�֡
//����˵��:	answer �ⲿ�����趨�Ĳ���,true��ʾΪ�ظ�֡
//����ֵ:	��
//////////////////////////////////////////////////////////////////////////
void CConnectCommon::ClearPasBuffer()
{
	pasLength = 0;
	memset(pasBuffer, 0 , REC_FRAME_MAXBUFF);
}

//////////////////////////////////////////////////////////////////////////
//������:	����֡���ú���
//����˵��:	��
//����ֵ:	��
//////////////////////////////////////////////////////////////////////////
void CConnectCommon::ResetFrame()
{
	frameAddr = 0x00;
	framePriority = 0x00;
	frameAnswer = 0x00;
	frameNum = 0x00;//cxm fix
		
}
//////////////////////////////////////////////////////////////////////////
//������:	RFIDϵͳ�������ú���
//����˵��:	��
//����ֵ:	��
//////////////////////////////////////////////////////////////////////////
void CConnectCommon::ResetRFIDSystemCfg()
{
	RFIDSystemCfg.strPortType = "COM";				//ͨѶģʽ��Ŀǰ����TCP/USB/COM
	RFIDSystemCfg.strHostName = "192.168.0.211";	//������IP��ַ����������ͨѶģʽ����Ч
	RFIDSystemCfg.nSocketPort = 7086;				//����SOCKET�˿�
	RFIDSystemCfg.strComNum = "COM1";				//COM1��COM4 ����COMͨѶģʽ����Ч
	RFIDSystemCfg.nBaud = 115200;					//����(USB��)ͨѶ����
	RFIDSystemCfg.nBusAddr = 0x00;					//���ߵ�ַ
	RFIDSystemCfg.strUSBNum = "USB1";               //USB1-USB8  ����USBͨѶģʽ����Ч
	RFIDSystemCfg.ucScanTimes = 2;					//ÿ�η��Ͷ���ָ��󣬶�������ѯ��ǩ�Ĵ���
	RFIDSystemCfg.ucRetryTimes = 4;					//û��ɨ�赽��ǩ�����·���ָ��Ĵ�����
	RFIDSystemCfg.ucRereadTimes = 20;				//����ǩ�ط�ָ�����
	RFIDSystemCfg.ucRewriteTimes = 20;				//д��ǩ�ط�ָ�����
	RFIDSystemCfg.ucLeadInTotal = 4;				//��������������1��4��
	RFIDSystemCfg.ucLeadInCtrl = 3;					//���߿��Ʒ�ʽ��0���Զ�ɨ���������߶˿�,1~4����ָ���˿ڽ���ɨ�裩
	RFIDSystemCfg.ucSaveLog = 0;					//�Ƿ񱣴���Լ�¼��־��0��������־��1��������־��
	RFIDSystemCfg.ucLogFName = ".\\SAAT_RFID.LOG";		//���Լ�¼��־�ļ���
}

//////////////////////////////////////////////////////////////////////////
//������:	���ݴ������
//����˵��:	pSendCommand Ϊָ��ָ��, pSendData Ϊ����ָ��, dataLength Ϊ���ݵĳ���(������ָ�), pForSend Ϊ���ش����͵�����
//����ֵ:	������ʵ�����ݳ���
//////////////////////////////////////////////////////////////////////////
bool CConnectCommon::PackMsg(unsigned char *pSendCommand, unsigned char *pSendData, int dataLength , unsigned char *pForSend,int *pSendLen)
{

	++frameNum ;//֡���к����� ��ʼΪ0,ÿ��һ��+1
	if (frameNum >= 16)
	{
		frameNum = 1;// 16ʱ��Ϊ0
	}
	//���ݴ��
	memset( (unsigned char *)&sendFrame, 0 , sizeof(sendFrame));		//��շ��ͽṹ��
	sendFrame.bFrame = FRAME_HEAD;					//֡ͷ ����Ϊ 55H
	sendFrame.bAddr = RFIDSystemCfg.nBusAddr;//cxm fixed
	sendFrame.bAddrInfo = framePriority + frameAnswer + frameNum;	//�����ֽ� ����:���ȼ�, �ظ�֡, �ظ����к�
	sendFrame.bLength = dataLength + 1;				//������Ϊ ���ݳ��� + ָ��(1�ֽ�)
	sendFrame.bCommand = *pSendCommand;				//����ָ��
	memcpy(sendFrame.bData, pSendData, dataLength);

	unsigned short CRCValue = 0;					//CRCУ���㷨, ������֡β2�ֽ�
	CRCValue = CRC16( (unsigned char*)&sendFrame, dataLength + 4);//֡ͷ��Ҫ,������Ϊ3
	sendFrame.bData[dataLength] = (char)((CRCValue >> 8) & 0xff);
	sendFrame.bData[dataLength + 1] = (char)(CRCValue & 0xff);

	//֡����ת��
	unsigned char pForSendBuffer[SENDFRAME_MAXBUF];
	unsigned char *pBuffer = pForSendBuffer + 1;			//������֡ͷ
	unsigned char *pFrameData = (unsigned char*)&sendFrame;
	int forSendLength = dataLength + 7;						//֡ͷΪ 1�ֽ�, ������Ϊ 3�ֽ�, ָ��Ϊ 1�ֽ�, CRC16Ϊ 2�ֽ�  7 = 1+3+1+2;

	pForSendBuffer[0] = FRAME_HEAD;
	for (int tempi = 1 ; tempi < dataLength + 7; ++tempi)
	{
		if ( pFrameData[tempi] == FRAME_HEAD)				//֡�����г��� 0x55 �����, ��0x56 + 0x56 2���ֽڴ���
		{
			*pBuffer++ = FRAME_HEAD_REPLACE;
			*pBuffer++ = FRAME_HEAD_REPLACE;
			++forSendLength;
		}
		else
			if ( pFrameData[tempi] == FRAME_HEAD_REPLACE)	//���� 0x56 �����, ��0x56 + 0x57 2�ֽڴ���
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
	printData("\n����������:",pForSend,forSendLength);
#endif
	return true;
}

//////////////////////////////////////////////////////////////////////////
//������:	���ݽ������
//����˵��:	revData Ϊ���յ���Ҫ���������������, revLength Ϊ���յ����ݵĳ���
//����ֵ:	true ��ʾ����1������������֡, �������ж�ʧ,���ʾ����1����֡, false ��ʾ���ص���1����������֡,������ȴ���������,�������
//////////////////////////////////////////////////////////////////////////
//bool CConnectCommon::UnpackMsg(unsigned char * revData, int revLength)
//{
//	int nCurPasBufferLen = 0;										//��ǰpasBuffer�е����ݳ���
//	int revHead = 0;
//	int nextHead = 0;
//	unsigned char *pRevData = (unsigned char*)&revFrame;		//�趨ָ�� ָ����յĽṹ��
//	// ���,��ǰbuffer����û��������
//	if ( pasLength == 0)										//�����ڹ�ȥ���ݰ�
//	{
//		for ( revHead = 0; revHead < revLength; ++revHead)
//		{
//			if (revData[revHead] == FRAME_HEAD)					//��鵽�½��յ��������а���֡ͷ, ��ʾ���µ�֡���ݰ�������
//				break;
//		}
//		if(revHead != revLength) //����ڴ˴��հ��������ҵ�֡ͷ
//		{
//			memcpy(pasBuffer, revData + revHead, revLength - revHead);	//���ڲ������й�ȥ�����ݰ�, �����½��յ���������֡ͷǰ������			
//			nCurPasBufferLen = revLength - revHead;						//����Ϊ��������, ����������
//		}
//		else//�½��յ����ݰ�����֡ͷ, ����Ϊ����������,���Բ��ٴ���
//		{
//			memset((unsigned char*)&revFrame, 0 , sizeof(revFrame));
//			return true;
//		}															
//	}						
//	else//��ǰbuffer����������(���ڹ�ȥ��)
//	{
//		if ( pasLength + revLength > REC_FRAME_MAXBUFF)	//����Ӧ�����ܳ���,revLength ����һ�ν�256��
//		{
//			memcpy(pasBuffer+pasLength, revData, REC_FRAME_MAXBUFF - pasLength);
//			nCurPasBufferLen = REC_FRAME_MAXBUFF;
//		}
//		else//Ӧ��ִ���������,���½��յ����ݴ���pasBuffer
//		{
//			memcpy(pasBuffer+pasLength, revData, revLength);
//			nCurPasBufferLen = pasLength + revLength;
//		}
//	}
//
//	for (nextHead = 1; nextHead < nCurPasBufferLen; ++nextHead)			//����pasBuffer���Ƿ���ڶ��֡, ���ҵ���2��֡ͷ��λ��
//	{
//		if ( pasBuffer[nextHead] == FRAME_HEAD)
//			break;
//	}
//	// ����ת�� ������ ���սṹ��
//	//OutputDebugString(L"data convert\n");
//	int nFixLen = 0;//cxm BugFix: ����������澭��ת����ʵ���յ������ݳ���
//	/*
//	��Ϊ����ȡ��,0x56 0x56 �ᱻת����0x 5!0x56,0x57�ᱻת����0x56,��ʵ�ʳ��ȹ�Ϊת���󳤶�
//	��� Ҫ��6B��ʱ,��13���ֽ�,����Щ�ֽ�ǡ����0x55,��(0x56,0x56),��ôҪ��26���ֽ�,������13���ֽ�
//	*/
//	int tempj = 0;
//	for (tempj = 0; tempj < nextHead - 1; ++tempj)//��:�յ�һ����������Ϊ23ʱ,nextHead=23,�˵�tempj��Χ[0-21],ע���ж�[tempj+1]�ķ���,����22���д��?
//	{
//		// 0x56 0x56ת����0x55
//		if( pasBuffer[tempj] == FRAME_HEAD_REPLACE && pasBuffer[tempj + 1] == FRAME_HEAD_REPLACE ) 
//		{
//			++tempj;
//			*pRevData ++ = FRAME_HEAD;
//		}
//		else
//		{
//			//0x56 0x57ת����0x56
//			if( pasBuffer[tempj] == FRAME_HEAD_REPLACE && pasBuffer[tempj + 1] == FRAME_FRAME_REPLACE ) 
//			{
//				++tempj;
//				*pRevData ++ = FRAME_HEAD_REPLACE;
//			}
//			else
//				*pRevData ++ = pasBuffer[tempj];
//		}
//		nFixLen ++;//cxm FixBug:ѭ����һ���������һ��ת��,revFrame ʵ�ʽ��յĳ���
//	}
//	/*
//	�������յ�23���ֽ�,pasBufferΪ[0-22]
//	0 1 2 3 4 ... 21 22 23 24
//	A:�����tempjΪ21ʱ,pasBuffer[tempj]Ϊ0x55,pasBuffer[tempj+1] = pasBuffer[22] Ϊ0x55,��ôpasBuffer[22]��ֵ�Ѿ���ת����
//		�������� pRevData = pasBuffer[nextHead-1] = pasBuffer[22] ������,pRevData�� ++ 
//	B:���tempjΪ21ʱ,pasBuffer[tempj]Ϊ0x45,pasBuffer[tempj+1]Ϊ0x08(������,��֮��������ת��0,ѭ����tempjֵδ��,����21,��һ��ѭ��ǰ
//	ֵ��Ϊ22,����������,ѭ��δִ��,��ʱ��*pRevData = pasBuffer[nextHead-1] = pasBuffer[22]���� 
//	*/
//	//*pRevData = pasBuffer[nextHead - 1];//cmx Buf fix:����������
//	if( tempj == nextHead ) //֤���������0x55,0x55 ����0x55,0x56
//	{
//
//	}
//	else//�������
//	{
//		*pRevData = pasBuffer[tempj];
//		nFixLen++;
//	}
//
//	
//	//���ϲ����ѽ�ԭ����pasbuffer�����ݺ��½��յ���revData�е�����һ�����revFrame��
//
//	//OutputDebugString(L"data exit\n");
//	//��pasBuffer �� pasLength ������
//	unsigned char moveBuffer[REC_FRAME_MAXBUFF];
//	if (nextHead != nCurPasBufferLen)	//ˢ��pasBuffer, �����ڶ�֡���,���Ƴ���1֡, �������������ǰ�ƶ�, ����ֱ��ˢ��pasBufferΪ0;
//
//	{	
//		memcpy (moveBuffer, pasBuffer + nextHead , nCurPasBufferLen - nextHead);
//		memset(pasBuffer, 0, nCurPasBufferLen);
//		memcpy(pasBuffer, moveBuffer,  nCurPasBufferLen - nextHead);
//		pasLength = nCurPasBufferLen - nextHead;
//	}
//	else//ֻ��1֡�����
//	{
//		if (revFrame.bLength == 0 )	//1.��ԭ����revFrame�еĳ�����bLength��û������
//		{
//			//if(revLength == 0)//���������������ʱ,
//			//{	//ֱ��ˢ��pasBuffer,������ԭ��������
//			//	memset((unsigned char*)&revFrame, 0 , sizeof(revFrame));
//			//	memset(pasBuffer, 0, nCurPasBufferLen);
//			//	pasLength = 0;
//			//	return true;//����һ���յ�����֡,�ڵ��ú������revFrame.bFrame�Ƿ�Ϊ 0 
//			//}	
//			//else														
//			{
//				pasLength = nCurPasBufferLen;//���ݰ���û������,���´˴���ȡ��pasLenth�ĳ���
//				return false;
//			}
//		}
//#ifdef _DEBUG
//		char szTemp[10];
//		itoa(revFrame.bLength,szTemp,10);
//		_bstr_t bstrCurPassBufferLen = szTemp;
//		OutputDebugString(L"Ҫ��ȡ�����ݳ���:");
//		OutputDebugString(bstrCurPassBufferLen);
//		OutputDebugString(L"\n");
//
//		itoa(nFixLen- FRAME_WITHOUTBLENGTH,szTemp,10);
//		bstrCurPassBufferLen = szTemp;
//		OutputDebugString(L"����ȡ��ʵ�����ݳ���:");
//		OutputDebugString(bstrCurPassBufferLen);
//		OutputDebugString(L"\n");
//		
//#endif
//	//	if (revFrame.bLength != 0 && revFrame.bLength > nCurPasBufferLen - FRAME_WITHOUTBLENGTH) //֡ͷΪ 1�ֽ�, ������Ϊ 3�ֽ�, CRC16Ϊ 2�ֽ� 6 = 1+3+2
//		if (revFrame.bLength != 0 && revFrame.bLength > nFixLen - FRAME_WITHOUTBLENGTH) //cxm FixBug
//		{																//2.��pasBuffer�е����ݲ�����1�����������
//			//if (revLength == 0)											//���������������ʱ,
//			//{															//ֱ��ˢ��pasBuffer,������ԭ��������
//			//	memset((unsigned char*)&revFrame, 0 , sizeof(revFrame));
//			//	memset(pasBuffer, 0, nCurPasBufferLen);
//			//	pasLength = 0;
//			//	return true;											//����һ���յ�����֡,�ڵ��ú������revFrame.bFrame�Ƿ�Ϊ 0 
//			//}															//,ȷ���Ƿ�Ϊ ��֡ ,
//			//else														//���ݰ���û������
//			{
//				pasLength = nCurPasBufferLen;//���ݰ���û������,���´˴���ȡ��pasLenth�ĳ���
//				return false;
//			}
//		}
//		else//3.���ý�����1�����ݰ�
//		{
//			memset(&revFrame.bCommand + revFrame.bLength + 2, 0, DATA_BUFFER - revFrame.bLength - 2);	//�����Ч��Ϣ����֮���������Ϣ
//			memset(pasBuffer, 0, nCurPasBufferLen);
//			pasLength = 0;//���������0,��Ϊ ����ֻ��һ֡(��if����),�Ѿ������� 
//		}
//
//	}
//#if _DEBUG
//	LPBYTE pTest = (LPBYTE)&revFrame;
//	printData("CRC��֤ǰ����:",pTest,revFrame.bLength +FRAME_WITHOUTBLENGTH);
//#endif
//	//�������ϴ���,��ǰ�õ���revFrame��һ�������İ�
//	//CRC16У��
//	unsigned short CRCValue = 0;					//CRCУ���㷨, ������֡β2�ֽ�
//	CRCValue = CRC16( (unsigned char*)(&revFrame), revFrame.bLength + 5);//֡ͷ��Ҫ
//	if(CRCValue != 0 )	//�����ʱ�򷵻�Ϊ1����֡
//	{
//		memset((unsigned char*)&revFrame, 0 , sizeof(CRFIDFrame));
//	}
//	return true;
//}


//////////////////////////////////////////////////////////////////////////
//������:	���ݽ������
//����˵��:	revData Ϊ���յ���Ҫ���������������, revLength Ϊ���յ����ݵĳ���
//����ֵ:	true ��ʾ����1������������֡, �������ж�ʧ,���ʾ����1����֡, false ��ʾ���ص���1����������֡,������ȴ���������,�������
//////////////////////////////////////////////////////////////////////////
bool CConnectCommon::UnpackMsg(unsigned char * revData, int revLength)
{	
	if (revLength + pasLength == 0 )
		return false;

	int nCurPasBufferLen = 0;							//��ǰpasBuffer�е����ݳ���
	int revHead = 0;
	int nextHead = 0;

	//1.���µ�ǰҪ��������ݻ������������յ����ݷ���洢��������
	//----------------------------------------------------------------------------------------------------------------------------
	if (pasLength == 0)	//�����ڹ�ȥ���ݰ�
	{
		for ( revHead = 0; revHead < revLength; ++revHead)
		{
			if (revData[revHead] == FRAME_HEAD)			//��鵽�½��յ��������а���֡ͷ, ��ʾ���µ�֡���ݰ�������
				break;
		}

		if(revHead != revLength) //����ڴ˴��հ��������ҵ�֡ͷ
		{
			memcpy(pasBuffer, revData + revHead, revLength - revHead);//���½��յ�����������ʶ��Ϊ֡ͷ������ݿ�������ǰ�洢������			
			nCurPasBufferLen = revLength - revHead;			//���µ�ǰ�洢����������
		}
		else//�½��յ����ݰ�����֡ͷ����Ϊ���������ݣ�����������
		{
			memset((unsigned char*)&revFrame, 0 , sizeof(revFrame));
			return true;
		}
	}																
	else//��ǰbuffer����������(���ڹ�ȥ��)
	{
		if ( pasLength + revLength > REC_FRAME_MAXBUFF)	//��ǰ������������ʱ��������������
		{//����������ݣ����½���
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
		else//Ӧ��ִ���������,���½��յ����ݴ���pasBuffer
		{
			memcpy(pasBuffer+pasLength, revData, revLength);
			nCurPasBufferLen = pasLength + revLength;
		}
	}

	/*char dbgbuffer[64];
	sprintf(dbgbuffer, "�����յ����ݣ�%d�ֽڣ�\t��ǰ�洢�������й������ݣ�%d�ֽ�\n", revLength, nCurPasBufferLen);
	OutputDebugString((_bstr_t)dbgbuffer);*/

	//2.����pasBuffer���Ƿ���ڶ��֡, ���ҵ���2��֡ͷ��λ�ã�Ŀ�������û���ҵ��ڶ�֡֡ͷ��˵���洢�������п���ֻ��һ֡������һ֡����ȫ
	//----------------------------------------------------------------------------------------------------------------------------
	for (nextHead = 1; nextHead < nCurPasBufferLen; ++nextHead)			
	{
		if ( pasBuffer[nextHead] == FRAME_HEAD)
			break;
	}

	//3.�������� ������������ݴ�����սṹ�壬��ԭ����pasbuffer�����ݺ��½��յ���revData�е�����һ�����revFrame��
	//----------------------------------------------------------------------------------------------------------------------------
	//cxm BugFix: ����������澭��ת����ʵ���յ������ݳ���
	//��Ϊ����ȡ��:
	//0x56 0x56�ᱻת����0x55
	//0x56 0x57�ᱻת����0x56����ʵ�ʳ��ȹ�Ϊת���󳤶�
	//��� Ҫ��6B��ʱ,��13���ֽ�,����Щ�ֽ�ǡ����0x55,��(0x56,0x56),��ôҪ��26���ֽ�,������13���ֽ�
	//
	int nFixLen = 0;

	unsigned char *pRevData = (unsigned char*)&revFrame;//�趨ָ�� ָ����յĽṹ��
	int tempj = 0;
	//��:�յ�һ����������Ϊ23ʱ,nextHead=23,�˵�tempj��Χ[0-21],ע���ж�[tempj+1]�ķ���,����22���д��?

	// ת������ ������������ݴ�����սṹ��
	for (tempj = 0; tempj < nextHead - 1; ++tempj)
	{
		// 0x56 0x56ת����0x55
		if( pasBuffer[tempj] == FRAME_HEAD_REPLACE && pasBuffer[tempj + 1] == FRAME_HEAD_REPLACE ) 
		{
			++tempj;
			*pRevData ++ = FRAME_HEAD;
		}
		//0x56 0x57ת����0x56
		else if( pasBuffer[tempj] == FRAME_HEAD_REPLACE && pasBuffer[tempj + 1] == FRAME_FRAME_REPLACE ) 
		{
			++tempj;
			*pRevData ++ = FRAME_HEAD_REPLACE;
		}			
		else
			*pRevData ++ = pasBuffer[tempj];

		nFixLen ++;//cxm FixBug:ѭ����һ���������һ��ת��,revFrame ʵ�ʽ��յĳ���
	}
	/*
	�������յ�23���ֽڣ�pasBufferΪ[0-22]
	0 1 2 3 4 ... 21 22 23 24
	A:�����tempjΪ21ʱ,pasBuffer[tempj]Ϊ0x55,pasBuffer[tempj+1] = pasBuffer[22] Ϊ0x55,��ôpasBuffer[22]��ֵ�Ѿ���ת����
	�������� pRevData = pasBuffer[nextHead-1] = pasBuffer[22] ������,pRevData�� ++ 
	B:���tempjΪ21ʱ,pasBuffer[tempj]Ϊ0x45,pasBuffer[tempj+1]Ϊ0x08(������,��֮��������ת��0,ѭ����tempjֵδ��,����21,��һ��ѭ��ǰ
	ֵ��Ϊ22,����������,ѭ��δִ��,��ʱ��*pRevData = pasBuffer[nextHead-1] = pasBuffer[22]���� 
	*/
	//*pRevData = pasBuffer[nextHead - 1];//cmx Buf fix:����������
	if( tempj != nextHead ) //֤������治��0x55,0x55 ����0x55,0x56
	{
		*pRevData = pasBuffer[tempj];
		nFixLen++;
	}

	//4.�������ݻ��������������ݣ������ڶ�֡���,���Ƴ���1֡, �������������ǰ�ƶ�, ����ֱ��ˢ��pasBufferΪ0
	//----------------------------------------------------------------------------------------------------------------------------
	unsigned char moveBuffer[REC_FRAME_MAXBUFF];
	if (nextHead != nCurPasBufferLen)	
	{	
		pasLength = nCurPasBufferLen - nextHead;
		memcpy (moveBuffer, pasBuffer + nextHead , pasLength);
		memset(pasBuffer, 0, nCurPasBufferLen);
		memcpy(pasBuffer, moveBuffer,  pasLength);
	}
	else//ֻ��1֡�����
	{
		if (revFrame.bLength == 0 )	//ԭ����revFrame�еĳ�����bLength��û������
		{
			pasLength = nCurPasBufferLen;//���ݰ���û������,���´˴���ȡ��pasLenth�ĳ���
			return false;
		}

		if (revFrame.bLength != 0 && revFrame.bLength > nFixLen - FRAME_WITHOUTBLENGTH) //cxm FixBug
		{	
			pasLength = nCurPasBufferLen;//���ݰ���û������,���´˴���ȡ��pasLenth�ĳ���
			return false;
		}
		else//3.���ý�����1�����ݰ�
		{
			memset(&revFrame.bCommand + revFrame.bLength + 2, 0, DATA_BUFFER - revFrame.bLength - 2);	//�����Ч��Ϣ����֮���������Ϣ
			memset(pasBuffer, 0, nCurPasBufferLen);
			pasLength = 0;//���������0,��Ϊ ����ֻ��һ֡(��if����),�Ѿ������� 
		}
	}

	//5.�������ϴ���,��ǰ�õ���revFrame��һ�������İ���У���������֡������
	//----------------------------------------------------------------------------------------------------------------------------
	if( CRC16( (unsigned char*)(&revFrame), revFrame.bLength + 5) != 0 )	//�����ʱ�򷵻�Ϊ1����֡
		memset((unsigned char*)&revFrame, 0 , sizeof(CRFIDFrame));

	return true;
}