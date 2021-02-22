/********************************************************************************
** Form generated from reading UI file 'carrierconfigform.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CARRIERCONFIGFORM_H
#define UI_CARRIERCONFIGFORM_H

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

class Ui_CarrierConfigForm
{
public:
    QGridLayout *gridLayout_2;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QGridLayout *gridLayout;
    QLabel *label;
    QComboBox *comboBox;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QSpacerItem *horizontalSpacer_4;

    void setupUi(QWidget *CarrierConfigForm)
    {
        if (CarrierConfigForm->objectName().isEmpty())
            CarrierConfigForm->setObjectName(QStringLiteral("CarrierConfigForm"));
        CarrierConfigForm->resize(327, 179);
        gridLayout_2 = new QGridLayout(CarrierConfigForm);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        verticalSpacer_2 = new QSpacerItem(20, 44, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_2, 0, 1, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(CarrierConfigForm);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        comboBox = new QComboBox(CarrierConfigForm);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        gridLayout->addWidget(comboBox, 0, 1, 1, 1);


        horizontalLayout_2->addLayout(gridLayout);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);


        gridLayout_2->addLayout(horizontalLayout_2, 1, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 44, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 2, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton = new QPushButton(CarrierConfigForm);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(CarrierConfigForm);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);


        gridLayout_2->addLayout(horizontalLayout, 3, 0, 1, 2);


        retranslateUi(CarrierConfigForm);

        QMetaObject::connectSlotsByName(CarrierConfigForm);
    } // setupUi

    void retranslateUi(QWidget *CarrierConfigForm)
    {
        CarrierConfigForm->setWindowTitle(QApplication::translate("CarrierConfigForm", "Form", Q_NULLPTR));
        label->setText(QApplication::translate("CarrierConfigForm", "\350\275\275\346\263\242\345\217\202\346\225\260", Q_NULLPTR));
        pushButton->setText(QApplication::translate("CarrierConfigForm", "\346\237\245\350\257\242", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("CarrierConfigForm", "\351\205\215\347\275\256", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CarrierConfigForm: public Ui_CarrierConfigForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CARRIERCONFIGFORM_H
