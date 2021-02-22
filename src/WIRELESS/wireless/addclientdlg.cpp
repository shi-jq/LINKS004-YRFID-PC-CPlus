#include "addclientdlg.h"
#include "ui_addclientdlg.h"
#include "LanguageSrc.h"
#include "widgetconfig.h"
#include "WirelessRecvCtrl.h"
#include "mainapp.h"
#include "wirelessrecv.h"
#include "appconfig.h"

AddClientDlg::AddClientDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddClientDlg)
{
    ui->setupUi(this);
	this->setWindowTitle(GET_TXT("IDCS_READER_ADD"));

	mConnetStackedWidget = ui->stackedWidget;
	mConnetBtn = ui->pushButton;
	mIpAddrCb = ui->comboBox_3;
	mIpAddrCb->setEditable(true);
	mComCb = ui->comboBox;
	mBaudRateCb = ui->comboBox_2;
	mConnetTypeCb = ui->comboBox_4;
	mLinkWidget = ui->widget_2;
	mUdpIpAddrCb = ui->comboBox_6;
	mUsbCb = ui->comboBox_7;
	mUsbBaudRateCb = ui->comboBox_5;
	mCannelBtn = ui->pushButton_2;
	ui->label_11->setText(GET_TXT("IDCS_LINK_TYPE"));
	ui->label_2->setText(GET_TXT("IDCS_IP_ADDR"));
	ui->label_10->setText(GET_TXT("IDCS_IP_ADDR"));
	ui->label_4->setText(GET_TXT("IDCS_COM_NAME"));
	ui->label->setText(GET_TXT("IDCS_BAUDRATE"));
	ui->label_13->setText(GET_TXT("IDCS_USB_PORT"));
	ui->label_3->setText(GET_TXT("IDCS_BAUDRATE"));
	ui->pushButton->setText(GET_TXT("IDCS_READER_ADD"));
	ui->pushButton_2->setText(GET_TXT("IDCS_CANCEL"));

	mConnetStackedWidget->setCurrentIndex(0);
	mUdpIpAddrCb->setEditable(true);

	mConnetTypeCb->addItem(QString("TCP"),Connet_TCP);
	mConnetTypeCb->addItem(QString("COM"),Connet_COM);
	mConnetTypeCb->addItem(QString("USB"),Connet_USB);
	mConnetTypeCb->addItem(QString("UDP"),Connet_UDP);
	
	mConnetTypeCb->setCurrentIndex(WIDGETSTRING_GET("AddClientDlg","CONNET_TYPE").toUInt());
	slot_ConnetTypeIndexChanged(mConnetTypeCb->currentIndex());
	QStringList sl;
	sl<<QString("COM1")
		<<QString("COM2")
		<<QString("COM3")
		<<QString("COM4")
		<<QString("COM5")
		<<QString("COM6")
		<<QString("COM7")
		<<QString("COM8")
		<<QString("COM9");

	mComCb->addItems(sl);
	mUsbCb->addItems(sl);

	QString defaultComName = WIDGETSTRING_GET("AddClientDlg","COM_NAME");
	if (!defaultComName.isEmpty())
	{
		mComCb->setCurrentIndex(mComCb->findText(defaultComName));
	}
	else
	{
		mComCb->setCurrentIndex(0);	
	}

	QString defaultUSBName = WIDGETSTRING_GET("AddClientDlg","USB_NAME");
	if (!defaultUSBName.isEmpty())
	{
		mUsbCb->setCurrentIndex(mUsbCb->findText(defaultUSBName));
	}
	else
	{
		mUsbCb->setCurrentIndex(0);	
	}
	sl.clear();
	sl<<QString("4800")
		<<QString("9600")
		<<QString("19200")
		<<QString("56000")
		<<QString("115200")
		<<QString("128000")
		<<QString("230400")
		<<QString("256000")
		<<QString("460800");
	mBaudRateCb->addItems(sl);
	mUsbBaudRateCb->addItems(sl);
	QString defaultBaudRate = WIDGETSTRING_GET("AddClientDlg","COM_BAUDRATE");
	if (!defaultBaudRate.isEmpty())
	{
		mBaudRateCb->setCurrentIndex(mBaudRateCb->findText(defaultBaudRate));
	}
	else
	{
		mBaudRateCb->setCurrentIndex(4);
	}

	QString defaultUsbBaudRate = WIDGETSTRING_GET("AddClientDlg","USB_BAUDRATE");
	if (!defaultUsbBaudRate.isEmpty())
	{
		mUsbBaudRateCb->setCurrentIndex(mUsbBaudRateCb->findText(defaultUsbBaudRate));
	}
	else
	{
		mUsbBaudRateCb->setCurrentIndex(4);
	}

	mIpAddrCb->setEditText(WIDGETSTRING_GET("AddClientDlg","TCP_ADDR"));
	mUdpIpAddrCb->setEditText(WIDGETSTRING_GET("AddClientDlg","UDP_ADDR"));

	mConnetBtn->setEnabled(true);

	connect( mConnetBtn, SIGNAL( clicked()), this, SLOT( slot_connetBtnClicked( ) ) );
	connect( mConnetTypeCb, SIGNAL( currentIndexChanged(int)), this, SLOT( slot_ConnetTypeIndexChanged(int ) ) );
	connect( mCannelBtn, SIGNAL( clicked()), this, SLOT( slot_cannelBtnClicked( ) ) );

	
}

