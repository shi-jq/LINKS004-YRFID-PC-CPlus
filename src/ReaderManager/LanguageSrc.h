#ifndef LANGUAGE_SRC_HEAD
#define LANGUAGE_SRC_HEAD

#include <QString>
/*
使用QSetting 处理ini文件,
从语言文件中通过键值来取得相对应的翻译
*/
class QSettings;

class CLanguageSrc
{
public:
	CLanguageSrc(void);
	~CLanguageSrc(void);
	static bool Initial(const QString& szExePath);
	static void Quit(void);
	static QString GetResourceString(const char *szID);

	static QString GetCurrentLanguage(void);
private:
	static QString GetResourceStringFromIni(const char *szID);

private:
    static QSettings *m_pLanguageSettings;
	static QString m_strLanguageFolder;
	static QString m_strLanguage;
};

#define GET_TXT(szID)  CLanguageSrc::GetResourceString(szID)

#endif //LANGUAGE_SRC_HEAD
