/********************************************************************************
** Form generated from reading UI file 'wirelessioctrlwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIRELESSIOCTRLWIDGET_H
#define UI_WIRELESSIOCTRLWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_wirelessioctrlwidget
{
public:
    QGridLayout *gridLayout;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QWidget *widget_5;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_8;
    QWidget *widget_6;
    QGridLayout *gridLayout_3;
    QGridLayout *gridLayout_2;
    QLabel *label;
    QComboBox *comboBox;
    QPushButton *pushButton;
    QLabel *label_2;
    QComboBox *comboBox_2;
    QPushButton *pushButton_2;
    QLabel *label_3;
    QComboBox *comboBox_3;
    QPushButton *pushButton_3;
    QLabel *label_4;
    QComboBox *comboBox_4;
    QPushButton *pushButton_4;
    QSpacerItem *verticalSpacer_2;
    QWidget *widget_9;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_10;
    QWidget *widget_10;
    QGridLayout *gridLayout_4;
    QSpacerItem *verticalSpacer_4;
    QLabel *label_7;
    QLabel *label_19;
    QCheckBox *checkBox_3;
    QCheckBox *checkBox_2;
    QSpinBox *spinBox_2;
    QLabel *label_23;
    QLabel *label_20;
    QLabel *label_13;
    QSpinBox *spinBox_5;
    QSpinBox *spinBox_4;
    QLabel *label_11;
    QCheckBox *checkBox_5;
    QLabel *label_12;
    QCheckBox *checkBox_4;
    QLabel *label_16;
    QLabel *label_15;
    QCheckBox *checkBox;
    QLabel *label_14;
    QSpinBox *spinBox_3;
    QLabel *label_22;
    QSpinBox *spinBox;
    QLabel *label_21;
    QLabel *label_17;
    QLabel *label_18;
    QLabel *label_24;
    QPushButton *pushButton_9;
    QPushButton *pushButton_10;
    QPushButton *pushButton_11;
    QPushButton *pushButton_8;
    QPushButton *pushButton_5;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *pushButton_7;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_3;

    void setupUi(QWidget *wirelessioctrlwidget)
    {
        if (wirelessioctrlwidget->objectName().isEmpty())
            wirelessioctrlwidget->setObjectName(QStringLiteral("wirelessioctrlwidget"));
        wirelessioctrlwidget->resize(631, 308);
        gridLayout = new QGridLayout(wirelessioctrlwidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 0, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        widget_5 = new QWidget(wirelessioctrlwidget);
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
"border-top-left-radius: 5px;"));

        verticalLayout_3->addWidget(label_8);

        widget_6 = new QWidget(widget_5);
        widget_6->setObjectName(QStringLiteral("widget_6"));
        widget_6->setStyleSheet(QLatin1String(".QWidget\n"
"{\n"
"	border: none;\n"
"	background-color: rgb(240, 241, 243);\n"
"}"));
        gridLayout_3 = new QGridLayout(widget_6);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        label = new QLabel(widget_6);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        comboBox = new QComboBox(widget_6);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        gridLayout_2->addWidget(comboBox, 0, 1, 1, 1);

        pushButton = new QPushButton(widget_6);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        gridLayout_2->addWidget(pushButton, 0, 2, 1, 1);

        label_2 = new QLabel(widget_6);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_2->addWidget(label_2, 1, 0, 1, 1);

        comboBox_2 = new QComboBox(widget_6);
        comboBox_2->setObjectName(QStringLiteral("comboBox_2"));

        gridLayout_2->addWidget(comboBox_2, 1, 1, 1, 1);

        pushButton_2 = new QPushButton(widget_6);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        gridLayout_2->addWidget(pushButton_2, 1, 2, 1, 1);

        label_3 = new QLabel(widget_6);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout_2->addWidget(label_3, 2, 0, 1, 1);

        comboBox_3 = new QComboBox(widget_6);
        comboBox_3->setObjectName(QStringLiteral("comboBox_3"));

        gridLayout_2->addWidget(comboBox_3, 2, 1, 1, 1);

        pushButton_3 = new QPushButton(widget_6);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        gridLayout_2->addWidget(pushButton_3, 2, 2, 1, 1);

        label_4 = new QLabel(widget_6);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout_2->addWidget(label_4, 3, 0, 1, 1);

        comboBox_4 = new QComboBox(widget_6);
        comboBox_4->setObjectName(QStringLiteral("comboBox_4"));

        gridLayout_2->addWidget(comboBox_4, 3, 1, 1, 1);

        pushButton_4 = new QPushButton(widget_6);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));

        gridLayout_2->addWidget(pushButton_4, 3, 2, 1, 1);


        gridLayout_3->addLayout(gridLayout_2, 0, 0, 1, 1);


        verticalLayout_3->addWidget(widget_6);


        verticalLayout->addWidget(widget_5);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);


        horizontalLayout_2->addLayout(verticalLayout);

        widget_9 = new QWidget(wirelessioctrlwidget);
        widget_9->setObjectName(QStringLiteral("widget_9"));
        widget_9->setStyleSheet(QLatin1String(".QWidget\n"
"{\n"
"	border: 1px solid rgb(218,218,218);\n"
"	border-top-right-radius: 5px;\n"
"	border-top-left-radius: 5px;\n"
"}"));
        verticalLayout_5 = new QVBoxLayout(widget_9);
        verticalLayout_5->setSpacing(0);
        verticalLayout_5->setContentsMargins(1, 1, 1, 1);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
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
"border-top-left-radius: 5px;"));

        verticalLayout_5->addWidget(label_10);

        widget_10 = new QWidget(widget_9);
        widget_10->setObjectName(QStringLiteral("widget_10"));
        widget_10->setStyleSheet(QLatin1String(".QWidget\n"
"{\n"
"	border: none;\n"
"	background-color: rgb(240, 241, 243);\n"
"}"));
        gridLayout_4 = new QGridLayout(widget_10);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_4->addItem(verticalSpacer_4, 5, 2, 1, 1);

        label_7 = new QLabel(widget_10);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout_4->addWidget(label_7, 0, 0, 1, 1);

        label_19 = new QLabel(widget_10);
        label_19->setObjectName(QStringLiteral("label_19"));

        gridLayout_4->addWidget(label_19, 4, 2, 1, 1);

        checkBox_3 = new QCheckBox(widget_10);
        checkBox_3->setObjectName(QStringLiteral("checkBox_3"));

        gridLayout_4->addWidget(checkBox_3, 2, 1, 1, 1);

        checkBox_2 = new QCheckBox(widget_10);
        checkBox_2->setObjectName(QStringLiteral("checkBox_2"));

        gridLayout_4->addWidget(checkBox_2, 1, 1, 1, 1);

        spinBox_2 = new QSpinBox(widget_10);
        spinBox_2->setObjectName(QStringLiteral("spinBox_2"));

        gridLayout_4->addWidget(spinBox_2, 1, 3, 1, 1);

        label_23 = new QLabel(widget_10);
        label_23->setObjectName(QStringLiteral("label_23"));

        gridLayout_4->addWidget(label_23, 3, 4, 1, 1);

        label_20 = new QLabel(widget_10);
        label_20->setObjectName(QStringLiteral("label_20"));

        gridLayout_4->addWidget(label_20, 0, 4, 1, 1);

        label_13 = new QLabel(widget_10);
        label_13->setObjectName(QStringLiteral("label_13"));

        gridLayout_4->addWidget(label_13, 3, 0, 1, 1);

        spinBox_5 = new QSpinBox(widget_10);
        spinBox_5->setObjectName(QStringLiteral("spinBox_5"));

        gridLayout_4->addWidget(spinBox_5, 4, 3, 1, 1);

        spinBox_4 = new QSpinBox(widget_10);
        spinBox_4->setObjectName(QStringLiteral("spinBox_4"));

        gridLayout_4->addWidget(spinBox_4, 3, 3, 1, 1);

        label_11 = new QLabel(widget_10);
        label_11->setObjectName(QStringLiteral("label_11"));

        gridLayout_4->addWidget(label_11, 1, 0, 1, 1);

        checkBox_5 = new QCheckBox(widget_10);
        checkBox_5->setObjectName(QStringLiteral("checkBox_5"));

        gridLayout_4->addWidget(checkBox_5, 4, 1, 1, 1);

        label_12 = new QLabel(widget_10);
        label_12->setObjectName(QStringLiteral("label_12"));

        gridLayout_4->addWidget(label_12, 2, 0, 1, 1);

        checkBox_4 = new QCheckBox(widget_10);
        checkBox_4->setObjectName(QStringLiteral("checkBox_4"));

        gridLayout_4->addWidget(checkBox_4, 3, 1, 1, 1);

        label_16 = new QLabel(widget_10);
        label_16->setObjectName(QStringLiteral("label_16"));

        gridLayout_4->addWidget(label_16, 1, 2, 1, 1);

        label_15 = new QLabel(widget_10);
        label_15->setObjectName(QStringLiteral("label_15"));

        gridLayout_4->addWidget(label_15, 0, 2, 1, 1);

        checkBox = new QCheckBox(widget_10);
        checkBox->setObjectName(QStringLiteral("checkBox"));

        gridLayout_4->addWidget(checkBox, 0, 1, 1, 1);

        label_14 = new QLabel(widget_10);
        label_14->setObjectName(QStringLiteral("label_14"));

        gridLayout_4->addWidget(label_14, 4, 0, 1, 1);

        spinBox_3 = new QSpinBox(widget_10);
        spinBox_3->setObjectName(QStringLiteral("spinBox_3"));

        gridLayout_4->addWidget(spinBox_3, 2, 3, 1, 1);

        label_22 = new QLabel(widget_10);
        label_22->setObjectName(QStringLiteral("label_22"));

        gridLayout_4->addWidget(label_22, 2, 4, 1, 1);

        spinBox = new QSpinBox(widget_10);
        spinBox->setObjectName(QStringLiteral("spinBox"));

        gridLayout_4->addWidget(spinBox, 0, 3, 1, 1);

        label_21 = new QLabel(widget_10);
        label_21->setObjectName(QStringLiteral("label_21"));

        gridLayout_4->addWidget(label_21, 1, 4, 1, 1);

        label_17 = new QLabel(widget_10);
        label_17->setObjectName(QStringLiteral("label_17"));

        gridLayout_4->addWidget(label_17, 2, 2, 1, 1);

        label_18 = new QLabel(widget_10);
        label_18->setObjectName(QStringLiteral("label_18"));

        gridLayout_4->addWidget(label_18, 3, 2, 1, 1);

        label_24 = new QLabel(widget_10);
        label_24->setObjectName(QStringLiteral("label_24"));

        gridLayout_4->addWidget(label_24, 4, 4, 1, 1);

        pushButton_9 = new QPushButton(widget_10);
        pushButton_9->setObjectName(QStringLiteral("pushButton_9"));

        gridLayout_4->addWidget(pushButton_9, 2, 5, 1, 1);

        pushButton_10 = new QPushButton(widget_10);
        pushButton_10->setObjectName(QStringLiteral("pushButton_10"));

        gridLayout_4->addWidget(pushButton_10, 3, 5, 1, 1);

        pushButton_11 = new QPushButton(widget_10);
        pushButton_11->setObjectName(QStringLiteral("pushButton_11"));

        gridLayout_4->addWidget(pushButton_11, 4, 5, 1, 1);

        pushButton_8 = new QPushButton(widget_10);
        pushButton_8->setObjectName(QStringLiteral("pushButton_8"));

        gridLayout_4->addWidget(pushButton_8, 1, 5, 1, 1);

        pushButton_5 = new QPushButton(widget_10);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));

        gridLayout_4->addWidget(pushButton_5, 0, 5, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        pushButton_7 = new QPushButton(widget_10);
        pushButton_7->setObjectName(QStringLiteral("pushButton_7"));

        horizontalLayout->addWidget(pushButton_7);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);


        gridLayout_4->addLayout(horizontalLayout, 6, 0, 1, 6);


        verticalLayout_5->addWidget(widget_10);


        horizontalLayout_2->addWidget(widget_9);


        gridLayout->addLayout(horizontalLayout_2, 1, 1, 2, 2);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 2, 3, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 26, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_3, 3, 2, 1, 1);


        retranslateUi(wirelessioctrlwidget);

        QMetaObject::connectSlotsByName(wirelessioctrlwidget);
    } // setupUi

    void retranslateUi(QWidget *wirelessioctrlwidget)
    {
        wirelessioctrlwidget->setWindowTitle(QApplication::translate("wirelessioctrlwidget", "Form", Q_NULLPTR));
        label_8->setText(QApplication::translate("wirelessioctrlwidget", "IO\346\216\247\345\210\266", Q_NULLPTR));
        label->setText(QApplication::translate("wirelessioctrlwidget", "V1", Q_NULLPTR));
        pushButton->setText(QApplication::translate("wirelessioctrlwidget", "\351\205\215\347\275\256", Q_NULLPTR));
        label_2->setText(QApplication::translate("wirelessioctrlwidget", "V2", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("wirelessioctrlwidget", "\351\205\215\347\275\256", Q_NULLPTR));
        label_3->setText(QApplication::translate("wirelessioctrlwidget", "OUT1", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("wirelessioctrlwidget", "\351\205\215\347\275\256", Q_NULLPTR));
        label_4->setText(QApplication::translate("wirelessioctrlwidget", "OUT2", Q_NULLPTR));
        pushButton_4->setText(QApplication::translate("wirelessioctrlwidget", "\351\205\215\347\275\256", Q_NULLPTR));
        label_10->setText(QApplication::translate("wirelessioctrlwidget", "\346\216\247\345\210\266\350\276\223\345\207\272", Q_NULLPTR));
        label_7->setText(QApplication::translate("wirelessioctrlwidget", "\350\234\202\351\270\243\345\231\250", Q_NULLPTR));
        label_19->setText(QApplication::translate("wirelessioctrlwidget", "\350\204\211\345\206\262\345\256\275\345\272\246", Q_NULLPTR));
        checkBox_3->setText(QApplication::translate("wirelessioctrlwidget", "\350\276\223\345\207\272", Q_NULLPTR));
        checkBox_2->setText(QApplication::translate("wirelessioctrlwidget", "\350\276\223\345\207\272", Q_NULLPTR));
        label_23->setText(QApplication::translate("wirelessioctrlwidget", "X100ms", Q_NULLPTR));
        label_20->setText(QApplication::translate("wirelessioctrlwidget", "X100ms", Q_NULLPTR));
        label_13->setText(QApplication::translate("wirelessioctrlwidget", "OUT1", Q_NULLPTR));
        label_11->setText(QApplication::translate("wirelessioctrlwidget", "V1", Q_NULLPTR));
        checkBox_5->setText(QApplication::translate("wirelessioctrlwidget", "\350\276\223\345\207\272", Q_NULLPTR));
        label_12->setText(QApplication::translate("wirelessioctrlwidget", "V2", Q_NULLPTR));
        checkBox_4->setText(QApplication::translate("wirelessioctrlwidget", "\350\276\223\345\207\272", Q_NULLPTR));
        label_16->setText(QApplication::translate("wirelessioctrlwidget", "\350\204\211\345\206\262\345\256\275\345\272\246", Q_NULLPTR));
        label_15->setText(QApplication::translate("wirelessioctrlwidget", "\350\204\211\345\206\262\345\256\275\345\272\246", Q_NULLPTR));
        checkBox->setText(QApplication::translate("wirelessioctrlwidget", "\350\276\223\345\207\272", Q_NULLPTR));
        label_14->setText(QApplication::translate("wirelessioctrlwidget", "OUT2", Q_NULLPTR));
        label_22->setText(QApplication::translate("wirelessioctrlwidget", "X100ms", Q_NULLPTR));
        label_21->setText(QApplication::translate("wirelessioctrlwidget", "X100ms", Q_NULLPTR));
        label_17->setText(QApplication::translate("wirelessioctrlwidget", "\350\204\211\345\206\262\345\256\275\345\272\246", Q_NULLPTR));
        label_18->setText(QApplication::translate("wirelessioctrlwidget", "\350\204\211\345\206\262\345\256\275\345\272\246", Q_NULLPTR));
        label_24->setText(QApplication::translate("wirelessioctrlwidget", "X100ms", Q_NULLPTR));
        pushButton_9->setText(QApplication::translate("wirelessioctrlwidget", "\346\237\245\350\257\242", Q_NULLPTR));
        pushButton_10->setText(QApplication::translate("wirelessioctrlwidget", "\346\237\245\350\257\242", Q_NULLPTR));
        pushButton_11->setText(QApplication::translate("wirelessioctrlwidget", "\346\237\245\350\257\242", Q_NULLPTR));
        pushButton_8->setText(QApplication::translate("wirelessioctrlwidget", "\346\237\245\350\257\242", Q_NULLPTR));
        pushButton_5->setText(QApplication::translate("wirelessioctrlwidget", "\346\237\245\350\257\242", Q_NULLPTR));
        pushButton_7->setText(QApplication::translate("wirelessioctrlwidget", "\346\211\247\350\241\214", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class wirelessioctrlwidget: public Ui_wirelessioctrlwidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIRELESSIOCTRLWIDGET_H
