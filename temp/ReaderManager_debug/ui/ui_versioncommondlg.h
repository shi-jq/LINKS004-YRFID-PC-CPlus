/********************************************************************************
** Form generated from reading UI file 'versioncommondlg.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VERSIONCOMMONDLG_H
#define UI_VERSIONCOMMONDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_VersionCommonDlg
{
public:
    QGridLayout *gridLayout_2;
    QSpacerItem *verticalSpacer_4;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_5;
    QGridLayout *gridLayout;
    QLabel *label_2;
    QLabel *label;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_4;
    QLabel *label_5;
    QSpacerItem *horizontalSpacer_6;
    QSpacerItem *verticalSpacer_3;

    void setupUi(QDialog *VersionCommonDlg)
    {
        if (VersionCommonDlg->objectName().isEmpty())
            VersionCommonDlg->setObjectName(QStringLiteral("VersionCommonDlg"));
        VersionCommonDlg->resize(366, 211);
        gridLayout_2 = new QGridLayout(VersionCommonDlg);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        verticalSpacer_4 = new QSpacerItem(20, 63, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_4, 0, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_5);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_2 = new QLabel(VersionCommonDlg);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        label = new QLabel(VersionCommonDlg);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_8 = new QLabel(VersionCommonDlg);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout->addWidget(label_8, 0, 1, 1, 2);

        label_9 = new QLabel(VersionCommonDlg);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout->addWidget(label_9, 1, 1, 1, 2);

        label_4 = new QLabel(VersionCommonDlg);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 2, 0, 1, 1);

        label_5 = new QLabel(VersionCommonDlg);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 2, 1, 1, 2);


        horizontalLayout_3->addLayout(gridLayout);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_6);


        gridLayout_2->addLayout(horizontalLayout_3, 1, 0, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 62, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_3, 3, 0, 1, 1);


        retranslateUi(VersionCommonDlg);

        QMetaObject::connectSlotsByName(VersionCommonDlg);
    } // setupUi

    void retranslateUi(QDialog *VersionCommonDlg)
    {
        VersionCommonDlg->setWindowTitle(QApplication::translate("VersionCommonDlg", "Dialog", Q_NULLPTR));
        label_2->setText(QApplication::translate("VersionCommonDlg", "API\347\211\210\346\234\254:", Q_NULLPTR));
        label->setText(QApplication::translate("VersionCommonDlg", "\350\275\257\344\273\266\347\211\210\346\234\254:", Q_NULLPTR));
        label_8->setText(QApplication::translate("VersionCommonDlg", "-", Q_NULLPTR));
        label_9->setText(QApplication::translate("VersionCommonDlg", "-", Q_NULLPTR));
        label_4->setText(QApplication::translate("VersionCommonDlg", "\347\250\213\345\272\217\347\274\226\350\257\221\346\227\266\351\227\264", Q_NULLPTR));
        label_5->setText(QApplication::translate("VersionCommonDlg", "-", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class VersionCommonDlg: public Ui_VersionCommonDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VERSIONCOMMONDLG_H
