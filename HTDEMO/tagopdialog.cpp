#include "tagopdialog.h"
#include "ui_tagopdialog.h"
#include "findtagform.h"
#include "lockopform.h"
#include "pwdsetform.h"
#include "readwritedataform.h"
#include "writeeidform.h"
#include "LanguageSrc.h"
#include "mainapp.h"
#include "widgetconfig.h"

TagOpDialog::TagOpDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TagOpDialog)
{
    ui->setupUi(this);
	mListWidget = ui->listWidget;
	mStackedWidget = ui->stackedWidget;
	this->setWindowTitle(GET_TXT("IDCS_TAG_OP"));

	QListWidgetItem* pListWidgetItem = NULL;

	mFindTagForm = new FindTagForm(this);
	pListWidgetItem = new QListWidgetItem(mListWidget);
	pListWidgetItem->setText(GET_TXT("IDCS_FIND_TAG"));
	pListWidgetItem->setTextAlignment(Qt::AlignCenter);
	pListWidgetItem->setData(Qt::UserRole+1,0);
	mListWidget->addItem(pListWidgetItem);
	mStackedWidget->addWidget(mFindTagForm);

	//mLockOpForm = new LockOpForm(this);
	//pListWidgetItem = new QListWidgetItem(mListWidget);
	//pListWidgetItem->setText(GET_TXT("IDCS_LOCK_TAG"));
	//pListWidgetItem->setTextAlignment(Qt::AlignCenter);
	//pListWidgetItem->setData(Qt::UserRole+1,1);
	//mListWidget->addItem(pListWidgetItem);
	//mStackedWidget->addWidget(mLockOpForm);

	//mPwdSetForm = new PwdSetForm(this);
	//pListWidgetItem = new QListWidgetItem(mListWidget);
	//pListWidgetItem->setText(GET_TXT("IDCS_PASSWORD_SET"));
	//pListWidgetItem->setTextAlignment(Qt::AlignCenter);
	//pListWidgetItem->setData(Qt::UserRole+1,2);
	//mListWidget->addItem(pListWidgetItem);
	//mStackedWidget->addWidget(mPwdSetForm);


	mReadWriteDataForm = new ReadWriteDataForm(this);
	pListWidgetItem = new QListWidgetItem(mListWidget);
	pListWidgetItem->setText(GET_TXT("IDCS_READ_WRITE_DATA"));
	pListWidgetItem->setTextAlignment(Qt::AlignCenter);
	pListWidgetItem->setData(Qt::UserRole+1,1);
	mListWidget->addItem(pListWidgetItem);
	mStackedWidget->addWidget(mReadWriteDataForm);

	/*mWriteEidForm = new WriteEidForm(this);
	pListWidgetItem = new QListWidgetItem(mListWidget);
	pListWidgetItem->setText(GET_TXT("IDCS_WRITE_EID"));
	pListWidgetItem->setTextAlignment(Qt::AlignCenter);
	pListWidgetItem->setData(Qt::UserRole+1,4);
	mListWidget->addItem(pListWidgetItem);
	mStackedWidget->addWidget(mWriteEidForm);*/

	connect( mListWidget, SIGNAL( itemClicked(QListWidgetItem*)), this, SLOT( slot_ListItemClicked(QListWidgetItem * ) ) );
}

TagOpDialog::~TagOpDialog()
{
    delete ui;
}

void TagOpDialog::slot_ListItemClicked(QListWidgetItem* item)
{
	if (item)
	{
		int nIndex = (item->data(Qt::UserRole+1).toInt());
		mStackedWidget->setCurrentIndex(nIndex);
	}
}

void TagOpDialog::SetTagStr(const QString& tagStr)
{
	mFindTagForm->SetTagID(tagStr);
	//mWriteEidForm->SetTagID(tagStr);
	mReadWriteDataForm->SetTagID(tagStr);
	//mPwdSetForm->SetTagID(tagStr);
	//mLockOpForm->SetTagID(tagStr);
}
