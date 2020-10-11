#include "wirelessreadparamwidget.h"
#include "ui_wirelessreadparamwidget.h"
#include "wirelessdeviceinfodlg.h"
#include "WirelessRecvCtrl.h"
#include "WIRELESSRFIDAPIEXPORT.h"
#include "LanguageSrc.h"
#include "mainapp.h"

WirelessReadParamWidget::WirelessReadParamWidget(WirelessDeviceInfoDlg* ctrlDlg,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::wirelessreadparamwidget)
{
    ui->setupUi(this);
	this->setWindowTitle(GET_TXT("IDCS_READER_CONFIG"));
	mCtrlDlg = ctrlDlg;
	
	mFlashEnableBtn = ui->pushButton_6;
	mFlashTagCountBtn = ui->pushButton_11;
	mFlashTagClearBtn = ui->pushButton_12;
	mFilterEnableBtn = ui->pushButton_14;
	mFilterTimeBtn = ui->pushButton_13;
	mFlashEnableCb = ui->checkBox_5;
	mTagCountLb = ui->label_44;
	mFilterEnableCb = ui->checkBox_6;
	mFilterTimeEdit = ui->lineEdit;
	mFilterQueryBtn = ui->pushButton_2;
	mFlashEnableQueryBtn = ui->pushButton;
	mQueryFilterTimeBtn = ui->pushButton_7;

	mFlashTagClearBtn->setEnabled(false);
	mFlashTagCountBtn->setEnabled(false);

	ui->label_36->setText(GET_TXT("IDCS_FLASH"));
	ui->label_39->setText(GET_TXT("IDCS_FLASH"));
	ui->label_40->setText(GET_TXT("IDCS_TAG_COUNT"));
	ui->label_41->setText(GET_TXT("IDCS_FILTER_TAG"));
	ui->label_42->setText(GET_TXT("IDCS_FILTER_TAG_TIME_LIMIT_1_255"));
	ui->checkBox_5->setText(GET_TXT("IDCS_ENABLE"));
	ui->checkBox_6->setText(GET_TXT("IDCS_ENABLE"));
	ui->pushButton->setText(GET_TXT("IDCS_QUERY"));
	ui->pushButton_2->setText(GET_TXT("IDCS_QUERY"));
	ui->pushButton_11->setText(GET_TXT("IDCS_QUERY"));
	ui->pushButton_6->setText(GET_TXT("IDCS_SET"));
	ui->pushButton_14->setText(GET_TXT("IDCS_SET"));
	ui->pushButton_13->setText(GET_TXT("IDCS_SET"));
	ui->pushButton_12->setText(GET_TXT("IDCS_CLEAR"));
	ui->label_37->setText(GET_TXT("IDCS_FILTER_TAG"));	

	connect( mFlashEnableBtn, SIGNAL( clicked()), this, SLOT( slot_FlashEnableBtnClicked( ) ) );
	connect( mFlashTagCountBtn, SIGNAL( clicked()), this, SLOT( slot_FlashTagCountBtnClicked( ) ) );
	connect( mFlashTagClearBtn, SIGNAL( clicked()), this, SLOT( slot_FlashTagClearBtnClicked( ) ) );
	connect( mFilterEnableBtn, SIGNAL( clicked()), this, SLOT( slot_FilterEnableBtnClicked( ) ) );
	connect( mFilterTimeBtn, SIGNAL( clicked()), this, SLOT( slot_FilterTimeBtnClicked( ) ) );
	connect( mFilterQueryBtn, SIGNAL( clicked()), this, SLOT( slot_QueryFilter( ) ) );
	connect( mFlashEnableQueryBtn, SIGNAL( clicked()), this, SLOT( slot_QueryFlashEnable( ) ) );
	connect( mQueryFilterTimeBtn, SIGNAL( clicked()), this, SLOT( slot_QueryFilterTimeBtnClicked( ) ) );
	mMsgID = 0;
}

WirelessReadParamWidget::~WirelessReadParamWidget()
{
    delete ui;
}

void WirelessReadParamWidget::slot_FlashEnableBtnClicked()
{
	WirelessReaderInfo* pWirelessReaderInfo = mCtrlDlg->GetReaderInfo();
	if(!pWirelessReaderInfo)
	{
		return;
	}

	unsigned char nType = 0x01;
	unsigned char btAddr = 249;//参数表249，1代表启用flash，0代表禁用flash
	unsigned char nDataLen = 1;//长度
	unsigned char btParams[1];
	ZeroMemory(btParams, 1);
	btParams[0] = mFlashEnableCb->isChecked();
	unsigned char nBufferLen = 1;

	bool retB = WIRELESS_SAAT_ParmOp (
		WIRELESSRECV_HANDLE,
		pWirelessReaderInfo,
		nType, btAddr, nDataLen, btParams, &nBufferLen,&mMsgID);
		
	
	if (retB)
	{	
		mOperType = OP_FLASH_ENABLE;
	}
	else
	{
		MainShowMsg(GET_TXT("IDCS_FLASH_ENABLE_FAILED"));	
	}	

}

