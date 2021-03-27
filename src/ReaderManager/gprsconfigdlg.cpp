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
	mApnEdit = ui->lineEdit_3;
	mAccoundEdit = ui->lineEdit_4; 
	mPwdEdit = ui->lineEdit_5;

	ui->label_3->setText(GET_TXT("IDCS_APN"));
	ui->label_4->setText(GET_TXT("IDCS_ACCOUNT_NAME"));
	ui->label_5->setText(GET_TXT("IDCS_PWD"));
	ui->pushButton->setText(GET_TXT("IDCS_QUERY"));
	ui->pushButton_2->setText(GET_TXT("IDCS_SET"));

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
