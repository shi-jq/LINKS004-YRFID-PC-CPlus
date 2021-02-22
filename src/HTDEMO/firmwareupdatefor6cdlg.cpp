#include "firmwareupdatefor6cdlg.h"
#include "ui_firmwareupdatefor6cdlg.h"
#include <QFileDialog>
#include <QFileInfo>
#include <assert.h>
#include <QCloseEvent>
#include "LanguageSrc.h"
#include "appconfig.h"
#include "mainapp.h"
#include "RFIDAPIEXPORT.h"
#include "readerdllbase.h"

const unsigned int crc32_table[256] = 
{
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

FirmWareUpdateFor6CDlg::FirmWareUpdateFor6CDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FirmWareUpdateFor6CDlg)
{
    ui->setupUi(this);
	this->setWindowTitle(GET_TXT("IDCS_FIRMWARE_UPDATE"));
	mUpdateBtn = ui->pushButton_2;
	mQuitBtn=ui->pushButton_3;
	mBrowerBtn=ui->pushButton;
	mFirmWareRBtn=ui->radioButton;
	mR2000RBtn=ui->radioButton_2;
	mFileEdit=ui->lineEdit;
	mProgressBar=ui->progressBar;

	mFirmWareRBtn->setChecked(true);
	ui->label_2->setText(GET_TXT("IDCS_UPDATE_FILE"));
	ui->label->setText(GET_TXT("IDCS_UPDATE_ITEM"));
	mUpdateBtn->setText(GET_TXT("IDCS_START_UPDATE"));
	mBrowerBtn->setText(GET_TXT("IDCS_BROWSE"));
	mFirmWareRBtn->setText(GET_TXT("IDCS_FIRMWARE"));

	mQuitBtn->setText(GET_TXT("IDCS_QUIT"));

	mFirmWareUpdateFor6CThread = new FirmWareUpdateFor6CThread();

	connect( mUpdateBtn, SIGNAL( clicked()), this, SLOT( slot_UpdateBtnClicked( ) ) );
	connect( mQuitBtn, SIGNAL( clicked()), this, SLOT( slot_QuitBtnClicked( ) ) );
	connect( mBrowerBtn, SIGNAL( clicked()), this, SLOT( slot_BrowerBtnCliecked( ) ) );
	connect( mFirmWareUpdateFor6CThread, SIGNAL( resultReady(int)), this, SLOT( slot_ResultUpdate( int ) ) ,Qt::QueuedConnection);
	connect( mFirmWareRBtn, SIGNAL( clicked()), this, SLOT( slot_SetBtnUp( ) ) );
	connect( mR2000RBtn, SIGNAL( clicked()), this, SLOT( slot_SetBtnUp( ) ) );

}

FirmWareUpdateFor6CDlg::~FirmWareUpdateFor6CDlg()
{
	if (mFirmWareUpdateFor6CThread)
	{
		delete mFirmWareUpdateFor6CThread;
		mFirmWareUpdateFor6CThread = NULL;
	}
    delete ui;
}

void FirmWareUpdateFor6CDlg::showEvent(QShowEvent *event)
{
	ReaderDllBase*	pReaderDllBase = pMainApp->GetReader();	
	if (!pReaderDllBase)
	{
		return;
	}

	if (pReaderDllBase->GetState() == STATE_READING ||
		pReaderDllBase->GetState() == STATE_DISCONNET ||
		pReaderDllBase->GetState() == STATE_DISABLE)
	{
		return;
	}
	mProgressBar->setValue(0);
	QWidget::showEvent(event);
}

void FirmWareUpdateFor6CDlg::closeEvent(QCloseEvent *event)
{
	if (mFirmWareUpdateFor6CThread->isUpdateing())
	{
		MainShowMsg(GET_TXT("IDCS_UPDATEING_WAIT"));
		event->ignore();
		return;
	}
	QWidget::closeEvent(event);
}

