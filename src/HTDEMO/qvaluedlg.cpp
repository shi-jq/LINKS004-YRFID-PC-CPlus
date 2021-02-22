#include "qvaluedlg.h"
#include "ui_qvaluedlg.h"
#include "LanguageSrc.h"
#include "appconfig.h"
#include "mainapp.h"
#include "RFIDAPIEXPORT.h"
#include "readerdllbase.h"

QValueDlg::QValueDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QValueDlg)
{
    ui->setupUi(this);
	this->setWindowTitle(GET_TXT("IDCS_QVALUE"));
	mQueryBtn = ui->pushButton;
	mSetBtn=ui->pushButton_2;
	mValueEdit=ui->spinBox;
	mValueEdit->setMinimum(0);
	mValueEdit->setMaximum(255);

	ui->label->setText(GET_TXT("IDCS_QVALUE_LIMIT_0_255"));
	mQueryBtn->setText(GET_TXT("IDCS_QUERY"));
	mSetBtn->setText(GET_TXT("IDCS_SET"));

	mIsFirst = true;

	connect( mQueryBtn, SIGNAL( clicked()), this, SLOT( slot_QueryBtnClicked( ) ) );
	connect( mSetBtn, SIGNAL( clicked()), this, SLOT( slot_SetBtnClicked( ) ) );

}

QValueDlg::~QValueDlg()
{
    delete ui;
}

void QValueDlg::showEvent(QShowEvent *event)
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
	if(mIsFirst)
	{
		mIsFirst = !Query();
	}

	QWidget::showEvent(event);
}

void QValueDlg::slot_QueryBtnClicked()
{
	Query();	
}

void QValueDlg::slot_SetBtnClicked()
{
	ReaderDllBase*	pReaderDllBase = pMainApp->GetReader();	
	if (!pReaderDllBase)
	{
		MainShowMsg(GET_TXT("IDCS_READ_NO_LINK"));
		return;
	}
	if (!pReaderDllBase->CheckState(STATE_CONNET))
	{
		MainShowMsg(GET_TXT("IDCS_READ_NO_LINK"));
		return ;
	}

	byte btParams = mValueEdit->value();
	
	unsigned char nType = 0x10;
	bool bRet = SAAT_TagOpParaSet(
		pReaderDllBase->m_hCom,
		nType,
		&btParams,
		1);


	if (bRet)
	{			
		MainShowMsg(GET_TXT("IDCS_QVALUE_SET_SUCCESS"));	
	}
	else
	{
		MainShowMsg(GET_TXT("IDCS_QVALUE_SET_FAILED"),true);
	}	
}

bool QValueDlg::Query()
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

	unsigned char iInfoType = 0x10;
	unsigned char btParam = 0;	

	unsigned char nLen = 1;
	bool bRet = SAAT_TagOpParaQuery(
		pReaderDllBase->m_hCom, 
		iInfoType,
		&btParam,
		&nLen);


	if (bRet)
	{		
		mValueEdit->setValue(btParam);
		MainShowMsg(GET_TXT("IDCS_QVALUE_SET_SUCCESS"));	
	}
	else
	{
		MainShowMsg(GET_TXT("IDCS_QVALUE_SET_FAILED"),true);
	}	

	return bRet;

}
