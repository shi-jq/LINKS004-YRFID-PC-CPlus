/********************************************************************************
** Form generated from reading UI file 'rebootdeviceform.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REBOOTDEVICEFORM_H
#define UI_REBOOTDEVICEFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RebootDeviceForm
{
public:
    QGridLayout *gridLayout;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *RebootDeviceForm)
    {
        if (RebootDeviceForm->objectName().isEmpty())
            RebootDeviceForm->setObjectName(QStringLiteral("RebootDeviceForm"));
        RebootDeviceForm->resize(269, 161);
        gridLayout = new QGridLayout(RebootDeviceForm);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalSpacer_2 = new QSpacerItem(20, 51, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 0, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(79, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 0, 1, 1);

        pushButton = new QPushButton(RebootDeviceForm);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        gridLayout->addWidget(pushButton, 1, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(79, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 2, 1, 1);

        verticalSpacer = new QSpacerItem(20, 51, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 2, 1, 1, 1);


        retranslateUi(RebootDeviceForm);

        QMetaObject::connectSlotsByName(RebootDeviceForm);
    } // setupUi

    void retranslateUi(QWidget *RebootDeviceForm)
    {
        RebootDeviceForm->setWindowTitle(QApplication::translate("RebootDeviceForm", "Form", Q_NULLPTR));
        pushButton->setText(QApplication::translate("RebootDeviceForm", "\351\207\215\345\220\257\350\257\273\345\206\231\345\231\250", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class RebootDeviceForm: public Ui_RebootDeviceForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REBOOTDEVICEFORM_H
