#include "pointconfigform.h"
#include "ui_pointconfigform.h"
#include "widgetconfig.h"
#include "LanguageSrc.h"
#include "mainapp.h"
#include "WIRELESSRFIDAPIEXPORT.h"
#include "wirelessdeviceinfodlg.h"
#include "WirelessRecvCtrl.h"

PointConfigForm::PointConfigForm(WirelessDeviceInfoDlg* ctrlDlg,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PointConfigForm)
{
    ui->setupUi(this);
	mCtrlDlg = ctrlDlg;
	mQueryBtn = ui->pushButton_2;
	mSetBtn = ui->pushButton;
	mPortEnableCb = ui->comboBox;
	m2401Cb = ui->comboBox_3;
	mFreqPwrCb = ui->comboBox_2;

	QStringList sl;
	sl<<GET_TXT("IDCS_EDIT_ALL_PRM_CONFIG");
	sl<<GET_TXT("IDCS_EDIT_SEND_POWER");
	sl<<GET_TXT("IDCS_EDIT_RECV_DECAY");
	mPortEnableCb->addItems(sl);

	sl.clear();
	sl<<QString("-6dBm");
	sl<<QString("0dBm");
	sl<<QString("6dBm");
	sl<<QString("12dBm");
	sl<<QString("18dBm");
	sl<<QString("20dBm");
	m2401Cb->addItems(sl);

	sl.clear();
	for (int i=0; i<=15; i++)
	{
		if (i==0)
		{
			sl<<QString("0db");
		}
		else
		{
			sl<<QString("-%1db").arg(i*2);
		}
		
	}
	mFreqPwrCb->addItems(sl);

	slot_currentIndexChanged(mPortEnableCb->currentIndex());

	connect( mQueryBtn, SIGNAL( clicked()), this, SLOT( slot_QurBtnClicked( ) ) );
	connect( mSetBtn, SIGNAL( clicked()), this, SLOT( slot_SetBtnClicked( ) ) );
	connect( mPortEnableCb, SIGNAL( currentIndexChanged(int)), this, SLOT( slot_currentIndexChanged(int ) ) );

}

PointConfigForm::~PointConfigForm()
{
    delete ui;
}

void PointConfigForm::slot_QurBtnClicked()
{
	QueryAll();
}

void PointConfigForm::slot_SetBtnClicked()
{
	WirelessReaderInfo* pWirelessReaderInfo = mCtrlDlg->GetReaderInfo();
	if(!pWirelessReaderInfo)
	{
		return;
	}

	unsigned char btPara[12];
	ZeroMemory(btPara,12);

	int index = mPortEnableCb->currentIndex();

	int iPwrRecPlus = 0;
	int i2401		= m2401Cb->currentIndex();
	int iAttenuator = mFreqPwrCb->currentIndex();
	
	btPara[0] = btPara[1] = btPara[2] = 0x03;
	btPara[4] = iPwrRecPlus; btPara[5] = i2401; btPara[6] = iAttenuator;
	switch (index)
	{
	case 0:
		break;	
	case 1:
		btPara[0] = btPara[2] = btPara[4] = btPara[6] = 0x00;
		break;
	case 2:
		btPara[0] = btPara[1] = btPara[4] = btPara[5] = 0x00;
		break;
	default:
		break;
	}
	if(WIRELESS_SAAT_YAntennaParmSet(
		WIRELESSRECV_HANDLE,
		pWirelessReaderInfo
		, btPara, 12))
	{
		MainShowMsg(GET_TXT("IDCS_RADIO_CONFIG_SET_SUCCESS"));	
	}
	else
	{
		MainShowMsg(GET_TXT("IDCS_RADIO_CONFIG_SET_FAILED"),true);
	}
}

void PointConfigForm::slot_currentIndexChanged(int index)
{
	switch(index)
	{
	case 0:
		m2401Cb->setEnabled(true);
		mFreqPwrCb->setEnabled(true);
		break;
	case 1:
		m2401Cb->setEnabled(true);
		mFreqPwrCb->setEnabled(false);
		break;
	case 2:
		m2401Cb->setEnabled(false);
		mFreqPwrCb->setEnabled(true);
		break;
	default:
		m2401Cb->setEnabled(false);
		mFreqPwrCb->setEnabled(false);
		break;
	}
}

bool PointConfigForm::QueryAll()
{
	WirelessReaderInfo* pWirelessReaderInfo = mCtrlDlg->GetReaderInfo();
	if(!pWirelessReaderInfo)
	{
		return false;
	}
	
	if (WIRELESS_SAAT_YAntennaParmQuery(
		WIRELESSRECV_HANDLE,
		pWirelessReaderInfo))
	{
		return true;
	}
	else
	{
		MainShowMsg(GET_TXT("IDCS_RADIO_CONFIG_QUERY_FAILED"),true);
		return false;
	}
}

void PointConfigForm::SetRevMsg(int msgID,
								unsigned char bCommand,
								unsigned char* pData, 
								int nLen)
{
	if (nLen<13)
	{	
		MainShowMsg(GET_TXT("IDCS_RADIO_CONFIG_QUERY_FAILED"),true);
		return;
	}

	unsigned char btPowerRecvPlus;
	unsigned char bt2401FreqSendPwr;
	unsigned char btAttenuatorPower;

	btPowerRecvPlus = pData[5];
	bt2401FreqSendPwr = pData[6];
	btAttenuatorPower = pData[7];

	m2401Cb->setCurrentIndex(bt2401FreqSendPwr);
	mFreqPwrCb->setCurrentIndex(btAttenuatorPower);

	MainShowMsg(GET_TXT("IDCS_RADIO_CONFIG_QUERY_SUCCESS"));
}
