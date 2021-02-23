#include "wirelessreadconfigwidget.h"
#include "ui_wirelessreadconfigwidget.h"
#include "wirelessdeviceinfodlg.h"
#include "WirelessRecvCtrl.h"
#include "WIRELESSRFIDAPIEXPORT.h"
#include "LanguageSrc.h"
#include "mainapp.h"
#include "widgetconfig.h"
#include "appconfig.h"
#include "antennaprmform.h"
#include "carrierconfigform.h"
#include "pointconfigform.h"

WirelessReadConfigWidget::WirelessReadConfigWidget(WirelessDeviceInfoDlg* ctrlDlg,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::wirelessreadconfigwidget)
{
    ui->setupUi(this);
	this->setWindowTitle(GET_TXT("IDCS_DEVICE_CONFIG"));
	mCtrlDlg = ctrlDlg;
	CreateView();
	updateLanguage();

}

WirelessReadConfigWidget::~WirelessReadConfigWidget()
{
    delete ui;
}


void WirelessReadConfigWidget::CreateView()
{
	mAntennaPrmForm = new AntennaPrmForm(mCtrlDlg,ui->widget_10);
	QGridLayout* gridLayout = new QGridLayout(ui->widget_10);
	gridLayout->setSpacing(0);
	gridLayout->setContentsMargins(0,0,0,0);
	gridLayout->addWidget(mAntennaPrmForm);	

	mCarrierConfigForm = new CarrierConfigForm(mCtrlDlg,ui->widget_12);
	gridLayout = new QGridLayout(ui->widget_12);
	gridLayout->setSpacing(0);
	gridLayout->setContentsMargins(0,0,0,0);
	gridLayout->addWidget(mCarrierConfigForm);	

	mPointConfigForm = new PointConfigForm(mCtrlDlg,ui->widget_14);
	gridLayout = new QGridLayout(ui->widget_14);
	gridLayout->setSpacing(0);
	gridLayout->setContentsMargins(0,0,0,0);
	gridLayout->addWidget(mPointConfigForm);
}

void WirelessReadConfigWidget::updateLanguage()
{
}


void WirelessReadConfigWidget::SetRevMsg(int msgID,
										 unsigned char bCommand,
										 unsigned char* pData, 
										 int nLen)
{
	switch(bCommand)
	{
	case COM_ANTENNA_QUERY:
		mPointConfigForm->SetRevMsg( msgID,bCommand,pData, nLen);
		break;
	case COM_ANTENNA_SET:
		MainShowMsg(GET_TXT("IDCS_ANTENNA_STATE_SET_SUCCESS"));	
		break;
	case COM_CARRYWAVE_QUERY:
		{
			mCarrierConfigForm->SetRevMsg( msgID,bCommand,pData, nLen);
		}
		break;
	case COM_CARRYWAVE_SET:
		MainShowMsg(GET_TXT("IDCS_FREQUENCY_POINT_SET_SUCCESS"));	
		break;
	case COM_ANTENNA_SET_EX:
		{
			MainShowMsg(GET_TXT("IDCS_ANTENNA_PORT_SET_SUCCESS"));	
		}
		break;
	case COM_ANTENNA_QUERY_EX:
		{
			mAntennaPrmForm->SetRevMsg( msgID,bCommand,pData, nLen);
		}
		break;
	default:
		break;
	}
}