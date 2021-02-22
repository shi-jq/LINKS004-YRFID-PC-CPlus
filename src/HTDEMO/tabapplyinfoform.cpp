#include "tabapplyinfoform.h"
#include "ui_tabapplyinfoform.h"

#include "ioconfigfor6cdlg.h"

TabApplyInfoForm::TabApplyInfoForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TabApplyInfoForm)
{
    ui->setupUi(this);

	mIoConfigFor6CDlg = new IoConfigFor6CDlg(ui->widget_6);
	QGridLayout* gridLayout = new QGridLayout(ui->widget_6);
	gridLayout->setSpacing(0);
	gridLayout->setContentsMargins(0,0,0,0);
	gridLayout->addWidget(mIoConfigFor6CDlg);	
}

TabApplyInfoForm::~TabApplyInfoForm()
{
    delete ui;
}
