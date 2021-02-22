/********************************************************************************
** Form generated from reading UI file 'tabforwardconfigform.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TABFORWARDCONFIGFORM_H
#define UI_TABFORWARDCONFIGFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
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
            TabForwardConfigForm->setObjectName(QStringLiteral("TabForwardConfigForm"));
        TabForwardConfigForm->resize(400, 300);
        gridLayout = new QGridLayout(TabForwardConfigForm);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        frame = new QFrame(TabForwardConfigForm);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(frame);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        widget = new QWidget(frame);
        widget->setObjectName(QStringLiteral("widget"));
        gridLayout_3 = new QGridLayout(widget);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(1, 1, 1, 1);
        widget_2 = new QWidget(widget);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        widget_2->setStyleSheet(QLatin1String(".QWidget\n"
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
        TabForwardConfigForm->setWindowTitle(QApplication::translate("TabForwardConfigForm", "Form", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class TabForwardConfigForm: public Ui_TabForwardConfigForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TABFORWARDCONFIGFORM_H
