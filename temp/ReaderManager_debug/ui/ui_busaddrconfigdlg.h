/********************************************************************************
** Form generated from reading UI file 'busaddrconfigdlg.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BUSADDRCONFIGDLG_H
#define UI_BUSADDRCONFIGDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BusAddrConfigDlg
{
public:
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QWidget *BusAddrConfigDlg)
    {
        if (BusAddrConfigDlg->objectName().isEmpty())
            BusAddrConfigDlg->setObjectName(QStringLiteral("BusAddrConfigDlg"));
        BusAddrConfigDlg->resize(399, 146);
        horizontalLayout_3 = new QHBoxLayout(BusAddrConfigDlg);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer_2 = new QSpacerItem(56, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalSpacer = new QSpacerItem(20, 49, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(BusAddrConfigDlg);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        lineEdit = new QLineEdit(BusAddrConfigDlg);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        horizontalLayout->addWidget(lineEdit);

        pushButton = new QPushButton(BusAddrConfigDlg);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(BusAddrConfigDlg);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer_2 = new QSpacerItem(20, 48, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));

        verticalLayout->addLayout(horizontalLayout_2);


        horizontalLayout_3->addLayout(verticalLayout);

        horizontalSpacer_3 = new QSpacerItem(55, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);


        retranslateUi(BusAddrConfigDlg);

        QMetaObject::connectSlotsByName(BusAddrConfigDlg);
    } // setupUi

    void retranslateUi(QWidget *BusAddrConfigDlg)
    {
        BusAddrConfigDlg->setWindowTitle(QApplication::translate("BusAddrConfigDlg", "Form", Q_NULLPTR));
        label->setText(QApplication::translate("BusAddrConfigDlg", "\346\200\273\347\272\277\345\234\260\345\235\200", Q_NULLPTR));
        lineEdit->setInputMask(QApplication::translate("BusAddrConfigDlg", "HH; ", Q_NULLPTR));
        lineEdit->setText(QString());
        pushButton->setText(QApplication::translate("BusAddrConfigDlg", "\346\237\245\350\257\242", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("BusAddrConfigDlg", "\351\205\215\347\275\256", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class BusAddrConfigDlg: public Ui_BusAddrConfigDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BUSADDRCONFIGDLG_H
