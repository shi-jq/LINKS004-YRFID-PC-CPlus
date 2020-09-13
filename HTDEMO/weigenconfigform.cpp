#include "weigenconfigform.h"
#include "ui_weigenconfigform.h"
#include "LanguageSrc.h"
#include "appconfig.h"
#include "mainapp.h"
#include "RFIDAPIEXPORT.h"
#include "readerdllbase.h"

WeiGenConfigForm::WeiGenConfigForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WeiGenConfigForm)
{
    ui->setupUi(this);

	m_WegenStartValueEdit = ui->lineEdit;
	m_WegenLenValueCb = ui->comboBox;
	mQueryBtn = ui->pushButton;
	mSetBtn = ui->pushButton_2;

	mQueryBtn->setText(GET_TXT("IDCS_QUERY"));
	mSetBtn->setText(GET_TXT("IDCS_SET"));
	ui->label_2->setText(GET_TXT("IDCS_WENGEN_START"));
	ui->label->setText(GET_TXT("IDCS_WEGEN_LEN"));

	mFirst = true;

	QStringList sl;
	sl<<GET_TXT("IDCS_WEGEN_LEN_PARAM_0")
		<<GET_TXT("IDCS_WEGEN_LEN_PARAM_1");
	m_WegenLenValueCb->addItems(sl);

	connect( mQueryBtn, SIGNAL( clicked()), this, SLOT( slot_QueryBtnClicked( ) ) );
	connect( mSetBtn, SIGNAL( clicked()), this, SLOT( slot_SetBtnClicked( ) ) );

}

WeiGenConfigForm::~WeiGenConfigForm()
{
    delete ui;
}

bool WeiGenConfigForm::WegenStartQuery()
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

	unsigned char nType = 0x02;
	unsigned char btAddr = 80;
	unsigned char nDataLen = 1;//长度
	unsigned char btParams[1];
	ZeroMemory(btParams, 1);
	unsigned char nBufferLen = 1;
	bool retB = SAAT_ParmOp (pReaderDllBase->m_hCom,
		nType, btAddr, nDataLen, btParams, &nBufferLen);

	if (retB)
	{	
		m_WegenStartValueEdit->setText(QString("%1").arg(btParams[0],2,16,QLatin1Char('0')).toUpper());
		MainShowMsg(GET_TXT("IDCS_WENGEN_START_QUERY_SUCCESS"));
	}
	else
	{
		MainShowMsg(GET_TXT("IDCS_WENGEN_START_QUERY_FAILED"),true);
	}

	return retB;
}

bool WeiGenConfigForm::WegenLenQuery()
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

	unsigned char nType = 0x02;
	unsigned char btAddr = 81;
	unsigned char nDataLen = 1;//长度
	unsigned char btParams[1];
	ZeroMemory(btParams, 1);
	unsigned char nBufferLen = 1;
	bool retB = SAAT_ParmOp (pReaderDllBase->m_hCom,
		nType, btAddr, nDataLen, btParams, &nBufferLen);

	if (retB)
	{		
		int index = 0;
		switch (btParams[0])
		{
		case 0x03:
			index=0;
			break;
		case 0x04:
			index=1;
			break;			
		default:
			break;
		}		
		m_WegenLenValueCb->setCurrentIndex(index);
		MainShowMsg(GET_TXT("IDCS_WENGEN_LEN_QUERY_SUCCESS"));
	}
	else
	{
		MainShowMsg(GET_TXT("IDCS_WENGEN_LEN_QUERY_FAILED"),true);
	}

	return retB;
}

bool WeiGenConfigForm::WegenStartSet()
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

	unsigned char nType = 0x01;
	unsigned char btAddr = 80;
	unsigned char nDataLen = 1;//长度
	unsigned char btParams[1];
	ZeroMemory(btParams, 1);	
	bool isOK;
	btParams[0] = m_WegenStartValueEdit->text().toUInt(&isOK,16);	
	unsigned char nBufferLen = 1;

	bool retB = SAAT_ParmOp (
		pReaderDllBase->m_hCom,
		nType, btAddr, nDataLen, 
		btParams, &nBufferLen);

	if (retB)
	{			
		MainShowMsg(GET_TXT("IDCS_WENGEN_START_SET_SUCCESS"));	
	}
	else
	{
		MainShowMsg(GET_TXT("IDCS_WENGEN_START_SET_FAILED"),true);
	}

	return retB;
}

bool WeiGenConfigForm::WegenLenSet()
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

	unsigned char nType = 0x01;
	unsigned char btAddr = 81;
	unsigned char nDataLen = 1;//长度
	unsigned char btParams[1];
	ZeroMemory(btParams, 1);
	switch (m_WegenLenValueCb->currentIndex())
	{
	case 0:
		btParams[0] = 0x03;
		break;
	case 1:
		btParams[0] = 0x04;
		break;	
	default:
		btParams[0] = 0x30;
		break;
	}
	unsigned char nBufferLen = 1;

	bool retB = SAAT_ParmOp (
		pReaderDllBase->m_hCom,
		nType, btAddr, nDataLen, 
		btParams, &nBufferLen);

	if (retB)
	{			
		MainShowMsg(GET_TXT("IDCS_WENGEN_LEN_SET_SUCCESS"));	
	}
	else
	{
		MainShowMsg(GET_TXT("IDCS_WENGEN_LEN_SET_FAILED"),true);
	}

	return retB;
}

void WeiGenConfigForm::slot_QueryBtnClicked()
{
	QueryAll();
}

void WeiGenConfigForm::slot_SetBtnClicked()
{
	SetAll();
}

bool WeiGenConfigForm::QueryAll()
{
	bool bRet = true;
	if (bRet)
	{
		bRet = WegenStartQuery();
	}

	if (bRet)
	{
		bRet = WegenLenQuery();
	}

	return bRet;
}

bool WeiGenConfigForm::SetAll()
{
	bool bRet = true;
	if (bRet)
	{
		bRet = WegenStartSet();
	}

	if (bRet)
	{
		bRet = WegenLenSet();
	}

	return bRet;
}

void WeiGenConfigForm::showEvent(QShowEvent *event)
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


