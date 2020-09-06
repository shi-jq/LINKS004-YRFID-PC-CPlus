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
#include "connetdlg.h"
#include "oplistdlg.h"
#include "mainapp.h"

#include "firmwareupdatefor6cdlg.h"

#include "busaddrconfigdlg.h"
#include "netconfigfor6cdlg.h"
#include "comconfigdlg.h"
#include "readertimesetdlg.h"
#include "flashconfigfor6cdlg.h"
#include "filtratetagfor6cdlg.h"
#include "qvaluedlg.h"
#include "ioconfigfor6cdlg.h"
#include "paramconfigfor6cdlg.h"
#include "gprsconfigdlg.h"
#include "softconfigdlg.h"
#include "readerdllbase.h"
#include "RFIDAPIEXPORT.h"
#include "MessageBox.h"
#include "versioncommondlg.h"

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent ),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

	this->setWindowTitle(GET_TXT("IDCS_WINTITLE2"));
	pMainApp->SetMainWindow(this);
	
	mIsNeetReboot = false;
	CreateView();
	CreateMenuBar();	
}

MainWindow::~MainWindow()
{
	pMainApp->SetMainWindow(NULL);
    delete ui;
}

void MainWindow::ShowMsg(QString msg,bool getErro,bool getReader)
{
	if (mOpListDlg)
	{
		mOpListDlg->ShowMsg(msg,getErro,getReader);
	}
}

void MainWindow::updateReaderState(int nConnetType)
{
	QMetaObject::invokeMethod(this, "slot_updateReaderState", Qt::QueuedConnection, Q_ARG(int, nConnetType) );
}

void MainWindow::slot_leftBtnClicked()
{
	if (mConnetDlg && mworkDpaceDlg)
	{
		if (mConnetDlg->parentWidget()->isHidden())
		{
//			mConnetDlg->parentWidget()->setShown(true);
			mworkDpaceDlg->setLeftBtnRight(true);
		}
		else
		{
//			mConnetDlg->parentWidget()->setShown(false);
			mworkDpaceDlg->setLeftBtnRight(false);
		}
	}	
}

void MainWindow::slot_downBtnClicked()
{
	if (mOpListDlg && mworkDpaceDlg)
	{
		if (mOpListDlg->parentWidget()->isHidden())
		{
//			mOpListDlg->parentWidget()->setShown(true);
			mworkDpaceDlg->setDownBtnUp(true);
		}
		else
		{
//			mOpListDlg->parentWidget()->setShown(false);
			mworkDpaceDlg->setDownBtnUp(false);
		}
	}	
}


void MainWindow::slot_updateReaderState(int nConnetType)
{
	if (mConnetDlg)
	{
		mConnetDlg->UpdateReaderState(nConnetType);
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

bool MainWindow::checkConnet()
{
	ReaderDllBase*	pReaderDllBase = pMainApp->GetReader();
	if (!pReaderDllBase)
	{
		MainShowMsg(GET_TXT("IDCS_READ_NO_LINK"));
		return false;
	}
	if (pReaderDllBase->CheckState(STATE_READING) )
	{
		MainShowMsg(GET_TXT("IDCS_READING_CARD"));
		return false;
	}

	if (!pReaderDllBase->CheckState(STATE_CONNET))
	{
		MainShowMsg(GET_TXT("IDCS_READ_NO_LINK"));
		return false;
	}

	return true;
}

void MainWindow::CreateMenuBar()
{
	CreateFileMenu();
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


void MainWindow::CreateHelpMenu()
{
	QMenu* helpMenu = NULL;
	
	helpMenu = menuBar()->addMenu(GET_TXT("IDCS_HELP"));
	
	mVersionCommonDlg = new VersionCommonDlg(this);
	mVersionCommonAc = helpMenu->addAction(GET_TXT("IDCS_SOFT_VER"));
	connect( mVersionCommonAc, SIGNAL( triggered()), this, SLOT( slot_VersionCommonAc( ) ) );
	
	
}

void MainWindow::CreateView()
{
	QGridLayout* gridLayout = NULL;
	
	mConnetDlg = new ConnetDlg(ui->widget);	
	gridLayout = new QGridLayout(ui->widget);
	gridLayout->setSpacing(0);
	gridLayout->setContentsMargins(0,0,0,0);
	gridLayout->addWidget(mConnetDlg);	
	
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
	ui->widget_3->setMinimumHeight(150);
	ui->widget_3->setMaximumHeight(200);	
	
}

void MainWindow::slot_UpdateReadCount(int count,int speed,int nReset)
{
	if(mConnetDlg)
	{
		mConnetDlg->slot_UpdateReadCount( count, speed,nReset);
	}
}

void MainWindow::CutConnet()
{
	QMetaObject::invokeMethod(this, "slot_CutConnet", Qt::QueuedConnection );
}


void MainWindow::slot_WIFIConfigFor6CAc()
{
	if (!checkConnet())
	{
		return;
	}

	ReaderDllBase*	pReaderDllBase = pMainApp->GetReader();
	if (!pReaderDllBase)
	{
		MainShowMsg(GET_TXT("IDCS_READ_NO_LINK"));
		return;
	}
	if(pReaderDllBase->GetLinkInfo().mconnetType != Connet_COM)
	{
		MainShowMsg(GET_TXT("IDCS_NOT_COM_CANNOT_WIFI"));
		return;
	}
}


void MainWindow::slot_SoftConfigAc()
{
	mSoftConfigDlg->exec();
}

bool MainWindow::isNeedReboot()
{
	return mIsNeetReboot;
}

void MainWindow::SetNeedReboot(bool isneed)
{
	mIsNeetReboot = isneed;
}

void MainWindow::slot_VersionCommonAc()
{
	mVersionCommonDlg->exec();
}

void MainWindow::keyPressEvent(QKeyEvent *ev)
{
	if  (ev->key() == Qt::Key_Escape)
	{
		slot_ExitAc();
	}

	QMainWindow::keyPressEvent(ev);
}

void MainWindow::slot_CutConnet()
{
	mConnetDlg->slot_cutCurConnect();
}
