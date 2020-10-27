#include "wirelessrecv.h"
#include "ui_wirelessrecv.h"
#include <QApplication>
#include "WIRELESSRFIDAPIEXPORT.h"
#include "mainapp.h"
#include "appconfig.h"
#include "LanguageSrc.h"
#include "widgetconfig.h"
#include "WirelessRecvCtrl.h"
#include "wirelessadvanceddlg.h"
#include "wirelessdeviceinfodlg.h"
#include "wirelesstcpserverconfigdlg.h"
#include "addclientdlg.h"
#include <QDateTime>
#include <assert.h>
#include <QFileDialog>
#include <QTextStream>
#include "MessageBox.h"

bool WirelessRecvDlg::PacketCallbackFunction(void* pHandle,  WirelessReaderInfo* pReaderInfo)
{
	CSingleton<WirelessRecvCtrl>::GetInstance()->recvReaderInfo(pReaderInfo);
	

	return true;
}

WirelessRecvDlg::WirelessRecvDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::wirelessrecv)
{
    ui->setupUi(this);
	mIsStart = false;
	mIsServerActive = false;
	CreateView();
	updateLanguage();
	CSingleton<WirelessRecvCtrl>::GetInstance()->SetpDlg(this);
	bool bResult = WIRELESS_ApiInit(&WIRELESSRECV_HANDLE);
	slot_EnableAsysTimeCkbChange(mEnableAsysTimeCkb->checkState());

}

WirelessRecvDlg::~WirelessRecvDlg()
{
	slot_stop();
	QuitServer();

	if (mRefreshTimer)
	{
		delete mRefreshTimer;
		mRefreshTimer = NULL;
	}
	if (mCheckOnline)
	{
		delete mCheckOnline;
		mCheckOnline = NULL;
	}

	if (mRightMenu)
	{
		delete mRightMenu;
		mRightMenu = NULL;
	}

    delete ui;
}

void WirelessRecvDlg::slot_Oper()
{
	if (!mIsStart)
	{
		slot_start();
	}
	else
	{
		slot_stop();	
	}
}

void WirelessRecvDlg::slot_disconnet()
{
	
	//bool bResult = WIRELESS_CloseReader(m_hCom, pWirelessReaderInfo);
	//if(bResult)
	//{
	//	pWirelessReaderInfo = NULL;
	//	MainShowMsg(QString::fromUtf8("slot_disconnet success"));
	//}
	//else
	//{
	//	MainShowMsg(QString::fromUtf8("slot_disconnet failed"));
	//}
}

void WirelessRecvDlg::CreateView()
{
	mStartBtn = ui->pushButton;
	mAdvancedBtn = ui->pushButton_2;
	mClearBtn = ui->pushButton_3;
	mTagTree = ui->treeWidget;
	mServerListenBtn = ui->pushButton_6;
	mAddReaderBtn = ui->pushButton_5;
	mEnableAsysTimeCkb = ui->checkBox_2;
	mSaveLogCkb = ui->checkBox;
	
	mServerListenBtn->setEnabled(false);
	mAddReaderBtn->setEnabled(false);
	mAdvancedBtn->setEnabled(true);
	mEnableAsysTimeCkb->hide();
	mAddReaderBtn->hide();
		
	mRightMenu = new TreeRightMenu(this,this);
	mRightMenu->hide();

	mWirelessAdvancedDlg = new WirelessAdvancedDlg(this);
	mWirelessAdvancedDlg->hide();
	mAddClientDlg = new AddClientDlg(this);
	mAddClientDlg->hide();
	mWirelessTcpServerConfigDlg = new WirelessTcpServerConfigDlg(this);
	mWirelessTcpServerConfigDlg->hide();

	mWirelessDeviceInfoDlg = new WirelessDeviceInfoDlg(this);
	mWirelessDeviceInfoDlg->hide();

	QStringList sl;
	sl << GET_TXT("IDCS_NUMBER")
		<< GET_TXT("IDCS_TAG_ID") 		
		<< GET_TXT("IDCS_READTIME")
		<< GET_TXT("IDCS_ANTENNA_ONE_COUNT")
		<< GET_TXT("IDCS_ANTENNA_TWO_COUNT")
		<< GET_TXT("IDCS_ANTENNA_THREE_COUNT")
		<< GET_TXT("IDCS_ANTENNA_FOUR_COUNT")
		<< GET_TXT("IDCS_TAG_STATUS")
		<< GET_TXT("IDCS_RSSI")
		<< GET_TXT("IDCS_OTHER_INFO");

	mTagTree->setHeaderLabels( sl );
	mTagTree->setColumnCount( 10);
	mTagTree->setColumnWidth( 0, 60 );
	mTagTree->setColumnWidth( 1, 80 );
	mTagTree->setColumnWidth( 2, 130 );
	mTagTree->setColumnWidth( 3, 50 );
	mTagTree->setColumnWidth( 4, 50 );
	mTagTree->setColumnWidth( 5, 50 );
	mTagTree->setColumnWidth( 6, 50 );
	mTagTree->setColumnWidth( 7, 100 );
	mTagTree->setColumnWidth( 8, 70 );
	mTagTree->setColumnWidth( 9, 100 );
	mTagTree->setAlternatingRowColors( true );

	mEnableAsysTimeCkb->setChecked(IsEnableAnalysisTime());

	connect( mStartBtn, SIGNAL( clicked()), this, SLOT( slot_Oper( ) ) );
	connect( mClearBtn, SIGNAL( clicked()), this, SLOT( slot_Clear( ) ) );
	connect( mAdvancedBtn, SIGNAL( clicked()), this, SLOT( slot_advanceBtnClicked( ) ) );
	connect( mServerListenBtn, SIGNAL( clicked()), this, SLOT( slot_ServerListenBtnClicked( ) ) );
	connect( mAddReaderBtn, SIGNAL( clicked()), this, SLOT( slot_AddReaderBtnClicked( ) ) );
	connect( mEnableAsysTimeCkb, SIGNAL( stateChanged(int) ), this, SLOT( slot_EnableAsysTimeCkbChange(int ) ) );

	mRefreshTimer =  new QTimer(this);
	connect(mRefreshTimer, SIGNAL(timeout()), this, SLOT(slot_refresh_time()));
	connect( mTagTree,  SIGNAL( itemPressed(QTreeWidgetItem *,int)), this, SLOT( slot_itemRightClicked(QTreeWidgetItem *,int) ) );
	
	mCheckOnline =  new QTimer(this);
	connect(mCheckOnline, SIGNAL(timeout()), this, SLOT(slot_checkOnline_time()));

}



