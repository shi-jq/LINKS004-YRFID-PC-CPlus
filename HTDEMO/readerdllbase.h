#ifndef READER_DLL_BASE_H
#define READER_DLL_BASE_H
#include <QString>
#include <wtypes.h>

enum ReaderState
{
	STATE_DISABLE,//������,ֻ�г�ʼ����,��δ�ɹ���Ϊ���״̬
	STATE_DISCONNET,//δ����,�򿪺�,�Ͽ���Ϊ���״̬
	STATE_CONNET,//����,��ʼ��,���򿪳ɹ�
	STATE_READING//����
};

enum ConnetType
{
	Connet_TCP,
	Connet_COM,
	Connet_USB,
	Connet_UDP
};

struct ReaderLinkInfo
{
	QString mIpAddr;//ip��ַ
	int nPort;	//�˿�
	QString mComStr;//���ں�
	int nBaudRate;//������
	ConnetType mconnetType;//��������
};

class ReaderDllBase
{
public:
	ReaderDllBase();
	~ReaderDllBase();
	bool ConnetReader();
	bool CloseReader();
	bool StopRead();//ֹͣ����
	bool ApiCopyright( char* copyright);
	int	GetErrorCode();//��ȡ�������
	bool GetReaderType(QString &ReaderType);//��ȡ��д��������

	bool SetState(int readerState);
	int GetState();

	QString GetStateStr();
	bool CheckState(int readerState);	
	ReaderLinkInfo GetLinkInfo();

	void SetTcpConnetInfo(const QString ipAddr,int nPort);
	void SetComConnetInfo(const QString ComStr,int nBaudRate);
	void SetUdpConnetInfo(const QString ipAddr,int nPort);
	void SetUsbConnetInfo(const QString ComStr,int nBaudRate);
public:
	HANDLE m_hCom;//��д����handle 
	ReaderLinkInfo mLinkInfo;
	int mState;//��д��״̬
	
};

#endif // READER_DLL_BASE_H
