#include "gprsconfigdlg.h"
#include "ui_gprsconfigdlg.h"
#include "LanguageSrc.h"
#include "appconfig.h"
#include "mainapp.h"
#include "RFIDAPIEXPORT.h"
#include "readerdllbase.h"
#include <QRegExpValidator>
GprsConfigDlg::GprsConfigDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GprsConfigDlg)
{
    ui->setupUi(this);
	this->setWindowTitle(GET_TXT("IDCS_CPRS_CONFIG"));
	mQueryBtn = ui->pushButton;
	mSetBtn = ui->pushButton_2;
	mIpaddrEdit = ui->lineEdit;
	mPortEdit = ui->lineEdit_2;
	mApnEdit = ui->lineEdit_3;
	mAccoundEdit = ui->lineEdit_4; 
	mPwdEdit = ui->lineEdit_5;

	ui->label->setText(GET_TXT("IDCS_IP_ADDR"));
	ui->label_2->setText(GET_TXT("IDCS_LISENT_PORT"));
	ui->label_3->setText(GET_TXT("IDCS_APN"));
	ui->label_4->setText(GET_TXT("IDCS_ACCOUNT_NAME"));
	ui->label_5->setText(GET_TXT("IDCS_PWD"));
	ui->pushButton->setText(GET_TXT("IDCS_QUERY"));
	ui->pushButton_2->setText(GET_TXT("IDCS_SET"));

	mIpaddrEdit->setInputMask(QString("000.000.000.000;"));
	//mPwdEdit->setEchoMode(QLineEdit::PasswordEchoOnEdit);

	mFirst = true;

	connect( mSetBtn, SIGNAL( clicked()), this, SLOT( slot_SetBtnClicked( ) ) );
	connect( mQueryBtn, SIGNAL( clicked()), this, SLOT( slot_QueryBtnClicked( ) ) );

}

GprsConfigDlg::~GprsConfigDlg()
{
    delete ui;
}

void GprsConfigDlg::slot_QueryBtnClicked()
{
	QueryAll();
}

void GprsConfigDlg::slot_SetBtnClicked()
{
	ReaderDllBase*	pReaderDllBase = pMainApp->GetReader();
	if (!pReaderDllBase)
	{
		MainShowMsg(GET_TXT("IDCS_READ_NO_LINK"));
		return ;
	}
	if (!pReaderDllBase->CheckState(STATE_CONNET))
	{
		MainShowMsg(GET_TXT("IDCS_READ_NO_LINK"));
		return ;
	}

	bool bRet = true;
	if (bRet)
	{
		bRet = SetIpAddr();
	}

	if (bRet)
	{
		bRet = SetDSCPort();
	}

	if (bRet)
	{
		bRet = SetApn();
	}

	if (bRet)
	{
		bRet = SetAccount();
	}

	if (bRet)
	{
		bRet = SetPwd();
	}

	if (bRet)
	{
		MainShowMsg(GET_TXT("IDCS_SET_SUCCESS"));
	}	
	else
	{	
		MainShowMsg(GET_TXT("IDCS_SET_FAILED"),true);
	}
}

void GprsConfigDlg::showEvent(QShowEvent *event)
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
	if (mFirst)
	{
        //mFirst = !QueryAll();
	}
	QWidget::showEvent(event);
}

bool GprsConfigDlg::QueryIpAddr()
{
	ReaderDllBase*	pReaderDllBase = pMainApp->GetReader();	
	if (!pReaderDllBase)
	{
		MainShowMsg(GET_TXT("IDCS_READ_NO_LINK"));
		return false;
	}
	if (!pReaderDllBase->CheckState(STATE_CONNET))
	{
		MainShowMsg(GET_TXT("IDCS_READ_NO_LINK"));
		return false;
	}

	unsigned char btAddr = 126;	//设备名称起始地址
	unsigned char nDataLen = 20;//长度
	unsigned char btExportData[20];
	ZeroMemory(btExportData,20);
	unsigned char nBufferSize = 20;

	btAddr = 250;		//IP地址起始地址
	nDataLen = 4;		//IP地址长度
	ZeroMemory(btExportData,20);
	nBufferSize = 20;
	bool bRet = SAAT_ParmOp (pReaderDllBase->m_hCom,
		0x02,
		btAddr, 
		nDataLen,  
		btExportData,
		&nBufferSize);		

	if (bRet)
	{		
		in_addr ia;
		memcpy(&ia,&btExportData,4);
		mIpaddrEdit->setText(QString::fromUtf8(inet_ntoa(ia)));
	}

	return bRet;
}

