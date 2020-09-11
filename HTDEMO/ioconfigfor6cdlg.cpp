#include "ioconfigfor6cdlg.h"
#include "ui_ioconfigfor6cdlg.h"
#include "LanguageSrc.h"
#include "appconfig.h"
#include "mainapp.h"
#include "RFIDAPIEXPORT.h"
#include "readerdllbase.h"

IoConfigFor6CDlg::IoConfigFor6CDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IoConfigFor6CDlg)
{
    ui->setupUi(this);
	this->setWindowTitle(GET_TXT("IDCS_IO_CONTRL"));
	mPutIn0Edit=ui->lineEdit;
	mPutIn1Edit=ui->lineEdit_2;
	mQueryInBtn=ui->pushButton;
	mPutout1CB=ui->comboBox;
	mPutout2CB=ui->comboBox_2;
	mPutout3CB=ui->comboBox_3;
	mPutout4CB=ui->comboBox_4;
	mPutout1Btn=ui->pushButton_2;
	mPutout2Btn=ui->pushButton_3;
	mPutout3Btn=ui->pushButton_4;
	mPutout4Btn=ui->pushButton_5;

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
	mCtrlOutQueryBtn=ui->pushButton_6;
	mCtrlOutSetBtn=ui->pushButton_7;

	mPutIn0Edit->setReadOnly(true);
	mPutIn1Edit->setReadOnly(true);

	QStringList sl;
	sl<<GET_TXT("IDCS_OUTPUT_LOW_VOLTAGE")
		<<GET_TXT("IDCS_OUTPUT_HIGH_VOLTAGE");
	mPutout1CB->addItems(sl);
	mPutout2CB->addItems(sl);
	
	sl.clear();
	sl<<GET_TXT("IDCS_CLOSE")
		<<GET_TXT("IDCS_OPEN");
	mPutout3CB->addItems(sl);
	mPutout4CB->addItems(sl);

	mFirst = true;

	connect( mQueryInBtn, SIGNAL( clicked()), this, SLOT( slot_QueryInBtnClicked( ) ) );
	connect( mPutout1Btn, SIGNAL( clicked()), this, SLOT( slot_Putout1BtnClicked( ) ) );
	connect( mPutout2Btn, SIGNAL( clicked()), this, SLOT( slot_Putout2BtnClicked( ) ) );
	connect( mPutout3Btn, SIGNAL( clicked()), this, SLOT( slot_Putout3BtnClicked( ) ) );
	connect( mPutout4Btn, SIGNAL( clicked()), this, SLOT( slot_Putout4BtnClicked( ) ) );
	connect( mCtrlOutQueryBtn, SIGNAL( clicked()), this, SLOT( slot_CtrlOutQueryBtnClicked( ) ) );
	connect( mCtrlOutSetBtn, SIGNAL( clicked()), this, SLOT( slot_CtrlOutSetBtnClicked( ) ) );

}

IoConfigFor6CDlg::~IoConfigFor6CDlg()
{
    delete ui;
}

void IoConfigFor6CDlg::showEvent(QShowEvent *event)
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
        //mFirst = !QueryOutPutAll();
	}
	QWidget::showEvent(event);
}

void IoConfigFor6CDlg::slot_QueryInBtnClicked()
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

	byte nState[2] ={0,0};
	bool bRet = SAAT_IOStateQuery(pReaderDllBase->m_hCom,&nState[0]);
	
	if (bRet)
	{		
		byte bPort1 = 0x01 & nState[0];
		byte bPort2 = 0x01 & (nState[0]>>1);
		if( bPort1 == 1)
		{
			mPutIn0Edit->setText(GET_TXT("IDCS_HIGH_VOLTAGE"));
		}
		else
		{
			mPutIn0Edit->setText(GET_TXT("IDCS_LOW_VOLTAGE"));
		}

		if( bPort2 == 1)
		{
			mPutIn1Edit->setText(GET_TXT("IDCS_HIGH_VOLTAGE"));
		}
		else
		{
			mPutIn1Edit->setText(GET_TXT("IDCS_LOW_VOLTAGE"));
		}
		MainShowMsg(GET_TXT("IDCS_QUERY_SUCCESS"));	
	}
	else
	{
		mPutIn0Edit->setText("");
		mPutIn1Edit->setText("");
		MainShowMsg(GET_TXT("IDCS_QUERY_FAILED"),true);
	}
}

void IoConfigFor6CDlg::slot_Putout1BtnClicked()
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

	byte nState = mPutout1CB->currentIndex();//high: 0x01 low: 0x00
	byte nPort  = 0x01;

	bool bRet = SAAT_IOOperate(pReaderDllBase->m_hCom,nPort,nState);

	if (bRet)
	{	
		MainShowMsg(GET_TXT("IDCS_SET_SUCCESS"));	
	}
	else
	{
		MainShowMsg(GET_TXT("IDCS_SET_FAILED"),true);
	}
}

