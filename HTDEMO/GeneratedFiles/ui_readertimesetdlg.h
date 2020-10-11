/********************************************************************************
** Form generated from reading UI file 'readertimesetdlg.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_READERTIMESETDLG_H
#define UI_READERTIMESETDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ReaderTimeSetDlg
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_2;
    QGridLayout *gridLayout;
    QLabel *label_2;
    QDateEdit *dateEdit;
    QTimeEdit *timeEdit;
    QLabel *label;
    QPushButton *pushButton_2;
    QPushButton *pushButton;
    QPushButton *pushButton_3;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *ReaderTimeSetDlg)
    {
        if (ReaderTimeSetDlg->objectName().isEmpty())
            ReaderTimeSetDlg->setObjectName(QStringLiteral("ReaderTimeSetDlg"));
        ReaderTimeSetDlg->resize(353, 88);
        verticalLayout_2 = new QVBoxLayout(ReaderTimeSetDlg);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(18, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalSpacer_2 = new QSpacerItem(20, 93, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_2 = new QLabel(ReaderTimeSetDlg);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        dateEdit = new QDateEdit(ReaderTimeSetDlg);
        dateEdit->setObjectName(QStringLiteral("dateEdit"));

        gridLayout->addWidget(dateEdit, 0, 1, 1, 1);

        timeEdit = new QTimeEdit(ReaderTimeSetDlg);
        timeEdit->setObjectName(QStringLiteral("timeEdit"));

        gridLayout->addWidget(timeEdit, 1, 1, 1, 1);

        label = new QLabel(ReaderTimeSetDlg);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        pushButton_2 = new QPushButton(ReaderTimeSetDlg);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        gridLayout->addWidget(pushButton_2, 1, 2, 1, 1);

        pushButton = new QPushButton(ReaderTimeSetDlg);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        gridLayout->addWidget(pushButton, 0, 2, 1, 1);

        pushButton_3 = new QPushButton(ReaderTimeSetDlg);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        gridLayout->addWidget(pushButton_3, 1, 3, 1, 1);


        verticalLayout->addLayout(gridLayout);

        verticalSpacer = new QSpacerItem(20, 92, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout_2->addLayout(verticalLayout);

        horizontalSpacer_2 = new QSpacerItem(19, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout_2);


        retranslateUi(ReaderTimeSetDlg);

        QMetaObject::connectSlotsByName(ReaderTimeSetDlg);
    } // setupUi

    void retranslateUi(QWidget *ReaderTimeSetDlg)
    {
        ReaderTimeSetDlg->setWindowTitle(QApplication::translate("ReaderTimeSetDlg", "Form", Q_NULLPTR));
        label_2->setText(QApplication::translate("ReaderTimeSetDlg", "\346\227\266\351\227\264", Q_NULLPTR));
        label->setText(QApplication::translate("ReaderTimeSetDlg", "\346\227\245\346\234\237", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("ReaderTimeSetDlg", "\350\256\276\347\275\256", Q_NULLPTR));
        pushButton->setText(QApplication::translate("ReaderTimeSetDlg", "\346\237\245\350\257\242", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("ReaderTimeSetDlg", "\350\256\276\347\275\256\345\275\223\345\211\215\347\263\273\347\273\237\346\227\266\351\227\264", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ReaderTimeSetDlg: public Ui_ReaderTimeSetDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_READERTIMESETDLG_H
