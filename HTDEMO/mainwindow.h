#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QSplitter;
class ConnetDlg;
class workDpaceDlg;
class OpListDlg;
class QCloseEvent;
class FirmWareUpdateFor6CDlg;
class R2000LogDlg;
class ComConfigDlg;
class BusAddrConfigDlg;
class NetConfigFor6CDlg;
class ReaderTimeSetDlg;
class FlashConfigFor6CDlg;
class FiltrateTagFor6CDlg;
class QValueDlg;
class IoConfigFor6CDlg;
class CarrierWaveFor6CDlg;
class ParamConfigFor6CDlg;
class WIFIConfigFor6CDLg;
class GprsConfigDlg;
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
	void ShowMsg(QString msg,bool getErro,bool getReader);//显示操作记录
	void updateReaderState(int nConnetType);//读写器状态更新,刷新界面
	void CutConnet();//断开连接

protected:
	void closeEvent(QCloseEvent *event);//退出程序事件
	void keyPressEvent(QKeyEvent *ev);//按键事件
private:
    Ui::MainWindow *ui;

	bool mIsNeetReboot;//是否需要重启

	ConnetDlg* mConnetDlg;//连接
	workDpaceDlg* mworkDpaceDlg;//工作区
	OpListDlg* mOpListDlg;//操作页面

	QAction* mVersionCommonAc;//软件版本
	//菜单栏	
	QAction* mExitAc;

	//6c部分的菜单栏Action
	QAction* mReaderInfoFor6CAc;
	QAction* mFirmWareUpdateFor6CAc;
	QAction* mR2000LogAc;
	QAction* mNetConfigFor6CAc;
	QAction* mComConfigAc;
	QAction* mBusAddrConfigAc;
	QAction* mReaderTimeSetAc;
	QAction* mFiltrateTagFor6CAc;
	QAction* mFlashConfigFor6CAc;
	QAction* mQVlaueAc;
	QAction* mIoConfigFor6CAc;
	QAction* mCarrierWaveFor6CAc;
	QAction* mParamConfigFor6CAc;
	QAction* mWIFIConfigFor6CAC;
	QAction* mGprsConfigFor6CAc;
	QAction* mRebootDeviceFor6CAc;

	QAction* mSoftCongfigAc;


	VersionCommonDlg* mVersionCommonDlg;
	

	//6c部分的弹出窗口		
	CarrierWaveFor6CDlg* mCarrierWaveFor6CDlg;
	ParamConfigFor6CDlg* mParamConfigFor6CDlg;
	GprsConfigDlg* mGprsConfigDlg;


	SoftConfigDlg* mSoftConfigDlg;
private:
	void CreateMenuBar();//生成菜单栏
	void CreateFileMenu();//文件
	
	void CreateHelpMenu();//帮助


	void CreateView();//生成视图

	bool checkConnet();//检查连接状态
	
private slots:
	void slot_leftBtnClicked();
	void slot_downBtnClicked();
	void slot_CutConnet();
	//菜单栏
	void slot_ExitAc();
	void slot_updateReaderState(int nConnetType);
	void slot_HelpAc();

	void slot_WIFIConfigFor6CAc();

	void slot_SoftConfigAc();


	void slot_VersionCommonAc();

	void slot_UpdateReadCount(int count,int speed, int nReset);//刷新读卡次数,总次数和即时次数
	
};

#endif // MAINWINDOW_H
