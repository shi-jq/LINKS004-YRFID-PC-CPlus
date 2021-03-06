﻿#include "readconfigfor6cdlg.h"
#include "ui_readconfigfor6cdlg.h"
#include <assert.h>
#include "RFIDAPIEXPORT.h"
#include "LanguageSrc.h"
#include "mainapp.h"
#include "widgetconfig.h"
#include "appconfig.h"
#include "readerdllbase.h"
#include "readermanager.h"
#include "antennaprmform.h"
#include "carrierconfigform.h"
#include "pointconfigform.h"
#include "buzzerconfigform.h"

ReadConfigFor6CDlg::ReadConfigFor6CDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReadConfigFor6CDlg)
{
    ui->setupUi(this);
	CreateView();
	updateLanguage();
	mIsFirst = true;
}

ReadConfigFor6CDlg::~ReadConfigFor6CDlg()
{
    delete ui;
}

void ReadConfigFor6CDlg::CreateView()
{
	mAntennaPrmForm = new AntennaPrmForm(ui->widget_10);
	QGridLayout* gridLayout = new QGridLayout(ui->widget_10);
	gridLayout->setSpacing(0);
	gridLayout->setContentsMargins(0,0,0,0);
	gridLayout->addWidget(mAntennaPrmForm);	
	//ui->widget_9->hide();

	mCarrierConfigForm = new CarrierConfigForm(ui->widget_12);
	gridLayout = new QGridLayout(ui->widget_12);
	gridLayout->setSpacing(0);
	gridLayout->setContentsMargins(0,0,0,0);
	gridLayout->addWidget(mCarrierConfigForm);	

	mPointConfigForm = new PointConfigForm(ui->widget_14);
	gridLayout = new QGridLayout(ui->widget_14);
	gridLayout->setSpacing(0);
	gridLayout->setContentsMargins(0,0,0,0);
	gridLayout->addWidget(mPointConfigForm);	


	mBuzzerConfigForm = new BuzzerConfigForm(ui->widget_16);
	gridLayout = new QGridLayout(ui->widget_16);
	gridLayout->setSpacing(0);
	gridLayout->setContentsMargins(0, 0, 0, 0);
	gridLayout->addWidget(mBuzzerConfigForm);

	ui->widget_13->hide();
}

void ReadConfigFor6CDlg::updateLanguage()
{
	ui->label_16->setText(GET_TXT("IDCS_ANTENNA_PORT_SET"));
	ui->label_18->setText(GET_TXT("IDCS_RADIO_CONFIG"));
	ui->label_17->setText(GET_TXT("IDCS_CARRIER_PARAM"));
	ui->label_19->setText(GET_TXT("IDCS_READ_SOUND"));
}

void ReadConfigFor6CDlg::showEvent(QShowEvent *event)
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
        //mIsFirst = !QurAll();
	}
	QWidget::showEvent(event);
}

bool ReadConfigFor6CDlg::QurAll()
{
	if (!mAntennaPrmForm->QurAntenna())
	{
		return false;
	}

	if(!mCarrierConfigForm->QueryAll())
	{
		return false;
	}

	if(!mPointConfigForm->QueryAll())
	{
		return false;
	}
	return true;
}
