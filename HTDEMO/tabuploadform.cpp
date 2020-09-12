#include "tabuploadform.h"
#include "ui_tabuploadform.h"
#include "filtratetagfor6cdlg.h"
#include "flashconfigfor6cdlg.h"
#include "uploadpramform.h"
#include "forwardsetdlg.h"
TabUploadForm::TabUploadForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TabUploadForm)
{
    ui->setupUi(this);

	mFiltrateTagFor6CDlg = new FiltrateTagFor6CDlg(ui->widget_4);
	QGridLayout* gridLayout = new QGridLayout(ui->widget_4);
	gridLayout->setSpacing(0);
	gridLayout->setContentsMargins(0,0,0,0);
	gridLayout->addWidget(mFiltrateTagFor6CDlg);	

	mFlashConfigFor6CDlg = new FlashConfigFor6CDlg(ui->widget_6);
	gridLayout = new QGridLayout(ui->widget_6);
	gridLayout->setSpacing(0);
	gridLayout->setContentsMargins(0,0,0,0);
	gridLayout->addWidget(mFlashConfigFor6CDlg);

	mUploadPramForm = new UploadPramForm(ui->widget_2);
	gridLayout = new QGridLayout(ui->widget_2);
	gridLayout->setSpacing(0);
	gridLayout->setContentsMargins(0,0,0,0);
	gridLayout->addWidget(mUploadPramForm);	


	mForwardSetDlg = new ForwardSetDlg(ui->widget_8);
	gridLayout = new QGridLayout(ui->widget_8);
	gridLayout->setSpacing(0);
	gridLayout->setContentsMargins(0, 0, 0, 0);
	gridLayout->addWidget(mForwardSetDlg);

	ui->widget_5->hide();
}

TabUploadForm::~TabUploadForm()
{
    delete ui;
}
