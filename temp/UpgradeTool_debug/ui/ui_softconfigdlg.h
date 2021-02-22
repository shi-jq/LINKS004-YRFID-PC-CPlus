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
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_2;
    QGridLayout *gridLayout;
    QLabel *label;
    QHBoxLayout *horizontalLayout_3;
    QComboBox *comboBox;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *lineEdit;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *lineEdit_2;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QSpacerItem *horizontalSpacer_5;

    void setupUi(QDialog *SoftConfigDlg)
    {
        if (SoftConfigDlg->objectName().isEmpty())
            SoftConfigDlg->setObjectName(QStringLiteral("SoftConfigDlg"));
        SoftConfigDlg->resize(392, 257);
        gridLayout_2 = new QGridLayout(SoftConfigDlg);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        verticalSpacer = new QSpacerItem(20, 78, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 0, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalSpacer_2 = new QSpacerItem(79, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(SoftConfigDlg);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        comboBox = new QComboBox(SoftConfigDlg);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setMinimumSize(QSize(120, 0));

        horizontalLayout_3->addWidget(comboBox);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);


        gridLayout->addLayout(horizontalLayout_3, 0, 1, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        lineEdit = new QLineEdit(SoftConfigDlg);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        horizontalLayout_2->addWidget(lineEdit);


        gridLayout->addLayout(horizontalLayout_2, 1, 1, 1, 1);

        label_2 = new QLabel(SoftConfigDlg);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        label_3 = new QLabel(SoftConfigDlg);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        lineEdit_2 = new QLineEdit(SoftConfigDlg);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));

        gridLayout->addWidget(lineEdit_2, 2, 1, 1, 1);


        horizontalLayout_4->addLayout(gridLayout);

        horizontalSpacer_3 = new QSpacerItem(79, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);


        gridLayout_2->addLayout(horizontalLayout_4, 1, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 68, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_2, 2, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton = new QPushButton(SoftConfigDlg);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(SoftConfigDlg);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_5);


        gridLayout_2->addLayout(horizontalLayout, 3, 0, 1, 1);


        retranslateUi(SoftConfigDlg);

        QMetaObject::connectSlotsByName(SoftConfigDlg);
    } // setupUi

    void retranslateUi(QDialog *SoftConfigDlg)
    {
        SoftConfigDlg->setWindowTitle(QApplication::translate("SoftConfigDlg", "Dialog", Q_NULLPTR));
        label->setText(QApplication::translate("SoftConfigDlg", "\350\257\255\350\250\200\351\205\215\347\275\256", Q_NULLPTR));
        lineEdit->setText(QApplication::translate("SoftConfigDlg", "com.handheld.yhfr", Q_NULLPTR));
        label_2->setText(QApplication::translate("SoftConfigDlg", "Package", Q_NULLPTR));
        label_3->setText(QApplication::translate("SoftConfigDlg", "Activity", Q_NULLPTR));
        lineEdit_2->setText(QApplication::translate("SoftConfigDlg", "com.rfid_demo.main.MainActivity", Q_NULLPTR));
        pushButton->setText(QApplication::translate("SoftConfigDlg", "\350\256\276\347\275\256", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("SoftConfigDlg", "\345\217\226\346\266\210", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SoftConfigDlg: public Ui_SoftConfigDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SOFTCONFIGDLG_H