bool WirelessRecvDlg::StartServer()
{

	QString ipAddr = mWirelessTcpServerConfigDlg->GetServerIp();
	int nPort = mWirelessTcpServerConfigDlg->GetServerPort().toInt();
	if (nPort == 0 || ipAddr.isEmpty())
	{
		MainShowMsg(GET_TXT("IDCS_IP_PORT_ERRO"));	
		return false;
	}
	bool bResult = false;

	bResult = WIRELESS_StartServer(
		WIRELESSRECV_HANDLE,
		ipAddr.toUtf8().data(),
		nPort,
		WirelessRecvDlg::PacketCallbackFunction);
	if(bResult)
	{
		MainShowMsg(GET_TXT("IDCS_SERVER_START_SUCCESS"));
	}
	else
	{
		MainShowMsg(GET_TXT("IDCS_SERVER_START_FAILED"));
	}

	return bResult;
}

bool WirelessRecvDlg::StopServer()
{
	bool bResult = WIRELESS_StopServer(WIRELESSRECV_HANDLE);
	if(bResult)
	{
		MainShowMsg(GET_TXT("IDCS_STOP_SCCUSS"));
	}
	else
	{
		MainShowMsg(GET_TXT("IDCS_STOP_FAILED"));
	}
	return bResult;
}

bool WirelessRecvDlg::QuitServer()
{
	bool bResult = WIRELESS_Quit(&(WIRELESSRECV_HANDLE));

	if(bResult)
	{
		MainShowMsg(GET_TXT("IDCS_SERVER_QUIT_SUCCESS"));
		WIRELESSRECV_HANDLE = INVALID_HANDLE_VALUE;
		WIRELESSRECV_HANDLE = NULL;
	}
	else
	{
		MainShowMsg(GET_TXT("IDCS_SERVER_QUIT_FAILED"));
	}
	return bResult;
}

void WirelessRecvDlg::slot_Clear()
{
	QTreeWidgetItem* ipItem = NULL;
	for (int i=0; i<mTagTree->topLevelItemCount(); ++i)
	{
		ipItem = mTagTree->topLevelItem(i);
		WirelessReaderInfo* pReaderInfo = (WirelessReaderInfo*)(ipItem->data(1, Qt::UserRole+1).toULongLong());
		CSingleton<WirelessRecvCtrl>::GetInstance()->ClearAllTag(pReaderInfo);
		ClearAllTagItem(ipItem);
	}
}

void WirelessRecvDlg::updateLanguage()
{
	ui->label_8->setText(GET_TXT("IDCS_READ_CARD"));	
	mStartBtn->setText(GET_TXT("IDCS_START"));
	mClearBtn->setText(GET_TXT("IDCS_CLEAR"));
	mAdvancedBtn->setText(GET_TXT("IDCS_SOFT_CONFIG"));
	//mServerConfigBtn->setText(GET_TXT("IDCS_SERVER_CONFIG"));
	mServerListenBtn->setText(GET_TXT("IDCS_START_LISTEN"));
	mAddReaderBtn->setText(GET_TXT("IDCS_READER_ADD"));
	ui->checkBox->setText(GET_TXT("IDCS_RECORD_INFO"));
}

void WirelessRecvDlg::slot_RecvreaderInfo(void* pReaderInfo)
{
	QTreeWidgetItem* item = GetReaderItem((WirelessReaderInfo*)pReaderInfo);
	StartReadItem(item);	

	SaveReaderState((WirelessReaderInfo*)pReaderInfo,true);
	
	QueryReaderName((WirelessReaderInfo*)pReaderInfo);
}

QTreeWidgetItem* WirelessRecvDlg::GetReaderItem(WirelessReaderInfo* pReaderInfo)
{	
	QTreeWidgetItem* item = FindReaderItem(pReaderInfo);
	if (!item)
	{
		item = 	CtreateReaderItem(pReaderInfo);
	}
	return item;
}

