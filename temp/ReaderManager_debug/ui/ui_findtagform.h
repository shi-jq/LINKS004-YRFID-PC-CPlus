/********************************************************************************
** Form generated from reading UI file 'findtagform.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FINDTAGFORM_H
#define UI_FINDTAGFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FindTagForm
{
public:
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_4;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *checkBox;
    QCheckBox *checkBox_2;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *FindTagForm)
    {
        if (FindTagForm->objectName().isEmpty())
            FindTagForm->setObjectName(QStringLiteral("FindTagForm"));
        FindTagForm->resize(346, 165);
        verticalLayout_2 = new QVBoxLayout(FindTagForm);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalSpacer_2 = new QSpacerItem(20, 24, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(FindTagForm);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        lineEdit = new QLineEdit(FindTagForm);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        horizontalLayout->addWidget(lineEdit);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        checkBox = new QCheckBox(FindTagForm);
        checkBox->setObjectName(QStringLiteral("checkBox"));

        horizontalLayout_2->addWidget(checkBox);

        checkBox_2 = new QCheckBox(FindTagForm);
        checkBox_2->setObjectName(QStringLiteral("checkBox_2"));

        horizontalLayout_2->addWidget(checkBox_2);


        verticalLayout->addLayout(horizontalLayout_2);


        horizontalLayout_4->addLayout(verticalLayout);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);


        verticalLayout_2->addLayout(horizontalLayout_4);

        verticalSpacer = new QSpacerItem(20, 24, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        pushButton = new QPushButton(FindTagForm);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout_3->addWidget(pushButton);

        pushButton_2 = new QPushButton(FindTagForm);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout_3->addWidget(pushButton_2);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout_3);


        retranslateUi(FindTagForm);

        QMetaObject::connectSlotsByName(FindTagForm);
    } // setupUi

    void retranslateUi(QWidget *FindTagForm)
    {
        FindTagForm->setWindowTitle(QApplication::translate("FindTagForm", "Form", Q_NULLPTR));
        label->setText(QApplication::translate("FindTagForm", "\346\240\207\347\255\276ID", Q_NULLPTR));
        checkBox->setText(QApplication::translate("FindTagForm", "\346\240\207\347\255\276LED", Q_NULLPTR));
        checkBox_2->setText(QApplication::translate("FindTagForm", "\346\240\207\347\255\276\350\234\202\351\270\243\345\231\250", Q_NULLPTR));
        pushButton->setText(QApplication::translate("FindTagForm", "\346\237\245\346\211\276", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("FindTagForm", "\345\201\234\346\255\242", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class FindTagForm: public Ui_FindTagForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FINDTAGFORM_H
