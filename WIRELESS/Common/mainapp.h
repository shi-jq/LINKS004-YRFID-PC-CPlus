#ifndef MAINAPP_H
#define MAINAPP_H
#include <QDialog>
#include <QWidget>
#include <QString>
#include <wtypes.h>
#include "Singleton.h"
#include "SetDebugNew.h"

class MainWindow;

#define pMainApp CSingleton<MainApp>::GetInstance()
#define MainShowMsg (CSingleton<MainApp>::GetInstance())->ShowMsg
#define SOFT_VERSION "V1.0.0"
class MainApp
{
	friend class CSingleton<MainApp>;
public:
	MainApp();
	bool Initial();//////初始化
	void Quit();//////退出 
	//保存主页面指针
	void SetMainWindow(MainWindow* pMainWindow)
	{
		this->pMainWindow = pMainWindow;
	};//
	MainWindow* GetMainWindow()
	{
		return pMainWindow;
	};

	void ShowMsg(QString str,bool getErro = false);
	void UpdateReaderState(int nConnetType);

	QString GetStrFromChar(unsigned char* , int len);
	
	//从str中获取nlen(位)长的数据放入buff中,返回buff长度
	int getBitBuffFromStr(const QString& str,unsigned char* buff,int bitlen);

	int CheckTimeout(unsigned int start, unsigned int hasElapsed);
	unsigned int GetSysTickCount();

private:
	MainWindow* pMainWindow;

};

#endif // MAINAPP_H
