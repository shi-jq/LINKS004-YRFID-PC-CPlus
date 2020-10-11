/********************************************************************************
** Form generated from reading UI file 'filtratetagfor6cdlg.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILTRATETAGFOR6CDLG_H
#define UI_FILTRATETAGFOR6CDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FiltrateTagFor6CDlg
{
public:
    QGridLayout *gridLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QGridLayout *gridLayout;
    QSpinBox *spinBox;
    QLabel *label_2;
    QCheckBox *checkBox;
    QLabel *label;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QWidget *FiltrateTagFor6CDlg)
    {
        if (FiltrateTagFor6CDlg->objectName().isEmpty())
            FiltrateTagFor6CDlg->setObjectName(QStringLiteral("FiltrateTagFor6CDlg"));
        FiltrateTagFor6CDlg->resize(353, 212);
        gridLayout_2 = new QGridLayout(FiltrateTagFor6CDlg);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        horizontalSpacer_2 = new QSpacerItem(47, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 0, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalSpacer = new QSpacerItem(17, 28, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        spinBox = new QSpinBox(FiltrateTagFor6CDlg);
        spinBox->setObjectName(QStringLiteral("spinBox"));

        gridLayout->addWidget(spinBox, 1, 1, 1, 1);

        label_2 = new QLabel(FiltrateTagFor6CDlg);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 2, 1, 1);

        checkBox = new QCheckBox(FiltrateTagFor6CDlg);
        checkBox->setObjectName(QStringLiteral("checkBox"));

        gridLayout->addWidget(checkBox, 0, 0, 1, 1);

        label = new QLabel(FiltrateTagFor6CDlg);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 1, 0, 1, 1);


        verticalLayout->addLayout(gridLayout);

        verticalSpacer_2 = new QSpacerItem(20, 38, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton = new QPushButton(FiltrateTagFor6CDlg);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(FiltrateTagFor6CDlg);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);


        verticalLayout->addLayout(horizontalLayout);


        gridLayout_2->addLayout(verticalLayout, 0, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(46, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_3, 0, 2, 1, 1);


        retranslateUi(FiltrateTagFor6CDlg);

        QMetaObject::connectSlotsByName(FiltrateTagFor6CDlg);
    } // setupUi

    void retranslateUi(QWidget *FiltrateTagFor6CDlg)
    {
        FiltrateTagFor6CDlg->setWindowTitle(QApplication::translate("FiltrateTagFor6CDlg", "Form", Q_NULLPTR));
        label_2->setText(QApplication::translate("FiltrateTagFor6CDlg", "X*100ms", Q_NULLPTR));
        checkBox->setText(QApplication::translate("FiltrateTagFor6CDlg", "\345\220\257\347\224\250", Q_NULLPTR));
        label->setText(QApplication::translate("FiltrateTagFor6CDlg", "\346\240\207\347\255\276\350\277\207\346\273\244\346\227\266\351\227\264", Q_NULLPTR));
        pushButton->setText(QApplication::translate("FiltrateTagFor6CDlg", "\346\237\245\350\257\242", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("FiltrateTagFor6CDlg", "\350\256\276\347\275\256", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class FiltrateTagFor6CDlg: public Ui_FiltrateTagFor6CDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILTRATETAGFOR6CDLG_H
