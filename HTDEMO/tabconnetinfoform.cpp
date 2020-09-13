#include "tabconnetinfoform.h"
#include "ui_tabconnetinfoform.h"
#include "LanguageSrc.h"
#include "netconfigfor6cdlg.h"
#include "comconfigdlg.h"
#include "busaddrconfigdlg.h"
#include "weigenconfigform.h"

TabConnetInfoForm::TabConnetInfoForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TabConnetInfoForm)
{
    ui->setupUi(this);

	mNetConfigFor6CDlg = new NetConfigFor6CDlg(ui->widget_6);
	QGridLayout* gridLayout = new QGridLayout(ui->widget_6);
	gridLayout->setSpacing(0);
	gridLayout->setContentsMargins(0,0,0,0);
	gridLayout->addWidget(mNetConfigFor6CDlg);	

	mComConfigDlg = new ComConfigDlg(ui->widget_2);
	gridLayout = new QGridLayout(ui->widget_2);
	gridLayout->setSpacing(0);
	gridLayout->setContentsMargins(0,0,0,0);
	gridLayout->addWidget(mComConfigDlg);	

	mBusAddrConfigDlg = new BusAddrConfigDlg(ui->widget_4);
	gridLayout = new QGridLayout(ui->widget_4);
	gridLayout->setSpacing(0);
	gridLayout->setContentsMargins(0,0,0,0);
	gridLayout->addWidget(mBusAddrConfigDlg);	


	mWeiGenConfigForm = new WeiGenConfigForm(ui->widget_10);
	gridLayout = new QGridLayout(ui->widget_10);
	gridLayout->setSpacing(0);
	gridLayout->setContentsMargins(0,0,0,0);
	gridLayout->addWidget(mWeiGenConfigForm);	

	ui->label_8->setText(GET_TXT("IDCS_NET_CONFIG"));
	ui->label_6->setText(GET_TXT("IDCS_COM_CONFIG"));
	ui->label_7->setText(GET_TXT("IDCS_BUS_CONFIG"));
	ui->label_10->setText(GET_TXT("IDCS_WENGEN_CONFIG"));
}

TabConnetInfoForm::~TabConnetInfoForm()
{
    delete ui;
}
