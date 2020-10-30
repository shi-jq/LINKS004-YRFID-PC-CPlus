#pragma once
#ifndef MainWindow_H
#define MainWindow_H
#include <QMainWindow>
#include <QProcess>
#include <QtWidgets/QWidget>
#include "ui_adb_tool.h"
//#include "adb_tool.ui"


namespace Ui {
	class MainWindow;
}


class adb_tool : public QMainWindow
{
	Q_OBJECT

public:
	explicit adb_tool(QWidget *parent = 0);
	~adb_tool();

	private slots:
	void on_choseButton_clicked();

	void on_startButton_clicked();

	void on_cancelButton_clicked();

	void on_checkButton_clicked();

	void on_rebootBtn_clicked();
	void on_uninstallBtn_clicked();

	void on_setbootBtn_clicked();
private:
	Ui::MainWindow *ui;
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

};

#endif // MAINWINDOW_H