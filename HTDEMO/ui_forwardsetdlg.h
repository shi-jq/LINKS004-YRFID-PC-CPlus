/********************************************************************************
** Form generated from reading UI file 'forwardsetdlg.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORWARDSETDLG_H
#define UI_FORWARDSETDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ForwardSetDlg
{
public:
    QGridLayout *gridLayout_2;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_3;
    QGridLayout *gridLayout;
    QLabel *label;
    QComboBox *comboBox;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *ForwardSetDlg)
    {
        if (ForwardSetDlg->objectName().isEmpty())
            ForwardSetDlg->setObjectName(QString::fromUtf8("ForwardSetDlg"));
        ForwardSetDlg->resize(320, 217);
        gridLayout_2 = new QGridLayout(ForwardSetDlg);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        verticalSpacer_2 = new QSpacerItem(20, 33, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_2, 0, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(ForwardSetDlg);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 2);

        comboBox = new QComboBox(ForwardSetDlg);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        gridLayout->addWidget(comboBox, 0, 2, 1, 1);

        label_2 = new QLabel(ForwardSetDlg);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 2);

        lineEdit = new QLineEdit(ForwardSetDlg);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        gridLayout->addWidget(lineEdit, 1, 2, 1, 1);

        lineEdit_2 = new QLineEdit(ForwardSetDlg);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));

        gridLayout->addWidget(lineEdit_2, 2, 2, 1, 1);

        label_3 = new QLabel(ForwardSetDlg);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 2);


        horizontalLayout_2->addLayout(gridLayout);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);


        gridLayout_2->addLayout(horizontalLayout_2, 1, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 33, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 2, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton = new QPushButton(ForwardSetDlg);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(ForwardSetDlg);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        gridLayout_2->addLayout(horizontalLayout, 3, 0, 1, 1);


        retranslateUi(ForwardSetDlg);

        QMetaObject::connectSlotsByName(ForwardSetDlg);
    } // setupUi

    void retranslateUi(QWidget *ForwardSetDlg)
    {
        ForwardSetDlg->setWindowTitle(QCoreApplication::translate("ForwardSetDlg", "Form", nullptr));
        label->setText(QCoreApplication::translate("ForwardSetDlg", "\350\275\254\345\217\221\351\200\232\351\201\223", nullptr));
        label_2->setText(QCoreApplication::translate("ForwardSetDlg", "\350\275\254\345\217\221\345\234\260\345\235\200", nullptr));
        label_3->setText(QCoreApplication::translate("ForwardSetDlg", "\347\253\257\345\217\243", nullptr));
        pushButton->setText(QCoreApplication::translate("ForwardSetDlg", "\346\237\245\350\257\242", nullptr));
        pushButton_2->setText(QCoreApplication::translate("ForwardSetDlg", "\350\256\276\347\275\256", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ForwardSetDlg: public Ui_ForwardSetDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORWARDSETDLG_H
