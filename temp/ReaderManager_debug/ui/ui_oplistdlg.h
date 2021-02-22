/********************************************************************************
** Form generated from reading UI file 'oplistdlg.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPLISTDLG_H
#define UI_OPLISTDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OpListDlg
{
public:
    QGridLayout *gridLayout_2;
    QWidget *widget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;
    QTreeWidget *treeWidget;

    void setupUi(QWidget *OpListDlg)
    {
        if (OpListDlg->objectName().isEmpty())
            OpListDlg->setObjectName(QStringLiteral("OpListDlg"));
        OpListDlg->resize(400, 300);
        gridLayout_2 = new QGridLayout(OpListDlg);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        widget = new QWidget(OpListDlg);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setStyleSheet(QStringLiteral(""));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setHorizontalSpacing(0);
        gridLayout->setVerticalSpacing(6);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setStyleSheet(QStringLiteral(""));

        horizontalLayout->addWidget(pushButton);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        treeWidget = new QTreeWidget(widget);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));
        treeWidget->setStyleSheet(QLatin1String(".QTreeWidget\n"
"{\n"
"	border: 1px solid rgb(218,218,218);\n"
"	border-radius: 6px;\n"
"	background-color: rgb(251, 252, 254);\n"
"}"));
        treeWidget->setInputMethodHints(Qt::ImhNone);
        treeWidget->header()->setVisible(false);

        gridLayout->addWidget(treeWidget, 1, 0, 1, 1);

        treeWidget->raise();

        gridLayout_2->addWidget(widget, 0, 0, 1, 1);


        retranslateUi(OpListDlg);

        QMetaObject::connectSlotsByName(OpListDlg);
    } // setupUi

    void retranslateUi(QWidget *OpListDlg)
    {
        OpListDlg->setWindowTitle(QApplication::translate("OpListDlg", "Form", Q_NULLPTR));
        pushButton->setText(QApplication::translate("OpListDlg", "\346\270\205\347\251\272", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class OpListDlg: public Ui_OpListDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPLISTDLG_H
