/********************************************************************************
** Form generated from reading UI file 'wirelesstcpserverconfigdlg.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIRELESSTCPSERVERCONFIGDLG_H
#define UI_WIRELESSTCPSERVERCONFIGDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_WirelessTcpServerConfigDlg
{
public:
    QGridLayout *gridLayout_2;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer;
    QGridLayout *gridLayout;
    QLabel *label;
    QComboBox *comboBox_2;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QSpacerItem *horizontalSpacer_4;

    void setupUi(QDialog *WirelessTcpServerConfigDlg)
    {
        if (WirelessTcpServerConfigDlg->objectName().isEmpty())
            WirelessTcpServerConfigDlg->setObjectName(QStringLiteral("WirelessTcpServerConfigDlg"));
        WirelessTcpServerConfigDlg->resize(287, 168);
        gridLayout_2 = new QGridLayout(WirelessTcpServerConfigDlg);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        verticalSpacer = new QSpacerItem(20, 27, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 0, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(45, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 1, 0, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(WirelessTcpServerConfigDlg);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        comboBox_2 = new QComboBox(WirelessTcpServerConfigDlg);
        comboBox_2->setObjectName(QStringLiteral("comboBox_2"));

        gridLayout->addWidget(comboBox_2, 0, 1, 1, 1);

        label_2 = new QLabel(WirelessTcpServerConfigDlg);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        lineEdit = new QLineEdit(WirelessTcpServerConfigDlg);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        gridLayout->addWidget(lineEdit, 1, 1, 1, 1);


        gridLayout_2->addLayout(gridLayout, 1, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(44, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 1, 2, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 26, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_2, 2, 1, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        pushButton = new QPushButton(WirelessTcpServerConfigDlg);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(WirelessTcpServerConfigDlg);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);


        gridLayout_2->addLayout(horizontalLayout, 3, 0, 1, 3);


        retranslateUi(WirelessTcpServerConfigDlg);

        QMetaObject::connectSlotsByName(WirelessTcpServerConfigDlg);
    } // setupUi

    void retranslateUi(QDialog *WirelessTcpServerConfigDlg)
    {
        WirelessTcpServerConfigDlg->setWindowTitle(QApplication::translate("WirelessTcpServerConfigDlg", "Dialog", Q_NULLPTR));
        label->setText(QApplication::translate("WirelessTcpServerConfigDlg", "\346\234\215\345\212\241\345\231\250\345\234\260\345\235\200", Q_NULLPTR));
        label_2->setText(QApplication::translate("WirelessTcpServerConfigDlg", "\347\233\221\345\220\254\347\253\257\345\217\243", Q_NULLPTR));
        pushButton->setText(QApplication::translate("WirelessTcpServerConfigDlg", "\347\241\256\345\256\232", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("WirelessTcpServerConfigDlg", "\345\217\226\346\266\210", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class WirelessTcpServerConfigDlg: public Ui_WirelessTcpServerConfigDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIRELESSTCPSERVERCONFIGDLG_H
