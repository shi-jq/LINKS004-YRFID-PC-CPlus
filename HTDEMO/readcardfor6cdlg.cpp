#include "readcardfor6cdlg.h"
#include "ui_readcardfor6cdlg.h"
#include <assert.h>
#include <QTimer>
#include <QDateTime>
#include <QSound>
#include <QFile>
#include <QMenu>
#include <QTextStream>
#include <QClipboard>
#include <QApplication>
#include <QFileDialog>
#include "LanguageSrc.h"
#include "widgetconfig.h"
#include "readerdllbase.h"
#include "readermanager.h"
#include "mainapp.h"
#include "ReadCardFor6CThread.h"
#include "RFIDAPIEXPORT.h"
#include "readerdllbase.h"
#include "mainapp.h"
#include "mainwindow.h"
#include "appconfig.h"
#include "BuzzerSpeakerCtrl.h"
#include <QKeyEvent>
#include "workdpacedlg.h"
#include "tagopdialog.h"

ReadCardFor6CDlg::ReadCardFor6CDlg(QWidget *parent,workDpaceDlg* pWorkSpaceDlg) :
    QWidget(parent),
    ui(new Ui::ReadCardFor6CDlg)
{
	mWorkSpaceDlg = pWorkSpaceDlg;
    ui->setupUi(this);
	CreateView();
	UpdateLanguage();
	haveNewCard = false;
	mIsReading = false;

	mTagOpBtn->hide();
}

ReadCardFor6CDlg::~ReadCardFor6CDlg()
{
	slot_stopReadBtnClicked();

	if (mRefreshTimer)
	{
		delete mRefreshTimer;
		mRefreshTimer = NULL;
	}
	if (mBeepSound)
	{
		delete mBeepSound;
		mBeepSound = NULL;
	}
/*	if (mBeepTimer)
	{
		delete mBeepTimer;
		mBeepTimer = NULL;
	}*/	

	if(mSaveTimer)
	{
		delete mSaveTimer;
		mSaveTimer = NULL;
	}

	ClearAllThread();

    delete ui;
}

