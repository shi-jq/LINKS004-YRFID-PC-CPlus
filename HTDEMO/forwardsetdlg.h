#ifndef FORWARDSETDLG_H
#define FORWARDSETDLG_H

#include <QWidget>

namespace Ui {
class ForwardSetDlg;
}
class QPushButton;
class QLineEdit;
class QComboBox;

class ForwardSetDlg : public QWidget
{
    Q_OBJECT

public:
    explicit ForwardSetDlg(QWidget *parent = nullptr);
    ~ForwardSetDlg();

private:
    Ui::ForwardSetDlg *ui;

    QPushButton *mReadForwardBtn;
    QPushButton *mWriteForwardBtn;
    QComboBox *mForwardChanCbx;
    QLineEdit *mIpEdit;
    QLineEdit *mPortEdit;

private slots:

    void slot_ReadForwardBtnClicked();
    void slot_WriteForwardBtnClicked();
private:
    bool CheckIPEdit(const QString& str);//检查ip地址是否合法
};

#endif // FORWARDSETDLG_H
