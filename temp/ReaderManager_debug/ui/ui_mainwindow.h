/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action;
    QAction *action_2;
    QAction *action_3;
    QAction *action_4;
    QAction *action_5;
    QAction *action_11;
    QAction *action_13;
    QAction *action_6;
    QAction *action_8;
    QAction *action_9;
    QAction *action_10;
    QAction *action_12;
    QAction *action_7;
    QAction *action_16;
    QAction *action_18;
    QAction *actionUDP;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QWidget *widget_4;
    QVBoxLayout *verticalLayout;
    QWidget *widget_2;
    QWidget *widget_3;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1051, 676);
        QIcon icon;
        icon.addFile(QStringLiteral(":/ico/skin/casc2.ico"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        action = new QAction(MainWindow);
        action->setObjectName(QStringLiteral("action"));
        action_2 = new QAction(MainWindow);
        action_2->setObjectName(QStringLiteral("action_2"));
        action_3 = new QAction(MainWindow);
        action_3->setObjectName(QStringLiteral("action_3"));
        action_4 = new QAction(MainWindow);
        action_4->setObjectName(QStringLiteral("action_4"));
        action_5 = new QAction(MainWindow);
        action_5->setObjectName(QStringLiteral("action_5"));
        action_11 = new QAction(MainWindow);
        action_11->setObjectName(QStringLiteral("action_11"));
        action_13 = new QAction(MainWindow);
        action_13->setObjectName(QStringLiteral("action_13"));
        action_6 = new QAction(MainWindow);
        action_6->setObjectName(QStringLiteral("action_6"));
        action_8 = new QAction(MainWindow);
        action_8->setObjectName(QStringLiteral("action_8"));
        action_9 = new QAction(MainWindow);
        action_9->setObjectName(QStringLiteral("action_9"));
        action_10 = new QAction(MainWindow);
        action_10->setObjectName(QStringLiteral("action_10"));
        action_12 = new QAction(MainWindow);
        action_12->setObjectName(QStringLiteral("action_12"));
        action_7 = new QAction(MainWindow);
        action_7->setObjectName(QStringLiteral("action_7"));
        action_16 = new QAction(MainWindow);
        action_16->setObjectName(QStringLiteral("action_16"));
        action_18 = new QAction(MainWindow);
        action_18->setObjectName(QStringLiteral("action_18"));
        actionUDP = new QAction(MainWindow);
        actionUDP->setObjectName(QStringLiteral("actionUDP"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setStyleSheet(QLatin1String(".QWidget\n"
"{\n"
"	background-color: rgb(240, 241, 243);\n"
"}"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        widget->setStyleSheet(QStringLiteral(""));

        horizontalLayout->addWidget(widget);

        widget_4 = new QWidget(centralWidget);
        widget_4->setObjectName(QStringLiteral("widget_4"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(10);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(widget_4->sizePolicy().hasHeightForWidth());
        widget_4->setSizePolicy(sizePolicy1);
        verticalLayout = new QVBoxLayout(widget_4);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        widget_2 = new QWidget(widget_4);
        widget_2->setObjectName(QStringLiteral("widget_2"));

        verticalLayout->addWidget(widget_2);

        widget_3 = new QWidget(widget_4);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(widget_3->sizePolicy().hasHeightForWidth());
        widget_3->setSizePolicy(sizePolicy2);

        verticalLayout->addWidget(widget_3);


        horizontalLayout->addWidget(widget_4);

        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        action->setText(QApplication::translate("MainWindow", "\347\201\265\346\225\217\345\272\246\346\265\213\350\257\225", Q_NULLPTR));
        action_2->setText(QApplication::translate("MainWindow", "\347\251\272\345\217\243\345\215\217\350\256\256\346\265\213\350\257\225", Q_NULLPTR));
        action_3->setText(QApplication::translate("MainWindow", "\350\207\252\345\271\262\346\211\260\346\212\221\345\210\266\345\210\235\345\247\213\345\214\226", Q_NULLPTR));
        action_4->setText(QApplication::translate("MainWindow", "\346\273\244\346\263\242\345\231\250\350\256\276\347\275\256", Q_NULLPTR));
        action_5->setText(QApplication::translate("MainWindow", "\346\240\207\347\255\276\347\233\230\347\202\271\346\250\241\345\274\217", Q_NULLPTR));
        action_11->setText(QApplication::translate("MainWindow", "RF\345\274\200\345\205\263", Q_NULLPTR));
        action_13->setText(QApplication::translate("MainWindow", "IP\350\256\276\347\275\256", Q_NULLPTR));
        action_6->setText(QApplication::translate("MainWindow", "\351\200\200\345\207\272", Q_NULLPTR));
        action_8->setText(QApplication::translate("MainWindow", "\351\200\200\345\207\272", Q_NULLPTR));
        action_9->setText(QApplication::translate("MainWindow", "\347\211\210\346\234\254/\345\205\263\344\272\216", Q_NULLPTR));
        action_10->setText(QApplication::translate("MainWindow", "\350\216\267\345\217\226\345\270\256\345\212\251", Q_NULLPTR));
        action_12->setText(QApplication::translate("MainWindow", "\350\260\203\345\210\266\346\267\261\345\272\246", Q_NULLPTR));
        action_7->setText(QApplication::translate("MainWindow", "\345\217\221\347\240\201\346\226\234\347\216\207", Q_NULLPTR));
        action_16->setText(QApplication::translate("MainWindow", "\344\277\235\345\257\206\346\250\241\345\235\227", Q_NULLPTR));
        action_18->setText(QApplication::translate("MainWindow", "\344\277\235\345\257\206\346\250\241\345\235\227", Q_NULLPTR));
        actionUDP->setText(QApplication::translate("MainWindow", "UDP\350\216\267\345\217\226\344\277\241\346\201\257", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
