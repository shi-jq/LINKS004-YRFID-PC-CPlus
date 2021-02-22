/********************************************************************************
** Form generated from reading UI file 'gprsconfigdlg.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GPRSCONFIGDLG_H
#define UI_GPRSCONFIGDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
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

class Ui_GprsConfigDlg
{
public:
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_3;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QLabel *label_2;
    QLineEdit *lineEdit_2;
    QLabel *label_3;
    QLineEdit *lineEdit_3;
    QLabel *label_4;
    QLineEdit *lineEdit_4;
    QLabel *label_5;
    QLineEdit *lineEdit_5;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *GprsConfigDlg)
    {
        if (GprsConfigDlg->objectName().isEmpty())
            GprsConfigDlg->setObjectName(QStringLiteral("GprsConfigDlg"));
        GprsConfigDlg->resize(437, 225);
        horizontalLayout_2 = new QHBoxLayout(GprsConfigDlg);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer_3 = new QSpacerItem(15, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalSpacer = new QSpacerItem(20, 31, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(GprsConfigDlg);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        lineEdit = new QLineEdit(GprsConfigDlg);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        gridLayout->addWidget(lineEdit, 0, 1, 1, 1);

        label_2 = new QLabel(GprsConfigDlg);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 0, 2, 1, 1);

        lineEdit_2 = new QLineEdit(GprsConfigDlg);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setMinimumSize(QSize(0, 0));

        gridLayout->addWidget(lineEdit_2, 0, 3, 1, 1);

        label_3 = new QLabel(GprsConfigDlg);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        lineEdit_3 = new QLineEdit(GprsConfigDlg);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));

        gridLayout->addWidget(lineEdit_3, 1, 1, 1, 1);

        label_4 = new QLabel(GprsConfigDlg);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 2, 0, 1, 1);

        lineEdit_4 = new QLineEdit(GprsConfigDlg);
        lineEdit_4->setObjectName(QStringLiteral("lineEdit_4"));

        gridLayout->addWidget(lineEdit_4, 2, 1, 1, 1);

        label_5 = new QLabel(GprsConfigDlg);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 2, 2, 1, 1);

        lineEdit_5 = new QLineEdit(GprsConfigDlg);
        lineEdit_5->setObjectName(QStringLiteral("lineEdit_5"));

        gridLayout->addWidget(lineEdit_5, 2, 3, 1, 1);


        verticalLayout->addLayout(gridLayout);

        verticalSpacer_2 = new QSpacerItem(20, 30, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton = new QPushButton(GprsConfigDlg);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(GprsConfigDlg);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);


        verticalLayout->addLayout(horizontalLayout);


        horizontalLayout_2->addLayout(verticalLayout);

        horizontalSpacer_2 = new QSpacerItem(15, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        retranslateUi(GprsConfigDlg);

        QMetaObject::connectSlotsByName(GprsConfigDlg);
    } // setupUi

    void retranslateUi(QWidget *GprsConfigDlg)
    {
        GprsConfigDlg->setWindowTitle(QApplication::translate("GprsConfigDlg", "Form", Q_NULLPTR));
        label->setText(QApplication::translate("GprsConfigDlg", "IP\345\234\260\345\235\200", Q_NULLPTR));
        label_2->setText(QApplication::translate("GprsConfigDlg", "\347\233\221\345\220\254\347\253\257\345\217\243", Q_NULLPTR));
        label_3->setText(QApplication::translate("GprsConfigDlg", "APN", Q_NULLPTR));
        label_4->setText(QApplication::translate("GprsConfigDlg", "\350\264\246\346\210\267\345\220\215", Q_NULLPTR));
        label_5->setText(QApplication::translate("GprsConfigDlg", "\345\257\206\347\240\201", Q_NULLPTR));
        pushButton->setText(QApplication::translate("GprsConfigDlg", "\346\237\245\350\257\242", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("GprsConfigDlg", "\350\256\276\347\275\256", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class GprsConfigDlg: public Ui_GprsConfigDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GPRSCONFIGDLG_H
