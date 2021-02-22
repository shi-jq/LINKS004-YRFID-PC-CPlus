#include "wirelessdeviceinfodlg.h"
#include "ui_wirelessdeviceinfodlg.h"
#include "wirelessreadparamwidget.h"
#include "wirelessreadconfigwidget.h"
#include "wirelessioctrlwidget.h"
#include "wirelesssysinfowidget.h"
#include "LanguageSrc.h"

WirelessDeviceInfoDlg::WirelessDeviceInfoDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WirelessDeviceInfoDlg)
{
    ui->setupUi(this);
	this->setWindowTitle(GET_TXT("IDCS_DEVICE_CONFIG"));

	mtabWidget = ui->tabWidget;
	mReaderInfo = NULL;

	mWirelessSysinfoWidget = new WirelessSysinfoWidget(this,mtabWidget);
	mtabWidget->addTab(mWirelessSysinfoWidget,QIcon(),GET_TXT("IDCS_DEVICE_INFO"));

	mWirelessReadConfigWidget = new WirelessReadConfigWidget(this,mtabWidget);
	mtabWidget->addTab(mWirelessReadConfigWidget,QIcon(),GET_TXT("IDCS_RADIO_CONFIG"));
	
	mWirelessReadParamWidget = new WirelessReadParamWidget(this,mtabWidget);
	mtabWidget->addTab(mWirelessReadParamWidget,QIcon(),GET_TXT("IDCS_READ_CARD_CONFIG"));

	mWirelessIOCtrlWidget = new WirelessIOCtrlWidget(this,mtabWidget);
	mtabWidget->addTab(mWirelessIOCtrlWidget,QIcon(),GET_TXT("IDCS_IO_CONTRL"));


}

WirelessDeviceInfoDlg::~WirelessDeviceInfoDlg()
{
    delete ui;
}

void WirelessDeviceInfoDlg::SetWirelessReaderInfo(WirelessReaderInfo* pReaderInfo)
{
	mReaderInfo = pReaderInfo;
}

WirelessReaderInfo* WirelessDeviceInfoDlg::GetReaderInfo()
{
	return mReaderInfo;
}

void WirelessDeviceInfoDlg::SetRevMsg(WirelessReaderInfo* pReaderInfo,int msgID,unsigned char bCommand,unsigned char* pData, int nLen)
{
	if (pReaderInfo != mReaderInfo)
	{
		return;
	}

	switch(bCommand)
	{
	case 0:
		break;
	case READER_TIME_QUERY:
	case READER_TIME_SET:
	case COM_SYS_QUERY:
		mWirelessSysinfoWidget->SetRevMsg(msgID,bCommand,pData,nLen);
		break;
	case COM_ANTENNA_QUERY:
	case COM_ANTENNA_SET:
	case COM_CARRYWAVE_QUERY:
	case COM_CARRYWAVE_SET:	
	case COM_ANTENNA_SET_EX:
	case COM_ANTENNA_QUERY_EX:
		mWirelessReadConfigWidget->SetRevMsg(msgID,bCommand,pData,nLen);
		break;
	case READER_FLASHDATA_QUERY:
	case READER_FLASHDATACOUNT_QUERY:
	case READER_FLASHCLEAR:
	case COM_TAG_SET:
	case COM_TAG_QUERY:	
		mWirelessReadParamWidget->SetRevMsg(msgID,bCommand,pData,nLen);
		break;

	case COM_PARA_OP:
		{		
			if (mWirelessReadConfigWidget->isVisible())
			{
				mWirelessReadConfigWidget->SetRevMsg(msgID,bCommand,pData,nLen);
			}
			else if(mWirelessReadParamWidget->isVisible())
			{
				mWirelessReadParamWidget->SetRevMsg(msgID,bCommand,pData,nLen);
			}		
		}
		break;

	case COM_IO_OP:
	case COM_INPUT_QUERY:
	case READING_IO_CONFIG:
	case READING_IO_QUERY:
	case COM_IO_PULSESET:
	case COM_IO_PULSEQUERY:
		mWirelessIOCtrlWidget->SetRevMsg(msgID,bCommand,pData,nLen);
		break;
	default:
		break;
	}
}
