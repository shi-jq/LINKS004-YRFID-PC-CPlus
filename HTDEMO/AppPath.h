#ifndef APP_PATH_H
#define APP_PATH_H

#include <QCoreApplication>

class AppPath
{
public:
	AppPath()
	{

	};
	//程序运行目录
	static QString GetAppDirPath()
	{
		return  QCoreApplication::applicationDirPath();
	};

	//系统配置,基础配置文件
	static QString GetAppBasicConfigFile()
	{
		QString ConfigFilePath = QString( "%1/Config/sys.ini" ).arg( QCoreApplication::applicationDirPath() );
		return ConfigFilePath;
	};

	//获取配置路径
	static QString GetDefaultDeviceConfigPath()
	{
		QString ConfigFilePath = QString( "%1/Config" ).arg( QCoreApplication::applicationDirPath() );
		return ConfigFilePath;
	};

	//样式表路径
	static QString GetStylesheetFileName()
	{
		QString ConfigFilePath = QString( "%1/skin/qss/stylesheet.css" ).arg( QCoreApplication::applicationDirPath() );
		return ConfigFilePath;
	};

	//语言文件配置
	static QString GetLanguagePath()
	{
		QString ConfigFilePath = QString( "%1/language" ).arg( QCoreApplication::applicationDirPath() );
		return ConfigFilePath;
	};
};

#endif // APP_PATH_H