QTreeWidgetItem* WirelessRecvDlg::FindReaderItem(WirelessReaderInfo* pReaderInfo)
{
	QTreeWidgetItem* item = NULL;
	QTreeWidgetItem* retItem = NULL;
	for (int i=0; i<mTagTree->topLevelItemCount(); ++i)
	{
		item = mTagTree->topLevelItem(i);
		WirelessReaderInfo* itemData = 
			(WirelessReaderInfo*)(item->data(1, Qt::UserRole+1).toULongLong());
		
		if (itemData == pReaderInfo)
		{
			retItem = item;
			break;
		}
	}
	return retItem;
}

QTreeWidgetItem* WirelessRecvDlg::CtreateReaderItem(WirelessReaderInfo* pReaderInfo)
{
	QTreeWidgetItem* retItem = NULL;
	retItem = new QTreeWidgetItem(mTagTree);
	QString ipAddrStr;
	QString nPortStr;
	if (pReaderInfo->ReaderType == READER_TCP_SERVER||
		pReaderInfo->ReaderType == READER_TCP_CLIENT ||
		pReaderInfo->ReaderType == READER_UDP)
	{
		ipAddrStr = QString::fromUtf8((char*)pReaderInfo->bIpAddr);
		nPortStr = QString("%1").arg(pReaderInfo->nPort);
	}
	else if(pReaderInfo->ReaderType == READER_COM||
		pReaderInfo->ReaderType == READER_USB )
	{
		ipAddrStr = QString::fromUtf8((char*)pReaderInfo->bComNum);
		nPortStr = QString("%1").arg(pReaderInfo->nBaud);
	}
	
	retItem->setExpanded(true);
	retItem->setData(0,Qt::UserRole+1,WIRELESS_ITEM_TYPE_IPADDR);
	retItem->setData(1, Qt::UserRole+1,(unsigned long long)pReaderInfo);

	retItem->setText(0,QString::fromUtf8("%1").arg(GetReaderItemIndex()));


	retItem->setText(1,QString("%1:%2").arg(ipAddrStr).arg(nPortStr));	
	//retItem->setText(3,GET_TXT("IDCS_LINKED"));	
	retItem->setData(3, Qt::UserRole+1,WIRELESS_ITEM_READ_TYPE_NORMAL);
	refalshOnlineTime(retItem);

	return retItem;
}

void WirelessRecvDlg::RecvreaderInfo(WirelessReaderInfo* pReaderInfo)
{
	QMetaObject::invokeMethod(this, "slot_RecvreaderInfo", Qt::QueuedConnection, Q_ARG(void*, pReaderInfo) );
}

void WirelessRecvDlg::RecvIOState(WirelessReaderInfo* pReaderInfo,QString& strState)
{
	MainShowMsg(strState);

	QMetaObject::invokeMethod(this, "slot_RecvIOState", Qt::QueuedConnection, Q_ARG(QString, strState) );
}

void WirelessRecvDlg::slot_refresh_time()
{
	QTreeWidgetItem* ipItem = NULL;
	QTreeWidgetItem* tagItem = NULL;
	WirelessReaderInfo* pReaderInfo = NULL;
	std::map<QString,CWirelessEpcCardInfo*> tmpList;
	std::map<QString,CWirelessEpcCardInfo*>::iterator ListIter ;
	CWirelessEpcCardInfo* pCWirelessEpcCardInfo = NULL;
	for (int i=0; i<mTagTree->topLevelItemCount(); ++i)
	{
		ipItem = mTagTree->topLevelItem(i);
		pReaderInfo = (WirelessReaderInfo*)(ipItem->data(1, Qt::UserRole+1).toULongLong());
		
		
		CSingleton<WirelessRecvCtrl>::GetInstance()->GetCardInfoList(pReaderInfo,tmpList);
		
		ListIter = tmpList.begin();
		for(; ListIter!=tmpList.end(); ++ListIter)
		{			
			pCWirelessEpcCardInfo = ListIter->second;
			tagItem = GetTagItem(ipItem,ListIter->first);
			tagItem->setText(2,pCWirelessEpcCardInfo->m_szCurReadTime);
			tagItem->setText(3,QString("%1").arg(pCWirelessEpcCardInfo->m_nAntenna1Count));
			tagItem->setText(4,QString("%1").arg(pCWirelessEpcCardInfo->m_nAntenna2Count));
			tagItem->setText(5,QString("%1").arg(pCWirelessEpcCardInfo->m_nAntenna3Count));
			tagItem->setText(6,QString("%1").arg(pCWirelessEpcCardInfo->m_nAntenna4Count));
			tagItem->setText(7,pCWirelessEpcCardInfo->m_szTagState);	
			tagItem->setText(8,pCWirelessEpcCardInfo->m_szRssi);	
			tagItem->setText(9,pCWirelessEpcCardInfo->m_otherInfo);	
		}
	
		
		ListIter = tmpList.begin();
		for(; ListIter!=tmpList.end(); ++ListIter)
		{
			delete ListIter->second;
			ListIter->second = NULL;
		}
		tmpList.clear();
	}


}	

QTreeWidgetItem* WirelessRecvDlg::GetTagItem(QTreeWidgetItem* ipItem,const QString& tagID)
{
	QTreeWidgetItem* tagItem = NULL;
	tagItem = FindTagItem(ipItem,tagID);
	if (!tagItem)
	{
		tagItem = CtreateTagItem(ipItem,tagID);
	}

	return tagItem;
}

