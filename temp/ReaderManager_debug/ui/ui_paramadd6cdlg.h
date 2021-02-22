/********************************************************************************
** Form generated from reading UI file 'paramadd6cdlg.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PARAMADD6CDLG_H
#define UI_PARAMADD6CDLG_H

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

class Ui_ParamAdd6CDlg
{
public:
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_3;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QLabel *label_2;
    QLineEdit *lineEdit_2;
    QLabel *label_3;
    QLineEdit *lineEdit_3;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_2;
    QPushButton *pushButton;
    QPushButton *pushButton_5;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *ParamAdd6CDlg)
    {
        if (ParamAdd6CDlg->objectName().isEmpty())
            ParamAdd6CDlg->setObjectName(QStringLiteral("ParamAdd6CDlg"));
        ParamAdd6CDlg->resize(289, 246);
        gridLayout_2 = new QGridLayout(ParamAdd6CDlg);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(ParamAdd6CDlg);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        lineEdit = new QLineEdit(ParamAdd6CDlg);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        gridLayout->addWidget(lineEdit, 0, 1, 1, 1);

        label_2 = new QLabel(ParamAdd6CDlg);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        lineEdit_2 = new QLineEdit(ParamAdd6CDlg);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));

        gridLayout->addWidget(lineEdit_2, 1, 1, 1, 1);

        label_3 = new QLabel(ParamAdd6CDlg);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        lineEdit_3 = new QLineEdit(ParamAdd6CDlg);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));

        gridLayout->addWidget(lineEdit_3, 2, 1, 1, 1);


        horizontalLayout_2->addLayout(gridLayout);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);


        verticalLayout->addLayout(horizontalLayout_2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton_2 = new QPushButton(ParamAdd6CDlg);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);

        pushButton = new QPushButton(ParamAdd6CDlg);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout->addWidget(pushButton);

        pushButton_5 = new QPushButton(ParamAdd6CDlg);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));

        horizontalLayout->addWidget(pushButton_5);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);


        gridLayout_2->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(ParamAdd6CDlg);

        QMetaObject::connectSlotsByName(ParamAdd6CDlg);
    } // setupUi

    void retranslateUi(QWidget *ParamAdd6CDlg)
    {
        ParamAdd6CDlg->setWindowTitle(QApplication::translate("ParamAdd6CDlg", "Form", Q_NULLPTR));
        label->setText(QApplication::translate("ParamAdd6CDlg", "\350\265\267\345\247\213\345\234\260\345\235\200", Q_NULLPTR));
        label_2->setText(QApplication::translate("ParamAdd6CDlg", "\351\225\277\345\272\246", Q_NULLPTR));
        label_3->setText(QApplication::translate("ParamAdd6CDlg", "\346\225\260\346\215\256", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("ParamAdd6CDlg", "\350\257\273\345\217\226", Q_NULLPTR));
        pushButton->setText(QApplication::translate("ParamAdd6CDlg", "\345\206\231\345\205\245", Q_NULLPTR));
        pushButton_5->setText(QApplication::translate("ParamAdd6CDlg", "\346\201\242\345\244\215\345\207\272\345\216\202\350\256\276\347\275\256", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ParamAdd6CDlg: public Ui_ParamAdd6CDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PARAMADD6CDLG_H