void ReadCardFor6CDlg::CreateView()
{
	mRecordCheckBox = ui->checkBox_2;
	mRecordSb = ui->spinBox_2;
	mClearBtn = ui->pushButton;
	mMakeTagUpLoadBtn = ui->pushButton_3;
    ui->pushButton_3->setHidden(true);
	mYTagReadBtn = ui->pushButton_2;
	mStopReadBtn = ui->pushButton_4;
	mAddFilterBtn = ui->pushButton_5;
	mClearFilterBtn = ui->pushButton_6;

	mAllCountLable = ui->label_9;
	mTagOpBtn = ui->pushButton_7;
	mTagTree = ui->treeWidget;
	mTagTree->setSortingEnabled(true);	

	mTagOpDialog = new TagOpDialog(this);
	mTagOpDialog->hide();

	mMakeTagUpLoadBtn->setEnabled(true);
	mYTagReadBtn->setEnabled(true);
	mStopReadBtn->setEnabled(false);
	
	mRecordSb->setMaximum(60000);
	mRecordSb->setMinimum(1);
	mRecordSb->setSingleStep(100);
	mRecordSb->setValue(1000);

	QStringList sl;
	sl << GET_TXT("IDCS_NUMBER")
		<< GET_TXT("IDCS_CRAD_NUMBER")
		<< GET_TXT("IDCS_READTIME")
		<< GET_TXT("IDCS_ANTENNA_NO")
		<< GET_TXT("IDCS_TAG_COUNT")
		<< GET_TXT("IDCS_TAG_STATUS")
		<< GET_TXT("IDCS_RSSI")
		<< GET_TXT("IDCS_OTHER_INFO");

	mTagTree->setHeaderLabels( sl );
	mTagTree->setColumnCount( 8);
	mTagTree->setColumnWidth( 0, 60 );
	mTagTree->setColumnWidth( 1, 80 );
	mTagTree->setColumnWidth( 2, 130 );
	mTagTree->setColumnWidth( 3, 60 );//天线号
	mTagTree->setColumnWidth(4, 100);//天线个数
	mTagTree->setColumnWidth( 5, 140 );
	mTagTree->setColumnWidth( 6, 70 );
	mTagTree->setColumnWidth( 7, 60 );
	mTagTree->setAlternatingRowColors( true );

	connect( mMakeTagUpLoadBtn, SIGNAL( clicked()), this, SLOT( slot_makeTagUpLoadBtnClicked( ) ) );
	connect( mYTagReadBtn, SIGNAL( clicked()), this, SLOT( slot_yTagReadBtnClicked( ) ) );
	connect( mStopReadBtn, SIGNAL( clicked()), this, SLOT( slot_stopReadBtnClicked( ) ) );
	connect( mTagOpBtn, SIGNAL( clicked()), this, SLOT( slot_TagOpBtnClicked( ) ) );
	connect( mAddFilterBtn, SIGNAL( clicked()), this, SLOT( slot_AddFilterBtnClicked( ) ) );
	connect( mClearFilterBtn, SIGNAL( clicked()), this, SLOT( slot_ClearFilterBtnClicked( ) ) );

	connect( mClearBtn, SIGNAL( clicked()), this, SLOT( slot_ClearBtnClicked( ) ) );
	
	mRefreshTimer =  new QTimer(this);
	mSaveTimer = new QTimer(this);

	QString fileName =QString("%1/%2").arg(CSingleton<AppConfig>::GetInstance()->GetRunPath())
		.arg(WIDGETSTRING_GET("ReadCardFor6CDlg","SoundFileName"));

	mBeepSound = new QSound(fileName,this);
	connect(mRefreshTimer, SIGNAL(timeout()), this, SLOT(slot_refresh_time()));

	connect(mSaveTimer, SIGNAL(timeout()), this, SLOT(slot_save_file()));

	connect( this, SIGNAL( sig_sendReadCount(int,int,int)), pMainApp->GetMainWindow(), SLOT( slot_UpdateReadCount(int,int ,int) ) );
	connect( mTagTree, SIGNAL( itemPressed(QTreeWidgetItem *,int)), this, SLOT( slot_itemRightClicked(QTreeWidgetItem *,int) ) );
}

void ReadCardFor6CDlg::UpdateLanguage()
{	
	ui->checkBox_2->setText(GET_TXT("IDCS_RECORD_INFO"));
	ui->label_6->setText(GET_TXT("IDCS_READ_ALL_COUNT"));
	mYTagReadBtn->setText(GET_TXT("IDCS_START"));
}