QTreeWidgetItem* WirelessRecvDlg::FindTagItem(QTreeWidgetItem* ipItem,const QString& tagID)
{
	QTreeWidgetItem* tagItem = NULL;
	QTreeWidgetItem* tmpItem = NULL;
	for (int j=0; j<ipItem->childCount(); ++j)
	{
		tmpItem  = ipItem->child(j);
		QString tmpStr = tmpItem->data(1,Qt::UserRole+1).toString();
		if (tmpItem->data(1,Qt::UserRole+1).toString().compare(tagID) == 0)
		{
			tagItem = tmpItem; 
			break;
		}
	}
	return tagItem;
}

QTreeWidgetItem* WirelessRecvDlg::CtreateTagItem(QTreeWidgetItem* ipItem,const QString& tagID)
{
	QTreeWidgetItem* tagItem = NULL;
	tagItem = new QTreeWidgetItem();
	tagItem->setText(0,QString::fromUtf8("%1").arg(ipItem->childCount()+1));
	tagItem->setText(1,tagID);
	tagItem->setData(0,Qt::UserRole+1,WIRELESS_ITEM_TYPE_TAG);
	tagItem->setData(1,Qt::UserRole+1,tagID);
	ipItem->addChild(tagItem);
	return tagItem;
}

void WirelessRecvDlg::slot_itemRightClicked(QTreeWidgetItem *item, int column)
{
	if(!(QApplication::mouseButtons()&Qt::RightButton))
	{
		return;
	}
	int readingType = item->data(3,Qt::UserRole+1).toInt();	

	int itemType = item->data(0,Qt::UserRole+1).toInt();
	if (itemType == WIRELESS_ITEM_TYPE_IPADDR)
	{
		mRightMenu->exec(QCursor::pos());
	}
	
}

void WirelessRecvDlg::StartReadItem(QTreeWidgetItem* item)
{
	int readingType = item->data(3,Qt::UserRole+1).toInt();
	if (readingType == WIRELESS_ITEM_READ_TYPE_READING)
	{
		MainShowMsg(GET_TXT("IDCS_READING_CARD"));	
		return;
	}

	if (readingType == WIRELESS_ITEM_READ_TYPE_NORMAL)
	{
		ClearAllTagItem(item);
		WirelessReaderInfo* pReaderInfo = (WirelessReaderInfo*)(item->data(1, Qt::UserRole+1).toULongLong());
		int nReadType = 0;		
		CSingleton<WirelessRecvCtrl>::GetInstance()->StartRead((WirelessReaderInfo*)pReaderInfo,nReadType);
		item->setData(3,Qt::UserRole+1,WIRELESS_ITEM_READ_TYPE_READING);

	}	
	
}

void WirelessRecvDlg::StopReadItem(QTreeWidgetItem* item)
{
	int readingType = item->data(3,Qt::UserRole+1).toInt();
	if (readingType == WIRELESS_ITEM_READ_TYPE_NORMAL)
	{
		MainShowMsg(GET_TXT("IDCS_READER_NOREAD"));	
		return;
	}

	if (readingType == WIRELESS_ITEM_READ_TYPE_READING)
	{
		WirelessReaderInfo* pReaderInfo = (WirelessReaderInfo*)(item->data(1, Qt::UserRole+1).toULongLong());
		CSingleton<WirelessRecvCtrl>::GetInstance()->StopRead((WirelessReaderInfo*)pReaderInfo);
		item->setData(3,Qt::UserRole+1,WIRELESS_ITEM_READ_TYPE_NORMAL);
	
	}	
}

void WirelessRecvDlg::ClearAllTagItem(QTreeWidgetItem* ipItem)
{
	QTreeWidgetItem *item = NULL;
	while(item = ipItem->child(0))
	{
		delete item;
		item = NULL;
	}
}

void WirelessRecvDlg::ClearAllReadItem()
{
	mTagTree->clear();
}

void WirelessRecvDlg::slot_advanceBtnClicked()
{
	mWirelessAdvancedDlg->exec();
	
	UpdateCheckOnlineTimer();
}

void WirelessRecvDlg::slot_checkOnline_time()
{
	QList<QTreeWidgetItem*> disConnetList;
	QTreeWidgetItem* ipItem = NULL;
	WirelessReaderInfo* pReaderInfo = NULL;	
	for (int i=0; i<mTagTree->topLevelItemCount(); ++i)
	{
		ipItem = mTagTree->topLevelItem(i);
		pReaderInfo = (WirelessReaderInfo*)(ipItem->data(1, Qt::UserRole+1).toULongLong());
		unsigned long nTime = QDateTime::currentDateTime().toTime_t() ;
		unsigned long nOldTime = ipItem->data(2,Qt::UserRole+1).toLongLong();
		int nCheckTime = mWirelessAdvancedDlg->GetCheckOnlineTime().toLongLong();
	
		if ((nTime - nOldTime) > nCheckTime)
		{
			disConnetList.push_back(ipItem);
		}
		
		if(WIRELESS_SAAT_GetLastTime(WIRELESSRECV_HANDLE,pReaderInfo,nTime))
		{
			ipItem->setText(2,QDateTime::fromTime_t(nTime).toString(QString("yyyy-MM-dd hh:mm:ss")));
			ipItem->setData(2,Qt::UserRole+1,QString("%1").arg(nTime));			
		}	
		else
		{
			disConnetList.push_back(ipItem);
		}

	}
	
	while( disConnetList.begin() != disConnetList.end())
	{
		ipItem = *(disConnetList.begin());
		disConnetList.erase(disConnetList.begin());
		DeleteReadItem(ipItem);
	}
}

void WirelessRecvDlg::DeleteReadItem(QTreeWidgetItem* item)
{
	WirelessReaderInfo* pReaderInfo = (WirelessReaderInfo*)(item->data(1, Qt::UserRole+1).toULongLong());
	
	SaveReaderState(pReaderInfo,false);
	CSingleton<WirelessRecvCtrl>::GetInstance()->DeleteRead((WirelessReaderInfo*)pReaderInfo);
	if (WIRELESS_CloseReader(WIRELESSRECV_HANDLE,(WirelessReaderInfo*)pReaderInfo))
	{
		delete item;
		item = NULL;
	}
	else
	{
		assert(false);
	}
}

void WirelessRecvDlg::refalshOnlineTime(QTreeWidgetItem* item)
{
	WirelessReaderInfo* pReaderInfo = (WirelessReaderInfo*)(item->data(1, Qt::UserRole+1).toULongLong());
	unsigned long nTime = 0;
	if(WIRELESS_SAAT_GetLastTime(WIRELESSRECV_HANDLE,
		pReaderInfo,nTime))
	{
		item->setText(2,QDateTime::fromTime_t(nTime).toString(QString("yyyy-MM-dd hh:mm:ss")));
		item->setData(2,Qt::UserRole+1,QString("%1").arg(nTime));
	}
}

void WirelessRecvDlg::slot_stop()
{
	mStartBtn->setText(GET_TXT("IDCS_START"));
	slot_ServerListenBtnStopClicked(); //停止界面需先停止监听的服务器
	mIsStart = !mIsStart; 
	mRefreshTimer->stop();
	mCheckOnline->stop();
	//清空所有读写器
	CSingleton<WirelessRecvCtrl>::GetInstance()->ClearAllRead();
	WIRELESS_ClearReader(WIRELESSRECV_HANDLE);	
	ClearAllReadItem();	

	mServerListenBtn->setEnabled(false);
	mAddReaderBtn->setEnabled(false);
	mAdvancedBtn->setEnabled(true);
}

void WirelessRecvDlg::slot_start()
{
	mIsStart = !mIsStart; 
	mStartBtn->setText(GET_TXT("IDCS_STOP"));

	mRefreshTimer->start(100);	
	UpdateCheckOnlineTimer();

	mServerListenBtn->setEnabled(true);
	mAddReaderBtn->setEnabled(true);
	mAdvancedBtn->setEnabled(false);
}

void WirelessRecvDlg::slot_AddReaderBtnClicked()
{
	mAddClientDlg->exec();	
}

void WirelessRecvDlg::slot_ServerListenBtnClicked()
{
	if (!mIsServerActive)
	{
		slot_ServerListenBtnStartClicked();
	}
	else
	{
		slot_ServerListenBtnStopClicked();	
	}

}

//开始监听
void WirelessRecvDlg::slot_ServerListenBtnStartClicked()
{
	
	if (mWirelessTcpServerConfigDlg->exec() ==  QDialog::Accepted)
	{
		if ( StartServer())
		{
			mIsServerActive = !mIsServerActive; 
			mServerListenBtn->setText(GET_TXT("IDCS_STOP_LISTEN"));
		}
	}

}

//停止所有的读写器
void WirelessRecvDlg::slot_ServerListenBtnStopClicked()
{
	bool bRet = true;
	if (mIsServerActive)
	{
		CSingleton<WirelessRecvCtrl>::GetInstance()->ClearAllRead();
		bRet = StopServer();		
		ClearAllReadItem();	
		mIsServerActive = false; 
		mServerListenBtn->setText(GET_TXT("IDCS_START_LISTEN"));
		//mServerConfigBtn->setEnabled(!mIsServerActive);
	}
}

void WirelessRecvDlg::slot_itemRemoveClicked()
{
	QTreeWidgetItem* item = mTagTree->currentItem();
	if (item)
	{
		DeleteReadItem(item);		
	}
}

void WirelessRecvDlg::slot_ServerConfigBtnClicked()
{
	mWirelessTcpServerConfigDlg->exec();
}

void WirelessRecvDlg::slot_itemRebootClicked()
{
	QTreeWidgetItem* item = mTagTree->currentItem();
	if (!item)
	{
		return;
	}

	if (HtMessageBox::Question(GET_TXT("IDCS_READLY_REBOOT_DEVICE"),this)
		!= HtMessageBox::RET_ENTER )
	{
		return;
	}

	WirelessReaderInfo* pReaderInfo =
		(WirelessReaderInfo*)(item->data(1, Qt::UserRole+1).toULongLong());

	bool bRet = false;
	bRet = WIRELESS_SAAT_Reboot (
		WIRELESSRECV_HANDLE,
		pReaderInfo,
		0x00);
	if (!bRet)
	{
		MainShowMsg(GET_TXT("IDCS_REBOOT_FAILED"));
	}
	else
	{
		DeleteReadItem(item);
		MainShowMsg(GET_TXT("IDCS_REBOOT_SUCCESS"));
			
	}
	
}

void WirelessRecvDlg::UpdateCheckOnlineTimer()
{
	mCheckOnline->stop();
	int nCheckTime = mWirelessAdvancedDlg->
		GetCheckOnlineRefashTime().toInt();
	if (nCheckTime > 0 )
	{
		mCheckOnline->start(nCheckTime*1000);
	}
}

