#ifndef APPCONFIG_H
#define APPCONFIG_H
#include "Singleton.h"
#include <QString>

#define BYTE_BUFFER_SIZE 255
class AppPath;
class AppConfig
{
	friend class CSingleton<AppConfig>;
public:
	AppConfig();
	bool Initial();//////初始化
	void Quit();//////退出 

	QString GetConfigFile();
	QString GetRunPath();

	QString GetStylesheetFileName();
	QString GetDeviceFileName();
	QString GetLanguageFileName();

	bool SetDllType(const QString& DllStr);
	QString GetPngPath();

	

	bool Set6CFrenyTable(const QString& FrenyTableStr);//这是6c的频点
	QString Get6CFrenyTable();
	bool Set6CAttachFunction(const QString& AttachFunctionStr);//设置6c附加功能
	QString Get6CAttachFunction();

	bool SetWirelessAnalysisTime(int isAnalysisTime);//设置无线的后七位解析为时间
	int GetWirelessAnalysisTime();

	bool IsUserType(); //是否是用户版
	QString GetLOADTYPE(); 
	bool SetLOADTYPE(const QString& loadTypeStr);

	bool GetSettingStr(const QString& keysStr, QString& valueStr,const QString& defaultStr);
	bool SetSettingStr(const QString& keysStr,const QString& valueStr);
	
	bool CheckIPEdit(const QString& str);//检查ip地址是否合法
	bool CheckIput16(const QString& str);//检测是否是16进制数
private:
	QString initDeviceFileName();

private:
	QString mRunPath;
	QString mConfigFile;
	QString mLanguagePath;
	QString mStylesheetFile;
	QString mDeviceConfigFile;
};


#endif // APPCONFIG_H
