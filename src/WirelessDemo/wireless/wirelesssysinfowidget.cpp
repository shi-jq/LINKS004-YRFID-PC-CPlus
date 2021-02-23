#include "wirelesssysinfowidget.h"
#include "ui_wirelesssysinfowidget.h"
#include "wirelessdeviceinfodlg.h"
#include "WirelessRecvCtrl.h"
#include "WIRELESSRFIDAPIEXPORT.h"
#include "LanguageSrc.h"
#include "mainapp.h"
#include "appconfig.h"

WirelessSysinfoWidget::WirelessSysinfoWidget(WirelessDeviceInfoDlg* ctrlDlg,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::wirelessSysInfoWidget)
{
    ui->setupUi(this);
	mCtrlDlg = ctrlDlg;
	ui->pushButton->setText(GET_TXT("IDCS_QUERY"));	
	ui->label_11->setText(GET_TXT("IDCS_DEVICE_INFO"));
	ui->label_13->setText(GET_TXT("IDCS_DATE"));
	ui->label_14->setText(GET_TXT("IDCS_TIME"));
	ui->pushButton_4->setText(GET_TXT("IDCS_QUERY"));
	ui->pushButton_2->setText(GET_TXT("IDCS_SET"));
	

	mQueryBtn = ui->pushButton;
	
	mTimeEdit = ui->timeEdit;
	mDateEidt = ui->dateEdit;
	mQueryTimeBtn = ui->pushButton_4;
	mSetTimeBtn = ui->pushButton_2;
	mGetCurtimeBtn=ui->pushButton_3;
	mQueryTypeCb = ui->comboBox;
	mQueryResultEdit = ui->lineEdit;


	connect( mQueryTimeBtn, SIGNAL( clicked()), this, SLOT( slot_QueryTimeBtnClicked( ) ) );
	connect( mSetTimeBtn, SIGNAL( clicked()), this, SLOT( slot_SetBtnTimeClicked( ) ) );
	connect( mGetCurtimeBtn, SIGNAL( clicked()), this, SLOT( slot_GetCurtimeBtnClicked( ) ) );

	connect( mQueryBtn, SIGNAL( clicked()), this, SLOT( slot_QueryBtnClicked( ) ) );
}

WirelessSysinfoWidget::~WirelessSysinfoWidget()
{
    delete ui;
}

void WirelessSysinfoWidget::slot_QueryBtnClicked()
{
	bool bRet = true;
	mQueryResultEdit->clear();
	switch(mQueryTypeCb->currentIndex())
	{
	case  0:
		bRet = QueryDeviceName();
		break;
	/*case  1:
		bRet = QuerySN();
		break;
	case  2:
		bRet = QueryDeviceType();
		break;
	case  3:
		bRet = QueryMCUVer();
		break;
	case  4:
		bRet = QueryHardwareVer();
		break;*/
	default:
		break;
	}	
}

unsigned int WirelessSysinfoWidget::C16Convert10(int a)
{
	bool bok;
	return QString("%1").arg( a).toUInt(&bok,16);
}

unsigned int WirelessSysinfoWidget::C10Convert16(int a)
{
	return QString("%1").arg( a,2,16,QLatin1Char('0')).toUInt();	
}

void WirelessSysinfoWidget::slot_QueryTimeBtnClicked()
{
	WirelessReaderInfo* pWirelessReaderInfo = mCtrlDlg->GetReaderInfo();
	if(!pWirelessReaderInfo)
	{
		return;
	}
	
	bool retB = WIRELESS_SAAT_ReaderTimeQuery(
		WIRELESSRECV_HANDLE,
		pWirelessReaderInfo);

	if (!retB)
	{
		MainShowMsg(GET_TXT("IDCS_QUERY_TIME_CONFIG_FAILED"),true);
	/*	int nSec =C10Convert16( btPara[0]);
		int nMin = C10Convert16(btPara[1]); 
		int nHour = C10Convert16(btPara[2]);
		int nDayWeek = C10Convert16(btPara[3]);
		int nDay = C10Convert16(btPara[4]);
		int nMonth = C10Convert16(btPara[5]);
		int nYear = C10Convert16(btPara[6])+2000;

		if ( (0==nDay) || (0==nMonth) )
		{
			MainShowMsg(GET_TXT("IDCS_QUERY_TIME_CONFIG_FAILED"));
			return ;
		}

		mDateEidt->setDate(QDate(nYear,nMonth,nDay));
		mTimeEdit->setTime(QTime(nHour,nMin,nSec));
		MainShowMsg(GET_TXT("IDCS_QUERY_TIME_CONFIG_SUCCESS"));*/
	}	
}

void WirelessSysinfoWidget::slot_SetBtnTimeClicked()
{
	WirelessReaderInfo* pWirelessReaderInfo = mCtrlDlg->GetReaderInfo();
	if(!pWirelessReaderInfo)
	{
		return;
	}

	unsigned char btPara[7] ;
	ZeroMemory(btPara,7);

	QDate tmpDate = mDateEidt->date();
	QTime tmpTime = mTimeEdit->time();

	btPara[0] = C16Convert10(tmpTime.second());
	btPara[1] = C16Convert10(tmpTime.minute());
	btPara[2] = C16Convert10(tmpTime.hour());
	btPara[3] = C16Convert10(tmpDate.dayOfWeek());
	btPara[4] = C16Convert10(tmpDate.day());
	btPara[5] = C16Convert10(tmpDate.month());
	int nYear = C16Convert10(tmpDate.year() %100);		
	btPara[6] = nYear;

	bool bRet = WIRELESS_SAAT_SetReaderTime(
		WIRELESSRECV_HANDLE,
		pWirelessReaderInfo,
		btPara,7);

	if (!bRet)
	{
		MainShowMsg(GET_TXT("IDCS_SET_TIME_CONFIG_FAILED"),true);
	}
}

