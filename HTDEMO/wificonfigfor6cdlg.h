#ifndef WIFICONFIGFOR6CDLG_H
#define WIFICONFIGFOR6CDLG_H

#include <QDialog>

namespace Ui {
class WIFIConfigFor6CDLg;
}
class QLineEdit;
class QComboBox;
class QCheckBox;
class QLabel;
class WifiSelectDlg;
class QWidget;
class WIFIConfigFor6CDLg : public QDialog
{
    Q_OBJECT
    
public:
    explicit WIFIConfigFor6CDLg(QWidget *parent = 0);
    ~WIFIConfigFor6CDLg();
protected:
	void showEvent(QShowEvent *ev);
	void closeEvent(QCloseEvent *ev);
private:
	bool EnterTrans();//����͸��ģʽ
	bool ExitTrans();//�˳�͸��ģʽ

	bool QueryNetPram();
	bool QuerySSID();
	bool QuerySecureType();
	bool QueryKey();
	bool QueryMac();
	bool QuerySocketConnectInfo();
	bool QueryWorkMode();

	bool SetNetPram();
	bool SetSSID();
	bool SetSecureType();
	bool SetKey();

	bool SetSocketConnectInfo();

	void SetViewEnable(bool isEnable);

	bool CheckIPEdit(const QString& str);

private:
    Ui::WIFIConfigFor6CDLg *ui;

	QWidget* mBg1;
	QWidget* mBg2;
	QWidget* mBg3;

	QCheckBox* mAutoGetIpCb;//�Զ���ȡIP
	QLineEdit* mIpAddrEdit; //ip��ַ
	QLineEdit* mMaskEdit;//��������
	QLineEdit* mGatewayEdit;//����
	QLineEdit* mDNSEdit;//DNS
	QLineEdit* mMacEdit;//mac
	
	QPushButton* mNetQueryBtn;
	QPushButton* mNetSetBtn;

	QLineEdit* mSSIDEdit;//ssid
	QComboBox* mSModelCb;//��ȫģʽ
	QComboBox* mPwdFomortCb;//��Կ��ʽ
	QComboBox* mPwdIndexCb;//��Կ����
	QLineEdit* mPwdEdit;//��Կ

	QPushButton* mWirelessQueryBtn;
	QPushButton* mWirelessSetBtn;

	QCheckBox* mAutoWorkModel;//�Զ�����ģʽ
	QComboBox* mProtocolCb;//Э��
	QComboBox* mCSModelCb;//csģʽ
	QLineEdit* mServerEdit;//��������ַ
	QLineEdit* mServerPortEdit;//�������˿�
	QPushButton* mModelQueryBtn;
	QPushButton* mModelSetBtn;

	QPushButton* mSelectSSIDBtn;
	QPushButton* mQueryStateBtn;
	QPushButton* mResetBtn;
	QLabel* mStateLabel;
	QLabel* mEnterTransFailedTig;

	QPushButton* mEnterTransBtn;
	QPushButton* mExitTransBtn;

	WifiSelectDlg* mWifiSelectDlg;
private slots:
	void slot_NetQueryBtnClicked();
	void slot_NetSetBtnClicked();
	void slot_WirelessQueryBtnClicked();
	void slot_WirelessSetBtnClicked();
	void slot_ModelQueryBtnClicked();
	void slot_ModelSetBtnClicked();
	void slot_SelectSSIDBtnClicked();
	void slot_QueryStateBtnClicked();
	void slot_ResetBtnClicked();
	void slot_EnterTransBtnClicked();
	void slot_ExitTransBtnClicked();
	void slot_SModelCbIndexChange(int index);
};

#endif // WIFICONFIGFOR6CDLG_H
