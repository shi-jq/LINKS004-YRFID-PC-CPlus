#include "buzzerconfigform.h"
#include "ui_buzzerconfigform.h"
#include "LanguageSrc.h"
#include "mainapp.h"
#include "readerdllbase.h"
#include "RFIDAPIEXPORT.h"

BuzzerConfigForm::BuzzerConfigForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BuzzerConfigForm)
{
    ui->setupUi(this);
	m_enableCb = ui->comboBox_1;
	mQueryBtn = ui->pushButton;
	mSetBtn = ui->pushButton_2;

	QStringList sl;
	sl << GET_TXT("IDCS_DISABLE")
		<< GET_TXT("IDCS_ENABLE");
	m_enableCb->addItems(sl);

	mQueryBtn->setText(GET_TXT("IDCS_QUERY"));
	mSetBtn->setText(GET_TXT("IDCS_SET"));
	ui->label_3->setText(GET_TXT("IDCS_READ_SOUND"));
	connect(mQueryBtn, SIGNAL(clicked()), this, SLOT(slot_QueryBtnClicked()));
	connect(mSetBtn, SIGNAL(clicked()), this, SLOT(slot_SetBtnClicked()));


}

BuzzerConfigForm::~BuzzerConfigForm()
{
    delete ui;
}

void BuzzerConfigForm::showEvent(QShowEvent *event)
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
	//if (mFirst)
	//{
		//mFirst = !QueryAll();
	//}
	QWidget::showEvent(event);
}

void BuzzerConfigForm::slot_QueryBtnClicked()
{
	EnableQuery();
}

void BuzzerConfigForm::slot_SetBtnClicked()
{
	EnableSet();
}

bool BuzzerConfigForm::EnableQuery()
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
	unsigned char btAddr = 241;
	unsigned char nDataLen = 1;//长度
	unsigned char btParams[1];
	ZeroMemory(btParams, 1);
	unsigned char nBufferLen = 1;
	bool retB = SAAT_ParmOp(pReaderDllBase->m_hCom,
		nType, btAddr, nDataLen, btParams, &nBufferLen);

	if (retB)
	{
		int index = -1;
		switch (btParams[0])
		{
		case 0x00:
			index = 0;
			break;
		case 0x01:
			index = 1;
			break;
		default:
			break;
		}
		m_enableCb->setCurrentIndex(index);
		MainShowMsg(GET_TXT("IDCS_SOUND_QUERY_SUCCESS"));
	}
	else
	{
		MainShowMsg(GET_TXT("IDCS_SOUND_QUERY_FAILED"), true);
	}

	return retB;
}

bool BuzzerConfigForm::EnableSet()
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
	unsigned char btAddr = 241;
	unsigned char nDataLen = 1;//长度
	unsigned char btParams[1];
	ZeroMemory(btParams, 1);
	switch (m_enableCb->currentIndex())
	{
	case 0:
		btParams[0] = 0x00;
		break;
	case 1:
		btParams[0] = 0x01;
		break;
	default:
		btParams[0] = 0x00;
		break;
	}
	unsigned char nBufferLen = 1;

	bool retB = SAAT_ParmOp(
		pReaderDllBase->m_hCom,
		nType, btAddr, nDataLen,
		btParams, &nBufferLen);

	if (retB)
	{
		MainShowMsg(GET_TXT("IDCS_SOUND_SET_SUCCESS"));
	}
	else
	{
		MainShowMsg(GET_TXT("IDCS_SOUND_SET_FAILED"), true);
	}

	return retB;
}
