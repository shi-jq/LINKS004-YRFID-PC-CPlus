#include "adb_tool.h"
#include <QApplication>
#include <QTextCodec>
#include <QFile>
#include <QDebug>
#include <QFont>
//#include <QWindowsVistaStyle>
#include <QStyleFactory>
#include "SetDebugNew.h"
#include "appconfig.h"
#include "widgetconfig.h"
#include "maininit.h"


int main(int argc, char *argv[])
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif	

	MainInit mMainInit;
	int ret = 0;
	QApplication a(argc, argv);


	bool isReboot = false;
	do
	{
		mMainInit.Initial();
		mMainInit.SetTextCodec();
		mMainInit.LoadStyleSheet();
		mMainInit.SetFont();
		{
			adb_tool w;
			w.show();
			ret = a.exec();

			isReboot = w.GetNeedReboot();
		}
		mMainInit.Quit();

	} while (isReboot);

	


#if defined(WIN32) && defined(_DEBUG)  
	setFilterDebugHook();
#endif 
	return ret;
}
