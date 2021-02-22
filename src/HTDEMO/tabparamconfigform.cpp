#include "tabparamconfigform.h"
#include "ui_tabparamconfigform.h"
#include "paramconfigfor6cdlg.h"

TabParamConfigForm::TabParamConfigForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TabParamConfigForm)
{
    ui->setupUi(this);
	
	mParamConfigFor6CDlg = new ParamConfigFor6CDlg(ui->widget_2);
	QGridLayout* gridLayout = new QGridLayout(ui->widget_2);
	gridLayout->setSpacing(0);
	gridLayout->setContentsMargins(0,0,0,0);
	gridLayout->addWidget(mParamConfigFor6CDlg);	
}

TabParamConfigForm::~TabParamConfigForm()
{
    delete ui;
}
