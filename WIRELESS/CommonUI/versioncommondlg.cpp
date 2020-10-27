#include "versioncommondlg.h"
#include "ui_versioncommondlg.h"
#include "LanguageSrc.h"
#include "mainapp.h"


VersionCommonDlg::VersionCommonDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VersionCommonDlg)
{
    ui->setupUi(this);
	this->setWindowTitle(GET_TXT("IDCS_SOFT_VER"));
	ui->label->setText(GET_TXT("IDCS_SOFT_VER"));
	ui->label_4->setText(GET_TXT("IDCS_SOFT_MAKE_TIME"));
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

	QDialog::showEvent(ev);
}
