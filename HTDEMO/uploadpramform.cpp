#include "uploadpramform.h"
#include "ui_uploadpramform.h"
#include "LanguageSrc.h"
#include "mainapp.h"
#include "readerdllbase.h"
#include "RFIDAPIEXPORT.h"

UploadPramForm::UploadPramForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UploadPramForm)
{
    ui->setupUi(this);
	m_DeviceTypeValueCb = ui->comboBox;
	m_CommandTypeValueCb = ui->comboBox_2;
	m_ConnetPortValueCb = ui->comboBox_4;
	mQueryBtn = ui->pushButton;
	mSetBtn = ui->pushButton_2;
	m_WorkModelCb = ui->comboBox_3;


	mQueryBtn->setText(GET_TXT("IDCS_QUERY"));
	mSetBtn->setText(GET_TXT("IDCS_SET"));
	ui->label_3->setText(GET_TXT("IDCS_WORK_MODEL_PARAM"));
	ui->label_4->setText(GET_TXT("IDCS_CONNET_PORT"));
	mFirst = true;

	QStringList sl;
	sl<<GET_TXT("IDCS_DEVICE_TYPE_PARAM_Y_0")		
		<<GET_TXT("IDCS_DEVICE_TYPE_PARAM_Y_1")
		<<GET_TXT("IDCS_DEVICE_TYPE_PARAM_Y_2");
	m_DeviceTypeValueCb->addItems(sl);

	sl.clear();
	sl<<GET_TXT("IDCS_WORK_MODEL_0")
		<<GET_TXT("IDCS_WORK_MODEL_1");
	m_WorkModelCb->addItems(sl);

	sl.clear();
	sl<<GET_TXT("IDCS_COMMAND_TYPE_PARAM_Y_0")
		<<GET_TXT("IDCS_COMMAND_TYPE_PARAM_Y_1");
	m_CommandTypeValueCb->addItems(sl);

	sl.clear();
	sl<<GET_TXT("IDCS_CONNET_PORT_PARAM_0")
		<<GET_TXT("IDCS_CONNET_PORT_PARAM_1")
		<<GET_TXT("IDCS_CONNET_PORT_PARAM_2")
		<<GET_TXT("IDCS_CONNET_PORT_PARAM_3")
		<<GET_TXT("IDCS_CONNET_PORT_PARAM_4")
		<<GET_TXT("IDCS_CONNET_PORT_PARAM_5");
	m_ConnetPortValueCb->addItems(sl);

	connect( mQueryBtn, SIGNAL( clicked()), this, SLOT( slot_QueryBtnClicked( ) ) );
	connect( mSetBtn, SIGNAL( clicked()), this, SLOT( slot_SetBtnClicked( ) ) );


	ui->label_2->hide();
	m_CommandTypeValueCb->hide();
	ui->label->hide();
	m_DeviceTypeValueCb->hide();
}	

UploadPramForm::~UploadPramForm()
{
    delete ui;
}

void UploadPramForm::slot_QueryBtnClicked()
{
	QueryAll();
}

void UploadPramForm::slot_SetBtnClicked()
{
	SetAll();
}

bool UploadPramForm::DeviceTypeQuery()
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
	unsigned char btAddr = 1;
	unsigned char nDataLen = 1;//长度
	unsigned char btParams[1];
	ZeroMemory(btParams, 1);
	unsigned char nBufferLen = 1;
	bool retB = SAAT_ParmOp (pReaderDllBase->m_hCom,
		nType, btAddr, nDataLen, btParams, &nBufferLen);

	if (retB)
	{		
		int index = -1;
		switch (btParams[0])
		{
		case 0x00:
			index=0;
			break;		
		case 0x10:
			index=1;
			break;		
		case 0x20:
			index=2;
			break;		
		default:
			break;
		}		
		m_DeviceTypeValueCb->setCurrentIndex(index);
		MainShowMsg(GET_TXT("IDCS_DEVICE_TYPE_SUCCESS"));
	}
	else
	{
		MainShowMsg(GET_TXT("IDCS_DEVICE_TYPE_FAILED"),true);
	}

	return retB;
}

bool UploadPramForm::CommandTypeQuery()
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
	unsigned char btAddr = 240;
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
		case 0x61:
			index=0;
			break;
		case 0x62:
			index=1;
			break;		
		default:
			index=-1;
			break;
		}		
		m_CommandTypeValueCb->setCurrentIndex(index);
		MainShowMsg(GET_TXT("IDCS_COMMAND_TYPE_QUERY_SUCCESS"));
	}
	else
	{
		MainShowMsg(GET_TXT("IDCS_COMMAND_TYPE_QUERY_FAILED"),true);
	}

	return retB;
}

bool UploadPramForm::ConnetPortQuery()
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
	unsigned char btAddr = 63;
	unsigned char nDataLen = 1;//长度
	unsigned char btParams[1];
	ZeroMemory(btParams, 1);
	unsigned char nBufferLen = 1;
	bool retB = SAAT_ParmOp (pReaderDllBase->m_hCom,
		nType, btAddr, nDataLen, btParams, &nBufferLen);

	if (retB)
	{			
		m_ConnetPortValueCb->setCurrentIndex(btParams[0]);
		MainShowMsg(GET_TXT("IDCS_CONNET_PORT_QUERY_SUCCESS"));
	}
	else
	{
		MainShowMsg(GET_TXT("IDCS_CONNET_PORT_QUERY_FAILED"),true);
	}

	return retB;
}

