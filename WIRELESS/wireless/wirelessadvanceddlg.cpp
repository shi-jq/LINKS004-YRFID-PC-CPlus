#include "wirelessadvanceddlg.h"
#include "ui_wirelessadvanceddlg.h"
#include "LanguageSrc.h"
#include "widgetconfig.h"
#include "mainapp.h"


WirelessAdvancedDlg::WirelessAdvancedDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WirelessAdvancedDlg)
{
    ui->setupUi(this);
	this->setWindowTitle(GET_TXT("IDCS_SOFT_CONFIG"));	
	mCheckConnetTimeEdit = ui->lineEdit_2;
	mOkBtn = ui->pushButton;
	mCheckRefashTimeEdit = ui->lineEdit_3;	
	mCannelBtn =  ui->pushButton_2;
	ui->label_4->setText(GET_TXT("IDCS_CHECK_DISCONNET_TIME"));
	ui->label_6->setText(GET_TXT("IDCS_SECOND"));
	ui->label_8->setText(GET_TXT("IDCS_SECOND"));
	ui->label_7->setText(GET_TXT("IDCS_CHECK_REFASH_TIME"));

	ui->pushButton->setText(GET_TXT("IDCS_OK"));
	mCannelBtn->setText(GET_TXT("IDCS_CANCEL"));
	mCannelBtn->hide();


	int nOnlineTime = WIDGETSTRING_GET("WirelessAdvancedDlg","CHECK_ONLINE_TIME").toInt();
	mCheckConnetTimeEdit->setText(QString::number(nOnlineTime));	
	mCheckRefashTimeEdit->setText(WIDGETSTRING_GET("WirelessAdvancedDlg","CHECK_ONLINE_REFASH_TIME"));
	

	connect( mOkBtn, SIGNAL( clicked()), this, SLOT( slot_OkBtnClicked( ) ) );
	connect( mCannelBtn, SIGNAL( clicked()), this, SLOT( slot_CannelBtnClicked( ) ) );

}

WirelessAdvancedDlg::~WirelessAdvancedDlg()
{
    delete ui;
}


QString WirelessAdvancedDlg::GetCheckOnlineTime()
{
	return mCheckConnetTimeEdit->text();
}

void WirelessAdvancedDlg::slot_OkBtnClicked()
{
	int nOnlineTime = WIDGETSTRING_GET("WirelessAdvancedDlg","CHECK_ONLINE_TIME").toInt();

	WIDGETSTRING_SET("WirelessAdvancedDlg","CHECK_ONLINE_TIME",mCheckConnetTimeEdit->text().toUtf8().data());
	WIDGETSTRING_SET("WirelessAdvancedDlg","CHECK_ONLINE_REFASH_TIME",mCheckRefashTimeEdit->text().toUtf8().data());	

	this->accept();
}

void WirelessAdvancedDlg::closeEvent(QCloseEvent * e)
{
	slot_OkBtnClicked();
	this->reject();
}

QString WirelessAdvancedDlg::GetCheckOnlineRefashTime()
{
	return mCheckRefashTimeEdit->text();
}



void WirelessAdvancedDlg::slot_CannelBtnClicked()
{
	this->reject();
}