#include "paramadd6cdlg.h"
#include "ui_paramadd6cdlg.h"
#include "LanguageSrc.h"
#include "mainapp.h"
#include "RFIDAPIEXPORT.h"
#include "readerdllbase.h"

ParamAdd6CDlg::ParamAdd6CDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ParamAdd6CDlg)
{
    ui->setupUi(this);
	this->setWindowTitle(GET_TXT("IDCS_PARAM_READ_WRITE"));
	mReadParamBtn = ui->pushButton_2;
	mWriteParamBtn = ui->pushButton;
	mResetBtn = ui->pushButton_5;
	mStartAddrEdit = ui->lineEdit;
	mLenEdit = ui->lineEdit_2;
	mDataEdit = ui->lineEdit_3;
	
	mReadParamBtn->setText(GET_TXT("IDCS_READ"));
	mWriteParamBtn->setText(GET_TXT("IDCS_WRITE"));
	mResetBtn->setText(GET_TXT("IDCS_RESET"));
	ui->label->setText(GET_TXT("IDCS_START_ADDR"));
	ui->label_2->setText(GET_TXT("IDCS_LEN"));
	ui->label_3->setText(GET_TXT("IDCS_DATA"));


	connect( mReadParamBtn, SIGNAL( clicked()), this, SLOT( slot_ReadParamBtnClicked( ) ) );
	connect( mWriteParamBtn, SIGNAL( clicked()), this, SLOT( slot_WriteParamBtnClicked( ) ) );
	connect( mResetBtn, SIGNAL( clicked()), this, SLOT( slot_ResetBtnClicked( ) ) );

}

ParamAdd6CDlg::~ParamAdd6CDlg()
{
    delete ui;
}

void ParamAdd6CDlg::slot_ReadParamBtnClicked()
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

	if (mStartAddrEdit->text().isEmpty() || mLenEdit->text().isEmpty())
	{
		MainShowMsg(GET_TXT("IDCS_INPUT_EMPTY"));
		return ;
	}

	int nStartAddr = mStartAddrEdit->text().toInt();
	if (nStartAddr < 0 || nStartAddr > 255)
	{
		MainShowMsg(GET_TXT("IDCD_INPUT_LIMIT_1_2").arg(0).arg(255));
		return ;
	}

	int nLen = mLenEdit->text().toInt();
	if (nLen<0 || nLen>255)
	{
		MainShowMsg(GET_TXT("IDCD_INPUT_LIMIT_1_2").arg(0).arg(255));
		return ;
	}	
	
	unsigned char nType = 0x02;
	unsigned char btAddr = nStartAddr;
	unsigned char nDataLen = nLen;//����
	unsigned char btParams[256];
	ZeroMemory(btParams, 256);
	unsigned char nBufferLen = nDataLen;
	bool retB = SAAT_ParmOp (pReaderDllBase->m_hCom,
		nType, btAddr, nDataLen, btParams, &nBufferLen);

	if (retB)
	{		
		QString tempStr = "";
		for (int i=0 ; i<nDataLen; ++i)
		{
			tempStr +=QString("%1").arg(btParams[i],2,16,QLatin1Char('0')).toUpper();
		}
		mDataEdit->setText(tempStr);
		MainShowMsg(GET_TXT("IDCS_READ_DATA_SUCCESS"));
	}
	else
	{
		MainShowMsg(GET_TXT("IDCS_READ_DATA_FAILED"),true);
	}
}

void ParamAdd6CDlg::slot_WriteParamBtnClicked()
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

	if (mStartAddrEdit->text().isEmpty() || mLenEdit->text().isEmpty())
	{
		MainShowMsg(GET_TXT("IDCS_INPUT_EMPTY"));
		return ;
	}

	int nStartAddr = mStartAddrEdit->text().toInt();
	if (nStartAddr<0 || nStartAddr>255)
	{
		MainShowMsg(GET_TXT("IDCD_INPUT_LIMIT_1_2").arg(0).arg(255));
		return ;
	}

	int nLen = mLenEdit->text().toInt();
	if (nLen<0 || nLen>255)
	{
		MainShowMsg(GET_TXT("IDCD_INPUT_LIMIT_1_2").arg(0).arg(255));
		return ;
	}	

	QString strData = mDataEdit->text();
	if (nLen*2 != strData.length())
	{
		MainShowMsg(GET_TXT("IDCS_DATA_LEN_ERRO"));
		return;
	}

	unsigned char nType = 0x01;
	unsigned char btAddr = nStartAddr;
	unsigned char nDataLen = nLen;//����
	unsigned char btParams[256];
	ZeroMemory(btParams, 256);
	unsigned char nBufferLen = 
		pMainApp->getBitBuffFromStr(strData,btParams,nDataLen*8);

	bool retB = SAAT_ParmOp (
		pReaderDllBase->m_hCom,
		nType, btAddr, nDataLen, 
		btParams, &nBufferLen);

	if (retB)
	{			
		MainShowMsg(GET_TXT("IDCS_WRITE_SUCCESS"));	
	}
	else
	{
		MainShowMsg(GET_TXT("IDCS_WRITE_FAILED"),true);
	}
}

void ParamAdd6CDlg::slot_ResetBtnClicked()
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

	unsigned char nType = 0x00;
	unsigned char nStartAddrr = 0x00;
	unsigned char nLen = 0;
	unsigned char nData ;
	unsigned char nDataLen = 1;
	bool retB = SAAT_ParmOp (pReaderDllBase->m_hCom,
		nType,
		nStartAddrr, 
		nLen,  
		&nData,
		&nDataLen);

	if (retB)
	{			
		MainShowMsg(GET_TXT("IDCS_RESET_SUCCESS"));	
	}
	else
	{
		MainShowMsg(GET_TXT("IDCS_RESET_FAILED"),true);
	}
}
