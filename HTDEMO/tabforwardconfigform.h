#ifndef TABFORWARDCONFIGFORM_H
#define TABFORWARDCONFIGFORM_H

#include <QWidget>

namespace Ui {
class TabForwardConfigForm;
}

class ForwardConfigDlg;


class TabForwardConfigForm : public QWidget
{
    Q_OBJECT

public:
    explicit TabForwardConfigForm(QWidget *parent = nullptr);
    ~TabForwardConfigForm();

private:
    Ui::TabForwardConfigForm *ui;

    ForwardConfigDlg* mForwardConfigDlg;
};

#endif // TABFORWARDCONFIGFORM_H
