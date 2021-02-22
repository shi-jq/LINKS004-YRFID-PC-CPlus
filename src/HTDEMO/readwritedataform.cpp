#include "readwritedataform.h"
#include "ui_readwritedataform.h"
#include "LanguageSrc.h"
#include "appconfig.h"
#include "mainapp.h"
#include "RFIDAPIEXPORT.h"
#include "readerdllbase.h"

ReadWriteDataForm::ReadWriteDataForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReadWriteDataForm)
{
    ui->setupUi(this);
	mIdTypeCb = ui->comboBox;
	mTagEdit = ui->lineEdit_2;
	mPwdEdit = ui->lineEdit;
	mBankCb = ui->comboBox_2;
	mStartAddrEdit = ui->lineEdit_4;
	mLenEdit = ui->lineEdit_5;
	mResultEdit = ui->textEdit;
	mReadBtn = ui->pushButton;
	mWriteBtn = ui->pushButton_2;
	mUseTimeLabel = ui->label_9;
	mWaitTimeEdit = ui->lineEdit_3;
	mClearBtn = ui->pushButton_3;
	mPwdEdit->setText(QString("00000000"));
	mStartAddrEdit->setText(QString("0"));
	mLenEdit->setText(QString("4"));
	mWaitTimeEdit->setText(QString("3000"));

	mIdTypeCb->addItem(QString("BID"));
	for(int i=0; i<8; ++i)
	{
		mBankCb->addItem(QString("%1").arg(i));
	}

	connect( mReadBtn, SIGNAL( clicked()), this, SLOT( slot_ReadBtnClicked( ) ) );
	connect( mWriteBtn, SIGNAL( clicked()), this, SLOT( slot_WriteBtnClicked( ) ) );
	connect( mClearBtn, SIGNAL( clicked()), this, SLOT( slot_ClearBtnClicked( ) ) );

}		

ReadWriteDataForm::~ReadWriteDataForm()
{
    delete ui;
}

void ReadWriteDataForm::slot_ReadBtnClicked()
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
		return;
	}

	if (mPwdEdit->text().toUtf8().length() != 8)
	{
		return;
	}

	if (mStartAddrEdit->text().isEmpty())
	{
		return;
	}

	if (mLenEdit->text().isEmpty())
	{
		return;
	}

	int nAddr = mStartAddrEdit->text().toInt();
	int nLen = mLenEdit->text().toInt();
	if( nAddr + nLen > 64)
	{
		return;
	}

	BYTE btTagID[8];
	BYTE btPwd[8];
	BYTE btData[BYTE_BUFFER_SIZE];
	ZeroMemory(btTagID,8);
	ZeroMemory(btPwd,8);
	ZeroMemory(btData,BYTE_BUFFER_SIZE);

	
	int iTagID = mTagEdit->text().toInt();
	btTagID[4] = (BYTE)((0xff000000&iTagID) >> 24 );
	btTagID[5] = (BYTE)((0xff0000&iTagID) >> 16 );
	btTagID[6] = (BYTE)((0xff00&iTagID) >> 8 );
	btTagID[7] = (BYTE)(0xff&iTagID);

	pMainApp->getBitBuffFromStr(mPwdEdit->text(),btPwd,4*8);	

	unsigned char nBank = mBankCb->currentIndex();
	unsigned char nStartAddr = (unsigned char)nAddr;
	int nIDType = mIdTypeCb->currentIndex() + 1;
	unsigned char nType = 0x00;

	int nWaitTime = mWaitTimeEdit->text().toInt();
	if (nWaitTime <= 0)
	{
		nWaitTime+=3000;
	}


	DWORD dwStart = GetTickCount();
	bool bRet = SAAT_YReadUserData(pReaderDllBase->m_hCom,
		nType,
		nIDType,
		btTagID,
		btPwd,
		nBank,
		nStartAddr,
		btData,
		&nLen
		,nWaitTime);
	if (!bRet)
	{
		MainShowMsg(GET_TXT("IDCS_READ_DATA_FAILED"),true,true);
		return;
	}


	DWORD dwStop = GetTickCount();
	DWORD TimeUsed = dwStop-dwStart;
	QString useTimeStr = GET_TXT("IDCS_USE_TIME_1").arg(TimeUsed);
	mUseTimeLabel->setText(useTimeStr);

	QString ResultStr = pMainApp->GetStrFromChar(btData,nLen);
	mResultEdit->setText(ResultStr);
	MainShowMsg(GET_TXT("IDCS_READ_DATA_SUCCESS"));
}

void ReadWriteDataForm::slot_WriteBtnClicked()
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
		return;
	}

	if (mPwdEdit->text().toUtf8().length() != 8)
	{
		return;
	}

	if (mStartAddrEdit->text().isEmpty())
	{
		return;
	}

	if (mLenEdit->text().isEmpty())
	{
		return;
	}

	int nAddr = mStartAddrEdit->text().toInt();
	int nLen = mLenEdit->text().toInt();
	if( nAddr + nLen > 64)
	{
		return;
	}

	BYTE btTagID[8];
	BYTE btPwd[8];
	BYTE btData[BYTE_BUFFER_SIZE];
	ZeroMemory(btTagID,8);
	ZeroMemory(btPwd,8);
	ZeroMemory(btData,BYTE_BUFFER_SIZE);


	int iTagID = mTagEdit->text().toInt();
	btTagID[4] = (BYTE)((0xff000000&iTagID) >> 24 );
	btTagID[5] = (BYTE)((0xff0000&iTagID) >> 16 );
	btTagID[6] = (BYTE)((0xff00&iTagID) >> 8 );
	btTagID[7] = (BYTE)(0xff&iTagID);

	pMainApp->getBitBuffFromStr(mPwdEdit->text(),btPwd,8*8);	

	unsigned char nBank = mBankCb->currentIndex();
	unsigned char nStartAddr = (unsigned char)nAddr;
	int nIDType = mIdTypeCb->currentIndex() + 1;
	unsigned char nType = 0x00;

	int nWaitTime = mWaitTimeEdit->text().toInt();
	if (nWaitTime <= 0)
	{
		nWaitTime+=3000;
	}
	QString ResultStr = mResultEdit->toPlainText();
	pMainApp->getBitBuffFromStr(ResultStr,btData,ResultStr.toUtf8().length()*4);	

	DWORD dwStart = GetTickCount();
	bool bRet = SAAT_YWriteUserData(pReaderDllBase->m_hCom,
		nType,
		nIDType,
		btTagID,
		btPwd,
		nBank,
		nStartAddr,
		btData,
		nLen
		,nWaitTime);
	if (!bRet)
	{
		MainShowMsg(GET_TXT("IDCS_WRITE_DATA_FAILED"),true,true);
		return;
	}


	DWORD dwStop = GetTickCount();
	DWORD TimeUsed = dwStop-dwStart;
	QString useTimeStr = GET_TXT("IDCS_USE_TIME_1").arg(TimeUsed);
	mUseTimeLabel->setText(useTimeStr);
	MainShowMsg(GET_TXT("IDCS_WRITE_DATA_SUCCESS"));
}

void ReadWriteDataForm::SetTagID(const QString& tagStr)
{
	mTagEdit->setText(tagStr);
}

void ReadWriteDataForm::slot_ClearBtnClicked()
{
	mResultEdit->clear();
}
