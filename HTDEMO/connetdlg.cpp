#include "connetdlg.h"
#include "ui_connetdlg.h"
#include <QApplication>
#include <QDateTime>
#include "widgetconfig.h"
#include "LanguageSrc.h"
#include "readerdllbase.h"
#include "appconfig.h"
#include "mainapp.h"
#include "MessageBox.h"
#include <QKeyEvent>
#include "readermanager.h"
#include <QMenu>
#include "RFIDAPIEXPORT.h"

ConnetDlg::ConnetDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConnetDlg)
{
    ui->setupUi(this);
	CreateView();
	UpdateLanguage();
	StartUDP();	
	mRefeshTime = 0;
}

ConnetDlg::~ConnetDlg()
{
	if (mUdpWorkerThread)
	{
		delete mUdpWorkerThread;
		mUdpWorkerThread = NULL;
	}

    delete ui;
}

void ConnetDlg::slot_connetBtnClicked()
{
	if (mDeviceList->topLevelItemCount() >= 255)
	{
		MainShowMsg(GET_TXT("IDCS_ADD_READER_MAX"));
		return;
	}
	QTreeWidgetItem*	item = NULL;
	if (mConnetTypeCb->currentIndex() == Connet_TCP)
	{
		item = AddConnectTcp();
	}
	else if(mConnetTypeCb->currentIndex() == Connet_COM)
	{	
		item = AddConnectCom();		
	}
	else if(mConnetTypeCb->currentIndex() == Connet_USB)
	{
		item = AddConnectUsb();
	}
	else if(mConnetTypeCb->currentIndex() == Connet_UDP)
	{
		item = AddConnectUdp();
	}
	else
	{
		Q_ASSERT(false);
	}

	if (!item)
	{
		return;
	}

	SavaIni();

	if(ConnectItem(item))
	{
		SetCurItem(item);
	}
	else if(mDeviceList->topLevelItemCount() == 1)
	{
		SetCurItem(item);
	}	
}

void ConnetDlg::slot_quitBtnClicked()
{
	
	ReaderDllBase*	pReaderDllBase = pMainApp->GetReader();
	if (pReaderDllBase->CheckState(STATE_READING))
	{
		MainShowMsg(GET_TXT("IDCS_READING_CARD"));
		return;
	}

	

	if (HtMessageBox::Question(GET_TXT("IDCS_QUIT_SOFT"),this)
		== HtMessageBox::RET_ENTER )
	{
		ClearAllItem();
		qApp->quit();
	}
	
}

void ConnetDlg::UpdateReaderState(int nConnetType)
{
	bool bEnableEdit = isEnableEdit(nConnetType);

	mConnetBtn->setEnabled(bEnableEdit);	
	mLinkWidget->setEnabled(bEnableEdit);
	mDeviceList->setEnabled(bEnableEdit);
	mClearBtn->setEnabled(bEnableEdit);
	mRebootBtn->setEnabled(bEnableEdit);
	mCutDownBtn->setEnabled(bEnableEdit);
	mConnectItemBtn->setEnabled(bEnableEdit);
}

void ConnetDlg::slot_UpdateReadCount(int count,int speed,int nReset)
{
	if (nReset == 0)
	{
		mCardCoundList.clear();
		return;
	}
	else if (nReset == 2)
	{
		mCardCountLabel->setText(QString("%1").arg(count));
		mCardReadSpeedLabel->setText(QString("%1").arg(speed));
		return ;
	}

	mCardCountLabel->setText(QString("%1").arg(count));
	
	int nCount = 20;
	if (nCount > mCardCoundList.size())
	{
		mCardCoundList.push_back(speed);
	}
	else
	{
		mCardCoundList.removeFirst();
		mCardCoundList.push_back(speed);
	}		
	int newSpeed = 0;
	for (int i=0; i<mCardCoundList.size(); ++i)
	{
		newSpeed += mCardCoundList.at(i);
	}
	newSpeed = newSpeed/mCardCoundList.size();
	mSpeed = newSpeed;
	
	mRefeshTime++;
	if (mRefeshTime %5 == 0)
	{
		mCardReadSpeedLabel->setText(QString("%1").arg(mSpeed));
		mRefeshTime=0;
	}
}

