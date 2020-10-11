#ifndef PROGRESSBARDLG_H
#define PROGRESSBARDLG_H

#include <QDialog>

namespace Ui {
class ProgressBarDlg;
}

class ProgressBarDlg : public QDialog
{
    Q_OBJECT
    
public:
    explicit ProgressBarDlg(QWidget *parent = 0);
    ~ProgressBarDlg();
    
private:
    Ui::ProgressBarDlg *ui;
};

#endif // PROGRESSBARDLG_H
