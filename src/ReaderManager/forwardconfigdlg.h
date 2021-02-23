#ifndef FORWARDCONFIGDLG_H
#define FORWARDCONFIGDLG_H

#include <QWidget>

namespace Ui {
class ForwardConfigDlg;
}

class ForwardSetDlg;

class ForwardConfigDlg : public QWidget
{
    Q_OBJECT

public:
    explicit ForwardConfigDlg(QWidget *parent = nullptr);
    ~ForwardConfigDlg();

private:
    Ui::ForwardConfigDlg *ui;
    ForwardSetDlg* mForwardSetDlg;
};

#endif // FORWARDCONFIGDLG_H
