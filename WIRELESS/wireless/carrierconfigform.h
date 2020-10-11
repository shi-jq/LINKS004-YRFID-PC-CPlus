#ifndef CARRIERCONFIGFORM_H
#define CARRIERCONFIGFORM_H

#include <QWidget>

namespace Ui {
class CarrierConfigForm;
}
class QComboBox;
class QPushButton;
class WirelessDeviceInfoDlg;
class CarrierConfigForm : public QWidget
{
    Q_OBJECT
    
public:
    explicit CarrierConfigForm(WirelessDeviceInfoDlg* ctrlDlg,QWidget *parent = 0);
    ~CarrierConfigForm();
    bool QueryAll();
	void SetRevMsg(int msgID,unsigned char bCommand,unsigned char* pData, int nLen);
private:
    Ui::CarrierConfigForm *ui;
	WirelessDeviceInfoDlg* mCtrlDlg;

	QComboBox*  mCarrierCb;
	QPushButton* mQueryBtn;
	QPushButton* mSetBtn;
private slots:
	void slot_QurBtnClicked();
	void slot_SetBtnClicked();
};

#endif // CARRIERCONFIGFORM_H
