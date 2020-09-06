#ifndef APP_PATH_H
#define APP_PATH_H

#include <QCoreApplication>

class AppPath
{
public:
	AppPath()
	{

	};
	//��������Ŀ¼
	static QString GetAppDirPath()
	{
		return  QCoreApplication::applicationDirPath();
	};

	//ϵͳ����,���������ļ�
	static QString GetAppBasicConfigFile()
	{
		QString ConfigFilePath = QString( "%1/Config/sys.ini" ).arg( QCoreApplication::applicationDirPath() );
		return ConfigFilePath;
	};

	//��ȡ����·��
	static QString GetDefaultDeviceConfigPath()
	{
		QString ConfigFilePath = QString( "%1/Config" ).arg( QCoreApplication::applicationDirPath() );
		return ConfigFilePath;
	};

	//��ʽ��·��
	static QString GetStylesheetFileName()
	{
		QString ConfigFilePath = QString( "%1/skin/qss/stylesheet.css" ).arg( QCoreApplication::applicationDirPath() );
		return ConfigFilePath;
	};

	//�����ļ�����
	static QString GetLanguagePath()
	{
		QString ConfigFilePath = QString( "%1/language" ).arg( QCoreApplication::applicationDirPath() );
		return ConfigFilePath;
	};
};

#endif // APP_PATH_H