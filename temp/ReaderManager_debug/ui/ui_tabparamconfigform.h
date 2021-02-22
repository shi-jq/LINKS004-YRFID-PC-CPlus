/********************************************************************************
** Form generated from reading UI file 'tabparamconfigform.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TABPARAMCONFIGFORM_H
#define UI_TABPARAMCONFIGFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TabParamConfigForm
{
public:
    QGridLayout *gridLayout_3;
    QFrame *frame;
    QGridLayout *gridLayout_2;
    QWidget *widget;
    QGridLayout *gridLayout;
    QWidget *widget_2;

    void setupUi(QWidget *TabParamConfigForm)
    {
        if (TabParamConfigForm->objectName().isEmpty())
            TabParamConfigForm->setObjectName(QStringLiteral("TabParamConfigForm"));
        TabParamConfigForm->resize(400, 300);
        gridLayout_3 = new QGridLayout(TabParamConfigForm);
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        frame = new QFrame(TabParamConfigForm);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setStyleSheet(QLatin1String(".QFrame\n"
"{\n"
"	background-color: rgb(245, 245, 245);\n"
"}"));
        frame->setFrameShape(QFrame::NoFrame);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(frame);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        widget = new QWidget(frame);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setStyleSheet(QLatin1String(".QWidget\n"
"{\n"
"	border: 1px solid rgb(218,218,218);\n"
"	border-top-right-radius: 5px;\n"
"	border-top-left-radius: 5px;\n"
"}"));
        gridLayout = new QGridLayout(widget);
        gridLayout->setContentsMargins(1, 1, 1, 1);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        widget_2 = new QWidget(widget);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        widget_2->setStyleSheet(QLatin1String(".QWidget\n"
"{\n"
"	border: none;\n"
"	background-color: rgb(240, 241, 243);\n"
"}"));

        gridLayout->addWidget(widget_2, 0, 0, 1, 1);


        gridLayout_2->addWidget(widget, 0, 0, 1, 1);


        gridLayout_3->addWidget(frame, 0, 0, 1, 1);


        retranslateUi(TabParamConfigForm);

        QMetaObject::connectSlotsByName(TabParamConfigForm);
    } // setupUi

    void retranslateUi(QWidget *TabParamConfigForm)
    {
        TabParamConfigForm->setWindowTitle(QApplication::translate("TabParamConfigForm", "Form", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class TabParamConfigForm: public Ui_TabParamConfigForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TABPARAMCONFIGFORM_H
