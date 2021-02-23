#include "workdpacedlg.h"
#include "ui_workdpacedlg.h"
#include "widgetconfig.h"
#include "LanguageSrc.h"
#include <QKeyEvent>
#include "mainapp.h"

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

void workDpaceDlg::UpdateReaderState(int nConnetType)
{
	
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
}

void workDpaceDlg::CreateView()
{
	mWirelessRecvDlg = new WirelessRecvDlg(ui->tabWidget);
	mTabWidget->addTab(mWirelessRecvDlg,QIcon(),GET_TXT("IDCS_WIRELESS_RECV"));
	mLeftBtn->hide();
	mDownBtn->show();
	connect( mTabWidget, SIGNAL( currentChanged(int)), this, SLOT( slot_tabChanged( int) ) );	
}