void ReadCardFor6CDlg::slot_refresh_time()
{
	unsigned int nowCount = 0;
	unsigned int cardSizeCount = 0;

	QTreeWidgetItem* tagItem = NULL;
	std::vector<CardFor6CInfo*> tmpList;
	CardFor6CInfo* pCardFor6CInfo = NULL;

	std::vector<CardFor6CInfo*>::iterator ListIter;
	std::map<QString,ReadCardFor6CThread*>::iterator ThreadIter = mThreadMap.begin();
	for (; ThreadIter!=mThreadMap.end(); ++ThreadIter)
	{
		ThreadIter->second->GetCardList(tmpList);
		ListIter = tmpList.begin();
		for(; ListIter!=tmpList.end(); ++ListIter)
		{	

			pCardFor6CInfo = *ListIter;
			nowCount += pCardFor6CInfo->m_nAntennaCount;


			if (!mFilterMap.empty())
			{
				if (!mFilterMap.contains(pCardFor6CInfo->m_szCardID))
				{
					continue;
				}
			}

			tagItem = GetTagItem(ThreadIter->first,pCardFor6CInfo->m_szCardID, pCardFor6CInfo->m_nAntennaNo);
			tagItem->setText(1,pCardFor6CInfo->m_szCardID);
	
			tagItem->setText(2,pCardFor6CInfo->m_szCurReadTime);
			tagItem->setText(3,QString("%1").arg(pCardFor6CInfo->m_nAntennaNo));	
			tagItem->setText(4, QString("%1").arg(pCardFor6CInfo->m_nAntennaCount));
			tagItem->setText(5,pCardFor6CInfo->m_szTagState);	
			tagItem->setText(6,pCardFor6CInfo->m_szRssi);	
			tagItem->setText(7,pCardFor6CInfo->m_otherInfo);	
			
		}
		cardSizeCount = tmpList.size();

		ListIter = tmpList.begin();
		for(; ListIter!=tmpList.end(); ++ListIter)
		{
			delete *ListIter;
			*ListIter = NULL;
		}
		tmpList.clear();
	}
	

	mAllCountLable->setText(QString("%1").arg(nowCount));

	if (nowCount != mReadCount)
		haveNewCard = true;

	int nTime = mFreshTime.elapsed();
	mFreshTime.restart();
	int speed = 0;
	if (nTime > 0)
	{
		speed = ((nowCount-mReadCount)*1000)/(nTime) ;
	}
	mReadCount = nowCount;
	emit sig_sendReadCount(cardSizeCount,speed,1);	
}

void ReadCardFor6CDlg::startReadBtnClicked(int nReadType)
{
	slot_ClearBtnClicked();	

	UpdateReaderThreadMap();

	bool bRet = StartRead(nReadType);

	if (bRet)
	{		
		mRefreshTimer->start(WIDGETSTRING_GET("ReadCardFor6CDlg","RefreshTimer").toInt());
		
		mReadCount = 0;

		if (mRecordCheckBox->isChecked())
		{
			mSaveTimer->start(mRecordSb->value());
		}
		
		mFreshTime.restart();
		pMainApp->SetReading(true);
		pMainApp->GetMainWindow()->updateReaderState(STATE_READING);
		emit sig_sendReadCount(0,0,0);
		MainShowMsg(GET_TXT("IDCS_READ_SUCCESS"),false,false);
		mIsReading = true;

		mMakeTagUpLoadBtn->setEnabled(false);
		mYTagReadBtn->setEnabled(false);
		mStopReadBtn->setEnabled(true);
		mTagOpBtn->setEnabled(false);
	}
	else
	{
		MainShowMsg(GET_TXT("IDCS_READ_FAILED"),false,false);
	}
	
}

void ReadCardFor6CDlg::slot_stopReadBtnClicked()
{
	StopRead();	
	mRefreshTimer->stop();
	mSaveTimer->stop();	
	pMainApp->SetReading(false);
	pMainApp->GetMainWindow()->updateReaderState(STATE_CONNET);
	MainShowMsg(GET_TXT("IDCS_STOP_SCCUSS"),false,false);
	mIsReading = false;

	mMakeTagUpLoadBtn->setEnabled(true);
	mYTagReadBtn->setEnabled(true);
	mStopReadBtn->setEnabled(false);
	mTagOpBtn->setEnabled(true);
}

void ReadCardFor6CDlg::slot_ClearBtnClicked()
{
	ClearCard();
	mReadCount=0;
	emit sig_sendReadCount(0,0,2);
	mAllCountLable->setText(QString("%1").arg(0));
	mTagTree->clear();
}

bool ReadCardFor6CDlg::SendReadCommand(const QString& strInfo,int nReadType)
{
	ReaderDllBase* pReaderDllBase = CSingleton<ReaderManager>::GetInstance()->FindReader(strInfo);
	if (!pReaderDllBase)
	{
		MainShowMsg(GET_TXT("IDCS_READ_NO_LINK"));
		return false;
	}

	bool bRet = false;
	
	int isDoAffirm = 0x01;
	int nIDType = 0x01;
	bRet = SAAT_YMakeTagUpLoadIDCode(
		pReaderDllBase->m_hCom,
		isDoAffirm,
		nIDType);


	return bRet;
}



