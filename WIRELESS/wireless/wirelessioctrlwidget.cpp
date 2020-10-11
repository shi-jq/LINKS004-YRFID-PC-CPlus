#include "wirelessioctrlwidget.h"
#include "ui_wirelessioctrlwidget.h"
#include "wirelessdeviceinfodlg.h"
#include "WirelessRecvCtrl.h"
#include "WIRELESSRFIDAPIEXPORT.h"
#include "LanguageSrc.h"
#include "mainapp.h"
WirelessIOCtrlWidget::WirelessIOCtrlWidget(WirelessDeviceInfoDlg* ctrlDlg,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::wirelessioctrlwidget)
{
    ui->setupUi(this);
	mCtrlDlg = ctrlDlg;
	mPort1Cb = ui->comboBox;
	mPort2Cb = ui->comboBox_2;
	mPort3Cb = ui->comboBox_3;
	mPort4Cb = ui->comboBox_4;
	mPort1Btn = ui->pushButton;
	mPort2Btn = ui->pushButton_2;
	mPort3Btn = ui->pushButton_3;
	mPort4Btn = ui->pushButton_4;

	mOutBuzzerCb=ui->checkBox;
	mCtrOut1Cb=ui->checkBox_2;
	mCtrOut2Cb=ui->checkBox_3;
	mCtrOut3Cb=ui->checkBox_4;
	mCtrOut4Cb=ui->checkBox_5;
	mOutBuzzerSb=ui->spinBox;
	mCtrlOut1Sb=ui->spinBox_2;
	mCtrlOut2Sb=ui->spinBox_3;
	mCtrlOut3Sb=ui->spinBox_4;
	mCtrlOut4Sb=ui->spinBox_5;
	//mCtrlOutQueryBtn=ui->pushButton_6;
	mCtrlOutSetBtn=ui->pushButton_7;

	mQueryWith1Btn = ui->pushButton_5;
	mQueryWith2Btn = ui->pushButton_8;
	mQueryWith3Btn = ui->pushButton_9;
	mQueryWith4Btn = ui->pushButton_10;
	mQueryWith5Btn = ui->pushButton_11; 



	mPort1Btn->setText(GET_TXT("IDCS_EXECUTE"));
	mPort2Btn->setText(GET_TXT("IDCS_EXECUTE"));
	mPort3Btn->setText(GET_TXT("IDCS_EXECUTE"));
	mPort4Btn->setText(GET_TXT("IDCS_EXECUTE"));
	ui->label_15->setText(GET_TXT("IDCS_PULSE_SIZE"));
	ui->label_16->setText(GET_TXT("IDCS_PULSE_SIZE"));
	ui->label_17->setText(GET_TXT("IDCS_PULSE_SIZE"));
	ui->label_18->setText(GET_TXT("IDCS_PULSE_SIZE"));
	ui->label_19->setText(GET_TXT("IDCS_PULSE_SIZE"));	
	ui->pushButton_7->setText(GET_TXT("IDCS_EXECUTE"));

	QStringList sl;
	sl<<GET_TXT("IDCS_OUTPUT_LOW_VOLTAGE")
		<<GET_TXT("IDCS_OUTPUT_HIGH_VOLTAGE")
		<<GET_TXT("IDCS_OUTPUT_IMPULSE_PLUS")
		<<GET_TXT("IDCS_OUTPUT_IMPULSE_MINUS");

	mPort1Cb->addItems(sl);
	mPort2Cb->addItems(sl);
	mPort3Cb->addItems(sl);
	mPort4Cb->addItems(sl);

	connect( mPort1Btn, SIGNAL( clicked()), this, SLOT( slot_StartPort1Clicked( ) ) );
	connect( mPort2Btn, SIGNAL( clicked()), this, SLOT( slot_StartPort2Clicked( ) ) );
	connect( mPort3Btn, SIGNAL( clicked()), this, SLOT( slot_StartPort3Clicked( ) ) );
	connect( mPort4Btn, SIGNAL( clicked()), this, SLOT( slot_StartPort4Clicked( ) ) );

	connect( mQueryWith1Btn, SIGNAL( clicked()), this, SLOT( slot_CtrlOutSet1Clicked( ) ) );
	connect( mQueryWith2Btn, SIGNAL( clicked()), this, SLOT( slot_CtrlOutSet2Clicked( ) ) );
	connect( mQueryWith3Btn, SIGNAL( clicked()), this, SLOT( slot_CtrlOutSet3Clicked( ) ) );
	connect( mQueryWith4Btn, SIGNAL( clicked()), this, SLOT( slot_CtrlOutSet4Clicked( ) ) );
	connect( mQueryWith5Btn, SIGNAL( clicked()), this, SLOT( slot_CtrlOutSet5Clicked( ) ) );

	connect( mCtrlOutSetBtn, SIGNAL( clicked()), this, SLOT( slot_CtrlOutSetBtnClicked( ) ) );
}

