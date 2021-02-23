#ifndef FIRMWAREUPDATEFOR6CDLG_H
#define FIRMWAREUPDATEFOR6CDLG_H

#include <QWidget>
#include <QThread>
#include "tcpclient.h"
#include "Lock.h"

namespace Ui {
class FirmWareUpdateFor6CDlg;
}

class QRadioButton;
class QPushButton;
class QLineEdit;
class QProgressBar;
class FirmWareUpdateFor6CThread;
class FirmWareUpdateFor6CDlg : public QWidget
{
    Q_OBJECT
    
public:
    explicit FirmWareUpdateFor6CDlg(QWidget *parent = 0);
    ~FirmWareUpdateFor6CDlg();
protected:
	void showEvent(QShowEvent *event); 
	void closeEvent(QCloseEvent *event);
private:
    Ui::FirmWareUpdateFor6CDlg *ui;
	QPushButton* mUpdateBtn;
	QPushButton* mQuitBtn;
	QRadioButton* mFirmWareRBtn;
	QRadioButton* mR2000RBtn;

	QLineEdit* mFileEdit;
	QPushButton* mBrowerBtn;
	QProgressBar* mProgressBar;

	unsigned char mUpdateType; //固件 1  r2000 0

	FirmWareUpdateFor6CThread* mFirmWareUpdateFor6CThread;
private:
	
private slots:
	void slot_UpdateBtnClicked();
	void slot_QuitBtnClicked();
	void slot_BrowerBtnCliecked();
	void slot_ResultUpdate(int nResult);
	void slot_SetBtnUp();
	void slot_SetBtnTransfer();
	
};

/************************************************************************/
/* 固件升级线程                                                                     */
/************************************************************************/
class FirmWareUpdateFor6CThread: public QThread
{
	Q_OBJECT
public:
	FirmWareUpdateFor6CThread(void);
	~FirmWareUpdateFor6CThread(void);
	bool StartUpdate(
		const QString& fileStr,
		unsigned char UpdateType	);
	bool isUpdateing();
//	bool StopUpdate();
private:
	void run();

	bool mIsStop;	//是否不在升级		
	CMyEvent mExitEvent;

	QString mFileStr;
	unsigned char mUpdateType; //固件 1  r2000 0

	TcpClient* mTcpClient;
private:	
	bool CheckFileAvail(const QString& fileStr,unsigned char* pFileBuff,int fileLen);
	bool CheckR2000File(const QString& fileStr,unsigned char* pFileBuff,int fileLen);
	bool CheckFirmWareFile(const QString& fileStr,unsigned char* pFileBuff,int fileLen);

	int GetFileBuff(const QString& fileStr,unsigned char* pFileBuff,int buffLen);
	unsigned int fast_crc32(unsigned int sum,unsigned char *p,unsigned int len);
	unsigned int swap32(UINT x);

	bool SendFileData(unsigned char* pFileBuff,int fileLen,const QString fileStr);

	int GetBockBuffFormFileBuff(unsigned char* pFileBuff,//文件buff
		int fileLen,//文件长度
		unsigned char* pBlockBuff,//块的缓存
		int BlockBuffLen,//缓存大小
		int Blocknum//块的序号
		);

	int MakeWRQ( char * const buf,
		int &buflength,
		const char * const filename,
		int namesize,int mode = 2);
	int getOpcode( char * const buf,
		int buflength,short &Opcode );		//用Opcode返回包类型
	int AnalyseACK( char * const buf,
		int buflength,
		short &Blocknum );	//用Blocknum返回确认包的编号
	int MakeACK( char * const buf,
		int &buflength,
		short Blocknum );
	int MakeDATA( char * const buf,
		int &buflength,
		short Blocknum ,
		const char * const data,
		int datasize);	//在buf开始的缓冲区中构造DATA包，

signals:
	//返回结果, -1 失败 ,100成功 ,0-100 是进度
	void resultReady(int nResult);
};

#endif // FIRMWAREUPDATEFOR6CDLG_H
