#include "pwdsetform.h"
#include "ui_pwdsetform.h"
#include "LanguageSrc.h"
#include "appconfig.h"
#include "mainapp.h"
#include "RFIDAPIEXPORT.h"
#include "readerdllbase.h"
PwdSetForm::PwdSetForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PwdSetForm)
{
    ui->setupUi(this);
	mIdTypeCb = ui->comboBox;
	mTagIdEdit = ui->lineEdit;
	mAccessPwdRbt = ui->radioButton;
	mConfigPwdRbt = ui->radioButton_2;
	mOldPwdEdit = ui->lineEdit_2;
	mNewPwdEdit = ui->lineEdit_3;
	mSetBtn = ui->pushButton;
	mIdTypeCb->addItem(QString("BID"));
	mOldPwdEdit->setText(QString("00000000"));
	mNewPwdEdit->setText(QString("00000000"));
	mAccessPwdRbt->setChecked(true);
	connect( mSetBtn, SIGNAL( clicked()), this, SLOT( slot_setBtnClicked( ) ) );

}

PwdSetForm::~PwdSetForm()
{
    delete ui;

}

void PwdSetForm::slot_setBtnClicked()
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

	if (mTagIdEdit->text().isEmpty())
	{
		return;
	}

	if (mOldPwdEdit->text().toUtf8().length()!=8)
	{
		return;
	}

	if (mNewPwdEdit->text().toUtf8().length()!=8)
	{
		return;
	}


	byte btIDCode[8];
	byte btOldPsw[8];
	byte btNewPsw[8];
	ZeroMemory(btOldPsw,8);
	ZeroMemory(btNewPsw,8);
	ZeroMemory(btIDCode,8);
	
	int iTagID = mTagIdEdit->text().toInt();
	btIDCode[4] = (byte)((0xff000000&iTagID) >> 24 );
	btIDCode[5] = (byte)((0xff0000&iTagID) >> 16 );
	btIDCode[6] = (byte)((0xff00&iTagID) >> 8 );
	btIDCode[7] = (byte)(0xff&iTagID);
	
	pMainApp->getBitBuffFromStr(mOldPwdEdit->text(),btOldPsw,8*8);

	pMainApp->getBitBuffFromStr(mNewPwdEdit->text(),btNewPsw,8*8);

	bool bRet = false;
	unsigned char nType = 0x00;
	int nIDType = mIdTypeCb->currentIndex() + 1;
	if (mAccessPwdRbt->isChecked())
	{
		bRet = SAAT_YAccessPWDSet (
			pReaderDllBase->m_hCom,
			nType, 
			nIDType,
			btIDCode,
			btOldPsw, 
			btNewPsw);		
	}
	else if (mConfigPwdRbt->isChecked())
	{

		bRet = SAAT_YCFGPWDSet(
			pReaderDllBase->m_hCom,
			nType, 
			nIDType,
			btIDCode,
			btOldPsw, 
			btNewPsw);	
	}

	if (bRet)
	{
		MainShowMsg(GET_TXT("IDCS_SET_SUCCESS"));
	}
	else
	{
		MainShowMsg(GET_TXT("IDCS_SET_FAILED"),true,true);
	}

}

void PwdSetForm::SetTagID(const QString& tagStr)
{
	mTagIdEdit->setText(tagStr);
}
