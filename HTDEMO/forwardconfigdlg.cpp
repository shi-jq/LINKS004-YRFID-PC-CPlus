#include "forwardconfigdlg.h"
#include "ui_forwardconfigdlg.h"
#include "LanguageSrc.h"
#include "appconfig.h"
#include "mainapp.h"
#include "RFIDAPIEXPORT.h"
#include "readerdllbase.h"
#include "forwardsetdlg.h"

#include <QGridLayout>

ForwardConfigDlg::ForwardConfigDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ForwardConfigDlg)
{
    ui->setupUi(this);
    this->setWindowTitle(GET_TXT("IDCS_PARAM_CONFIG_OP"));
    mForwardSetDlg = new ForwardSetDlg(ui->widget);
    QGridLayout* gridLayout = new QGridLayout(ui->widget);
    gridLayout->setSpacing(0);
    gridLayout->setContentsMargins(0,0,0,0);
    gridLayout->addWidget(mForwardSetDlg);
}

ForwardConfigDlg::~ForwardConfigDlg()
{
    delete ui;
}
