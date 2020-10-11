/********************************************************************************
** Form generated from reading UI file 'wirelessrecv.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIRELESSRECV_H
#define UI_WIRELESSRECV_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_wirelessrecv
{
public:
    QGridLayout *gridLayout_2;
    QWidget *widget_5;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_8;
    QWidget *widget_6;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton_6;
    QPushButton *pushButton_5;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_5;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox;
    QPushButton *pushButton_3;
    QTreeWidget *treeWidget;

    void setupUi(QWidget *wirelessrecv)
    {
        if (wirelessrecv->objectName().isEmpty())
            wirelessrecv->setObjectName(QStringLiteral("wirelessrecv"));
        wirelessrecv->resize(867, 382);
        gridLayout_2 = new QGridLayout(wirelessrecv);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, -1, 0, 0);
        widget_5 = new QWidget(wirelessrecv);
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
        gridLayout = new QGridLayout(widget_6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        pushButton = new QPushButton(widget_6);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout_2->addWidget(pushButton);

        pushButton_2 = new QPushButton(widget_6);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout_2->addWidget(pushButton_2);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);


        gridLayout->addLayout(horizontalLayout_2, 0, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        pushButton_6 = new QPushButton(widget_6);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));

        horizontalLayout_3->addWidget(pushButton_6);

        pushButton_5 = new QPushButton(widget_6);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));
        pushButton_5->setStyleSheet(QStringLiteral(""));

        horizontalLayout_3->addWidget(pushButton_5);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);


        gridLayout->addLayout(horizontalLayout_3, 0, 1, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_5);

        checkBox_2 = new QCheckBox(widget_6);
        checkBox_2->setObjectName(QStringLiteral("checkBox_2"));

        horizontalLayout->addWidget(checkBox_2);

        checkBox = new QCheckBox(widget_6);
        checkBox->setObjectName(QStringLiteral("checkBox"));

        horizontalLayout->addWidget(checkBox);

        pushButton_3 = new QPushButton(widget_6);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        horizontalLayout->addWidget(pushButton_3);


        gridLayout->addLayout(horizontalLayout, 0, 2, 1, 1);

        treeWidget = new QTreeWidget(widget_6);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));
        treeWidget->setStyleSheet(QLatin1String("\n"
".QTreeWidget{\n"
"border: 1px solid rgb(218,218,218);\n"
"background-color: rgb(251, 252, 254);\n"
"border-radius: 0px;\n"
"}\n"
"\n"
"\n"
""));

        gridLayout->addWidget(treeWidget, 1, 0, 1, 3);


        verticalLayout_3->addWidget(widget_6);


        gridLayout_2->addWidget(widget_5, 0, 0, 1, 1);


        retranslateUi(wirelessrecv);

        QMetaObject::connectSlotsByName(wirelessrecv);
    } // setupUi

    void retranslateUi(QWidget *wirelessrecv)
    {
        wirelessrecv->setWindowTitle(QApplication::translate("wirelessrecv", "Form", Q_NULLPTR));
        label_8->setText(QApplication::translate("wirelessrecv", "Read", Q_NULLPTR));
        pushButton->setText(QApplication::translate("wirelessrecv", "\345\220\257\345\212\250", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("wirelessrecv", "\350\275\257\344\273\266\350\256\276\347\275\256", Q_NULLPTR));
        pushButton_6->setText(QApplication::translate("wirelessrecv", "\345\274\200\345\247\213\347\233\221\345\220\254", Q_NULLPTR));
        pushButton_5->setText(QApplication::translate("wirelessrecv", "\346\267\273\345\212\240\350\257\273\345\206\231\345\231\250", Q_NULLPTR));
        checkBox_2->setText(QApplication::translate("wirelessrecv", "\350\247\243\346\236\220\346\227\266\351\227\264", Q_NULLPTR));
        checkBox->setText(QApplication::translate("wirelessrecv", "\344\277\235\345\255\230\346\227\245\345\277\227", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("wirelessrecv", "Clear", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class wirelessrecv: public Ui_wirelessrecv {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIRELESSRECV_H
