#include "comconfigdlg.h"
#include "ui_comconfigdlg.h"
#include "LanguageSrc.h"
#include "appconfig.h"
#include "mainapp.h"
#include "RFIDAPIEXPORT.h"
#include "readerdllbase.h"

ComConfigDlg::ComConfigDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ComConfigDlg)
{
    ui->setupUi(this);
	this->setWindowTitle(GET_TXT("IDCS_COM_CONFIG"));
	
	mBaudRateCb = ui->comboBox;
	mQueryBtn = ui->pushButton;
	mSetBtn = ui->pushButton_2;

	ui->label->setText(GET_TXT("IDCS_BAUDRATE"));
	mQueryBtn->setText(GET_TXT("IDCS_QUERY"));
	mSetBtn->setText(GET_TXT("IDCS_SET"));

	QStringList sl;
	sl<<QString("4800")
		<<QString("9600")
		<<QString("19200")
		<<QString("38400")
		<<QString("57600")
		<<QString("115200");

	mBaudRateCb->addItems(sl);

	mFirst = true;

	connect( mQueryBtn, SIGNAL( clicked()), this, SLOT( slot_QueryBtnClicked( ) ) );
	connect( mSetBtn, SIGNAL( clicked()), this, SLOT( slot_SetBtnClicked( ) ) );
}

ComConfigDlg::~ComConfigDlg()
{
    delete ui;
}

void ComConfigDlg::slot_QueryBtnClicked()
{
	Query();
}

void ComConfigDlg::slot_SetBtnClicked()
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

	unsigned char iInfoType = 0x10;
	unsigned char btParam = mBaudRateCb->currentIndex();
	unsigned char nSize = 1;
	bool bRet = SAAT_CommunicatParaSet(pReaderDllBase->m_hCom,
		iInfoType,
		&btParam,
		nSize);

	if (bRet)
	{
		MainShowMsg(GET_TXT("IDCS_BAUD_RATE_SET_SUCCESS"));
	}
	else
	{
		MainShowMsg(GET_TXT("IDCS_BAUD_RATE_SET_FAILED"),true);
	}
}

void ComConfigDlg::showEvent(QShowEvent *event)
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
	if(mFirst)
	{
        //mFirst = !Query();
	}
	QWidget::showEvent(event);
}

bool ComConfigDlg::Query()
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

	int iInfoType = 0x10;
	unsigned char btParams = 0x00;
	unsigned char size=1;

	bool retB = SAAT_CommunicatParaQuery(
		pReaderDllBase->m_hCom,
		iInfoType,
		&btParams,
		&size) ;

	if (retB)
	{
		mBaudRateCb->setCurrentIndex(btParams);
		MainShowMsg(GET_TXT("IDCS_BAUD_RATE_QUERY_SUCCESS"));
	}
	else
	{
		MainShowMsg(GET_TXT("IDCS_BAUD_RATE_QUERY_FAILED"),true);
	}

	return retB;
}
