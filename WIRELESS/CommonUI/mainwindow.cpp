#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCloseEvent>
#include <QDesktopServices>
#include <QUrl>
#include <QMenuBar>
#include "appconfig.h"
#include "widgetconfig.h"
#include "LanguageSrc.h"
#include "workdpacedlg.h"
#include "oplistdlg.h"
#include "mainapp.h"
#include "MessageBox.h"
#include "versioncommondlg.h"
#include "softconfigdlg.h"

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent ),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

	this->setWindowTitle(GET_TXT("IDCS_WIRELESS_RECV"));
	pMainApp->SetMainWindow(this);
	mSoftConfigDlg = NULL;
	mIsNeetReboot = false;
	CreateView();
	CreateMenuBar();	
}

MainWindow::~MainWindow()
{
	pMainApp->SetMainWindow(NULL);
    delete ui;
}

void MainWindow::ShowMsg(QString msg,bool getErro)
{
	if (mOpListDlg)
	{
		mOpListDlg->ShowMsg(msg,getErro);
	}
}

void MainWindow::updateReaderState(int nConnetType)
{
	QMetaObject::invokeMethod(this, "slot_updateReaderState", Qt::QueuedConnection, Q_ARG(int, nConnetType) );
}

void MainWindow::slot_leftBtnClicked()
{
	
}

void MainWindow::slot_downBtnClicked()
{
	if (mOpListDlg && mworkDpaceDlg)
	{
		if (mOpListDlg->parentWidget()->isHidden())
		{
			mOpListDlg->parentWidget()->show();
			mworkDpaceDlg->setDownBtnUp(true);
		}
		else
		{
			mOpListDlg->parentWidget()->hide();
			mworkDpaceDlg->setDownBtnUp(false);
		}
	}	
}


void MainWindow::slot_updateReaderState(int nConnetType)
{
	if (mworkDpaceDlg)
	{
		mworkDpaceDlg->UpdateReaderState(nConnetType);
	}	
}


void MainWindow::closeEvent(QCloseEvent *event)
{
	if (HtMessageBox::Question(GET_TXT("IDCS_QUIT_SOFT"),this)
		== HtMessageBox::RET_ENTER )
	{		
		event->accept();
	}
	else
	{
		event->ignore();
	}

	
}

void MainWindow::slot_ExitAc()
{
	if (HtMessageBox::Question(GET_TXT("IDCS_QUIT_SOFT"),this)
		== HtMessageBox::RET_ENTER )
	{
		qApp->quit();
	}
	
}


void MainWindow::slot_HelpAc()
{
	QString fileName =QString("file:///%1")
		.arg(CSingleton<AppConfig>::GetInstance()->GetRunPath()+"/"+WIDGETSTRING_GET("MainWindow","HelpFileName"));
	if(!QDesktopServices::openUrl
		(QUrl
		(fileName, 
		QUrl::TolerantMode)))
	{
		MainShowMsg(GET_TXT("IDCS_NO_HELP_DOC"));
	}
}

void MainWindow::CreateMenuBar()
{
	CreateFileMenu();
	CreateWirelessMenu();
	CreateHelpMenu();
}

void MainWindow::CreateFileMenu()
{
	QMenu* fileMenu = NULL;
	fileMenu = menuBar()->addMenu(GET_TXT("IDCS_FILE"));	
	
	mSoftConfigDlg = new SoftConfigDlg(this);
	mSoftCongfigAc = fileMenu->addAction(GET_TXT("IDCS_SOFT_CONFIG"));
	connect( mSoftCongfigAc, SIGNAL( triggered()), this, SLOT( slot_SoftConfigAc( ) ) );

	mExitAc = fileMenu->addAction(GET_TXT("IDCS_QUIT"));
	connect( mExitAc, SIGNAL( triggered()), this, SLOT( slot_ExitAc( ) ) );		
}

void MainWindow::CreateView()
{
	QGridLayout* gridLayout = NULL;

	mworkDpaceDlg = new workDpaceDlg(ui->widget_2);	
	gridLayout = new QGridLayout(ui->widget_2);
	gridLayout->setSpacing(0);
	gridLayout->setContentsMargins(0,0,0,0);
	gridLayout->addWidget(mworkDpaceDlg);

	connect( mworkDpaceDlg, SIGNAL( leftBtnClicked()), this, SLOT( slot_leftBtnClicked( ) ) );
	connect( mworkDpaceDlg, SIGNAL( downBtnClicked()), this, SLOT( slot_downBtnClicked( ) ) );

	mOpListDlg = new OpListDlg(ui->widget_3);
	gridLayout = new QGridLayout(ui->widget_3);
	gridLayout->setSpacing(0);
	gridLayout->setContentsMargins(0,0,0,0);
	gridLayout->addWidget(mOpListDlg);
	mOpListDlg->setMaximumHeight(150);
}


void MainWindow::CutConnet()
{
	QMetaObject::invokeMethod(this, "slot_CutConnet", Qt::QueuedConnection );
}

void MainWindow::slot_CutConnet()
{
	
}


bool MainWindow::isNeedReboot()
{
	return mIsNeetReboot;
}

void MainWindow::SetNeedReboot(bool isneed)
{
	mIsNeetReboot = isneed;
}


void MainWindow::keyPressEvent(QKeyEvent *ev)
{
	if  (ev->key() == Qt::Key_Escape)
	{
		slot_ExitAc();
	}
	
	QMainWindow::keyPressEvent(ev);
}

void MainWindow::CreateWirelessMenu()
{
	
}

void MainWindow::slot_SoftConfigAc()
{
	mSoftConfigDlg->exec();
}

void MainWindow::CreateHelpMenu()
{
	QMenu* helpMenu = NULL;

	helpMenu = menuBar()->addMenu(GET_TXT("IDCS_HELP"));

	mVersionCommonDlg = new VersionCommonDlg(this);
	mVersionCommonAc = helpMenu->addAction(GET_TXT("IDCS_SOFT_VER"));
	connect( mVersionCommonAc, SIGNAL( triggered()), this, SLOT( slot_VersionCommonAc( ) ) );

}

void MainWindow::slot_VersionCommonAc()
{
	mVersionCommonDlg->exec();
}