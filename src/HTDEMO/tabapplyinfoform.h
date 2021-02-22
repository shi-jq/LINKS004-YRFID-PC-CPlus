#ifndef TABAPPLYINFOFORM_H
#define TABAPPLYINFOFORM_H

#include <QWidget>

namespace Ui {
class TabApplyInfoForm;
}
class IoConfigFor6CDlg;
class TabApplyInfoForm : public QWidget
{
    Q_OBJECT
    
public:
    explicit TabApplyInfoForm(QWidget *parent = 0);
    ~TabApplyInfoForm();
    
private:
    Ui::TabApplyInfoForm *ui;
	IoConfigFor6CDlg* mIoConfigFor6CDlg;
};

#endif // TABAPPLYINFOFORM_H