bool ReadCardFor6CDlg::SendStopCommand(const QString& strInfo)
{	
	ReaderDllBase* pReaderDllBase = CSingleton<ReaderManager>::GetInstance()->FindReader(strInfo);
	if (!pReaderDllBase || pReaderDllBase->GetState() == STATE_DISABLE || pReaderDllBase->GetState() == STATE_DISCONNET )
	{
		MainShowMsg(GET_TXT("IDCS_READ_NO_LINK"));
		return false;
	}
	return SAAT_PowerOff(pReaderDllBase->m_hCom);
}

QTreeWidgetItem* ReadCardFor6CDlg::GetTagItem(const QString&strInfo,const QString& cardStr,int antenna)
{
	QTreeWidgetItem * item = FindTagItem(strInfo,cardStr, antenna);
	if (item)
	{
		return item;
	}

	item = CreateTagItem(strInfo,cardStr,antenna);
	return item;
}

QTreeWidgetItem* ReadCardFor6CDlg::FindTagItem(const QString&strInfo,const QString& cardStr, int antenna)
{
	QTreeWidgetItem* tagItem = NULL;
	QTreeWidgetItem* tmpItem = NULL;
	QString tmpStr;

	QTreeWidgetItem* readerItem = GetReaderItem(strInfo);
	for (int j=0; j<readerItem->childCount(); ++j)
	{
		tmpItem  = readerItem->child(j);
		
		tmpStr = tmpItem->data(1,Qt::UserRole+1).toString();
		int antennaItem = tmpItem->data(3, Qt::UserRole + 1).toInt();
		if (tmpItem->data(1,Qt::UserRole+1).toString().compare(cardStr) == 0
			&& antennaItem == antenna)
		{
			tagItem = tmpItem; 
			break;
		}		
	}
	return tagItem;
}

QTreeWidgetItem* ReadCardFor6CDlg::GetReaderItem(const QString&strInfo)
{
	QTreeWidgetItem* tagItem = NULL;
	QTreeWidgetItem* tmpItem = NULL;
	for (int j=0; j<mTagTree->topLevelItemCount(); ++j)
	{
		tmpItem  = mTagTree->topLevelItem(j);
		if(tmpItem->text(1).contains(strInfo))
		{
			tagItem = tmpItem;
		}
	}

	if (!tagItem)
	{
		tagItem = new QTreeWidgetItem(mTagTree);
		tagItem->setText(0,QString("%1").arg(mTagTree->topLevelItemCount()));
		tagItem->setText(1,strInfo);
		tagItem->setExpanded(true);
	}

	return tagItem;
}

QTreeWidgetItem* ReadCardFor6CDlg::CreateTagItem(const QString&strInfo,const QString& cardStr, int antenna)
{
	QTreeWidgetItem* readerItem = GetReaderItem(strInfo);
	QTreeWidgetItem* tagItem = NULL;
	tagItem = new QTreeWidgetItem(readerItem);
	tagItem->setText(0,QString::fromUtf8("%1").arg(readerItem->childCount()));
	tagItem->setText(1,cardStr);
	tagItem->setData(1,Qt::UserRole+1,cardStr);
	tagItem->setText(3, QString::number(antenna));
	tagItem->setData(3, Qt::UserRole + 1, antenna);

	return tagItem;
}


void ReadCardFor6CDlg::slot_beep()
{
	if (haveNewCard)
	{	
		CSingleton<BuzzerSpeakerCtrl>::GetInstance()->OpenBuzzer();
		haveNewCard = false;
	}
}


void ReadCardFor6CDlg::slot_save_file()
{
	SaveDataToFile(WIDGETSTRING_GET("ReadCardFor6CDlg","SaveFile"));
	
}

