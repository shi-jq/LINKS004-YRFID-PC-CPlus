#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QSplitter;
class ConnetDlg;
class workDpaceDlg;
class OpListDlg;
class QCloseEvent;
class SoftConfigDlg;
class VersionCommonDlg;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT    
public:
     explicit MainWindow( QWidget *parent = 0);
	 bool isNeedReboot();
	 void SetNeedReboot(bool isneed);
    ~MainWindow();
	void ShowMsg(QString msg,bool getErro);//显示操作记录
	void updateReaderState(int nConnetType);//读写器状态更新,刷新界面
	void CutConnet();//断开连接

protected:
	void closeEvent(QCloseEvent *event);//退出程序事件
	void keyPressEvent(QKeyEvent *ev);//按键事件
private:
    Ui::MainWindow *ui;

	bool mIsNeetReboot;//是否需要重启

	workDpaceDlg* mworkDpaceDlg;//工作区
	OpListDlg* mOpListDlg;//操作页面

	QAction* mVersionCommonAc;//软件版本
	//菜单栏	
	QAction* mSoftCongfigAc;
	QAction* mExitAc;

	SoftConfigDlg* mSoftConfigDlg;
	VersionCommonDlg* mVersionCommonDlg;
private:
	void CreateMenuBar();//生成菜单栏
	void CreateFileMenu();//文件
	void CreateHelpMenu();

	void CreateWirelessMenu();//805s无线接收配置菜单

	void CreateView();//生成视图
	

	
private slots:
	void slot_leftBtnClicked();
	void slot_downBtnClicked();
	void slot_VersionCommonAc();
	//菜单栏
	void slot_SoftConfigAc();
	void slot_ExitAc();
	void slot_updateReaderState(int nConnetType);
	void slot_HelpAc();
	void slot_CutConnet();
};

#endif // MAINWINDOW_H
