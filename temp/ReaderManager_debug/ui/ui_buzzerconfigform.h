/********************************************************************************
** Form generated from reading UI file 'buzzerconfigform.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BUZZERCONFIGFORM_H
#define UI_BUZZERCONFIGFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BuzzerConfigForm
{
public:
    QGridLayout *gridLayout_2;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_3;
    QGridLayout *gridLayout;
    QLabel *label_3;
    QComboBox *comboBox_1;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *BuzzerConfigForm)
    {
        if (BuzzerConfigForm->objectName().isEmpty())
            BuzzerConfigForm->setObjectName(QStringLiteral("BuzzerConfigForm"));
        BuzzerConfigForm->resize(400, 300);
        gridLayout_2 = new QGridLayout(BuzzerConfigForm);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        verticalSpacer = new QSpacerItem(20, 105, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 0, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_3 = new QLabel(BuzzerConfigForm);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 0, 0, 1, 1);

        comboBox_1 = new QComboBox(BuzzerConfigForm);
        comboBox_1->setObjectName(QStringLiteral("comboBox_1"));

        gridLayout->addWidget(comboBox_1, 0, 1, 1, 1);


        horizontalLayout_2->addLayout(gridLayout);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);


        gridLayout_2->addLayout(horizontalLayout_2, 1, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 104, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_2, 2, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton = new QPushButton(BuzzerConfigForm);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(BuzzerConfigForm);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        gridLayout_2->addLayout(horizontalLayout, 3, 0, 1, 1);


        retranslateUi(BuzzerConfigForm);

        QMetaObject::connectSlotsByName(BuzzerConfigForm);
    } // setupUi

    void retranslateUi(QWidget *BuzzerConfigForm)
    {
        BuzzerConfigForm->setWindowTitle(QApplication::translate("BuzzerConfigForm", "Form", Q_NULLPTR));
        label_3->setText(QApplication::translate("BuzzerConfigForm", "\350\257\273\345\215\241\345\243\260\351\237\263", Q_NULLPTR));
        pushButton->setText(QApplication::translate("BuzzerConfigForm", "\346\237\245\350\257\242", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("BuzzerConfigForm", "\350\256\276\347\275\256", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class BuzzerConfigForm: public Ui_BuzzerConfigForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BUZZERCONFIGFORM_H
