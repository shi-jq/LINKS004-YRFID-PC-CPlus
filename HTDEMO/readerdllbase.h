#ifndef READER_DLL_BASE_H
#define READER_DLL_BASE_H
#include <QString>
#include <wtypes.h>

enum ReaderState
{
	STATE_DISABLE,//不可用,只有初始化后,打开未成功才为这个状态
	STATE_DISCONNET,//未连接,打开后,断开的为这个状态
	STATE_CONNET,//连接,初始化,并打开成功
	STATE_READING//读卡
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
	QString mIpAddr;//ip地址
	int nPort;	//端口
	QString mComStr;//串口号
	int nBaudRate;//波特率
	ConnetType mconnetType;//连接类型
};

class ReaderDllBase
{
public:
	ReaderDllBase();
	~ReaderDllBase();
	bool ConnetReader();
	bool CloseReader();
	bool StopRead();//停止读卡
	bool ApiCopyright( char* copyright);
	int	GetErrorCode();//获取出错代码
	bool GetReaderType(QString &ReaderType);//获取读写器的类型

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
	HANDLE m_hCom;//读写器的handle 
	ReaderLinkInfo mLinkInfo;
	int mState;//读写器状态
	
};

#endif // READER_DLL_BASE_H
