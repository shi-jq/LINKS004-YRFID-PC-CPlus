/********************************************************************************
** Form generated from reading UI file 'tagopdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TAGOPDIALOG_H
#define UI_TAGOPDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QStackedWidget>

QT_BEGIN_NAMESPACE

class Ui_TagOpDialog
{
public:
    QGridLayout *gridLayout;
    QListWidget *listWidget;
    QStackedWidget *stackedWidget;

    void setupUi(QDialog *TagOpDialog)
    {
        if (TagOpDialog->objectName().isEmpty())
            TagOpDialog->setObjectName(QStringLiteral("TagOpDialog"));
        TagOpDialog->resize(598, 328);
        gridLayout = new QGridLayout(TagOpDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        listWidget = new QListWidget(TagOpDialog);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setMaximumSize(QSize(150, 16777215));

        gridLayout->addWidget(listWidget, 0, 0, 1, 1);

        stackedWidget = new QStackedWidget(TagOpDialog);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));

        gridLayout->addWidget(stackedWidget, 0, 1, 1, 1);


        retranslateUi(TagOpDialog);

        QMetaObject::connectSlotsByName(TagOpDialog);
    } // setupUi

    void retranslateUi(QDialog *TagOpDialog)
    {
        TagOpDialog->setWindowTitle(QApplication::translate("TagOpDialog", "Dialog", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class TagOpDialog: public Ui_TagOpDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TAGOPDIALOG_H
