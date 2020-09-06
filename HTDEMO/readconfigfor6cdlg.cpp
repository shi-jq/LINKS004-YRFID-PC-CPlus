#include "readconfigfor6cdlg.h"
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

ReadConfigFor6CDlg::ReadConfigFor6CDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReadConfigFor6CDlg)
{
    ui->setupUi(this);
	CreateView();
	updateLanguage();
	mIsFirst= true;
    ui->widget_10->setEnabled(false);
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
}

void ReadConfigFor6CDlg::updateLanguage()
{
	
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
		mIsFirst = !QurAll();	
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
