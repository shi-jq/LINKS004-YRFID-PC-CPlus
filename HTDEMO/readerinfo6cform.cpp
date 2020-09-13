#include "readerinfo6cform.h"
#include "ui_readerinfo6cform.h"
#include <QSettings>
#include "LanguageSrc.h"
#include "appconfig.h"
#include "mainapp.h"
#include "RFIDAPIEXPORT.h"
#include "readerdllbase.h"
#include "MessageBox.h"
#include "mainwindow.h"

ReaderInfo6CForm::ReaderInfo6CForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReaderInfo6CForm)
{
    ui->setupUi(this);
    this->setWindowTitle(GET_TXT("IDCS_READER_INFO"));

    mProductNameEdit = ui->lineEdit;
    mProductSerialEdit = ui->lineEdit_2;
    mRWerTypeEdit = ui->lineEdit_3;
    mProcessSoftVerEdit = ui->lineEdit_4;
    mBaseHardVerEdit = ui->lineEdit_6;
	mSerialPwdEdit = ui->lineEdit_8;

    mProcessSoftVerEdit->setReadOnly(true);
    mBaseHardVerEdit->setReadOnly(true);
  

    mQureyBtn = ui->pushButton_4;
    mProductNameSetBtn = ui->pushButton;
    mRWerTypeSetBtn = ui->pushButton_3;
    mProductSerialSetBtn = ui->pushButton_2;

    ui->label->setText(GET_TXT("IDCS_DEVICE_NAME"));
    ui->label_2->setText(GET_TXT("IDCS_DEVICE_SN"));
    ui->label_3->setText(GET_TXT("IDCS_DEVICE_TYPE"));
    ui->label_4->setText(GET_TXT("IDCS_CPU_SOFT_VER"));
    ui->label_6->setText(GET_TXT("IDCS_BASE_HARD_VER"));
    ui->pushButton->setText(GET_TXT("IDCS_SET"));
    ui->pushButton_2->setText(GET_TXT("IDCS_SET"));
    ui->pushButton_3->setText(GET_TXT("IDCS_SET"));
    ui->pushButton_4->setText(GET_TXT("IDCS_QUERY"));
	ui->label_8->setText(GET_TXT("IDCS_PWD"));

	mFirst = true;

    connect( mQureyBtn, SIGNAL( clicked()), this, SLOT( slot_QureyBtnClicked( ) ) );
    connect( mProductNameSetBtn, SIGNAL( clicked()), this, SLOT( slot_ProductNameSetBtnClicked( ) ) );
    connect( mRWerTypeSetBtn, SIGNAL( clicked()), this, SLOT( slot_RWerTypeSetBtnClicked( ) ) );
    connect( mProductSerialSetBtn, SIGNAL( clicked()), this, SLOT( slot_ProductSerialSetBtnClicked( ) ) );

}

ReaderInfo6CForm::~ReaderInfo6CForm()
{
    delete ui;
}


void ReaderInfo6CForm::slot_QureyBtnClicked()
{
	QueryAll();
}

void ReaderInfo6CForm::slot_ProductNameSetBtnClicked()
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

    QString inputStr = mProductNameEdit->text();
    int realLen = inputStr.toUtf8().length();
    if (inputStr.isEmpty())
    {
        MainShowMsg(GET_TXT("IDCS_INPUT_EMPTY"));
        return ;
    }
    if (realLen > 8)
    {
        MainShowMsg(GET_TXT("IDCS_INPUT_LIMIT_8"));
        return ;
    }
    unsigned char pPram[8] = {0};

    memcpy(pPram,inputStr.toUtf8().data(),realLen);
    unsigned char ntype = 0x00;
    bool bRet = SAAT_SysInfSet (pReaderDllBase->m_hCom,
        ntype,
        pPram,
        8);

    if (bRet)
    {
        MainShowMsg(GET_TXT("IDCS_READER_NAME_SET_SUCCESS"));
    }
    else
    {
        MainShowMsg(GET_TXT("IDCS_READER_NAME_SET_FAILED"),true);
    }

}

void ReaderInfo6CForm::slot_RWerTypeSetBtnClicked()
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

	if (mSerialPwdEdit->text().isEmpty())
	{
		MainShowMsg(GET_TXT("IDCS_RDER_TYPE_SET_NEED_PWD"));
		return ;
	}

	if (!mSerialPwdEdit->text().contains("szaat"))
	{
		MainShowMsg(GET_TXT("IDCS_PWD_ERRO"));
		return ;
	}

    QString inputStr = mRWerTypeEdit->text();
    int realLen = inputStr.toUtf8().length();
    if (inputStr.isEmpty())
    {
        MainShowMsg(GET_TXT("IDCS_INPUT_EMPTY"));
        return ;
    }
    if (realLen > 6)
    {
        MainShowMsg(GET_TXT("IDCS_INPUT_LIMIT_6"));
        return ;
    }
    unsigned char pPram[6] = {0};

    memcpy(pPram,inputStr.toUtf8().data(),realLen);
    unsigned char ntype = 0x01;
    bool bRet = SAAT_SysInfSet (pReaderDllBase->m_hCom,
        ntype,
        pPram,
        6);

    if (bRet)
    {
        MainShowMsg(GET_TXT("IDCS_READER_TYPE_SET_SUCCESS"));
    }
    else
    {
        MainShowMsg(GET_TXT("IDCS_READER_TYPE_SET_FAILED"),true);
    }
}

