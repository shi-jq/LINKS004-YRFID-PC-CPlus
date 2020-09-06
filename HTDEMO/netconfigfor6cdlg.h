#ifndef NETCONFIGFOR6CDLG_H
#define NETCONFIGFOR6CDLG_H

#include <QWidget>

namespace Ui {
class NetConfigFor6CDlg;
}
class QLineEdit;
class QPushButton;

class NetConfigFor6CDlg : public QWidget
{
    Q_OBJECT
    
public:
    explicit NetConfigFor6CDlg(QWidget *parent = 0);
    ~NetConfigFor6CDlg();
    
private:
    Ui::NetConfigFor6CDlg *ui;
	QLineEdit* mIpAddrEdit;
	QLineEdit* mMaskEdit;
	QLineEdit* mGatewayEdit;
	QLineEdit* mUdpEdit;
	QLineEdit* mTcpEdit;
	QLineEdit* mMacEdit;
	QPushButton* mQurBtn;
	QPushButton* mSetBtn;

	bool mFirst;
protected:
	void showEvent(QShowEvent *event);
private:
	bool QueryAll();
	bool QueryIp();
	bool QueryUdpPort();
	bool QueryTcpPort();
	bool QueryMac();

	bool SetAll();
	bool SetIp();
	bool SetUdpPort();
	bool SetTcpPort();
	bool SetMac();

	bool CheckIPEdit(const QString& str);
private slots:
	void slot_QueryBtnClicked();
	void slot_SetBtnClicked();
	
};

#endif // NETCONFIGFOR6CDLG_H
