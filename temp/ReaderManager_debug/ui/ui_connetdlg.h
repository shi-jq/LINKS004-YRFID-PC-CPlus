/********************************************************************************
** Form generated from reading UI file 'connetdlg.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONNETDLG_H
#define UI_CONNETDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ConnetDlg
{
public:
    QGridLayout *gridLayout_7;
    QTreeWidget *treeWidget;
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *pushButton_6;
    QPushButton *pushButton_5;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_9;
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QLabel *LableCompanyTitle;
    QLabel *LableAppTitle;
    QWidget *widget_2;
    QGridLayout *gridLayout_4;
    QWidget *widget_23;
    QGridLayout *gridLayout_6;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_11;
    QComboBox *comboBox_4;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QGridLayout *gridLayout;
    QLabel *label_2;
    QLabel *label_15;
    QLineEdit *lineEdit_2;
    QPushButton *pushButton_4;
    QComboBox *comboBox_3;
    QWidget *page_2;
    QGridLayout *gridLayout_3;
    QComboBox *comboBox;
    QComboBox *comboBox_2;
    QLabel *label;
    QLabel *label_4;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *pushButton_7;
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
    QLabel *label_14;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit;
    QSpacerItem *horizontalSpacer;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer_5;

    void setupUi(QWidget *ConnetDlg)
    {
        if (ConnetDlg->objectName().isEmpty())
            ConnetDlg->setObjectName(QStringLiteral("ConnetDlg"));
        ConnetDlg->resize(350, 812);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ConnetDlg->sizePolicy().hasHeightForWidth());
        ConnetDlg->setSizePolicy(sizePolicy);
        gridLayout_7 = new QGridLayout(ConnetDlg);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        treeWidget = new QTreeWidget(ConnetDlg);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(treeWidget->sizePolicy().hasHeightForWidth());
        treeWidget->setSizePolicy(sizePolicy1);
        treeWidget->setMinimumSize(QSize(0, 150));

        gridLayout_7->addWidget(treeWidget, 2, 0, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        label_5 = new QLabel(ConnetDlg);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(label_5);

        label_6 = new QLabel(ConnetDlg);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setStyleSheet(QLatin1String("font: 28pt \"Arial\";\n"
"color:qlineargradient(spread:pad, x1:0.5, y1:0, x2:0.5, y2:1, stop:0 #44a3df, stop:1 #2988d3);"));
        label_6->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(label_6);

        label_7 = new QLabel(ConnetDlg);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(label_7);

        label_8 = new QLabel(ConnetDlg);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setStyleSheet(QLatin1String("font: 28pt \"Arial\";\n"
"color:qlineargradient(spread:pad, x1:0.5, y1:0, x2:0.5, y2:1, stop:0 #44a3df, stop:1 #2988d3);"));
        label_8->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(label_8);


        horizontalLayout_6->addLayout(verticalLayout_3);


        gridLayout_7->addLayout(horizontalLayout_6, 8, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 112, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_7->addItem(verticalSpacer, 7, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer_4 = new QSpacerItem(0, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);

        pushButton_6 = new QPushButton(ConnetDlg);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));

        horizontalLayout_3->addWidget(pushButton_6);

        pushButton_5 = new QPushButton(ConnetDlg);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));

        horizontalLayout_3->addWidget(pushButton_5);

        pushButton_2 = new QPushButton(ConnetDlg);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout_3->addWidget(pushButton_2);

        pushButton_3 = new QPushButton(ConnetDlg);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        horizontalLayout_3->addWidget(pushButton_3);

        horizontalSpacer_3 = new QSpacerItem(0, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);


        gridLayout_7->addLayout(horizontalLayout_3, 3, 0, 1, 1);

        label_9 = new QLabel(ConnetDlg);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setMinimumSize(QSize(0, 30));

        gridLayout_7->addWidget(label_9, 1, 0, 1, 1);

        widget = new QWidget(ConnetDlg);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setEnabled(true);
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        LableCompanyTitle = new QLabel(widget);
        LableCompanyTitle->setObjectName(QStringLiteral("LableCompanyTitle"));
        LableCompanyTitle->setMinimumSize(QSize(100, 100));
        LableCompanyTitle->setStyleSheet(QStringLiteral(""));
        LableCompanyTitle->setScaledContents(false);

        verticalLayout_2->addWidget(LableCompanyTitle);

        LableAppTitle = new QLabel(widget);
        LableAppTitle->setObjectName(QStringLiteral("LableAppTitle"));

        verticalLayout_2->addWidget(LableAppTitle);


        gridLayout_7->addWidget(widget, 0, 0, 1, 1);

        widget_2 = new QWidget(ConnetDlg);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(widget_2->sizePolicy().hasHeightForWidth());
        widget_2->setSizePolicy(sizePolicy2);
        gridLayout_4 = new QGridLayout(widget_2);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        widget_23 = new QWidget(widget_2);
        widget_23->setObjectName(QStringLiteral("widget_23"));
        sizePolicy.setHeightForWidth(widget_23->sizePolicy().hasHeightForWidth());
        widget_23->setSizePolicy(sizePolicy);
        gridLayout_6 = new QGridLayout(widget_23);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        gridLayout_6->setContentsMargins(-1, -1, -1, 0);
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        label_11 = new QLabel(widget_23);
        label_11->setObjectName(QStringLiteral("label_11"));

        horizontalLayout_9->addWidget(label_11);


        gridLayout_6->addLayout(horizontalLayout_9, 0, 0, 1, 1);

        comboBox_4 = new QComboBox(widget_23);
        comboBox_4->setObjectName(QStringLiteral("comboBox_4"));
        comboBox_4->setStyleSheet(QStringLiteral(""));

        gridLayout_6->addWidget(comboBox_4, 0, 1, 1, 1);


        gridLayout_4->addWidget(widget_23, 0, 0, 1, 1);

        stackedWidget = new QStackedWidget(widget_2);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        stackedWidget->setEnabled(true);
        sizePolicy2.setHeightForWidth(stackedWidget->sizePolicy().hasHeightForWidth());
        stackedWidget->setSizePolicy(sizePolicy2);
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        gridLayout = new QGridLayout(page);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(-1, 2, -1, -1);
        label_2 = new QLabel(page);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        label_15 = new QLabel(page);
        label_15->setObjectName(QStringLiteral("label_15"));

        gridLayout->addWidget(label_15, 1, 0, 1, 1);

        lineEdit_2 = new QLineEdit(page);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setMaximumSize(QSize(60, 16777215));

        gridLayout->addWidget(lineEdit_2, 1, 1, 1, 1);

        pushButton_4 = new QPushButton(page);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));

        gridLayout->addWidget(pushButton_4, 1, 2, 1, 1);

        comboBox_3 = new QComboBox(page);
        comboBox_3->setObjectName(QStringLiteral("comboBox_3"));
        comboBox_3->setMaximumSize(QSize(180, 16777215));

        gridLayout->addWidget(comboBox_3, 0, 1, 1, 2);

        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        gridLayout_3 = new QGridLayout(page_2);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(-1, 2, -1, -1);
        comboBox = new QComboBox(page_2);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setStyleSheet(QStringLiteral(""));

        gridLayout_3->addWidget(comboBox, 1, 1, 1, 1);

        comboBox_2 = new QComboBox(page_2);
        comboBox_2->setObjectName(QStringLiteral("comboBox_2"));
        comboBox_2->setStyleSheet(QStringLiteral(""));

        gridLayout_3->addWidget(comboBox_2, 3, 1, 1, 1);

        label = new QLabel(page_2);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_3->addWidget(label, 3, 0, 1, 1);

        label_4 = new QLabel(page_2);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout_3->addWidget(label_4, 1, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_6);

        pushButton_7 = new QPushButton(page_2);
        pushButton_7->setObjectName(QStringLiteral("pushButton_7"));

        horizontalLayout_4->addWidget(pushButton_7);


        gridLayout_3->addLayout(horizontalLayout_4, 2, 0, 1, 2);

        stackedWidget->addWidget(page_2);
        page_3 = new QWidget();
        page_3->setObjectName(QStringLiteral("page_3"));
        gridLayout_5 = new QGridLayout(page_3);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        gridLayout_5->setContentsMargins(-1, 2, -1, -1);
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
        gridLayout_2->setContentsMargins(-1, 2, -1, -1);
        label_10 = new QLabel(page_4);
        label_10->setObjectName(QStringLiteral("label_10"));

        gridLayout_2->addWidget(label_10, 0, 0, 1, 1);

        comboBox_6 = new QComboBox(page_4);
        comboBox_6->setObjectName(QStringLiteral("comboBox_6"));
        comboBox_6->setMaximumSize(QSize(180, 16777215));

        gridLayout_2->addWidget(comboBox_6, 0, 1, 1, 1);

        label_14 = new QLabel(page_4);
        label_14->setObjectName(QStringLiteral("label_14"));

        gridLayout_2->addWidget(label_14, 1, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        lineEdit = new QLineEdit(page_4);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setMaximumSize(QSize(60, 16777215));

        horizontalLayout->addWidget(lineEdit);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        gridLayout_2->addLayout(horizontalLayout, 1, 1, 1, 1);

        stackedWidget->addWidget(page_4);

        gridLayout_4->addWidget(stackedWidget, 1, 0, 1, 1);


        gridLayout_7->addWidget(widget_2, 5, 0, 1, 1);

        widget_3 = new QWidget(ConnetDlg);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        sizePolicy.setHeightForWidth(widget_3->sizePolicy().hasHeightForWidth());
        widget_3->setSizePolicy(sizePolicy);
        horizontalLayout_2 = new QHBoxLayout(widget_3);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_2 = new QSpacerItem(1, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        pushButton = new QPushButton(widget_3);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setStyleSheet(QStringLiteral(""));

        horizontalLayout_2->addWidget(pushButton);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_5);


        gridLayout_7->addWidget(widget_3, 6, 0, 1, 1);


        retranslateUi(ConnetDlg);

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(ConnetDlg);
    } // setupUi

    void retranslateUi(QWidget *ConnetDlg)
    {
        ConnetDlg->setWindowTitle(QApplication::translate("ConnetDlg", "Form", Q_NULLPTR));
        label_5->setText(QApplication::translate("ConnetDlg", "\346\240\207\347\255\276\346\200\273\346\225\260(\345\274\240):", Q_NULLPTR));
        label_6->setText(QApplication::translate("ConnetDlg", "0", Q_NULLPTR));
        label_7->setText(QApplication::translate("ConnetDlg", "\350\257\273\345\215\241\351\200\237\345\272\246(\346\254\241/\347\247\222):", Q_NULLPTR));
        label_8->setText(QApplication::translate("ConnetDlg", "0", Q_NULLPTR));
        pushButton_6->setText(QApplication::translate("ConnetDlg", "\350\277\236\346\216\245", Q_NULLPTR));
        pushButton_5->setText(QApplication::translate("ConnetDlg", "\346\226\255\345\274\200", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("ConnetDlg", "\351\207\215\345\220\257", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("ConnetDlg", "\346\270\205\347\251\272", Q_NULLPTR));
        label_9->setText(QString());
        LableCompanyTitle->setText(QString());
        LableAppTitle->setText(QString());
        label_11->setText(QApplication::translate("ConnetDlg", "\350\277\236\346\216\245\346\226\271\345\274\217:", Q_NULLPTR));
        label_2->setText(QApplication::translate("ConnetDlg", "IP\345\234\260\345\235\200", Q_NULLPTR));
        label_15->setText(QApplication::translate("ConnetDlg", "\347\253\257\345\217\243", Q_NULLPTR));
        pushButton_4->setText(QApplication::translate("ConnetDlg", "\346\237\245\350\257\242", Q_NULLPTR));
        label->setText(QApplication::translate("ConnetDlg", "\346\263\242\347\211\271\347\216\207:", Q_NULLPTR));
        label_4->setText(QApplication::translate("ConnetDlg", "\344\270\262\345\217\243\345\217\267:", Q_NULLPTR));
        pushButton_7->setText(QApplication::translate("ConnetDlg", "\345\210\267\346\226\260", Q_NULLPTR));
        label_13->setText(QApplication::translate("ConnetDlg", "USB\345\217\243:", Q_NULLPTR));
        label_3->setText(QApplication::translate("ConnetDlg", "\346\263\242\347\211\271\347\216\207:", Q_NULLPTR));
        label_10->setText(QApplication::translate("ConnetDlg", "IP\345\234\260\345\235\200", Q_NULLPTR));
        label_14->setText(QApplication::translate("ConnetDlg", "\347\253\257\345\217\243", Q_NULLPTR));
        pushButton->setText(QApplication::translate("ConnetDlg", "\346\267\273\345\212\240\350\277\236\346\216\245", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ConnetDlg: public Ui_ConnetDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONNETDLG_H
