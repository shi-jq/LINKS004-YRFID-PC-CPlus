#include "oplistdlg.h"
#include "ui_oplistdlg.h"
#include <QDateTime>
#include "appconfig.h"
#include "readerdllbase.h"
#include "mainapp.h"
#include "widgetconfig.h"
#include "LanguageSrc.h"
#include "readermanager.h"

OpListDlg::OpListDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OpListDlg)
{
    ui->setupUi(this);
	mOpListWidget= ui->treeWidget;
	mClearBtn = ui->pushButton;

	QStringList sl;
	sl << QString::fromUtf8("") 
		<< QString::fromUtf8("" )
		<< QString::fromUtf8("" )
		<< QString::fromUtf8("" );

	mOpListWidget->setHeaderLabels( sl );
	mOpListWidget->setColumnCount( 4);
	mOpListWidget->setColumnWidth( 0, 80 );
	mOpListWidget->setColumnWidth( 1, 100 );
	mOpListWidget->setColumnWidth( 2, 130 );
	
	connect( mClearBtn, SIGNAL( clicked()), this, SLOT( slot_clearBtnClicked( ) ) );

	itemCount= 0;
	MaxOpRecord = WIDGETSTRING_GET("OpListDlg","Max_OPERATE_RECORD").toInt();
	ToDeleteRecord=  WIDGETSTRING_GET("OpListDlg","OVER_TO_DELETE").toInt();

	mClearBtn->setText(GET_TXT("IDCS_CLEAR"));

}

OpListDlg::~OpListDlg()
{
    delete ui;
}

void OpListDlg::ShowMsg(QString msg,bool getErro,bool getReader)
{
	QMetaObject::invokeMethod(this, "slot_showMsg", Qt::QueuedConnection, Q_ARG(QString, msg) , Q_ARG(bool, getErro), Q_ARG(bool, getReader)  );
	
}

void OpListDlg::slot_showMsg(QString msg,bool getErro,bool getReader)
{
	itemCount++;
	QTreeWidgetItem* item = new QTreeWidgetItem();
	item->setText(0,QString("%1").arg(itemCount));

	QString showMsg = msg;	
	item->setText(1,QDateTime::currentDateTime().toString("hh:mm:ss"));
	if(getReader)
	{
		item->setText(2, CSingleton<ReaderManager>::GetInstance()->GetReaderStrInfo());
	}	
	item->setText(3,showMsg);

	int topItemCount = mOpListWidget->topLevelItemCount();
	mOpListWidget->insertTopLevelItem(topItemCount,item);
	topItemCount++;

	if (topItemCount > MaxOpRecord)
	{
		for (int i=0;(i<ToDeleteRecord) && (topItemCount>0); ++i)
		{
		
			topItemCount -- ;
			item = mOpListWidget->topLevelItem(0);
			delete item;
			item = NULL;	
		}			
	}

	mOpListWidget->scrollToBottom();
}

void OpListDlg::slot_clearBtnClicked()
{
	mOpListWidget->clear();
	itemCount = 0;
}



