/********************************************************************************
** Form generated from reading UI file 'wirelessreadconfigwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIRELESSREADCONFIGWIDGET_H
#define UI_WIRELESSREADCONFIGWIDGET_H

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

class Ui_wirelessreadconfigwidget
{
public:
    QGridLayout *gridLayout_2;
    QFrame *frame;
    QGridLayout *gridLayout;
    QWidget *widget_13;
    QVBoxLayout *verticalLayout_8;
    QLabel *label_18;
    QWidget *widget_14;
    QWidget *widget_11;
    QVBoxLayout *verticalLayout_7;
    QLabel *label_17;
    QWidget *widget_12;
    QWidget *widget_9;
    QVBoxLayout *verticalLayout_6;
    QLabel *label_16;
    QWidget *widget_10;

    void setupUi(QWidget *wirelessreadconfigwidget)
    {
        if (wirelessreadconfigwidget->objectName().isEmpty())
            wirelessreadconfigwidget->setObjectName(QStringLiteral("wirelessreadconfigwidget"));
        wirelessreadconfigwidget->resize(652, 431);
        gridLayout_2 = new QGridLayout(wirelessreadconfigwidget);
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        frame = new QFrame(wirelessreadconfigwidget);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setStyleSheet(QLatin1String(".QFrame\n"
"{\n"
"	background-color: rgb(245, 245, 245);\n"
"}"));
        frame->setFrameShape(QFrame::NoFrame);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(frame);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        widget_13 = new QWidget(frame);
        widget_13->setObjectName(QStringLiteral("widget_13"));
        widget_13->setStyleSheet(QLatin1String(".QWidget\n"
"{\n"
"	border: 1px solid rgb(218,218,218);\n"
"	border-top-right-radius: 5px;\n"
"	border-top-left-radius: 5px;\n"
"}\n"
""));
        verticalLayout_8 = new QVBoxLayout(widget_13);
        verticalLayout_8->setSpacing(0);
        verticalLayout_8->setContentsMargins(1, 1, 1, 1);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        label_18 = new QLabel(widget_13);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setMinimumSize(QSize(0, 30));
        label_18->setMaximumSize(QSize(16777215, 30));
        label_18->setStyleSheet(QString::fromUtf8("font: 10pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"color: rgb(255, 255, 255);\n"
"background-color: rgb(168, 168, 168);\n"
"padding: 3px 3px 3px 10px;\n"
"border: none;\n"
"border-top-right-radius: 5px;\n"
"border-top-left-radius: 5px;\n"
""));

        verticalLayout_8->addWidget(label_18);

        widget_14 = new QWidget(widget_13);
        widget_14->setObjectName(QStringLiteral("widget_14"));
        widget_14->setStyleSheet(QLatin1String(".QWidget\n"
"{\n"
"	border: none;\n"
"	background-color: rgb(240, 241, 243);\n"
"}"));

        verticalLayout_8->addWidget(widget_14);


        gridLayout->addWidget(widget_13, 0, 1, 1, 1);

        widget_11 = new QWidget(frame);
        widget_11->setObjectName(QStringLiteral("widget_11"));
        widget_11->setStyleSheet(QLatin1String(".QWidget\n"
"{\n"
"	border: 1px solid rgb(218,218,218);\n"
"	border-top-right-radius: 5px;\n"
"	border-top-left-radius: 5px;\n"
"}\n"
""));
        verticalLayout_7 = new QVBoxLayout(widget_11);
        verticalLayout_7->setSpacing(0);
        verticalLayout_7->setContentsMargins(1, 1, 1, 1);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        label_17 = new QLabel(widget_11);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setMinimumSize(QSize(0, 30));
        label_17->setMaximumSize(QSize(16777215, 30));
        label_17->setStyleSheet(QString::fromUtf8("font: 10pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"color: rgb(255, 255, 255);\n"
"background-color: rgb(168, 168, 168);\n"
"padding: 3px 3px 3px 10px;\n"
"border: none;\n"
"border-top-right-radius: 5px;\n"
"border-top-left-radius: 5px;\n"
""));

        verticalLayout_7->addWidget(label_17);

        widget_12 = new QWidget(widget_11);
        widget_12->setObjectName(QStringLiteral("widget_12"));
        widget_12->setStyleSheet(QLatin1String(".QWidget\n"
"{\n"
"	border: none;\n"
"	background-color: rgb(240, 241, 243);\n"
"}"));

        verticalLayout_7->addWidget(widget_12);


        gridLayout->addWidget(widget_11, 1, 1, 1, 1);

        widget_9 = new QWidget(frame);
        widget_9->setObjectName(QStringLiteral("widget_9"));
        widget_9->setStyleSheet(QLatin1String(".QWidget\n"
"{\n"
"	border: 1px solid rgb(218,218,218);\n"
"	border-top-right-radius: 5px;\n"
"	border-top-left-radius: 5px;\n"
"}\n"
""));
        verticalLayout_6 = new QVBoxLayout(widget_9);
        verticalLayout_6->setSpacing(0);
        verticalLayout_6->setContentsMargins(1, 1, 1, 1);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        label_16 = new QLabel(widget_9);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setMinimumSize(QSize(0, 30));
        label_16->setMaximumSize(QSize(16777215, 30));
        label_16->setStyleSheet(QString::fromUtf8("font: 10pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"color: rgb(255, 255, 255);\n"
"background-color: rgb(168, 168, 168);\n"
"padding: 3px 3px 3px 10px;\n"
"border: none;\n"
"border-top-right-radius: 5px;\n"
"border-top-left-radius: 5px;\n"
""));

        verticalLayout_6->addWidget(label_16);

        widget_10 = new QWidget(widget_9);
        widget_10->setObjectName(QStringLiteral("widget_10"));
        widget_10->setStyleSheet(QLatin1String(".QWidget\n"
"{\n"
"	border: none;\n"
"	background-color: rgb(240, 241, 243);\n"
"}"));

        verticalLayout_6->addWidget(widget_10);


        gridLayout->addWidget(widget_9, 0, 0, 2, 1);

        widget_9->raise();
        widget_11->raise();
        widget_13->raise();

        gridLayout_2->addWidget(frame, 0, 0, 1, 1);


        retranslateUi(wirelessreadconfigwidget);

        QMetaObject::connectSlotsByName(wirelessreadconfigwidget);
    } // setupUi

    void retranslateUi(QWidget *wirelessreadconfigwidget)
    {
        wirelessreadconfigwidget->setWindowTitle(QApplication::translate("wirelessreadconfigwidget", "Form", Q_NULLPTR));
        label_18->setText(QApplication::translate("wirelessreadconfigwidget", "\345\260\204\351\242\221\350\256\276\347\275\256", Q_NULLPTR));
        label_17->setText(QApplication::translate("wirelessreadconfigwidget", "\350\275\275\346\263\242\350\256\276\347\275\256", Q_NULLPTR));
        label_16->setText(QApplication::translate("wirelessreadconfigwidget", "\345\244\251\347\272\277\350\256\276\347\275\256", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class wirelessreadconfigwidget: public Ui_wirelessreadconfigwidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIRELESSREADCONFIGWIDGET_H
