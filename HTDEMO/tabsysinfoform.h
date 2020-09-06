#ifndef TABSYSINFOFORM_H
#define TABSYSINFOFORM_H

#include <QWidget>

namespace Ui {
class TabSysInfoForm;
}

class ReaderInfo6CForm;
class FirmWareUpdateFor6CDlg;
class R2000LogDlg;
class ReaderTimeSetDlg;
class RebootDeviceForm;
class TabSysInfoForm : public QWidget
{
    Q_OBJECT
    
public:
    explicit TabSysInfoForm(QWidget *parent = 0);
    ~TabSysInfoForm();
    
private:
    Ui::TabSysInfoForm *ui;
	ReaderInfo6CForm* mReaderInfo6CForm;
	FirmWareUpdateFor6CDlg* mFirmWareUpdateFor6CDlg;
	ReaderTimeSetDlg* mReaderTimeSetDlg;
	//RebootDeviceForm* mRebootDeviceForm;

};

#endif // TABSYSINFOFORM_H
