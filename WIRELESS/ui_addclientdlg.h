/********************************************************************************
** Form generated from reading UI file 'addclientdlg.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDCLIENTDLG_H
#define UI_ADDCLIENTDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AddClientDlg
{
public:
    QGridLayout *gridLayout_7;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QSpacerItem *horizontalSpacer_2;
    QWidget *widget_2;
    QGridLayout *gridLayout_4;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QComboBox *comboBox_3;
    QWidget *page_2;
    QGridLayout *gridLayout_3;
    QComboBox *comboBox;
    QLabel *label_4;
    QComboBox *comboBox_2;
    QLabel *label;
    QWidget *page_3;
    QGridLayout *gridLayout_5;
    QLabel *label_13;
    QComboBox *comboBox_7;
    QLabel *label_3;
    QComboBox *comboBox_5;
    QWidget *page_4;
    QGridLayout *gridLayout_2;
    QLabel *label_10;
    QComboBox *comboBox_6;
    QWidget *widget_3;
    QGridLayout *gridLayout_6;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_11;
    QComboBox *comboBox_4;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QDialog *AddClientDlg)
    {
        if (AddClientDlg->objectName().isEmpty())
            AddClientDlg->setObjectName(QStringLiteral("AddClientDlg"));
        AddClientDlg->resize(340, 217);
        gridLayout_7 = new QGridLayout(AddClientDlg);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        pushButton = new QPushButton(AddClientDlg);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout_2->addWidget(pushButton);

        pushButton_2 = new QPushButton(AddClientDlg);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout_2->addWidget(pushButton_2);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        gridLayout_7->addLayout(horizontalLayout_2, 3, 1, 1, 1);

        widget_2 = new QWidget(AddClientDlg);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget_2->sizePolicy().hasHeightForWidth());
        widget_2->setSizePolicy(sizePolicy);
        gridLayout_4 = new QGridLayout(widget_2);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        stackedWidget = new QStackedWidget(widget_2);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        stackedWidget->setEnabled(true);
        sizePolicy.setHeightForWidth(stackedWidget->sizePolicy().hasHeightForWidth());
        stackedWidget->setSizePolicy(sizePolicy);
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        gridLayout = new QGridLayout(page);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_2 = new QLabel(page);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 1);

        comboBox_3 = new QComboBox(page);
        comboBox_3->setObjectName(QStringLiteral("comboBox_3"));

        gridLayout->addWidget(comboBox_3, 2, 0, 1, 1);

        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        gridLayout_3 = new QGridLayout(page_2);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        comboBox = new QComboBox(page_2);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setStyleSheet(QStringLiteral(""));

        gridLayout_3->addWidget(comboBox, 1, 1, 1, 1);

        label_4 = new QLabel(page_2);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout_3->addWidget(label_4, 1, 0, 1, 1);

        comboBox_2 = new QComboBox(page_2);
        comboBox_2->setObjectName(QStringLiteral("comboBox_2"));
        comboBox_2->setStyleSheet(QStringLiteral(""));

        gridLayout_3->addWidget(comboBox_2, 2, 1, 1, 1);

        label = new QLabel(page_2);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_3->addWidget(label, 2, 0, 1, 1);

        stackedWidget->addWidget(page_2);
        page_3 = new QWidget();
        page_3->setObjectName(QStringLiteral("page_3"));
        gridLayout_5 = new QGridLayout(page_3);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        label_13 = new QLabel(page_3);
        label_13->setObjectName(QStringLiteral("label_13"));

        gridLayout_5->addWidget(label_13, 0, 0, 1, 1);

        comboBox_7 = new QComboBox(page_3);
        comboBox_7->setObjectName(QStringLiteral("comboBox_7"));
        comboBox_7->setStyleSheet(QStringLiteral(""));

        gridLayout_5->addWidget(comboBox_7, 0, 1, 1, 1);

        label_3 = new QLabel(page_3);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout_5->addWidget(label_3, 1, 0, 1, 1);

        comboBox_5 = new QComboBox(page_3);
        comboBox_5->setObjectName(QStringLiteral("comboBox_5"));
        comboBox_5->setStyleSheet(QStringLiteral(""));

        gridLayout_5->addWidget(comboBox_5, 1, 1, 1, 1);

        stackedWidget->addWidget(page_3);
        page_4 = new QWidget();
        page_4->setObjectName(QStringLiteral("page_4"));
        gridLayout_2 = new QGridLayout(page_4);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        label_10 = new QLabel(page_4);
        label_10->setObjectName(QStringLiteral("label_10"));

        gridLayout_2->addWidget(label_10, 0, 0, 1, 1);

        comboBox_6 = new QComboBox(page_4);
        comboBox_6->setObjectName(QStringLiteral("comboBox_6"));

        gridLayout_2->addWidget(comboBox_6, 1, 0, 1, 1);

        stackedWidget->addWidget(page_4);

        gridLayout_4->addWidget(stackedWidget, 1, 0, 1, 1);

        widget_3 = new QWidget(widget_2);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(widget_3->sizePolicy().hasHeightForWidth());
        widget_3->setSizePolicy(sizePolicy1);
        gridLayout_6 = new QGridLayout(widget_3);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        gridLayout_6->setContentsMargins(-1, -1, -1, 0);
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        label_11 = new QLabel(widget_3);
        label_11->setObjectName(QStringLiteral("label_11"));

        horizontalLayout_9->addWidget(label_11);

        comboBox_4 = new QComboBox(widget_3);
        comboBox_4->setObjectName(QStringLiteral("comboBox_4"));

        horizontalLayout_9->addWidget(comboBox_4);


        gridLayout_6->addLayout(horizontalLayout_9, 0, 0, 1, 1);


        gridLayout_4->addWidget(widget_3, 0, 0, 1, 1);


        gridLayout_7->addWidget(widget_2, 1, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_7->addItem(verticalSpacer, 0, 1, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_7->addItem(horizontalSpacer_4, 1, 2, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_7->addItem(horizontalSpacer_3, 1, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_7->addItem(verticalSpacer_2, 2, 1, 1, 1);


        retranslateUi(AddClientDlg);

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(AddClientDlg);
    } // setupUi

    void retranslateUi(QDialog *AddClientDlg)
    {
        AddClientDlg->setWindowTitle(QApplication::translate("AddClientDlg", "Dialog", Q_NULLPTR));
        pushButton->setText(QApplication::translate("AddClientDlg", "\346\267\273\345\212\240", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("AddClientDlg", "\345\217\226\346\266\210", Q_NULLPTR));
        label_2->setText(QApplication::translate("AddClientDlg", "IP\345\234\260\345\235\200", Q_NULLPTR));
        label_4->setText(QApplication::translate("AddClientDlg", "\344\270\262\345\217\243\345\217\267:", Q_NULLPTR));
        label->setText(QApplication::translate("AddClientDlg", "\346\263\242\347\211\271\347\216\207:", Q_NULLPTR));
        label_13->setText(QApplication::translate("AddClientDlg", "USB\345\217\243:", Q_NULLPTR));
        label_3->setText(QApplication::translate("AddClientDlg", "\346\263\242\347\211\271\347\216\207:", Q_NULLPTR));
        label_10->setText(QApplication::translate("AddClientDlg", "IP\345\234\260\345\235\200", Q_NULLPTR));
        label_11->setText(QApplication::translate("AddClientDlg", "\350\277\236\346\216\245\346\226\271\345\274\217:", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class AddClientDlg: public Ui_AddClientDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDCLIENTDLG_H