void FirmWareUpdateFor6CDlg::slot_UpdateBtnClicked()
{
	if (mFirmWareUpdateFor6CThread->isUpdateing())
	{
		MainShowMsg(GET_TXT("IDCS_UPDATEING_WAIT"));
		return ;
	}
	//选择文件
	QString fileStr = mFileEdit->text();
	if (fileStr.isEmpty())
	{
		MainShowMsg(GET_TXT("IDCS_PLEASE_SELECT_FILE"));
		return ;
	}
	mUpdateType = 0;
	if (mR2000RBtn->isChecked())
	{
		mUpdateType = 0;
	}
	else if (mFirmWareRBtn->isChecked())
	{
		mUpdateType = 1;
	}

	mFirmWareUpdateFor6CThread->StartUpdate(fileStr,mUpdateType);
}

void FirmWareUpdateFor6CDlg::slot_QuitBtnClicked()
{
	if (mFirmWareUpdateFor6CThread->isUpdateing())
	{
		MainShowMsg(GET_TXT("IDCS_UPDATEING_WAIT"));
		return;
	}

	//this->accept();
}

void FirmWareUpdateFor6CDlg::slot_BrowerBtnCliecked()
{
	QString fileName = QFileDialog::getOpenFileName(this,
		GET_TXT("IDCS_SELECT_FILE"), "./", tr("All Files (*.*)"));

	if(!fileName.isEmpty())
	{
		mFileEdit->setText(fileName);				
	}
}

void FirmWareUpdateFor6CDlg::slot_ResultUpdate(int nResult)
{
	if (nResult == 100)
	{
		MainShowMsg(GET_TXT("IDCS_FIRMWARE_UPDATE_SUCCESS"));
		if (mUpdateType != 2)
		{
			pMainApp->CutConnet();	//重启	
		}		
		mProgressBar->setValue (nResult);
		//this->accept();
		
	}
	else if (nResult == -1)
	{
		MainShowMsg(GET_TXT("IDCS_FIRMWARE_UPDATE_FAILED"),true);
		mProgressBar->setValue(0);
	}
	else 
	{
		mProgressBar->setValue (nResult);
	}
}

void FirmWareUpdateFor6CDlg::slot_SetBtnTransfer()
{
	mUpdateBtn->setText(GET_TXT("IDCS_START_TRANSFER"));
}

void FirmWareUpdateFor6CDlg::slot_SetBtnUp()
{
	mUpdateBtn->setText(GET_TXT("IDCS_START_UPDATE"));
}

/************************************************************************/
/* 固件升级线程                                                                     */
/************************************************************************/
FirmWareUpdateFor6CThread::FirmWareUpdateFor6CThread(void)
{
	mIsStop = true;
	mTcpClient = new TcpClient();
}

FirmWareUpdateFor6CThread::~FirmWareUpdateFor6CThread(void)
{
	if (mTcpClient)
	{
		delete mTcpClient;
		mTcpClient = NULL;
	}
}

bool FirmWareUpdateFor6CThread::StartUpdate(
	const QString& fileStr,
	unsigned char UpdateType)
{
	if (mIsStop == false)
	{
		return true;
	}
	mFileStr = fileStr;
	mUpdateType = UpdateType;

	mIsStop = false;
	this->start();
	return true;
}

//bool FirmWareUpdateFor6CThread::StopUpdate()
//{
//	if (mIsStop == true)
//	{
//		return true;
//	}
//	this->quit();
//	mIsStop = true;
//	mExitEvent.WaitEvent(3000);
//	this->wait();
//	return true;
//}

void FirmWareUpdateFor6CThread::run()
{
	bool bRet = false;
	int nResult = -1;
	if( !mIsStop )
	{
	
		//读取文件buff
		const int updataFileLen=1024*500;
		unsigned char updateBuff[updataFileLen] = {0};
		int realLen = GetFileBuff(mFileStr,updateBuff,updataFileLen);
		if (realLen == 0)
		{
			MainShowMsg(GET_TXT("IDCS_FILE_NOT_VALIDITY"));
			emit resultReady(-1);
			mIsStop = true; 
			return;
		}
		emit resultReady(10);
		//检查文件有效性
		if (!CheckFileAvail(mFileStr,updateBuff,realLen))
		{
			MainShowMsg(GET_TXT("IDCS_FILE_NOT_VALIDITY"));
			emit resultReady(-1);
			mIsStop = true;
			return;
		}
		emit resultReady(15);
		QFileInfo fi(mFileStr);
		mFileStr = fi.fileName(); 

		bRet = SendFileData(updateBuff,realLen,mFileStr);		
	}  

	mExitEvent.SetEvent();
	mIsStop = true;

	if (bRet)
	{
		nResult = 100;
	}
	else
	{
		nResult = -1;
	}

	emit resultReady(nResult);
}

