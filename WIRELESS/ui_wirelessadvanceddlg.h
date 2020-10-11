/********************************************************************************
** Form generated from reading UI file 'wirelessadvanceddlg.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIRELESSADVANCEDDLG_H
#define UI_WIRELESSADVANCEDDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_WirelessAdvancedDlg
{
public:
    QGridLayout *gridLayout_2;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer;
    QGridLayout *gridLayout;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_4;
    QLabel *label_6;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_3;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QSpacerItem *horizontalSpacer_4;

    void setupUi(QDialog *WirelessAdvancedDlg)
    {
        if (WirelessAdvancedDlg->objectName().isEmpty())
            WirelessAdvancedDlg->setObjectName(QStringLiteral("WirelessAdvancedDlg"));
        WirelessAdvancedDlg->setWindowModality(Qt::WindowModal);
        WirelessAdvancedDlg->resize(262, 192);
        gridLayout_2 = new QGridLayout(WirelessAdvancedDlg);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        verticalSpacer = new QSpacerItem(20, 1, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 0, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(89, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 1, 0, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_7 = new QLabel(WirelessAdvancedDlg);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout->addWidget(label_7, 2, 0, 1, 1);

        label_8 = new QLabel(WirelessAdvancedDlg);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout->addWidget(label_8, 2, 2, 1, 1);

        label_4 = new QLabel(WirelessAdvancedDlg);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 1, 0, 1, 1);

        label_6 = new QLabel(WirelessAdvancedDlg);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout->addWidget(label_6, 1, 2, 1, 1);

        lineEdit_2 = new QLineEdit(WirelessAdvancedDlg);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));

        gridLayout->addWidget(lineEdit_2, 1, 1, 1, 1);

        lineEdit_3 = new QLineEdit(WirelessAdvancedDlg);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));

        gridLayout->addWidget(lineEdit_3, 2, 1, 1, 1);


        gridLayout_2->addLayout(gridLayout, 1, 1, 1, 2);

        horizontalSpacer_2 = new QSpacerItem(74, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 1, 3, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 2, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_2, 2, 2, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        pushButton = new QPushButton(WirelessAdvancedDlg);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(WirelessAdvancedDlg);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);


        gridLayout_2->addLayout(horizontalLayout, 3, 1, 1, 2);


        retranslateUi(WirelessAdvancedDlg);

        QMetaObject::connectSlotsByName(WirelessAdvancedDlg);
    } // setupUi

    void retranslateUi(QDialog *WirelessAdvancedDlg)
    {
        WirelessAdvancedDlg->setWindowTitle(QApplication::translate("WirelessAdvancedDlg", "Dialog", Q_NULLPTR));
        label_7->setText(QApplication::translate("WirelessAdvancedDlg", "\346\243\200\346\265\213\346\227\266\351\227\264", Q_NULLPTR));
        label_8->setText(QApplication::translate("WirelessAdvancedDlg", "\347\247\222", Q_NULLPTR));
        label_4->setText(QApplication::translate("WirelessAdvancedDlg", "\346\243\200\346\265\213\346\226\255\347\272\277\346\227\266\351\227\264:", Q_NULLPTR));
        label_6->setText(QApplication::translate("WirelessAdvancedDlg", "\347\247\222", Q_NULLPTR));
        pushButton->setText(QApplication::translate("WirelessAdvancedDlg", "\347\241\256\345\256\232", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("WirelessAdvancedDlg", "\345\217\226\346\266\210", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class WirelessAdvancedDlg: public Ui_WirelessAdvancedDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIRELESSADVANCEDDLG_H
