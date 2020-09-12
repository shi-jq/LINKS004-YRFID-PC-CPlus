#include "workdpacedlg.h"
#include "ui_workdpacedlg.h"
#include "widgetconfig.h"
#include "LanguageSrc.h"
#include "readerdllbase.h"
#include <QKeyEvent>
#include "mainapp.h"
#include "tabsysinfoform.h"
#include "readconfigfor6cdlg.h"
#include "readcardfor6cdlg.h"
#include "tabconnetinfoform.h"
#include "tabapplyinfoform.h"
#include "tabparamconfigform.h"
#include "tabuploadform.h"
#include "tabforwardconfigform.h"

workDpaceDlg::workDpaceDlg(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::workDpaceDlg)
{
    ui->setupUi(this);
	mTabWidget = ui->tabWidget;	

	mLeftBtn = ui->LeftPushBtn;
	mDownBtn = ui->DownPushBtn;
	connect( mLeftBtn, SIGNAL( clicked()), this, SLOT( slot_leftBtnClicked( ) ) );
	connect( mDownBtn, SIGNAL( clicked()), this, SLOT( slot_downBtnClicked( ) ) );

	CreateView();	
}

workDpaceDlg::~workDpaceDlg()
{
    delete ui;
}

void workDpaceDlg::setDownBtnUp(bool isDown)
{
	QString imageStr;
	if (isDown)
	{
		imageStr = "cebian_down";
	}
	else
	{
		imageStr = "cebian_up";
	}

	QString styleSheetStr = QString("QPushButton {	\
									background: transparent; \
									border: 0px;\
									border-image: \
									url(:/cebian/skin/%1.png) 0 0 36 0  ;\
									}\
									QPushButton:hover, QPushButton:focus {\
									border-image: \
									url(:/cebian/skin/%1.png) 12 0 24 0 ;\
									}\
									QPushButton:pressed {\
									border-image: \
									url(:/cebian/skin/%1.png) 24 0 12 0  ;\
									}\
									QPushButton:disabled {\
									border-image:\
									url(:/cebian/skin/%1.png) 0 0 0 36  ;\
									}\
									QPushButton:checked {\
									border-image: \
									url(:/cebian/skin/%1.png) 24 0 12 0  ;\
									}\
									QPushButton:focus:!hover {\
									border-image:\
									url(:/cebian/skin/%1.png) 0 0 36 0 ;\
									}\
									QPushButton:focus:!hover {\
									border-image: \
									url(:/cebian/skin/%1.png) 0 0 36 0  ;\
									}").arg(imageStr);
	mDownBtn->setStyleSheet(styleSheetStr);
}

void workDpaceDlg::setLeftBtnRight(bool isDown)
{
	QString imageStr;
	if (isDown)
	{
		imageStr = "cebian_left";
	}
	else
	{
		imageStr = "cebian_right";
	}

	QString styleSheetStr = QString("QPushButton {	\
									background: transparent; \
									border: 0px;\
									border-image: \
									url(:/cebian/skin/%1.png) 0 36 0 0 ;\
									}\
									QPushButton:hover, QPushButton:focus {\
									border-image: \
									url(:/cebian/skin/%1.png) 0 24 0 12 ;\
									}\
									QPushButton:pressed {\
									border-image: \
									url(:/cebian/skin/%1.png) 0 12 0 24 ;\
									}\
									QPushButton:disabled {\
									border-image: \
									url(:/cebian/skin/%1.png) 0 0 36 0 ;\
									}\
									QPushButton:checked {\
									border-image: \
									url(:/cebian/skin/%1.png) 0 12 0 24 ;\
									}\
									QPushButton:focus:!hover {\
									border-image: url(:/cebian/skin/%1.png) 0 36 0 0 ;\
									}\
									QPushButton:focus:!hover {\
									border-image:\
									url(:/cebian/skin/%1.png) 0 36 0 0 ;\
									}").arg(imageStr);

	mLeftBtn->setStyleSheet(styleSheetStr);
}

void workDpaceDlg::slot_leftBtnClicked()
{
	emit leftBtnClicked();
}

void workDpaceDlg::slot_downBtnClicked()
{
	emit downBtnClicked();
}

void workDpaceDlg::slot_tabChanged(int index)
{
	if (pMainApp->IsReading())
	{
		if (index != 0)
		{
			MainShowMsg(GET_TXT("IDCS_READING_CARD"),false,false);
			mTabWidget->setCurrentIndex(0);
		}
	}
}

void workDpaceDlg::CreateView()
{	
	mReadCardFor6CDlg = new ReadCardFor6CDlg(mTabWidget,this);
	mTabWidget->addTab(mReadCardFor6CDlg,QIcon(),GET_TXT("IDCS_READ_TAG"));

	mReadConfigFor6CDlg = new ReadConfigFor6CDlg(mTabWidget);
	mTabWidget->addTab(mReadConfigFor6CDlg,QIcon(),GET_TXT("IDCS_READ_CARD_CONFIG"));

	mTabSysInfoForm = new TabSysInfoForm(mTabWidget);
	mTabWidget->addTab(mTabSysInfoForm,QIcon(),GET_TXT("IDCS_SYS_CONFIG"));
	
    mTabConnetInfoForm = new TabConnetInfoForm(mTabWidget);
    mTabWidget->addTab(mTabConnetInfoForm,QIcon(),GET_TXT("IDCS_CONNET_CONFIG"));

    mTabUploadForm = new TabUploadForm(mTabWidget);
    mTabWidget->addTab(mTabUploadForm,QIcon(),GET_TXT("IDCS_DATA_UPLOAD"));

//	mTabParamConfigForm = new TabParamConfigForm(mTabWidget);
//	mTabWidget->addTab(mTabParamConfigForm,QIcon(),GET_TXT("IDCS_PARAM_CONFIG_OP"));

//	mTabApplyInfoForm = new TabApplyInfoForm(mTabWidget);
//	mTabWidget->addTab(mTabApplyInfoForm,QIcon(),GET_TXT("IDCS_IO_CONTRL"));

    //mTabForwardConfigForm = new TabForwardConfigForm(mTabWidget);
    //mTabWidget->addTab(mTabForwardConfigForm,QIcon(),GET_TXT("IDCS_FORWARD_CONFIG"));
	mLeftBtn->show();
	mDownBtn->show();	

	connect( mTabWidget, SIGNAL( currentChanged(int)), this, SLOT( slot_tabChanged( int) ) );	
}
