#ifndef WIDGETCONFIG_H
#define WIDGETCONFIG_H
#include "Singleton.h"
#include <QString>
#include <QSettings>
#include "SetDebugNew.h"

#define WIDGETENABLE(widgetName,childName) CSingleton<WidgetConfig>::GetInstance()->GetWidgetEnable(widgetName,childName)
#define WIDGETSTRING_GET(widgetName,childName) CSingleton<WidgetConfig>::GetInstance()->GetConfigStr(widgetName,childName)
#define WIDGETSTRING_SET(widgetName,childName,strValue) CSingleton<WidgetConfig>::GetInstance()->SetConfigStr(widgetName,childName,strValue)

class AppPath;
class WidgetConfig
{
	friend class CSingleton<WidgetConfig>;
public:
	WidgetConfig();
	bool Initial(const QString& configName);//////³õÊ¼»¯
	void Quit();//////ÍË³ö 
	
	bool GetWidgetEnable(const char *widgetName,const char *childName);
	QString GetConfigStr(const char *widgetName,const char *childName);
	bool SetConfigStr(const char *widgetName,const char *childName,const char *Value);
private:	
	bool GetSettingStr(const QString& keysStr, QString& valueStr,const QString& defaultStr);
	bool SetSettingStr(const QString& keysStr,const QString& valueStr);

private:
	QString mConfigFile;
	QSettings* mSettings;


};


#endif // WIDGETCONFIG_H