bool ConnetDlg::CheckIPEdit(const QString& str)
{
	QRegExp regexp( "((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)" );

	QRegExpValidator regexp_validator( regexp, this );
	int nPos = 0;
	if ( str.isEmpty() )
	{
		return false;
	}
	QString tmp = str;
	if ( !str.isEmpty() && regexp_validator.validate( tmp, nPos ) != QValidator::Acceptable )
	{
		return false;
	}
	return true;
}

void ConnetDlg::slot_queryIpBtnClicked()
{
	if (mUdpWorkerThread->StartUdp())
	{
		mIpAddrCb->clear();
	}		
}

void ConnetDlg::slot_GetUdpResult(const QString& ipStr, const QString& nameStr)
{
	mIpAddrCb->addItem(ipStr);
}

void ConnetDlg::CreateView()
{
	mConnetStackedWidget = ui->stackedWidget;
	mConnetBtn = ui->pushButton;
	mIpAddrCb = ui->comboBox_3;
	mIpAddrCb->setEditable(true);
	mComCb = ui->comboBox;
	mBaudRateCb = ui->comboBox_2;
	mCardCountLabel = ui->label_6;
	mCardReadSpeedLabel = ui->label_8;	
	mConnetTypeCb = ui->comboBox_4;
	mQueryIPBtn =  ui->pushButton_4;
	mLinkWidget = ui->widget_2;
	mUdpIpAddrCb = ui->comboBox_6;
	mUsbCb = ui->comboBox_7;
	mUsbBaudRateCb = ui->comboBox_5;
	mTcpPortEdit=ui->lineEdit_2;
	mUdpPortEdit=ui->lineEdit;
	mClearBtn = ui->pushButton_3;
	mRebootBtn = ui->pushButton_2;
	mCutDownBtn = ui->pushButton_5;
	mConnectItemBtn = ui->pushButton_6;
	//ui->widget->hide();
	ui->label_9->hide();
	//ui->label_12->setWordWrap(true);

	mDeviceList = ui->treeWidget;

	mConnetStackedWidget->setCurrentIndex(0);
	mUdpIpAddrCb->setEditable(true);

	if (WIDGETENABLE("ConnetDlg","TCP_TYPE"))
	{
		mConnetTypeCb->addItem(QString("TCP"),Connet_TCP);
	}
	if (WIDGETENABLE("ConnetDlg","COM_TYPE"))	
	{
		mConnetTypeCb->addItem(QString("COM"),Connet_COM);
	}
//	if (WIDGETENABLE("ConnetDlg","USB_TYPE"))
//	{
//		mConnetTypeCb->addItem(QString("USB"),Connet_USB);
//	}
//	if (WIDGETENABLE("ConnetDlg","UDP_TYPE"))
//	{
//		mConnetTypeCb->addItem(QString("UDP"),Connet_UDP);
//	}

	mConnetTypeCb->setCurrentIndex(WIDGETSTRING_GET("ConnetDlg","CONNET_TYPE").toUInt());
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
	
	QString defaultComName = WIDGETSTRING_GET("ConnetDlg","COM_NAME");
	if (!defaultComName.isEmpty())
	{
		mComCb->setCurrentIndex(mComCb->findText(defaultComName));
	}
	else
	{
		mComCb->setCurrentIndex(0);	
	}

	QString defaultUSBName = WIDGETSTRING_GET("ConnetDlg","USB_NAME");
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

	QString defaultBaudRate = WIDGETSTRING_GET("ConnetDlg","COM_BAUDRATE");
	if (!defaultBaudRate.isEmpty())
	{
		mBaudRateCb->setCurrentIndex(mBaudRateCb->findText(defaultBaudRate));
	}
	else
	{
		mBaudRateCb->setCurrentIndex(4);
	}

	QString defaultUsbBaudRate = WIDGETSTRING_GET("ConnetDlg","USB_BAUDRATE");
	if (!defaultUsbBaudRate.isEmpty())
	{
		mUsbBaudRateCb->setCurrentIndex(mUsbBaudRateCb->findText(defaultUsbBaudRate));
	}
	else
	{
		mUsbBaudRateCb->setCurrentIndex(4);
	}

	mIpAddrCb->setEditText(WIDGETSTRING_GET("ConnetDlg","TCP_ADDR"));
	mUdpIpAddrCb->setEditText(WIDGETSTRING_GET("ConnetDlg","UDP_ADDR"));
	mTcpPortEdit->setText(WIDGETSTRING_GET("ConnetDlg","TCP_PORT"));
	mUdpPortEdit->setText(WIDGETSTRING_GET("ConnetDlg","UDP_PORT"));
	mConnetBtn->setEnabled(true);

	mDeviceList->setColumnCount(3);
	sl.clear();
	sl<<GET_TXT("IDCS_NUMBER")
		<<GET_TXT("IDCS_READER_INFO")
		<<GET_TXT("IDCS_LINK_STATE");
	mDeviceList->setHeaderLabels(sl);
	mDeviceList->setColumnWidth(0,45);
	mDeviceList->setColumnWidth(1,95);

	connect( mConnetBtn, SIGNAL( clicked()), this, SLOT( slot_connetBtnClicked( ) ) );
	connect( mClearBtn, SIGNAL( clicked()), this, SLOT( slot_ClearBtnClicked( ) ) );
	connect( mConnetTypeCb, SIGNAL( currentIndexChanged(int)), this, SLOT( slot_ConnetTypeIndexChanged(int ) ) );
	connect( mDeviceList, SIGNAL( itemPressed(QTreeWidgetItem *,int)), this, SLOT( slot_itemRightClicked(QTreeWidgetItem *,int) ) );
	connect( mDeviceList, SIGNAL( itemDoubleClicked(QTreeWidgetItem *,int)), this, SLOT( slot_itemDoubleClicked(QTreeWidgetItem *,int) ) );
	connect( mRebootBtn, SIGNAL( clicked()), this, SLOT( slot_RebootBtnClicked( ) ) );
	connect( mCutDownBtn, SIGNAL( clicked()), this, SLOT( slot_CutDownBtnClicked( ) ) );
	connect( mConnectItemBtn, SIGNAL( clicked()), this, SLOT( slot_connetItemBtnClicked( ) ) );

}

