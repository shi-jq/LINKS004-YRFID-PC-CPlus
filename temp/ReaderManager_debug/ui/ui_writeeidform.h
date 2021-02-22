/********************************************************************************
** Form generated from reading UI file 'writeeidform.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WRITEEIDFORM_H
#define UI_WRITEEIDFORM_H

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

class Ui_WriteEidForm
{
public:
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
    QLabel *label_4;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *WriteEidForm)
    {
        if (WriteEidForm->objectName().isEmpty())
            WriteEidForm->setObjectName(QStringLiteral("WriteEidForm"));
        WriteEidForm->resize(295, 184);
        verticalLayout = new QVBoxLayout(WriteEidForm);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalSpacer_2 = new QSpacerItem(20, 11, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(WriteEidForm);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        lineEdit = new QLineEdit(WriteEidForm);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        gridLayout->addWidget(lineEdit, 0, 1, 1, 1);

        label_2 = new QLabel(WriteEidForm);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        lineEdit_2 = new QLineEdit(WriteEidForm);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));

        gridLayout->addWidget(lineEdit_2, 1, 1, 1, 1);

        label_3 = new QLabel(WriteEidForm);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        lineEdit_3 = new QLineEdit(WriteEidForm);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));

        gridLayout->addWidget(lineEdit_3, 2, 1, 1, 1);

        label_4 = new QLabel(WriteEidForm);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 3, 0, 1, 2);


        horizontalLayout_2->addLayout(gridLayout);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);


        verticalLayout->addLayout(horizontalLayout_2);

        verticalSpacer = new QSpacerItem(20, 12, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton = new QPushButton(WriteEidForm);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout->addWidget(pushButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(WriteEidForm);

        QMetaObject::connectSlotsByName(WriteEidForm);
    } // setupUi

    void retranslateUi(QWidget *WriteEidForm)
    {
        WriteEidForm->setWindowTitle(QApplication::translate("WriteEidForm", "Form", Q_NULLPTR));
        label->setText(QApplication::translate("WriteEidForm", "\350\246\201\345\206\231\345\205\245\347\232\204\346\240\207\347\255\276ID\347\240\201", Q_NULLPTR));
        label_2->setText(QApplication::translate("WriteEidForm", "\345\206\231\345\205\245\347\232\204EID\347\240\201", Q_NULLPTR));
        label_3->setText(QApplication::translate("WriteEidForm", "\351\205\215\347\275\256\345\257\206\347\240\201", Q_NULLPTR));
        label_4->setText(QApplication::translate("WriteEidForm", "*\346\240\207\347\255\276\351\273\230\350\256\244\350\256\277\351\227\256\345\257\206\347\240\201\344\270\272\357\274\23200000000", Q_NULLPTR));
        pushButton->setText(QApplication::translate("WriteEidForm", "\345\206\231\345\205\245", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class WriteEidForm: public Ui_WriteEidForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WRITEEIDFORM_H
