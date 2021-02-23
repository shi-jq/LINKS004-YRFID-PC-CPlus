#ifndef WIRELESSREADCONFIGWIDGET_H
#define WIRELESSREADCONFIGWIDGET_H

#include <QDialog>

namespace Ui {
class wirelessreadconfigwidget;
}
class QLabel;
class QPushButton;
class QCheckBox;
class QComboBox;
class QListWidget;
class QTextEdit;
class QListWidgetItem;
class QSpinBox;
class WirelessDeviceInfoDlg;
class AntennaPrmForm;
class CarrierConfigForm;
class PointConfigForm;
class WirelessReadConfigWidget : public QDialog
{
    Q_OBJECT
    
public:
    explicit WirelessReadConfigWidget(WirelessDeviceInfoDlg* ctrlDlg,QWidget *parent = 0);
    ~WirelessReadConfigWidget();
	void CreateView();
	void updateLanguage();

	 void SetRevMsg(int msgID,unsigned char bCommand,unsigned char* pData, int nLen);
private:
    Ui::wirelessreadconfigwidget *ui;
	WirelessDeviceInfoDlg* mCtrlDlg;

	int  mMsgID;

	AntennaPrmForm* mAntennaPrmForm;
	CarrierConfigForm* mCarrierConfigForm;
	PointConfigForm* mPointConfigForm;
private slots:
	
};

#endif // WIRELESSREADCONFIGWIDGET_H