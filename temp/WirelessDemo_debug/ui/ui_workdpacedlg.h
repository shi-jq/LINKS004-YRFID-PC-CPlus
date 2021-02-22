/********************************************************************************
** Form generated from reading UI file 'workdpacedlg.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WORKDPACEDLG_H
#define UI_WORKDPACEDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_workDpaceDlg
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_2;
    QPushButton *LeftPushBtn;
    QSpacerItem *verticalSpacer;
    QTabWidget *tabWidget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *DownPushBtn;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *workDpaceDlg)
    {
        if (workDpaceDlg->objectName().isEmpty())
            workDpaceDlg->setObjectName(QStringLiteral("workDpaceDlg"));
        workDpaceDlg->resize(400, 300);
        gridLayout = new QGridLayout(workDpaceDlg);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 9, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalSpacer_2 = new QSpacerItem(12, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        LeftPushBtn = new QPushButton(workDpaceDlg);
        LeftPushBtn->setObjectName(QStringLiteral("LeftPushBtn"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(LeftPushBtn->sizePolicy().hasHeightForWidth());
        LeftPushBtn->setSizePolicy(sizePolicy);
        LeftPushBtn->setMinimumSize(QSize(12, 84));
        LeftPushBtn->setMaximumSize(QSize(12, 84));
        LeftPushBtn->setFocusPolicy(Qt::ClickFocus);
        LeftPushBtn->setStyleSheet(QStringLiteral(""));
        LeftPushBtn->setAutoExclusive(false);
        LeftPushBtn->setAutoDefault(false);

        verticalLayout->addWidget(LeftPushBtn);

        verticalSpacer = new QSpacerItem(12, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

        tabWidget = new QTabWidget(workDpaceDlg);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));

        gridLayout->addWidget(tabWidget, 0, 1, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 12, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        DownPushBtn = new QPushButton(workDpaceDlg);
        DownPushBtn->setObjectName(QStringLiteral("DownPushBtn"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(DownPushBtn->sizePolicy().hasHeightForWidth());
        DownPushBtn->setSizePolicy(sizePolicy1);
        DownPushBtn->setMinimumSize(QSize(84, 12));
        DownPushBtn->setMaximumSize(QSize(84, 12));
        DownPushBtn->setStyleSheet(QStringLiteral(""));

        horizontalLayout->addWidget(DownPushBtn);

        horizontalSpacer_2 = new QSpacerItem(40, 12, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        gridLayout->addLayout(horizontalLayout, 1, 1, 1, 1);


        retranslateUi(workDpaceDlg);

        tabWidget->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(workDpaceDlg);
    } // setupUi

    void retranslateUi(QWidget *workDpaceDlg)
    {
        workDpaceDlg->setWindowTitle(QApplication::translate("workDpaceDlg", "Form", Q_NULLPTR));
        LeftPushBtn->setText(QString());
        DownPushBtn->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class workDpaceDlg: public Ui_workDpaceDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WORKDPACEDLG_H