void WirelessRecvDlg::slot_itemSaveClicked()
{
	QString fileName = QFileDialog::getSaveFileName(this,
		GET_TXT("IDCS_SELECT_FILE"), "./", tr("All Files (*.*)"));

	if(!fileName.isEmpty())
	{
		if (SaveDataToFile(fileName))
		{
			MainShowMsg(GET_TXT("IDCS_EXPORT_SUCCESS"));
		}
		else
		{
			MainShowMsg(GET_TXT("IDCS_EXPORT_FAILED"));
		}	
	}
}

bool WirelessRecvDlg::SaveDataToFile(const QString& fileStr)
{
	QFile file(fileStr);
	if (!file.open(QIODevice::WriteOnly|QIODevice::Append | QIODevice::Text))
		return false;

	QTextStream out(&file);	
	QString OutPutStr;	

	QTreeWidgetItem *pItem = NULL;
	QTreeWidgetItem *pChildItem = NULL;
	for (int i=0; i<mTagTree->topLevelItemCount(); ++i)
	{	
		OutPutStr.clear();
		pItem = mTagTree->topLevelItem(i);
		OutPutStr += GET_TXT("IDCS_NUMBER");
		OutPutStr += ":";
		OutPutStr += QString("%1").arg(i+1);
		OutPutStr += "\t";
		OutPutStr += GET_TXT("IDCS_DEVICE_NAME");
		OutPutStr += ":";
		OutPutStr += pItem->text(1);
		OutPutStr += "\t";
		OutPutStr += "\n\n";
		for (int j=0; j<pItem->childCount(); ++j)
		{
			pChildItem = pItem->child(j);
			
			OutPutStr += GET_TXT("IDCS_NUMBER");
			OutPutStr += ":";
			OutPutStr += QString("%1").arg(j+1);
			OutPutStr += "\t";
			OutPutStr += GET_TXT("IDCS_TAG_ID");
			OutPutStr += ":";
			OutPutStr += pChildItem->text(1);
			OutPutStr += "\t";	
			OutPutStr += GET_TXT("IDCS_READTIME");
			OutPutStr += ":";
			OutPutStr += pChildItem->text(2);
			OutPutStr += "\t";
			OutPutStr += GET_TXT("IDCS_ANTENNA_ONE_COUNT");
			OutPutStr += ":";
			OutPutStr += pChildItem->text(3);
			OutPutStr += "\t";
			OutPutStr += GET_TXT("IDCS_ANTENNA_TWO_COUNT");
			OutPutStr += ":";
			OutPutStr += pChildItem->text(4);
			OutPutStr += "\t";
			OutPutStr += GET_TXT("IDCS_ANTENNA_THREE_COUNT");
			OutPutStr += ":";
			OutPutStr += pChildItem->text(5);
			OutPutStr += "\t";
			OutPutStr += GET_TXT("IDCS_ANTENNA_FOUR_COUNT");
			OutPutStr += ":";
			OutPutStr += pChildItem->text(6);
			OutPutStr += "\t";
			OutPutStr += GET_TXT("IDCS_TAG_STATUS");
			OutPutStr += ":";
			OutPutStr += pChildItem->text(7);
			OutPutStr += "\t";
			OutPutStr += GET_TXT("IDCS_RSSI");
			OutPutStr += ":";
			OutPutStr += pChildItem->text(8);
			OutPutStr += "\t";
			OutPutStr += GET_TXT("IDCS_OTHER_INFO");
			OutPutStr += ":";
			OutPutStr += pChildItem->text(9);
	

			OutPutStr += "\t\n";

		}	

		out<<OutPutStr;
	}
	
	if (!OutPutStr.isEmpty())
	{
		out<< "\t\n\n\n";
	}

	file.close();
	return true;
}

bool WirelessRecvDlg::IsEnableAnalysisTime()
{
	return (Qt::CheckState)CSingleton<AppConfig>::GetInstance()->GetWirelessAnalysisTime() == Qt::Checked;
}

void WirelessRecvDlg::slot_EnableAsysTimeCkbChange(int nState)
{
	CSingleton<WirelessRecvCtrl>::GetInstance()->SetEnableAnalysisTime(nState == Qt::Checked);
	CSingleton<AppConfig>::GetInstance()->SetWirelessAnalysisTime(nState);
}


void WirelessRecvDlg::slot_RecvIOState(const QString& strState)
{	
	if (mSaveLogCkb->isChecked())
	{
		QString  fileStr = WIDGETSTRING_GET("Wireless_Config","SaveFile");
		QFile file(fileStr);
		if (!file.open(QIODevice::WriteOnly|QIODevice::Append | QIODevice::Text))
			return ;

		QTextStream out(&file);		
		out<<strState;
		out<< "\t\n\n\n";
		file.close();
	}	
}

void WirelessRecvDlg::SaveCardInfo(const QString& cardStr)
{
	QMetaObject::invokeMethod(this, "slot_SaveCardInfo", Qt::QueuedConnection, Q_ARG(QString, cardStr) );

}

void WirelessRecvDlg::slot_SaveCardInfo(const QString& strCard)
{
	if (mSaveLogCkb->isChecked())
	{
		QString  fileStr = WIDGETSTRING_GET("Wireless_Config","SaveFile");
		QFile file(fileStr);
		if (!file.open(QIODevice::WriteOnly|QIODevice::Append | QIODevice::Text))
			return ;

		QTextStream out(&file);		
		out<<strCard;
		out<< "\t\n\n\n";
		file.close();
	}	
}

