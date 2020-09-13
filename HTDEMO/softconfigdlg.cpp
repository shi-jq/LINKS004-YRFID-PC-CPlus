#include "softconfigdlg.h"
#include "ui_softconfigdlg.h"
#include <QSettings>
#include <QFileDialog>
#include "LanguageSrc.h"
#include "appconfig.h"
#include "mainapp.h"
#include "RFIDAPIEXPORT.h"
#include "readerdllbase.h"
#include "mainapp.h"
#include "mainwindow.h"
#include "readermanager.h"
#include "MessageBox.h"
#include "widgetconfig.h"

SoftConfigDlg::SoftConfigDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SoftConfigDlg)
{
    ui->setupUi(this);
	this->setWindowTitle(GET_TXT("IDCS_SOFT_CONFIG"));

	m_languageCb= ui->comboBox;
	mSetBtn=ui->pushButton;
	mCancelBtn=ui->pushButton_2;
	mBrowseBtn = ui->pushButton_3;
	mFileNameEdit = ui->lineEdit;



	connect( mSetBtn, SIGNAL( clicked()), this, SLOT( slot_SetBtnClicked( ) ) );
	connect( mCancelBtn, SIGNAL( clicked()), this, SLOT( slot_CancelBtnClicked( ) ) );
	connect( mBrowseBtn, SIGNAL( clicked()), this, SLOT( slot_BrowseBtnClicked( ) ) );


	ui->label->setText(GET_TXT("IDCS_LANGUAGE_CONFIG"));
	ui->pushButton->setText(GET_TXT("IDCS_SET"));
	ui->pushButton_2->setText(GET_TXT("IDCS_CANCEL"));
	ui->label_4->setText(GET_TXT("IDCS_REBOOT_ENABLE"));
	ui->label_2->setText(GET_TXT("IDCS_SAVE_FILE"));
	ui->pushButton_3->setText(GET_TXT("IDCS_BROWSE"));
}

SoftConfigDlg::~SoftConfigDlg()
{
    delete ui;
}

void SoftConfigDlg::showEvent(QShowEvent *ev)
{
	initLanguageCb();	
	InitSaveLogFile();
	QDialog::showEvent(ev);
}


void SoftConfigDlg::slot_SetBtnClicked()
{
	if (HtMessageBox::Question(GET_TXT("IDCS_IF_REBOOT_SOFT"),this)
		== HtMessageBox::RET_ENTER )
	{
		SetLanguageConfig();
		pMainApp->GetMainWindow()->CutConnet();
		pMainApp->GetMainWindow()->SetNeedReboot(true);
		qApp->quit();
	}

}

void SoftConfigDlg::slot_CancelBtnClicked()
{
	this->reject();
}

void SoftConfigDlg::initLanguageCb()
{
	m_languageCb->clear();
	QString languageIniStr = CSingleton<AppConfig>::GetInstance()->GetLanguageFileName();
	languageIniStr = QString( "%1/LanguageIndex.ini" ).arg(  languageIniStr );
	QSettings settings( languageIniStr, QSettings::IniFormat );
	settings.setIniCodec( "UTF-8" );
	settings.beginGroup("languages");
	QStringList languageList = settings.allKeys();
	QString vauleStr;
	QString keyStr;
	for (int i=0; i<languageList.count(); ++i)
	{
		keyStr = languageList.at(i);
		vauleStr= settings.value(keyStr).toString();
		if (!vauleStr.isEmpty())
		{
			m_languageCb->addItem(vauleStr,keyStr);
		}
	}
	settings.endGroup();
	settings.beginGroup("info");
	keyStr= settings.value("languagesSel").toString();
	settings.endGroup();
	if (!keyStr.isEmpty())
	{
		vauleStr=settings.value(QString("languages/%1").arg(keyStr)).toString();
		m_languageCb->setCurrentIndex(m_languageCb->findText(vauleStr));
	}
	else
	{
		m_languageCb->setCurrentIndex(0);
	}

}



void SoftConfigDlg::SetLanguageConfig()
{
	QString languageIniStr = CSingleton<AppConfig>::GetInstance()->GetLanguageFileName();
	languageIniStr = QString( "%1/LanguageIndex.ini" ).arg(  languageIniStr );
	QSettings settings( languageIniStr, QSettings::IniFormat );
	settings.setIniCodec( "UTF-8" );
	settings.beginGroup("info");
	QString keyStr = m_languageCb->itemData(m_languageCb->currentIndex()).toString();
	settings.setValue("languagesSel",keyStr);
	settings.endGroup();
}


void SoftConfigDlg::slot_BrowseBtnClicked()
{
	QString fileName = QFileDialog::getSaveFileName(this,
		GET_TXT("IDCS_SELECT_FILE"), "./", tr("All Files (*.*)"));
	mFileNameEdit->setText(fileName);
}

void SoftConfigDlg::InitSaveLogFile()
{
	QString fileStr = WIDGETSTRING_GET("ReadCardFor6CDlg","SaveFile");
	if (!fileStr.isEmpty())
	{
		mFileNameEdit->setText(fileStr);
	}	
}


void SoftConfigDlg::SetSaveLogFile()
{
	QString fileStr = mFileNameEdit->text();
	WIDGETSTRING_SET("ReadCardFor6CDlg","SaveFile",fileStr.toUtf8().data());
}
