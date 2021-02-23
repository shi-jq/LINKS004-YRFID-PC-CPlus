#include "wifiselectdlg.h"
#include "ui_wifiselectdlg.h"
#include "LanguageSrc.h"
#include "appconfig.h"
#include "mainapp.h"
#include "RFIDAPIEXPORT.h"
#include "readerdllcommon.h"
#include "AtTransExport.h"
#include "wifiselectdlg.h"

WifiSelectDlg::WifiSelectDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WifiSelectDlg)
{
    ui->setupUi(this);
	this->setModal(true);
	this->setWindowTitle(GET_TXT("IDCS_SELECT_WIFI"));
	mScanBtn = ui->pushButton;
	mSelectBtn = ui->pushButton_3;
	mTreeWidget = ui->treeWidget;

	mScanBtn->setText(GET_TXT("IDCS_SELECT_WIFI"));
	mSelectBtn->setText(GET_TXT("IDCS_SELECT"));

	QStringList sl;
	sl 	<< GET_TXT("IDCS_NET_TYPE")
		<< GET_TXT("IDCS_SSID")		
		<< GET_TXT("IDCS_RSSI")
		<< GET_TXT("IDCS_CHANNEL")
		<< GET_TXT("IDCS_SECURITY_IS")		
		<< GET_TXT("IDCS_MAC");

	mTreeWidget->setHeaderLabels( sl );
	mTreeWidget->setColumnCount( 6);
	mTreeWidget->setColumnWidth( 0, 80 );
	mTreeWidget->setColumnWidth( 1, 150 );
	mTreeWidget->setColumnWidth( 2, 80 );
	mTreeWidget->setColumnWidth( 3, 60 );
	mTreeWidget->setColumnWidth( 4, 80 );
	mTreeWidget->setColumnWidth( 5, 100 );

	connect( mScanBtn, SIGNAL( clicked()), this, SLOT( slot_scanBtnClicked( ) ) );
	connect( mSelectBtn, SIGNAL( clicked()), this, SLOT( slot_selectBtnClicked( ) ) );
	connect( mTreeWidget, SIGNAL( itemDoubleClicked(QTreeWidgetItem *,int)), this, SLOT( slot_itemDoubleClicked(QTreeWidgetItem *,int) ) );

}

WifiSelectDlg::~WifiSelectDlg()
{
    delete ui;
}

void WifiSelectDlg::slot_scanBtnClicked()
{
	ReaderDllCommon*	pReaderDllCommon = (ReaderDllCommon*)pMainApp->GetReader();	
	Q_ASSERT(pReaderDllCommon);
	if (!pReaderDllCommon->CheckState(STATE_CONNET))
	{
		MainShowMsg(GET_TXT("IDCS_READ_NO_LINK"));
		return ;
	}

	mTreeWidget->clear();
	char pNet[4045] = {0};

	bool bRet = Wifi_Search(pReaderDllCommon->m_hCom, pNet);
	if (bRet)
	{
		QString retStr = QString::fromUtf8(pNet);
		QStringList itemList = retStr.split(";");
		QStringList tempList;
		QTreeWidgetItem* item = NULL;
		QString tempStr;
		for (int i=0;i<itemList.count(); ++i)
		{
			tempList = itemList.at(i).split(",");
			if (tempList.count() < 6)
			{
				continue;
			}
			item = new QTreeWidgetItem(mTreeWidget);
			if (tempList.at(1).toInt() == 0)//网络类型
			{
				tempStr = GET_TXT("IDCS_JICHUWANG");
			}
			else
			{
				tempStr = GET_TXT("IDCS_ZIZUWANG");
			}
			item->setText(0,tempStr);

			item->setText(1,tempList.at(4));//ssid		
			item->setText(2,"-"+tempList.at(5)+"db");//信号强度
			item->setText(3,tempList.at(2));//信号道
			if(tempList.at(3).toInt() == 0)
			{
				tempStr = GET_TXT("IDCS_NO");
			}
			else
			{
				tempStr = GET_TXT("IDCS_YES");
			}
			item->setText(4,tempStr);//是否加密		
			item->setText(5,tempList.at(0).toUpper());			
		}
		
		MainShowMsg(GET_TXT("IDCS_SELECT_SUCCUESS"));
	}
	else
	{
		MainShowMsg(GET_TXT("IDCS_SELECT_FAILED"));
	}
}	

void WifiSelectDlg::slot_selectBtnClicked()
{
	QTreeWidgetItem* item;
	QList<QTreeWidgetItem*> itemList = mTreeWidget->selectedItems();
	if (itemList.count() > 0)
	{
		item = itemList.at(0);
		mCurSSID = item->text(1);
		
		this->accept();		
	}
	else
	{
		mCurSSID.clear();
	}
}

QString WifiSelectDlg::GetSelectSSID()
{
	return mCurSSID;
}

void WifiSelectDlg::showEvent(QShowEvent *ev)
{
	mCurSSID.clear();
	QDialog::showEvent(ev);
}

void WifiSelectDlg::slot_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
	if (item)
	{
		mCurSSID = item->text(1);
		this->accept();		
	}
}
