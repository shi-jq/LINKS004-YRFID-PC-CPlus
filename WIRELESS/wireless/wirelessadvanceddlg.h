#ifndef WIRELESSADVANCEDDLG_H
#define WIRELESSADVANCEDDLG_H

#include <QDialog>
class QPushButton;
class QComboBox;
class QLineEdit;
class QCheckBox;


namespace Ui {
class WirelessAdvancedDlg;
}

class WirelessAdvancedDlg : public QDialog
{
    Q_OBJECT    
public:
    explicit WirelessAdvancedDlg(QWidget *parent = 0);
    ~WirelessAdvancedDlg();
   
	QString GetCheckOnlineTime();//检测断线时间
	QString GetCheckOnlineRefashTime();//检测刷新时间

	
protected:
	void closeEvent ( QCloseEvent * e );
private: 
    Ui::WirelessAdvancedDlg *ui;
	
	QLineEdit* mCheckConnetTimeEdit;
	QLineEdit* mCheckRefashTimeEdit;
	QPushButton* mOkBtn;
	QPushButton* mCannelBtn;
	
private slots:
	void slot_OkBtnClicked();
	void slot_CannelBtnClicked();

};

#endif // WIRELESSADVANCEDDLG_H