void WirelessSysinfoWidget::slot_GetCurtimeBtnClicked()
{
	QDateTime curTimeDate = QDateTime::currentDateTime();
	mDateEidt->setDateTime(curTimeDate);
	mTimeEdit->setDateTime(curTimeDate);

	slot_SetBtnTimeClicked();
}

bool WirelessSysinfoWidget::QueryDeviceName()
{
	WirelessReaderInfo* pWirelessReaderInfo = mCtrlDlg->GetReaderInfo();
	if(!pWirelessReaderInfo)
	{
		return false;
	}
	
	//Éè±¸Ãû³Æ
	int nParam = 0;
	bool bRet = WIRELESS_SAAT_SysInfQuery(
		WIRELESSRECV_HANDLE,
		pWirelessReaderInfo,
		nParam);

	if(!bRet)
	{
		MainShowMsg(GET_TXT("IDCS_DEVICE_NAME_QUERY_FAILED"));	
	}

	return bRet;
}

bool WirelessSysinfoWidget::QuerySN()
{
	WirelessReaderInfo* pWirelessReaderInfo = mCtrlDlg->GetReaderInfo();
	if(!pWirelessReaderInfo)
	{
		return false;
	}

	int nParam = 0x02;
	bool bRet = WIRELESS_SAAT_SysInfQuery(
		WIRELESSRECV_HANDLE,
		pWirelessReaderInfo,
		nParam);

	if(!bRet)
	{
		MainShowMsg(GET_TXT("IDCS_DEVICE_NAME_QUERY_FAILED"));	
	}

	return bRet;
}

bool WirelessSysinfoWidget::QueryDeviceType()
{
	WirelessReaderInfo* pWirelessReaderInfo = mCtrlDlg->GetReaderInfo();
	if(!pWirelessReaderInfo)
	{
		return false;
	}

	int nParam = 0x01;
	bool bRet = WIRELESS_SAAT_SysInfQuery(
		WIRELESSRECV_HANDLE,
		pWirelessReaderInfo,
		nParam);

	if(!bRet)
	{
		MainShowMsg(GET_TXT("IDCS_DEVICE_NAME_QUERY_FAILED"));	
	}

	return bRet;
}

bool WirelessSysinfoWidget::QueryMCUVer()
{
	WirelessReaderInfo* pWirelessReaderInfo = mCtrlDlg->GetReaderInfo();
	if(!pWirelessReaderInfo)
	{
		return false;
	}

	int nParam = 0x03;
	bool bRet = WIRELESS_SAAT_SysInfQuery(
		WIRELESSRECV_HANDLE,
		pWirelessReaderInfo,
		nParam);

	if(!bRet)
	{
		MainShowMsg(GET_TXT("IDCS_DEVICE_NAME_QUERY_FAILED"));	
	}

	return bRet;
}

bool WirelessSysinfoWidget::QueryHardwareVer()
{
	WirelessReaderInfo* pWirelessReaderInfo = mCtrlDlg->GetReaderInfo();
	if(!pWirelessReaderInfo)
	{
		return false;
	}

	int nParam = 0x05;
	bool bRet = WIRELESS_SAAT_SysInfQuery(
		WIRELESSRECV_HANDLE,
		pWirelessReaderInfo,
		nParam);

	if(!bRet)
	{
		MainShowMsg(GET_TXT("IDCS_DEVICE_NAME_QUERY_FAILED"));	
	}

	return bRet;
}

void WirelessSysinfoWidget::SetRevMsg(int msgID,unsigned char bCommand,unsigned char* pData, int nLen)
{
	switch(bCommand)
	{
	case COM_SYS_QUERY:
		{
			if (nLen>1)
			{
				QString strTmp = QString::fromUtf8((char*)(pData+1),nLen-1);
				mQueryResultEdit->setText(strTmp);
			}
		}
		break;
	case READER_TIME_QUERY:
		{
			int nSec =C10Convert16( pData[1]);
			int nMin = C10Convert16(pData[2]); 
			int nHour = C10Convert16(pData[3]);
			int nDayWeek = C10Convert16(pData[4]);
			int nDay = C10Convert16(pData[5]);
			int nMonth = C10Convert16(pData[6]);
			int nYear = C10Convert16(pData[7])+2000;
			if(nYear>=2070)
			{
				nYear -= 100;
			}

			if ( (0==nDay) || (0==nMonth) )
			{
				MainShowMsg(GET_TXT("IDCS_QUERY_TIME_CONFIG_FAILED"));
				return ;
			}

			mDateEidt->setDate(QDate(nYear,nMonth,nDay));
			mTimeEdit->setTime(QTime(nHour,nMin,nSec));
			MainShowMsg(GET_TXT("IDCS_QUERY_TIME_CONFIG_SUCCESS"));
		}
		break;
	case READER_TIME_SET:
		{
			MainShowMsg(GET_TXT("IDCS_SET_TIME_CONFIG_SUCCESS"));
		}
		break;
	default:
		break;
	}

}