bool FirmWareUpdateFor6CThread::isUpdateing()
{
	return !mIsStop;
}


bool FirmWareUpdateFor6CThread::CheckFileAvail(const QString& fileStr,unsigned char* pFileBuff,int fileLen)
{
	if (mUpdateType == 1)
	{
		return true;//CheckFirmWareFile(fileStr,pFileBuff,fileLen);
	}

	else if (mUpdateType == 0)
	{
		return true;//CheckR2000File(fileStr,pFileBuff,fileLen);
	}
	else if (mUpdateType == 2)
	{
		return true;
	}

	return false;
}

bool FirmWareUpdateFor6CThread::CheckR2000File(const QString& fileStr,unsigned char* pFileBuff,int fileLen)
{
	unsigned int nFileCrc32 = 0;
	unsigned char r2000FileCrc32[4]={0};

	// 计算文件CRC 32 
	nFileCrc32 =	fast_crc32(nFileCrc32,pFileBuff,fileLen-4);


	memcpy(r2000FileCrc32,&nFileCrc32,4);

	if (memcmp(r2000FileCrc32,pFileBuff+(fileLen-4),4))
	{
		return  false;
	}

	return true;
}

bool FirmWareUpdateFor6CThread::CheckFirmWareFile(const QString& fileStr,unsigned char* pFileBuff,int fileLen)
{
	if ((fileStr.compare(QString("f806.cfg.bk")))
		&& (  fileStr.compare(QString("f866.cfg.bk"))))
	{
		unsigned char checkFile[4]={0x7f,0x45,0x4c,0x46};
		if (memcmp(checkFile,pFileBuff,4))
		{
			return false;
		}
		else
		{
			return true;	
		}
	}

	return false;
}

unsigned int FirmWareUpdateFor6CThread::fast_crc32(unsigned int sum,unsigned char *p,unsigned int len)
{
	while (len--) 
	{
		sum = crc32_table[(sum >> 24) ^ *p++] ^ (sum << 8);
	}

	return sum;
}


unsigned int FirmWareUpdateFor6CThread::swap32(UINT x)
{
	return ((x & 0x000000FF) << 24) |
		((x & 0x0000FF00) << 8) |
		((x & 0x00FF0000) >> 8) |
		((x & 0xFF000000) >> 24);
}


int FirmWareUpdateFor6CThread::GetFileBuff(const QString& fileStr,unsigned char* pFileBuff,int buffLen)
{
	int nRet = 0;
	QFile file(fileStr);
	if (!file.open(QIODevice::ReadOnly))
		return nRet;
	QByteArray bytedata;
	bytedata = file.readAll();
	file.close();
	int readLen = bytedata.length();
	if (readLen > buffLen)
	{
		return nRet;
	}

	nRet = readLen;
	memcpy(pFileBuff,bytedata.data(),nRet);
	
	return nRet;
}