void WirelessReadParamWidget::slot_FlashTagCountBtnClicked()
{
	
	WirelessReaderInfo* pWirelessReaderInfo = mCtrlDlg->GetReaderInfo();
	if(!pWirelessReaderInfo)
	{
		return;
	}

	bool retB = WIRELESS_SAAT_FlashTotalCountQuery(
		WIRELESSRECV_HANDLE,
		pWirelessReaderInfo);
	if(retB)
	{
		mOperType = OP_FLASH_COUNT;
	}
	else
	{
		MainShowMsg(GET_TXT("IDCS_FLASH_TAG_COUNT_FAILED"));
		mTagCountLb->setText(QString("%1").arg(0));
	}
	
}

void WirelessReadParamWidget::slot_FlashTagClearBtnClicked()
{
	WirelessReaderInfo* pWirelessReaderInfo = mCtrlDlg->GetReaderInfo();
	if(!pWirelessReaderInfo)
	{
		return;
	}
	
	bool retB = WIRELESS_SAAT_ClearFlash(
		WIRELESSRECV_HANDLE,
		pWirelessReaderInfo);

	if(retB)
	{
		mOperType = OP_FLASH_CLEAR;
	}
	else
	{
		MainShowMsg(GET_TXT("IDCS_FLASH_CLEAR_FAILED"));
	}
}

void WirelessReadParamWidget::slot_FilterEnableBtnClicked()
{
	WirelessReaderInfo* pWirelessReaderInfo = mCtrlDlg->GetReaderInfo();
	if(!pWirelessReaderInfo)
	{
		return;
	}

	int iInfoType = 0x02;
	byte btParam = 0x00;
	if (mFilterEnableCb->isChecked())
	{
		btParam = 0x01;
	}
	else
	{
		btParam = 0x00;
	}

	bool retB = WIRELESS_SAAT_TagOpParaSet(	
		WIRELESSRECV_HANDLE,
		pWirelessReaderInfo,
		iInfoType,
		&btParam,
		1);
	if (retB)
	{
		mOperType = OP_FLITER_ENABLE;		
	}
	else
	{
		MainShowMsg(GET_TXT("IDCS_FILTER_ENABLE_FAILED"));
	}
}

void WirelessReadParamWidget::slot_FilterTimeBtnClicked()
{
	WirelessReaderInfo* pWirelessReaderInfo = mCtrlDlg->GetReaderInfo();
	if(!pWirelessReaderInfo)
	{
		return;
	}
	int iInfoType = 0x03;
	byte btParam = mFilterTimeEdit->text().toInt();	

	bool bRet = WIRELESS_SAAT_TagOpParaSet(
		WIRELESSRECV_HANDLE,
		pWirelessReaderInfo,
		iInfoType,
		&btParam,
		1);
	if (bRet)
	{
		mOperType = OP_FILTER_TIME;		
	}
	else
	{
		MainShowMsg(GET_TXT("IDCS_FILTER_TIME_FAILED"));
	}
}

void WirelessReadParamWidget::slot_QueryFlashEnable()
{
	WirelessReaderInfo* pWirelessReaderInfo = mCtrlDlg->GetReaderInfo();
	if(!pWirelessReaderInfo)
	{
		return;
	}
	//查询Flash的使能状态
	unsigned char nType = 0x02;
	unsigned char btAddr = 249;//参数表249，1代表启用flash，0代表禁用flash
	unsigned char nDataLen = 1;//长度
	unsigned char btParams[1];
	ZeroMemory(btParams, 1);
	unsigned char nBufferLen = 1;
	bool retB = WIRELESS_SAAT_ParmOp (
		WIRELESSRECV_HANDLE,
		pWirelessReaderInfo,
		nType, btAddr, nDataLen, btParams, &nBufferLen,&mMsgID);
	if (retB)
	{
		mOperType = OP_QUERY_FLASH_ENABLE;
	}
	else
	{
		MainShowMsg(GET_TXT("IDCS_FLASH_ENABLE_QUERY_FAILED"));	
		mFlashTagClearBtn->setEnabled(false);
		mFlashTagCountBtn->setEnabled(false);
	}
}

void WirelessReadParamWidget::slot_QueryFilter()
{
	WirelessReaderInfo* pWirelessReaderInfo = mCtrlDlg->GetReaderInfo();
	if(!pWirelessReaderInfo)
	{
		return;
	}

	int iInfoType = 0x02;
	bool bRet = WIRELESS_SAAT_TagOpParaQuery(
		WIRELESSRECV_HANDLE,
		pWirelessReaderInfo,
		iInfoType);
	if (bRet)
	{
		mOperType = OP_QUERY_FLITER_ENABLE;
	}
	else
	{
		MainShowMsg(GET_TXT("IDCS_FILTER_ENABLE_QUERY_FAILED"));		
	}
}