void ReadCardFor6CDlg::slot_itemRightClicked(QTreeWidgetItem *item, int column)
{
	if(!(QApplication::mouseButtons()&Qt::RightButton))
	{
		return;
	}

	QMenu* pMenu = new QMenu(this);
	QAction* saveItemAct = new QAction( GET_TXT("IDCS_EXPORT"), pMenu );
	connect( saveItemAct, SIGNAL(triggered()), this, SLOT(slot_exportItem()) );
	pMenu->addAction(saveItemAct);

	pMenu->exec(QCursor::pos());

	delete saveItemAct;
	saveItemAct = NULL;
	delete pMenu;
	pMenu = NULL;
}

void ReadCardFor6CDlg::slot_exportItem()
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

bool ReadCardFor6CDlg::SaveDataToFile(const QString& fileStr)
{
	QFile file(fileStr);
	if (!file.open(QIODevice::WriteOnly|QIODevice::Append | QIODevice::Text))
		return false;

	QTextStream out(&file);	
	QString OutPutStr;	

	std::vector<CardFor6CInfo*> tmpList;
	CardFor6CInfo* pCardFor6CInfo = NULL;

	std::map<QString,ReadCardFor6CThread*>::iterator ThreadIter = mThreadMap.begin();
	for (; ThreadIter!=mThreadMap.end(); ++ThreadIter)
	{
		ThreadIter->second->GetCardList(tmpList);
		OutPutStr = QString("%1").arg(ThreadIter->first);
		OutPutStr += "\t\n"; 
		out<<OutPutStr;
		std::vector<CardFor6CInfo*>::iterator ListIter = tmpList.begin();

		for(int index=1; ListIter!=tmpList.end(); ++ListIter,++index)
		{			
			pCardFor6CInfo = *ListIter;
			OutPutStr.clear();
			OutPutStr += GET_TXT("IDCS_NUMBER");
			OutPutStr += ":";
			OutPutStr += QString("%1").arg(index);
			OutPutStr += "\t";
			OutPutStr += GET_TXT("IDCS_CRAD_NUMBER");
			OutPutStr += ":";
			OutPutStr += pCardFor6CInfo->m_szCardID;	
			OutPutStr += "\t";
			OutPutStr += GET_TXT("IDCS_READTIME");
			OutPutStr += ":";
			OutPutStr += pCardFor6CInfo->m_szCurReadTime;
			OutPutStr += "\t";
			OutPutStr += GET_TXT("IDCS_ANTENNA_NO");
			OutPutStr += ":";
			OutPutStr += QString("%1").arg(pCardFor6CInfo->m_nAntennaNo);
			OutPutStr += "\t";
			OutPutStr += GET_TXT("IDCS_TAG_COUNT");
			OutPutStr += ":";
			OutPutStr += QString("%1").arg(pCardFor6CInfo->m_nAntennaCount);		
			OutPutStr += "\t\n";

			out<<OutPutStr;

		}

		out<< "\t\n";

		ListIter = tmpList.begin();
		for(; ListIter!=tmpList.end(); ++ListIter)
		{
			delete *ListIter;
			*ListIter = NULL;
		}
		tmpList.clear();
	}

	file.close();
	return true;
}

void ReadCardFor6CDlg::UpdateReaderThreadMap()
{
	std::map<QString,ReaderDllBase*> readerMap;
	CSingleton<ReaderManager>::GetInstance()->GetConnectReaderMap(readerMap);

	std::map<QString,ReadCardFor6CThread*>::iterator threadIter = mThreadMap.begin();
	while(threadIter!=mThreadMap.end())
	{
		if (readerMap.find(threadIter->first) == readerMap.end())
		{	
			delete threadIter->second;			
			mThreadMap.erase(threadIter++);
		}
		else
		{
			threadIter++;
		}
	}	

	std::map<QString,ReaderDllBase*>::iterator iter = readerMap.begin();
	for (; iter!=readerMap.end(); ++iter)
	{
		CreateThread(iter->second,iter->first);
	}
	
}

