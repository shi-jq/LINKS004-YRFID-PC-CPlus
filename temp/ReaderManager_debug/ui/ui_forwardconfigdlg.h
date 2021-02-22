/********************************************************************************
** Form generated from reading UI file 'forwardconfigdlg.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORWARDCONFIGDLG_H
#define UI_FORWARDCONFIGDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ForwardConfigDlg
{
public:
    QGridLayout *gridLayout;
    QWidget *widget;

    void setupUi(QWidget *ForwardConfigDlg)
    {
        if (ForwardConfigDlg->objectName().isEmpty())
            ForwardConfigDlg->setObjectName(QStringLiteral("ForwardConfigDlg"));
        ForwardConfigDlg->resize(400, 300);
        gridLayout = new QGridLayout(ForwardConfigDlg);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        widget = new QWidget(ForwardConfigDlg);
        widget->setObjectName(QStringLiteral("widget"));

        gridLayout->addWidget(widget, 0, 0, 1, 1);


        retranslateUi(ForwardConfigDlg);

        QMetaObject::connectSlotsByName(ForwardConfigDlg);
    } // setupUi

    void retranslateUi(QWidget *ForwardConfigDlg)
    {
        ForwardConfigDlg->setWindowTitle(QApplication::translate("ForwardConfigDlg", "Form", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ForwardConfigDlg: public Ui_ForwardConfigDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORWARDCONFIGDLG_H
