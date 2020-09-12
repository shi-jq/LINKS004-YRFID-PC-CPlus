#include "tabforwardconfigform.h"
#include "ui_tabforwardconfigform.h"
#include "forwardconfigdlg.h"
#include <QGridLayout>

TabForwardConfigForm::TabForwardConfigForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TabForwardConfigForm)
{
    ui->setupUi(this);
    mForwardConfigDlg = new ForwardConfigDlg(ui->widget_2);
    QGridLayout* gridLayout = new QGridLayout(ui->widget_2);
    gridLayout->setSpacing(0);
    gridLayout->setContentsMargins(0,0,0,0);
    gridLayout->addWidget(mForwardConfigDlg);
}

TabForwardConfigForm::~TabForwardConfigForm()
{
    delete ui;
}
