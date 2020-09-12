#ifndef TABCONNETINFOFORM_H
#define TABCONNETINFOFORM_H

#include <QWidget>

namespace Ui {
class TabConnetInfoForm;
}
class NetConfigFor6CDlg;
class ComConfigDlg;
class BusAddrConfigDlg;
class WeiGenConfigForm;
class TabConnetInfoForm : public QWidget
{
    Q_OBJECT
    
public:
    explicit TabConnetInfoForm(QWidget *parent = 0);
    ~TabConnetInfoForm();
    
private:
    Ui::TabConnetInfoForm *ui;
	NetConfigFor6CDlg* mNetConfigFor6CDlg;
	ComConfigDlg* mComConfigDlg;
	BusAddrConfigDlg* mBusAddrConfigDlg;
	WeiGenConfigForm* mWeiGenConfigForm;
};

#endif // TABCONNETINFOFORM_H
