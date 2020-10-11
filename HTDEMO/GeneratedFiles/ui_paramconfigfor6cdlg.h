/********************************************************************************
** Form generated from reading UI file 'paramconfigfor6cdlg.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PARAMCONFIGFOR6CDLG_H
#define UI_PARAMCONFIGFOR6CDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ParamConfigFor6CDlg
{
public:
    QGridLayout *gridLayout;
    QWidget *widget;

    void setupUi(QWidget *ParamConfigFor6CDlg)
    {
        if (ParamConfigFor6CDlg->objectName().isEmpty())
            ParamConfigFor6CDlg->setObjectName(QStringLiteral("ParamConfigFor6CDlg"));
        ParamConfigFor6CDlg->resize(430, 228);
        gridLayout = new QGridLayout(ParamConfigFor6CDlg);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        widget = new QWidget(ParamConfigFor6CDlg);
        widget->setObjectName(QStringLiteral("widget"));

        gridLayout->addWidget(widget, 0, 0, 1, 1);


        retranslateUi(ParamConfigFor6CDlg);

        QMetaObject::connectSlotsByName(ParamConfigFor6CDlg);
    } // setupUi

    void retranslateUi(QWidget *ParamConfigFor6CDlg)
    {
        ParamConfigFor6CDlg->setWindowTitle(QApplication::translate("ParamConfigFor6CDlg", "Form", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ParamConfigFor6CDlg: public Ui_ParamConfigFor6CDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PARAMCONFIGFOR6CDLG_H
