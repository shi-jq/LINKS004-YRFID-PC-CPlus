#ifndef WIRELESSREADPARAMWIDGET_H
#define WIRELESSREADPARAMWIDGET_H

#include <QDialog>

namespace Ui {
class wirelessreadparamwidget;
}
class QLabel;
class QCheckBox;
class QPushButton;
class QLineEdit;
class WirelessDeviceInfoDlg;
class QComboBox;
class WirelessReadParamWidget : public QDialog
{
    Q_OBJECT
    
public:
    explicit WirelessReadParamWidget(WirelessDeviceInfoDlg* ctrlDlg,QWidget *parent = 0);
    ~WirelessReadParamWidget();
    void SetRevMsg(int msgID,unsigned char bCommand,unsigned char* pData, int nLen);
private:
    Ui::wirelessreadparamwidget *ui;
	WirelessDeviceInfoDlg* mCtrlDlg;

	QPushButton* mFlashEnableBtn;
	QPushButton* mFlashEnableQueryBtn;
	QPushButton* mFlashTagCountBtn;
	QPushButton* mFlashTagClearBtn;
	QPushButton* mFilterEnableBtn;
	QPushButton* mFilterQueryBtn;
	QPushButton* mFilterTimeBtn;
	QPushButton* mQueryFilterTimeBtn;


	QCheckBox* mFlashEnableCb;
	QLabel* mTagCountLb;
	QCheckBox* mFilterEnableCb;
	QLineEdit* mFilterTimeEdit;
	
	int mMsgID;
	int mOperType;
	enum
	{
		OP_FLASH_ENABLE,
		OP_FLASH_COUNT,
		OP_FLASH_CLEAR,
		OP_FLITER_ENABLE,
		OP_FILTER_TIME,
		OP_QUERYFILTER_TIME,
		OP_QUERY_FLASH_ENABLE,
		OP_QUERY_FLITER_ENABLE,
		OP_QUERY_READERSPACETIME,
		OP_SET_READERSPACETIME,
		OP_SET_WORKMODE,
		OP_QUERY_WORKMODE,
		OP_QUERY_CONNETVALUE,
		OP_SET_CONNETVALUE,
	};
private slots:
	void slot_FlashEnableBtnClicked();
	void slot_FlashTagCountBtnClicked();
	void slot_FlashTagClearBtnClicked();
	void slot_FilterEnableBtnClicked();
	void slot_FilterTimeBtnClicked();
	void slot_QueryFilterTimeBtnClicked();
	void slot_QueryFlashEnable();
	void slot_QueryFilter();
};

#endif // WIRELESSREADPARAMWIDGET_H