#include "adb_tool.h"
#include "ui_adb_tool.h"
#include "QDir"
#include "QDatetime"
#include"QString"
#include"QStringList"
#include "QFileDialog"
#include "QMessageBox"
#include "QProgressBar"
#include "QSettings"
#include <windows.h>
#include "LanguageSrc.h"
#include "MessageBox.h"
#include <QMenuBar>
#include "widgetconfig.h"
#include <QDebug>

//QProgressBar *startprogressbar;


adb_tool::adb_tool(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow),
	isNeedReboot(false)
{
	ui->setupUi(this);
	//初始化界面
	ui->progressBar->setValue(0);
	p = new QProcess(this);
	ui->setupButton->setChecked(true);
	ui->installtypewdg->hide();
	exePath = QCoreApplication::applicationDirPath()+"/platform-tools";
	qDebug() << "exePath:"<< exePath;
	p->setWorkingDirectory(exePath);

	QSettings setting("./Setting.ini", QSettings::IniFormat);//保存路径信息至运行目录
	QString lastPath = setting.value("LastFilePath").toString();//获取路径
	QString PathName = setting.value("LastFilePath", "").toString();	
	QFile file(PathName);
	if (file.exists())
	{
		ui->pathtEdit->setText(PathName);//文件名称显示
	}

	apkPackage = WIDGETSTRING_GET("adb_tool", "ApkPackage");
	apkActivity = WIDGETSTRING_GET("adb_tool", "ApkActivity");
	launcherPackage = setting.value("launcherPackage", defaultLauncherPackage).toString();
	launcherActivity = setting.value("launcherActivity", defaultLauncherActivity).toString();

	QMenu* fileMenu = NULL;
	fileMenu = menuBar()->addMenu(GET_TXT("IDCS_FILE"));
	mSoftConfigDlg = new SoftConfigDlg(this);
	mSoftConfigDlg->setMainwindow(this);
	mSoftCongfigAc = fileMenu->addAction(GET_TXT("IDCS_SOFT_CONFIG"));
	connect(mSoftCongfigAc, SIGNAL(triggered()), this, SLOT(slot_SoftConfigAc()));
	mExitAc = fileMenu->addAction(GET_TXT("IDCS_QUIT"));
	connect(mExitAc, SIGNAL(triggered()), this, SLOT(slot_ExitAc()));

	this->setWindowTitle(GET_TXT("IDCS_INSTALL"));
	
//	ui->tabWidget->setTabText(0,GET_TXT("IDCS_INSTALL"));
//	ui->tabWidget->setTabText(1, GET_TXT("IDCS_POWERBOOT"));
	ui->pathtext->setText(GET_TXT("IDCS_FILE"));
	ui->choseButton->setText(GET_TXT("IDCS_BROWSE"));
	ui->startButton->setText(GET_TXT("IDCS_INSTALL"));
	ui->uninstallBtn->setText(GET_TXT("IDCS_UNINSTALL"));

	ui->rebootBtn->setText(GET_TXT("IDCS_REBOOT"));
	ui->checkButton->setText(GET_TXT("IDCS_CHECK_LINK"));
	ui->cancelButton->setText(GET_TXT("IDCS_CLOSE"));
	ui->bootCkb->setText(GET_TXT("IDCS_POWERBOOT"));
	ui->label->setText(GET_TXT("IDCS_PWD"));
	ui->setbootBtn->setText(GET_TXT("IDCS_SET"));
	
}

adb_tool::~adb_tool()
{
	if (p)
	{
		delete p;
		p = NULL;
	}
	delete ui;

}


//检测装置
void adb_tool::on_checkButton_clicked()
{
	if (!checkConnect())
	{
		showInfoDialog(GET_TXT("IDCS_CONNET_FAILED"));
	}
	else
	{
		showInfoDialog(GET_TXT("IDCS_LINKED"));
	}
}


