#pragma execution_character_set("utf-8")
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

//QProgressBar *startprogressbar;


adb_tool::adb_tool(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow),
	isNeedReboot(false)
{
	ui->setupUi(this);
	//��ʼ������
	ui->progressBar->setValue(0);
	p = new QProcess(this);
	ui->setupButton->setChecked(true);
	ui->installtypewdg->hide();
	exePath = QCoreApplication::applicationDirPath()+"/platform-tools";

	QSettings setting("./Setting.ini", QSettings::IniFormat);//����·����Ϣ������Ŀ¼
	QString lastPath = setting.value("LastFilePath").toString();//��ȡ·��
	QString PathName = setting.value("LastFilePath", "").toString();	
	QFile file(PathName);
	if (file.exists())
	{
		ui->pathtEdit->setText(PathName);//�ļ�������ʾ
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
	
	ui->tabWidget->setTabText(0,GET_TXT("IDCS_INSTALL"));
	ui->tabWidget->setTabText(1, GET_TXT("IDCS_POWERBOOT"));
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


//���װ��
void adb_tool::on_checkButton_clicked()
{
	//p = new QProcess(this);
	QString test = QString("%1/adb shell getprop ro.product.model").arg(exePath);

	//p->start("cmd", QStringList() << "/c" << QString("%1/adb shell getprop ro.product.model").arg(exePath));
	p->start(QString("%1/adb shell getprop ro.product.model").arg(exePath));
	p->waitForStarted();
	p->waitForFinished();
	//�ɹ�����ʾ���ӳɹ�����ӡ�豸�ͺţ������ӡ����ʧ��
	QString checkTemp = QString::fromLocal8Bit(p->readAllStandardOutput());
	if (checkTemp.isNull())
	{
		QMessageBox testMassage;
		testMassage.setWindowTitle(GET_TXT("IDCS_INFO"));
		testMassage.setText(GET_TXT("IDCS_CONNET_FAILED"));
		testMassage.exec();
	}
	else
	{
		QMessageBox testMassage;
		testMassage.setWindowTitle(GET_TXT("IDCS_INFO"));
		testMassage.setText(GET_TXT("IDCS_LINKED") +"  "+ checkTemp);
		testMassage.exec();
	}

}


//�������
void adb_tool::on_choseButton_clicked()
{
	//ѡ��װ������ֻ����ʾ��׺Ϊapk���ļ�
	if (ui->setupButton->isChecked())
	{
		QDir dir;
		QSettings setting("./Setting.ini", QSettings::IniFormat);//����·����Ϣ������Ŀ¼
		QString lastPath = setting.value("LastFilePath").toString();//��ȡ·��
		PathName = QFileDialog::getOpenFileName(this, GET_TXT("IDCS_PLEASE_SELECT_FILE"), lastPath, "*apk");
		if (!PathName.isEmpty())
		{
			setting.setValue("LastFilePath", PathName);//��¼���һ��ʹ��·��
		}
		//PathName.replace("/","\\");// ��б��ת��˫б��
		ui->pathtEdit->setText(PathName);//�ļ�������ʾ


	}
	//ѡ���ϴ��ļ�ʱ��ѡ�������ļ�����
	if (ui->uploadButton->isChecked())
	{
		QDir dir;
		PathName = QFileDialog::getOpenFileName(this, GET_TXT("IDCS_PLEASE_SELECT_FILE"), "D:/");
		//PathName.replace("/","\\");// ��б��ת��˫б��
		ui->pathtEdit->setText(PathName);//�ļ�������ʾ
		/*
		//push��֧�ֶ���ļ���ʽ��������Ҫ�������ű�����ʵ�ֵ����ļ�
		QDir dir;
		QStringList PathName = QFileDialog::getOpenFileNames(this,"��ѡ���ļ�·��","D:/");
		//PathName.replace("/","\\");  // ��б��ת��˫б��
		for(int i=0;i<PathName.size();i++)
		{
		ui->pathtEdit->append(PathName.at(i));//�ļ�������ʾ
		}
		*/

	}
}

//��ʼ����
void adb_tool::on_startButton_clicked() //�����ʼ��ť���ݹ�ѡ��������ִ�в�ͬ��adb����
{
	pathinfo = ui->pathtEdit->text();
	if (pathinfo.isEmpty())
	{
		QMessageBox testMassage;
		testMassage.setWindowTitle(GET_TXT("IDCS_INFO"));
		testMassage.setText(GET_TXT("IDCS_PLEASE_SELECT_FILE"));
		testMassage.exec();
		return;
	}
	QFile file(pathinfo);
	if (!file.exists())
	{
		QMessageBox testMassage;
		testMassage.setWindowTitle(GET_TXT("IDCS_INFO"));
		testMassage.setText(GET_TXT("IDCS_FILE_NOT_VALIDITY"));
		testMassage.exec();
		return;
	}


	//��װ����
	if (ui->setupButton->isChecked())
	{	
		//p->start("cmd", QStringList() << "/c" << QString("%1/adb shell getprop ro.product.model").arg(exePath));//����豸�Ƿ����
		p->start(QString("%1/adb shell getprop ro.product.model").arg(exePath));//����豸�Ƿ����
		p->waitForStarted();
		p->waitForFinished();
		QString checkTemp = QString::fromUtf8(p->readAllStandardOutput());
		
		if (checkTemp.isNull())
		{
			QMessageBox testMassage;
			testMassage.setWindowTitle(GET_TXT("IDCS_INFO"));
			testMassage.setText(GET_TXT("IDCS_CONNET_FAILED"));
			testMassage.exec();
			return;
		}
		else
		{
			QFile file(pathinfo);
			if (!file.exists())
			{
				QMessageBox testMassage;
				testMassage.setWindowTitle(GET_TXT("IDCS_INFO"));
				testMassage.setText(GET_TXT("IDCS_FILE_NOT_VALIDITY"));
				testMassage.exec();
				return;
			}

			if (file.fileName().contains(" "))
			{
				QMessageBox testMassage;
				testMassage.setWindowTitle(GET_TXT("IDCS_INFO"));
				testMassage.setText(GET_TXT("IDCS_NOT_SPACE_FILE"));
				testMassage.exec();
				return;
			}
			bool b = pathinfo.contains(QRegExp("[\\x4e00-\\x9fa5]+"));//���·�����Ƿ��������		
			if (b == true)
			{
				QMessageBox testMassage;
				testMassage.setWindowTitle(GET_TXT("IDCS_INFO"));
				testMassage.setText(GET_TXT("IDCS_CHOOSE_ENGLISH_PATH"));
				testMassage.exec();
			}
			else
			{
				p->start(QString("%1/adb install  ").arg(exePath) + pathinfo);//����cmd����ִ�а�װ
																					//p->waitForStarted();
				if (!p->waitForStarted())
				{
					QMessageBox testMassage;
					testMassage.setWindowTitle(GET_TXT("IDCS_INFO"));
					testMassage.setText(GET_TXT("IDCS_EXECUTE_FAILED"));
					testMassage.exec();
				}
				for (int i = 0; i <= 70; i++)
				{
					ui->progressBar->setValue(i);//��������ִ�������޷���ȡ����ִ��״̬����ʵ�ֽ���Ч��
				}
				//p->waitForFinished();
				if (!p->waitForFinished())
				{
					QMessageBox testMassage;
					testMassage.setText(GET_TXT("IDCS_EXECUTE_FAILED"));
					testMassage.exec();
				}
				ui->progressBar->setValue(100);//�ɹ������ý�����ֵΪ100%
				QString startTemp = QString::fromUtf8(p->readAllStandardOutput());

				if (true)//ui->bootCkb->isChecked())
				{
					p->start(QString("%1/adb shell cmd package set-home-activity %2/%3").arg(exePath).arg(apkPackage).arg(apkActivity));
				}
				else
				{
					p->start(QString("%1/adb shell cmd package set-home-activity %2/%3").arg(exePath).arg(launcherPackage).arg(launcherActivity));
				}

				p->waitForStarted();
				p->waitForFinished();

				p->start( QString("%1/adb shell am start -n  %2/%3").arg(exePath).arg(apkPackage).arg(apkActivity));
				p->waitForStarted();
				p->waitForFinished();

				startTemp = QString::fromUtf8(p->readAllStandardOutput());

				
				//p->start("cmd", QStringList() << "/c" << "adb reboot");	//push�ļ����ֻ�sdcradĿ¼
				//p->waitForStarted();
				//p->waitForFinished();

				QMessageBox testMassage;
				testMassage.setWindowTitle(GET_TXT("IDCS_INFO"));
				testMassage.setText(GET_TXT("IDCS_INSTALL_SUCCESS")+" " + startTemp);
				testMassage.exec();
				ui->progressBar->setValue(0);//��ʼ��������

			}


		}

	}


	//�ϴ��ļ�
	if (ui->uploadButton->isChecked())
	{
		p->start(QString("%1/adb shell getprop ro.product.model").arg(exePath));	//push�ļ����ֻ�sdcradĿ¼
		p->waitForStarted();
		p->waitForFinished();
		QString checkTemp = QString::fromUtf8(p->readAllStandardOutput());
		pathinfo = ui->pathtEdit->text();
		if (checkTemp.isNull())
		{
			QMessageBox testMassage;
			testMassage.setWindowTitle(GET_TXT("IDCS_INFO"));
			testMassage.setText(GET_TXT("IDCS_CONNET_FAILED"));
			testMassage.exec();
		}
		else
		{			
			bool b = pathinfo.contains(QRegExp("[\\x4e00-\\x9fa5]+"));//���·�����Ƿ��������
			if (b == true)
			{
				QMessageBox testMassage;
				testMassage.setWindowTitle(GET_TXT("IDCS_INFO"));
				testMassage.setText(GET_TXT("IDCS_CHOOSE_ENGLISH_PATH"));
				testMassage.exec();
			}
			else
			{
				//QString path = ui->pathtEdit->toPlainText();
				p->start(QString("%1/adb push ").arg(exePath) + pathinfo + " /sdcard");//�ϴ��ļ���/sdcard��Ŀ¼
				//p->waitForStarted();
				if (!p->waitForStarted(-1))
				{
					QMessageBox testMassage;
					testMassage.setWindowTitle(GET_TXT("IDCS_INFO"));
					testMassage.setText(GET_TXT("IDCS_UPLOAD_FAILED"));
					testMassage.exec();
				}
				for (int i = 0; i <= 70; i++)
				{
					ui->progressBar->setValue(i);//��������ִ�������޷���ȡ����ִ��״̬����ʵ�ֽ���Ч��
				}
				//p->waitForFinished();
				if (!p->waitForFinished(-1))
				{
					QMessageBox testMassage;
					testMassage.setWindowTitle(GET_TXT("IDCS_INFO"));
					testMassage.setText(GET_TXT("IDCS_UPLOAD_FAILED"));
					testMassage.exec();
				}
				ui->progressBar->setValue(100);//�ɹ������ý�����ֵΪ100%

				QString startTemp = QString::fromUtf8(p->readAllStandardOutput());//ʹ��UTF8����ʱ���������ļ����䶪ʧ�������������⣬ֱ�Ӹ���ʧ��				

				QMessageBox testMassage;
				testMassage.setWindowTitle(GET_TXT("IDCS_INFO"));
				testMassage.setText(GET_TXT("IDCS_UPLOAD_SUCCESS")+" " + startTemp);
				testMassage.exec();
				ui->progressBar->setValue(0);//��ʼ��������
			}

		}

	}

}

//�˳�����
void adb_tool::on_cancelButton_clicked()
{
	QWidget::close(); //����˳���ť���ý��沢�رճ���kill adb���̣���ʵ�ֹرմ��ڣ�adb�����ô������Դ
}




void adb_tool::on_rebootBtn_clicked()
{
	p->start(QString("%1/adb shell getprop ro.product.model").arg(exePath));//����豸�Ƿ����
	p->waitForStarted();
	p->waitForFinished();
	QString checkTemp = QString::fromUtf8(p->readAllStandardOutput());
	pathinfo = ui->pathtEdit->text();
	if (checkTemp.isNull())
	{
		QMessageBox testMassage;
		testMassage.setWindowTitle(GET_TXT("IDCS_INFO"));
		testMassage.setText(GET_TXT("IDCS_CONNET_FAILED"));
		testMassage.exec();
		return;
	}

	p->start(QString("%1/adb reboot").arg(exePath));//����豸�Ƿ����
	p->waitForStarted();
	p->waitForFinished();

	QString startTemp = QString::fromUtf8(p->readAllStandardOutput());//ʹ��UTF8����ʱ���������ļ����䶪ʧ�������������⣬ֱ�Ӹ���ʧ��				

	QMessageBox testMassage;
	testMassage.setWindowTitle(GET_TXT("IDCS_INFO"));
	testMassage.setText(GET_TXT("IDCS_REBOOT_SUCCESS")+" " + startTemp);
	testMassage.exec();
	ui->progressBar->setValue(0);
}



void adb_tool::on_uninstallBtn_clicked()
{
	p->start(QString("%1/adb shell getprop ro.product.model").arg(exePath));//����豸�Ƿ����
	p->waitForStarted();
	p->waitForFinished();
	QString checkTemp = QString::fromUtf8(p->readAllStandardOutput());
	pathinfo = ui->pathtEdit->text();
	if (checkTemp.isNull())
	{
		QMessageBox testMassage;
		testMassage.setWindowTitle(GET_TXT("IDCS_INFO"));
		testMassage.setText(GET_TXT("IDCS_CONNET_FAILED"));
		testMassage.exec();
		return;
	}

	p->start(QString("%1/adb shell pm uninstall -k %2").arg(exePath).arg(apkPackage));//����豸�Ƿ����
	p->waitForStarted();
	p->waitForFinished();

	QString startTemp = QString::fromUtf8(p->readAllStandardOutput());//ʹ��UTF8����ʱ���������ļ����䶪ʧ�������������⣬ֱ�Ӹ���ʧ��				

	QMessageBox testMassage;
	testMassage.setWindowTitle(GET_TXT("IDCS_INFO"));
	testMassage.setText(GET_TXT("IDCS_UNINSTALL_SUCCESS")+" " + startTemp);
	testMassage.exec();
	ui->progressBar->setValue(0);
}


void adb_tool::on_setbootBtn_clicked()
{
	if (!ui->lineEdit->text().compare("Admin@cirfid.com") == 0)
	{
		QMessageBox testMassage;
		testMassage.setWindowTitle(GET_TXT("IDCS_INFO"));
		testMassage.setText(GET_TXT("IDCS_PWD_ERRO"));
		testMassage.exec();
		return;
	}
	p->start(QString("%1/adb shell getprop ro.product.model").arg(exePath));//����豸�Ƿ����
	p->waitForStarted();
	p->waitForFinished();
	QString checkTemp = QString::fromUtf8(p->readAllStandardOutput());
	pathinfo = ui->pathtEdit->text();
	if (checkTemp.isNull())
	{
		QMessageBox testMassage;
		testMassage.setWindowTitle(GET_TXT("IDCS_INFO"));
		testMassage.setText(GET_TXT("IDCS_CONNET_FAILED"));
		testMassage.exec();
		return;
	}

	if (ui->bootCkb->isChecked())
	{
		p->start(QString("%1/adb shell cmd package set-home-activity %2/%3").arg(exePath).arg(apkPackage).arg(apkActivity));
	}
	else
	{
		p->start(QString("%1/adb shell cmd package set-home-activity %2/%3").arg(exePath).arg(launcherPackage).arg(launcherActivity));
	}

	p->waitForStarted();
	p->waitForFinished();

	QString startTemp = QString::fromUtf8(p->readAllStandardOutput());//ʹ��UTF8����ʱ���������ļ����䶪ʧ�������������⣬ֱ�Ӹ���ʧ��				

	QMessageBox testMassage;
	testMassage.setWindowTitle(GET_TXT("IDCS_INFO"));
	testMassage.setText(GET_TXT("IDCS_SET_SUCCESS") + " " + startTemp);
	testMassage.exec();
	ui->progressBar->setValue(0);
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

void adb_tool::SetNeedReboot(bool b)
{
	isNeedReboot = b;
}

bool adb_tool::GetNeedReboot()
{
	return isNeedReboot;
}