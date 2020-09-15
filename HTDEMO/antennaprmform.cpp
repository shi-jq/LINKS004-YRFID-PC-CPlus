#include "antennaprmform.h"
#include "ui_antennaprmform.h"
#include "widgetconfig.h"
#include "RFIDAPIEXPORT.h"
#include "LanguageSrc.h"
#include "readerdllbase.h"
#include "mainapp.h"
#include "readermanager.h"

AntennaPrmForm::AntennaPrmForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AntennaPrmForm)
{
    ui->setupUi(this);

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

	mFreqPwrCb1 = ui->comboBox;
	mFreqPwrCb2 = ui->comboBox_2;
	mFreqPwrCb3 = ui->comboBox_3;
	mFreqPwrCb4 = ui->comboBox_4;

	QStringList sl;
	sl.clear();
	for (int i = 0; i <= 30; i += 2)
	{
		if (i == 0)
		{
			sl << QString("%1db").arg(i);
		}
		else
		{
			sl << QString("-%1db").arg(i);
		}
	}
	mFreqPwrCb1->addItems(sl);
	mFreqPwrCb2->addItems(sl);
	mFreqPwrCb3->addItems(sl);
	mFreqPwrCb4->addItems(sl);

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


	ui->label_16->setText(GET_TXT("IDCS_ANTENNA_NO"));
	ui->label_18->setText(GET_TXT("IDCS_ANTENNA_TIME"));
	ui->checkBox->setText(GET_TXT("IDCS_ANTENNA_ONE"));
	ui->checkBox_2->setText(GET_TXT("IDCS_ANTENNA_TWO"));
	ui->checkBox_3->setText(GET_TXT("IDCS_ANTENNA_THREE"));
	ui->checkBox_4->setText(GET_TXT("IDCS_ANTENNA_FOUR"));
	ui->pushButton->setText(GET_TXT("IDCS_QUERY"));
	ui->pushButton_2->setText(GET_TXT("IDCS_SET"));
	ui->label->setText(GET_TXT("IDCS_ATTENUATION"));

	connect(mQurAntennaBtn, SIGNAL(clicked()), this, SLOT(slot_QurAntennaBtnClicked()));
	connect( mSetAntennaBtn, SIGNAL( clicked()), this, SLOT( slot_SetAntennaBtnClicked( ) ) );
}

AntennaPrmForm::~AntennaPrmForm()
{
    delete ui;
}

bool AntennaPrmForm::QurAntenna()
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

	unsigned int nPortEnable = 0, nPollTime=0,nParam=0;
	bool bRet = SAAT_YAntennaPort_EXQuery(
		pReaderDllBase->m_hCom,
		&nPortEnable,
		&nPollTime,
		&nParam);
	if(bRet)
	{
		
		mAntenna1CheckBox->setChecked(((BYTE)((nPortEnable) >> 24 ) & 0x01) == 0x01);
		mAntenna2CheckBox->setChecked(((BYTE)((nPortEnable) >> 16 ) & 0x01) == 0x01);
		mAntenna3CheckBox->setChecked(((BYTE)((nPortEnable) >> 8 ) & 0x01) == 0x01);
		mAntenna4CheckBox->setChecked(((BYTE)((nPortEnable)) & 0x01) == 0x01);

		mAntenna1TimeSb->setValue(0xff&(nPollTime >> 24 ));
		mAntenna2TimeSb->setValue(0xff&(nPollTime >> 16 ));
		mAntenna3TimeSb->setValue(0xff&(nPollTime >> 8 ));
		mAntenna4TimeSb->setValue(0xff&(nPollTime >> 0 ));

		mFreqPwrCb1->setCurrentIndex(0xff & (nParam >> 24));
		mFreqPwrCb2->setCurrentIndex(0xff & (nParam >> 16));
		mFreqPwrCb3->setCurrentIndex(0xff & (nParam >> 8));
		mFreqPwrCb4->setCurrentIndex(0xff & (nParam >> 0));
	}

	if (bRet)
	{
		MainShowMsg(GET_TXT("IDCS_ANTENNA_STATE_QUERY_SUCCESS"));
	}
	else
	{
		MainShowMsg(GET_TXT("IDCS_ANTENNA_STATE_QUERY_FAILED"),true);
	}

	return bRet;
}

bool AntennaPrmForm::SetAntenna()
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


	nParam += (mFreqPwrCb1->currentIndex()) << 24;
	nParam += (mFreqPwrCb2->currentIndex()) << 16;
	nParam += (mFreqPwrCb3->currentIndex()) << 8;
	nParam += (mFreqPwrCb4->currentIndex());


	bool bRet = SAAT_YAntennaPort_EXSet( 
		pReaderDllBase->m_hCom,
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
