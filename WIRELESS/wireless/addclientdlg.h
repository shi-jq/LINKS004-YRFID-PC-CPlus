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

	QWidget*	mLinkWidget; //���ӷ�ʽ�Ŀ�,���������û��Ƿ���ʹ�õ�
	QStackedWidget* mConnetStackedWidget;//tcp,com usb udp

	QComboBox* mIpAddrCb;	//tcp ip��ַ
	QComboBox* mComCb;		//����
	QComboBox* mBaudRateCb; //������

	QComboBox* mUdpIpAddrCb;	//udp ip��ַ
	QComboBox* mUsbCb;		//usb����
	QComboBox* mUsbBaudRateCb; //usb������

	QPushButton* mConnetBtn;//���Ӱ�ť
	QPushButton* mCannelBtn;//ȡ��

	QComboBox* mConnetTypeCb;//���ӷ�ʽ
private slots:
	void slot_ConnetTypeIndexChanged(int index);//��������
	void slot_connetBtnClicked();//����
	void slot_cannelBtnClicked();//ȡ��
};

#endif // ADDCLIENTDLG_H
