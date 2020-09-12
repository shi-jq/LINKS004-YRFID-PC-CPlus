#include "carrierconfigform.h"
#include "ui_carrierconfigform.h"
#include "widgetconfig.h"
#include "RFIDAPIEXPORT.h"
#include "LanguageSrc.h"
#include "readerdllbase.h"
#include "mainapp.h"
#include "readermanager.h"

CarrierConfigForm::CarrierConfigForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CarrierConfigForm)
{
    ui->setupUi(this);
	mCarrierCb = ui->comboBox;
	mQueryBtn = ui->pushButton;
	mSetBtn = ui->pushButton_2;
	int nLimit = 24;
	QString tmpStr;
	for( int i = 0 ; i < nLimit; i++)
	{
		tmpStr = QString("%1M").arg( 2405+i*5);
		mCarrierCb->addItem(tmpStr);
	}

	connect( mQueryBtn, SIGNAL( clicked()), this, SLOT( slot_QurBtnClicked( ) ) );
	connect( mSetBtn, SIGNAL( clicked()), this, SLOT( slot_SetBtnClicked( ) ) );
}

CarrierConfigForm::~CarrierConfigForm()
{
    delete ui;
}

void CarrierConfigForm::slot_QurBtnClicked()
{
	QueryAll();
}

void CarrierConfigForm::slot_SetBtnClicked()
{
	ReaderDllBase* pReaderDllBase = pMainApp->GetReader();
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

	unsigned char nPara = mCarrierCb->currentIndex();
	if (SAAT_YRFParaSet(pReaderDllBase->m_hCom,0x00,nPara))
	{
		MainShowMsg(GET_TXT("IDCS_CARRIER_SET_SUCCESS"));
	}
	else
	{
		MainShowMsg(GET_TXT("IDCS_CARRIER_SET_FAILED"),true);
	}
}

bool CarrierConfigForm::QueryAll()
{
	ReaderDllBase* pReaderDllBase = pMainApp->GetReader();
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

	unsigned char nPara;
	if (SAAT_YRFParaQuery (pReaderDllBase->m_hCom,0x00,&nPara))
	{
		mCarrierCb->setCurrentIndex(nPara);
		MainShowMsg(GET_TXT("IDCS_CARRIER_QUERY_SUCCESS"));
		return true;
	}
	else
	{
		MainShowMsg(GET_TXT("IDCS_CARRIER_QUERY_FAILED"),true);
		return false;
	}
}
