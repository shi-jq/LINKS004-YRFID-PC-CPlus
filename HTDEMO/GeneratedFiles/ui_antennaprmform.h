/********************************************************************************
** Form generated from reading UI file 'antennaprmform.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ANTENNAPRMFORM_H
#define UI_ANTENNAPRMFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
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

class Ui_AntennaPrmForm
{
public:
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_4;
    QGridLayout *gridLayout;
    QSpinBox *spinBox_4;
    QSpinBox *spinBox_2;
    QCheckBox *checkBox;
    QCheckBox *checkBox_3;
    QCheckBox *checkBox_2;
    QSpinBox *spinBox_3;
    QSpinBox *spinBox;
    QLabel *label_18;
    QLabel *label_16;
    QCheckBox *checkBox_4;
    QLabel *label;
    QComboBox *comboBox;
    QComboBox *comboBox_2;
    QComboBox *comboBox_3;
    QComboBox *comboBox_4;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *AntennaPrmForm)
    {
        if (AntennaPrmForm->objectName().isEmpty())
            AntennaPrmForm->setObjectName(QStringLiteral("AntennaPrmForm"));
        AntennaPrmForm->setEnabled(true);
        AntennaPrmForm->resize(423, 278);
        verticalLayout = new QVBoxLayout(AntennaPrmForm);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        spinBox_4 = new QSpinBox(AntennaPrmForm);
        spinBox_4->setObjectName(QStringLiteral("spinBox_4"));
        spinBox_4->setStyleSheet(QStringLiteral(""));

        gridLayout->addWidget(spinBox_4, 4, 1, 1, 1);

        spinBox_2 = new QSpinBox(AntennaPrmForm);
        spinBox_2->setObjectName(QStringLiteral("spinBox_2"));
        spinBox_2->setStyleSheet(QStringLiteral(""));

        gridLayout->addWidget(spinBox_2, 2, 1, 1, 1);

        checkBox = new QCheckBox(AntennaPrmForm);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setStyleSheet(QStringLiteral(""));

        gridLayout->addWidget(checkBox, 1, 0, 1, 1);

        checkBox_3 = new QCheckBox(AntennaPrmForm);
        checkBox_3->setObjectName(QStringLiteral("checkBox_3"));
        checkBox_3->setStyleSheet(QStringLiteral(""));

        gridLayout->addWidget(checkBox_3, 3, 0, 1, 1);

        checkBox_2 = new QCheckBox(AntennaPrmForm);
        checkBox_2->setObjectName(QStringLiteral("checkBox_2"));
        checkBox_2->setStyleSheet(QStringLiteral(""));

        gridLayout->addWidget(checkBox_2, 2, 0, 1, 1);

        spinBox_3 = new QSpinBox(AntennaPrmForm);
        spinBox_3->setObjectName(QStringLiteral("spinBox_3"));
        spinBox_3->setStyleSheet(QStringLiteral(""));

        gridLayout->addWidget(spinBox_3, 3, 1, 1, 1);

        spinBox = new QSpinBox(AntennaPrmForm);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setStyleSheet(QStringLiteral(""));

        gridLayout->addWidget(spinBox, 1, 1, 1, 1);

        label_18 = new QLabel(AntennaPrmForm);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_18, 0, 1, 1, 1);

        label_16 = new QLabel(AntennaPrmForm);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_16, 0, 0, 1, 1);

        checkBox_4 = new QCheckBox(AntennaPrmForm);
        checkBox_4->setObjectName(QStringLiteral("checkBox_4"));
        checkBox_4->setStyleSheet(QStringLiteral(""));

        gridLayout->addWidget(checkBox_4, 4, 0, 1, 1);

        label = new QLabel(AntennaPrmForm);
        label->setObjectName(QStringLiteral("label"));
        label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label, 0, 2, 1, 1);

        comboBox = new QComboBox(AntennaPrmForm);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        gridLayout->addWidget(comboBox, 1, 2, 1, 1);

        comboBox_2 = new QComboBox(AntennaPrmForm);
        comboBox_2->setObjectName(QStringLiteral("comboBox_2"));

        gridLayout->addWidget(comboBox_2, 2, 2, 1, 1);

        comboBox_3 = new QComboBox(AntennaPrmForm);
        comboBox_3->setObjectName(QStringLiteral("comboBox_3"));

        gridLayout->addWidget(comboBox_3, 3, 2, 1, 1);

        comboBox_4 = new QComboBox(AntennaPrmForm);
        comboBox_4->setObjectName(QStringLiteral("comboBox_4"));

        gridLayout->addWidget(comboBox_4, 4, 2, 1, 1);


        horizontalLayout_2->addLayout(gridLayout);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout_2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton = new QPushButton(AntennaPrmForm);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(AntennaPrmForm);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(AntennaPrmForm);

        QMetaObject::connectSlotsByName(AntennaPrmForm);
    } // setupUi

    void retranslateUi(QWidget *AntennaPrmForm)
    {
        AntennaPrmForm->setWindowTitle(QApplication::translate("AntennaPrmForm", "Form", Q_NULLPTR));
        checkBox->setText(QApplication::translate("AntennaPrmForm", "\345\244\251\347\272\2771", Q_NULLPTR));
        checkBox_3->setText(QApplication::translate("AntennaPrmForm", "\345\244\251\347\272\2773", Q_NULLPTR));
        checkBox_2->setText(QApplication::translate("AntennaPrmForm", "\345\244\251\347\272\2772", Q_NULLPTR));
        label_18->setText(QApplication::translate("AntennaPrmForm", "\350\275\256\350\257\242\346\227\266\351\227\264(*20ms)", Q_NULLPTR));
        label_16->setText(QApplication::translate("AntennaPrmForm", "\345\244\251\347\272\277\345\217\267", Q_NULLPTR));
        checkBox_4->setText(QApplication::translate("AntennaPrmForm", "\345\244\251\347\272\2774", Q_NULLPTR));
        label->setText(QApplication::translate("AntennaPrmForm", "\350\241\260\345\207\217", Q_NULLPTR));
        pushButton->setText(QApplication::translate("AntennaPrmForm", "\346\237\245\350\257\242", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("AntennaPrmForm", "\351\205\215\347\275\256", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class AntennaPrmForm: public Ui_AntennaPrmForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ANTENNAPRMFORM_H
