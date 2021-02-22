#include "LanguageSrc.h"
#include <QLocale>
#include <QSettings>

QSettings *CLanguageSrc::m_pLanguageSettings = NULL;
QString CLanguageSrc::m_strLanguageFolder = QString::null;
QString CLanguageSrc::m_strLanguage = QString::null;

CLanguageSrc::CLanguageSrc(void)
{
}

CLanguageSrc::~CLanguageSrc(void)
{

}


bool CLanguageSrc::Initial(const QString& szExePath)
{
    m_strLanguageFolder = szExePath;

    //先读取用户配置
    QString fileName = QString( "%1/LanguageIndex.ini" ).arg(  m_strLanguageFolder );
    QSettings settings( fileName, QSettings::IniFormat );
    settings.setIniCodec( "UTF-8" );

    QString strDefaultLanguage = settings.value("info/languagesSel").toString();
	m_strLanguage = settings.value( QString("languages/%1")
		.arg(strDefaultLanguage)).toString();

	QString strLanguagePath = QString( "%1/%2.ini" )
		.arg(m_strLanguageFolder)
		.arg(m_strLanguage);
  
    m_pLanguageSettings =  new QSettings( strLanguagePath, QSettings::IniFormat );
    m_pLanguageSettings->setIniCodec( "UTF-8" );
    m_pLanguageSettings->beginGroup( "text" );



    return true;
}

void CLanguageSrc::Quit(void)
{
	if (m_pLanguageSettings != NULL)
	{
		delete m_pLanguageSettings;
		m_pLanguageSettings = NULL;
	}
}

QString CLanguageSrc::GetResourceString(const char *szID)
{
	return GetResourceStringFromIni(szID);
}

////////////////////通过ID，获取字符串资源，默认为系统当前设置的语言，如果不存在则以英文代替
//若ID不存在则在中文语言中加此ID（字符串为ID)
QString CLanguageSrc::GetResourceStringFromIni( const char *szID )
{
    if( szID == NULL ||  QString( szID ).isEmpty() )
        return "";
    Q_CHECK_PTR( m_pLanguageSettings  );
    QString tmpStr = m_pLanguageSettings->value( szID ).toString();
	if (tmpStr.isEmpty())
	{
		tmpStr = QString::fromUtf8(szID);
	}
	return tmpStr;
}


QString CLanguageSrc::GetCurrentLanguage(void)
{
	return m_strLanguage;
}