bool GprsConfigDlg::QueryPort()
{
	ReaderDllBase*	pReaderDllBase = pMainApp->GetReader();	
	if (!pReaderDllBase)
	{
		MainShowMsg(GET_TXT("IDCS_READ_NO_LINK"));
		return false;
	}
	if (!pReaderDllBase->CheckState(STATE_CONNET))
	{
		MainShowMsg(GET_TXT("IDCS_READ_NO_LINK"));
		return false;
	}

	unsigned char btAddr = 126;	//设备名称起始地址
	unsigned char nDataLen = 20;//长度
	unsigned char btExportData[20];
	ZeroMemory(btExportData,20);
	unsigned char nBufferSize = 20;

	btAddr = 254;		//端口号起始地址
	nDataLen = 2;		//端口号长度
	ZeroMemory(btExportData,20);
	nBufferSize = 20;
	bool bRet = SAAT_ParmOp (pReaderDllBase->m_hCom,
		0x02,
		btAddr, 
		nDataLen,  
		btExportData,
		&nBufferSize);		

	if (bRet)
	{		
		int gprsPort = MAKEWORD(btExportData[1],btExportData[0]);
		mPortEdit->setText(QString("%1").arg(gprsPort));
	}
	
	return bRet;
}


bool GprsConfigDlg::QueryApn()
{
	ReaderDllBase*	pReaderDllBase = pMainApp->GetReader();	
	if (!pReaderDllBase)
	{
		MainShowMsg(GET_TXT("IDCS_READ_NO_LINK"));
		return false;
	}
	if (!pReaderDllBase->CheckState(STATE_CONNET))
	{
		MainShowMsg(GET_TXT("IDCS_READ_NO_LINK"));
		return false;
	}

	unsigned char btAddr = 126;
	unsigned char nDataLen = 64;
	unsigned char btExportData[68];
	ZeroMemory(btExportData,68);
	unsigned char nBufferSize = nDataLen;

	btAddr = 122;				
	ZeroMemory(btExportData,nBufferSize);	
	bool bRet = SAAT_ParmOp (pReaderDllBase->m_hCom,
		0x02,
		btAddr, 
		nDataLen,  
		btExportData,
		&nBufferSize);		

	if (bRet)
	{	
		mApnEdit->setText(QString::fromUtf8((char*)btExportData));		
	}

	return bRet;
}	

bool GprsConfigDlg::QueryAccount()
{
	ReaderDllBase*	pReaderDllBase = pMainApp->GetReader();	
	if (!pReaderDllBase)
	{
		MainShowMsg(GET_TXT("IDCS_READ_NO_LINK"));
		return false;
	}
	if (!pReaderDllBase->CheckState(STATE_CONNET))
	{
		MainShowMsg(GET_TXT("IDCS_READ_NO_LINK"));
		return false;
	}

	unsigned char btAddr = 126;
	unsigned char nDataLen = 64;
	unsigned char btExportData[68];
	ZeroMemory(btExportData,68);
	unsigned char nBufferSize = 64;

	btAddr = 123;		
	nDataLen = 64;		
	ZeroMemory(btExportData,64);
	nBufferSize = 64;
	bool bRet = SAAT_ParmOp (pReaderDllBase->m_hCom,
		0x02,
		btAddr, 
		nDataLen,  
		btExportData,
		&nBufferSize);		

	if (bRet)
	{				
		mAccoundEdit->setText(QString::fromUtf8((char*)btExportData));
	}

	return bRet;
}	

bool GprsConfigDlg::QueryPwd()
{
	ReaderDllBase*	pReaderDllBase = pMainApp->GetReader();	
	if (!pReaderDllBase)
	{
		MainShowMsg(GET_TXT("IDCS_READ_NO_LINK"));
		return false;
	}
	if (!pReaderDllBase->CheckState(STATE_CONNET))
	{
		MainShowMsg(GET_TXT("IDCS_READ_NO_LINK"));
		return false;
	}

	unsigned char btAddr = 126;
	unsigned char nDataLen = 64;
	unsigned char btExportData[68];
	ZeroMemory(btExportData,68);
	unsigned char nBufferSize = 64;

	btAddr = 124;		
	nDataLen = 64;		
	ZeroMemory(btExportData,64);
	nBufferSize = 64;
	bool bRet = SAAT_ParmOp (pReaderDllBase->m_hCom,
		0x02,
		btAddr, 
		nDataLen,  
		btExportData,
		&nBufferSize);		

	if (bRet)
	{	
		mPwdEdit->setText(QString::fromUtf8((char*)btExportData));
	}

	return bRet;
}