void IoConfigFor6CDlg::slot_Putout2BtnClicked()
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

	byte nState = mPutout2CB->currentIndex();
	byte nPort  = 0x02;

	bool bRet = SAAT_IOOperate(pReaderDllBase->m_hCom,nPort,nState);

	if (bRet)
	{	
		MainShowMsg(GET_TXT("IDCS_SET_SUCCESS"));	
	}
	else
	{
		MainShowMsg(GET_TXT("IDCS_SET_FAILED"),true);
	}
}

void IoConfigFor6CDlg::slot_Putout3BtnClicked()
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

	byte nState = mPutout3CB->currentIndex();
	byte nPort  = 0x03;

	bool bRet = SAAT_IOOperate(pReaderDllBase->m_hCom,nPort,nState);

	if (bRet)
	{	
		MainShowMsg(GET_TXT("IDCS_SET_SUCCESS"));	
	}
	else
	{
		MainShowMsg(GET_TXT("IDCS_SET_FAILED"),true);
	}
}

void IoConfigFor6CDlg::slot_Putout4BtnClicked()
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

	byte nState = mPutout4CB->currentIndex();
	byte nPort  = 0x04;

	bool bRet = SAAT_IOOperate(pReaderDllBase->m_hCom,nPort,nState);

	if (bRet)
	{	
		MainShowMsg(GET_TXT("IDCS_SET_SUCCESS"));	
	}
	else
	{
		MainShowMsg(GET_TXT("IDCS_SET_FAILED"),true);
	}
}

void IoConfigFor6CDlg::slot_CtrlOutQueryBtnClicked()
{
	QueryOutPutAll();
}

void IoConfigFor6CDlg::slot_CtrlOutSetBtnClicked()
{
	ReaderDllBase*	pReaderDllBase = pMainApp->GetReader();
	if (!pReaderDllBase)
	{
		MainShowMsg(GET_TXT("IDCS_READ_NO_LINK"));
		return ;
	}
	if (!pReaderDllBase->CheckState(STATE_CONNET))
	{
		MainShowMsg(GET_TXT("IDCS_READ_NO_LINK"));
		return ;
	}

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

bool IoConfigFor6CDlg::InquireIO()
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

	byte nState = 0;
	bool bRet = SAAT_Reading_IOQuery(
		pReaderDllBase->m_hCom,&nState);

	if (bRet)
	{	
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
	else
	{
		MainShowMsg(GET_TXT("IDCS_QUERY_FAILED"),true);
	}

	return bRet;
}

bool IoConfigFor6CDlg::InquirePulseWidth()
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

	for( int i = 0 ; i < 5; i++ )
	{
		unsigned char nWidth = 0;
		if( !SAAT_IOPulseWidthQuery(pReaderDllBase->m_hCom,i,&nWidth ) )
		{
			break;
		}
		IOPulseWidthUISet(i,nWidth);
	}
	return true;
}

bool IoConfigFor6CDlg::IOPulseWidthUISet(unsigned char nPort,unsigned char nWidth)
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

bool IoConfigFor6CDlg::SetPulseWidth()
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

	int nValue0 = mOutBuzzerSb->value();
	int nValue1 = mCtrlOut1Sb->value();
	int nValue2 = mCtrlOut2Sb->value();
	int nValue3 = mCtrlOut3Sb->value();
	int nValue4 = mCtrlOut4Sb->value();
	bool bRet = SAAT_IOPulseWidthSet(
		pReaderDllBase->m_hCom,0x00,nValue0);
	if (bRet)
	{
		bRet = SAAT_IOPulseWidthSet(
			pReaderDllBase->m_hCom,0x01,nValue1);
	}
	if (bRet)
	{
		bRet = SAAT_IOPulseWidthSet(
			pReaderDllBase->m_hCom,0x02,nValue2);
	}
	if (bRet)
	{
		bRet = SAAT_IOPulseWidthSet(
			pReaderDllBase->m_hCom,0x03,nValue3);
	}
	if (bRet)
	{
		bRet = SAAT_IOPulseWidthSet(
			pReaderDllBase->m_hCom,0x04,nValue4);
	}
	
	return bRet;
}

bool IoConfigFor6CDlg::SetReadingIO()
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

	bool bRet = SAAT_Reading_IOConfig(pReaderDllBase->m_hCom,nMask);

	return bRet;
}

bool IoConfigFor6CDlg::QueryOutPutAll()
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

	if (!InquireIO())
	{
		MainShowMsg(GET_TXT("IDCS_QUERY_FAILED"),true);
		return false;
	}
	if (!InquirePulseWidth())
	{
		MainShowMsg(GET_TXT("IDCS_QUERY_FAILED"),true);
		return false;
	}
	MainShowMsg(GET_TXT("IDCS_QUERY_SUCCESS"));

	return true;
}
