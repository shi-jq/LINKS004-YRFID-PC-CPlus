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
class SoftConfigDlg : public QDialog
{
    Q_OBJECT
    
public:
    explicit SoftConfigDlg(QWidget *parent = 0);
    ~SoftConfigDlg();
protected:
    void showEvent(QShowEvent *ev);
private:
    Ui::SoftConfigDlg *ui;
	QComboBox* m_languageCb;
	QPushButton* mSetBtn;
	QPushButton* mCancelBtn;
	QPushButton* mBrowseBtn;
	QLineEdit*   mFileNameEdit;
private:
	void initLanguageCb();//初始化支持语言combobox
	void InitSaveLogFile();
	void SetLanguageConfig();
	void SetSaveLogFile();
private slots:
	void slot_SetBtnClicked();
	void slot_CancelBtnClicked();
	void slot_BrowseBtnClicked();

};

#endif // SOFTCONFIGDLG_H
