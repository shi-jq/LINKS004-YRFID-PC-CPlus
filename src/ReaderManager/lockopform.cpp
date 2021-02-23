#include "lockopform.h"
#include "ui_lockopform.h"
#include "LanguageSrc.h"
#include "appconfig.h"
#include "mainapp.h"
#include "RFIDAPIEXPORT.h"
#include "readerdllbase.h"

LockOpForm::LockOpForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LockOpForm)
{
    ui->setupUi(this);
	mIdTypeCb = ui->comboBox;
	mTagEdit = ui->lineEdit;
	mConfigPwdEdit = ui->lineEdit_2;
	mOpTypCb = ui->comboBox_2;
	mStartAddrEdit = ui->lineEdit_3;
	mLenEdit = ui->lineEdit_4;
	mSetBtn = ui->pushButton;
	mConfigPwdEdit->setText(QString("00000000"));
	mStartAddrEdit->setText(QString("0"));
	mLenEdit->setText(QString("1"));
	mIdTypeCb->addItem(QString("BID"));
	mOpTypCb->addItem(GET_TXT("IDCS_LOCK"));
	mOpTypCb->addItem(GET_TXT("IDCS_UNLOCK"));

	connect( mSetBtn, SIGNAL( clicked()), this, SLOT( slot_SetBtnClicked( ) ) );
}

LockOpForm::~LockOpForm()
{
    delete ui;
}

void LockOpForm::SetTagID(const QString& tagStr)
{
	mTagEdit->setText(tagStr);
}

void LockOpForm::slot_SetBtnClicked()
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
	if (mConfigPwdEdit->text().toUtf8().length() != 8)
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


	byte btIDCode[8];
	byte btCFGPsw[4];	
	ZeroMemory(btIDCode,8);
	ZeroMemory(btCFGPsw,4);
	
	int iTagID = mTagEdit->text().toInt();
	btIDCode[4] = (byte)((0xff000000&iTagID) >> 24 );
	btIDCode[5] = (byte)((0xff0000&iTagID) >> 16 );
	btIDCode[6] = (byte)((0xff00&iTagID) >> 8 );
	btIDCode[7] = (byte)(0xff&iTagID);

	pMainApp->getBitBuffFromStr(mConfigPwdEdit->text(),btCFGPsw,4*8);	

	unsigned char nType = 0x00;
	int nIDType = mIdTypeCb->currentIndex() + 1;
	int nOpType = mOpTypCb->currentIndex();
	switch (nOpType)
	{
	case 0:
		{
			nOpType = 0x00 ;//0x00
			break;
		}
	case 1:
		{
			nOpType = 0x01;//0x01  
			break;
		}
	default:
		{
			nOpType = 0x01;//0x01
			break;
		}
	}
	
	WORD dStartAddr=  nAddr;			
	bool bRet = SAAT_YTagOp( pReaderDllBase->m_hCom,
		nType, 
		nIDType,
		btIDCode,
		btCFGPsw, 
		nOpType,
		dStartAddr,
		nLen);

	if (bRet)
	{
		MainShowMsg(GET_TXT("IDCS_SET_SUCCESS"));
	}
	else
	{
		MainShowMsg(GET_TXT("IDCS_SET_FAILED"),true,true);
	}
}
