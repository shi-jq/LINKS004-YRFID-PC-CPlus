#pragma once
#ifndef MainWindow_H
#define MainWindow_H
#include <QMainWindow>
#include <QProcess>
#include <QtWidgets/QWidget>
#include "ui_adb_tool.h"
//#include "adb_tool.ui"

#include "SoftConfigDlg.h"

namespace Ui {
	class MainWindow;
}

static const QString defaultApkPackage = "com.handheld.yhfr";
static const QString defaultApkActivity = "com.rfid_demo.main.MainActivity";
static const QString defaultLauncherPackage = "com.android.launcher3";
static const QString defaultLauncherActivity = "com.android.launcher3.Launcher";


class adb_tool : public QMainWindow
{
	Q_OBJECT

public:
	explicit adb_tool(QWidget *parent = 0);
	~adb_tool();

	void SetNeedReboot(bool b);

	bool GetNeedReboot();

	private slots:
	void on_choseButton_clicked();

	void on_startButton_clicked();

	void on_cancelButton_clicked();

	void on_checkButton_clicked();

	void on_rebootBtn_clicked();
	void on_uninstallBtn_clicked();

	void on_setbootBtn_clicked();

	void slot_SoftConfigAc();
	void slot_ExitAc();

	bool uninstallPathFileOld();

	bool uninstallPathFile();
	bool installPathFile(const QString& pathinfo);

	bool checkConnect();
	void showInfoDialog(const QString& str);
private:
	Ui::MainWindow *ui;

	SoftConfigDlg* mSoftConfigDlg;
	//²Ëµ¥À¸	
	QAction* mSoftCongfigAc;
	QAction* mExitAc;

	QProcess *p;

	QString PathName;
	QString checkTemp;
	QString starttemp;
	QString canceltemp;
	QString pathinfo;
	QString lastPath;
	QString file;


	QString apkPackage;
	QString apkActivity;

	QString launcherPackage;
	QString launcherActivity;
	QString exePath;

	bool isNeedReboot;
};

#endif // MAINWINDOW_H