ReadCardFor6CThread* ReadCardFor6CDlg::FindThread(const QString& strInfo)
{
	std::map<QString,ReadCardFor6CThread*>::iterator iter = mThreadMap.find(strInfo);
	if (iter != mThreadMap.end())
	{
		return iter->second;
	}

	return NULL;
}

void ReadCardFor6CDlg::CreateThread(ReaderDllBase* pReaderDllBase,const QString& strInfo)
{
	ReadCardFor6CThread* pReadCardFor6CThread = FindThread(strInfo);
	if (!pReadCardFor6CThread)
	{
		pReadCardFor6CThread = new ReadCardFor6CThread(
			pReaderDllBase,
			this);
		mThreadMap[strInfo] = pReadCardFor6CThread;
	}
	else
	{
		pReadCardFor6CThread->SetReader(pReaderDllBase);
	}
}

void ReadCardFor6CDlg::ClearAllThread()
{
	std::map<QString,ReadCardFor6CThread*>::iterator threadIter = mThreadMap.begin();
	for(;threadIter!=mThreadMap.end();++threadIter)
	{
		delete threadIter->second;		
	}	

	mThreadMap.clear();
}

bool ReadCardFor6CDlg::StartRead(int nReadType)
{
	std::map<QString,ReadCardFor6CThread*>::iterator threadIter = mThreadMap.begin();
	for(;threadIter!=mThreadMap.end();++threadIter)
	{
		if (SendReadCommand(threadIter->first,nReadType))
		{
			threadIter->second->StartRead(nReadType);
		}
		else
		{
			MainShowMsg(GET_TXT("IDCS_READ_FAILED_1").arg(threadIter->first));
		}
	}

	return true;
}

bool ReadCardFor6CDlg::StopRead()
{
	std::map<QString,ReadCardFor6CThread*>::iterator threadIter = mThreadMap.begin();
	for(;threadIter!=mThreadMap.end();++threadIter)
	{
		SendStopCommand(threadIter->first);		
		threadIter->second->StopRead();	
	}

	return true;
}

bool ReadCardFor6CDlg::ClearCard()
{
	std::map<QString,ReadCardFor6CThread*>::iterator threadIter = mThreadMap.begin();
	for(;threadIter!=mThreadMap.end();++threadIter)
	{
		threadIter->second->clearCard();	
	}

	return true;
}

void ReadCardFor6CDlg::slot_makeTagUpLoadBtnClicked()
{
	startReadBtnClicked(ReadCardFor6CThread::READ_FOR_MAKETAGUPLOAD);
}

void ReadCardFor6CDlg::slot_yTagReadBtnClicked()
{
	startReadBtnClicked(ReadCardFor6CThread::READ_FOR_YTAGREAD);
}

void ReadCardFor6CDlg::slot_TagOpBtnClicked()
{
	QString tagStr;
	QTreeWidgetItem* item = mTagTree->currentItem();
	if (item && item->parent())
	{
		tagStr = item->text(1);
	}
	mTagOpDialog->SetTagStr(tagStr);
	mTagOpDialog->exec();
}

void ReadCardFor6CDlg::slot_AddFilterBtnClicked()
{
	QTreeWidgetItem* item = mTagTree->currentItem();
	if (item && item->parent())
	{
		QString tagStr = item->text(1);
		mFilterMap.push_back(tagStr);
		MainShowMsg(GET_TXT("IDCS_ADD_FILTER_SUCCESS_1").arg(tagStr));
	}
	else
	{
		MainShowMsg(GET_TXT("IDCS_SELECT_ONE_ITEM"));
	}

}

void ReadCardFor6CDlg::slot_ClearFilterBtnClicked()
{
	mFilterMap.clear();	
	MainShowMsg(GET_TXT("IDCS_FLASH_CLEAR_SUCCESS"));
}
