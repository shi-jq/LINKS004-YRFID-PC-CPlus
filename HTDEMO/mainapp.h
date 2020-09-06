#ifndef MAINAPP_H
#define MAINAPP_H
#include <QDialog>
#include <QWidget>
#include <QString>
#include <wtypes.h>
#include "Singleton.h"
#include "readerdllbase.h"
#include "SetDebugNew.h"

class MainWindow;

#define pMainApp CSingleton<MainApp>::GetInstance()
#define MainShowMsg (CSingleton<MainApp>::GetInstance())->ShowMsg
#define SOFT_VERSION "V1.0.2"
class MainApp
{
	friend class CSingleton<MainApp>;
public:
	MainApp();
	bool Initial();//////��ʼ��
	void Quit();//////�˳�

	bool IsReading();
	void SetReading(bool isReading);
	//������ҳ��ָ��
	void SetMainWindow(MainWindow* pMainWindow)
	{
		this->pMainWindow = pMainWindow;
	};//
	MainWindow* GetMainWindow()
	{
		return pMainWindow;
	};

	void ShowMsg(QString str,bool getErro = false,bool getReader = true);
	void UpdateReaderState(int nConnetType);
	void CutConnet();
	bool ConnetReader();
	bool CloseReader();
	ReaderDllBase* GetReader();

	QString GetStrFromChar(unsigned char* , int len);
	
	//��str�л�ȡnlen(λ)�������ݷ���buff��,����buff����
	int getBitBuffFromStr(const QString& str,unsigned char* buff,int bitlen);

	int CheckTimeout(unsigned int start, unsigned int hasElapsed);
	unsigned int GetSysTickCount();
private:
	MainWindow* pMainWindow;

	bool mIsReading;

};

#endif // MAINAPP_H
