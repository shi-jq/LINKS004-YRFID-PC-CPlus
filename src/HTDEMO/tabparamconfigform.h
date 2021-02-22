#ifndef TABPARAMCONFIGFORM_H
#define TABPARAMCONFIGFORM_H

#include <QWidget>

namespace Ui {
class TabParamConfigForm;
}
class ParamConfigFor6CDlg;
class CarrierWaveFor6CDlg;
class TabParamConfigForm : public QWidget
{
    Q_OBJECT
    
public:
    explicit TabParamConfigForm(QWidget *parent = 0);
    ~TabParamConfigForm();
    
private:
    Ui::TabParamConfigForm *ui;
	ParamConfigFor6CDlg* mParamConfigFor6CDlg;
};

#endif // TABPARAMCONFIGFORM_H
