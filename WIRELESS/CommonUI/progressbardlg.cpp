#include "progressbardlg.h"
#include "ui_progressbardlg.h"

ProgressBarDlg::ProgressBarDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProgressBarDlg)
{
    ui->setupUi(this);
}

ProgressBarDlg::~ProgressBarDlg()
{
    delete ui;
}
