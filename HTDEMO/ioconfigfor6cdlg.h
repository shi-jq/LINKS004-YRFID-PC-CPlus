#ifndef IOCONFIGFOR6CDLG_H
#define IOCONFIGFOR6CDLG_H

#include <QWidget>

namespace Ui {
class IoConfigFor6CDlg;
}
class QLineEdit;
class QPushButton;
class QComboBox;
class QCheckBox;
class QSpinBox;

class IoConfigFor6CDlg : public QWidget
{
    Q_OBJECT
    
public:
    explicit IoConfigFor6CDlg(QWidget *parent = 0);
    ~IoConfigFor6CDlg();
protected:
	void showEvent(QShowEvent *event);  
private:
    Ui::IoConfigFor6CDlg *ui;
	QLineEdit* mPutIn0Edit;
	QLineEdit* mPutIn1Edit;
	QPushButton* mQueryInBtn;

	QComboBox* mPutout1CB;
	QComboBox* mPutout2CB;
	QComboBox* mPutout3CB;
	QComboBox* mPutout4CB;
	QPushButton* mPutout1Btn;
	QPushButton* mPutout2Btn;
	QPushButton* mPutout3Btn;
	QPushButton* mPutout4Btn;

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
	QPushButton* mCtrlOutQueryBtn;
	QPushButton* mCtrlOutSetBtn;

	bool mFirst;
private:
	bool InquireIO();
	bool InquirePulseWidth();
	bool IOPulseWidthUISet(unsigned char nPort,unsigned char nWidth);

	bool SetPulseWidth();
	bool SetReadingIO();	

	bool QueryOutPutAll();
private slots:
	void slot_QueryInBtnClicked();
	void slot_Putout1BtnClicked();
	void slot_Putout2BtnClicked();
	void slot_Putout3BtnClicked();
	void slot_Putout4BtnClicked();

	void slot_CtrlOutQueryBtnClicked();
	void slot_CtrlOutSetBtnClicked();
};

#endif // IOCONFIGFOR6CDLG_H
