#include "busaddrconfigdlg.h"
#include "ui_busaddrconfigdlg.h"
#include "LanguageSrc.h"
#include "appconfig.h"
#include "mainapp.h"
#include "RFIDAPIEXPORT.h"
#include "readerdllbase.h"

BusAddrConfigDlg::BusAddrConfigDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BusAddrConfigDlg)
{
    ui->setupUi(this);
	this->setWindowTitle(GET_TXT("IDCS_BUS_CONFIG"));
	mBusEdit = ui->lineEdit;
	mQueryBtn = ui->pushButton;
	mSetBtn = ui->pushButton_2;

	ui->label->setText(GET_TXT("IDCS_BUS_ADDR"));
	mQueryBtn->setText(GET_TXT("IDCS_QUERY"));
	mSetBtn->setText(GET_TXT("IDCS_SET"));

	mBusEdit->setText("00");
	mBusEdit->setMaxLength(2);
	mFirst = true;
	
	connect( mQueryBtn, SIGNAL( clicked()), this, SLOT( slot_QueryBtnClicked( ) ) );
	connect( mSetBtn, SIGNAL( clicked()), this, SLOT( slot_SetBtnClicked( ) ) );
}

BusAddrConfigDlg::~BusAddrConfigDlg()
{
    delete ui;
}

void BusAddrConfigDlg::slot_QueryBtnClicked()
{
	Query();
}

void BusAddrConfigDlg::slot_SetBtnClicked()
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
	bool isOk;
	unsigned char iInfoType = 0x00;
	unsigned char btParam = mBusEdit->text().toUInt(&isOk,16);
	unsigned char nSize = 1;
	bool bRet = SAAT_CommunicatParaSet(pReaderDllBase->m_hCom,
		iInfoType,
		&btParam,
		nSize);

	if (bRet)
	{
		MainShowMsg(GET_TXT("IDCS_BUS_SET_SUCCESS"));
	}
	else
	{
		MainShowMsg(GET_TXT("IDCS_BUS_SET_FAILED"),true);
	}
}

void BusAddrConfigDlg::showEvent(QShowEvent *event)
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
		mFirst =!Query();
	}
	QWidget::showEvent(event);
}

bool BusAddrConfigDlg::Query()
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

	int iInfoType = 0x00;
	unsigned char btParams = 0x00;
	unsigned char size=1;

	bool retB = SAAT_CommunicatParaQuery(
		pReaderDllBase->m_hCom,
		iInfoType,
		&btParams,
		&size) ;

	if (retB)
	{
		mBusEdit->setText(QString("%1").arg(btParams,2,16,QLatin1Char('0')).toUpper());
		MainShowMsg(GET_TXT("IDCS_BUS_QUERY_SUCCESS"));
	}
	else
	{
		MainShowMsg(GET_TXT("IDCS_BUS_QUERY_FAILED"),true);
	}

	return retB;
}
