#include "wirelesstcpserverconfigdlg.h"
#include "ui_wirelesstcpserverconfigdlg.h"
#include <QtNetwork/QNetworkInterface>
#include <QtNetwork/QHostAddress>
#include "LanguageSrc.h"
#include "widgetconfig.h"
#include "mainapp.h"

WirelessTcpServerConfigDlg::WirelessTcpServerConfigDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WirelessTcpServerConfigDlg)
{
    ui->setupUi(this);
	this->setWindowTitle(GET_TXT("IDCS_SERVER_CONFIG"));
	ui->label->setText(GET_TXT("IDCS_SERVER_ADDR"));
	ui->label_2->setText(GET_TXT("IDCS_LISENT_PORT"));
	ui->pushButton->setText(GET_TXT("IDCS_OK"));
	mServerAddrCb = ui->comboBox_2;
	mServerPortEdit = ui->lineEdit;
	mCannelBtn = ui->pushButton_2;
	mServerAddrCb->setEditable(true);
	mOkBtn = ui->pushButton;

	mCannelBtn->setText(GET_TXT("IDCS_CANCEL"));

	QList<QHostAddress> nets =QNetworkInterface::allAddresses();
	for (int i=0; i<nets.size(); ++i)
	{
		QHostAddress item = nets.at(i);
		if (item.protocol() == QAbstractSocket::IPv4Protocol)
		{
			mServerAddrCb->addItem(item.toString());	
		}				
	}

	int nPort = WIDGETSTRING_GET("WirelessAdvancedDlg","TCP_SERVER_PORT").toInt();
	QString ipAddr = WIDGETSTRING_GET("WirelessAdvancedDlg","TCP_SERVER_ADDR");
	mServerAddrCb->setEditText(ipAddr);
	mServerPortEdit->setText(QString::number(nPort));

	connect( mOkBtn, SIGNAL( clicked()), this, SLOT( slot_OkBtnClicked( ) ) );
	connect( mCannelBtn, SIGNAL( clicked()), this, SLOT( slot_CannelBtnClicked( ) ) );
}

WirelessTcpServerConfigDlg::~WirelessTcpServerConfigDlg()
{
    delete ui;
}

QString WirelessTcpServerConfigDlg::GetServerIp()
{
	return mServerAddrCb->currentText();
}

QString WirelessTcpServerConfigDlg::GetServerPort()
{
	return mServerPortEdit->text();
}

void WirelessTcpServerConfigDlg::slot_OkBtnClicked()
{
	int nPort = WIDGETSTRING_GET("WirelessAdvancedDlg","TCP_SERVER_PORT").toInt();
	QString ipAddr = WIDGETSTRING_GET("WirelessAdvancedDlg","TCP_SERVER_ADDR");

	WIDGETSTRING_SET("WirelessAdvancedDlg","TCP_SERVER_PORT",mServerPortEdit->text().toUtf8().data());
	WIDGETSTRING_SET("WirelessAdvancedDlg","TCP_SERVER_ADDR",mServerAddrCb->currentText().toUtf8().data());
	this->accept();
}

void WirelessTcpServerConfigDlg::closeEvent(QCloseEvent * e)
{
	slot_OkBtnClicked();
	this->reject();
}

void WirelessTcpServerConfigDlg::slot_CannelBtnClicked()
{
	//QDialog::rejected();
	this->reject();
}
