#ifndef ANTENNAPRMFORM_H
#define ANTENNAPRMFORM_H

#include <QWidget>

namespace Ui {
class AntennaPrmForm;
}
class QPushButton;
class QCheckBox;
class QSpinBox;
class WirelessDeviceInfoDlg;
class AntennaPrmForm : public QWidget
{
    Q_OBJECT
    
public:
    explicit AntennaPrmForm(WirelessDeviceInfoDlg* ctrlDlg,QWidget *parent = 0);
    ~AntennaPrmForm();

	bool QurAntenna();   
	void SetRevMsg(int msgID,unsigned char bCommand,unsigned char* pData, int nLen);
private:
    Ui::AntennaPrmForm *ui;
	WirelessDeviceInfoDlg* mCtrlDlg;

	QPushButton* mQurAntennaBtn;//���ð�ť
	QPushButton* mSetAntennaBtn;//��ѯ��ť

	QCheckBox* mAntenna1CheckBox;//����1234
	QCheckBox* mAntenna2CheckBox;
	QCheckBox* mAntenna3CheckBox;
	QCheckBox* mAntenna4CheckBox;

	QSpinBox* mAntenna1TimeSb;//����ʹ��ʱ��1234
	QSpinBox* mAntenna2TimeSb;
	QSpinBox* mAntenna3TimeSb;
	QSpinBox* mAntenna4TimeSb;

	
	bool SetAntenna();
private slots:
	void slot_QurAntennaBtnClicked();
	void slot_SetAntennaBtnClicked();
};

#endif // ANTENNAPRMFORM_H
