
#include <QApplication>
#include <QTextCodec>
#include <QFile>
#include <QDebug>
#include <QFont>
//#include <QWindowsVistaStyle>
#include <QStyleFactory>
#include "SetDebugNew.h"
#include "appconfig.h"
#include "mainwindow.h"
#include "widgetconfig.h"
#include "maininit.h"

class QFont;
int main(int argc, char *argv[])
{

#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF|_CRTDBG_LEAK_CHECK_DF);
#endif	

	int nRet;
	bool isReboot = true;
	MainInit mMainInit;	
	QApplication a(argc, argv);
	while(isReboot)
	{	
		mMainInit.Initial();
		mMainInit.SetTextCodec();
		mMainInit.LoadStyleSheet();
		mMainInit.SetFont();
		{
			MainWindow w;		
			w.show();	
			nRet = a.exec();			
			isReboot = w.isNeedReboot();
		}
		mMainInit.Quit();		
	}	
	
#if defined(WIN32) && defined(_DEBUG)  
	setFilterDebugHook();  
#endif 
    return nRet;
}
