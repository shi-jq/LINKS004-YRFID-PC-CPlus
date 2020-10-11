/********************************************************************************
** Form generated from reading UI file 'progressbardlg.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROGRESSBARDLG_H
#define UI_PROGRESSBARDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_ProgressBarDlg
{
public:
    QGridLayout *gridLayout;
    QProgressBar *progressBar;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *ProgressBarDlg)
    {
        if (ProgressBarDlg->objectName().isEmpty())
            ProgressBarDlg->setObjectName(QStringLiteral("ProgressBarDlg"));
        ProgressBarDlg->resize(658, 69);
        gridLayout = new QGridLayout(ProgressBarDlg);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        progressBar = new QProgressBar(ProgressBarDlg);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setValue(24);

        gridLayout->addWidget(progressBar, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton = new QPushButton(ProgressBarDlg);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout->addWidget(pushButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 1);


        retranslateUi(ProgressBarDlg);

        QMetaObject::connectSlotsByName(ProgressBarDlg);
    } // setupUi

    void retranslateUi(QDialog *ProgressBarDlg)
    {
        ProgressBarDlg->setWindowTitle(QApplication::translate("ProgressBarDlg", "Dialog", Q_NULLPTR));
        pushButton->setText(QApplication::translate("ProgressBarDlg", "\345\217\226\346\266\210", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ProgressBarDlg: public Ui_ProgressBarDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROGRESSBARDLG_H
