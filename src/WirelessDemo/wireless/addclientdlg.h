#ifndef ADDCLIENTDLG_H
#define ADDCLIENTDLG_H

#include <QDialog>

namespace Ui {
class AddClientDlg;
}
class QWidget;
class QStackedWidget;
class QComboBox;
class QPushButton;
class AddClientDlg : public QDialog
{
    Q_OBJECT
    
public:
    explicit AddClientDlg(QWidget *parent = 0);
    ~AddClientDlg();
    
	enum ConnetType
	{
		Connet_TCP,
		Connet_COM,
		Connet_USB,
		Connet_UDP
	};
private:
    Ui::AddClientDlg *ui;

	QWidget*	mLinkWidget; //连接方式的框,用来控制用户是否能使用的
	QStackedWidget* mConnetStackedWidget;//tcp,com usb udp

	QComboBox* mIpAddrCb;	//tcp ip地址
	QComboBox* mComCb;		//串口
	QComboBox* mBaudRateCb; //波特率

	QComboBox* mUdpIpAddrCb;	//udp ip地址
	QComboBox* mUsbCb;		//usb串口
	QComboBox* mUsbBaudRateCb; //usb波特率

	QPushButton* mConnetBtn;//连接按钮
	QPushButton* mCannelBtn;//取消

	QComboBox* mConnetTypeCb;//连接方式
private slots:
	void slot_ConnetTypeIndexChanged(int index);//连接类型
	void slot_connetBtnClicked();//连接
	void slot_cannelBtnClicked();//取消
};

#endif // ADDCLIENTDLG_H
