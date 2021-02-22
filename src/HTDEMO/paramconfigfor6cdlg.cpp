#include "paramconfigfor6cdlg.h"
#include "ui_paramconfigfor6cdlg.h"
#include <QFileDialog>
#include <QTextStream>
#include <QFile>
#include "LanguageSrc.h"
#include "appconfig.h"
#include "mainapp.h"
#include "RFIDAPIEXPORT.h"
#include "readerdllbase.h"
#include "paramadd6cdlg.h"


ParamConfigFor6CDlg::ParamConfigFor6CDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ParamConfigFor6CDlg)
{
    ui->setupUi(this);
	this->setWindowTitle(GET_TXT("IDCS_PARAM_CONFIG_OP"));
	mParamAdd6CDlg = new ParamAdd6CDlg(ui->widget);
	QGridLayout* gridLayout = new QGridLayout(ui->widget);
	gridLayout->setSpacing(0);
	gridLayout->setContentsMargins(0,0,0,0);
	gridLayout->addWidget(mParamAdd6CDlg);	
}

ParamConfigFor6CDlg::~ParamConfigFor6CDlg()
{
    delete ui;
}