bool FirmWareUpdateFor6CThread::SendFileData(unsigned char* pFileBuff,int fileLen,const QString fileStr)
{
	bool bRet=false;
	ReaderDllBase*	pReaderDllBase = pMainApp->GetReader();	
	if (!pReaderDllBase)
	{
		MainShowMsg(GET_TXT("IDCS_READ_NO_LINK"));
		return false;
	}
	if (!pReaderDllBase->CheckState(STATE_CONNET))
	{
		MainShowMsg(GET_TXT("IDCS_READ_NO_LINK"));
		return bRet;
	}
	QString ipAddr = pReaderDllBase->mLinkInfo.mIpAddr;
	//ipAddr = QString("18.0.4.238");
	int nPort = 69;
	emit resultReady(20);
	unsigned long nIpStr;
	nIpStr = inet_addr(ipAddr.toUtf8().data());
	//打开通讯连接
	if (!mTcpClient->OpenConn(nPort,nIpStr))
	{
		MainShowMsg(GET_TXT("IDCS_TCP_LINK_FAILED"));
		return false;
	}
	emit resultReady(25);

	char sendbuf[1024] = {0};//发送的缓存
	char recvbuf[255]={0}; //接收的数据包
	char blockBuff[512] = {0};//文件块的数据缓存 
	int recvLen = 255;
	int datasize;
	int sendbuflen = 1024;

	short Opcode;//操作码
	short Blocknum;//块序号
	short recvnum = 0;//发送的序号

	//发送文件名, 文件头
	QByteArray fileStrBa = fileStr.toUtf8();
	bRet = (MakeWRQ(sendbuf,sendbuflen,fileStrBa.data(),fileStrBa.length())==1);
	if(!bRet)
	{
		mTcpClient->CloseConn();
		MainShowMsg(GET_TXT("IDCS_CAN_NOT_PACK_WRQ"));
		return false;
	}

	emit resultReady(30);
	bRet = mTcpClient->Send((unsigned char*)sendbuf,sendbuflen);
	if (!bRet)
	{
		mTcpClient->CloseConn();
		MainShowMsg(GET_TXT("IDCS_WRQ_SEND_FAILED"));
		return false;
	}

	emit resultReady(40);
	//确认收到回复后, 根据回复的内容解析,
	int nStartResult = 40;	
	int nEndResult = 80;
	int	nTimeResult = 1;
	
	while(1)
	{
		if (nTimeResult % 5 == 0)
		{
			emit resultReady(nStartResult+nTimeResult); 
		}
		nTimeResult ++;
		if (nTimeResult+nStartResult >= nEndResult)
		{
			nTimeResult = 0;
		}

		recvLen = 255;
		recvLen = mTcpClient->RevMsg((unsigned char *)recvbuf,&recvLen);
		if(recvLen <= 0)
		{
			mTcpClient->CloseConn();
			MainShowMsg(GET_TXT("IDCS_RECV_FAILED"));
			return false;
		}
		//获取操作码
		getOpcode(recvbuf,recvLen,Opcode);
		if(Opcode!=4) 
		{
			mTcpClient->CloseConn();		
			QString opStr = QString::fromUtf8(recvbuf,recvLen);
			MainShowMsg(opStr);
			return false;
		}
		//解析块的序号
		AnalyseACK(recvbuf,recvLen,Blocknum);
		if (Blocknum == recvnum)
		{
			//获取包号
			int blockBuffLen =
				GetBockBuffFormFileBuff(pFileBuff,fileLen,(unsigned char *)&blockBuff,512,Blocknum);
			if (blockBuffLen == 0)
			{
				break;
			}
			//打包发送
			recvnum++;
			MakeDATA(sendbuf,sendbuflen,recvnum,blockBuff,blockBuffLen);
			bRet = mTcpClient->Send((unsigned char*)sendbuf,sendbuflen);
			if (!bRet)
			{
				mTcpClient->CloseConn();
				MainShowMsg(GET_TXT("IDCS_RECV_FAILED"));
				return false;
			}
		}
		else
		{
			mTcpClient->CloseConn();
			MainShowMsg(GET_TXT("IDCS_BLOCK_NUM_FAILED"));
			return false;
		}		
	}
	
	mTcpClient->CloseConn();

	emit resultReady(80);
	unsigned char Crc32[4] = {0};
	unsigned char file[255] = {0} ;
	unsigned int nCrc32 = 0;
	// 计算CRC 32   
	nCrc32 =	fast_crc32(nCrc32,pFileBuff,fileLen);
	nCrc32 = swap32(nCrc32) ;
	memcpy(Crc32,&nCrc32,4);
	memcpy(file,fileStrBa.data(),fileStrBa.length());


	bRet = SAAT_Updata (pReaderDllBase->m_hCom,
		mUpdateType,
		fileLen, 
		Crc32,  
		fileStrBa.length(),
		file);	
	emit resultReady(85);
	if (bRet)
	{
		if (mUpdateType != 2)
		{
			bRet = SAAT_Reboot (pReaderDllBase->m_hCom,
				0x00);
			if (!bRet)
			{
				MainShowMsg(GET_TXT("IDCS_REBOOT_COMAND_FAILED"));
			}
		}		

		emit resultReady(90);
	}	

	return bRet;
}


