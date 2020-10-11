#include "appconfig.h"
#include "AppPath.h"
#include <QSettings>
#include <QRegExp>
#include <QRegExpValidator>

AppConfig::AppConfig()
{
}

bool AppConfig::Initial()
{
	mRunPath = AppPath::GetAppDirPath();	
	mLanguagePath = AppPath::GetLanguagePath();
	mStylesheetFile = AppPath::GetStylesheetFileName();
	mDeviceConfigFile = initDeviceFileName();
	mConfigFile = mDeviceConfigFile;
	return true;
}

void AppConfig::Quit()
{

}

bool AppConfig::GetSettingStr(const QString& keysStr, QString& valueStr,const QString& defaultStr)
{
	QSettings  Settings(mConfigFile, QSettings::IniFormat);
	Settings.setIniCodec("UTF-8");

	valueStr = Settings.value(keysStr,defaultStr).toString();
	if (valueStr.isEmpty())
	{
		return false;
	}	

	return true;
}

bool AppConfig::SetSettingStr(const QString& keysStr,const QString& valueStr)
{
	QSettings  Settings(mConfigFile, QSettings::IniFormat);
	Settings.setIniCodec("UTF-8");
	Settings.setValue(keysStr,valueStr);		

	return true;
}

QString AppConfig::GetStylesheetFileName()
{
	return mStylesheetFile;
}

QString AppConfig::initDeviceFileName()
{
	return QString("%1/WirelessDemo.ini").arg(AppPath::GetDefaultDeviceConfigPath());
}

QString AppConfig::GetDeviceFileName()
{
	return mDeviceConfigFile;
}

QString AppConfig::GetLanguageFileName()
{
	return mLanguagePath;
}

QString AppConfig::GetDllType()
{
	QString keyStr = QString("DEVICE_CONFIG/DLL_TYPE");
	QString valueStr;
	QString defaultStr = "6C";
	GetSettingStr(keyStr,valueStr,defaultStr);
	return valueStr;
}


bool AppConfig::SetDllType(const QString& DllStr)
{
	QString keyStr = QString("DEVICE_CONFIG/DLL_TYPE");
	return SetSettingStr(keyStr,DllStr);
}


QString AppConfig::GetPngPath()
{
	QString FilePath = QString( "%1/skin" ).arg( mRunPath );
	return FilePath;
}

QString AppConfig::GetRunPath()
{
	return mRunPath;
}

QString AppConfig::GetConfigFile()
{
	return mConfigFile;
}

bool AppConfig::Set6CFrenyTable(const QString& FrenyTableStr)
{
	QString keyStr = QString("6CCONIFG/FrenyTable");
	return SetSettingStr(keyStr,FrenyTableStr);
}

QString AppConfig::Get6CFrenyTable()
{
	QString keyStr = QString("6CCONIFG/FrenyTable");
	QString valueStr;
	QString defaultStr = "China";
	GetSettingStr(keyStr,valueStr,defaultStr);
	return valueStr;
}

bool AppConfig::Set6CAttachFunction(const QString& AttachFunctionStr)
{
	QString keyStr = QString("6CCONIFG/AttachFunction");
	return SetSettingStr(keyStr,AttachFunctionStr);
}

QString AppConfig::Get6CAttachFunction()
{
	QString keyStr = QString("6CCONIFG/AttachFunction");
	QString valueStr;
	QString defaultStr = "NULL";
	GetSettingStr(keyStr,valueStr,defaultStr);
	return valueStr;
}

QString AppConfig::GetLOADTYPE()
{
	QString keyStr = QString("DEVICE_CONFIG/LOADTYPE");
	QString valueStr;
	QString defaultStr = "DEBUG";
	GetSettingStr(keyStr,valueStr,defaultStr);
	return valueStr;
}

bool AppConfig::SetLOADTYPE(const QString& loadTypeStr)
{
	QString keyStr = QString("DEVICE_CONFIG/LOADTYPE");
	return SetSettingStr(keyStr,loadTypeStr);
}

bool AppConfig::IsUserType()
{
	return (GetLOADTYPE().compare("RELEASE") == 0);
}

bool AppConfig::CheckIPEdit(const QString& str)
{
	QRegExp regexp( "((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)" );

	QRegExpValidator regexp_validator( regexp );
	int nPos = 0;
	if ( str.isEmpty() )
	{
		return false;
	}
	QString tmp = str;
	if ( !str.isEmpty() && regexp_validator.validate( tmp, nPos ) != QValidator::Acceptable )
	{
		return false;
	}
	return true;
}

bool AppConfig::CheckIput16(const QString& str)
{
	QRegExp regexp("[a-fA-F0-9]+$");
	QRegExpValidator regexp_validator( regexp );
	int nPos = 0;
	if ( str.isEmpty() )
	{
		return false;
	}
	QString tmp = str;
	if ( !str.isEmpty() && regexp_validator.validate( tmp, nPos ) != QValidator::Acceptable )
	{
		return false;
	}
	return true;
}

bool AppConfig::SetWirelessAnalysisTime(int isAnalysisTime)
{
	QString keyStr = QString("Wireless_Config/AnalysisTime");
	
	return SetSettingStr(keyStr,QString("%1").arg(isAnalysisTime));
}

int AppConfig::GetWirelessAnalysisTime()
{
	QString keyStr = QString("Wireless_Config/AnalysisTime");
	QString valueStr;
	QString defaultStr = "0";
	GetSettingStr(keyStr,valueStr,defaultStr);
	return valueStr.toInt();
}