bool GprsConfigDlg::SetIpAddr()
{
	ReaderDllBase*	pReaderDllBase = pMainApp->GetReader();	
	if (!pReaderDllBase)
	{
		MainShowMsg(GET_TXT("IDCS_READ_NO_LINK"));
		return false;
	}
	if (!pReaderDllBase->CheckState(STATE_CONNET))
	{
		MainShowMsg(GET_TXT("IDCS_READ_NO_LINK"));
		return false;
	}
	
	if (!CheckIPEdit(mIpaddrEdit->text()))
	{
		MainShowMsg(GET_TXT("IDCS_IPADDR_INVAID"));
		return false;
	}

	unsigned char btParams[16];
	ZeroMemory(btParams, 16);

	QStringList tmpList = mIpaddrEdit->text().split(".");
	if (tmpList.size() < 4)
	{
		MainShowMsg(GET_TXT("IDCS_IP_ERRO"));
		return false;
	}

	btParams[0] = tmpList.at(0).toUInt();
	btParams[1] = tmpList.at(1).toUInt();
	btParams[2] = tmpList.at(2).toUInt();
	btParams[3] = tmpList.at(3).toUInt();

	unsigned char btAddr = 126;	
	unsigned char nDataLen = 11; 
	unsigned char nBufferSize = 16;

	btAddr = 250;	//IP地址参数表中起始地址
	nDataLen = 4;	//IP地址长度
	nBufferSize = 4;

	bool bRet = SAAT_ParmOp (pReaderDllBase->m_hCom,
		0x01,
		btAddr, 
		nDataLen,  
		btParams,
		&nBufferSize);
	
	return bRet;
}

bool GprsConfigDlg::SetDSCPort()
{
	ReaderDllBase*	pReaderDllBase = pMainApp->GetReader();	

	if (!pReaderDllBase)
	{
		MainShowMsg(GET_TXT("IDCS_READ_NO_LINK"));
		return false;
	}
	if (!pReaderDllBase->CheckState(STATE_CONNET))
	{
		MainShowMsg(GET_TXT("IDCS_READ_NO_LINK"));
		return false;
	}

	if (mPortEdit->text().isEmpty())
	{
		MainShowMsg(GET_TXT("IDCS_INPUT_EMPTY"));
		return false;
	}

	unsigned char btParams[16]= {0};

	unsigned char btAddr = 126;	
	unsigned char nDataLen = 11; 
	unsigned char nBufferSize = 16;

	btAddr = 254;
	nDataLen = 2;
	nBufferSize = 2;

	ZeroMemory(btParams, 16);
	WORD dLoSocketPort =  LOWORD(mPortEdit->text().toUInt());
	btParams[0] = HIBYTE(dLoSocketPort);
	btParams[1] = LOBYTE(dLoSocketPort);

	bool bRet = SAAT_ParmOp (pReaderDllBase->m_hCom,
		0x01,
		btAddr, 
		nDataLen,  
		btParams,
		&nBufferSize);

	return bRet;
}

bool GprsConfigDlg::SetApn()
{
	ReaderDllBase*	pReaderDllBase = pMainApp->GetReader();	
	if (!pReaderDllBase)
	{
		MainShowMsg(GET_TXT("IDCS_READ_NO_LINK"));
		return false;
	}
	if (!pReaderDllBase->CheckState(STATE_CONNET))
	{
		MainShowMsg(GET_TXT("IDCS_READ_NO_LINK"));
		return false;
	}

	if (mApnEdit->text().isEmpty())
	{
		MainShowMsg(GET_TXT("IDCS_INPUT_EMPTY"));
		return false;
	}


	unsigned char btParams[64]= {0};

	unsigned char btAddr = 122;	
	unsigned char nDataLen = 64; 
	unsigned char nBufferSize = 64;

	QString inputStr = mApnEdit->text();
	int realLen = inputStr.toUtf8().length();
	nDataLen = realLen;
	nBufferSize = realLen;
	if (realLen > 64)
	{
		MainShowMsg(GET_TXT("IDCS_INPUT_LIMIT_1").arg(64));
		return false;
	}

	memcpy(btParams,inputStr.toUtf8().data(),realLen);

	bool bRet = SAAT_ParmOp (pReaderDllBase->m_hCom,
		0x01,
		btAddr, 
		nDataLen,  
		btParams,
		&nBufferSize);

	return bRet;
}

