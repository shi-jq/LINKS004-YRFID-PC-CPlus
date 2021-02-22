/********************************************************************************
** Form generated from reading UI file 'languagesetdlg.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LANGUAGESETDLG_H
#define UI_LANGUAGESETDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_LanguageSetDlg
{
public:

    void setupUi(QDialog *LanguageSetDlg)
    {
        if (LanguageSetDlg->objectName().isEmpty())
            LanguageSetDlg->setObjectName(QStringLiteral("LanguageSetDlg"));
        LanguageSetDlg->resize(400, 300);

        retranslateUi(LanguageSetDlg);

        QMetaObject::connectSlotsByName(LanguageSetDlg);
    } // setupUi

    void retranslateUi(QDialog *LanguageSetDlg)
    {
        LanguageSetDlg->setWindowTitle(QApplication::translate("LanguageSetDlg", "Dialog", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class LanguageSetDlg: public Ui_LanguageSetDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LANGUAGESETDLG_H
