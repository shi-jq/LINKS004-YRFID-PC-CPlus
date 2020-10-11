/********************************************************************************
** Form generated from reading UI file 'pointconfigform.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POINTCONFIGFORM_H
#define UI_POINTCONFIGFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PointConfigForm
{
public:
    QGridLayout *gridLayout_2;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_3;
    QGridLayout *gridLayout;
    QLabel *label_3;
    QComboBox *comboBox;
    QComboBox *comboBox_3;
    QComboBox *comboBox_2;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_4;
    QComboBox *comboBox_4;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_2;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *PointConfigForm)
    {
        if (PointConfigForm->objectName().isEmpty())
            PointConfigForm->setObjectName(QStringLiteral("PointConfigForm"));
        PointConfigForm->resize(328, 183);
        gridLayout_2 = new QGridLayout(PointConfigForm);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 0, 1, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_3 = new QLabel(PointConfigForm);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 3, 0, 1, 1);

        comboBox = new QComboBox(PointConfigForm);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        gridLayout->addWidget(comboBox, 0, 1, 1, 1);

        comboBox_3 = new QComboBox(PointConfigForm);
        comboBox_3->setObjectName(QStringLiteral("comboBox_3"));

        gridLayout->addWidget(comboBox_3, 3, 1, 1, 1);

        comboBox_2 = new QComboBox(PointConfigForm);
        comboBox_2->setObjectName(QStringLiteral("comboBox_2"));

        gridLayout->addWidget(comboBox_2, 2, 1, 1, 1);

        label = new QLabel(PointConfigForm);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(PointConfigForm);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 2, 0, 1, 1);

        label_4 = new QLabel(PointConfigForm);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 1, 0, 1, 1);

        comboBox_4 = new QComboBox(PointConfigForm);
        comboBox_4->setObjectName(QStringLiteral("comboBox_4"));

        gridLayout->addWidget(comboBox_4, 1, 1, 1, 1);


        horizontalLayout_2->addLayout(gridLayout);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);


        gridLayout_2->addLayout(horizontalLayout_2, 1, 0, 1, 2);

        verticalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_2, 2, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton_2 = new QPushButton(PointConfigForm);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);

        pushButton = new QPushButton(PointConfigForm);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout->addWidget(pushButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        gridLayout_2->addLayout(horizontalLayout, 3, 0, 1, 2);


        retranslateUi(PointConfigForm);

        QMetaObject::connectSlotsByName(PointConfigForm);
    } // setupUi

    void retranslateUi(QWidget *PointConfigForm)
    {
        PointConfigForm->setWindowTitle(QApplication::translate("PointConfigForm", "Form", Q_NULLPTR));
        label_3->setText(QApplication::translate("PointConfigForm", "\345\260\204\351\242\221\345\217\221\351\200\201\345\212\237\347\216\207", Q_NULLPTR));
        label->setText(QApplication::translate("PointConfigForm", "\345\212\237\347\216\207\351\205\215\347\275\256", Q_NULLPTR));
        label_2->setText(QApplication::translate("PointConfigForm", "\346\216\245\346\224\266\350\241\260\345\207\217\345\231\250\350\241\260\345\207\217", Q_NULLPTR));
        label_4->setText(QApplication::translate("PointConfigForm", "\345\212\237\346\224\276\346\216\245\346\224\266\345\242\236\347\233\212", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("PointConfigForm", "\346\237\245\350\257\242", Q_NULLPTR));
        pushButton->setText(QApplication::translate("PointConfigForm", "\350\256\276\347\275\256", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class PointConfigForm: public Ui_PointConfigForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POINTCONFIGFORM_H
