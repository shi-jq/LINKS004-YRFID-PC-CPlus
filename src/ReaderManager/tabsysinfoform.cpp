﻿#include "tabsysinfoform.h"
#include "ui_tabsysinfoform.h"
#include "LanguageSrc.h"
#include "readerinfo6cform.h"
#include "firmwareupdatefor6cdlg.h"
#include "readertimesetdlg.h"
#include "rebootdeviceform.h"

TabSysInfoForm::TabSysInfoForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TabSysInfoForm)
{
    ui->setupUi(this);

	mReaderInfo6CForm = new ReaderInfo6CForm(ui->widget_2);
	QGridLayout* gridLayout = new QGridLayout(ui->widget_2);
	gridLayout->setSpacing(0);
	gridLayout->setContentsMargins(0,0,0,0);
	gridLayout->addWidget(mReaderInfo6CForm);	

    mFirmWareUpdateFor6CDlg = new FirmWareUpdateFor6CDlg(ui->widget_4);
    gridLayout = new QGridLayout(ui->widget_4);
    gridLayout->setSpacing(0);
    gridLayout->setContentsMargins(0,0,0,0);
    gridLayout->addWidget(mFirmWareUpdateFor6CDlg);

    mReaderTimeSetDlg = new ReaderTimeSetDlg(ui->widget_6);
    gridLayout = new QGridLayout(ui->widget_6);
    gridLayout->setSpacing(0);
    gridLayout->setContentsMargins(0,0,0,0);
    gridLayout->addWidget(mReaderTimeSetDlg);

	/*mRebootDeviceForm = new RebootDeviceForm(ui->widget_8);
	gridLayout = new QGridLayout(ui->widget_8);
	gridLayout->setSpacing(0);
	gridLayout->setContentsMargins(0,0,0,0);
	gridLayout->addWidget(mRebootDeviceForm);*/


	ui->label_6->setText(GET_TXT("IDCS_READER_INFO"));
	ui->label_7->setText(GET_TXT("IDCS_FIRMWARE_UPDATE"));
	ui->label_8->setText(GET_TXT("IDCS_SYSTEM_TIME"));
    ui->widget_3->hide();
}

TabSysInfoForm::~TabSysInfoForm()
{
    delete ui;
}