void ConnetDlg::slot_ConnetTypeIndexChanged(int index)
{
	if (index == -1)
	{
		return;
	}

	mConnetStackedWidget->setCurrentIndex(index);
}

void ConnetDlg::UpdateLanguage()
{
	ui->label_11->setText(GET_TXT("IDCS_LINK_TYPE"));
	ui->label_4->setText(GET_TXT("IDCS_COM_NAME"));
	ui->label->setText(GET_TXT("IDCS_BAUDRATE"));
	ui->pushButton_4->setText(GET_TXT("IDCS_QUERY"));
	ui->label_2->setText(GET_TXT("IDCS_IP_ADDR"));
	ui->label_5->setText(GET_TXT("IDCS_TAG_COUNT"));
	ui->label_7->setText(GET_TXT("IDCS_TAG_READ_SPEED"));
	ui->label_14->setText(GET_TXT("IDCS_PORT"));
	ui->label_15->setText(GET_TXT("IDCS_PORT"));
	
	ui->LableCompanyTitle->setStyleSheet(QString("\
		.QLabel{\
		image: url(%1/logo.png);\
		}").arg(CSingleton<AppConfig>::GetInstance()->GetPngPath()));
}

void ConnetDlg::StartUDP()
{
	
	if(WIDGETENABLE("ConnetDlg","UdpWorkerThread"))
	{
		mQueryIPBtn->show();
		mUdpWorkerThread = new UdpWorkerThread();
		connect( mUdpWorkerThread, SIGNAL( resultReady(const QString&,const QString& )), this, SLOT( slot_GetUdpResult(const QString&,const QString& ) ) );
		connect( mQueryIPBtn, SIGNAL( clicked()), this, SLOT( slot_queryIpBtnClicked( ) ) );
		slot_queryIpBtnClicked();
	}
	else
	{
		mUdpWorkerThread = NULL;
		mQueryIPBtn->hide();
	}

}

bool ConnetDlg::isEnableEdit(int nConnetType)
{
	if(nConnetType == STATE_READING )
	{
		return false;
	}
	
	return true;
}

