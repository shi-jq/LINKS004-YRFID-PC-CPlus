#ifndef HELPFOR6CDLG_H
#define HELPFOR6CDLG_H

#include <QDialog>

namespace Ui {
class HelpFor6cDlg;
}

class HelpFor6cDlg : public QDialog
{
    Q_OBJECT
    
public:
    explicit HelpFor6cDlg(QWidget *parent = 0);
    ~HelpFor6cDlg();
    
private:
    Ui::HelpFor6cDlg *ui;
};

#endif // HELPFOR6CDLG_H
