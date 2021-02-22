/********************************************************************************
** Form generated from reading UI file 'qvaluedlg.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QVALUEDLG_H
#define UI_QVALUEDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QValueDlg
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_3;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_6;
    QLabel *label;
    QSpinBox *spinBox;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QSpacerItem *horizontalSpacer_4;

    void setupUi(QWidget *QValueDlg)
    {
        if (QValueDlg->objectName().isEmpty())
            QValueDlg->setObjectName(QStringLiteral("QValueDlg"));
        QValueDlg->resize(469, 129);
        verticalLayout_2 = new QVBoxLayout(QValueDlg);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer_3 = new QSpacerItem(8, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_6);

        label = new QLabel(QValueDlg);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        spinBox = new QSpinBox(QValueDlg);
        spinBox->setObjectName(QStringLiteral("spinBox"));

        horizontalLayout->addWidget(spinBox);


        verticalLayout->addLayout(horizontalLayout);


        horizontalLayout_3->addLayout(verticalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        pushButton = new QPushButton(QValueDlg);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout_2->addWidget(pushButton);

        pushButton_2 = new QPushButton(QValueDlg);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout_2->addWidget(pushButton_2);


        horizontalLayout_3->addLayout(horizontalLayout_2);

        horizontalSpacer_4 = new QSpacerItem(8, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);


        verticalLayout_2->addLayout(horizontalLayout_3);


        retranslateUi(QValueDlg);

        QMetaObject::connectSlotsByName(QValueDlg);
    } // setupUi

    void retranslateUi(QWidget *QValueDlg)
    {
        QValueDlg->setWindowTitle(QApplication::translate("QValueDlg", "Form", Q_NULLPTR));
        label->setText(QApplication::translate("QValueDlg", "Q\345\200\274", Q_NULLPTR));
        pushButton->setText(QApplication::translate("QValueDlg", "\346\237\245\350\257\242", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("QValueDlg", "\350\256\276\347\275\256", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class QValueDlg: public Ui_QValueDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QVALUEDLG_H
