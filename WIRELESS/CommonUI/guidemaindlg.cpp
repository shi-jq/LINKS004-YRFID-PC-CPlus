#include "guidemaindlg.h"
#include "ui_guidemaindlg.h"

GuideMainDlg::GuideMainDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GuideMainDlg)
{
    ui->setupUi(this);
}

GuideMainDlg::~GuideMainDlg()
{
    delete ui;
}
