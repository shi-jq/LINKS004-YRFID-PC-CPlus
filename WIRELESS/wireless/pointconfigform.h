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
	QComboBox* mPortEnableCb;//��������
	QComboBox* m2401Cb;//��Ƶ���书��
	QComboBox* mFreqPwrCb;//����˥����˥��
private slots:
	void slot_QurBtnClicked();
	void slot_SetBtnClicked();
	void slot_currentIndexChanged(int index);
};

#endif // POINTCONFIGFORM_H
