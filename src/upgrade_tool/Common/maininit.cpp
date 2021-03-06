﻿#include "maininit.h"
#include <QApplication>
#include <QTextCodec>
#include <QFile>
//#include <QWindowsVistaStyle>
#include <QStyleFactory>
#include <QDebug>
#include <QFont>
#include "appconfig.h"
#include "widgetconfig.h"
#include "mainapp.h"
#include "LanguageSrc.h"

MainInit::MainInit()
{
}

bool MainInit::Initial()
{
	CSingleton<AppConfig>::GetInstance()->Initial();
	QString DeviceFileName = CSingleton<AppConfig>::GetInstance()->GetDeviceFileName();
	QString LanguageFileName = CSingleton<AppConfig>::GetInstance()->GetLanguageFileName();
	QString dllType = CSingleton<AppConfig>::GetInstance()->GetDllType();

	CSingleton<WidgetConfig>::GetInstance()->Initial(DeviceFileName);
	CLanguageSrc::Initial( LanguageFileName);


	return true;
}

void MainInit::Quit()
{
	CLanguageSrc::Quit();
	CSingleton<WidgetConfig>::GetInstance()->Quit();
	CSingleton<AppConfig>::GetInstance()->Quit();


	CSingleton<WidgetConfig>::ReleaseInstance();	
	CSingleton<AppConfig>::ReleaseInstance();
}

void MainInit::SetTextCodec()
{
#if QT_VERSION >= 0x050000
	//不设置VistaTreeWidget行选中绘制有残留
	qApp->setStyle( QStyleFactory::create( "Windows" ) ); 
#else
	QTextCodec::setCodecForTr( QTextCodec::codecForName( "GBK" ) );
	QTextCodec::setCodecForCStrings( QTextCodec::codecForName( "GBK" ) );
	QTextCodec::setCodecForLocale( QTextCodec::codecForLocale() );
#endif
}

/************************************************************************/
/* 加载样式表                                                                     */
/************************************************************************/
void MainInit::LoadStyleSheet()
{
	QFile file( CSingleton<AppConfig>::GetInstance()->GetStylesheetFileName());
	if ( file.open( QIODevice::ReadOnly ) )
	{
		qApp->setStyleSheet( file.readAll() );
		file.close();
	}
	else
	{
		qDebug() << file.errorString();
	}
}

void MainInit::SetFont()
{
	QFont font;
#if defined(Q_OS_WIN)
	font = QFont( "Microsoft YaHei" );
#elif defined(Q_WS_X11)
	font = QFont( "Microsoft YaHei" );
#elif defined(Q_WS_QWS)
	font = QFont( "Droid Sans Fallback" );//android默认中文字体
#elif defined(Q_OS_MAC)
	font = QFont( "Lucida Grande" );
#endif
	font.setPixelSize( 12 );
	qApp->setFont( font );
	qApp->setQuitOnLastWindowClosed( true );
	//qApp->setStyle(new QWindowsVistaStyle);
}

