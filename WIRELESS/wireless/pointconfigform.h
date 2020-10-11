#ifndef POINTCONFIGFORM_H
#define POINTCONFIGFORM_H

#include <QWidget>

namespace Ui {
class PointConfigForm;
}
class QPushButton;
class QComboBox;
class WirelessDeviceInfoDlg;
class PointConfigForm : public QWidget
{
    Q_OBJECT
    
public:
    explicit PointConfigForm(WirelessDeviceInfoDlg* ctrlDlg,QWidget *parent = 0);
    ~PointConfigForm();
    bool QueryAll();
	void SetRevMsg(int msgID,unsigned char bCommand,unsigned char* pData, int nLen);
private:
    Ui::PointConfigForm *ui;
	WirelessDeviceInfoDlg* mCtrlDlg;

	QPushButton*  mQueryBtn;
	QPushButton*  mSetBtn;
	QComboBox* mPortEnableCb;//功率配置
	QComboBox* m2401Cb;//射频发射功率
	QComboBox* mFreqPwrCb;//接收衰减器衰减
private slots:
	void slot_QurBtnClicked();
	void slot_SetBtnClicked();
	void slot_currentIndexChanged(int index);
};

#endif // POINTCONFIGFORM_H