AddClientDlg::~AddClientDlg()
{
    delete ui;
}

void AddClientDlg::slot_ConnetTypeIndexChanged(int index)
{
	if (index == -1)
	{
		return;
	}

	mConnetStackedWidget->setCurrentIndex(index);
}

void AddClientDlg::slot_connetBtnClicked()
{
	bool bRet = false;
	if (mConnetTypeCb->currentIndex() == Connet_TCP)
	{
		int nPort = WIDGETSTRING_GET("AddClientDlg","TCP_PORT").toInt();
		QString ipAddr = mIpAddrCb->currentText();	
		
		if (!CSingleton<AppConfig>::GetInstance()->CheckIPEdit(ipAddr))
		{
			MainShowMsg(GET_TXT("IDCS_IPADDR_INVAID"));
			return ;
		}
		//调用API
		bRet = WIRELESS_AddTcpClient(WIRELESSRECV_HANDLE,
				ipAddr.toUtf8().data(),
				nPort,
				WirelessRecvDlg::PacketCallbackFunction);
		if (bRet)
		{
			MainShowMsg(GET_TXT("IDCS_ADD_SUCCESS"));
		}
		else
		{
			MainShowMsg(GET_TXT("IDCS_ADD_FAILED"));
		}

		WIDGETSTRING_SET("AddClientDlg","TCP_ADDR",ipAddr.toUtf8().data());
		WIDGETSTRING_SET("AddClientDlg","CONNET_TYPE",(QString("%1").arg(Connet_TCP).toUtf8().data()));

	}
	else if(mConnetTypeCb->currentIndex() == Connet_COM)
	{
		//调用API
		bRet = WIRELESS_AddCOMReader(WIRELESSRECV_HANDLE,
			0x00,
			mComCb->currentText().toUtf8().data(),
			mBaudRateCb->currentText().toInt(),
			WirelessRecvDlg::PacketCallbackFunction);
		if (bRet)
		{
			MainShowMsg(GET_TXT("IDCS_ADD_SUCCESS"));
		}
		else
		{
			MainShowMsg(GET_TXT("IDCS_ADD_FAILED"));
		}

		WIDGETSTRING_SET("AddClientDlg","COM_NAME",mComCb->currentText().toUtf8().data());
		WIDGETSTRING_SET("AddClientDlg","COM_BAUDRATE",mBaudRateCb->currentText().toUtf8().data());
		WIDGETSTRING_SET("AddClientDlg","CONNET_TYPE",QString("%1").arg(Connet_COM).toUtf8().data());

	}
	else if(mConnetTypeCb->currentIndex() == Connet_USB)
	{

		//调用API
		bRet = WIRELESS_AddUSBReader(WIRELESSRECV_HANDLE,
			0x00,
			mUsbCb->currentText().toUtf8().data(),
			mUsbBaudRateCb->currentText().toInt(),
			WirelessRecvDlg::PacketCallbackFunction);
		if (bRet)
		{
			MainShowMsg(GET_TXT("IDCS_ADD_SUCCESS"));
		}
		else
		{
			MainShowMsg(GET_TXT("IDCS_ADD_FAILED"));
		}

		WIDGETSTRING_SET("AddClientDlg","USB_NAME",mUsbCb->currentText().toUtf8().data());
		WIDGETSTRING_SET("AddClientDlg","USB_BAUDRATE",mUsbBaudRateCb->currentText().toUtf8().data());
		WIDGETSTRING_SET("AddClientDlg","CONNET_TYPE",QString("%1").arg(Connet_USB).toUtf8().data());

	}
	else if(mConnetTypeCb->currentIndex() == Connet_UDP)
	{
		int nPort = WIDGETSTRING_GET("AddClientDlg","UDP_PORT").toInt();
		QString ipAddr = mUdpIpAddrCb->currentText();	
		
		if (!CSingleton<AppConfig>::GetInstance()->CheckIPEdit(ipAddr))
		{
			MainShowMsg(GET_TXT("IDCS_IPADDR_INVAID"));
			return ;

		}

		//调用API
		bRet = WIRELESS_AddUDPReader(WIRELESSRECV_HANDLE,
			ipAddr.toUtf8().data(),
			nPort,
			WirelessRecvDlg::PacketCallbackFunction);
		if (bRet)
		{
			MainShowMsg(GET_TXT("IDCS_ADD_SUCCESS"));
		}
		else
		{
			MainShowMsg(GET_TXT("IDCS_ADD_FAILED"));
		}


		WIDGETSTRING_SET("AddClientDlg","UDP_ADDR",ipAddr.toUtf8().data());
		WIDGETSTRING_SET("AddClientDlg","CONNET_TYPE",(QString("%1").arg(Connet_UDP).toUtf8().data()));
	}
	

	if (bRet)
	{
		this->hide();
	}
}

void AddClientDlg::slot_cannelBtnClicked()
{
	this->hide();
}
