#include "flashconfigfor6cdlg.h"
#include "ui_flashconfigfor6cdlg.h"
#include <QFileDialog>
#include "LanguageSrc.h"
#include "appconfig.h"
#include "mainapp.h"
#include "RFIDAPIEXPORT.h"
#include "readerdllbase.h"

FlashConfigFor6CDlg::FlashConfigFor6CDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FlashConfigFor6CDlg)
{
    ui->setupUi(this);
	setWindowTitle(GET_TXT("IDCS_FLASH"));
	mFlashEnableCb = ui->checkBox;
	mAllTagNumEdit = ui->lineEdit;
	mQueryBtn = ui->pushButton;
	mClearBtn = ui->pushButton_2;
	mAllTagNumEdit->setReadOnly(true);

	ui->label->setText(GET_TXT("IDCS_TAG_COUNT"));
	mFlashEnableCb->setText(GET_TXT("IDCS_ENABLE"));
	mQueryBtn->setText(GET_TXT("IDCS_QUERY"));
	mClearBtn->setText(GET_TXT("IDCS_CLEAR"));

	setFlashEnable(false);

	mFirst = true;

	connect( mQueryBtn, SIGNAL( clicked()), this, SLOT( slot_QueryBtnClicked( ) ) );
	connect( mClearBtn, SIGNAL( clicked()), this, SLOT( slot_ClearBtnClicked( ) ) );
	connect( mFlashEnableCb, SIGNAL( stateChanged(int )), this, SLOT( slot_EnableStateChanged(int ) ) );
}

FlashConfigFor6CDlg::~FlashConfigFor6CDlg()
{
    delete ui;
}

void FlashConfigFor6CDlg::slot_QueryBtnClicked()
{
	QueryTagNum();
}

void FlashConfigFor6CDlg::slot_ClearBtnClicked()
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

	bool retB = SAAT_ClearFlash(pReaderDllBase->m_hCom) ;

	if (retB)
	{
		mAllTagNumEdit->setText(QString("0"));
		MainShowMsg(GET_TXT("IDCS_FLASH_CLEAR_SUCCESS"));
	}
	else
	{

		MainShowMsg(GET_TXT("IDCS_FLASH_CLEAR_FAILED"),true);
	}
	
}


void FlashConfigFor6CDlg::showEvent(QShowEvent *event)
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
		mFirst = !QueryAll();
	}
	QWidget::showEvent(event);
}

bool FlashConfigFor6CDlg::QueryFlashEnable()
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
	//查询Flash的使能状态
	unsigned char nType = 0x02;
	unsigned char btAddr = 249;//参数表249，1代表启用flash，0代表禁用flash
	unsigned char nDataLen = 1;//长度
	unsigned char btParams[1];
	ZeroMemory(btParams, 1);
	unsigned char nBufferLen = 1;
	bool retB = SAAT_ParmOp (pReaderDllBase->m_hCom,
		nType, btAddr, nDataLen, btParams, &nBufferLen);

	if (retB)
	{
		if (1 == btParams[0])
		{
			setFlashEnable(true);
		}
		else
		{
			setFlashEnable(false);
		}
		MainShowMsg(GET_TXT("IDCS_FLASH_ENABLE_QUERY_SUCCESS"));
	}
	else
	{
		setFlashEnable(false);
		MainShowMsg(GET_TXT("IDCS_FLASH_ENABLE_QUERY_FAILED"),true);
	}

	return retB;
}

bool FlashConfigFor6CDlg::QueryTagNum()
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
	
	unsigned char btPara[7] ;
	ZeroMemory(btPara,7);
	unsigned char nLen = 7;
	int nCount = -1 ;

	bool retB = SAAT_FlashTotalCountQuery(
		pReaderDllBase->m_hCom,
		btPara,&nLen);

	if (retB)
	{
		nCount =   
			(btPara[0] << 24) + 
			(btPara[1] << 16) + 
			(btPara[2] << 8) + 
			btPara[3];

		if (-1 == nCount)
		{
			nCount = 0;
		}
		mAllTagNumEdit->setText(QString("%1").arg(nCount));
		MainShowMsg(GET_TXT("IDCS_FLASH_TAG_COUNT_QUERY_SUCCESS"));
	}
	else
	{
	
		MainShowMsg(GET_TXT("IDCS_FLASH_TAG_COUNT_QUERY_FAILED"),true);
	}

	return retB;
}

void FlashConfigFor6CDlg::setFlashEnable(bool isEnable)
{	
	mFlashEnableCb->setChecked(isEnable);
	mAllTagNumEdit->setEnabled(isEnable);
	mQueryBtn->setEnabled(isEnable);
	mClearBtn->setEnabled(isEnable);
}

void FlashConfigFor6CDlg::slot_EnableStateChanged(int state)
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

	unsigned char nType = 0x01;
	unsigned char btAddr = 249;//参数表249，1代表启用flash，0代表禁用flash
	unsigned char nDataLen = 1;//长度
	unsigned char btParams[1];
	ZeroMemory(btParams, 1);
	bool isEnable = (state == Qt::Checked);
	btParams[0] = isEnable;
	unsigned char nBufferLen = 1;

	bool retB = SAAT_ParmOp (
		pReaderDllBase->m_hCom,
		nType, btAddr, nDataLen, 
		btParams, &nBufferLen);

	if (retB)
	{		
		setFlashEnable(isEnable);		
		MainShowMsg(GET_TXT("IDCS_FLASH_ENABLE_SET_SUCCESS"));	
	}
	else
	{
		mFlashEnableCb->setChecked(false);
		MainShowMsg(GET_TXT("IDCS_FLASH_ENABLE_SET_FAILED"),true);
	}	
}

bool FlashConfigFor6CDlg::QueryAll()
{
	if (QueryFlashEnable())
	{
		return QueryTagNum();
	}
	return false;
}