QTreeWidgetItem* ConnetDlg::AddConnectUdp()
{
	int nPort = mUdpPortEdit->text().toInt();
	QString ipAddr = mUdpIpAddrCb->currentText();	

	if (!CheckIPEdit(ipAddr))
	{
		MainShowMsg(GET_TXT("IDCS_IPADDR_INVAID"));
		return NULL;

	}

	if (mUdpPortEdit->text().isEmpty() || mUdpPortEdit->text().toUInt() <=0)
	{
		MainShowMsg(GET_TXT("IDCS_IP_PORT_ERRO"));
		return NULL;
	}

	QString strInfo = QString("%1:%2").arg(ipAddr).arg(nPort);
	ReaderDllBase* pReaderDllBase = CSingleton<ReaderManager>::GetInstance()->FindReader(strInfo);
	if (pReaderDllBase)
	{
		MainShowMsg(GET_TXT("IDCS_LINK_ADDED"),false,false);
		return NULL;
	}

	pReaderDllBase = CSingleton<ReaderManager>::GetInstance()->CreateReader(strInfo);
	pReaderDllBase->SetUdpConnetInfo(ipAddr,nPort);

	return CreateItem(strInfo,pReaderDllBase);
}

QTreeWidgetItem*	ConnetDlg::AddConnectTcp()
{
	int nPort = mTcpPortEdit->text().toInt();
	QString ipAddr = mIpAddrCb->currentText();	

	if (!CheckIPEdit(ipAddr))
	{
		MainShowMsg(GET_TXT("IDCS_IPADDR_INVAID"));
		return NULL;
	}
	if (mTcpPortEdit->text().isEmpty() || mTcpPortEdit->text().toUInt() <=0)
	{
		MainShowMsg(GET_TXT("IDCS_IP_PORT_ERRO"));
		return NULL;
	}

	QString strInfo = QString("%1:%2").arg(ipAddr).arg(nPort);
	ReaderDllBase* pReaderDllBase = CSingleton<ReaderManager>::GetInstance()->FindReader(strInfo);
	if (pReaderDllBase)
	{
		MainShowMsg(GET_TXT("IDCS_LINK_ADDED"),false,false);
		return NULL;
	}

	pReaderDllBase = CSingleton<ReaderManager>::GetInstance()->CreateReader(strInfo);
	pReaderDllBase->SetTcpConnetInfo(ipAddr,nPort);

	return CreateItem(strInfo,pReaderDllBase);
}

QTreeWidgetItem* ConnetDlg::AddConnectCom()
{
	QString strCom = mComCb->currentText();
	int nBaudreate = mBaudRateCb->currentText().toInt();
	QString strInfo = QString("%1:%2").arg(strCom).arg(nBaudreate);
	ReaderDllBase* pReaderDllBase = CSingleton<ReaderManager>::GetInstance()->FindReader(strInfo);
	if (pReaderDllBase)
	{
		MainShowMsg(GET_TXT("IDCS_LINK_ADDED"),false,false);
		return NULL;
	}

	pReaderDllBase = CSingleton<ReaderManager>::GetInstance()->CreateReader(strInfo);

	pReaderDllBase->SetComConnetInfo(
		strCom,
		nBaudreate);

	return CreateItem(strInfo,pReaderDllBase);

}

QTreeWidgetItem* ConnetDlg::AddConnectUsb()
{
	QString strCom = mUsbCb->currentText();
	int nBaudreate = mUsbBaudRateCb->currentText().toInt();
	QString strInfo = QString("%1:%2").arg(strCom).arg(nBaudreate);
	ReaderDllBase* pReaderDllBase = CSingleton<ReaderManager>::GetInstance()->FindReader(strInfo);
	if (pReaderDllBase)
	{
		MainShowMsg(GET_TXT("IDCS_LINK_ADDED"),false,false);
		return NULL;
	}

	pReaderDllBase = CSingleton<ReaderManager>::GetInstance()->CreateReader(strInfo);

	pReaderDllBase->SetUsbConnetInfo(
		strCom,
		nBaudreate);

	return CreateItem(strInfo,pReaderDllBase);
}

