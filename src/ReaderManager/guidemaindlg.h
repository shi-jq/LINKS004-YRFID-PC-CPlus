#ifndef GUIDEMAINDLG_H
#define GUIDEMAINDLG_H

#include <QDialog>

namespace Ui {
class GuideMainDlg;
}

class GuideMainDlg : public QDialog
{
    Q_OBJECT
    
public:
    explicit GuideMainDlg(QWidget *parent = 0);
    ~GuideMainDlg();
    
private:
    Ui::GuideMainDlg *ui;
};

#endif // GUIDEMAINDLG_H
