#include "filtratetagfor6cdlg.h"
#include "ui_filtratetagfor6cdlg.h"
#include "LanguageSrc.h"
#include "appconfig.h"
#include "mainapp.h"
#include "RFIDAPIEXPORT.h"
#include "readerdllbase.h"
FiltrateTagFor6CDlg::FiltrateTagFor6CDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FiltrateTagFor6CDlg)
{
    ui->setupUi(this);
	this->setWindowTitle(GET_TXT("IDCS_FILTER_TAG"));
	mEnableCb = ui->checkBox;
	mTimeEdit = ui->spinBox;
	mQueryBtn = ui->pushButton;
	mSetBtn = ui->pushButton_2;
	mTimeEdit->setMinimum(1);
	mTimeEdit->setMaximum(255);
	mTimeEdit->setValue(1);
	
	ui->label->setText(GET_TXT("IDCS_FILTER_TAG_TIME_LIMIT_1_255"));
	mEnableCb->setText(GET_TXT("IDCS_ENABLE"));
	mQueryBtn->setText(GET_TXT("IDCS_QUERY"));
	mSetBtn->setText(GET_TXT("IDCS_SET"));

	SetFiltrateEnable(false);

	mFirst = true;

	connect( mQueryBtn, SIGNAL( clicked()), this, SLOT( slot_QueryBtnClicked( ) ) );
	connect( mSetBtn, SIGNAL( clicked()), this, SLOT( slot_SetBtnClicked( ) ) );
	connect( mEnableCb, SIGNAL( stateChanged(int )), this, SLOT( slot_EnableStateChanged(int ) ) );
}

FiltrateTagFor6CDlg::~FiltrateTagFor6CDlg()
{
    delete ui;
}

void FiltrateTagFor6CDlg::slot_QueryBtnClicked()
{
	QueryValue();
}

void FiltrateTagFor6CDlg::slot_SetBtnClicked()
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

	int iInfoType = 0x03;	//配置类型
	byte btParam = mTimeEdit->value();//标签过滤时间

	bool bRet = SAAT_TagOpParaSet(pReaderDllBase->m_hCom,
		iInfoType,
		&btParam,
		1);


	if (bRet)
	{			
		MainShowMsg(GET_TXT("IDCS_FILTER_TIME_SUCCESS"));	
	}
	else
	{
		MainShowMsg(GET_TXT("IDCS_FILTER_TIME_FAILED"),true);
	}	
}

void FiltrateTagFor6CDlg::slot_EnableStateChanged(int state)
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

	int iInfoType = 0x02;//标签过滤使能
	unsigned char btParam = (state == Qt::Checked); //使能状态 1为使能，0为不使能

	bool retB = SAAT_TagOpParaSet(pReaderDllBase->m_hCom,
		iInfoType,
		&btParam,
		1);


	if (retB)
	{		
		SetFiltrateEnable(btParam);		
		MainShowMsg(GET_TXT("IDCS_FILTER_ENABLE_SUCCESS"));	
	}
	else
	{
		mEnableCb->setChecked(false);
		MainShowMsg(GET_TXT("IDCS_FILTER_ENABLE_FAILED"),true);
	}	
}

void FiltrateTagFor6CDlg::showEvent(QShowEvent *event)
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

void FiltrateTagFor6CDlg::SetFiltrateEnable(bool isEnable)
{
	mEnableCb->setChecked(isEnable);
	mTimeEdit->setEnabled(isEnable);
	mQueryBtn->setEnabled(isEnable);
	mSetBtn->setEnabled(isEnable);
}

bool FiltrateTagFor6CDlg::QueryEnable()
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

	unsigned char iInfoType = 0x02; //查询标签状态使能
	unsigned char btParam = 0; //查询出的值
	unsigned char nLen = 1;//查询的长度
	bool retB = SAAT_TagOpParaQuery(pReaderDllBase->m_hCom, 
		iInfoType,
		&btParam,
		&nLen);


	if (retB)
	{		
		
		SetFiltrateEnable(btParam == 1);		
		MainShowMsg(GET_TXT("IDCS_FILTER_ENABLE_QUERY_SUCCESS"));	
	}
	else
	{
		SetFiltrateEnable(false);
		MainShowMsg(GET_TXT("IDCS_FILTER_ENABLE_QUERY_FAILED"),true);
	}	

	return retB;
}

bool FiltrateTagFor6CDlg::QueryValue()
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

	unsigned char iInfoType = 0x03;//查询标签过滤使能
	unsigned char btParam = 0;//查询出的值存放
	unsigned char nLen = 1;//查询长度

	bool bRet = SAAT_TagOpParaQuery(pReaderDllBase->m_hCom, 
		iInfoType,
		&btParam,
		&nLen);


	if (bRet)
	{
		mTimeEdit->setValue(btParam);
		MainShowMsg(GET_TXT("IDCS_FILTER_TIME_QUERY_SUCCESS"));	
	}
	else
	{
		mTimeEdit->setValue(0);
		MainShowMsg(GET_TXT("IDCS_FILTER_TIME_QUERY_FAILED"),true);
	}	

	return bRet;
}	

bool FiltrateTagFor6CDlg::QueryAll()
{
	bool bRet = QueryEnable();
	if (bRet)
	{
		bRet = QueryValue();
	}

	return bRet;
}
