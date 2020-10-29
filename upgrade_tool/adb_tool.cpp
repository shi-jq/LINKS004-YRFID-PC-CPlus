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


//QProgressBar *startprogressbar;

static const QString defaultApkPackage = "com.handheld.yhfr";
static const QString defaultApkActivity = "com.rfid_demo.main.MainActivity";
static const QString defaultLauncherPackage = "com.android.launcher3";
static const QString defaultLauncherActivity = "com.android.launcher3.Launcher";

adb_tool::adb_tool(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	//��ʼ������
	ui->progressBar->setValue(0);
	p = new QProcess(this);
	ui->setupButton->setChecked(true);
	ui->installtypewdg->hide();

	QSettings setting("./Setting.ini", QSettings::IniFormat);//����·����Ϣ������Ŀ¼
	QString lastPath = setting.value("LastFilePath").toString();//��ȡ·��
	QString PathName = setting.value("LastFilePath", "").toString();	
	QFile file(PathName);
	if (file.exists())
	{
		ui->pathtEdit->setText(PathName);//�ļ�������ʾ
	}

	apkPackage = setting.value("apkPackage", defaultApkPackage).toString();
	apkActivity = setting.value("apkActivity", defaultApkActivity).toString();
	launcherPackage = setting.value("launcherPackage", defaultLauncherPackage).toString();
	launcherActivity = setting.value("launcherActivity", defaultLauncherActivity).toString();

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
	p->start("cmd", QStringList() << "/c" << "adb shell getprop ro.product.model");
	p->waitForStarted();
	p->waitForFinished();
	//�ɹ�����ʾ���ӳɹ�����ӡ�豸�ͺţ������ӡ����ʧ��
	QString checkTemp = QString::fromLocal8Bit(p->readAllStandardOutput());
	if (checkTemp.isNull())
	{
		QMessageBox testMassage;
		testMassage.setWindowTitle("��ʾ��");
		testMassage.setText("����ʧ�ܣ�");
		testMassage.exec();
	}
	else
	{
		QMessageBox testMassage;
		testMassage.setWindowTitle("��ʾ��");
		testMassage.setText("�豸������!\n�豸�ͺ�:" + checkTemp);
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
		PathName = QFileDialog::getOpenFileName(this, "��ѡ���ļ�·��", lastPath, "*apk");
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
		PathName = QFileDialog::getOpenFileName(this, "��ѡ���ļ�·��", "D:/");
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
		testMassage.setWindowTitle("��ʾ��");
		testMassage.setText("��ѡ���ļ�");
		testMassage.exec();
		return;
	}
	QFile file(pathinfo);
	if (!file.exists())
	{
		QMessageBox testMassage;
		testMassage.setWindowTitle("��ʾ��");
		testMassage.setText("�ļ�������");
		testMassage.exec();
		return;
	}


	//��װ����
	if (ui->setupButton->isChecked())
	{	
		p->start("cmd", QStringList() << "/c" << "adb shell getprop ro.product.model");//����豸�Ƿ����
		p->waitForStarted();
		p->waitForFinished();
		QString checkTemp = QString::fromUtf8(p->readAllStandardOutput());
		
		if (checkTemp.isNull())
		{
			QMessageBox testMassage;
			testMassage.setWindowTitle("��ʾ��");
			testMassage.setText("�豸δ����");
			testMassage.exec();
		}
		else
		{
			bool b = pathinfo.contains(QRegExp("[\\x4e00-\\x9fa5]+"));//���·�����Ƿ��������
			if (b == true)
			{
				QMessageBox testMassage;
				testMassage.setWindowTitle("��ʾ��");
				testMassage.setText("·�����ܰ��������ַ�");
				testMassage.exec();
			}
			else
			{
				p->start("cmd", QStringList() << "/c" << "adb install" << pathinfo);//����cmd����ִ�а�װ
																					//p->waitForStarted();
				if (!p->waitForStarted())
				{
					QMessageBox testMassage;
					testMassage.setWindowTitle("��ʾ��");
					testMassage.setText("ִ��ʧ�ܣ�");
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
					testMassage.setText("ִ��ʧ�ܣ�");
					testMassage.exec();
				}
				ui->progressBar->setValue(100);//�ɹ������ý�����ֵΪ100%
				QString startTemp = QString::fromUtf8(p->readAllStandardOutput());

				if (ui->bootCkb->isChecked())
				{
					p->start("cmd", QStringList() << "/c" << QString("adb shell cmd package set-home-activity %1/%2").arg(apkPackage).arg(apkActivity));
				}
				else
				{
					p->start("cmd", QStringList() << "/c" << QString("adb shell cmd package set-home-activity %1/%2").arg(launcherPackage).arg(launcherActivity));
				}

				p->waitForStarted();
				p->waitForFinished();

				p->start("cmd", QStringList() << "/c" << QString("adb shell am start -n  %1/%2").arg(apkPackage).arg(apkActivity));
				p->waitForStarted();
				p->waitForFinished();

				startTemp = QString::fromUtf8(p->readAllStandardOutput());

				
				//p->start("cmd", QStringList() << "/c" << "adb reboot");	//push�ļ����ֻ�sdcradĿ¼
				//p->waitForStarted();
				//p->waitForFinished();

				QMessageBox testMassage;
				testMassage.setWindowTitle("��ʾ��");
				testMassage.setText("ִ�а�װ�ɹ������������ֻ�ִ�а�װ!\n��װ��Ϣ��" + startTemp);
				testMassage.exec();
				ui->progressBar->setValue(0);//��ʼ��������

			}


		}

	}


	//�ϴ��ļ�
	if (ui->uploadButton->isChecked())
	{
		p->start("cmd", QStringList() << "/c" << "adb shell getprop ro.product.model");	//push�ļ����ֻ�sdcradĿ¼
		p->waitForStarted();
		p->waitForFinished();
		QString checkTemp = QString::fromUtf8(p->readAllStandardOutput());
		pathinfo = ui->pathtEdit->text();
		if (checkTemp.isNull())
		{
			QMessageBox testMassage;
			testMassage.setWindowTitle("��ʾ��");
			testMassage.setText("�豸δ����");
			testMassage.exec();
		}
		else
		{			
			bool b = pathinfo.contains(QRegExp("[\\x4e00-\\x9fa5]+"));//���·�����Ƿ��������
			if (b == true)
			{
				QMessageBox testMassage;
				testMassage.setWindowTitle("��ʾ��");
				testMassage.setText("·�����ܰ��������ַ�");
				testMassage.exec();
			}
			else
			{
				//QString path = ui->pathtEdit->toPlainText();
				p->start("cmd", QStringList() << "/c" << "adb push" << pathinfo << "/sdcard");//�ϴ��ļ���/sdcard��Ŀ¼
				//p->waitForStarted();
				if (!p->waitForStarted(-1))
				{
					QMessageBox testMassage;
					testMassage.setWindowTitle("��ʾ��");
					testMassage.setText("�ϴ�ʧ�ܣ�");
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
					testMassage.setWindowTitle("��ʾ��");
					testMassage.setText("�ϴ�ʧ�ܣ�");
					testMassage.exec();
				}
				ui->progressBar->setValue(100);//�ɹ������ý�����ֵΪ100%

				QString startTemp = QString::fromUtf8(p->readAllStandardOutput());//ʹ��UTF8����ʱ���������ļ����䶪ʧ�������������⣬ֱ�Ӹ���ʧ��				

				QMessageBox testMassage;
				testMassage.setWindowTitle("��ʾ��");
				testMassage.setText("ִ���ϴ�����ɹ������飡\n������Ϣ��" + startTemp);
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
	p->start("cmd", QStringList() << "/c" << "adb shell getprop ro.product.model");//����豸�Ƿ����
	p->waitForStarted();
	p->waitForFinished();
	QString checkTemp = QString::fromUtf8(p->readAllStandardOutput());
	pathinfo = ui->pathtEdit->text();
	if (checkTemp.isNull())
	{
		QMessageBox testMassage;
		testMassage.setWindowTitle("��ʾ��");
		testMassage.setText("�豸δ����");
		testMassage.exec();
		return;
	}

	p->start("cmd", QStringList() << "/c" << "adb reboot");//����豸�Ƿ����
	p->waitForStarted();
	p->waitForFinished();

	QString startTemp = QString::fromUtf8(p->readAllStandardOutput());//ʹ��UTF8����ʱ���������ļ����䶪ʧ�������������⣬ֱ�Ӹ���ʧ��				

	QMessageBox testMassage;
	testMassage.setWindowTitle("��ʾ��");
	testMassage.setText("�����ɹ�! " + startTemp);
	testMassage.exec();
	ui->progressBar->setValue(0);
}



void adb_tool::on_uninstallBtn_clicked()
{
	p->start("cmd", QStringList() << "/c" << "adb shell getprop ro.product.model");//����豸�Ƿ����
	p->waitForStarted();
	p->waitForFinished();
	QString checkTemp = QString::fromUtf8(p->readAllStandardOutput());
	pathinfo = ui->pathtEdit->text();
	if (checkTemp.isNull())
	{
		QMessageBox testMassage;
		testMassage.setWindowTitle("��ʾ��");
		testMassage.setText("�豸δ����");
		testMassage.exec();
		return;
	}

	p->start("cmd", QStringList() << "/c" << QString("adb shell pm uninstall -k %1").arg(apkPackage));//����豸�Ƿ����
	p->waitForStarted();
	p->waitForFinished();

	QString startTemp = QString::fromUtf8(p->readAllStandardOutput());//ʹ��UTF8����ʱ���������ļ����䶪ʧ�������������⣬ֱ�Ӹ���ʧ��				

	QMessageBox testMassage;
	testMassage.setWindowTitle("��ʾ��");
	testMassage.setText("ж�سɹ�! " + startTemp);
	testMassage.exec();
	ui->progressBar->setValue(0);
}


void adb_tool::on_setbootBtn_clicked()
{
	p->start("cmd", QStringList() << "/c" << "adb shell getprop ro.product.model");//����豸�Ƿ����
	p->waitForStarted();
	p->waitForFinished();
	QString checkTemp = QString::fromUtf8(p->readAllStandardOutput());
	pathinfo = ui->pathtEdit->text();
	if (checkTemp.isNull())
	{
		QMessageBox testMassage;
		testMassage.setWindowTitle("��ʾ��");
		testMassage.setText("�豸δ����");
		testMassage.exec();
		return;
	}

	if (ui->bootCkb->isChecked())
	{
		p->start("cmd", QStringList() << "/c" << QString("adb shell cmd package set-home-activity %1/%2").arg(apkPackage).arg(apkActivity));
	}
	else
	{
		p->start("cmd", QStringList() << "/c" << QString("adb shell cmd package set-home-activity %1/%2").arg(launcherPackage).arg(launcherActivity));
	}

	p->waitForStarted();
	p->waitForFinished();

	QString startTemp = QString::fromUtf8(p->readAllStandardOutput());//ʹ��UTF8����ʱ���������ļ����䶪ʧ�������������⣬ֱ�Ӹ���ʧ��				

	QMessageBox testMassage;
	testMassage.setWindowTitle("��ʾ��");
	testMassage.setText("���óɹ�! " + startTemp);
	testMassage.exec();
	ui->progressBar->setValue(0);
}