void WirelessRecvDlg::SaveReaderState(WirelessReaderInfo*pReaderInfo ,bool bOnline)
{

	if(!mSaveLogCkb->isChecked())
	{
		return;
	}

	QString  fileStr = WIDGETSTRING_GET("Wireless_Config","SaveFile");
	QFile file(fileStr);
	if (!file.open(QIODevice::WriteOnly|QIODevice::Append | QIODevice::Text))
		return ;

	QString tmpStr;

	tmpStr = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
	tmpStr += " ";

	tmpStr += GET_TXT("IDCS_IP_ADDR");
	tmpStr += ":";

	tmpStr += QString::fromUtf8((char*)pReaderInfo->bIpAddr);
	tmpStr += ":";
	tmpStr += QString("%1 ").arg(pReaderInfo->nPort);

	if (bOnline)
	{
		tmpStr += GET_TXT("IDCS_CONNET_SUCCESS");	
	}
	else
	{
		tmpStr += GET_TXT("IDCS_CLOSE_CONNET");	
	}
	
	QTextStream out(&file);		
	out<<tmpStr;
	out<< "\t\n\n\n";
	file.close();
}

void WirelessRecvDlg::SetRevMsg(WirelessReaderInfo* pWirelessReaderInfo,int msgID,unsigned char bCommand,unsigned char* pData, int nLen)
{
	unsigned char* tmpData = new unsigned char[nLen];
	memcpy(tmpData,pData,nLen);
	QMetaObject::invokeMethod(this, "slot_SetRevMsg", 
		Qt::QueuedConnection, 
		Q_ARG(void*, pWirelessReaderInfo),
		Q_ARG(int, msgID),
		Q_ARG(unsigned char, bCommand),
		Q_ARG(void*, tmpData),
		Q_ARG(int, nLen));

}

void WirelessRecvDlg::slot_SetRevMsg(void* pReaderInfo,int msgID,unsigned char bCommand,void*  pData, int nLen)
{
	WirelessReaderInfo* pWirelessReaderInfo = (WirelessReaderInfo*)pReaderInfo;
	unsigned char* pTmpData = (unsigned char*)pData;
	if(pTmpData[0] != 0)
	{
		MainShowMsg(GET_TXT("IDCS_RECV_STATE_ERRO_2").arg(bCommand).arg(pTmpData[0]));	
		delete[] pTmpData;
		pTmpData = NULL;
		return;
	}

	switch(bCommand)
	{
	case 0:
		break;
	case COM_CARRY_OP:
		if (pTmpData[0] == 0)
		{
			MainShowMsg(GET_TXT("IDCS_STOP_READ_SUCCESS"));	
		}
		else
		{
			MainShowMsg(GET_TXT("IDCS_STOP_READ_FAILED"));	
		}	
		break;
	case COM_SYS_QUERY:
		{
			if (nLen>1)
			{
				QTreeWidgetItem* item = FindReaderItem(pWirelessReaderInfo);
				if (item)
				{
					QString strTmp = QString::fromUtf8((char*)(pTmpData+1),nLen-1);
					item->setText(3,strTmp);
					MainShowMsg(GET_TXT("IDCS_DEVICE_NAME_QUERY_SUCCESS") + "--" + strTmp);
				}
			
			}
		}		
	case READER_TIME_QUERY:
	case READER_TIME_SET:	
	case COM_ANTENNA_QUERY:
	case COM_ANTENNA_SET:
	case COM_IO_OP:
	case COM_ANTENNA_SET_EX:
	case COM_ANTENNA_QUERY_EX:
	case COM_CARRYWAVE_QUERY:
	case COM_CARRYWAVE_SET:
		mWirelessDeviceInfoDlg->SetRevMsg(pWirelessReaderInfo,msgID,bCommand,pTmpData,nLen);
		break;
	default:
		mWirelessDeviceInfoDlg->SetRevMsg(pWirelessReaderInfo,msgID,bCommand,pTmpData,nLen);
		break;
	}

	delete[] pTmpData;
	pTmpData = NULL;
}

int WirelessRecvDlg::GetReaderItemIndex()
{
	for (int i = 0; i<255; ++i)
	{
		if (!FindItemIndex(i))
		{
			return i;
		}
	}
	return 0;
}

QTreeWidgetItem* WirelessRecvDlg::FindItemIndex(int nIndex)
{
	QTreeWidgetItem* item = NULL;
	for (int i=0; i<mTagTree->topLevelItemCount(); ++i)
	{
		item = mTagTree->topLevelItem(i);
		if (item->text(0).toInt() == nIndex)
		{
			return item;
		}
	}
	return NULL;
}

bool WirelessRecvDlg::QueryReaderName(WirelessReaderInfo* pReaderInfo)
{
	if(!pReaderInfo)
	{
		return false;
	}

	int nParam = 0x00;
	bool bRet = WIRELESS_SAAT_SysInfQuery(
		WIRELESSRECV_HANDLE,
		pReaderInfo,
		nParam);

	if(!bRet)
	{
		MainShowMsg(GET_TXT("IDCS_DEVICE_NAME_QUERY_FAILED"));	
	}

	return bRet;
}

