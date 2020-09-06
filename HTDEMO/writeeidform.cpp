#include "writeeidform.h"
#include "ui_writeeidform.h"
#include "LanguageSrc.h"
#include "appconfig.h"
#include "mainapp.h"
#include "RFIDAPIEXPORT.h"
#include "readerdllbase.h"

WriteEidForm::WriteEidForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WriteEidForm)
{
    ui->setupUi(this);
	mOldEidEdit = ui->lineEdit;
	mWirteEidEdit = ui->lineEdit_2;
	mPwdEdit = ui->lineEdit_3;
	mSetBtn = ui->pushButton;

	mPwdEdit->setText(QString("00000000"));

	connect( mSetBtn, SIGNAL( clicked()), this, SLOT( slot_SetBtnClicked( ) ) );
}

WriteEidForm::~WriteEidForm()
{
    delete ui;
}

void WriteEidForm::slot_SetBtnClicked()
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

	if (mOldEidEdit->text().isEmpty())
	{
		return;
	}

	if (mWirteEidEdit->text().isEmpty())
	{
		return;
	}

	if (mPwdEdit->text().toUtf8().length() != 8)
	{
		return;
	}

	byte btPsw[8];
	ZeroMemory(btPsw,8);

	byte btBIDCode[8];
	ZeroMemory(btBIDCode,8);

	byte btEIDCode[8];
	ZeroMemory(btEIDCode,8);
	
	int iTagID = mOldEidEdit->text().toInt();
	btBIDCode[4] = (byte)((0xff000000&iTagID) >> 24 );
	btBIDCode[5] = (byte)((0xff0000&iTagID) >> 16 );
	btBIDCode[6] = (byte)((0xff00&iTagID) >> 8 );
	btBIDCode[7] = (byte)(0xff&iTagID);

	int nEid = mWirteEidEdit->text().toInt();
	btEIDCode[4]  = (byte)((0xff000000&nEid) >> 24 );
	btEIDCode[5] = (byte)((0xff0000&nEid) >> 16 );
	btEIDCode[6] = (byte)((0xff00&nEid) >> 8 );
	btEIDCode[7] = (byte)(0xff&nEid);
	
	QString pswStr = mPwdEdit->text();
	pMainApp->getBitBuffFromStr(pswStr,btPsw,8*8);

	unsigned char nType = 0x00;
	bool bRet = SAAT_YWriteEIDCode(pReaderDllBase->m_hCom, 
		nType,
		btBIDCode,
		btPsw, 
		btEIDCode);//nSize = 12
	if (bRet)
	{
		MainShowMsg(GET_TXT("IDCS_WRITE_EID_SUCCESS"));
	}
	else
	{
		MainShowMsg(GET_TXT("IDCS_WRITE_EID_FAILED"),true);
	}
}

void WriteEidForm::SetTagID(const QString& tagStr)
{
	mOldEidEdit->setText(tagStr);
}
