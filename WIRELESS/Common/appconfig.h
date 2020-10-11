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
	bool Initial();//////��ʼ��
	void Quit();//////�˳� 

	QString GetConfigFile();
	QString GetRunPath();

	QString GetStylesheetFileName();
	QString GetDeviceFileName();
	QString GetLanguageFileName();
	QString GetDllType();
	bool SetDllType(const QString& DllStr);
	QString GetPngPath();

	

	bool Set6CFrenyTable(const QString& FrenyTableStr);//����6c��Ƶ��
	QString Get6CFrenyTable();
	bool Set6CAttachFunction(const QString& AttachFunctionStr);//����6c���ӹ���
	QString Get6CAttachFunction();

	bool SetWirelessAnalysisTime(int isAnalysisTime);//�������ߵĺ���λ����Ϊʱ��
	int GetWirelessAnalysisTime();

	bool IsUserType(); //�Ƿ����û���
	QString GetLOADTYPE(); 
	bool SetLOADTYPE(const QString& loadTypeStr);

	bool GetSettingStr(const QString& keysStr, QString& valueStr,const QString& defaultStr);
	bool SetSettingStr(const QString& keysStr,const QString& valueStr);
	
	bool CheckIPEdit(const QString& str);//���ip��ַ�Ƿ�Ϸ�
	bool CheckIput16(const QString& str);//����Ƿ���16������
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
