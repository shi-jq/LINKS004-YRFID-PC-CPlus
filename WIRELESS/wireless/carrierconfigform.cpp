#include "carrierconfigform.h"
#include "ui_carrierconfigform.h"
#include "widgetconfig.h"
#include "RFIDAPIEXPORT.h"
#include "LanguageSrc.h"
#include "mainapp.h"
#include "wirelessdeviceinfodlg.h"
#include "WirelessRecvCtrl.h"

CarrierConfigForm::CarrierConfigForm(WirelessDeviceInfoDlg* ctrlDlg,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CarrierConfigForm)
{
    ui->setupUi(this);
	mCtrlDlg = ctrlDlg;
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
	WirelessReaderInfo* pWirelessReaderInfo = mCtrlDlg->GetReaderInfo();
	if(!pWirelessReaderInfo)
	{
		return ;
	}

	unsigned char nPara = mCarrierCb->currentIndex();
	if (WIRELESS_SAAT_YRFParaSet(
		WIRELESSRECV_HANDLE,
		pWirelessReaderInfo,
		0x00,nPara))
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
	WirelessReaderInfo* pWirelessReaderInfo = mCtrlDlg->GetReaderInfo();
	if(!pWirelessReaderInfo)
	{
		return false;
	}

	
	if (WIRELESS_SAAT_YRFParaQuery (
		WIRELESSRECV_HANDLE,
		pWirelessReaderInfo,
		0x00))
	{
		return true;
	}
	else
	{
		MainShowMsg(GET_TXT("IDCS_CARRIER_QUERY_FAILED"),true);
		return false;
	}
}

void CarrierConfigForm::SetRevMsg(int msgID,unsigned char bCommand,unsigned char* pData, int nLen)
{
	if (nLen<2)
	{	
		MainShowMsg(GET_TXT("IDCS_CARRIER_QUERY_FAILED"),true);
		return;
	}

	mCarrierCb->setCurrentIndex(pData[1]);
	MainShowMsg(GET_TXT("IDCS_CARRIER_QUERY_SUCCESS"));
}