WirelessIOCtrlWidget::~WirelessIOCtrlWidget()
{
    delete ui;
}

void WirelessIOCtrlWidget::slot_StartPort1Clicked()
{
	startPort(1,mPort1Cb->currentIndex());
}

void WirelessIOCtrlWidget::slot_StartPort2Clicked()
{
	startPort(2,mPort2Cb->currentIndex());
}	

void WirelessIOCtrlWidget::slot_StartPort3Clicked()
{
	startPort(3,mPort3Cb->currentIndex());
}

void WirelessIOCtrlWidget::slot_StartPort4Clicked()
{
	startPort(4,mPort4Cb->currentIndex());
}

void WirelessIOCtrlWidget::startPort(int nPort,int nState)
{
	WirelessReaderInfo* pWirelessReaderInfo = mCtrlDlg->GetReaderInfo();
	if(!pWirelessReaderInfo)
	{
		return;
	}

	bool retB = WIRELESS_SAAT_IOOperate(
		WIRELESSRECV_HANDLE,
		pWirelessReaderInfo
		,nPort,nState);
	if(!retB)
	{	
		MainShowMsg(GET_TXT("IDCS_PORT_SET_FAILED_1").arg(nPort));	
	}
}

//void WirelessIOCtrlWidget::slot_CtrlOutQueryBtnClicked()
//{
//	if (!InquireIO())
//	{
//		MainShowMsg(GET_TXT("IDCS_QUERY_FAILED"),true);
//		return;
//	}
//	if (!InquirePulseWidth())
//	{
//		MainShowMsg(GET_TXT("IDCS_QUERY_FAILED"),true);
//		return;
//	}
//	MainShowMsg(GET_TXT("IDCS_QUERY_SUCCESS"));	
//}

void WirelessIOCtrlWidget::slot_CtrlOutSetBtnClicked()
{
	if (!SetPulseWidth())
	{
		MainShowMsg(GET_TXT("IDCS_SET_FAILED"),true);
		return;
	}

	if (!SetReadingIO())
	{
		MainShowMsg(GET_TXT("IDCS_SET_FAILED"),true);
		return;
	}

	MainShowMsg(GET_TXT("IDCS_SET_SUCCESS"));	
}

bool WirelessIOCtrlWidget::InquireIO()
{
	WirelessReaderInfo* pWirelessReaderInfo = mCtrlDlg->GetReaderInfo();
	if(!pWirelessReaderInfo)
	{
		return false;
	}

	bool bRet = WIRELESS_SAAT_Reading_IOQuery(
		WIRELESSRECV_HANDLE,
		pWirelessReaderInfo);

	if (!bRet)
	{	
		MainShowMsg(GET_TXT("IDCS_QUERY_FAILED"),true);
	}

	return bRet;

}

bool WirelessIOCtrlWidget::InquirePulseWidth()
{
	WirelessReaderInfo* pWirelessReaderInfo = mCtrlDlg->GetReaderInfo();
	if(!pWirelessReaderInfo)
	{
		return false;
	}

	for( int i = 0 ; i < 5; i++ )
	{
		unsigned char nWidth = 0;
		if( !WIRELESS_SAAT_IOPulseWidthQuery(
			WIRELESSRECV_HANDLE,
			pWirelessReaderInfo,i) )
		{
			break;
		}
		IOPulseWidthUISet(i,nWidth);
	}
	return true;
}

bool WirelessIOCtrlWidget::IOPulseWidthUISet(unsigned char nPort,unsigned char nWidth)
{
	switch(nPort)
	{
	case 0:
		mOutBuzzerSb->setValue(nWidth);
		break;
	case 1:
		mCtrlOut1Sb->setValue(nWidth);
		break;
	case 2:
		mCtrlOut2Sb->setValue(nWidth);
		break;
	case 3:
		mCtrlOut3Sb->setValue(nWidth);
		break;
	case 4:
		mCtrlOut4Sb->setValue(nWidth);
		break;
	}
	return true;
}