void WirelessRecvDlg::slot_itemSyncTimeClicked()
{
	QTreeWidgetItem* item = mTagTree->currentItem();
	if (!item)
	{
		return;
	}
	unsigned char btPara[7] ;
	ZeroMemory(btPara,7);

	QDate tmpDate = QDate::currentDate();
	QTime tmpTime = QTime::currentTime();

	btPara[0] = C16Convert10(tmpTime.second());
	btPara[1] = C16Convert10(tmpTime.minute());
	btPara[2] = C16Convert10(tmpTime.hour());
	btPara[3] = C16Convert10(tmpDate.dayOfWeek());
	btPara[4] = C16Convert10(tmpDate.day());
	btPara[5] = C16Convert10(tmpDate.month());
	int nYear = C16Convert10(tmpDate.year() %100);		
	btPara[6] = nYear;

	WirelessReaderInfo* pReaderInfo =
		(WirelessReaderInfo*)(item->data(1, Qt::UserRole+1).toULongLong());

	bool bRet = false;
	bRet = WIRELESS_SAAT_SetReaderTime (
		WIRELESSRECV_HANDLE,
		pReaderInfo,
		btPara,7);

	if (bRet)
	{
		MainShowMsg(GET_TXT("IDCS_SYNCH_TIME_SUCCESS"));
	}
	else
	{		
		MainShowMsg(GET_TXT("IDCS_SYNCH_TIME_FAILED"));
	}
}

unsigned int WirelessRecvDlg::C16Convert10(int a)
{
	bool bok;
	return QString("%1").arg( a).toUInt(&bok,16);
}

void WirelessRecvDlg::slot_itemQueryNameClicked()
{
	QTreeWidgetItem* item = mTagTree->currentItem();
	if (!item)
	{
		return;
	}

	WirelessReaderInfo* pReaderInfo =
		(WirelessReaderInfo*)(item->data(1, Qt::UserRole+1).toULongLong());

	QueryReaderName(pReaderInfo);
}

void WirelessRecvDlg::slot_itemDeviceConfig()
{
	QTreeWidgetItem* item = mTagTree->currentItem();
	if (!item)
	{
		return;
	}

	if (HtMessageBox::Question(GET_TXT("IDCS_DEVICE_CONFIG_NEED_STOP"),this)
		!= HtMessageBox::RET_ENTER )
	{
		return;
	}

	WirelessReaderInfo* pReaderInfo =
		(WirelessReaderInfo*)(item->data(1, Qt::UserRole+1).toULongLong());

	bool bRet = false;
	bRet = WIRELESS_SAAT_PowerOff (
		WIRELESSRECV_HANDLE,
		pReaderInfo);

	if (!bRet)
	{
		MainShowMsg(GET_TXT("IDCS_STOP_READ_FAILED"));
		return;
	}	

	mWirelessDeviceInfoDlg->SetWirelessReaderInfo(pReaderInfo);
	mWirelessDeviceInfoDlg->exec();
	
	if (HtMessageBox::Question(GET_TXT("IDCS_DEVICE_CONFIG_NEED_REBOOT"),this)
		!= HtMessageBox::RET_ENTER )
	{
		return;
	}

	bRet = WIRELESS_SAAT_Reboot (
		WIRELESSRECV_HANDLE,
		pReaderInfo,0x00);
	if (!bRet)
	{
		MainShowMsg(GET_TXT("IDCS_REBOOT_FAILED"));
		return;
	}

	mWirelessDeviceInfoDlg->SetWirelessReaderInfo(NULL);
	
	DeleteReadItem(item);		
}


/************************************************************************/
/* 右击菜单                                                                     */
/************************************************************************/
TreeRightMenu::TreeRightMenu(QWidget *slotParent,QWidget *parent)
{

	/*m_DeviceConfigAct = new QAction( GET_TXT("IDCS_DEVICE_CONFIG"), this );
	connect( m_DeviceConfigAct, SIGNAL(triggered()), slotParent, SLOT(slot_itemDeviceConfig()) );
	addAction(m_DeviceConfigAct);*/

	m_RemoveAct = new QAction( GET_TXT("IDCS_REMOVE"), this );
	connect( m_RemoveAct, SIGNAL(triggered()), slotParent, SLOT(slot_itemRemoveClicked()) );
	addAction(m_RemoveAct);

	m_RebootAct = new QAction( GET_TXT("IDCS_REBOOT_DEVICE"), this );
	connect( m_RebootAct, SIGNAL(triggered()), slotParent, SLOT(slot_itemRebootClicked()) );
	addAction(m_RebootAct);

	m_SetTimeAct = new QAction( GET_TXT("IDCS_SYNCH_TIME"), this );
	connect( m_SetTimeAct, SIGNAL(triggered()), slotParent, SLOT(slot_itemSyncTimeClicked()) );
	addAction(m_SetTimeAct);

	m_QueryNameAct = new QAction( GET_TXT("IDCS_DEVICE_NAME_QUERY"), this );
	connect( m_QueryNameAct, SIGNAL(triggered()), slotParent, SLOT(slot_itemQueryNameClicked()) );
	addAction(m_QueryNameAct);

	m_SaveAct = new QAction( GET_TXT("IDCS_SAVE_FILE"), this );
	connect( m_SaveAct, SIGNAL(triggered()), slotParent, SLOT(slot_itemSaveClicked()) );
	addAction(m_SaveAct);
}

TreeRightMenu::~TreeRightMenu()
{

	if (m_RemoveAct)
	{
		delete m_RemoveAct;
		m_RemoveAct = NULL;
	}
	if (m_RebootAct)
	{
		delete m_RebootAct;
		m_RebootAct = NULL;
	}
}

