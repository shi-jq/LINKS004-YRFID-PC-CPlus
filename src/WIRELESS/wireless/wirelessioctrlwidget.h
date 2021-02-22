#ifndef WIRELESSIOCTRLWIDGET_H
#define WIRELESSIOCTRLWIDGET_H

#include <QDialog>

namespace Ui {
class wirelessioctrlwidget;
}

class QLabel;
class QComboBox;
class QPushButton;
class QCheckBox;
class QSpinBox;

class WirelessDeviceInfoDlg;
class WirelessIOCtrlWidget : public QDialog
{
    Q_OBJECT
    
public:
    explicit WirelessIOCtrlWidget(WirelessDeviceInfoDlg* ctrlDlg,QWidget *parent = 0);
    ~WirelessIOCtrlWidget();
     void SetRevMsg(int msgID,unsigned char bCommand,unsigned char* pData, int nLen);
private:
    Ui::wirelessioctrlwidget *ui;
	WirelessDeviceInfoDlg* mCtrlDlg;
	QComboBox* mPort1Cb;
	QComboBox* mPort2Cb;
	QComboBox* mPort3Cb;
	QComboBox* mPort4Cb;
	QPushButton* mPort1Btn;
	QPushButton* mPort2Btn;
	QPushButton* mPort3Btn;
	QPushButton* mPort4Btn;

	QCheckBox* mOutBuzzerCb;
	QCheckBox* mCtrOut1Cb;
	QCheckBox* mCtrOut2Cb;
	QCheckBox* mCtrOut3Cb;
	QCheckBox* mCtrOut4Cb;
	QSpinBox* mOutBuzzerSb;
	QSpinBox* mCtrlOut1Sb;
	QSpinBox* mCtrlOut2Sb;
	QSpinBox* mCtrlOut3Sb;
	QSpinBox* mCtrlOut4Sb;
	//QPushButton* mCtrlOutQueryBtn;
	QPushButton* mCtrlOutSetBtn;

	QPushButton* mQueryWith1Btn;
	QPushButton* mQueryWith2Btn;
	QPushButton* mQueryWith3Btn;
	QPushButton* mQueryWith4Btn;
	QPushButton* mQueryWith5Btn;

	QPushButton* mOperBtn;
private:
	void startPort(int nPort,int nState);

	bool InquireIO();
	bool InquirePulseWidth();
	bool IOPulseWidthUISet(unsigned char nPort,unsigned char nWidth);

	bool SetPulseWidth();
	bool SetReadingIO();
private slots:
	void slot_StartPort1Clicked();
	void slot_StartPort2Clicked();
	void slot_StartPort3Clicked();
	void slot_StartPort4Clicked();
	

	//void slot_CtrlOutQueryBtnClicked();
	void slot_CtrlOutSetBtnClicked();

	void slot_CtrlOutSet1Clicked();
	void slot_CtrlOutSet2Clicked();
	void slot_CtrlOutSet3Clicked();
	void slot_CtrlOutSet4Clicked();
	void slot_CtrlOutSet5Clicked();
};

#endif // WIRELESSIOCTRLWIDGET_H