int FirmWareUpdateFor6CThread::GetBockBuffFormFileBuff(unsigned char* pFileBuff,/*文件buff */ int fileLen,/*文件长度 */ unsigned char* pBlockBuff,/*块的 捍?*/ int BlockBuffLen,/* 捍娲笮?*/ int Blocknum/*块的序号 */)
{
	int nStart = 0;
	int nLen = 0;
	if(Blocknum*BlockBuffLen > fileLen)
	{
		return 0;
	}

	nStart = Blocknum*BlockBuffLen;
	if((Blocknum+1)*BlockBuffLen > fileLen)
	{
		nLen = fileLen-nStart;
	}
	else
	{
		nLen = BlockBuffLen;
	}

	memcpy(pBlockBuff,pFileBuff+nStart,nLen);

	return nLen;	
}


int FirmWareUpdateFor6CThread::MakeWRQ(char * const buf,int &buflength, const char * const filename, int namesize,int mode)
{
	char * buff=buf;
	buflength=0;
	short Opcode=htons(2);
	memcpy(buff,&Opcode,2);
	buff+=2;
	buflength+=2;
	memcpy(buff,filename,namesize);
	buff+=namesize;
	buflength+=namesize;
	char a=0;
	memcpy(buff,&a,1);
	buff+=1;
	buflength+=1;
	char mode1[10]="netascii",mode2[10]="octet",mode3[10]="mail";
	switch (mode)
	{
	case 1:
		memcpy(buff,mode1,strlen(mode1)+1);
		buff+=strlen(mode1)+1;
		buflength+=strlen(mode1)+1;
		break;
	case 2:
		memcpy(buff,mode2,strlen(mode2)+1);
		buff+=strlen(mode2)+1;
		buflength+=strlen(mode2)+1;
		break;
	case 3:
		memcpy(buff,mode3,strlen(mode3)+1);
		buff+=strlen(mode3)+1;
		buflength+=strlen(mode3)+1;
		break;
	default:
		return 0;
	}
	return 1;
}

int FirmWareUpdateFor6CThread::getOpcode(char * const buf, int buflength,short &Opcode)
{
	short oc;
	memcpy(&oc,buf,2);
	Opcode = ntohs(oc);	
	return 1;
}

int FirmWareUpdateFor6CThread::AnalyseACK(char * const buf, int buflength, short &Blocknum)
{
	short Opcode,num;
	getOpcode(buf,buflength,Opcode);
	if ( Opcode!=4 )  return 0;
	memcpy(&num,buf+2,2);
	Blocknum = ntohs(num);
	return 1;
}

int FirmWareUpdateFor6CThread::MakeACK(char * const buf, int &buflength, short Blocknum)
{
	char * buff=buf;
	buflength=0;
	short Opcode=htons(4);
	memcpy(buff,&Opcode,2);
	buff+=2;
	buflength+=2;
	Blocknum = htons(Blocknum);
	memcpy(buff,&Blocknum,2);
	buff+=2;
	buflength+=2;
	return 1;
}

int FirmWareUpdateFor6CThread::MakeDATA(char * const buf, int &buflength, short Blocknum , const char * const data, int datasize)
{	
	char * buff=buf;														//Blocknum为包编号
	buflength=0;															//data为数据的首址
	short Opcode=htons(3);														//datasize为数据字节数。
	memcpy(buff,&Opcode,2);
	buff+=2;
	buflength+=2;
	Blocknum = htons(Blocknum);
	memcpy(buff,&Blocknum,2);
	buff+=2;
	buflength+=2;
	memcpy(buff,data,datasize);
	buff+=datasize;
	buflength+=datasize;
	return 1;
}


