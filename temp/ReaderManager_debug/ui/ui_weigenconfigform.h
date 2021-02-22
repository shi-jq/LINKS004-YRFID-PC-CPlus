/********************************************************************************
** Form generated from reading UI file 'weigenconfigform.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WEIGENCONFIGFORM_H
#define UI_WEIGENCONFIGFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WeiGenConfigForm
{
public:
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_3;
    QGridLayout *gridLayout;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QLabel *label;
    QComboBox *comboBox;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *WeiGenConfigForm)
    {
        if (WeiGenConfigForm->objectName().isEmpty())
            WeiGenConfigForm->setObjectName(QStringLiteral("WeiGenConfigForm"));
        WeiGenConfigForm->resize(400, 101);
        gridLayout_2 = new QGridLayout(WeiGenConfigForm);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_2 = new QLabel(WeiGenConfigForm);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        lineEdit = new QLineEdit(WeiGenConfigForm);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        gridLayout->addWidget(lineEdit, 0, 1, 1, 1);

        label = new QLabel(WeiGenConfigForm);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 1, 0, 1, 1);

        comboBox = new QComboBox(WeiGenConfigForm);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        gridLayout->addWidget(comboBox, 1, 1, 1, 1);


        horizontalLayout_2->addLayout(gridLayout);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton = new QPushButton(WeiGenConfigForm);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(WeiGenConfigForm);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);


        gridLayout_2->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(WeiGenConfigForm);

        QMetaObject::connectSlotsByName(WeiGenConfigForm);
    } // setupUi

    void retranslateUi(QWidget *WeiGenConfigForm)
    {
        WeiGenConfigForm->setWindowTitle(QApplication::translate("WeiGenConfigForm", "Form", Q_NULLPTR));
        label_2->setText(QApplication::translate("WeiGenConfigForm", "\351\237\246\346\240\271\350\265\267\345\247\213\344\275\215", Q_NULLPTR));
        label->setText(QApplication::translate("WeiGenConfigForm", "\351\237\246\346\240\271\346\225\260\346\215\256\351\225\277\345\272\246", Q_NULLPTR));
        pushButton->setText(QApplication::translate("WeiGenConfigForm", "\346\237\245\350\257\242", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("WeiGenConfigForm", "\350\256\276\347\275\256", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class WeiGenConfigForm: public Ui_WeiGenConfigForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WEIGENCONFIGFORM_H
