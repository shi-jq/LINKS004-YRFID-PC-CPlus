/********************************************************************************
** Form generated from reading UI file 'flashconfigfor6cdlg.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FLASHCONFIGFOR6CDLG_H
#define UI_FLASHCONFIGFOR6CDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
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

class Ui_FlashConfigFor6CDlg
{
public:
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *lineEdit;
    QSpacerItem *horizontalSpacer_3;
    QCheckBox *checkBox;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *FlashConfigFor6CDlg)
    {
        if (FlashConfigFor6CDlg->objectName().isEmpty())
            FlashConfigFor6CDlg->setObjectName(QStringLiteral("FlashConfigFor6CDlg"));
        FlashConfigFor6CDlg->resize(251, 218);
        horizontalLayout_3 = new QHBoxLayout(FlashConfigFor6CDlg);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer = new QSpacerItem(21, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label = new QLabel(FlashConfigFor6CDlg);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_2->addWidget(label);

        lineEdit = new QLineEdit(FlashConfigFor6CDlg);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_2->addWidget(lineEdit);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);


        gridLayout->addLayout(horizontalLayout_2, 1, 0, 1, 1);

        checkBox = new QCheckBox(FlashConfigFor6CDlg);
        checkBox->setObjectName(QStringLiteral("checkBox"));

        gridLayout->addWidget(checkBox, 0, 0, 1, 1);


        verticalLayout->addLayout(gridLayout);

        verticalSpacer_2 = new QSpacerItem(20, 33, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer_4 = new QSpacerItem(0, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);

        pushButton = new QPushButton(FlashConfigFor6CDlg);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(FlashConfigFor6CDlg);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);

        horizontalSpacer_5 = new QSpacerItem(0, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_5);


        verticalLayout->addLayout(horizontalLayout);


        horizontalLayout_3->addLayout(verticalLayout);

        horizontalSpacer_2 = new QSpacerItem(22, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);


        retranslateUi(FlashConfigFor6CDlg);

        QMetaObject::connectSlotsByName(FlashConfigFor6CDlg);
    } // setupUi

    void retranslateUi(QWidget *FlashConfigFor6CDlg)
    {
        FlashConfigFor6CDlg->setWindowTitle(QApplication::translate("FlashConfigFor6CDlg", "Form", Q_NULLPTR));
        label->setText(QApplication::translate("FlashConfigFor6CDlg", "\346\240\207\347\255\276\346\200\273\346\225\260", Q_NULLPTR));
        checkBox->setText(QApplication::translate("FlashConfigFor6CDlg", "\345\220\257\347\224\250", Q_NULLPTR));
        pushButton->setText(QApplication::translate("FlashConfigFor6CDlg", "\346\237\245\350\257\242", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("FlashConfigFor6CDlg", "\346\270\205\351\231\244", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class FlashConfigFor6CDlg: public Ui_FlashConfigFor6CDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FLASHCONFIGFOR6CDLG_H