bool ConnetDlg::SavaIni()
{	
	if (mConnetTypeCb->currentIndex() == Connet_TCP)
	{

		WIDGETSTRING_SET("ConnetDlg","TCP_ADDR",mIpAddrCb->currentText().toUtf8().data());
		WIDGETSTRING_SET("ConnetDlg","CONNET_TYPE",(QString("%1").arg(Connet_TCP).toUtf8().data()));
		WIDGETSTRING_SET("ConnetDlg","TCP_PORT",mTcpPortEdit->text().toUtf8().data());

	}
	else if(mConnetTypeCb->currentIndex() == Connet_COM)
	{	
		WIDGETSTRING_SET("ConnetDlg","COM_NAME",mComCb->currentText().toUtf8().data());
		WIDGETSTRING_SET("ConnetDlg","COM_BAUDRATE",mBaudRateCb->currentText().toUtf8().data());
		WIDGETSTRING_SET("ConnetDlg","CONNET_TYPE",QString("%1").arg(Connet_COM).toUtf8().data());

	}
//	else if(mConnetTypeCb->currentIndex() == Connet_USB)
//	{

//		WIDGETSTRING_SET("ConnetDlg","USB_NAME",mUsbCb->currentText().toUtf8().data());
//		WIDGETSTRING_SET("ConnetDlg","USB_BAUDRATE",mUsbBaudRateCb->currentText().toUtf8().data());
//		WIDGETSTRING_SET("ConnetDlg","CONNET_TYPE",QString("%1").arg(Connet_USB).toUtf8().data());

//	}
//	else if(mConnetTypeCb->currentIndex() == Connet_UDP)
//	{
//		WIDGETSTRING_SET("ConnetDlg","UDP_ADDR",mUdpIpAddrCb->currentText().toUtf8().data());
//		WIDGETSTRING_SET("ConnetDlg","CONNET_TYPE",(QString("%1").arg(Connet_UDP).toUtf8().data()));
//		WIDGETSTRING_SET("ConnetDlg","UDP_PORT",mUdpPortEdit->text().toUtf8().data());
//	}
	else
	{
		return false;
	}


	return true;
}

QTreeWidgetItem* ConnetDlg::CreateItem(const QString& strInfo,ReaderDllBase* pReaderDllBase)
{
	QTreeWidgetItem* item = new QTreeWidgetItem(mDeviceList);
	int  nIndex = GetReaderItemIndex();
	item->setData(0,Qt::UserRole+2,nIndex);
	item->setText(0,QString("%1").arg(nIndex));
	item->setText(1,strInfo);
	QString strState = pReaderDllBase->GetStateStr();	
	item->setText(2,strState);

	return item;
}

int ConnetDlg::GetReaderItemIndex()
{
	for (int i=1; i<255; ++i)
	{
		if (FindIndexItem(i) == NULL)
		{
			return i;
		}
	}
	return 0;
}

QTreeWidgetItem* ConnetDlg::FindIndexItem(int nIndex)
{
	QTreeWidgetItem* item = NULL;
	for (int i=0; i<mDeviceList->topLevelItemCount(); ++i)
	{
		item = mDeviceList->topLevelItem(i);
		if (item->data(0,Qt::UserRole+2).toInt() == nIndex)
		{	
			return item;
		}
	}

	return NULL;
}



void ConnetDlg::slot_itemRightClicked(QTreeWidgetItem * item,int)
{
	if(!(QApplication::mouseButtons()&Qt::RightButton))
	{
		return;
	}

	QMenu* pMenu = new QMenu(this);
	QAction* connectAct = new QAction( GET_TXT("IDCS_CONNET"), pMenu );
	connect( connectAct, SIGNAL(triggered()), this, SLOT(slot_connectItem()) );
	pMenu->addAction(connectAct);
	QAction* disconnectAct = new QAction( GET_TXT("IDCS_DISCONNET"), pMenu );
	connect( disconnectAct, SIGNAL(triggered()), this, SLOT(slot_disconnectItem()) );
	pMenu->addAction(disconnectAct);
	QAction* deleteAct = new QAction( GET_TXT("IDCS_DELETE"), pMenu );
	connect( deleteAct, SIGNAL(triggered()), this, SLOT(slot_deleteItem()) );
	pMenu->addAction(deleteAct);
	QAction* setcurAct = new QAction( GET_TXT("IDCS_SET_CUR_ITEM"), pMenu );
	connect( setcurAct, SIGNAL(triggered()), this, SLOT(slot_setCurItem()) );
	pMenu->addAction(setcurAct);
	pMenu->exec(QCursor::pos());

	delete connectAct;
	delete disconnectAct;
	delete deleteAct;
	delete setcurAct;


	connectAct = NULL;
	disconnectAct = NULL;
	deleteAct = NULL;
	setcurAct = NULL;
	
	delete pMenu;
	pMenu = NULL;
}

void ConnetDlg::slot_connectItem()
{
	QTreeWidgetItem *item = mDeviceList->currentItem();
	if (!item)
	{
		return;
	}

	ConnectItem(item);
}