void ReaderInfo6CForm::slot_ProductSerialSetBtnClicked()
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

	if (mSerialPwdEdit->text().isEmpty())
	{
		MainShowMsg(GET_TXT("IDCS_SERIAL_SET_NEED_PWD"));
		return ;
	}

	if (!mSerialPwdEdit->text().compare("Admin@cirfid.com") == 0)
	{
		MainShowMsg(GET_TXT("IDCS_PWD_ERRO"));
		return ;
	}

    QString inputStr = mProductSerialEdit->text().trimmed();
    int realLen = inputStr.toUtf8().length();
    if (inputStr.isEmpty())
    {
        MainShowMsg(GET_TXT("IDCS_INPUT_EMPTY"));
        return ;
    }
    if (realLen > 8)
    {
        MainShowMsg(GET_TXT("IDCS_INPUT_LIMIT_8"));
        return ;
    }
    unsigned char pPram[8] = {0};

    memcpy(pPram,inputStr.toUtf8().data(),realLen);
    unsigned char ntype = 0x02;
    bool bRet = SAAT_SysInfSet (pReaderDllBase->m_hCom,
        ntype,
        pPram,
        8);

    if (bRet)
    {
        MainShowMsg(GET_TXT("IDCS_PRODUCT_SERIAL_SET_SUCCESS"));
    }
    else
    {
        MainShowMsg(GET_TXT("IDCS_PRODUCT_SERIAL_SET_FAILED"),true);
    }
}

bool ReaderInfo6CForm::QuerySysInfo(int index ,QString& str)
{
    ReaderDllBase*	pReaderDllBase = pMainApp->GetReader();
	if (!pReaderDllBase)
	{
		MainShowMsg(GET_TXT("IDCS_READ_NO_LINK"));
		return false;
	}
    if (!pReaderDllBase->CheckState(STATE_CONNET))
    {
        MainShowMsg(GET_TXT("IDCS_READ_NO_LINK"));
        return false;
    }
    bool bRet = false;
    unsigned char btParams[BYTE_BUFFER_SIZE];
    unsigned char size = BYTE_BUFFER_SIZE;
    ZeroMemory(btParams,BYTE_BUFFER_SIZE);

    bRet = SAAT_SysInfQuery(pReaderDllBase->m_hCom,
        index,
        btParams,
        &size);

    if (bRet)
    {
        str = QString::fromUtf8((char*)btParams,size);
    }

    return bRet;
}

void ReaderInfo6CForm::showEvent(QShowEvent *event)
{
	ReaderDllBase*	pReaderDllBase = pMainApp->GetReader();	
	if (!pReaderDllBase)
	{
		return;
	}

	if (pReaderDllBase->GetState() == STATE_READING ||
		pReaderDllBase->GetState() == STATE_DISCONNET ||
		pReaderDllBase->GetState() == STATE_DISABLE)
	{
		return;
	}


	if (mFirst)
	{
        //mFirst = !QueryAll();
	}
 
    QWidget::showEvent(event);
}

bool ReaderInfo6CForm::QueryAll()
{
	ReaderDllBase*	pReaderDllBase = pMainApp->GetReader();
	if (!pReaderDllBase)
	{
		MainShowMsg(GET_TXT("IDCS_READ_NO_LINK"));
		return false;
	}
	if (!pReaderDllBase->CheckState(STATE_CONNET))
	{
		MainShowMsg(GET_TXT("IDCS_READ_NO_LINK"));
		return false;
	}

	int index = 0;
	QString readStr;

	index=0;
	readStr.clear();
	if (QuerySysInfo(index,readStr))
	{
		mProductNameEdit->setText(readStr);
	}
	else
	{
		MainShowMsg(GET_TXT("IDCS_DEVICE_NAME_QUERY_FAILED"),true);
		return false;
	}


	index++;
	readStr.clear();
	if (QuerySysInfo(index,readStr))
	{
		mRWerTypeEdit->setText(readStr);
	}
	else
	{
		MainShowMsg(GET_TXT("IDCS_READER_TYPE_FAILED"),true);
		return false;
	}

	index++;
	readStr.clear();
	if (QuerySysInfo(index,readStr))
	{
		mProductSerialEdit->setText(readStr);
	}
	else
	{
		MainShowMsg(GET_TXT("IDCS_DEVICE_SN_QUERY_FAILED"),true);
		return false;
	}

	index++;
	readStr.clear();
	if (QuerySysInfo(index,readStr))
	{
		mProcessSoftVerEdit->setText(readStr);
	}
	else
	{
		MainShowMsg(GET_TXT("IDCS_PROCESS_SOFT_VER_FAILED"),true);
		return false;
	}

	index++;
	//readStr.clear();
	//if (QuerySysInfo(index,readStr))
	//{
	//	mFDSoftVerEdit->setText(readStr);
	//}
	//else
	//{
	//	MainShowMsg(GET_TXT("IDCS_FPGA_VER_FAILED"),true);
	//	return false;
	//}

	index++;
	readStr.clear();
	if (QuerySysInfo(index,readStr))
	{
		mBaseHardVerEdit->setText(readStr);
	}
	else
	{
		MainShowMsg(GET_TXT("IDCS_BASE_HARD_VER_FAILED"),true);
		return false;
	}

	/*index++;
	readStr.clear();
	if (QuerySysInfo(index,readStr))
	{
		mSPHardVerEdit->setText(readStr);
	}
	else
	{
		MainShowMsg(GET_TXT("IDCS_SP_HARD_VER_FAILED"),true);
		return false;
	}*/

	MainShowMsg(GET_TXT("IDCS_READER_INFO_SUCCESS"));
	return true;
}