void WirelessReadParamWidget::SetRevMsg(int msgID,unsigned char bCommand,unsigned char* pData, int nLen)
{	
	if (bCommand == READER_FLASHDATA_QUERY)
	{
		return;
	}

	if (bCommand == READER_FLASHDATACOUNT_QUERY)
	{
		MainShowMsg(GET_TXT("IDCS_FLASH_TAG_COUNT_SUCCESS"));
		int	nCount = (  (pData[1] << 24) + 
			(pData[2] << 16) + 
			(pData[3] << 8) + 
			pData[4] );
		mTagCountLb->setText(QString("%1").arg(nCount));
		return;
	}

	if (bCommand == READER_FLASHCLEAR)
	{
		MainShowMsg(GET_TXT("IDCS_FLASH_CLEAR_SUCCESS"));	
		mTagCountLb->setText(QString("%1").arg(0));
		return;
	}

	if (bCommand == COM_TAG_SET)
	{
		if (mOperType == OP_FLITER_ENABLE)
		{
			MainShowMsg(GET_TXT("IDCS_FILTER_ENABLE_SUCCESS"));	
			if (mFilterEnableCb->isChecked())
			{
				mFilterTimeEdit->setEnabled(true);				
				mQueryFilterTimeBtn->setEnabled(true);
				mFilterTimeBtn->setEnabled(true);
			}
			else
			{
				mFilterTimeEdit->setEnabled(false);
				mQueryFilterTimeBtn->setEnabled(false);
				mFilterTimeBtn->setEnabled(false);
			}			
			
		}
		else if (mOperType == OP_FILTER_TIME)
		{
			MainShowMsg(GET_TXT("IDCS_FILTER_TIME_SUCCESS"));	
		}
	
		return;
	}

	if (bCommand == COM_TAG_QUERY)
	{		
		if (mOperType == OP_QUERYFILTER_TIME)
		{
			MainShowMsg(GET_TXT("IDCS_FILTER_TIME_QUERY_SUCCESS"));		
			mFilterTimeEdit->setText(QString("%1").arg(pData[1]));
		}	

		if (mOperType == OP_QUERY_FLITER_ENABLE)
		{
			MainShowMsg(GET_TXT("IDCS_FILTER_ENABLE_QUERY_SUCCESS"));	

			if (1 == pData[1])
			{
				mFilterTimeEdit->setEnabled(true);				
				mQueryFilterTimeBtn->setEnabled(true);
				mFilterTimeBtn->setEnabled(true);
				mFilterEnableCb->setChecked(true);
			}
			else
			{
				mFilterTimeEdit->setEnabled(false);
				mQueryFilterTimeBtn->setEnabled(false);
				mFilterTimeBtn->setEnabled(false);
				mFilterEnableCb->setChecked(false);
			}
		}

		return;
	}

	if (mMsgID != msgID)
	{
		return;
	}

	switch(mOperType)
	{
	case OP_FLASH_ENABLE:
		{
			mFlashTagCountBtn->setEnabled(mFlashEnableCb->isChecked());
			mFlashTagClearBtn->setEnabled(mFlashEnableCb->isChecked());
			MainShowMsg(GET_TXT("IDCS_FLASH_ENABLE_SUCCESS"));		
		}
		break;
	case OP_FLASH_COUNT:		
		break;
	case OP_FLASH_CLEAR:		
		break;
	case OP_FLITER_ENABLE:
		{	
			MainShowMsg(GET_TXT("IDCS_FILTER_ENABLE_SUCCESS"));	
		}
		break;
	case OP_FILTER_TIME:
		{
			MainShowMsg(GET_TXT("IDCS_FILTER_TIME_SUCCESS"));
		}
		break;
	case OP_QUERY_FLASH_ENABLE:
		{
			MainShowMsg(GET_TXT("IDCS_FLASH_ENABLE_QUERY_SUCCESS"));	
			if (1 == pData[1])
			{
				mFlashTagClearBtn->setEnabled(true);
				mFlashTagCountBtn->setEnabled(true);
				mFlashEnableCb->setChecked(true);
			}
			else
			{
				mFlashTagClearBtn->setEnabled(false);
				mFlashTagCountBtn->setEnabled(false);
				mFlashEnableCb->setChecked(false);
			}
		}
		break;
	case OP_QUERY_FLITER_ENABLE:
		break;
	case OP_QUERY_READERSPACETIME:		
		break;
	case OP_SET_READERSPACETIME:		
		break;
	case OP_SET_WORKMODE:		
		break;
	case OP_QUERY_WORKMODE:		
		break;
	case OP_QUERY_CONNETVALUE:		
		break;
	case OP_SET_CONNETVALUE:
		break;
	default:
		break;
	}
}

void WirelessReadParamWidget::slot_QueryFilterTimeBtnClicked()
{
	WirelessReaderInfo* pWirelessReaderInfo = mCtrlDlg->GetReaderInfo();
	if(!pWirelessReaderInfo)
	{
		return;
	}

	int iInfoType = 0x03;
	bool bRet = WIRELESS_SAAT_TagOpParaQuery(
		WIRELESSRECV_HANDLE,
		pWirelessReaderInfo,
		iInfoType);

	if (bRet)
	{
		mOperType = OP_QUERYFILTER_TIME;
	}
	else
	{

		MainShowMsg(GET_TXT("IDCS_FILTER_TIME_QUERY_FAILED"));	
	}
}

