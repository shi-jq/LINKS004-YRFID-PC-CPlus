﻿#include "tabuploadform.h"
#include "ui_tabuploadform.h"
#include "LanguageSrc.h"
#include "filtratetagfor6cdlg.h"
#include "flashconfigfor6cdlg.h"
#include "uploadpramform.h"
#include "forwardsetdlg.h"
#include "gprsconfigdlg.h"
TabUploadForm::TabUploadForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TabUploadForm)
{
    ui->setupUi(this);

	mFiltrateTagFor6CDlg = new FiltrateTagFor6CDlg(ui->widget_4);
	QGridLayout* gridLayout = new QGridLayout(ui->widget_4);
	gridLayout->setSpacing(0);
	gridLayout->setContentsMargins(0,0,0,0);
	gridLayout->addWidget(mFiltrateTagFor6CDlg);	

	mFlashConfigFor6CDlg = new FlashConfigFor6CDlg(ui->widget_6);
	gridLayout = new QGridLayout(ui->widget_6);
	gridLayout->setSpacing(0);
	gridLayout->setContentsMargins(0,0,0,0);
	gridLayout->addWidget(mFlashConfigFor6CDlg);

	mUploadPramForm = new UploadPramForm(ui->widget_2);
	gridLayout = new QGridLayout(ui->widget_2);
	gridLayout->setSpacing(0);
	gridLayout->setContentsMargins(0,0,0,0);
	gridLayout->addWidget(mUploadPramForm);	


	mForwardSetDlg = new ForwardSetDlg(ui->widget_8);
	gridLayout = new QGridLayout(ui->widget_8);
	gridLayout->setSpacing(0);
	gridLayout->setContentsMargins(0, 0, 0, 0);
	gridLayout->addWidget(mForwardSetDlg);

	//*
	mGprsConfigDlg = new GprsConfigDlg(ui->widget_10);
	gridLayout = new QGridLayout(ui->widget_10);
	gridLayout->setSpacing(0);
	gridLayout->setContentsMargins(0, 0, 0, 0);
	gridLayout->addWidget(mGprsConfigDlg);
	//*/
	ui->widget_5->hide();

	ui->label_6->setText(GET_TXT("IDCS_UP_CONFIG"));
	ui->label_9->setText(GET_TXT("IDCS_NET_CONFIG"));
	ui->label_7->setText(GET_TXT("IDCS_FILTER_TAG"));
	ui->label_8->setText(GET_TXT("IDCS_FLASH"));
	ui->label_10->setText(GET_TXT("IDCS_CPRS_CONFIG"));
}

TabUploadForm::~TabUploadForm()
{
    delete ui;
}
