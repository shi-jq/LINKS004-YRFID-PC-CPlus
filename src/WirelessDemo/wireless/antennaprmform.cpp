#include "antennaprmform.h"
#include "ui_antennaprmform.h"
#include "widgetconfig.h"
#include "LanguageSrc.h"
#include "mainapp.h"
#include "wirelessdeviceinfodlg.h"
#include "WIRELESSRFIDAPIEXPORT.h"
#include "WirelessRecvCtrl.h"

AntennaPrmForm::AntennaPrmForm(WirelessDeviceInfoDlg* ctrlDlg,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AntennaPrmForm)
{
    ui->setupUi(this);
	mCtrlDlg = ctrlDlg;

	mQurAntennaBtn = ui->pushButton;
	mSetAntennaBtn = ui->pushButton_2;

	mAntenna1CheckBox = ui->checkBox;
	mAntenna2CheckBox = ui->checkBox_2;
	mAntenna3CheckBox = ui->checkBox_3;
	mAntenna4CheckBox = ui->checkBox_4;

	mAntenna1TimeSb = ui->spinBox;
	mAntenna2TimeSb = ui->spinBox_2;
	mAntenna3TimeSb = ui->spinBox_3;
	mAntenna4TimeSb = ui->spinBox_4;

	mAntenna1TimeSb->setMinimum(0);
	mAntenna1TimeSb->setMaximum(255);
	mAntenna1TimeSb->setValue(1);
	mAntenna2TimeSb->setMinimum(0);
	mAntenna2TimeSb->setMaximum(255);
	mAntenna2TimeSb->setValue(1);
	mAntenna3TimeSb->setMinimum(0);
	mAntenna3TimeSb->setMaximum(255);
	mAntenna3TimeSb->setValue(1);
	mAntenna4TimeSb->setMinimum(0);
	mAntenna4TimeSb->setMaximum(255);
	mAntenna4TimeSb->setValue(1);	

	connect( mQurAntennaBtn, SIGNAL( clicked()), this, SLOT( slot_QurAntennaBtnClicked( ) ) );
	connect( mSetAntennaBtn, SIGNAL( clicked()), this, SLOT( slot_SetAntennaBtnClicked( ) ) );
}

AntennaPrmForm::~AntennaPrmForm()
{
    delete ui;
}

bool AntennaPrmForm::QurAntenna()
{
	WirelessReaderInfo* pWirelessReaderInfo = mCtrlDlg->GetReaderInfo();
	if(!pWirelessReaderInfo)
	{
		return false;
	}

	unsigned int nPortEnable = 0, nPollTime=0,nParam=0;
	bool bRet = WIRELESS_SAAT_YAntennaPort_EXQuery(
		WIRELESSRECV_HANDLE,
		pWirelessReaderInfo);
	if (!bRet)
	{
		MainShowMsg(GET_TXT("IDCS_ANTENNA_STATE_QUERY_FAILED"),true);
	}

	return bRet;
}

bool AntennaPrmForm::SetAntenna()
{
	WirelessReaderInfo* pWirelessReaderInfo = mCtrlDlg->GetReaderInfo();
	if(!pWirelessReaderInfo)
	{
		return false;
	}


	unsigned int nPortEnable = 0, nPollTime=0,nParam=0;
	if(mAntenna1CheckBox->isChecked())
	{
		nPortEnable += ((0x01)<<24);
	}

	if(mAntenna2CheckBox->isChecked())
	{
		nPortEnable += ((0x01)<<16);
	}

	if(mAntenna3CheckBox->isChecked())
	{
		nPortEnable += ((0x01)<<8);
	}

	if(mAntenna4CheckBox->isChecked())
	{
		nPortEnable += ((0x01));
	}

	nPollTime += (mAntenna1TimeSb->value())<<24;
	nPollTime += (mAntenna2TimeSb->value())<<16;
	nPollTime += (mAntenna3TimeSb->value())<<8;
	nPollTime += (mAntenna4TimeSb->value()) ;

	bool bRet = WIRELESS_SAAT_YAntennaPort_EXSet( 
		WIRELESSRECV_HANDLE,
		pWirelessReaderInfo,
		nPortEnable,
		nPollTime,
		nParam
		);
	if (bRet)
	{
		MainShowMsg(GET_TXT("IDCS_ANTENNA_STATE_SET_SUCCESS"));
	}
	else
	{
		MainShowMsg(GET_TXT("IDCS_ANTENNA_STATE_SET_FAILED"),true);
	}

	return bRet;
}

void AntennaPrmForm::slot_QurAntennaBtnClicked()
{
	QurAntenna();
}

void AntennaPrmForm::slot_SetAntennaBtnClicked()
{
	SetAntenna();
}

void AntennaPrmForm::SetRevMsg(int msgID,unsigned char bCommand,unsigned char* pData, int nLen)
{
	if (nLen < 13)
	{
		MainShowMsg(GET_TXT("IDCS_ANTENNA_STATE_QUERY_FAILED"),true);
		return;
	}

	int nPortEnable =(pData[1] << 24) + 
		(pData[2] << 16) + 
		(pData[3] << 8) + 
		pData[4];

	int nPollTime =(pData[5] << 24) + 
		(pData[6] << 16) + 
		(pData[7] << 8) + 
		pData[8];

	int nParam =(pData[9] << 24) + 
		(pData[10] << 16) + 
		(pData[11] << 8) + 
		pData[12];

	mAntenna1CheckBox->setChecked(((BYTE)((nPortEnable) >> 24 ) & 0x01) == 0x01);
	mAntenna2CheckBox->setChecked(((BYTE)((nPortEnable) >> 16 ) & 0x01) == 0x01);
	mAntenna3CheckBox->setChecked(((BYTE)((nPortEnable) >> 8 ) & 0x01) == 0x01);
	mAntenna4CheckBox->setChecked(((BYTE)((nPortEnable)) & 0x01) == 0x01);

	mAntenna1TimeSb->setValue(0xff&(nPollTime >> 24 ));
	mAntenna2TimeSb->setValue(0xff&(nPollTime >> 16 ));
	mAntenna3TimeSb->setValue(0xff&(nPollTime >> 8 ));
	mAntenna4TimeSb->setValue(0xff&(nPollTime >> 0 ));

	MainShowMsg(GET_TXT("IDCS_ANTENNA_STATE_QUERY_SUCCESS"));
}
