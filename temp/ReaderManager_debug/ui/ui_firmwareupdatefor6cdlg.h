/********************************************************************************
** Form generated from reading UI file 'firmwareupdatefor6cdlg.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FIRMWAREUPDATEFOR6CDLG_H
#define UI_FIRMWAREUPDATEFOR6CDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FirmWareUpdateFor6CDlg
{
public:
    QGridLayout *gridLayout_2;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QProgressBar *progressBar;
    QLabel *label_2;
    QLabel *label;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QWidget *FirmWareUpdateFor6CDlg)
    {
        if (FirmWareUpdateFor6CDlg->objectName().isEmpty())
            FirmWareUpdateFor6CDlg->setObjectName(QStringLiteral("FirmWareUpdateFor6CDlg"));
        FirmWareUpdateFor6CDlg->resize(421, 292);
        gridLayout_2 = new QGridLayout(FirmWareUpdateFor6CDlg);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 0, 2, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        radioButton = new QRadioButton(FirmWareUpdateFor6CDlg);
        radioButton->setObjectName(QStringLiteral("radioButton"));

        horizontalLayout->addWidget(radioButton);

        radioButton_2 = new QRadioButton(FirmWareUpdateFor6CDlg);
        radioButton_2->setObjectName(QStringLiteral("radioButton_2"));

        horizontalLayout->addWidget(radioButton_2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        gridLayout->addLayout(horizontalLayout, 1, 1, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        lineEdit = new QLineEdit(FirmWareUpdateFor6CDlg);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        horizontalLayout_3->addWidget(lineEdit);

        pushButton = new QPushButton(FirmWareUpdateFor6CDlg);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout_3->addWidget(pushButton);


        gridLayout->addLayout(horizontalLayout_3, 2, 1, 1, 1);

        progressBar = new QProgressBar(FirmWareUpdateFor6CDlg);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setValue(0);
        progressBar->setTextVisible(false);

        gridLayout->addWidget(progressBar, 3, 0, 1, 2);

        label_2 = new QLabel(FirmWareUpdateFor6CDlg);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 2, 0, 1, 1);

        label = new QLabel(FirmWareUpdateFor6CDlg);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 1, 0, 1, 1);


        verticalLayout->addLayout(gridLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        pushButton_2 = new QPushButton(FirmWareUpdateFor6CDlg);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout_2->addWidget(pushButton_2);

        pushButton_3 = new QPushButton(FirmWareUpdateFor6CDlg);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        horizontalLayout_2->addWidget(pushButton_3);


        verticalLayout->addLayout(horizontalLayout_2);


        gridLayout_2->addLayout(verticalLayout, 1, 1, 2, 2);

        horizontalSpacer_4 = new QSpacerItem(42, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_4, 1, 3, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(54, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_3, 2, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_2, 3, 1, 1, 1);


        retranslateUi(FirmWareUpdateFor6CDlg);

        QMetaObject::connectSlotsByName(FirmWareUpdateFor6CDlg);
    } // setupUi

    void retranslateUi(QWidget *FirmWareUpdateFor6CDlg)
    {
        FirmWareUpdateFor6CDlg->setWindowTitle(QApplication::translate("FirmWareUpdateFor6CDlg", "Form", Q_NULLPTR));
        radioButton->setText(QApplication::translate("FirmWareUpdateFor6CDlg", "\345\233\272\344\273\266", Q_NULLPTR));
        radioButton_2->setText(QApplication::translate("FirmWareUpdateFor6CDlg", "NRF51822", Q_NULLPTR));
        pushButton->setText(QApplication::translate("FirmWareUpdateFor6CDlg", "\346\265\217\350\247\210", Q_NULLPTR));
        label_2->setText(QApplication::translate("FirmWareUpdateFor6CDlg", "\345\215\207\347\272\247\346\226\207\344\273\266", Q_NULLPTR));
        label->setText(QApplication::translate("FirmWareUpdateFor6CDlg", "\345\215\207\347\272\247\351\241\271", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("FirmWareUpdateFor6CDlg", "\345\274\200\345\247\213\345\215\207\347\272\247", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("FirmWareUpdateFor6CDlg", "\351\200\200\345\207\272", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class FirmWareUpdateFor6CDlg: public Ui_FirmWareUpdateFor6CDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FIRMWAREUPDATEFOR6CDLG_H
