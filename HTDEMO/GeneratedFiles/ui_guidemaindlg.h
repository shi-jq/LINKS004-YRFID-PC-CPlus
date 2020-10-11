/********************************************************************************
** Form generated from reading UI file 'guidemaindlg.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUIDEMAINDLG_H
#define UI_GUIDEMAINDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_GuideMainDlg
{
public:

    void setupUi(QDialog *GuideMainDlg)
    {
        if (GuideMainDlg->objectName().isEmpty())
            GuideMainDlg->setObjectName(QStringLiteral("GuideMainDlg"));
        GuideMainDlg->resize(400, 300);

        retranslateUi(GuideMainDlg);

        QMetaObject::connectSlotsByName(GuideMainDlg);
    } // setupUi

    void retranslateUi(QDialog *GuideMainDlg)
    {
        GuideMainDlg->setWindowTitle(QApplication::translate("GuideMainDlg", "Dialog", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class GuideMainDlg: public Ui_GuideMainDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUIDEMAINDLG_H