bool GprsConfigDlg::SetAccount()
{
	ReaderDllBase*	pReaderDllBase = pMainApp->GetReader();	
	if (!pReaderDllBase)
	{
		MainShowMsg(GET_TXT("IDCS_READ_NO_LINK"));
		return false;
	}
	if (!pReaderDllBase->CheckState(STATE_CONNET))
	{
		MainShowMsg(GET_TXT("IDCS_READ_NO_LINK"));
		return false;
	}

	if (mAccoundEdit->text().isEmpty())
	{
		MainShowMsg(GET_TXT("IDCS_INPUT_EMPTY"));
		return false;
	}

	unsigned char btParams[64] = {0};

	unsigned char btAddr = 123;	
	unsigned char nDataLen = 64; 
	unsigned char nBufferSize = 64;

	QString inputStr = mAccoundEdit->text();
	int realLen = inputStr.toUtf8().length();
	nDataLen = realLen;
	nBufferSize = realLen;
	if (realLen > 64)
	{
		MainShowMsg(GET_TXT("IDCS_INPUT_LIMIT_1").arg(64));
		return false;
	}

	memcpy(btParams,inputStr.toUtf8().data(),realLen);

	bool bRet = SAAT_ParmOp (pReaderDllBase->m_hCom,
		0x01,
		btAddr, 
		nDataLen,  
		btParams,
		&nBufferSize);
	return bRet;
}

bool GprsConfigDlg::SetPwd()
{
	ReaderDllBase*	pReaderDllBase = pMainApp->GetReader();	
	if (!pReaderDllBase)
	{
		MainShowMsg(GET_TXT("IDCS_READ_NO_LINK"));
		return false;
	}
	if (!pReaderDllBase->CheckState(STATE_CONNET))
	{
		MainShowMsg(GET_TXT("IDCS_READ_NO_LINK"));
		return false;
	}

	if (mPwdEdit->text().isEmpty())
	{
		MainShowMsg(GET_TXT("IDCS_INPUT_EMPTY"));
		return false;
	}

	unsigned char btParams[64]= {0};

	unsigned char btAddr = 124;	
	unsigned char nDataLen = 64; 
	unsigned char nBufferSize = 64;

	QString inputStr = mPwdEdit->text();
	int realLen = inputStr.toUtf8().length();
	nDataLen = realLen;
	nBufferSize = realLen;
	if (realLen > 64)
	{
		MainShowMsg(GET_TXT("IDCS_INPUT_LIMIT_1").arg(64));
		return false;
	}

	memcpy(btParams,inputStr.toUtf8().data(),realLen);

	bool bRet = SAAT_ParmOp (pReaderDllBase->m_hCom,
		0x01,
		btAddr, 
		nDataLen,  
		btParams,
		&nBufferSize);

	return bRet;
}


bool GprsConfigDlg::CheckIPEdit(const QString& str)
{
	QRegExp regexp( "((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)" );

	QRegExpValidator regexp_validator( regexp, this );
	int nPos = 0;
	if ( str.isEmpty() )
	{
		return false;
	}
	QString tmp = str;
	if ( !str.isEmpty() && regexp_validator.validate( tmp, nPos ) != QValidator::Acceptable )
	{
		return false;
	}
	return true;
}

bool GprsConfigDlg::QueryAll()
{
	ReaderDllBase*	pReaderDllBase = pMainApp->GetReader();
	if (!pReaderDllBase)
	{
		MainShowMsg(GET_TXT("IDCS_READ_NO_LINK"));
		return false;
	}
	if (!pReaderDllBase->CheckState(STATE_CONNET))
	{
		MainShowMsg(GET_TXT("IDCS_READ_NO_LINK"));
		return false;
	}

	bool bRet = true;
	if (bRet)
	{
		bRet = QueryIpAddr();
	}

	if (bRet)
	{
		bRet = QueryPort();
	}

	if (bRet)
	{
		bRet = QueryApn();
	}

	if (bRet)
	{
		bRet = QueryAccount();
	}

	if (bRet)
	{
		bRet = QueryPwd();
	}

	if (bRet)
	{		
		MainShowMsg(GET_TXT("IDCS_QUERY_SUCCESS"));	
	}
	else
	{

		MainShowMsg(GET_TXT("IDCS_QUERY_FAILED"),true);
	}

	return bRet;
}
