#include "findtagform.h"
#include "ui_findtagform.h"
#include "LanguageSrc.h"
#include "appconfig.h"
#include "mainapp.h"
#include "RFIDAPIEXPORT.h"
#include "readerdllbase.h"

FindTagForm::FindTagForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FindTagForm)
{
    ui->setupUi(this);
	mFindBtn = ui->pushButton;
	mStopFindBtn = ui->pushButton_2;
	mTagEdit = ui->lineEdit;
	mLedCkb = ui->checkBox;
	mBeepCkb = ui->checkBox_2;
	mLedCkb->setChecked(true);
	mBeepCkb->setChecked(true);

	connect( mFindBtn, SIGNAL( clicked()), this, SLOT( slot_FindBtnClicked( ) ) );
	connect( mStopFindBtn, SIGNAL( clicked()), this, SLOT( slot_StopBtnClicked( ) ) );
}

FindTagForm::~FindTagForm()
{
    delete ui;
}

void FindTagForm::slot_FindBtnClicked()
{
	ReaderDllBase*	pReaderDllBase = pMainApp->GetReader();	
	if (!pReaderDllBase)
	{
		MainShowMsg(GET_TXT("IDCS_READ_NO_LINK"));
		return;
	}
	if (!pReaderDllBase->CheckState(STATE_CONNET))
	{
		MainShowMsg(GET_TXT("IDCS_READ_NO_LINK"));
		return ;
	}
	
	if (mTagEdit->text().isEmpty())
	{
		MainShowMsg(GET_TXT("IDCS_TAG_NOT_EMPTY"));
		return;
	}

	unsigned char isenable = 0;
	if (mBeepCkb->isChecked())
	{
		isenable = isenable | 0x01;
	}
	if (mLedCkb->isChecked())
	{
		isenable = isenable | 0x02;
	}

	int data = mTagEdit->text().toInt();
	unsigned char sz[4];
	memset(sz,0, 4);
	sz[0] = (unsigned char)((data >> 24) & 0xFF);
	sz[1] = (unsigned char)((data >> 16) & 0xFF);
	sz[2] = (unsigned char)((data >> 8) & 0xFF);
	sz[3] = (unsigned char)(data & 0xFF);

	if (SAAT_YTagSelect(pReaderDllBase->m_hCom, isenable, 0x01, sz, 4))
	{
		MainShowMsg(GET_TXT("IDCS_FIND_TAG_SUCCESS"));	
	}
	else
	{
		MainShowMsg(GET_TXT("IDCS_FIND_TAG_FAILED"),true);
	}
}

void FindTagForm::slot_StopBtnClicked()
{
	ReaderDllBase*	pReaderDllBase = pMainApp->GetReader();	
	if (!pReaderDllBase)
	{
		MainShowMsg(GET_TXT("IDCS_READ_NO_LINK"));
		return;
	}
	if (!pReaderDllBase->CheckState(STATE_CONNET))
	{
		MainShowMsg(GET_TXT("IDCS_READ_NO_LINK"));
		return ;
	}

	if (SAAT_PowerOff(pReaderDllBase->m_hCom))
	{
		MainShowMsg(GET_TXT("IDCS_STOP_SCCUSS"));	
	}
	else
	{
		MainShowMsg(GET_TXT("IDCS_STOP_FAILED"),true);
	}
	
}

void FindTagForm::SetTagID(const QString& tagStr)
{
	mTagEdit->setText(tagStr);
}
