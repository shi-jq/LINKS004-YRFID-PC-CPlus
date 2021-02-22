/********************************************************************************
** Form generated from reading UI file 'tabconnetinfoform.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TABCONNETINFOFORM_H
#define UI_TABCONNETINFOFORM_H

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

class Ui_TabConnetInfoForm
{
public:
    QGridLayout *gridLayout_3;
    QFrame *frame;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout_6;
    QWidget *widget_5;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_8;
    QWidget *widget_6;
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QGridLayout *gridLayout;
    QLabel *label_6;
    QWidget *widget_2;
    QWidget *widget_3;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_7;
    QWidget *widget_4;
    QWidget *widget_9;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_10;
    QWidget *widget_10;

    void setupUi(QWidget *TabConnetInfoForm)
    {
        if (TabConnetInfoForm->objectName().isEmpty())
            TabConnetInfoForm->setObjectName(QStringLiteral("TabConnetInfoForm"));
        TabConnetInfoForm->resize(400, 300);
        gridLayout_3 = new QGridLayout(TabConnetInfoForm);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        frame = new QFrame(TabConnetInfoForm);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setStyleSheet(QLatin1String(".QFrame\n"
"{\n"
"	background-color: rgb(245, 245, 245);\n"
"}"));
        frame->setFrameShape(QFrame::NoFrame);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(frame);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
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


        verticalLayout_6->addWidget(widget_5);


        gridLayout_2->addLayout(verticalLayout_6, 0, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
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
        gridLayout->setVerticalSpacing(0);
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


        verticalLayout->addWidget(widget);

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

        widget_9 = new QWidget(frame);
        widget_9->setObjectName(QStringLiteral("widget_9"));
        widget_9->setStyleSheet(QLatin1String(".QWidget\n"
"{\n"
"	border: 1px solid rgb(218,218,218);\n"
"	border-top-right-radius: 5px;\n"
"	border-top-left-radius: 5px;\n"
"}\n"
""));
        verticalLayout_5 = new QVBoxLayout(widget_9);
        verticalLayout_5->setSpacing(0);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(1, 1, 1, 1);
        label_10 = new QLabel(widget_9);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setMinimumSize(QSize(0, 30));
        label_10->setMaximumSize(QSize(16777215, 30));
        label_10->setStyleSheet(QString::fromUtf8("font: 10pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"color: rgb(255, 255, 255);\n"
"background-color: rgb(168, 168, 168);\n"
"padding: 3px 3px 3px 10px;\n"
"border: none;\n"
"border-top-right-radius: 5px;\n"
"border-top-left-radius: 5px;\n"
""));

        verticalLayout_5->addWidget(label_10);

        widget_10 = new QWidget(widget_9);
        widget_10->setObjectName(QStringLiteral("widget_10"));
        widget_10->setStyleSheet(QLatin1String(".QWidget\n"
"{\n"
"	border: none;\n"
"	background-color: rgb(240, 241, 243);\n"
"}"));

        verticalLayout_5->addWidget(widget_10);


        verticalLayout->addWidget(widget_9);


        gridLayout_2->addLayout(verticalLayout, 0, 1, 1, 1);


        gridLayout_3->addWidget(frame, 0, 0, 1, 1);


        retranslateUi(TabConnetInfoForm);

        QMetaObject::connectSlotsByName(TabConnetInfoForm);
    } // setupUi

    void retranslateUi(QWidget *TabConnetInfoForm)
    {
        TabConnetInfoForm->setWindowTitle(QApplication::translate("TabConnetInfoForm", "Form", Q_NULLPTR));
        label_8->setText(QApplication::translate("TabConnetInfoForm", "\347\275\221\347\273\234\351\205\215\347\275\256", Q_NULLPTR));
        label_6->setText(QApplication::translate("TabConnetInfoForm", "\344\270\262\345\217\243", Q_NULLPTR));
        label_7->setText(QApplication::translate("TabConnetInfoForm", "\346\200\273\347\272\277\345\234\260\345\235\200", Q_NULLPTR));
        label_10->setText(QApplication::translate("TabConnetInfoForm", "\351\237\246\346\240\271\351\205\215\347\275\256", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class TabConnetInfoForm: public Ui_TabConnetInfoForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TABCONNETINFOFORM_H