//浏览功能
void adb_tool::on_choseButton_clicked()
{
	//选择安装程序功能只能显示后缀为apk的文件
	if (ui->setupButton->isChecked())
	{
		QDir dir;
		QSettings setting("./Setting.ini", QSettings::IniFormat);//保存路径信息至运行目录
		QString lastPath = setting.value("LastFilePath").toString();//获取路径
		PathName = QFileDialog::getOpenFileName(this, GET_TXT("IDCS_PLEASE_SELECT_FILE"), lastPath, "*apk");
		if (!PathName.isEmpty())
		{
			setting.setValue("LastFilePath", PathName);//记录最后一次使用路径
		}
		//PathName.replace("/","\\");// 单斜杠转换双斜杠
		ui->pathtEdit->setText(PathName);//文件名称显示


	}
	//选择上传文件时能选择所有文件类型
	if (ui->uploadButton->isChecked())
	{
		QDir dir;
		PathName = QFileDialog::getOpenFileName(this, GET_TXT("IDCS_PLEASE_SELECT_FILE"), "D:/");
		//PathName.replace("/","\\");// 单斜杠转换双斜杠
		ui->pathtEdit->setText(PathName);//文件名称显示
		/*
		//push不支持多个文件方式，可能需要另外做脚本，先实现单个文件
		QDir dir;
		QStringList PathName = QFileDialog::getOpenFileNames(this,"请选择文件路径","D:/");
		//PathName.replace("/","\\");  // 单斜杠转换双斜杠
		for(int i=0;i<PathName.size();i++)
		{
		ui->pathtEdit->append(PathName.at(i));//文件名称显示
		}
		*/

	}
}

//开始功能
void adb_tool::on_startButton_clicked() //点击开始按钮根据勾选操作类型执行不同的adb命令
{
	pathinfo = ui->pathtEdit->text();
	if (pathinfo.isEmpty())
	{
		showInfoDialog(GET_TXT("IDCS_PLEASE_SELECT_FILE"));
		return;
	}
	QFile file(pathinfo);
	if (!file.exists())
	{
		showInfoDialog(GET_TXT("IDCS_FILE_NOT_VALIDITY"));
		return;
	}

	if (file.fileName().contains(" "))
	{
		showInfoDialog(GET_TXT("IDCS_NOT_SPACE_FILE"));
		return;
	}

	if (!checkConnect())
	{
		showInfoDialog(GET_TXT("IDCS_CONNET_FAILED"));
		return;
	}

	bool b = pathinfo.contains(QRegExp("[\\x4e00-\\x9fa5]+"));//检查路径中是否包含中文		
	if (b == true)
	{
		QMessageBox testMassage;
		testMassage.setWindowTitle(GET_TXT("IDCS_INFO"));
		testMassage.setText(GET_TXT("IDCS_CHOOSE_ENGLISH_PATH"));
		testMassage.exec();
	}
	else
	{
		if (!uninstallPathFile())
		{
			return;
		}

		if (!installPathFile(pathinfo))
		{
			return;
		}
			
		ui->progressBar->setValue(100);//成功后设置进度条值为100%

		showInfoDialog(GET_TXT("IDCS_INSTALL_SUCCESS"));
		ui->progressBar->setValue(0);//初始化进度条
	}
}

//退出功能
void adb_tool::on_cancelButton_clicked()
{
	QWidget::close(); //点击退出按钮重置界面并关闭程序，kill adb进程，先实现关闭窗口，adb命令不怎么消耗资源
}




void adb_tool::on_rebootBtn_clicked()
{
	if (!checkConnect())
	{
		showInfoDialog(GET_TXT("IDCS_CONNET_FAILED"));
		return;
	}

	p->start(QString("%1/adb reboot").arg(exePath));//检查设备是否存在
	p->waitForStarted();
	p->waitForFinished();

	QString startTemp = QString::fromUtf8(p->readAllStandardOutput());//使用UTF8可暂时过滤中文文件传输丢失后续或乱码问题，直接复制失败				

	QMessageBox testMassage;
	testMassage.setWindowTitle(GET_TXT("IDCS_INFO"));
	testMassage.setText(GET_TXT("IDCS_REBOOT_SUCCESS")+" " + startTemp);
	testMassage.exec();
	ui->progressBar->setValue(0);
}



