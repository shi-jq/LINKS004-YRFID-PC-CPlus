#ifndef WIRELESSSYSINFOWIDGET_H
#define WIRELESSSYSINFOWIDGET_H

#include <QDialog>

namespace Ui {
class wirelessSysInfoWidget;
}
class QLabel;
class WirelessDeviceInfoDlg;
class QTimeEdit;
class QDateEdit;
class QComboBox;
class QLineEdit;

class WirelessSysinfoWidget : public QDialog
{
    Q_OBJECT    
public:
    explicit WirelessSysinfoWidget(WirelessDeviceInfoDlg* ctrlDlg,QWidget *parent = 0);
    ~WirelessSysinfoWidget();
	void SetRevMsg(int msgID,unsigned char bCommand,unsigned char* pData, int nLen);
protected:
	 
private:
    Ui::wirelessSysInfoWidget *ui;
	WirelessDeviceInfoDlg* mCtrlDlg;
	QPushButton* mQueryBtn;
	QComboBox* mQueryTypeCb;
	QLineEdit* mQueryResultEdit;

	QTimeEdit* mTimeEdit;
	QDateEdit* mDateEidt;
	QPushButton* mQueryTimeBtn;
	QPushButton* mSetTimeBtn;
	QPushButton* mGetCurtimeBtn;
private:
	unsigned int C16Convert10(int a);
	unsigned int C10Convert16(int a);

	bool QueryDeviceName();	//设备名称
	bool QuerySN(); //产品序列号
	bool QueryDeviceType();//设备类型
	bool QueryMCUVer();//固件版本
	bool QueryHardwareVer();//硬件版本

	int mParam;
	
private slots:
	void slot_QueryBtnClicked();

	void slot_QueryTimeBtnClicked();
	void slot_SetBtnTimeClicked();
	void slot_GetCurtimeBtnClicked();
};

#endif // WIRELESSSYSINFOWIDGET_H