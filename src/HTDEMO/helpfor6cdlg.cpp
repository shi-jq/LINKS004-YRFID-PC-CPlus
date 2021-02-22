#include "helpfor6cdlg.h"
#include "ui_helpfor6cdlg.h"

HelpFor6cDlg::HelpFor6cDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HelpFor6cDlg)
{
    ui->setupUi(this);
}

HelpFor6cDlg::~HelpFor6cDlg()
{
    delete ui;
}
