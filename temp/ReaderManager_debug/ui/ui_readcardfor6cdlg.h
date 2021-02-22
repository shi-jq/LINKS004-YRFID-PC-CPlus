/********************************************************************************
** Form generated from reading UI file 'readcardfor6cdlg.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_READCARDFOR6CDLG_H
#define UI_READCARDFOR6CDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ReadCardFor6CDlg
{
public:
    QGridLayout *gridLayout_3;
    QFrame *frame;
    QGridLayout *gridLayout_2;
    QTreeWidget *treeWidget;
    QHBoxLayout *horizontalLayout_4;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_3;
    QPushButton *pushButton_2;
    QPushButton *pushButton_4;
    QPushButton *pushButton_7;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *pushButton;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_6;
    QLabel *label_9;
    QSpacerItem *horizontalSpacer_5;
    QCheckBox *checkBox_2;
    QSpinBox *spinBox_2;
    QLabel *label_7;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;

    void setupUi(QWidget *ReadCardFor6CDlg)
    {
        if (ReadCardFor6CDlg->objectName().isEmpty())
            ReadCardFor6CDlg->setObjectName(QStringLiteral("ReadCardFor6CDlg"));
        ReadCardFor6CDlg->resize(822, 491);
        gridLayout_3 = new QGridLayout(ReadCardFor6CDlg);
        gridLayout_3->setSpacing(0);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        frame = new QFrame(ReadCardFor6CDlg);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setStyleSheet(QLatin1String(".QFrame\n"
"{\n"
"	background-color: rgb(245, 245, 245);\n"
"}"));
        frame->setFrameShape(QFrame::NoFrame);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(frame);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(9, 9, 9, 9);
        treeWidget = new QTreeWidget(frame);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));
        treeWidget->setStyleSheet(QStringLiteral(""));
        treeWidget->setAlternatingRowColors(true);

        gridLayout_2->addWidget(treeWidget, 2, 1, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);


        horizontalLayout_4->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        pushButton_3 = new QPushButton(frame);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setEnabled(true);
        pushButton_3->setStyleSheet(QStringLiteral(""));

        horizontalLayout_2->addWidget(pushButton_3);

        pushButton_2 = new QPushButton(frame);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout_2->addWidget(pushButton_2);

        pushButton_4 = new QPushButton(frame);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));

        horizontalLayout_2->addWidget(pushButton_4);

        pushButton_7 = new QPushButton(frame);
        pushButton_7->setObjectName(QStringLiteral("pushButton_7"));

        horizontalLayout_2->addWidget(pushButton_7);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        horizontalLayout_4->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);

        pushButton = new QPushButton(frame);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setStyleSheet(QStringLiteral(""));

        horizontalLayout_3->addWidget(pushButton);


        horizontalLayout_4->addLayout(horizontalLayout_3);


        gridLayout_2->addLayout(horizontalLayout_4, 0, 1, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_6 = new QLabel(frame);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_5->addWidget(label_6);

        label_9 = new QLabel(frame);
        label_9->setObjectName(QStringLiteral("label_9"));

        horizontalLayout_5->addWidget(label_9);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_5);

        checkBox_2 = new QCheckBox(frame);
        checkBox_2->setObjectName(QStringLiteral("checkBox_2"));
        checkBox_2->setStyleSheet(QStringLiteral(""));

        horizontalLayout_5->addWidget(checkBox_2);

        spinBox_2 = new QSpinBox(frame);
        spinBox_2->setObjectName(QStringLiteral("spinBox_2"));
        spinBox_2->setMinimumSize(QSize(60, 0));
        spinBox_2->setStyleSheet(QStringLiteral(""));
        spinBox_2->setMaximum(9999);

        horizontalLayout_5->addWidget(spinBox_2);

        label_7 = new QLabel(frame);
        label_7->setObjectName(QStringLiteral("label_7"));

        horizontalLayout_5->addWidget(label_7);

        pushButton_5 = new QPushButton(frame);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));

        horizontalLayout_5->addWidget(pushButton_5);

        pushButton_6 = new QPushButton(frame);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));

        horizontalLayout_5->addWidget(pushButton_6);


        gridLayout_2->addLayout(horizontalLayout_5, 3, 1, 1, 1);


        gridLayout_3->addWidget(frame, 0, 0, 1, 1);


        retranslateUi(ReadCardFor6CDlg);

        QMetaObject::connectSlotsByName(ReadCardFor6CDlg);
    } // setupUi

    void retranslateUi(QWidget *ReadCardFor6CDlg)
    {
        ReadCardFor6CDlg->setWindowTitle(QApplication::translate("ReadCardFor6CDlg", "Form", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("ReadCardFor6CDlg", "\344\270\273\345\212\250\346\240\207\347\255\276", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("ReadCardFor6CDlg", "\350\242\253\345\212\250\346\240\207\347\255\276", Q_NULLPTR));
        pushButton_4->setText(QApplication::translate("ReadCardFor6CDlg", "\345\201\234\346\255\242", Q_NULLPTR));
        pushButton_7->setText(QApplication::translate("ReadCardFor6CDlg", "\346\240\207\347\255\276\346\223\215\344\275\234", Q_NULLPTR));
        pushButton->setText(QApplication::translate("ReadCardFor6CDlg", "\346\270\205\347\251\272", Q_NULLPTR));
        label_6->setText(QApplication::translate("ReadCardFor6CDlg", "\350\257\273\345\215\241\346\200\273\346\254\241\346\225\260:", Q_NULLPTR));
        label_9->setText(QApplication::translate("ReadCardFor6CDlg", "0", Q_NULLPTR));
        checkBox_2->setText(QApplication::translate("ReadCardFor6CDlg", "\344\277\235\345\255\230\350\256\260\345\275\225", Q_NULLPTR));
        label_7->setText(QApplication::translate("ReadCardFor6CDlg", "ms", Q_NULLPTR));
        pushButton_5->setText(QApplication::translate("ReadCardFor6CDlg", "\346\267\273\345\212\240\350\277\207\346\273\244", Q_NULLPTR));
        pushButton_6->setText(QApplication::translate("ReadCardFor6CDlg", "\346\270\205\347\251\272\350\277\207\346\273\244", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ReadCardFor6CDlg: public Ui_ReadCardFor6CDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_READCARDFOR6CDLG_H
