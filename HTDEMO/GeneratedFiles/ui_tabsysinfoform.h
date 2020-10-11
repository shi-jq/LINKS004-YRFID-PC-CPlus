/********************************************************************************
** Form generated from reading UI file 'tabsysinfoform.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TABSYSINFOFORM_H
#define UI_TABSYSINFOFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TabSysInfoForm
{
public:
    QGridLayout *gridLayout_4;
    QFrame *frame;
    QGridLayout *gridLayout_2;
    QWidget *widget;
    QGridLayout *gridLayout;
    QLabel *label_6;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout;
    QWidget *widget_3;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_7;
    QWidget *widget_4;
    QWidget *widget_5;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_8;
    QWidget *widget_6;

    void setupUi(QWidget *TabSysInfoForm)
    {
        if (TabSysInfoForm->objectName().isEmpty())
            TabSysInfoForm->setObjectName(QStringLiteral("TabSysInfoForm"));
        TabSysInfoForm->resize(611, 530);
        gridLayout_4 = new QGridLayout(TabSysInfoForm);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        frame = new QFrame(TabSysInfoForm);
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
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(1, 1, 1, 1);
        label_6 = new QLabel(widget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setMinimumSize(QSize(0, 30));
        label_6->setMaximumSize(QSize(16777215, 30));
        label_6->setStyleSheet(QString::fromUtf8("font: 10pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"color: rgb(255, 255, 255);\n"
"background-color: rgb(168, 168, 168);\n"
"padding: 3px 3px 3px 10px;\n"
"border: none;\n"
"border-top-right-radius: 5px;\n"
"border-top-left-radius: 5px;"));

        gridLayout->addWidget(label_6, 0, 0, 1, 1);

        widget_2 = new QWidget(widget);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        widget_2->setStyleSheet(QLatin1String(".QWidget\n"
"{\n"
"	border: none;\n"
"	background-color: rgb(240, 241, 243);\n"
"}"));

        gridLayout->addWidget(widget_2, 1, 0, 1, 1);


        gridLayout_2->addWidget(widget, 0, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        widget_3 = new QWidget(frame);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        widget_3->setStyleSheet(QLatin1String(".QWidget\n"
"{\n"
"	border: 1px solid rgb(218,218,218);\n"
"	border-top-right-radius: 5px;\n"
"	border-top-left-radius: 5px;\n"
"}\n"
""));
        verticalLayout_2 = new QVBoxLayout(widget_3);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(1, 1, 1, 1);
        label_7 = new QLabel(widget_3);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setMinimumSize(QSize(0, 30));
        label_7->setMaximumSize(QSize(16777215, 30));
        label_7->setStyleSheet(QString::fromUtf8("font: 10pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"color: rgb(255, 255, 255);\n"
"background-color: rgb(168, 168, 168);\n"
"padding: 3px 3px 3px 10px;\n"
"border: none;\n"
"border-top-right-radius: 5px;\n"
"border-top-left-radius: 5px;\n"
""));

        verticalLayout_2->addWidget(label_7);

        widget_4 = new QWidget(widget_3);
        widget_4->setObjectName(QStringLiteral("widget_4"));
        widget_4->setStyleSheet(QLatin1String(".QWidget\n"
"{\n"
"	border: none;\n"
"	background-color: rgb(240, 241, 243);\n"
"}"));

        verticalLayout_2->addWidget(widget_4);


        verticalLayout->addWidget(widget_3);

        widget_5 = new QWidget(frame);
        widget_5->setObjectName(QStringLiteral("widget_5"));
        widget_5->setStyleSheet(QLatin1String(".QWidget\n"
"{\n"
"	border: 1px solid rgb(218,218,218);\n"
"	border-top-right-radius: 5px;\n"
"	border-top-left-radius: 5px;\n"
"}\n"
""));
        verticalLayout_3 = new QVBoxLayout(widget_5);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(1, 1, 1, 1);
        label_8 = new QLabel(widget_5);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setMinimumSize(QSize(0, 30));
        label_8->setMaximumSize(QSize(16777215, 30));
        label_8->setStyleSheet(QString::fromUtf8("font: 10pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"color: rgb(255, 255, 255);\n"
"background-color: rgb(168, 168, 168);\n"
"padding: 3px 3px 3px 10px;\n"
"border: none;\n"
"border-top-right-radius: 5px;\n"
"border-top-left-radius: 5px;\n"
""));

        verticalLayout_3->addWidget(label_8);

        widget_6 = new QWidget(widget_5);
        widget_6->setObjectName(QStringLiteral("widget_6"));
        widget_6->setStyleSheet(QLatin1String(".QWidget\n"
"{\n"
"	border: none;\n"
"	background-color: rgb(240, 241, 243);\n"
"}"));

        verticalLayout_3->addWidget(widget_6);


        verticalLayout->addWidget(widget_5);


        gridLayout_2->addLayout(verticalLayout, 0, 1, 1, 1);


        gridLayout_4->addWidget(frame, 0, 0, 1, 1);


        retranslateUi(TabSysInfoForm);

        QMetaObject::connectSlotsByName(TabSysInfoForm);
    } // setupUi

    void retranslateUi(QWidget *TabSysInfoForm)
    {
        TabSysInfoForm->setWindowTitle(QApplication::translate("TabSysInfoForm", "Form", Q_NULLPTR));
        label_6->setText(QApplication::translate("TabSysInfoForm", "\350\257\273\345\206\231\345\231\250\344\277\241\346\201\257", Q_NULLPTR));
        label_7->setText(QApplication::translate("TabSysInfoForm", "\345\233\272\344\273\266\345\215\207\347\272\247", Q_NULLPTR));
        label_8->setText(QApplication::translate("TabSysInfoForm", "\346\227\266\351\227\264\350\256\276\347\275\256", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class TabSysInfoForm: public Ui_TabSysInfoForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TABSYSINFOFORM_H
