/********************************************************************************
** Form generated from reading UI file 'tabforwardconfigform.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TABFORWARDCONFIGFORM_H
#define UI_TABFORWARDCONFIGFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TabForwardConfigForm
{
public:
    QGridLayout *gridLayout;
    QFrame *frame;
    QGridLayout *gridLayout_2;
    QWidget *widget;
    QGridLayout *gridLayout_3;
    QWidget *widget_2;

    void setupUi(QWidget *TabForwardConfigForm)
    {
        if (TabForwardConfigForm->objectName().isEmpty())
            TabForwardConfigForm->setObjectName(QString::fromUtf8("TabForwardConfigForm"));
        TabForwardConfigForm->resize(400, 300);
        gridLayout = new QGridLayout(TabForwardConfigForm);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        frame = new QFrame(TabForwardConfigForm);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(frame);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        widget = new QWidget(frame);
        widget->setObjectName(QString::fromUtf8("widget"));
        gridLayout_3 = new QGridLayout(widget);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(1, 1, 1, 1);
        widget_2 = new QWidget(widget);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget_2->setStyleSheet(QString::fromUtf8(".QWidget\n"
"{\n"
"	border: none;\n"
"	background-color: rgb(240, 241, 243);\n"
"}"));

        gridLayout_3->addWidget(widget_2, 0, 0, 1, 1);


        gridLayout_2->addWidget(widget, 0, 0, 1, 1);


        gridLayout->addWidget(frame, 0, 0, 1, 1);


        retranslateUi(TabForwardConfigForm);

        QMetaObject::connectSlotsByName(TabForwardConfigForm);
    } // setupUi

    void retranslateUi(QWidget *TabForwardConfigForm)
    {
        TabForwardConfigForm->setWindowTitle(QCoreApplication::translate("TabForwardConfigForm", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TabForwardConfigForm: public Ui_TabForwardConfigForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TABFORWARDCONFIGFORM_H