bool UploadPramForm::QueryAll()
{
	bool bRet = true;
	if (bRet)
	{
		bRet = WorkModelQuery();
	}


	/*if (bRet)
	{
		bRet = DeviceTypeQuery();
	}*/

	/*if (bRet)
	{
		bRet = CommandTypeQuery();
	}*/	

	if (bRet)
	{
		bRet = ConnetPortQuery();
	}

	return bRet;
}

bool UploadPramForm::DeviceTypeSet()
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
	unsigned char btAddr = 1;
	unsigned char nDataLen = 1;//长度
	unsigned char btParams[1];
	ZeroMemory(btParams, 1);
	switch (m_DeviceTypeValueCb->currentIndex())
	{
	case 0:
		btParams[0] = 0x00;
		break;
	case 1:
		btParams[0] = 0x10;
		break;
	case 2:
		btParams[0] = 0x20;
		break;	
	default:
		btParams[0] = 0x00;
		break;
	}
	unsigned char nBufferLen = 1;

	bool retB = SAAT_ParmOp (
		pReaderDllBase->m_hCom,
		nType, btAddr, nDataLen, 
		btParams, &nBufferLen);

	if (retB)
	{			
		MainShowMsg(GET_TXT("IDCS_DEVICE_TYPE_SUCCESS_SET"));	
	}
	else
	{
		MainShowMsg(GET_TXT("IDCS_DEVICE_TYPE_FAILED_SET"),true);
	}

	return retB;
}

bool UploadPramForm::CommandTypeSet()
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
	unsigned char btAddr = 63;
	unsigned char nDataLen = 1;//长度
	unsigned char btParams[1];
	ZeroMemory(btParams, 1);
	switch (m_CommandTypeValueCb->currentIndex())
	{
	case 0:
		btParams[0] = 0x61;
		break;
	case 1:
		btParams[0] = 0x62;
		break;	
	default:
		btParams[0] = 0x61;
		break;
	}
	unsigned char nBufferLen = 1;

	bool retB = SAAT_ParmOp (
		pReaderDllBase->m_hCom,
		nType, btAddr, nDataLen, 
		btParams, &nBufferLen);

	if (retB)
	{			
		MainShowMsg(GET_TXT("IDCS_COMMAND_TYPE_SET_SUCCESS"));	
	}
	else
	{
		MainShowMsg(GET_TXT("IDCS_COMMAND_TYPE_SET_FAILED"),true);
	}

	return retB;
}

bool UploadPramForm::ConnetPortSet()
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
	unsigned char btAddr = 63;
	unsigned char nDataLen = 1;//长度
	unsigned char btParams[1];
	ZeroMemory(btParams, 1);	
	btParams[0] = m_ConnetPortValueCb->currentIndex();	
	unsigned char nBufferLen = 1;

	bool retB = SAAT_ParmOp (
		pReaderDllBase->m_hCom,
		nType, btAddr, nDataLen, 
		btParams, &nBufferLen);

	if (retB)
	{			
		MainShowMsg(GET_TXT("IDCS_CONNET_PORT_SET_SUCCESS"));	
	}
	else
	{
		MainShowMsg(GET_TXT("IDCS_CONNET_PORT_SET_FAILED"),true);
	}

	return retB;
}

bool UploadPramForm::SetAll()
{
	bool bRet = true;
	if (bRet)
	{
		bRet = WorkModelSet();
	}

	/*if (bRet)
	{
		bRet = DeviceTypeSet();
	}*/

	/*if (bRet)
	{
		bRet = CommandTypeSet();
	}*/

	if (bRet)
	{
		bRet = ConnetPortSet();
	}

	return bRet;
}

void UploadPramForm::showEvent(QShowEvent *event)
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

bool UploadPramForm::WorkModelQuery()
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
	unsigned char btAddr = 56;
	unsigned char nDataLen = 1;//长度
	unsigned char btParams[1];
	ZeroMemory(btParams, 1);
	unsigned char nBufferLen = 1;
	bool retB = SAAT_ParmOp (pReaderDllBase->m_hCom,
		nType, btAddr, nDataLen, btParams, &nBufferLen);

	if (retB)
	{		
		int index = -1;
		switch (btParams[0])
		{
		case 0x00:
			index=0;
			break;		
		case 0x01:
			index=1;
			break;	
		default:
			break;
		}		
		m_WorkModelCb->setCurrentIndex(index);
		MainShowMsg(GET_TXT("IDCS_WORK_MODEL_QUERY_SUCCESS"));
	}
	else
	{
		MainShowMsg(GET_TXT("IDCS_WORK_MODEL_QUERY_FAILED"),true);
	}

	return retB;
}

bool UploadPramForm::WorkModelSet()
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
	unsigned char btAddr = 56;
	unsigned char nDataLen = 1;//长度
	unsigned char btParams[1];
	ZeroMemory(btParams, 1);
	switch (m_WorkModelCb->currentIndex())
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

	bool retB = SAAT_ParmOp (
		pReaderDllBase->m_hCom,
		nType, btAddr, nDataLen, 
		btParams, &nBufferLen);

	if (retB)
	{			
		MainShowMsg(GET_TXT("IDCS_WORK_MODEL_SET_SUCCESS"));	
	}
	else
	{
		MainShowMsg(GET_TXT("IDCS_WORK_MODEL_SET_FAILED"),true);
	}

	return retB;
}
