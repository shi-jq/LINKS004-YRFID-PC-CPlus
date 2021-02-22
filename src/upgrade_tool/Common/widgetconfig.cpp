#include "widgetconfig.h"
#include "AppPath.h"

WidgetConfig::WidgetConfig()
{
}

bool WidgetConfig::Initial(const QString& configName)
{
	mConfigFile = configName;
	mSettings =  new QSettings( mConfigFile, QSettings::IniFormat );
	mSettings->setIniCodec( "UTF-8" );

	return true;
}

void WidgetConfig::Quit()
{
	if (mSettings)
	{
		delete mSettings;
		mSettings = NULL;
	}
}

bool WidgetConfig::GetSettingStr(const QString& keysStr, QString& valueStr,const QString& defaultStr)
{
	if (mSettings)
	{
		valueStr = mSettings->value(keysStr,defaultStr).toString();
		return true;
	}
	return false;	
}


bool WidgetConfig::SetSettingStr(const QString& keysStr,const QString& valueStr)
{
	if (mSettings)
	{
		mSettings->setValue(keysStr,valueStr);
		return true;
	}
	
	return false;
}

bool WidgetConfig::GetWidgetEnable(const char *widgetName,const char *childName)
{
	QString strValue;
	if (GetSettingStr(QString("%1/%2").arg(widgetName).arg(childName), strValue,"0"))
	{
		if (strValue.toUInt() == 1)
		{
			return true;
		}
	}

	return false;
}

QString WidgetConfig::GetConfigStr(const char *widgetName,const char *childName)
{
	QString strValue = "";
	if (GetSettingStr(QString("%1/%2").arg(widgetName).arg(childName), strValue,""))
	{

	}
	return strValue;
}

bool WidgetConfig::SetConfigStr(const char *widgetName,const char *childName,const char *Value)
{
	return SetSettingStr(QString("%1/%2").arg(widgetName).arg(childName), Value);	
}


