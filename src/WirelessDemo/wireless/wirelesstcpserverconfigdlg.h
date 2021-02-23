#ifndef WIRELESSTCPSERVERCONFIGDLG_H
#define WIRELESSTCPSERVERCONFIGDLG_H

#include <QDialog>
class QPushButton;
class QComboBox;
class QLineEdit;
namespace Ui {
class WirelessTcpServerConfigDlg;
}

class WirelessTcpServerConfigDlg : public QDialog
{
    Q_OBJECT
    
public:
    explicit WirelessTcpServerConfigDlg(QWidget *parent = 0);
    ~WirelessTcpServerConfigDlg();

	QString GetServerIp();
	QString GetServerPort();

protected:
	void closeEvent ( QCloseEvent * e );

private:
    Ui::WirelessTcpServerConfigDlg *ui;
	QComboBox* mServerAddrCb;
	QLineEdit* mServerPortEdit;
	QPushButton* mOkBtn;
	QPushButton* mCannelBtn;
private slots:
	void slot_OkBtnClicked();
	void slot_CannelBtnClicked();
};

#endif // WIRELESSTCPSERVERCONFIGDLG_H
