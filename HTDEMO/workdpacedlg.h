#ifndef WORKDPACEDLG_H
#define WORKDPACEDLG_H

#include <QWidget>
#include <QFrame>
#include <QTabWidget>

class ReaderDllBase;

namespace Ui {
class workDpaceDlg;
}
class QPushButton;
class QTabWidget;
class ReadCardFor6CDlg;
class ReadConfigFor6CDlg;
class TagOpFor6CDlg;
class TabSysInfoForm;
class TabConnetInfoForm;
class TabApplyInfoForm;
class TabParamConfigForm;
class TabUploadForm;
class workDpaceDlg : public QFrame
{
    Q_OBJECT
    
public:
    explicit workDpaceDlg(QWidget *parent = 0);
    ~workDpaceDlg();
	
	void setDownBtnUp(bool isDown);
	void setLeftBtnRight(bool left);

private:
    Ui::workDpaceDlg *ui;
	QTabWidget* mTabWidget;
	ReadCardFor6CDlg* mReadCardFor6CDlg;
	ReadConfigFor6CDlg* mReadConfigFor6CDlg;
	//TagOpFor6CDlg* mTagOpFor6CDlg;
	TabSysInfoForm* mTabSysInfoForm;
	TabConnetInfoForm* mTabConnetInfoForm;
	TabApplyInfoForm* mTabApplyInfoForm;
	TabParamConfigForm* mTabParamConfigForm;
	TabUploadForm* mTabUploadForm;

	QPushButton* mDownBtn;
	QPushButton* mLeftBtn;

	void CreateView();
signals:
	void leftBtnClicked();
	void downBtnClicked();
private slots:
	void slot_leftBtnClicked();
	void slot_downBtnClicked();
	void slot_tabChanged(int index);
};


#endif // WORKDPACEDLG_H
