#include "versioncommondlg.h"
#include "ui_versioncommondlg.h"
#include "LanguageSrc.h"
#include "mainapp.h"
#include "RFIDAPIEXPORT.h"

VersionCommonDlg::VersionCommonDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VersionCommonDlg)
{
    ui->setupUi(this);
	this->setWindowTitle(GET_TXT("IDCS_SOFT_VER"));
	ui->label->setText(GET_TXT("IDCS_SOFT_VER"));
	ui->label_2->setText(GET_TXT("IDCS_API_VER"));
	mApiLabel = ui->label_9;
	mSoftLabel = ui->label_8;
	mSoftCreateTimeLabel = ui->label_5;

}

VersionCommonDlg::~VersionCommonDlg()
{
    delete ui;
}

void VersionCommonDlg::showEvent(QShowEvent *ev)
{
	mSoftLabel->setText(QString("%1").arg(SOFT_VERSION));

	mSoftCreateTimeLabel->setText(QString("%1 %2")
		.arg(QString::fromLocal8Bit(__DATE__))
		.arg(QString::fromLocal8Bit(__TIME__)));

	char apiVer[255] = {0};
	if (SAAT_Copyright(NULL,apiVer))
	{
		mApiLabel->setText(QString::fromUtf8(apiVer));
	}
	else
	{
		mApiLabel->setText("-");
	}

	QDialog::showEvent(ev);
}
