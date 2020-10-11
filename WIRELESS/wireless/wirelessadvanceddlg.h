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
   
	QString GetCheckOnlineTime();//������ʱ��
	QString GetCheckOnlineRefashTime();//���ˢ��ʱ��

	
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
