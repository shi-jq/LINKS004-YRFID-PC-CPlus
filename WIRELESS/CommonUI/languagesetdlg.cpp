#include "languagesetdlg.h"
#include "ui_languagesetdlg.h"

LanguageSetDlg::LanguageSetDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LanguageSetDlg)
{
    ui->setupUi(this);
}

LanguageSetDlg::~LanguageSetDlg()
{
    delete ui;
}
