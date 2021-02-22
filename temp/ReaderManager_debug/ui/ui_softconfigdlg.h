/********************************************************************************
** Form generated from reading UI file 'softconfigdlg.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SOFTCONFIGDLG_H
#define UI_SOFTCONFIGDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_SoftConfigDlg
{
public:
    QGridLayout *gridLayout_2;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer_2;
    QGridLayout *gridLayout;
    QLabel *label;
    QHBoxLayout *horizontalLayout_4;
    QLineEdit *lineEdit;
    QPushButton *pushButton_3;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout_3;
    QComboBox *comboBox;
    QSpacerItem *horizontalSpacer_8;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_9;
    QSpacerItem *horizontalSpacer_5;
    QHBoxLayout *horizontalLayout_8;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *label_4;
    QHBoxLayout *horizontalLayout_6;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QSpacerItem *horizontalSpacer_7;
    QSpacerItem *horizontalSpacer_9;

    void setupUi(QDialog *SoftConfigDlg)
    {
        if (SoftConfigDlg->objectName().isEmpty())
            SoftConfigDlg->setObjectName(QStringLiteral("SoftConfigDlg"));
        SoftConfigDlg->resize(412, 225);
        gridLayout_2 = new QGridLayout(SoftConfigDlg);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        verticalSpacer = new QSpacerItem(20, 78, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 0, 0, 1, 1);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        horizontalSpacer_2 = new QSpacerItem(79, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_2);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(SoftConfigDlg);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        lineEdit = new QLineEdit(SoftConfigDlg);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setMinimumSize(QSize(150, 0));

        horizontalLayout_4->addWidget(lineEdit);

        pushButton_3 = new QPushButton(SoftConfigDlg);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        horizontalLayout_4->addWidget(pushButton_3);


        gridLayout->addLayout(horizontalLayout_4, 1, 1, 1, 1);

        label_2 = new QLabel(SoftConfigDlg);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        comboBox = new QComboBox(SoftConfigDlg);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setMinimumSize(QSize(120, 0));

        horizontalLayout_3->addWidget(comboBox);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_8);


        gridLayout->addLayout(horizontalLayout_3, 0, 1, 1, 1);


        horizontalLayout_7->addLayout(gridLayout);

        horizontalSpacer_3 = new QSpacerItem(79, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_3);


        gridLayout_2->addLayout(horizontalLayout_7, 1, 0, 1, 2);

        verticalSpacer_2 = new QSpacerItem(20, 68, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_2, 2, 1, 1, 1);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_5);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label_4 = new QLabel(SoftConfigDlg);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout->addWidget(label_4);


        horizontalLayout_8->addLayout(horizontalLayout);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        pushButton = new QPushButton(SoftConfigDlg);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout_5->addWidget(pushButton);

        pushButton_2 = new QPushButton(SoftConfigDlg);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout_5->addWidget(pushButton_2);


        horizontalLayout_6->addLayout(horizontalLayout_5);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_7);


        horizontalLayout_8->addLayout(horizontalLayout_6);


        horizontalLayout_9->addLayout(horizontalLayout_8);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_9);


        gridLayout_2->addLayout(horizontalLayout_9, 3, 0, 1, 2);


        retranslateUi(SoftConfigDlg);

        QMetaObject::connectSlotsByName(SoftConfigDlg);
    } // setupUi

    void retranslateUi(QDialog *SoftConfigDlg)
    {
        SoftConfigDlg->setWindowTitle(QApplication::translate("SoftConfigDlg", "Dialog", Q_NULLPTR));
        label->setText(QApplication::translate("SoftConfigDlg", "\350\257\255\350\250\200\351\205\215\347\275\256", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("SoftConfigDlg", "\346\265\217\350\247\210", Q_NULLPTR));
        label_2->setText(QApplication::translate("SoftConfigDlg", "\346\227\245\345\277\227\350\256\260\345\275\225\346\226\207\344\273\266", Q_NULLPTR));
        label_4->setText(QApplication::translate("SoftConfigDlg", "\351\207\215\345\220\257\345\220\216\347\224\237\346\225\210!", Q_NULLPTR));
        pushButton->setText(QApplication::translate("SoftConfigDlg", "\350\256\276\347\275\256", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("SoftConfigDlg", "\345\217\226\346\266\210", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SoftConfigDlg: public Ui_SoftConfigDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SOFTCONFIGDLG_H
