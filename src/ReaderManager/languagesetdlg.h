#ifndef LANGUAGESETDLG_H
#define LANGUAGESETDLG_H

#include <QDialog>

namespace Ui {
class LanguageSetDlg;
}

class LanguageSetDlg : public QDialog
{
    Q_OBJECT
    
public:
    explicit LanguageSetDlg(QWidget *parent = 0);
    ~LanguageSetDlg();
    
private:
    Ui::LanguageSetDlg *ui;
};

#endif // LANGUAGESETDLG_H