void ConnetDlg::slot_disconnectItem()
{
	QTreeWidgetItem *item = mDeviceList->currentItem();
	if (!item)
	{
		return;
	}

	DisConnectItem(item);	
}


bool ConnetDlg::DisConnectItem(QTreeWidgetItem *item)
{
	QString strInfo = item->text(1);
	ReaderDllBase* pReaderDllBase = CSingleton<ReaderManager>::GetInstance()->FindReader(strInfo);
	if (pReaderDllBase)
	{
		if (pReaderDllBase->GetState() == STATE_DISABLE ||
			pReaderDllBase->GetState() == STATE_DISCONNET )
		{
			MainShowMsg(GET_TXT("IDCS_AREADY_NOT_CONNECTED"));	
			return false;
		}

		if (pReaderDllBase->CloseReader())
		{
			MainShowMsg(GET_TXT("IDCS_DISCONNET_SUCCESS"));
			UpdateItemState(item,pReaderDllBase);

			return true;
		}
		else
		{
			MainShowMsg(GET_TXT("IDCS_DISCONNET_FAILED"));
		}	

	}

	return false;
}


void ConnetDlg::slot_deleteItem()
{
	QTreeWidgetItem *item = mDeviceList->currentItem();
	if (!item)
	{
		return;
	}

	QString strInfo = item->text(1);	
	if (CSingleton<ReaderManager>::GetInstance()->DeleteReader(strInfo))
	{
		MainShowMsg(GET_TXT("IDCS_DELETE_SUCCESS"));
		delete item;
	}
	else
	{
		MainShowMsg(GET_TXT("IDCS_DELETE_FAILED"));
		delete item;
	}		
}

void ConnetDlg::UpdateItemState(QTreeWidgetItem *item, ReaderDllBase* pReaderDllBase)
{
	QString strState = pReaderDllBase->GetStateStr();	
	item->setText(2,strState);
}

void ConnetDlg::slot_setCurItem()
{
	QTreeWidgetItem *item = mDeviceList->currentItem();
	if (!item)
	{
		return;
	}
	SetCurItem(item);
}

void ConnetDlg::SetCurItem(QTreeWidgetItem *item)
{

	QString strInfo = item->text(1);
	if (CSingleton<ReaderManager>::GetInstance()->SetCurReader(strInfo))
	{
		int nIndex;
		int nItemCount = mDeviceList->topLevelItemCount();
		for (int i=0; i<nItemCount; ++i)
		{
			nIndex = mDeviceList->topLevelItem(i)->data(0,Qt::UserRole+2).toInt();	
			if (item != mDeviceList->topLevelItem(i))
			{
				
				mDeviceList->topLevelItem(i)->setText(0,QString("%1").arg(nIndex));
				mDeviceList->topLevelItem(i)->setData(0,Qt::UserRole+1,0);
			}
			else
			{				
                mDeviceList->topLevelItem(i)->setText(0,QString::fromLocal8Bit("%1").arg(nIndex));
				mDeviceList->topLevelItem(i)->setData(0,Qt::UserRole+1,1);
			}
		}
	}
}

void ConnetDlg::ClearAllItem()
{
	if (mDeviceList->topLevelItemCount()<=0)
	{
		return;
	}

	if (HtMessageBox::Question(GET_TXT("IDCS_SURE_CLEAR_AND_DISCONNECT"),this)
		!= HtMessageBox::RET_ENTER )
	{
		return ;
	}

	CSingleton<ReaderManager>::GetInstance()->ClearAllReader();
	mDeviceList->clear();
}

bool ConnetDlg::ConnectItem(QTreeWidgetItem *item)
{
	if (!item)
	{
		return false; 
	}
	QString strInfo = item->text(1);
	ReaderDllBase* pReaderDllBase = CSingleton<ReaderManager>::GetInstance()->FindReader(strInfo);
	if (pReaderDllBase)
	{
		if (pReaderDllBase->GetState() == STATE_CONNET)
		{
			MainShowMsg(GET_TXT("IDCS_AREADY_CONNECTED"));
			return false;
		}

		if (pReaderDllBase->ConnetReader())
		{
			MainShowMsg(GET_TXT("IDCS_CONNET_SUCCESS"));	
			UpdateItemState(item,pReaderDllBase);
			return true;
		}
		else
		{
			MainShowMsg(GET_TXT("IDCS_CONNET_FAILED"),true,false);
			return false;
		}			
	}

	return false;
}