bool WirelessIOCtrlWidget::SetPulseWidth()
{
	WirelessReaderInfo* pWirelessReaderInfo = mCtrlDlg->GetReaderInfo();
	if(!pWirelessReaderInfo)
	{
		return false;
	}

	int nValue0 = mOutBuzzerSb->value();
	int nValue1 = mCtrlOut1Sb->value();
	int nValue2 = mCtrlOut2Sb->value();
	int nValue3 = mCtrlOut3Sb->value();
	int nValue4 = mCtrlOut4Sb->value();
	bool bRet = WIRELESS_SAAT_IOPulseWidthSet(
		WIRELESSRECV_HANDLE,
		pWirelessReaderInfo,0x00,nValue0);
	if (bRet)
	{
		bRet = WIRELESS_SAAT_IOPulseWidthSet(
			WIRELESSRECV_HANDLE,
			pWirelessReaderInfo,0x01,nValue1);
	}
	if (bRet)
	{
		bRet = WIRELESS_SAAT_IOPulseWidthSet(
			WIRELESSRECV_HANDLE,
			pWirelessReaderInfo,0x02,nValue2);
	}
	if (bRet)
	{
		bRet = WIRELESS_SAAT_IOPulseWidthSet(
			WIRELESSRECV_HANDLE,
			pWirelessReaderInfo,0x03,nValue3);
	}
	if (bRet)
	{
		bRet = WIRELESS_SAAT_IOPulseWidthSet(
			WIRELESSRECV_HANDLE,
			pWirelessReaderInfo,0x04,nValue4);
	}

	return bRet;
}

bool WirelessIOCtrlWidget::SetReadingIO()
{
	WirelessReaderInfo* pWirelessReaderInfo = mCtrlDlg->GetReaderInfo();
	if(!pWirelessReaderInfo)
	{
		return false;
	}

	unsigned char nMask = 0;

	if(mCtrOut4Cb->isChecked() )
	{
		nMask = nMask | 0x10;
	}
	if(mCtrOut3Cb->isChecked())
	{
		nMask = nMask | 0x08;
	}
	if( mCtrOut2Cb->isChecked() )
	{
		nMask = nMask | 0x04;
	}
	if( mCtrOut1Cb->isChecked() )
	{
		nMask = nMask | 0x02;
	}
	if(mOutBuzzerCb->isChecked() )
	{
		nMask = nMask | 0x01;
	}

	bool bRet = WIRELESS_SAAT_Reading_IOConfig(
		WIRELESSRECV_HANDLE,
		pWirelessReaderInfo,nMask);

	return bRet;
}

void WirelessIOCtrlWidget::SetRevMsg(int msgID,unsigned char bCommand,unsigned char* pData, int nLen)
{
	switch(bCommand)
	{
	case COM_IO_OP:
		{
			MainShowMsg(GET_TXT("IDCS_EXECUTE_SUCCESS"));
		}
		break;
	case COM_INPUT_QUERY:
		{}
		break;
	case READING_IO_CONFIG:
		break;
	case READING_IO_QUERY:
		{
			int nState = pData[1];
			byte bPort0 = 0x01 & (nState);
			byte bPort1 = 0x01 & (nState>>1);
			byte bPort2 = 0x01 & (nState>>2);
			byte bPort3 = 0x01 & (nState>>3);
			byte bPort4 = 0x01 & (nState>>4);

			mOutBuzzerCb->setChecked(bPort0 == 1);
			mCtrOut1Cb->setChecked(bPort1 == 1);
			mCtrOut2Cb->setChecked(bPort2 == 1);
			mCtrOut3Cb->setChecked(bPort3 == 1);
			mCtrOut4Cb->setChecked(bPort4 == 1);

			MainShowMsg(GET_TXT("IDCS_QUERY_SUCCESS"));
		}
		break;
	case COM_IO_PULSESET:
		{
			MainShowMsg(GET_TXT("IDCS_SET_SUCCESS"));
		}
		break;
	case COM_IO_PULSEQUERY:
		{
			unsigned char nWidth = pData[1];
			if (mOperBtn)
			{
				if (mOperBtn == mQueryWith1Btn)
				{
					IOPulseWidthUISet(0,nWidth);
					MainShowMsg(GET_TXT("IDCS_QUERY_SUCCESS"));
				}
				else if (mOperBtn == mQueryWith2Btn)
				{
					IOPulseWidthUISet(1,nWidth);
					MainShowMsg(GET_TXT("IDCS_QUERY_SUCCESS"));
				}
				else if (mOperBtn == mQueryWith3Btn)
				{
					IOPulseWidthUISet(2,nWidth);
					MainShowMsg(GET_TXT("IDCS_QUERY_SUCCESS"));
				}
				else if (mOperBtn == mQueryWith4Btn)
				{
					IOPulseWidthUISet(3,nWidth);
					MainShowMsg(GET_TXT("IDCS_QUERY_SUCCESS"));
				}
				else if (mOperBtn == mQueryWith5Btn)
				{
					IOPulseWidthUISet(4,nWidth);
					MainShowMsg(GET_TXT("IDCS_QUERY_SUCCESS"));
				}
			}				
		}
		break;
	default:
		break;
	}
}

