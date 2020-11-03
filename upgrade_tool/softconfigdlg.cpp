#include "softconfigdlg.h"
#include "ui_softconfigdlg.h"
#include <QSettings>
#include <QFileDialog>
#include "LanguageSrc.h"
#include "appconfig.h"
#include "mainapp.h"
#include "widgetconfig.h"
#include "adb_tool.h"
#include "MessageBox.h"
#include "adb_tool.h"

SoftConfigDlg::SoftConfigDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SoftConfigDlg)
{
    ui->setupUi(this);
	this->setWindowTitle(GET_TXT("IDCS_SOFT_CONFIG"));

	m_languageCb= ui->comboBox;
	mSetBtn=ui->pushButton;
    mCancelBtn=ui->pushButton_2;

	connect( mSetBtn, SIGNAL( clicked()), this, SLOT( slot_SetBtnClicked( ) ) );
    connect( mCancelBtn, SIGNAL( clicked()), this, SLOT( slot_CancelBtnClicked( ) ) );

	ui->label->setText(GET_TXT("IDCS_LANGUAGE_CONFIG"));
	ui->pushButton->setText(GET_TXT("IDCS_SET"));
    ui->pushButton_2->setText(GET_TXT("IDCS_CANCEL"));
	ui->lineEdit->setText(defaultApkPackage);
	ui->lineEdit_2->setText(defaultApkActivity);



}

SoftConfigDlg::~SoftConfigDlg()
{
    delete ui;
}

void SoftConfigDlg::setMainwindow(adb_tool* tool)
{
	this->mainwindow = tool;
}

void SoftConfigDlg::showEvent(QShowEvent *ev)
{
	initLanguageCb();	
	InitPagActy();
	QDialog::showEvent(ev);
}


void SoftConfigDlg::slot_SetBtnClicked()
{
	
	if (HtMessageBox::Question(GET_TXT("IDCS_IF_REBOOT_SOFT"),this)
		== HtMessageBox::RET_ENTER )
	{
		SetLanguageConfig();

		QString ApkPackage = ui->lineEdit->text();
		WIDGETSTRING_SET("adb_tool", "ApkPackage", ApkPackage.toUtf8().data());

		QString ApkActivity = ui->lineEdit_2->text();
		WIDGETSTRING_SET("adb_tool", "ApkActivity", ApkActivity.toUtf8().data());

		mainwindow->SetNeedReboot(true);
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

void SoftConfigDlg::InitPagActy()
{
	QString ApkPackage = WIDGETSTRING_GET("adb_tool", "ApkPackage");
	if (!ApkPackage.isEmpty())
	{
		ui->lineEdit->setText(ApkPackage);
	}

	QString ApkActivity = WIDGETSTRING_GET("adb_tool", "ApkActivity");
	if (!ApkActivity.isEmpty())
	{
		ui->lineEdit_2->setText(ApkActivity);
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