void ConnetDlg::slot_ClearBtnClicked()
{
	ClearAllItem();
}

void ConnetDlg::slot_itemDoubleClicked(QTreeWidgetItem * item,int)
{
	if (!item)
	{
		return;
	}

	SetCurItem(item);
}

void ConnetDlg::slot_cutCurConnect()
{
	QTreeWidgetItem* tempitem = NULL;
	QTreeWidgetItem* item = NULL;
	for (int i=0;i<mDeviceList->topLevelItemCount(); ++i )
	{
		tempitem = mDeviceList->topLevelItem(i);
		if (tempitem->data(0,Qt::UserRole+1).toInt() == 1)
		{
			item = tempitem;
			break;
		}
	}
	if (!item)
	{
		return;
	}


	QString strInfo = item->text(1);
	ReaderDllBase* pReaderDllBase = CSingleton<ReaderManager>::GetInstance()->FindReader(strInfo);
	if (pReaderDllBase)
	{
		if (pReaderDllBase->CloseReader())
		{
			MainShowMsg(GET_TXT("IDCS_DISCONNET_SUCCESS"));
			UpdateItemState(item,pReaderDllBase);
		}
		else
		{
			MainShowMsg(GET_TXT("IDCS_DISCONNET_FAILED"));
		}		
	}
}

void ConnetDlg::slot_RebootBtnClicked()
{
	QTreeWidgetItem* tempitem = NULL;
	QTreeWidgetItem* item = mDeviceList->currentItem();
	if (!item)
	{
		for (int i=0;i<mDeviceList->topLevelItemCount(); ++i )
		{
			tempitem = mDeviceList->topLevelItem(i);
			if (tempitem->data(0,Qt::UserRole+1).toInt() == 1)
			{
				item = tempitem;
				break;
			}
		}
		if (!item)
		{
			return;
		}
	}

	RebootItem(item);
}	

void ConnetDlg::slot_CutDownBtnClicked()
{
	QTreeWidgetItem* tempitem = NULL;
	QTreeWidgetItem* item = mDeviceList->currentItem();
	if (!item)
	{
		for (int i=0;i<mDeviceList->topLevelItemCount(); ++i )
		{
			tempitem = mDeviceList->topLevelItem(i);
			if (tempitem->data(0,Qt::UserRole+1).toInt() == 1)
			{
				item = tempitem;
				break;
			}
		}
		if (!item)
		{
			return;
		}
	}

	DisConnectItem(item);
}

bool ConnetDlg::RebootItem(QTreeWidgetItem *item)
{

	QString strInfo = item->text(1);
	ReaderDllBase* pReaderDllBase = CSingleton<ReaderManager>::GetInstance()->FindReader(strInfo);
	if (!pReaderDllBase)
	{
		MainShowMsg(GET_TXT("IDCS_READ_NO_LINK"));
		return false;
	}
	if (!pReaderDllBase->CheckState(STATE_CONNET))
	{
		MainShowMsg(GET_TXT("IDCS_READ_NO_LINK"));
		return false;
	}

	if (HtMessageBox::Question(GET_TXT("IDCS_READLY_REBOOT_DEVICE"),this)
		!= HtMessageBox::RET_ENTER )
	{
		return false;
	}

	bool retB = SAAT_Reboot (
		pReaderDllBase->m_hCom,
		0x00);

	if (retB)
	{		
		DisConnectItem(item);	
		MainShowMsg(GET_TXT("IDCS_REBOOT_SUCCESS"));	
	}
	else
	{
		MainShowMsg(GET_TXT("IDCS_REBOOT_FAILED"),true);
	}

	return retB;
}

void ConnetDlg::slot_connetItemBtnClicked()
{
	QTreeWidgetItem* tempitem = NULL;
	QTreeWidgetItem* item = mDeviceList->currentItem();
	if (!item)
	{
		for (int i=0;i<mDeviceList->topLevelItemCount(); ++i )
		{
			tempitem = mDeviceList->topLevelItem(i);
			if (tempitem->data(0,Qt::UserRole+1).toInt() == 1)
			{
				item = tempitem;
				break;
			}
		}
		if (!item)
		{
			return;
		}
	}

	ConnectItem(item);
}