void WirelessIOCtrlWidget::slot_CtrlOutSet1Clicked()
{

	WirelessReaderInfo* pWirelessReaderInfo = mCtrlDlg->GetReaderInfo();
	if(!pWirelessReaderInfo)
	{
		return ;
	}

	if (!InquireIO())
	{
		MainShowMsg(GET_TXT("IDCS_QUERY_FAILED"),true);
		return;
	}


	if( !WIRELESS_SAAT_IOPulseWidthQuery(
		WIRELESSRECV_HANDLE,
		pWirelessReaderInfo,0) )
	{
		MainShowMsg(GET_TXT("IDCS_QUERY_FAILED"),true);
		return;
	}

	mOperBtn = mQueryWith1Btn;
	
}

void WirelessIOCtrlWidget::slot_CtrlOutSet2Clicked()
{
	WirelessReaderInfo* pWirelessReaderInfo = mCtrlDlg->GetReaderInfo();
	if(!pWirelessReaderInfo)
	{
		return ;
	}
	if (!InquireIO())
	{
		MainShowMsg(GET_TXT("IDCS_QUERY_FAILED"),true);
		return;
	}


	if( !WIRELESS_SAAT_IOPulseWidthQuery(
		WIRELESSRECV_HANDLE,
		pWirelessReaderInfo,1) )
	{
		MainShowMsg(GET_TXT("IDCS_QUERY_FAILED"),true);
		return;
	}
	mOperBtn = mQueryWith2Btn;
}

void WirelessIOCtrlWidget::slot_CtrlOutSet3Clicked()
{	
	WirelessReaderInfo* pWirelessReaderInfo = mCtrlDlg->GetReaderInfo();
	if(!pWirelessReaderInfo)
	{
		return ;
	}
	if (!InquireIO())
	{
		MainShowMsg(GET_TXT("IDCS_QUERY_FAILED"),true);
		return;
	}


	if( !WIRELESS_SAAT_IOPulseWidthQuery(
		WIRELESSRECV_HANDLE,
		pWirelessReaderInfo,2) )
	{
		MainShowMsg(GET_TXT("IDCS_QUERY_FAILED"),true);
		return;
	}
	mOperBtn = mQueryWith3Btn;
}

void WirelessIOCtrlWidget::slot_CtrlOutSet4Clicked()
{
	WirelessReaderInfo* pWirelessReaderInfo = mCtrlDlg->GetReaderInfo();
	if(!pWirelessReaderInfo)
	{
		return ;
	}
	if (!InquireIO())
	{
		MainShowMsg(GET_TXT("IDCS_QUERY_FAILED"),true);
		return;
	}


	if( !WIRELESS_SAAT_IOPulseWidthQuery(
		WIRELESSRECV_HANDLE,
		pWirelessReaderInfo,3) )
	{
		MainShowMsg(GET_TXT("IDCS_QUERY_FAILED"),true);
		return;
	}
	mOperBtn = mQueryWith4Btn;
}

void WirelessIOCtrlWidget::slot_CtrlOutSet5Clicked()
{
	WirelessReaderInfo* pWirelessReaderInfo = mCtrlDlg->GetReaderInfo();
	if(!pWirelessReaderInfo)
	{
		return ;
	}
	if (!InquireIO())
	{
		MainShowMsg(GET_TXT("IDCS_QUERY_FAILED"),true);
		return;
	}


	if( !WIRELESS_SAAT_IOPulseWidthQuery(
		WIRELESSRECV_HANDLE,
		pWirelessReaderInfo,4) )
	{
		MainShowMsg(GET_TXT("IDCS_QUERY_FAILED"),true);
		return;
	}
	mOperBtn = mQueryWith5Btn;
}	