void adb_tool::on_uninstallBtn_clicked()
{
	if (!checkConnect())
	{
		showInfoDialog(GET_TXT("IDCS_CONNET_FAILED"));
		return;
	}

	uninstallPathFile();

	ui->progressBar->setValue(100);//成功后设置进度条值为100%

	QMessageBox testMassage;
	testMassage.setWindowTitle(GET_TXT("IDCS_INFO"));
	testMassage.setText(GET_TXT("IDCS_UNINSTALL_SUCCESS"));
	testMassage.exec();
	ui->progressBar->setValue(0);
}


void adb_tool::on_setbootBtn_clicked()
{
	
}

void adb_tool::slot_SoftConfigAc()
{
	mSoftConfigDlg->exec();
}

void adb_tool::slot_ExitAc()
{
	if (HtMessageBox::Question(GET_TXT("IDCS_QUIT_SOFT"), this)
		== HtMessageBox::RET_ENTER)
	{
		qApp->quit();
	}
}

bool adb_tool::uninstallPathFileOld()
{
	p->start(QString("%1/adb shell pm uninstall -k %2").arg(exePath).arg(apkPackage));//检查设备是否存在
	p->waitForStarted();
	p->waitForFinished();
	return false;
}

bool adb_tool::uninstallPathFile()
{
	uninstallPathFileOld();

	qDebug() <<"exePath:"<< exePath;

	p->start(QString("%1/adb root ").arg(exePath));
	p->waitForStarted();
	p->waitForFinished();
	QString msg = QString::fromUtf8(p->readAllStandardOutput());
	qDebug() << msg;
	

	ui->progressBar->setValue(5);
	p->start(QString("%1/adb remount ").arg(exePath));
	p->waitForStarted();
	p->waitForFinished();
	msg = QString::fromUtf8(p->readAllStandardOutput());
	qDebug() << msg;

	
	ui->progressBar->setValue(10);
	msg = QString("rm_cmd.bat");
	qDebug() << msg;
	p->start(QString("%1/rm_cmd.bat ").arg(exePath));//调用cmd命令执行安装
	p->waitForStarted();
	p->waitForFinished(3000);
	msg = QString::fromUtf8(p->readAllStandardOutput());
	qDebug() << msg;


	msg = QString("rm_cmd.bat");
	qDebug() << msg;
	p->start(QString("%1/rm_cmd.bat ").arg(exePath));//调用cmd命令执行安装
	p->waitForStarted();
	p->waitForFinished(3000);
	msg = QString::fromUtf8(p->readAllStandardOutput());
	qDebug() << msg;
	
	p->close();
	ui->progressBar->setValue(20);
	return true;

}

bool adb_tool::installPathFile(const QString& pathinfo)
{

	p->start(QString("%1/adb root ").arg(exePath));
	p->waitForStarted();
	p->waitForFinished();
	QString msg;

	msg = QString::fromUtf8(p->readAllStandardOutput());
	qDebug() << msg;

	p->start(QString("%1/adb push %2 /sdcard/ ").arg(exePath).arg(pathinfo));
	p->waitForStarted();
	p->waitForFinished();
	msg = QString::fromUtf8(p->readAllStandardOutput());
	qDebug() << msg;
	p->start(QString("%1/ins_cmd.bat ").arg(exePath));//调用cmd命令执行安装
	p->waitForStarted();
	p->waitForFinished();
	msg = QString::fromUtf8(p->readAllStandardOutput());
	qDebug() << msg;
	p->close();
	ui->progressBar->setValue(100);//成功后设置进度条值为100%
	return true;
}

bool adb_tool::checkConnect()
{
	p->start(QString("%1/adb shell getprop ro.product.model").arg(exePath));
	p->waitForStarted();
	p->waitForFinished();
	//成功则提示连接成功并打印设备型号，否则打印连接失败
	QString checkTemp = QString::fromLocal8Bit(p->readAllStandardOutput());
	if (checkTemp.isNull())
	{
		return false;
	}
	else
	{
		return true;
	}

	return true;
}

void adb_tool::showInfoDialog(const QString& str)
{
	QMessageBox testMassage;
	testMassage.setWindowTitle(GET_TXT("IDCS_INFO"));
	testMassage.setText(str);
	testMassage.exec();
}

void adb_tool::SetNeedReboot(bool b)
{
	isNeedReboot = b;
}

bool adb_tool::GetNeedReboot()
{
	return isNeedReboot;
}
