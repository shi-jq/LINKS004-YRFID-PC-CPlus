/********************************************************************************
** Form generated from reading UI file 'wirelesssysinfowidget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIRELESSSYSINFOWIDGET_H
#define UI_WIRELESSSYSINFOWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_wirelessSysInfoWidget
{
public:
    QGridLayout *gridLayout_5;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *horizontalSpacer_2;
    QWidget *widget_5;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_11;
    QWidget *widget_6;
    QGridLayout *gridLayout;
    QComboBox *comboBox;
    QLineEdit *lineEdit;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer_6;
    QWidget *widget_7;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_12;
    QWidget *widget_8;
    QGridLayout *gridLayout_4;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_7;
    QGridLayout *gridLayout_3;
    QTimeEdit *timeEdit;
    QDateEdit *dateEdit;
    QLabel *label_13;
    QLabel *label_14;
    QSpacerItem *horizontalSpacer_8;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *pushButton_4;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QSpacerItem *horizontalSpacer_5;

    void setupUi(QWidget *wirelessSysInfoWidget)
    {
        if (wirelessSysInfoWidget->objectName().isEmpty())
            wirelessSysInfoWidget->setObjectName(QStringLiteral("wirelessSysInfoWidget"));
        wirelessSysInfoWidget->resize(471, 334);
        gridLayout_5 = new QGridLayout(wirelessSysInfoWidget);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        verticalSpacer = new QSpacerItem(20, 74, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_5->addItem(verticalSpacer, 0, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(120, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer_3, 2, 3, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 73, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_5->addItem(verticalSpacer_2, 4, 1, 1, 2);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer_2, 1, 0, 1, 1);

        widget_5 = new QWidget(wirelessSysInfoWidget);
        widget_5->setObjectName(QStringLiteral("widget_5"));
        widget_5->setStyleSheet(QLatin1String(".QWidget\n"
"{\n"
"	border: 1px solid rgb(218,218,218);\n"
"	border-top-right-radius: 5px;\n"
"	border-top-left-radius: 5px;\n"
"}"));
        verticalLayout_3 = new QVBoxLayout(widget_5);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setContentsMargins(1, 1, 1, 1);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        label_11 = new QLabel(widget_5);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setMinimumSize(QSize(0, 30));
        label_11->setMaximumSize(QSize(16777215, 30));
        label_11->setStyleSheet(QString::fromUtf8("font: 10pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"color: rgb(255, 255, 255);\n"
"background-color: rgb(168, 168, 168);\n"
"padding: 3px 3px 3px 10px;\n"
"border: none;\n"
"border-top-right-radius: 5px;\n"
"border-top-left-radius: 5px;"));

        verticalLayout_3->addWidget(label_11);

        widget_6 = new QWidget(widget_5);
        widget_6->setObjectName(QStringLiteral("widget_6"));
        widget_6->setStyleSheet(QLatin1String(".QWidget\n"
"{\n"
"	border: none;\n"
"	background-color: rgb(240, 241, 243);\n"
"}"));
        gridLayout = new QGridLayout(widget_6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        comboBox = new QComboBox(widget_6);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        gridLayout->addWidget(comboBox, 0, 1, 1, 1);

        lineEdit = new QLineEdit(widget_6);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        gridLayout->addWidget(lineEdit, 0, 2, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton = new QPushButton(widget_6);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout->addWidget(pushButton);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_6);


        gridLayout->addLayout(horizontalLayout, 1, 1, 1, 2);


        verticalLayout_3->addWidget(widget_6);


        gridLayout_5->addWidget(widget_5, 1, 1, 2, 1);

        widget_7 = new QWidget(wirelessSysInfoWidget);
        widget_7->setObjectName(QStringLiteral("widget_7"));
        widget_7->setStyleSheet(QLatin1String(".QWidget\n"
"{\n"
"	border: 1px solid rgb(218,218,218);\n"
"	border-top-right-radius: 5px;\n"
"	border-top-left-radius: 5px;\n"
"}"));
        verticalLayout_4 = new QVBoxLayout(widget_7);
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setContentsMargins(1, 1, 1, 1);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        label_12 = new QLabel(widget_7);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setMinimumSize(QSize(0, 30));
        label_12->setMaximumSize(QSize(16777215, 30));
        label_12->setStyleSheet(QString::fromUtf8("font: 10pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"color: rgb(255, 255, 255);\n"
"background-color: rgb(168, 168, 168);\n"
"padding: 3px 3px 3px 10px;\n"
"border: none;\n"
"border-top-right-radius: 5px;\n"
"border-top-left-radius: 5px;"));

        verticalLayout_4->addWidget(label_12);

        widget_8 = new QWidget(widget_7);
        widget_8->setObjectName(QStringLiteral("widget_8"));
        widget_8->setStyleSheet(QLatin1String(".QWidget\n"
"{\n"
"	border: none;\n"
"	background-color: rgb(240, 241, 243);\n"
"}"));
        gridLayout_4 = new QGridLayout(widget_8);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_7);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        timeEdit = new QTimeEdit(widget_8);
        timeEdit->setObjectName(QStringLiteral("timeEdit"));

        gridLayout_3->addWidget(timeEdit, 1, 1, 1, 1);

        dateEdit = new QDateEdit(widget_8);
        dateEdit->setObjectName(QStringLiteral("dateEdit"));

        gridLayout_3->addWidget(dateEdit, 0, 1, 1, 1);

        label_13 = new QLabel(widget_8);
        label_13->setObjectName(QStringLiteral("label_13"));

        gridLayout_3->addWidget(label_13, 0, 0, 1, 1);

        label_14 = new QLabel(widget_8);
        label_14->setObjectName(QStringLiteral("label_14"));

        gridLayout_3->addWidget(label_14, 1, 0, 1, 1);


        horizontalLayout_3->addLayout(gridLayout_3);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_8);


        gridLayout_4->addLayout(horizontalLayout_3, 0, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);

        pushButton_4 = new QPushButton(widget_8);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));

        horizontalLayout_2->addWidget(pushButton_4);

        pushButton_2 = new QPushButton(widget_8);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout_2->addWidget(pushButton_2);

        pushButton_3 = new QPushButton(widget_8);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        horizontalLayout_2->addWidget(pushButton_3);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_5);


        gridLayout_4->addLayout(horizontalLayout_2, 1, 0, 1, 1);


        verticalLayout_4->addWidget(widget_8);


        gridLayout_5->addWidget(widget_7, 3, 1, 1, 1);


        retranslateUi(wirelessSysInfoWidget);

        QMetaObject::connectSlotsByName(wirelessSysInfoWidget);
    } // setupUi

    void retranslateUi(QWidget *wirelessSysInfoWidget)
    {
        wirelessSysInfoWidget->setWindowTitle(QApplication::translate("wirelessSysInfoWidget", "Form", Q_NULLPTR));
        label_11->setText(QApplication::translate("wirelessSysInfoWidget", "\350\256\276\345\244\207\344\277\241\346\201\257", Q_NULLPTR));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("wirelessSysInfoWidget", "\350\256\276\345\244\207\345\220\215", Q_NULLPTR)
        );
        pushButton->setText(QApplication::translate("wirelessSysInfoWidget", "\346\237\245\350\257\242", Q_NULLPTR));
        label_12->setText(QApplication::translate("wirelessSysInfoWidget", "\350\256\276\347\275\256\346\227\266\351\227\264", Q_NULLPTR));
        label_13->setText(QApplication::translate("wirelessSysInfoWidget", "\346\227\245\346\234\237", Q_NULLPTR));
        label_14->setText(QApplication::translate("wirelessSysInfoWidget", "\346\227\266\351\227\264", Q_NULLPTR));
        pushButton_4->setText(QApplication::translate("wirelessSysInfoWidget", "\346\237\245\350\257\242", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("wirelessSysInfoWidget", "\350\256\276\347\275\256", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("wirelessSysInfoWidget", "\350\256\276\347\275\256\345\275\223\345\211\215\347\263\273\347\273\237\346\227\266\351\227\264", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class wirelessSysInfoWidget: public Ui_wirelessSysInfoWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIRELESSSYSINFOWIDGET_H
