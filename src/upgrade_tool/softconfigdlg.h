#ifndef SOFTCONFIGDLG_H
#define SOFTCONFIGDLG_H

#include <QDialog>
#include <map>

namespace Ui {
class SoftConfigDlg;
}
class QComboBox;
class QPushButton;
class QRadioButton;
class QCheckBox;
class QLineEdit;
class adb_tool;
class SoftConfigDlg : public QDialog
{
    Q_OBJECT
    
public:
    explicit SoftConfigDlg(QWidget *parent = 0);
    ~SoftConfigDlg();
	void setMainwindow(adb_tool* tool);
protected:
    void showEvent(QShowEvent *ev);
private:
    Ui::SoftConfigDlg *ui;
    QComboBox* m_languageCb;
    QPushButton* mSetBtn;
    QPushButton* mCancelBtn;

	adb_tool* mainwindow;
private:
	void initLanguageCb();//初始化支持语言combobox
	void InitPagActy();
	void SetLanguageConfig();

private slots:
	void slot_SetBtnClicked();
    void slot_CancelBtnClicked();

};

#endif // SOFTCONFIGDLG_H
