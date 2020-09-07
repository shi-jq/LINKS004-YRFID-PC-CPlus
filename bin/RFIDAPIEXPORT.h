////////////////////////////////////////////////////////////////////////
// Module:  RFIDEXPORT.h
// Author:  cxm owen
// Modified: 2010��12��17�� 14:23:09
// Purpose: 
////////////////////////////////////////////////////////////////////////
#pragma once

#ifndef  _RFIDEXPORT_H
#define  _RFIDEXPORT_H
#define  STDCALL __stdcall

#ifdef RFIDAPI_EXPORTS
#define RFID_API __declspec( dllexport )
#else
#define RFID_API __declspec( dllimport )
#endif

#ifdef __cplusplus
extern "C" {
#endif


	//////////////////////////////////////////////////////////////////////////
	//1.0 API��̬��汾��ѯ
	//���ܣ�ͨ���������룬��ѯ��ǰAPI��汾
	//������
	//  pHandle 			Ϊ����򿪵Ķ˿ھ��
	//  copyright			�汾��
	//����ֵ�� trueΪ�����ɹ�, falseΪ����ʧ��
	//////////////////////////////////////////////////////////////////////////
	bool RFID_API STDCALL SAAT_Copyright(void** pHandle, char* copyright);


	//////////////////////////////////////////////////////////////////////////
	//1.1 TCP������ʼ��
	//���ܣ�ͨ���������룬��ʼ��TCP��Ϊ��������׼��
	//������
	//  pHandle 		Ϊ����򿪵Ķ˿ھ��
	//  pHostName		������IP��ַ����������ͨѶģʽ����Ч
	//  nsocketPort		����SOCKET�˿�
	//����ֵ�� trueΪ�����ɹ�, falseΪ����ʧ��
	//////////////////////////////////////////////////////////////////////////
	bool RFID_API STDCALL SAAT_TCPInit(void** pHandle,char *pHostName,int nsocketPort);


	//////////////////////////////////////////////////////////////////////////
	//1.2 COM������ʼ��
	//���ܣ�ͨ���������룬��ʼ��COM��Ϊ��������׼��
	//������
	//  pHandle 		Ϊ����򿪵Ķ˿ھ��
	//  nBusAddr		Ϊ���ߵ�ַ
	//  pComNum			COM1��COM4 ����COMͨѶģʽ����Ч
	//  nBaud			����ͨѶ����
	//����ֵ�� trueΪ�����ɹ�, falseΪ����ʧ��
	//////////////////////////////////////////////////////////////////////////
	bool RFID_API STDCALL SAAT_COMInit(void** pHandle,unsigned char nBusAddr,char *pComNum,int nBaud );

	//////////////////////////////////////////////////////////////////////////
	//1.3 USB������ʼ��
	//����������Ŀǰ��д����USB�ӿ�Ӧ��ͨ����ͨ����������ģ����USB�ӿڵ�ʹ��ҲҪ��ʼ��COM�ڣ��˺���ͨ���������룬��ʼ�������COM�ڣ�Ϊ������������USB������׼����
	//����ԭ�ͣ�
	//���������
	//pHandle		Ϊ����򿪵Ķ˿ھ��
	//nBusAddr		Ϊ���ߵ�ַ��Ĭ��Ϊ0
	//pUSBNum		COM1��COM4 (COM1-COM4������Ĵ��ڣ�ͨ��ʱתUSBЭ��)����USBͨѶģʽ����Ч
	//nBaud			USB��ͨѶ����,Ĭ��Ϊ152000
	//����ֵ��true�������ɹ���false������ʧ�ܡ�
	//////////////////////////////////////////////////////////////////////////
	bool RFID_API __stdcall SAAT_USBInit(void** pHandle,unsigned char nBusAddr,char * pUSBNum,int nBaud );

	//////////////////////////////////////////////////////////////////////////
	//1.4 UDP������ʼ��
	//����������ͨ���������룬�˺������ڼ��������̫��Ӧ�����ã���ʼ��һ��SOCKET��Ϊ����������̫���ӿڵ�UDP������׼����
	//����ԭ�ͣ�
	//bool	SAAT_UDPInit (void** pHandle,char *pHostName,int nsocketPort)
	//���������
	//pHandle			Ϊ����򿪵Ķ˿ھ��
	//pHostName			��д��IP��ַ
	//nsocketPort		��д��UDP SOCKET�˿ڣ�Ĭ��Ϊ7088
	//����ֵ��true�������ɹ���false������ʧ�ܡ�
	//////////////////////////////////////////////////////////////////////////
	bool RFID_API __stdcall SAAT_UDPInit(void** pHandle,char *pHostName,int nsocketPort);

	//////////////////////////////////////////////////////////////////////////
	//1.5 �򿪶�д��
	//���ܣ�		������������
	//������
	//  pHandle 		Ϊ����򿪵Ķ˿ھ��
	//����ֵ�� trueΪ�����ɹ�, falseΪ����ʧ��
	//////////////////////////////////////////////////////////////////////////
	bool RFID_API  STDCALL SAAT_Open(void* pHandle);


	//////////////////////////////////////////////////////////////////////////
	//1.6 �رն�д��
	//���ܣ�	������������
	//������
	//	pHandle 	Ϊ�򿪵Ķ˿ھ��
	//����ֵ�� trueΪ�����ɹ�, falseΪ����ʧ��
	//////////////////////////////////////////////////////////////////////////
	bool RFID_API  STDCALL SAAT_Close(void *pHandle);


	//////////////////////////////////////////////////////////////////////////
	//1.7 ����API��̬����������
	//�����������˺�����������API��̬���������͡�
	//����ԭ�ͣ�
	//bool   SAAT_SetLanguageType (void *pHandle, char* szType)
	//��������� 
	//pHandle 		�򿪵Ķ˿ھ��
	//szType		��������,cnΪ��������,twΪ��������,enΪӢ��
	//����ֵ��true�������ɹ���false������ʧ�ܡ�
	//////////////////////////////////////////////////////////////////////////
	bool RFID_API  __stdcall SAAT_SetLanguageType (void* pHandle,char* szType);

	//////////////////////////////////////////////////////////////////////////
	//1.8  ��ȡ������Ϣ
	//���ܣ����ڹرչ���,��Ҫ���ڹرն�������
	//������
	//		pHandle:	�򿪵Ķ˿ھ��
	//		szMsg:		���ش�����Ϣ
	//      nLen:       szMsg�������ĳ���    
	//����ֵ�� trueΪ�����ɹ�, falseΪ����ʧ��
	//////////////////////////////////////////////////////////////////////////
	bool RFID_API  STDCALL SAAT_GetErrorMessage(void *pHandle,char *szMsg, int nLen);


	//////////////////////////////////////////////////////////////////////////
	//1.9  ��ȡ����������
	//���ܣ���ȡ����������
	//������
	//		pHandle:	�򿪵Ķ˿ھ��
	//		pCode:		���ش������
	//����ֵ�� trueΪ�����ɹ�, falseΪ����ʧ��
	//////////////////////////////////////////////////////////////////////////
	bool RFID_API  STDCALL SAAT_GetErrorCode(void *pHandle,int *pCode);

	//////////////////////////////////////////////////////////////////////////
	//2.0 �Ͽ����Ӳ�����
	//�������������ڶϿ����Ӳ�������
	//����ԭ�ͣ�
	//bool	SAAT_Reconnect(void *pHandle)
	//���������
	//pHandle	Ϊ�򿪵Ķ˿ھ��
	//����ֵ��true�������ɹ���false������ʧ�ܡ�
	//////////////////////////////////////////////////////////////////////////
	bool RFID_API  __stdcall SAAT_Reconnect(void* pHandle);

	//////////////////////////////////////////////////////////////////////////
	//2.1 ����ָ��
	//������������ָ��������λ����RFID�豸֮�佨��������̫�������ڡ�USB�ڵȵ�ͨѶ���Ӻ�������ӿڵ���ͨ�������λ��һ�㳬��һ��ʱ��δ���յ�RFID�豸�����ݣ���RFID�豸�ȴ���������ǰ��Ƶ��Χ���޿��������ɷ��͸�ָ��Ҫ��RFID�豸��Ӧ�����������ͨѶ��·������״̬��RFID�豸�Ĺ���״̬��
	//����ԭ�ͣ�
	//bool	SAAT_HeartSend (void *pHandle)
	//���������
	//pHandle	Ϊ�򿪵Ķ˿ھ��
	//����ֵ��true������������false�����ӶϿ���
	//////////////////////////////////////////////////////////////////////////
	bool RFID_API  STDCALL SAAT_HeartSend (void* pHandle);

	//////////////////////////////////////////////////////////////////////////
	//2.2 ϵͳ��Ϣ����
	//���ܣ��趨��д������
	//������
	//  pHandle:	�򿪵Ķ˿�����
	//	nType:		ϵͳ��Ϣ��������
	//				0x00	    	��д������					8�ֽ�
	//				0x10  	    	��д��ϵͳȨ����			6�ֽ�
	//	pParm:		ϵͳ����
	//	nLen:		ϵͳ��������
	//����ֵ�� trueΪ�����ɹ�, falseΪ����ʧ��
	//////////////////////////////////////////////////////////////////////////
	bool RFID_API  STDCALL SAAT_SysInfSet (void* pHandle, unsigned char nType, unsigned char* pParm, int nLen);

	//////////////////////////////////////////////////////////////////////////
	//2.3 ϵͳ��Ϣ��ѯ
	//���ܣ���ѯ��д������
	//������
	//	pHandle:		�򿪵Ķ˿ھ��
	//	nType ��		Ҫ��ѯ�Ĳ�������
	//					nType           ����							����
	//					0x00			��д������						8�ֽ�
	//					0x01			��д����Ʒ�ͺ�					5�ֽ�
	//					0x02  			��д��������Ʒ���к�			8�ֽ�
	//					0x03   			��д������������汾��			4�ֽ�
	//					0x04   			��д�����뵥Ԫ����汾��		4�ֽ�
	//					0x05  			������·Ӳ���汾��				4�ֽ�
	//					0x06			��Ƶ��·Ӳ���汾��				4�ֽ�
	//	pPara��			ָ����ն�д�����������ڴ��ָ�� 
	//	pLen�� 			pLenָ����ڴ泤��
	//����ֵ�� trueΪ�����ɹ�, falseΪ����ʧ��
	bool RFID_API  STDCALL SAAT_SysInfQuery (void* pHandle ,unsigned char nType, unsigned char *pPara, unsigned char *pLen);

	//////////////////////////////////////////////////////////////////////////
	//2.4 ����ģʽ����
	//�����������˺����������ö�д���Ĺ���ģʽ��
	//����ԭ�ͣ�
	//bool	SAAT_WorkModeSet (void* pHandle ,unsigned nType)
	//���������
	//pHandle		�򿪵Ķ˿ھ��
	//nType			Ҫ���õĹ���ģʽ
	//����ģʽ      ����			˵��
	//0x00			����ģʽ    ��д������λ����ָ�������ִ�б�ǩ������
	//0x01			Ԥ��ģʽ    ��д����������Ԥ�õ�ָ��ִ�б�ǩ������
	//0x02			����ģʽ    ��д������IO���봥����ǩ����ָ�
	//0x03			��ʱģʽ    ��д������ϵͳʱ�Ӷ�ʱ��ִ�б�ǩ������
	//����ֵ��true�������ɹ���false������ʧ�ܡ�
	//////////////////////////////////////////////////////////////////////////
	bool RFID_API  __stdcall SAAT_WorkModeSet (void* pHandle ,unsigned char nType);


	//////////////////////////////////////////////////////////////////////////
	//2.5 ��д��ϵͳ����
	//���ܣ����ڲ��Զ�д��
	//������
	//	pHandle:		�򿪵Ķ˿ھ��
	//	nType ��		����ģʽ
	//  nAntenna:		���߶˿ں�
	//	pTestParm: 		����ģʽ����
	//	nLen:			����ģʽ�����ĳ���
	//����ֵ�� trueΪ�����ɹ�, falseΪ����ʧ��
	//////////////////////////////////////////////////////////////////////////
	bool RFID_API  STDCALL SAAT_SysTest(void* pHandle ,
		unsigned char nType,
		unsigned char nAntenna, 
		unsigned char *pTestParm, 
		unsigned char nLen);


	//////////////////////////////////////////////////////////////////////////
	//2.6 ���������
	//���ܣ����ڲ�����д���Ĳ���������������ߵ�����д����ϵͳ������
	//������
	//	pHandle:	�򿪵Ķ˿ھ��
	//	nType: 			����������Ĳ���ģʽ  
	//		0			�ָ�ϵͳ������Ϊ��������
	//		1			����ϵͳ������
	//		2			����ϵͳ������
	//	nStartAddrr:	ָ��������������ʼλ��
	//	nLen:			ָ��������������
	//	pData:			��������ʱ�ĵ�������
	//	pDataLen:		�������ݳ���
	//ע������ģʽΪ0x00ʱ����ʼ��ַ�Ͳ�������������������塣
	//����ֵ�� trueΪ�����ɹ�, falseΪ����ʧ��
	//////////////////////////////////////////////////////////////////////////
	bool RFID_API  STDCALL SAAT_ParmOp (void* pHandle ,
		unsigned char nType, 
		unsigned char nStartAddrr, 
		unsigned char nLen,  
		unsigned char *pData, 
		unsigned char *pDataLen);


	//////////////////////////////////////////////////////////////////////////
	//2.7 ͨѶ��������
	//���ܣ���������ͨѶ����
	//������
	//	pHandle : 	�򿪵Ķ˿ھ��
	//	nType: 		���õĲ�������
	//		0x00	���������豸��ַ
	//		0x01	RS-232��������
	//		0x02	RS-485��������
	//	pPara:		��д���Ĵ������߲���
	//		RS-232��������
	//		0x00	4800bps
	//		0x01	9600 bps
	//		0x02	19200 bps
	//		0x03	38400 bps
	//		0x04	57600 bps
	//		0x05	115200 bps
	//	nLen:		��д���Ĵ������߲�������
	//����ֵ�� trueΪ�����ɹ�, falseΪ����ʧ��
	//////////////////////////////////////////////////////////////////////////
	bool RFID_API  STDCALL SAAT_CommunicatParaSet (void* pHandle ,
		unsigned char nType, 
		unsigned char* pPara, 
		unsigned char nLen);


	//////////////////////////////////////////////////////////////////////////
	//2.8 ͨѶ������ѯ
	//���ܣ����ڲ�ѯ��д����ͨѶ����
	//������
	//	pHandle : 	�򿪵Ķ˿ھ��
	//	nType: 	���õĲ�������
	//	pPara:		��ѯ�Ķ�д�����߲���
	//	pLen:		���߲�������
	//����ֵ�� trueΪ�����ɹ�, falseΪ����ʧ��
	//////////////////////////////////////////////////////////////////////////
	bool RFID_API  STDCALL SAAT_CommunicatParaQuery (void* pHandle ,
		unsigned char nType, 
		unsigned char* pPara,
		unsigned char *pLen);


	//////////////////////////////////////////////////////////////////////////
	//2.9 �����������
	//���ܣ���������ͨѶ����
	//������
	//	pHandle :	�򿪵Ķ˿ھ��
	//	nType: 		���õĲ�������
	//		0x02	IP��ַ
	//		0x03	SOCKET�˿ں�
	//	pPara:		���õ���̫����������
	//	nLen:		�������ݳ���
	//����ֵ�� trueΪ�����ɹ�, falseΪ����ʧ��
	//////////////////////////////////////////////////////////////////////////
	bool RFID_API  STDCALL SAAT_NetParaSet (void* pHandle ,
		unsigned char nType, 
		unsigned char* pPara, 
		unsigned char nLen);


	//////////////////////////////////////////////////////////////////////////
	//3.0 ���������ѯ
	//���ܣ����ڲ�ѯͨѶ����
	//������
	//		pHandle :	�򿪵Ķ˿ھ��
	//		nType: 		Ϊ���õĲ�������
	//			0x01	MAC��ַ
	//			0x02	IP��ַ
	//			0x03	SOCKET�˿ں�
	//		pPara:		��д�����ص������������
	//		pLen:		�������ݳ���
	//����ֵ�� trueΪ�����ɹ�, falseΪ����ʧ��
	//////////////////////////////////////////////////////////////////////////
	bool RFID_API  STDCALL SAAT_NetParaQuery (void* pHandle ,
		int nType, 
		unsigned char* pPara,
		unsigned char *pLen);


	//////////////////////////////////////////////////////////////////////////
	//3.1 ��ǩ������������
	//���ܣ��������ñ�ǩ��������
	//������
	//		pHandle :	�򿪵Ķ˿ھ��
	//		nType: 		�����͡�Ϊ���õĲ������ͣ�������
	//				����	���� 		����	˵��
	//				����ID	ȫѡ		0X00	Ҫ��IDֵ��Ƶ��Χ��ȫ����ǩ��Ӧ��ѯָ��
	//				����ID	����		0X01	Ҫ��IDֵ����ƥ�����ݵı�ǩ��Ӧ��ѯָ��
	//				����ID	������		0X02	Ҫ��IDֵ������ƥ�����ݵı�ǩ��Ӧ��ѯָ��
	//				����ID	����		0X03	Ҫ��IDֵ����ƥ�����ݵı�ǩ��Ӧ��ѯָ��
	//				����ID	С��		0X04	Ҫ��IDֵС��ƥ�����ݵı�ǩ��Ӧ��ѯָ��
	//				��չID	����		0X11	Ҫ��IDֵ����ƥ�����ݵı�ǩ��Ӧ��ѯָ��
	//				��չID	������		0X12	Ҫ��IDֵ������ƥ�����ݵı�ǩ��Ӧ��ѯָ��
	//				��չID	����		0X13	Ҫ��IDֵ����ƥ�����ݵı�ǩ��Ӧ��ѯָ��
	//				��չID	С��		0X14	Ҫ��IDֵС��ƥ�����ݵı�ǩ��Ӧ��ѯָ��
	//		pPara: 		"ƥ������"Ϊ��ǩ��ID��
	//		nLen:		ƥ�����ݵĳ���
	//����ֵ�� trueΪ�����ɹ�, falseΪ����ʧ��
	//////////////////////////////////////////////////////////////////////////
	bool RFID_API  STDCALL SAAT_TagOpParaSet(void* pHandle ,
		unsigned char nType, 
		unsigned char *pPara,
		unsigned char nLen);

	//////////////////////////////////////////////////////////////////////////
	//3.2 ��ǩ����������ѯ
	//�����������˺����������ö�д���Ա�ǩ����д�Ȳ����Ĳ�����
	///����ԭ�ͣ�
	//bool	SAAT_TagOpParaQuery (void* pHandle ,unsigned char nType, unsigned char* pPara, unsigned char *pLen)
	//���������
	//pHandle		�򿪵Ķ˿ھ��
	//nType			Ϊ���õĲ������ͣ������˵����
	//pPara			ָ�򱣴����õĲ������ڴ�ָ��
	//Len			����ʱΪpPara���ȣ�����ʱΪ��ǩ������������
	//����ֵ��true�������ɹ���false������ʧ�ܡ�
	//˵����nType Ϊ���õĲ������ͣ��������Ͻ���ͬ��
	//////////////////////////////////////////////////////////////////////////
	bool RFID_API STDCALL SAAT_TagOpParaQuery(void* pHandle ,
		unsigned char nType, unsigned char* pPara, unsigned char *pLen);

	//////////////////////////////////////////////////////////////////////////
	//3.3 ��Ƶ�˿ڲ�����ѯ
	//���ܣ����ڲ�ѯ��д���Ĳ������ȫ����Ƶ�˿ڲ���
	//������
	//		pHandle:		�򿪵Ķ˿ھ��
	//		szAntennaPara:	ȫ����Ƶ�˿ڲ���
	//			���˿�ʹ�ܡ��� 
	//			��1���ֽڣ�0x03�������޸Ĺ��Ž�������
	//			��2���ֽڣ�0x03�������޸�2401��Ƶ�������͹���
	//			��3���ֽڣ�0x03�������޸���Ƶ˥��������
	//			��4���ֽڣ�������0x00
	//			��������ʡ��� 
	//			��1���ֽڣ����Ž������棩��
	//			0x02�������棻
	//			0x03�������棻
	//			��2���ֽڣ�2401��Ƶ�������͹��ʣ���
	//			0x00��-18DB
	//			0x01��-12DB
	//			0x02�� -6DB
	//			0x03��  0DB
	//			��3���ֽڣ���Ƶ˥�������ʣ���
	//			0��-0DB
	//			1��-1DB
	//			2��-2DB
	//			3��-3DB
	//			4��-4DB
	//			5��-5DB
	//			6��-6DB
	//			...
	//			15��-30dB
	//			��4���ֽڣ�������0x00
	//			����ѯʱ�䡱������Ϊ4���ֽڣ����� 0x00 0x00 0x00 0x00
	//		pLen: 			��������
	//����ֵ�� trueΪ�����ɹ�, falseΪ����ʧ��
	//////////////////////////////////////////////////////////////////////////
	bool RFID_API  STDCALL SAAT_TotalAntennaParmQuery (void* pHandle,unsigned char *szAntennaPara,unsigned char *pLen);


	//////////////////////////////////////////////////////////////////////////
	//3.4 �رչ��� (�رն���)
	//���ܣ����ڹرչ���,��Ҫ���ڹرն�������
	//������
	//		pHandle:		�򿪵Ķ˿ھ��
	//����ֵ�� trueΪ�����ɹ�, falseΪ����ʧ��
	//////////////////////////////////////////////////////////////////////////
	bool RFID_API  STDCALL SAAT_PowerOff(void *pHandle);

	//////////////////////////////////////////////////////////////////////////
	//3.5 ֹͣ����
	//���ܣ�����ֹͣ����
	//������
	//		pHandle:		�򿪵Ķ˿ھ��
	//����ֵ�� trueΪ�����ɹ�, falseΪ����ʧ��
	//////////////////////////////////////////////////////////////////////////
	bool RFID_API  STDCALL SAAT_YPowerOff(void *pHandle);

	//////////////////////////////////////////////////////////////////////////
	//3.6 IO�������
	//���ܣ����ڿ��ƶ�д����IO�������
	//������
	//		pHandle:	�򿪵Ķ˿ھ��
	//		nPort:����˿ڣ�    0    ���ж˿�
	//							1    �˿�1
	//							2	 �˿�2
	//							3	 �˿�3
	//							4	 �˿�4
	//		nState:���״̬��   0    ����͵�ƽ
	//							1    ����ߵ�ƽ  
	//							2    ���������
	//							3    ���������
	//����ֵ�� trueΪ�����ɹ�, falseΪ����ʧ��
	//////////////////////////////////////////////////////////////////////////
	bool RFID_API  STDCALL SAAT_IOOperate(void* pHandle,unsigned char nPort,unsigned char nState);


	//////////////////////////////////////////////////////////////////////////
	//3.7 IO�����ѯָ��
	//���ܣ����ڲ�ѯ��д����չ���IO����״̬
	//����ԭ�ͣ�
	//bool SAAT_IOStateQuery(void* pHandle,unsigned char *pState)
	//������
	//		pHandle:	�򿪵Ķ˿ھ��
	//		pState:		����˿ڵĵ�ƽ״̬
	//					��˵�����˿�״̬
	//				λ		Bit7	Bit 6	Bit 5	Bit 4	Bit 3	Bit 2	Bit 1	Bit 0
	//				����	����	����	����	����	����	����	�˿�2	�˿�1
	//				�˿�״̬��	0 :�͵�ƽ
	//							1:�ߵ�ƽ
	//����ֵ�� trueΪ�����ɹ�, falseΪ����ʧ��
	//////////////////////////////////////////////////////////////////////////
	bool RFID_API  STDCALL SAAT_IOStateQuery(void* pHandle,unsigned char *pState);

	//////////////////////////////////////////////////////////////////////////
	//3.8 ��Դ���Ͷ�ID������
	//���ܣ� ��Դ����ID������
	//����:
	//		pHandle:	Ϊ�Ѿ���ʼ���Ķ˿ھ��
	//		nOpType:	Ϊ����ģʽ, 
	//		����ģʽ��
	//		00����ͬһ����ǩ��ID���д��ֻ����λ������һ�Σ�
	//		��Ҫ����λ�����պ�����д��"��������ȷ��"��
	//		01"����д������ȡ�������еı�ǩID��ȫ���ϴ�����λ������Ҫ����λ�����պ����
	//				��д��"��������ȷ��"��ֱ����λ���·�"�ع���"������ֹͣ����ǩID�롣
	//		nIDType:
	//		0x01     ����ID��BID��
	//		0x02     ��չID��EID��
	//		0X03    ��ǩ���ػ���ID����չID
	//		nTagCount: ΪͬʱԤ�ƶ�ȡ��ǩ��, Ԥ�ƹ���������һ����Ҫͬʱ��ȡ������ǩ�������Ϊ1��255��
	//����ֵ�� trueΪ�����ɹ�, falseΪ����ʧ��
	//////////////////////////////////////////////////////////////////////////
	bool RFID_API  STDCALL SAAT_YReadIDCode ( void *pHandle,
		unsigned char nOpType,
		unsigned char nIDType,
		unsigned int nTagCount);


	//////////////////////////////////////////////////////////////////////////
	//3.9 ��Դ-���ͱ�ǩ�����ϴ�����
	//���ܣ� ��Դ-���ͱ�ǩ�����ϴ�����
	//����:
	//		pHandle Ϊ�Ѿ���ʼ���Ķ˿ھ��
	//		nOpType: Ϊ����ģʽ, 
	//		����ģʽ��
	//		00����ͬһ����ǩ��ID���д��ֻ����λ������һ�Σ�
	//		��Ҫ����λ�����պ�����д��"��������ȷ��"��
	//		01"����д������ȡ�������еı�ǩID��ȫ���ϴ�����λ������Ҫ����λ�����պ����
	//			��д��"��������ȷ��"��ֱ����λ���·�"�ع���"������ֹͣ����ǩID�롣
	//		nIDType Ҫ���յ�ID����
	//����ֵ�� trueΪ�����ɹ�, falseΪ����ʧ��
	//////////////////////////////////////////////////////////////////////////
	bool RFID_API  STDCALL SAAT_YMakeTagUpLoadIDCode ( void *pHandle,
		unsigned char nOpType,
		unsigned char nIDType);

	//////////////////////////////////////////////////////////////////////////
	//4.0 ����EAS�Ĵ���
	//���ܣ� ����EAS�Ĵ���
	//������ 
	//		pHandle: 		Ϊ�Ѿ���ʼ���Ķ˿ھ��
	//		nOpType:		ESA��־��λ����ִ��ģʽ
	//		nIDType:		ID����,ִ��EAS��־��λ��ID��������
	//		pCodeID:		ID����
	//		nTagPwd:		��ǩ����
	//		nSetMode:		��ǩ�ڽ��յ�ָ�����λ�����ķ�ʽ
	//						0x00      ��λ������EAS�Ĵ��������롱������
	//						0x01      ��λ������EAS�Ĵ��������򡱲�����
	//		nFlagBit:			EAS��־����8�����أ��á�1��������EAS����λ���á�0�������EASλ��
	//����ֵ�� trueΪ�����ɹ�, falseΪ����ʧ��
	//////////////////////////////////////////////////////////////////////////
	bool  RFID_API  STDCALL SAAT_YEASRegSet (void *pHandle, 
		unsigned char nOpType, 
		unsigned char nIDType, 
		unsigned char *pCodeID,
		unsigned char *pTagPwd,
		unsigned char nSetMode,
		unsigned char nFlagBit);

	//////////////////////////////////////////////////////////////////////////
	//4.1 ��ѯEAS�Ĵ���
	//���ܣ� ��ѯEAS�Ĵ���
	//������ 
	//		pHandle: 		Ϊ�Ѿ���ʼ���Ķ˿ھ��
	//		nOpType:		ESA��־��λ����ִ��ģʽ
	//		nIDType:		ID����,ִ��EAS��־��λ��ID��������
	//		pIDCode:		ID����
	//		nTagPwd:		��ǩ����
	//		pIDType			ִ��EAS���ID��������
	//		pEASIDCode		ִ��EAS��صĻ���ID����
	//		pFlagBit:		��λ����,��ǩEAS�Ĵ����ڵ�����
	//����ֵ�� trueΪ�����ɹ�, falseΪ����ʧ��
	//////////////////////////////////////////////////////////////////////////
	bool  RFID_API  STDCALL SAAT_YEASRegQuery (void *pHandle, 
		unsigned char nOpType, 
		unsigned char nIDType, 
		unsigned char *pIDCode,
		unsigned char *pTagPwd,
		unsigned char *pIDType,
		unsigned char *pEASIDCode,
		unsigned char *pFlagBit);


	//////////////////////////////////////////////////////////////////////////
	//4.2 ����EAS���
	//���ܣ�  ����EAS���
	//������ 
	//		pHandle 		Ϊ�Ѿ���ʼ���Ķ˿ھ��
	//		nOpType:		Ϊִ��ģʽ
	//						0x00 -> ����EAS���;
	//						0x01 ->����EAS���
	//		nIDType:		ID����
	//		nEasBit:		nEasBit

	//����ֵ�� trueΪ�����ɹ�, falseΪ����ʧ��
	//////////////////////////////////////////////////////////////////////////
	bool  RFID_API  STDCALL SAAT_YEASMonitorEnable (void *pHandle,
		unsigned char nOpType, 
		unsigned char nIDType,
		unsigned char nEasBit);


	//////////////////////////////////////////////////////////////////////////
	//4.3 ����EAS��ص�����������
	//���ܣ�����EAS��ص�����������
	//����:
	//		pHandle 	Ϊ�Ѿ���ʼ���Ķ˿ھ��
	//		pIDData		ΪID����, 
	//		nIDLen		ΪID���ݳ���
	//		nBit		Ϊ��ǩEAS�Ĵ����ڵ�����
	//����ֵ�� trueΪ�����ɹ�, falseΪ����ʧ��
	//////////////////////////////////////////////////////////////////////////
	int  RFID_API  STDCALL SAAT_YRevEASIDMsg (void *pHandle, unsigned char* pIDData,
		unsigned char* pIDLen,
		unsigned char* pBit);


	//////////////////////////////////////////////////////////////////////////
	//4.4 ��Ƶ�˿ڹ�������
	//���ܣ��������ö�д����ָ����Ƶ�˿ڹ���
	//������
	//		pHandle:		�򿪵Ķ˿ھ��
	//		rfPower:	ȫ����Ƶ�˿ڲ�������ֵ��Ӧ���£�
	//		                0��-0DB
	//		                1��-1DB
	//		                2��-2DB
	//		                3��-3DB
	//		                4��-4DB
	//		                5��-5DB
	//		                6��-6DB
	//		                ...
	//		                15��-30dB
	//����ֵ�� trueΪ�����ɹ�, falseΪ����ʧ��
	//////////////////////////////////////////////////////////////////////////
	bool RFID_API  STDCALL SAAT_YAntennaPowerSet (void* pHandle,unsigned char nPower );


	//////////////////////////////////////////////////////////////////////////
	//4.5 ��Ƶ�˿ڹ��ʲ�ѯ
	//���ܣ����ڲ�ѯ��д���Ĳ��������Ƶ�˿ڹ���
	//������
	//		pHandle:	�򿪵Ķ˿ھ��
	//		rfPower:	ȫ����Ƶ�˿ڲ�������ֵ��Ӧ���£�
	//		                0��-0DB
	//		                1��-1DB
	//		                2��-2DB
	//		                3��-3DB
	//		                4��-4DB
	//		                5��-5DB
	//		                6��-6DB
	//		                ...
	//		                15��-30dB	                
	//����ֵ�� trueΪ�����ɹ�, falseΪ����ʧ��
	bool RFID_API  STDCALL SAAT_YAntennaPowerQuery (void* pHandle,unsigned char* pPower);


	//////////////////////////////////////////////////////////////////////////
	//4.6 дEID��
	//���ܣ�����дEID��
	//����:
	//		pHandle 	Ϊ�Ѿ���ʼ���Ķ˿ھ��
	//		nOpMode 	Ϊ����ģʽ
	//		nIDCode		ΪBID��
	//		pAccessPWD 	Ϊ4�ֽڷ�������
	//		pWriteEIDData Ϊд���ǩ��EPC�������
	//����ֵ�� trueΪ�����ɹ�, falseΪ����ʧ��
	//////////////////////////////////////////////////////////////////////////
	bool RFID_API  STDCALL  SAAT_YWriteEIDCode ( void* pHandle, 
		unsigned char nOpMode,
		unsigned char* pIDCode,
		unsigned char *pAccessPWD, 
		unsigned char *pWriteEIDData);

	//////////////////////////////////////////////////////////////////////////
	//4.7 ���û�������
	//���ܣ���ȡ�û����ݷ���
	//������	
	//		pHandle 	ΪIConnectָ��
	//		nOpMode		Ϊ����ģʽ
	//		nIDCodeType Ϊ�������
	//		pIDCode		ΪIDCode
	//		pTagPwd		Ϊ��ǩ����
	//		nBank		Ϊ��ǩ�洢��
	//		nStartAddr 	Ϊ��ȡ��ǩ���������׵�ַ
	//		UserData	��ȡ��������������
	//		pReadLen	ʵ�ʶ�ȡ�����ֽ���
	//		nWaitTime	��ʱʱ��
	//����ֵ�� trueΪ�����ɹ�, falseΪ����ʧ��
	//////////////////////////////////////////////////////////////////////////
	bool RFID_API  __stdcall SAAT_YReadUserData ( void* pHandle, 
		unsigned char nOpMode, 
		unsigned char nIDCodeType,
		unsigned char *pIDCode,
		unsigned char *pTagPwd,
		unsigned char nBank,
		unsigned char nStartAddr,
		unsigned char *pReadData,
		int *pReadLen,
		unsigned int nWaitTime = 1000);

	//////////////////////////////////////////////////////////////////////////
	//4.8 д�û�������
	//		pHandle 	ΪIConnectָ��
	//		nOpMode		Ϊ����ģʽ
	//		nIDCodeType Ϊ�������
	//		pIDCode		ΪIDCode
	//		pTagPwd		Ϊ��ǩ����
	//		nBank		Ϊ��ǩ�洢��
	//		nStartAddr 	Ϊд��ǩ���������׵�ַ
	//		pWriteData	д��������������
	//		pRealWriteLen ����ʵ��д�볤��
	//		nWaitTime	��ʱʱ��
	//����ֵ�� trueΪ�����ɹ�, falseΪ����ʧ��
	//////////////////////////////////////////////////////////////////////////
	bool RFID_API  __stdcall SAAT_YWriteUserData ( void* pHandle, 
		unsigned char nOpMode, 
		unsigned char nIDCodeType,
		unsigned char *pIDCode,
		unsigned char *pTagPwd,
		unsigned char nBank,
		unsigned char nStartAddr,
		unsigned char *pWriteData,
		int nWriteLen,
		unsigned int nWaitTime = 1000);


	//////////////////////////////////////////////////////////////////////////
	//4.9  ��Դ���÷�������
	//���ܣ����÷�������
	//������
	//		pHandle Ϊ�Ѿ���ʼ���Ķ˿ھ��
	//		nOpMode Ϊ����ģʽ
	//		nIDType ΪID����
	//		pIDCode ΪID����
	//		pOrgPWDΪ4�ֽھɷ�������,Ĭ��Ϊ8����
	//		pNewPWDΪ4�ֽ��·�������
	//����ֵ�� trueΪ�����ɹ�, falseΪ����ʧ��
	//////////////////////////////////////////////////////////////////////////
	bool RFID_API  STDCALL SAAT_YAccessPWDSet (void *pHandle,
		unsigned char nOpMode, 
		unsigned char nIDType,
		unsigned char *pIDCode,
		unsigned char *pOrgPWD, 
		unsigned char *pNewPWD);


	//////////////////////////////////////////////////////////////////////////
	//5.0 ��Դ������������
	//���ܣ�������������
	//������
	//		pHandle Ϊ�Ѿ���ʼ���Ķ˿ھ��
	//		nOpMode Ϊ����ģʽ
	//		nIDType ΪID����
	//		pIDCode ΪID����
	//		pOrgPWDΪ4�ֽھ���������,Ĭ��Ϊ8����
	//		pNewPWDΪ4�ֽ�����������
	//����ֵ�� trueΪ�����ɹ�, falseΪ����ʧ��
	//////////////////////////////////////////////////////////////////////////
	bool RFID_API  STDCALL SAAT_YCFGPWDSet (void *pHandle,
		unsigned char nOpMode, 
		unsigned char nIDType,
		unsigned char *pIDCode,
		unsigned char *pOrgPWD, 
		unsigned char *pNewPWD);


	//////////////////////////////////////////////////////////////////////////
	//5.1 ��ǩ������������
	//���ܣ�����ǩ������
	//������
	//		pHandle Ϊ�Ѿ���ʼ���Ķ˿ھ��
	//		nOpMode Ϊ����ģʽ
	//		nIDType ΪID����
	//		pIDCode ΪID����
	//		pTagPWD Ϊ4�ֽ���������
	//		nTagOpType Ϊ����ǩ��������
	//		nStartAddr Ϊ��ʼ��ַ
	//		nDataLen	Ϊ���ݳ���
	//����ֵ�� trueΪ�����ɹ�, falseΪ����ʧ��
	//////////////////////////////////////////////////////////////////////////
	bool RFID_API  STDCALL SAAT_YTagOp(void *pHandle,
		unsigned char nOpMode, 
		unsigned char nIDType,
		unsigned char *pIDCode,
		unsigned char *pTagPWD, 
		unsigned char nTagOpType,
		unsigned short nStartAddr,
		unsigned char nDataLen);

	//////////////////////////////////////////////////////////////////////////
	//5.2 ��ǩ��Ƶ��������ָ��
	//���ܣ���ǩ��Ƶ��������ָ��
	//������ 
	//		pHandle: 		Ϊ�Ѿ���ʼ���Ķ˿ھ��
	//		nOpType:		ִ��ģʽ
	//		nIDType:		ID����,ִ��EAS��־��λ��ID��������
	//		pIDCode:		ID����
	//		nTagPwd:		��ǩ��������
	//		nAntennaPower	��ʶ��ǩ�ĵ�ǰ����Ƶ����
	//			��ʶ�ñ�ǩ����Ƶ���͹��ʣ��������£�
	//			0x00     -18dBm
	//			0x01     -12dBm 
	//			0X02     -6dBm
	//			0X03     0dBm
	//			����     ��������λ���Ƿ�������Ĭ��Ϊ0dBm
	//		nAntennaFrequency ��ƵƵ��	1	0x00~0xFF	��ǩ�Ĺ�����ƵƵ��
	//			��ʶ�ñ�ǩ����Ƶ����Ƶ�㣬�������£�Ƶ����Ϊ27��������Ϊ5MHz����
	//			0x05     2405MHz
	//			0x0A     2410MHz
	//			��        ��   
	//			��        ��   
	//			��        ��   
	//			0X73     2450MHz 
	//			0X78     2520MHz
	//			����     ��������λ���Ƿ�������Ĭ��Ƶ��2450MHz
	//		nHoppingMode:		��λ����,��ǩEAS�Ĵ����ڵ�����
	//			��Ƶ��ʽ����ʶ�ñ�ǩ����Ƶ��ʽ���������£�
	//			0x00     ��ǩ����Ƶ����ǩ�����ڵ�Ƶ������ʽ
	//			����     ��������λ���Ƿ�������

	//����ֵ�� trueΪ�����ɹ�, falseΪ����ʧ��
	//////////////////////////////////////////////////////////////////////////
	bool  RFID_API  STDCALL SAAT_YTagParmSet (void *pHandle, 
		unsigned char nOpType, 
		unsigned char nIDType, 
		unsigned char *pIDCode,
		unsigned char *pTagPwd,
		unsigned char nAntennaPower,
		unsigned char nAntennaFrequency,
		unsigned char nHoppingMode);


	//////////////////////////////////////////////////////////////////////////
	//5.3 ��ǩ��Ƶ������ѯָ��
	//���ܣ���ǩ��Ƶ������ѯָ��
	//������ 
	//		pHandle: 		Ϊ�Ѿ���ʼ���Ķ˿ھ��
	//		nOpType:		ִ��ģʽ
	//		nIDType:		ID����,ִ��EAS��־��λ��ID��������
	//		pIDCode:		ID����
	//		nTagPwd:		��ǩ��������
	//		pAntennaPower	��ʶ��ǩ�ĵ�ǰ����Ƶ����
	//			��ʶ�ñ�ǩ����Ƶ���͹��ʣ��������£�
	//			0x00     -18dBm
	//			0x01     -12dBm 
	//			0X02    -6dBm
	//			0X03     0dBm
	//			����     ��������λ���Ƿ�������Ĭ��Ϊ0dBm
	//		pAntennaFrequency ��ƵƵ��	1	0x00~0xFF	��ǩ�Ĺ�����ƵƵ��
	//			��ʶ�ñ�ǩ����Ƶ����Ƶ�㣬�������£�Ƶ����Ϊ27��������Ϊ5MHz����
	//			0x05     2405MHz
	//			0x0A     2410MHz
	//			��        ��   
	//			��        ��   
	//			��        ��   
	//			0X73     2450MHz 
	//			0X78     2520MHz
	//			����     ��������λ���Ƿ�������Ĭ��Ƶ��2450MHz
	//		pHoppingMode:		��λ����,��ǩEAS�Ĵ����ڵ�����
	//			��Ƶ��ʽ����ʶ�ñ�ǩ����Ƶ��ʽ���������£�
	//			0x00     ��ǩ����Ƶ����ǩ�����ڵ�Ƶ������ʽ
	//			����     ��������λ���Ƿ�������

	//����ֵ�� trueΪ�����ɹ�, falseΪ����ʧ��
	//////////////////////////////////////////////////////////////////////////
	bool  RFID_API  STDCALL SAAT_YTagParmQuery (void *pHandle, 
		unsigned char nOpType, 
		unsigned char nIDType, 
		unsigned char *pIDCode,
		unsigned char *nTagPwd,
		unsigned char *pAntennaPower,
		unsigned char *pAntennaFrequency,
		unsigned char *pHoppingMode);

	//////////////////////////////////////////////////////////////////////////
	//5.3.6 ����ָʾ����
	//�����������˺�����������RFID�豸�ķ�������ָʾ�豸�Ĺ���״̬��
	//����ԭ�ͣ�
	//bool	SAAT_Reading_IOConfig (void* pHandle,unsigned char nConfigBit)
	//���������
	//pHandle		�򿪵Ķ˿ھ��	
	//nConfigBit��	���ò���
	//Bit7	Bit6	Bit5	Bit4	Bit3	Bit2	Bit1	Bit0
	//����	����	����	IO���4	IO���3	IO���2	IO���1	������
	//�豸��Ӧ����ֵΪ
	//0 ����ֹ
	//1 ��ʹ��    
	//* IO�˿�ʹ��״̬����Դ����Ͷ˿�����������̵�������Ͷ˿ڱպϡ�
	//* ���ʹ���ź�Ϊ���壬ʱ��Ϊ100mS��
	//����ֵ��true�������ɹ���false������ʧ�ܡ�
	//////////////////////////////////////////////////////////////////////////
	bool RFID_API  __stdcall SAAT_Reading_IOConfig (void* pHandle,unsigned char nConfigBit);

	//////////////////////////////////////////////////////////////////////////
	//5.3.7 ����ָʾ��ѯ
	//�����������˺������ڲ�ѯRFID�豸�ķ�������ָʾ�豸�Ĺ���״̬��
	//����ԭ�ͣ�
	//bool	SAAT_Reading_IOQuery (void* pHandle,unsigned char* pConfigBit)
	//���������
	//pHandle		�򿪵Ķ˿ھ��	
	//pConfigBit��	��ѯ����
	//Bit7	Bit6	Bit5	Bit4	Bit3	Bit2	Bit1	Bit0
	//����	����	����	IO���4	IO���3	IO���2	IO���1	������
	//�豸��Ӧ����ֵΪ
	//0 ����ֹ
	//1 ��ʹ��    
	//* IO�˿�ʹ��״̬����Դ����Ͷ˿�����������̵�������Ͷ˿ڱպϡ�
	//* ���ʹ���ź�Ϊ���壬ʱ��Ϊ100mS��
	//����ֵ��true�������ɹ���false������ʧ�ܡ�
	//////////////////////////////////////////////////////////////////////////
	bool RFID_API  __stdcall SAAT_Reading_IOQuery (void* pHandle,unsigned char* pConfigBit);

	//////////////////////////////////////////////////////////////////////////
	//5.3.8 ����ָʾ����������
	//�����������˺����������ö���ʱIO�������Ŀ��
	//����ԭ�ͣ�
	//bool	SAAT_IOPulseWidthSet (void* pHandle,unsigned char nIOPort,unsigned char nWidth)
	//���������
	//pHandle		�򿪵Ķ˿ھ��	
	//nIOPort��		���õ�IO�˿�:�˿�1���˿�4
	//nWidth��		������(��λΪ100ms)
	//����ֵ��true�������ɹ���false������ʧ�ܡ�
	//////////////////////////////////////////////////////////////////////////
	bool RFID_API  __stdcall SAAT_IOPulseWidthSet (void* pHandle,unsigned char nIOPort,unsigned char nWidth);

	//////////////////////////////////////////////////////////////////////////
	//5.3.9 ����ָʾ�����Ȳ�ѯ
	//�����������˺������ڲ�ѯ����ʱIO�������Ŀ��
	//����ԭ�ͣ�
	//bool	SAAT_IOPulseWidthQuery (void* pHandle,unsigned char nIOPort,unsigned char* pWidth)
	//���������
	//pHandle		�򿪵Ķ˿ھ��	
	//nIOPort��		��ѯ��IO�˿�:�˿�1���˿�4
	//pWidth��		������(��λΪ100ms)
	//����ֵ��true�������ɹ���false������ʧ�ܡ�
	//////////////////////////////////////////////////////////////////////////
	bool RFID_API  __stdcall SAAT_IOPulseWidthQuery (void* pHandle,unsigned char nIOPort,unsigned char* pWidth);

	//////////////////////////////////////////////////////////////////////////
	//5.4  ��ǩ����ģʽ����ָ��
	//���ܣ���ǩ����ģʽ����ָ��
	//������ 
	//		pHandle: 		Ϊ�Ѿ���ʼ���Ķ˿ھ��
	//		nOpType:		ִ��ģʽ
	//		nIDType:		ID����,ִ��EAS��־��λ��ID��������
	//		pIDCode:		ID����
	//		nTagPwd:		��ǩ��������
	//		nWorkMode:		ִ�����ñ�ǩ�Ĺ���ģʽ
	//			0x00  �Զ�����ģʽ
	//			0x01  ָ���ѯģʽ
	//			0x02  �����Զ�����ģʽ
	//			0x03  ����ָ���ѯģʽ
	//			0x20  ��Ƶ����ģʽ����Ƶ�����޵����ز�
	//			0x21 ��Ƶ����ģʽ����Ƶ��ʽ�����޵����ز�
	//			0x22 ��Ƶ����ģʽ�������ʲ��������ģʽ
	//			0x23 ��Ƶ����ģʽ�������ʲ����뷢��ģʽ
	//			����  �������Ƿ�����

	//		nUpLoadIDType:	���ñ�ǩ����������ʽ�·��͵�ID����
	//			0x00  ��ǩ��������ģʽ�·���BID
	//			0x01  ��ǩ��������ģʽ�·���UID
	//			����  �������Ƿ�����

	//		nSleepTime: ˯��ʱ�䣺�����ǩ�����������Ĺ���ģʽ�±�ǩ˯��ʱ�䣬2�ֽڣ�
	//					˯��ʱ�䲽��Ϊ100mS���˯��ʱ��Ϊ6553500mS��

	//		nSleepInterval:���������������Ĺ���ģʽ�±�ǩ˯�߼��ʱ�䣬
	//						��ǩ��������ʽʱ���ò�����Ϊ��ǩ������������ʱ�䣬
	//						��ǩ�ڱ�����ʽʱ���ò��������ǩ�̴���ռ���ǩ��Ӧʱ�䣬
	//						˯�߼������Ϊ1mS���˯�߼��ʱ��Ϊ255mS��

	//����ֵ�� trueΪ�����ɹ�, falseΪ����ʧ��
	//////////////////////////////////////////////////////////////////////////
	bool  RFID_API  STDCALL SAAT_YTagWorkModeSet (void *pHandle, 
		unsigned char nOpType, 
		unsigned char nIDType, 
		unsigned char *pIDCode,
		unsigned char *pTagPwd,
		unsigned char nWorkMode,
		unsigned char nUpLoadIDType,
		unsigned short nSleepTime,
		unsigned char nSleepInterval);


	//////////////////////////////////////////////////////////////////////////
	//5.5  ��ǩ����ģʽ��ѯָ��
	//���ܣ���ǩ����ģʽ��ѯָ��
	//������ 
	//		pHandle: 		Ϊ�Ѿ���ʼ���Ķ˿ھ��
	//		nOpType:		ִ��ģʽ
	//		nIDType:		ID����,ִ��EAS��־��λ��ID��������
	//		pIDCode:		ID����
	//		nTagPwd:		��ǩ��������
	//		*pWorkMode:		ִ�����ñ�ǩ�Ĺ���ģʽ
	//			0x00  �Զ�����ģʽ
	//			0x01  ָ���ѯģʽ
	//			0x02  �����Զ�����ģʽ
	//			0x03  ����ָ���ѯģʽ
	//			0x20  ��Ƶ����ģʽ  ��Ƶ�����޵����ز�
	//			0x21  ��Ƶ����ģʽ  ��Ƶ��ʽ�����޵����ز�
	//			0x22  ��Ƶ����ģʽ  �����ʲ��������ģʽ
	//			0x23  ��Ƶ����ģʽ  �����ʲ����뷢��ģʽ
	//			����   �������Ƿ�����

	//		*pUpLoadIDType:	���ñ�ǩ����������ʽ�·��͵�ID����
	//			0x00  ��ǩ��������ģʽ�·���BID
	//			0x01  ��ǩ��������ģʽ�·���UID
	//			����  �������Ƿ�����

	//		*pSleepTime: ˯��ʱ�䣺�����ǩ�����������Ĺ���ģʽ�±�ǩ˯��ʱ�䣬2�ֽڣ�
	//					˯��ʱ�䲽��Ϊ100mS���˯��ʱ��Ϊ6553500mS��

	//		*pSleepInterval:���������������Ĺ���ģʽ�±�ǩ˯�߼��ʱ�䣬
	//						��ǩ��������ʽʱ���ò�����Ϊ��ǩ������������ʱ�䣬
	//						��ǩ�ڱ�����ʽʱ���ò��������ǩ�̴���ռ���ǩ��Ӧʱ�䣬
	//						˯�߼������Ϊ1mS���˯�߼��ʱ��Ϊ255mS��

	//		*pBatteryVoltage:
	//			��ص�ѹ�������ǩ���õ�صĵ�ѹ��
	//			���ݱ�ǩ����AD�ɼ���ѹֵ���ر�ǩ��ǰ��ص�ѹֵ��ǩ�ĵ�ص�ѹ��
	//			����ֵ����0.1V��Ϊ��ص�ѹ��
	//		*pRemainingCapacity:ʣ������������ǩ���õ�ص�ʣ��������԰ٷֱȱ�ʾ��
	//����ֵ�� trueΪ�����ɹ�, falseΪ����ʧ��
	//////////////////////////////////////////////////////////////////////////
	bool  RFID_API  STDCALL SAAT_YTagWorkModeQuery (void *pHandle, 
		unsigned char nOpType, 
		unsigned char nIDType, 
		unsigned char *pIDCode,
		unsigned char *pTagPwd,
		unsigned char *pWorkMode,
		unsigned char *pUpLoadIDType,
		unsigned short *pSleepTime,
		unsigned char *pSleepInterval,
		unsigned char *pBatteryVoltage,
		unsigned char *pRemainingCapacity);


	//////////////////////////////////////////////////////////////////////////
	//5.6  ��ǩ������������ָ��(ָ���֣�0x75H)
	//���ܣ���ǩ������������ָ��(ָ���֣�0x75H)
	//������ 
	//		pHandle: 		Ϊ�Ѿ���ʼ���Ķ˿ھ��
	//		nOpType:		ִ��ģʽ
	//		nIDType:		ID����,ִ��EAS��־��λ��ID��������
	//		pIDCode:		ID����
	//		nTagPwd:		��ǩ��������
	//		nTagType:��ǩ���ͣ������ǩ�ͺż����͡�
	//			0x01  SAAT-T501��ǩ
	//			0x02  SAAT-T502��ǩ
	//			0x03  SAAT-T503��ǩ
	//			0x04  SAAT-T504��ǩ
	//			����  δ���壬��������
	//		nHardWareVersion:
	//			Ӳ���汾�������ǩ����Ӳ����·�汾�š���4λ����Ӳ���汾���ţ����ֽڶ�Ӳ���汾�κţ���汾Ϊ1.0��1.1��2.2�������£�
	//			0x10  ��ǩӲ���汾��Ϊ1.0�汾
	//			0x11  ��ǩӲ���汾��Ϊ1.1�汾
	//			0x22  ��ǩӲ���汾��Ϊ2.2�汾
	//		nSoftWareVersion:
	//			����汾�������ǩ��������汾�š���4λ��������汾���ţ����ֽڶ�����汾�κţ���汾Ϊ1.0��1.1��2.2�������£�
	//			0x10  ��ǩ����汾��Ϊ1.0�汾
	//			0x11  ��ǩ����汾��Ϊ1.1�汾
	//			0x22  ��ǩ����汾��Ϊ2.2�汾 
	//		nBatteryConfiguration:
	//			������ã������ǩ���õ�ص��ͺţ���ͬ�ı�ǩ���ò�ͬ���,�������£�
	//			0x01  SAAT-T501��ǩ��أ��������750mA���ͺ�CP224147
	//			0x02  SAAT-T502��ǩ��أ��������550mA���ͺ�CR3032
	//			0x03  SAAT-T503��ǩ��أ��������450mA���ͺ�CR2450
	//			0x04  SAAT-T504��ǩ��أ��������1600mA���ͺ�ER14505S
	//			����  δ���壬��������
	//		nNominalCapacity:
	//			��������������ǩ���õ�صı��������
	//����������嵥λΪ50mA�������ǩ����������Ϊ12750mA.
	//���ǩ�����õĵ��Ϊ1000mA����ֵΪʮ��������0x14��0x14Ϊʮ������20
	//����ֵ�� trueΪ�����ɹ�, falseΪ����ʧ��
	//////////////////////////////////////////////////////////////////////////
	bool  RFID_API  STDCALL SAAT_YTagFatorySet (void *pHandle, 
		unsigned char nOpType, 
		unsigned char nIDType, 
		unsigned char *pIDCode,
		unsigned char *pTagPwd,
		unsigned char nTagType,
		unsigned char nHardWareVersion,
		unsigned char nSoftWareVersion,
		unsigned char nBatteryConfiguration,
		unsigned char nNominalCapacity);


	//////////////////////////////////////////////////////////////////////////
	//5.7 ��ǩ�������ò�ѯָ��(ָ���֣�0x75H)
	//���ܣ���ǩ�������ò�ѯָ��(ָ���֣�0x75H)
	//������ 
	//		pHandle: 		Ϊ�Ѿ���ʼ���Ķ˿ھ��
	//		nOpType:		ִ��ģʽ
	//		nIDType:		ID����,ִ��EAS��־��λ��ID��������
	//		pIDCode:		ID����
	//		nTagPwd:		��ǩ��������
	//		*pTagType:��ǩ���ͣ������ǩ�ͺż����͡�
	//			0x01  SAAT-T501��ǩ
	//			0x02  SAAT-T502��ǩ
	//			0x03  SAAT-T503��ǩ
	//			0x04  SAAT-T504��ǩ
	//			����  δ���壬��������
	//		*pHardWareVersion:
	//			Ӳ���汾�������ǩ����Ӳ����·�汾�š���4λ����Ӳ���汾���ţ����ֽڶ�Ӳ���汾�κţ���汾Ϊ1.0��1.1��2.2�������£�
	//			0x10  ��ǩӲ���汾��Ϊ1.0�汾
	//			0x11  ��ǩӲ���汾��Ϊ1.1�汾
	//			0x22  ��ǩӲ���汾��Ϊ2.2�汾
	//		*pSoftWareVersion:
	//			����汾�������ǩ��������汾�š���4λ��������汾���ţ����ֽڶ�����汾�κţ���汾Ϊ1.0��1.1��2.2�������£�
	//			0x10  ��ǩ����汾��Ϊ1.0�汾
	//			0x11  ��ǩ����汾��Ϊ1.1�汾
	//			0x22  ��ǩ����汾��Ϊ2.2�汾 
	//		*pBatteryConfiguration:
	//			������ã������ǩ���õ�ص��ͺţ���ͬ�ı�ǩ���ò�ͬ���,�������£�
	//			0x01  SAAT-T501��ǩ��أ��������750mA���ͺ�CP224147
	//			0x02  SAAT-T502��ǩ��أ��������550mA���ͺ�CR3032
	//			0x03  SAAT-T503��ǩ��أ��������450mA���ͺ�CR2450
	//			0x04  SAAT-T504��ǩ��أ��������1600mA���ͺ�ER14505S
	//			����  δ���壬��������
	//		*pNominalCapacity:
	//			��������������ǩ���õ�صı��������
	//����������嵥λΪ50mA�������ǩ����������Ϊ12750mA.
	//���ǩ�����õĵ��Ϊ1000mA����ֵΪʮ��������0x14��0x14Ϊʮ������20
	//����ֵ�� trueΪ�����ɹ�, falseΪ����ʧ��
	//////////////////////////////////////////////////////////////////////////
	bool  RFID_API  STDCALL SAAT_YTagFatoryQuery (void *pHandle, 
		unsigned char nOpType, 
		unsigned char nIDType, 
		unsigned char *pIDCode,
		unsigned char *pTagPwd,
		unsigned char *pTagType,
		unsigned char *pHardWareVersion,
		unsigned char *pSoftWareVersion,
		unsigned char *pBatteryConfiguration,
		unsigned char *pNominalCapacity);


	//////////////////////////////////////////////////////////////////////////
	//5.8 ��ǩ��ʼ����������ָ��
	//���ܣ�5.2 ��ǩ��ʼ����������ָ��
	//������ 
	//		pHandle: 		Ϊ�Ѿ���ʼ���Ķ˿ھ��
	//		nOpType:		ִ��ģʽ
	//		nIDType:		ID����,ִ��EAS��־��λ��ID��������
	//		pIDCode:		ID����
	//		nTagPwd:		��ǩ��������
	//		ָ��˵����ִ�и�ָ���Ժ󣬱�ǩִ�����²�����
	//		��Ƶ���������ò����ָ�Ϊ����Ĭ��ֵ��
	//		����ID���䣻
	//		��չID����ָ�Ϊȫ��0����
	//		�û����ݻָ�Ϊȫ��0����
	//		�û��������ָ�Ϊ�������뱣����״̬����δ������״̬��
	//		��������ָ�Ϊȫ��0����
	//		��������ָ�Ϊȫ��0����
	//����ֵ�� trueΪ�����ɹ�, falseΪ����ʧ��
	//////////////////////////////////////////////////////////////////////////
	bool  RFID_API  STDCALL SAAT_YTagResetToFatory (void *pHandle, 
		unsigned char nOpType, 
		unsigned char nIDType, 
		unsigned char *pIDCode,
		unsigned char *nTagPwd);
	

	//////////////////////////////////////////////////////////////////////////
	//5.9 ��Դ��Ƶ�˿ڲ�������
	//���ܣ�����������Դ��д���Ĳ��������Ƶ�˿ڲ���
	//������
	//		pHandle:	�򿪵Ķ˿ھ��
	//		pPara:		���ö�д���Ĳ��������Ƶ�˿ڲ��� 
	//		nLen: 		��������, 12�ֽ�
	//����ֵ�� trueΪ�����ɹ�, falseΪ����ʧ��
	//////////////////////////////////////////////////////////////////////////
	bool RFID_API  STDCALL SAAT_YAntennaParmSet(void* pHandle ,unsigned char *pPara,unsigned char nLen );

	//////////////////////////////////////////////////////////////////////////
	//6.0 ��Դ��Ƶ�˿ڲ�����ѯ
	//���ܣ����ڲ�ѯ��Դ��д���Ĳ��������Ƶ�˿ڲ���
	//������
	//		pHandle:			�򿪵Ķ˿ھ��
	//		pPowerRecvPlus:		���Ž�������
	//				0x02:	������
	//				0x03:	������
	//		p2401FreqSendPwr:	2401��Ƶ�������͹���
	//				0x00:	-18DB
	//				0x01:	-12DB
	//				0x02:	-6DB
	//				0x03:	0DB
	//		pAttenuatorPower:	��Ƶ˥��������
	//				0x00:	0DB
	//				0x01:	-1DB
	//				0x02:	-2DB
	//				0x03:	-3DB
	//				0x04:	-4DB
	//				0x05:	-5DB
	//				0x06:	-6DB
	//				0x07:	-7DB
	//����ֵ�� trueΪ�����ɹ�, falseΪ����ʧ��
	//////////////////////////////////////////////////////////////////////////
	bool RFID_API  STDCALL SAAT_YAntennaParmQuery(void* pHandle,
		unsigned char *pPowerRecvPlus,
		unsigned char *p2401FreqSendPwr,
		unsigned char *pAttenuatorPower);

	//////////////////////////////////////////////////////////////////////////
	//6.1 ��Դ��д���ز���������
	//���ܣ��������ö�д�����ز�����
	//������
	//	pHandle:	�򿪵Ķ˿ھ��
	//	nType: 		���õ�Ƶ�ʱ�Ĳ������ͣ�Ϊ�ز����������ͣ�Ĭ��Ϊ0x00
	//	pPara: 		���õ�Ƶ�ʱ����
	//		0		2405MHZ
	//		1		2410MHZ
	//		2		2415MHZ
	//		3		2420MHZ
	//		��
	//		23		2520MHZ
	//����ֵ�� trueΪ�����ɹ�, falseΪ����ʧ��
	//////////////////////////////////////////////////////////////////////////
	bool RFID_API  STDCALL SAAT_YRFParaSet (void* pHandle ,
		unsigned char nType, 
		unsigned char nPara);


	//////////////////////////////////////////////////////////////////////////
	//6.2 ��Դ��д���ز�������ѯ
	//���ܣ����ڲ�ѯ��д�����ز�����
	//������
	//	pHandle:	�򿪵Ķ˿ھ��
	//	nType: 		���õ�Ƶ�ʱ�Ĳ������ͣ�Ϊ�ز����������ͣ�Ĭ��Ϊ0x00
	//	pPara: 		���õ�Ƶ�ʱ����
	//		0		2405MHZ
	//		1		2410MHZ
	//		2		2415MHZ
	//		3		2420MHZ
	//		��
	//		23		2520MHZ
	//����ֵ�� trueΪ�����ɹ�, falseΪ����ʧ��
	//////////////////////////////////////////////////////////////////////////
	bool RFID_API  STDCALL SAAT_YRFParaQuery (void* pHandle ,
		unsigned char nType,
		unsigned char* pPara);


	//////////////////////////////////////////////////////////////////////////
	//6.3 ��Դ�ز�����
	//���ܣ����ڿ��ƶ�д�����ز����򿪻�ر��ز�����ָ���˿������
	//������
	//		pHandle :		�򿪵Ķ˿ھ��
	//		nType:
	//			0x00		�ر��ز�
	//			0x01		���ز�
	//����ֵ�� trueΪ�����ɹ�, falseΪ����ʧ��
	//////////////////////////////////////////////////////////////////////////
	bool RFID_API  STDCALL SAAT_YCarrierWaveOp(void* pHandle ,unsigned char nType);


	//////////////////////////////////////////////////////////////////////////
	//6.4 ��Դ��д������������
	//���ܣ��������ö�д�������÷������Ƿ�����
	//������
	//	pHandle:	�򿪵Ķ˿ھ��
	//	nPara: 		�������������
	//		0x00	��ֹ����������
	//		0x01	�򿪷���������
	//����ֵ�� trueΪ�����ɹ�, falseΪ����ʧ��
	//////////////////////////////////////////////////////////////////////////
	bool RFID_API  STDCALL SAAT_YBuzzerSet (void* pHandle , unsigned char nPara);


	//////////////////////////////////////////////////////////////////////////
	//6.5 ��Դ��д����������ѯ
	//���ܣ����ڲ�ѯ��д�������÷�����״̬
	//������
	//	pHandle:	�򿪵Ķ˿ھ��
	//	pPara: 		��ѯ���������
	//����ֵ�� trueΪ�����ɹ�, falseΪ����ʧ��
	//////////////////////////////////////////////////////////////////////////
	bool RFID_API  STDCALL SAAT_YBuzzerQuery (void* pHandle ,	unsigned char* pPara);


	//////////////////////////////////////////////////////////////////////////
	//6.6 ������ԴID������
	//���ܣ����ڽ���ID��, ID��Ϊ8λʮ����
	//����:
	//		pHandle 	Ϊ�Ѿ���ʼ���Ķ˿ھ��
	//		pId			Ϊʮ����int��ID, 
	//		nBit		Ϊ��ǩ���
	//��	����	��ǩID����	ʡ����	���б��	�������	�������	��ѹ���
	//λ	2	       1           1	       1         	1	       1	       1
	//����ֵ�� 1Ϊ�����ɹ�, 0Ϊ����ʧ��
	//////////////////////////////////////////////////////////////////////////
	int RFID_API  STDCALL SAAT_YRevIDMsgDec(void *pHandle, unsigned int* pId, unsigned char* nBit);


	//////////////////////////////////////////////////////////////////////////
	//6.7 ������ԴID������
	//���ܣ����ڽ���ID��, ID��Ϊ4λ(��4�ֽ�)ʮ������
	//����:
	//		pHandle 	Ϊ�Ѿ���ʼ���Ķ˿ھ��
	//		pIDData		ΪID����, 
	//		nIDLen		ΪID���ݳ���
	//		nBit		Ϊ��ǩ���
	//��	����	��ǩID����	ʡ����	���б��	�������	�������	��ѹ���
	//λ	2	       1           1	       1         	1	       1	       1
	//����ֵ�� 1Ϊ�����ɹ�, 0Ϊ����ʧ��
	//////////////////////////////////////////////////////////////////////////
	int RFID_API  STDCALL SAAT_YRevIDMsgHex(void *pHandle, 
		unsigned char* pIDData,
		unsigned char* nIDLen, 
		unsigned char* nBit);



	//////////////////////////////////////////////////////////////////////////
	//6.8 ���ñ�������ID��
	//���ܣ�������������, ���ش������ʱ������Ӧ��������ʾ
	//����:
	//		nLangId 	Ϊ�Ѿ���ʼ���Ķ˿ھ��
	//			ZH_CN = 0,
	//			ZH_TW = 1,
	//			EN_US = 2
	//����ֵ�� trueΪ�����ɹ�, falseΪ����ʧ��
	//////////////////////////////////////////////////////////////////////////
	bool RFID_API STDCALL SAAT_SetLangId(void *pHandle, unsigned char nLangId);

	//////////////////////////////////////////////////////////////////////////
	//6.9 ��д��ϵͳ�����ú���
	//���ܣ�ֱ�ӷ��͵ײ�����(���ڲ��Զ�д���Զ����������ݴ�������)
	//������
	//	pHandle:		�򿪵Ķ˿ھ��
	//	pSendData: 		��������
	//	nLen:			���ݳ���	
	//����ֵ�� trueΪ�����ɹ�, falseΪ����ʧ��
	//////////////////////////////////////////////////////////////////////////
	bool RFID_API  STDCALL SAAT_RawSendData(void* pHandle , unsigned char *pSendData, unsigned char nLen); 

	//////////////////////////////////////////////////////////////////////////
	//7.0 ֱ����ȡ�ײ�����
	//���ܣ�ֱ����ȡ�ײ�����
	//������
	//	pHandle:		�򿪵Ķ˿ھ��
	//	pTestParm: 		��������
	//	nLen:			���ݳ���	
	//	nWaitTime       ��ʱʱ��
	//����ֵ�� trueΪ�����ɹ�, falseΪ����ʧ��
	//////////////////////////////////////////////////////////////////////////
	bool RFID_API  STDCALL SAAT_RawRevData(void* pHandle , unsigned char *pRecvData, unsigned char* pLen,int nWaitTime); 

	//////////////////////////////////////////////////////////////////////////
	//7.1 ֱ�ӷ��Ͳ���ȡ�ײ�����
	//���ܣ�ֱ�ӷ��Ͳ���ȡ�ײ�����
	//������
	//	pHandle:		�򿪵Ķ˿ھ��
	//	pSendData: 		��������
	//	nLen:			�������ݳ���	
	//  pRecvData		��������
	//	pLen			�������ݳ���
	//  nWaitTime       ��ʱʱ��
	//����ֵ�� trueΪ�����ɹ�, falseΪ����ʧ��
	//////////////////////////////////////////////////////////////////////////
	bool RFID_API  STDCALL SAAT_RawSendAndRevData(void* pHandle , 
		unsigned char *pSendData,
		unsigned char nLen,
		unsigned char *pRecvData,
		unsigned char *pLen,
		unsigned char nWaitTime); 

	//////////////////////////////////////////////////////////////////////////
	// 7.2 ��д��ʱ������
	//���ܣ��������ö�д��ʱ��
	//������
	//		pHandle :	�򿪵Ķ˿ھ��
	//		pPara:		��д�����صĶ�д��ʱ������
	//		pLen:		�������ݳ���
	//����ֵ�� trueΪ�����ɹ�, falseΪ����ʧ��
	//////////////////////////////////////////////////////////////////////////
	bool RFID_API  STDCALL SAAT_SetReaderTime (void* pHandle ,unsigned char* pPara,unsigned char nLen);

	//////////////////////////////////////////////////////////////////////////
	// 7.3 ��д��ʱ���ѯ
	//���ܣ����ڲ�ѯ��д��ʱ��
	//������
	//		pHandle :	�򿪵Ķ˿ھ��
	//		pPara:		��д�����صĶ�д��ʱ������
	//		pLen:		�������ݳ���
	//����ֵ�� trueΪ�����ɹ�, falseΪ����ʧ��
	//////////////////////////////////////////////////////////////////////////
	bool RFID_API  STDCALL SAAT_ReaderTimeQuery (void* pHandle, unsigned char* pPara, unsigned char *pLen);

	//////////////////////////////////////////////////////////////////////////
	// 7.4 Flash���������ѯ
	//���ܣ����������ѯ
	//������
	//		pHandle :	�򿪵Ķ˿ھ��
	//		pPara:		
	//		pLen:		�ܼ���
	//����ֵ�� trueΪ�����ɹ�, falseΪ����ʧ��
	//////////////////////////////////////////////////////////////////////////
	bool RFID_API  STDCALL SAAT_FlashTotalCountQuery (void* pHandle ,
		unsigned char* pPara,
		unsigned char *pLen);

	//////////////////////////////////////////////////////////////////////////
	// 7.5 Flash�������ݲ�ѯ
	//���ܣ����������ѯ
	//������
	//		pHandle :	�򿪵Ķ˿ھ��
	//		nOpType :
	//		pPara:	
	//		pLen:		�ܼ���
	//����ֵ�� trueΪ�����ɹ�, falseΪ����ʧ��
	//////////////////////////////////////////////////////////////////////////
	bool RFID_API  STDCALL SAAT_FlashDataQuery (void* pHandle ,
		unsigned char nOpType,
		unsigned char* pPara,
		unsigned char *pLen);

	//////////////////////////////////////////////////////////////////////////
	// 7.6 Flash�����������
	//���ܣ����������ѯ
	//������
	//		pHandle :	�򿪵Ķ˿ھ��
	//����ֵ�� trueΪ�����ɹ�, falseΪ����ʧ��
	//////////////////////////////////////////////////////////////////////////
	bool RFID_API STDCALL SAAT_ClearFlash (void* pHandle );


	//////////////////////////////////////////////////////////////////////////
	//7.7 WIFIͨѶ��������
	//���ܣ���������WIFIģ��ͨѶ����
	//������
	//	pHandle : 	�򿪵Ķ˿ھ��
	//	nType: 	���õĲ�������
	//			�����͡�Ϊ���õĲ������ͣ�������
	//			0		WIFIģ�鴮��ͨ�Ų�����
	//			1		WIFIģ��MAC��ַ
	//			2		WIFIģ��IP��ַ
	//			3		WIFIģ��TCP�˿ں�
	//			4		WIFIģ��UDP�˿ں� 
	//	pPara:		����
	//	nLen:		�������� ���ݶ���Ϊ��
	//				0x00		4800bps
	//				0x01		9600 bps
	//				0x02		19200
	//				0x03		38400
	//				0x04		57600
	//				0x05		115200
	//����ֵ�� trueΪ�����ɹ�, falseΪ����ʧ��
	//////////////////////////////////////////////////////////////////////////
	bool RFID_API STDCALL SAAT_WCommunicatParaSet (void* pHandle ,unsigned char nType, unsigned char* pPara, unsigned char nLen);


	//////////////////////////////////////////////////////////////////////////
	//7.8 WIFIͨѶ������ѯ
	//���ܣ����ڲ�ѯWIFIģ���ͨѶ����
	//������
	//	pHandle : 	�򿪵Ķ˿ھ��
	//	nType: 	���õĲ�������
	//			�����͡�Ϊ���õĲ������ͣ�������
	//			0		WIFIģ�鴮��ͨ�Ų�����
	//			1		WIFIģ��MAC��ַ
	//			2		WIFIģ��IP��ַ
	//			3		WIFIģ��TCP�˿ں�
	//			4		WIFIģ��UDP�˿ں� 
	//	pPara:		����
	//	nLen:		�������� ���ݶ���Ϊ��
	//				0x00		4800bps
	//				0x01		9600 bps
	//				0x02		19200
	//				0x03		38400
	//				0x04		57600
	//				0x05		115200
	//����ֵ�� trueΪ�����ɹ�, falseΪ����ʧ��
	//////////////////////////////////////////////////////////////////////////
	bool RFID_API STDCALL SAAT_WCommunicatParaQuery (void* pHandle ,unsigned char nType, unsigned char* pPara,unsigned char *pLen);

	//////////////////////////////////////////////////////////////////////////
	//7.9 ������д��
	//�����������˺�����������������д����
	//����ԭ�ͣ�
	//bool	SAAT_Reboot(void* pHandle,unsigned char nMode)
	//���������
	//pHandle		�򿪵Ķ˿ھ��	
	//nMode			����ģʽ
	//0x00  ��ͨģʽ
	//0x01  BOOT����ģʽ��������RFID�豸������BOOTָ��
	//����ֵ��true�������ɹ���false������ʧ�ܡ�
	//////////////////////////////////////////////////////////////////////////
	bool RFID_API STDCALL SAAT_Reboot(void* pHandle ,unsigned char nType);

	//////////////////////////////////////////////////////////////////////////
	//8.0 ��Դ��ǩѡ������
	//���ܣ� ��Դ��ǩѡ������
	//����:
	//		pHandle: ΪIConnectָ��
	//      nOpEnable:LED�� ��������ʹ��
	//		nMatchType: ƥ��ģʽ, 
	//		MatchData: ƥ������
	//����ֵ�� trueΪ�����ɹ�, falseΪ����ʧ��
	//////////////////////////////////////////////////////////////////////////
	bool RFID_API  __stdcall SAAT_YTagSelect ( void *pHandle, unsigned char nOpEnable, unsigned char nMatchType, unsigned char *MatchData, unsigned char nLenth);

	//////////////////////////////////////////////////////////////////////////
	//8.1 ��д�����ý���͸��ģʽ�ú�����WIFI�豸���ã�
	//���ܣ���д�����ý���͸��ģʽ
	//������
	//	pHandle:		�򿪵Ķ˿ھ��
	//	nType: 			���Ͳ������� 0x00-WIFI  0xFD ��λ������SAAT_ResetWifiBaund
	//����ֵ�� trueΪ�����ɹ�, falseΪ����ʧ��
	//////////////////////////////////////////////////////////////////////////
	bool RFID_API STDCALL SAAT_EnterTrans(void* pHandle ,unsigned char nType);

	//////////////////////////////////////////////////////////////////////////
	//8.2 ��д��WIFI���ò����ʺ���(WIFI�豸����)
	//���ܣ���������WIFI������
	//������
	//	pHandle:		�򿪵Ķ˿ھ��
	//����ֵ�� trueΪ�����ɹ�, falseΪ����ʧ��
	//////////////////////////////////////////////////////////////////////////
	bool RFID_API STDCALL SAAT_ResetWifiBaund(void* pHandle);

	//�¶ȱ�ǩ
	//////////////////////////////////////////////////////////////////////////
	// 8.3������ԴID������
	//���ܣ����ڽ���ID��, ID��Ϊʮ����
	//����:
	//		pHandle 	Ϊ�Ѿ���ʼ���Ķ˿ھ��
	//      nTagType		Ϊ��ǩ��ǣ�0x00��ʾ��ͨ��ǩ��0x01��ʾ�¶ȱ�ǩ��0x02��ʾ������ǩ
	//		pId			Ϊʮ����int��ID,
	//		nBit		Ϊ��ǩ���
	//					��	����	��ǩID����	ʡ����	���б��	�������	�������	��ѹ���
	//					λ	2	       1           1	       1         	1	       1	       1
	//      nParam1		�¶ȱ�ǩ���� or ������ַ
	//      nParam2		�¶ȱ�ǩС�� or ��ǿǿ��
	//����ֵ�� 1Ϊ�����ɹ�, 0Ϊ����ʧ��
	//////////////////////////////////////////////////////////////////////////
	//int RFID_API STDCALL SAAT_YRevIDMsgDecTemperature(void *pHandle,unsigned char* nTagType,unsigned int* pId,unsigned char* pBit, unsigned char* nParam1, unsigned char* nParam2);
	int RFID_API STDCALL SAAT_YRevIDMsgDecExpand(void *pHandle,unsigned char* nTagType,unsigned int* pId,unsigned char* pBit, int* nParam1, int* nParam2);

	//////////////////////////////////////////////////////////////////////////
	//8.4 ������ԴID������
	//���ܣ����ڽ���ID��, ID��Ϊ4λ(��4�ֽ�)ʮ������
	//����:
	//		pHandle 	Ϊ�Ѿ���ʼ���Ķ˿ھ��
	//      nFlag		Ϊ��ǩ��ǣ�0x00��ʾ��ͨ��ǩ��0x01��ʾ�¶ȱ�ǩ��0x02��ʾ������ǩ
	//		pIDData		ΪID����, 
	//		nIDLen		ΪID���ݳ���
	//		nBit		Ϊ��ǩ���
	//					��	����	��ǩID����	ʡ����	���б��	�������	�������	��ѹ���
	//					λ	2	       1           1	       1         	1	       1	       1
	//      nParam1		�¶ȱ�ǩ���� or ������ַ
	//      nParam2		�¶ȱ�ǩС�� or ��ǿǿ��
	//����ֵ�� 1Ϊ�����ɹ�, 0Ϊ����ʧ��
	//////////////////////////////////////////////////////////////////////////
	int RFID_API  STDCALL SAAT_YRevIDMsgHexExpand(void *pHandle, unsigned char* nTagType, unsigned char* pIDData, unsigned char* nIDLen, unsigned char* nBit, unsigned char* nParam1, unsigned char* nParam2);


	bool RFID_API STDCALL SAAT_GCommunicatParaSet (void* pHandle ,unsigned char nType, unsigned char* pPara, unsigned char nLen);

	bool RFID_API STDCALL SAAT_GCommunicatParaQuery (void* pHandle ,unsigned char nType, unsigned char* pPara,unsigned char *pLen);

	bool RFID_API STDCALL SAAT_SendTrans(void* pHandle,unsigned char nType,unsigned char* pData,unsigned char nLen);

	bool RFID_API STDCALL SAAT_RecvTrans(void* pHandle,unsigned char nType,unsigned char *pData,unsigned char* pLen);

	bool RFID_API STDCALL SAAT_ModuleReboot(void* pHandle ,unsigned char nType);


	/******************************���߼�����-start******************************************/
	/*
	6.1���߼�����ϵͳ���������-����
	��������	���߼�����ϵͳ���������-���á�
	����ԭ��	bool  SAAT_EncourageParmOpReset(void* pHandle,unsigned int nSNID)
	�������	pHandle	Ϊ�Ѿ���ʼ���Ķ˿ھ��
				nSNID	������SN
	����ֵ	true 	�����ɹ�
	false	����ʧ��	
	 **/
	bool RFID_API STDCALL SAAT_EncourageParmOpReset(void* pHandle,
		unsigned int nSNID);	

	/*
	 *6.2���߼�����ϵͳ���������-��
	��������	���߼�����ϵͳ���������-����
	����ԭ��	bool  SAAT_EncourageParmOpRead(void* pHandle,
												unsigned int nSNID,  
												unsigned int nStartAddrr,
												unsigned char nlen,
												unsigned char *pData)
	�������	pHandle	Ϊ�Ѿ���ʼ���Ķ˿ھ��
				nSNID	������SN
				nStartAddrr	�����������ַ
				nlen	��������
				pData	����
	����ֵ	true 	�����ɹ�
			false	����ʧ��

	 **/
	bool RFID_API STDCALL SAAT_EncourageParmOpRead(void* pHandle,
		unsigned int nSNID,  
		unsigned int nStartAddrr,
		unsigned char nlen,
		unsigned char *pData);	//���߼�����ϵͳ���������

	/*
	6.3���߼�����ϵͳ���������-д
	��������	���߼�����ϵͳ���������-����
	����ԭ��	bool  SAAT_EncourageParmOpWrite (void* pHandle,
											unsigned int nSNID,  
											unsigned int nStartAddrr,
											unsigned char nlen,
											unsigned char *pData)
	�������	pHandle	Ϊ�Ѿ���ʼ���Ķ˿ھ��
				nSNID	������SN
				nStartAddrr	�����������ַ
				nlen	��������
				pData	����
	����ֵ	true 	�����ɹ�
			false	����ʧ��


	 **/
	bool RFID_API STDCALL SAAT_EncourageParmOpWrite(void* pHandle,
		unsigned int nSNID,  
		unsigned int nStartAddrr,
		unsigned char nlen,
		unsigned char *pData);	//���߼�����ϵͳ���������

	/*
	6.4���߼�����ϵͳ���������-Ӧ��
	��������	���߼�����ϵͳ���������-Ӧ�á�
	����ԭ��	bool  SAAT_EncourageParmOpActive (void* pHandle,unsigned int nSNID)
	�������	pHandle	Ϊ�Ѿ���ʼ���Ķ˿ھ��
				nSNID	������SN
	����ֵ	true 	�����ɹ�
			false	����ʧ��
	 **/
	bool RFID_API STDCALL SAAT_EncourageParmOpActive(void* pHandle,
		unsigned int nSNID);	//���߼�����ϵͳ���������


	/*
	6.5���߼�����ϵͳ��Ϣ����
	��������	���߼�����ϵͳ��Ϣ���á�
	����ԭ��	bool  SAAT_EncourageSysInfSet (void* pHandle,
	unsigned int nSNID,
	unsigned char nType,
	unsigned char* pParm,
	int nLen)
	�������	pHandle	Ϊ�Ѿ���ʼ���Ķ˿ھ��
	nSNID	������SN
	nType	0x00-0x03 
	0x00�豸����
	0x01����
	0x02�豸���к�
	0x03�豸��ַ
	pParm	������	N	0x00~0xFF	�����������ݵĲ�ͬ�����ݳ��Ȳ�ͬ
	nLen	���ݳ���
	����ֵ	true 	�����ɹ�
	false	����ʧ��
	 **/
	bool RFID_API STDCALL SAAT_EncourageSysInfSet (void* pHandle,
		unsigned int nSNID,
		unsigned char nType,
		unsigned char* pParm,
		int nLen);//���߼�����ϵͳ��Ϣ����
	
	/************************************************************************/
	/* 6.6���߼�����ϵͳ��Ϣ��ѯ
	��������	���߼�����ϵͳ��Ϣ��ѯ��
	����ԭ��	bool  SAAT_SAAT_EncourageSysInfQuery (void* pHandle,
													unsigned int nSNID,
													unsigned char nType,
													unsigned char* pParm,
													int nLen)
	�������	pHandle	Ϊ�Ѿ���ʼ���Ķ˿ھ��
				nSNID	������SN
				nType	0x00-0x03 
				0x00�豸����
				0x01����
				0x02�豸���к�
				0x03�豸��ַ
				pPara	������	N	0x00~0xFF	�����������ݵĲ�ͬ�����ݳ��Ȳ�ͬ
				nLen	���ݳ���
	����ֵ	true 	�����ɹ�
			false	����ʧ��
                                                                     */
	/************************************************************************/
	bool RFID_API STDCALL SAAT_EncourageSysInfQuery (void* pHandle,
		unsigned int nSNID,
		unsigned char nType, 
		unsigned char *pPara, 
		unsigned char *pLen);//���߼�����ϵͳ��Ϣ��ѯ

	/************************************************************************/
	/* 6.7���߼���������
	��������	���߼�����������
	����ԭ��	bool  SAAT_EncourageReboot (void* pHandle,unsigned int nSNID)
	�������	pHandle	Ϊ�Ѿ���ʼ���Ķ˿ھ��
	nSNID	������SN
	����ֵ	true 	�����ɹ�
	false	����ʧ��
                                                                     */
	/************************************************************************/
	bool RFID_API STDCALL SAAT_EncourageReboot(void* pHandle,unsigned int nSNID);	//���߼���������

	/************************************************************************/
	/* 6.8��ʼ���߼������������
	��������	��ʼ���߼������������, ���յ��������м�������������Ϣ��
	����ԭ��	bool  SAAT_EncourageUpLoadHeartStart (void* pHandle)
	�������	pHandle	Ϊ�Ѿ���ʼ���Ķ˿ھ��
	����ֵ	true 	�����ɹ�
	false	����ʧ��

                                                                     */
	/************************************************************************/
	bool RFID_API STDCALL SAAT_EncourageUpLoadHeartStart (void* pHandle);	

	/************************************************************************/
	/* 6.9��ȡ����������
	��������	��ȡ������������
	����ԭ��	bool  SAAT_YReadEncourageHeart (void* pHandle,
	unsigned int nSNID,
	unsigned char nType,
	unsigned char* pParm,
	int nLen)
	�������	pHandle	Ϊ�Ѿ���ʼ���Ķ˿ھ��
	nSNID	������SN
	nState	����״̬
	0x00��������	����������״̬��������������
	pDeviceID	�豸ID��	
	0x00-0xfe	1�ֽڼ�����ID�ţ����������͸���ǩ��ID�š�
	pRate	������Ƶ�� 0-85	����������Ƶ��
	pTimeSpace	����ʱ����	2	200-65535	���������������������ݼ��ʱ��
	pPower	125k�������	1		��������ǰ���������
	����ֵ	true 	�����ɹ�
	false	����ʧ��
                                                                  */
	/************************************************************************/
	bool RFID_API STDCALL SAAT_YReadEncourageHeart(void* pHandle,
		unsigned int* pSNID,
		unsigned char* nState,
		unsigned char* pDeviceID,
		unsigned char* pRate,
		unsigned int* pTimeSpace,
		unsigned char* pPower);

	/************************************************************************/
	/* 6.10ֹͣ���߼������������
	��������	ֹͣ���߼�����������⡣
	����ԭ��	bool  SAAT_EncourageUpLoadHeartStop (void* pHandle)
	�������	pHandle	Ϊ�Ѿ���ʼ���Ķ˿ھ��
	����ֵ	true 	�����ɹ�
	false	����ʧ��
                                                                     */
	/************************************************************************/
	bool RFID_API STDCALL SAAT_EncourageUpLoadHeartStop (void* pHandle);	

	/******************************���߼�����-end******************************************/


	/******************************��ƿ������-start******************************************/
	/*
	 * ��ǩ1��Ӧ���ǩn  �� 
	 * */	

	/************************************************************************/
	/* ��ʼ��ȡ��ƿ����ǩ��
	��������	��ȡ��ƿ����ǩ��
	����ԭ��	bool  SAAT_ElectropileUpLoadCardStart (void* pHandle)
	�������	pHandle	Ϊ�Ѿ���ʼ���Ķ˿ھ��
	����ֵ	true 	�����ɹ�
	false	����ʧ��                       */
	/************************************************************************/
	bool RFID_API STDCALL SAAT_ElectropileUpLoadCardStart (void* pHandle);

	/************************************************************************/
	/* ֹͣ����                                                                     */
	/************************************************************************/
	bool RFID_API STDCALL SAAT_ElectropileStop (void* pHandle);

	/************************************************************************/
	/*���տ�                                                              */
	/************************************************************************/
	bool RFID_API STDCALL SAAT_YReadElectropileCard(void* pHandle,
		unsigned int* nSNID,//��id
		unsigned int* nPresonID,//����id
		unsigned char* nWarningMark,//�澯
		unsigned int* nPectral,//���ٶ�
		unsigned char* pObligate,//Ԥ������
		unsigned int* nObligateLen//Ԥ����������
		); //���տ�
	/************************************************************************/
	/*
	��ƿ����ǩ���������-����
	��������	��ƿ����ǩ���������-���á�
	����ԭ��	bool  SAAT_ElectropileParmOpReset(void* pHandle,unsigned int nSNID)
	�������	pHandle	Ϊ�Ѿ���ʼ���Ķ˿ھ��
				nSNID	��ǩid
				nStartAddr	������ʼλ��
				nLen   ��������
	����ֵ	true 	�����ɹ�
	false	����ʧ��	
	 **/
	/************************************************************************/
	bool RFID_API STDCALL SAAT_ElectropileParmOpReset(void* pHandle,
		unsigned int nSNID,
		unsigned int nStartAddr,
		unsigned int nLen);	

	/************************************************************************/
	/*��ƿ����ǩ���������-��
	��������	��ƿ����ǩ���������-����
	����ԭ��	bool  SAAT_ElectropileParmOpRead(void* pHandle,
												unsigned int nSNID,  
												unsigned int nStartAddrr,
												unsigned char nlen,
												unsigned char *pData)
	�������	pHandle	Ϊ�Ѿ���ʼ���Ķ˿ھ��
				nSNID	��ǩid
				nStartAddrr	�����������ַ
				nlen	��������
				pData	����
	����ֵ	true 	�����ɹ�
			false	����ʧ��
	*/
	 /************************************************************************/
	bool RFID_API STDCALL SAAT_ElectropileParmOpRead(void* pHandle,
		unsigned int nSNID,  
		unsigned int nStartAddr,
		unsigned char nlen,
		unsigned char *pData);	//���߼�����ϵͳ���������

	/*
	��ƿ����ǩ���������-д
	��������	��ƿ����ǩ���������-д��
	����ԭ��	bool  SAAT_ElectropileParmOpWrite (void* pHandle,
											unsigned int nSNID,  
											unsigned int nStartAddrr,
											unsigned char nlen,
											unsigned char *pData)
	�������	pHandle	Ϊ�Ѿ���ʼ���Ķ˿ھ��
				nSNID	��ǩid
				nStartAddrr	�����������ַ
				nlen	��������
				pData	����
	����ֵ	true 	�����ɹ�
			false	����ʧ��
	 **/
	bool RFID_API STDCALL SAAT_ElectropileParmOpWrite(void* pHandle,
		unsigned int nSNID,  
		unsigned int nStartAddrr,
		unsigned char nlen,
		unsigned char *pData);	//���߼�����ϵͳ���������

	/************************************************************************/
	/* �󶨳����ͳ���id     
	* ��������	�󶨳����ͳ���id ��
	����ԭ��	bool  SAAT_ElectropileBindingPreson (void* pHandle,
	unsigned int nSNID,  
	unsigned int nPresonID)
	�������	pHandle	Ϊ�Ѿ���ʼ���Ķ˿ھ��
	nSNID	��ǩid
	nPresonID	��Աid
	nKeyNum		�󶨱��
	����ֵ	true 	�����ɹ�
	false	����ʧ��*/
	/************************************************************************/
	bool RFID_API STDCALL SAAT_ElectropileBindingPreson(void* pHandle,
		unsigned int nSNID,  
		unsigned int nPresonID,
		unsigned int nKeyNum);

	/************************************************************************/
	/* �Ӵ��󶨳����ͳ���id     
	* ��������	�Ӵ��󶨳����ͳ���id ��
	����ԭ��	bool  SAAT_ElectropileReBindingPreson (void* pHandle,
	unsigned int nSNID,  
	unsigned int nPresonID)
	�������	pHandle	Ϊ�Ѿ���ʼ���Ķ˿ھ��
	nSNID	��ǩid
	nPresonID	��Աid
	nKeyNum		�󶨱��
	����ֵ	true 	�����ɹ�
	false	����ʧ��*/
	/************************************************************************/
	bool RFID_API STDCALL SAAT_ElectropileReBindingPreson(void* pHandle,
		unsigned int nSNID,  
		unsigned int nPresonID,
		unsigned int nKeyNum);

/************************************************************************/
	/* ��ѯ�󶨳����ͳ���id     
	* ��������	�Ӵ��󶨳����ͳ���id ��
	����ԭ��	bool  SAAT_ElectropileQueryBindingPreson (void* pHandle,
	unsigned int nSNID,  
	unsigned int* pPresonID,
	unsigned int* nCount)
	�������	pHandle	Ϊ�Ѿ���ʼ���Ķ˿ھ��
	nSNID	��ǩid
	nPresonID	��Աid (���� ����5)
	nCount		��ѯ���ĸ���
	����ֵ	true 	�����ɹ�
	false	����ʧ��*/
	/************************************************************************/
	bool RFID_API STDCALL SAAT_ElectropileQueryBindingPreson(
		void* pHandle,
		unsigned int nSNID,  
		unsigned int* pPresonID,
		unsigned int* nCount);
	/**********************************��ƿ������-end**************************************/

	bool RFID_API STDCALL SAAT_YAntennaPort_EXSet(void* pHandle,unsigned int nPortEnable,unsigned int nPollTime,unsigned int nParam); 
	bool RFID_API STDCALL SAAT_YAntennaPort_EXQuery(void* pHandle,unsigned int* nPortEnable,unsigned int* nPollTime,unsigned int* nParam); 

	//////////////////////////////////////////////////////////////////////////
	//8.4 ������ԴID��������չ
	//���ܣ����ڽ���ID��, ID��Ϊ4λ(��4�ֽ�)ʮ������
	//����:
	//		pHandle 	Ϊ�Ѿ���ʼ���Ķ˿ھ��
	//      nFlag		Ϊ��ǩ��ǣ�0x00��ʾ��ͨ��ǩ��0x01��ʾ�¶ȱ�ǩ��0x02��ʾ������ǩ,
	//					����λ��ʾ��չ���� ����0xF1��ʾ�¶ȱ�ǩ�ľ�����չ���� 
	//		pIDData		ΪID����, 
	//		nIDLen		ΪID���ݳ���
	//		nBit		Ϊ��ǩ���
	//					��	����	��ǩID����	ʡ����	���б��	�������	�������	��ѹ���
	//					λ	2	       1           1	       1         	1	       1	       1
	//      nParam1		�¶ȱ�ǩ���� or ������ַ
	//      nParam2		�¶ȱ�ǩС�� or ��ǿǿ��
	//      nParam3		RSSI 	
	//����ֵ�� 1Ϊ�����ɹ�, 0Ϊ����ʧ��
	//////////////////////////////////////////////////////////////////////////
	int RFID_API  STDCALL SAAT_YRevIDMsgDecRssiExpand(
		void *pHandle,
		unsigned char* nTagType,
		unsigned int* pId,
		int* nParam1,
		int* nRssi,
		int* nAntenna);


	bool RFID_API  __stdcall SAAT_Updata (void* pHandle,unsigned char nType ,int nFileLen ,unsigned char* pCRC32 ,unsigned char nFileNameLen ,unsigned char* pFileName);




#ifdef __cplusplus
}
#endif


#endif