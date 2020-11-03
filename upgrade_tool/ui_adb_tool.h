/********************************************************************************
** Form generated from reading UI file 'adb_tool.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADB_TOOL_H
#define UI_ADB_TOOL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_4;
    QSpacerItem *verticalSpacer;
    QTabWidget *tabWidget;
    QWidget *tab_2;
    QGridLayout *gridLayout_2;
    QWidget *installtypewdg;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_5;
    QRadioButton *setupButton;
    QRadioButton *uploadButton;
    QSpacerItem *horizontalSpacer_4;
    QGridLayout *gridLayout;
    QLineEdit *pathtEdit;
    QLabel *pathtext;
    QProgressBar *progressBar;
    QPushButton *choseButton;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *startButton;
    QPushButton *uninstallBtn;
    QWidget *tab;
    QGridLayout *gridLayout_3;
    QSpacerItem *horizontalSpacer_8;
    QLabel *label;
    QCheckBox *bootCkb;
    QLineEdit *lineEdit;
    QPushButton *setbootBtn;
    QSpacerItem *verticalSpacer_4;
    QSpacerItem *verticalSpacer_3;
    QSpacerItem *horizontalSpacer_6;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *rebootBtn;
    QPushButton *checkButton;
    QPushButton *cancelButton;
    QSpacerItem *horizontalSpacer_2;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(429, 253);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_4 = new QGridLayout(centralWidget);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_4->addItem(verticalSpacer, 0, 1, 1, 1);

        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        gridLayout_2 = new QGridLayout(tab_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        installtypewdg = new QWidget(tab_2);
        installtypewdg->setObjectName(QStringLiteral("installtypewdg"));
        horizontalLayout_3 = new QHBoxLayout(installtypewdg);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_5);

        setupButton = new QRadioButton(installtypewdg);
        setupButton->setObjectName(QStringLiteral("setupButton"));

        horizontalLayout_3->addWidget(setupButton);

        uploadButton = new QRadioButton(installtypewdg);
        uploadButton->setObjectName(QStringLiteral("uploadButton"));

        horizontalLayout_3->addWidget(uploadButton);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);


        gridLayout_2->addWidget(installtypewdg, 0, 0, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        pathtEdit = new QLineEdit(tab_2);
        pathtEdit->setObjectName(QStringLiteral("pathtEdit"));

        gridLayout->addWidget(pathtEdit, 0, 1, 1, 1);

        pathtext = new QLabel(tab_2);
        pathtext->setObjectName(QStringLiteral("pathtext"));

        gridLayout->addWidget(pathtext, 0, 0, 1, 1);

        progressBar = new QProgressBar(tab_2);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setValue(24);

        gridLayout->addWidget(progressBar, 2, 1, 1, 2);

        choseButton = new QPushButton(tab_2);
        choseButton->setObjectName(QStringLiteral("choseButton"));

        gridLayout->addWidget(choseButton, 0, 2, 1, 1);


        gridLayout_2->addLayout(gridLayout, 1, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);

        startButton = new QPushButton(tab_2);
        startButton->setObjectName(QStringLiteral("startButton"));

        horizontalLayout_4->addWidget(startButton);

        uninstallBtn = new QPushButton(tab_2);
        uninstallBtn->setObjectName(QStringLiteral("uninstallBtn"));

        horizontalLayout_4->addWidget(uninstallBtn);


        gridLayout_2->addLayout(horizontalLayout_4, 2, 0, 1, 1);

        tabWidget->addTab(tab_2, QString());
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        gridLayout_3 = new QGridLayout(tab);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_8, 2, 1, 1, 1);

        label = new QLabel(tab);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_3->addWidget(label, 2, 2, 1, 1);

        bootCkb = new QCheckBox(tab);
        bootCkb->setObjectName(QStringLiteral("bootCkb"));
        bootCkb->setChecked(true);

        gridLayout_3->addWidget(bootCkb, 1, 3, 1, 1);

        lineEdit = new QLineEdit(tab);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        gridLayout_3->addWidget(lineEdit, 2, 3, 1, 1);

        setbootBtn = new QPushButton(tab);
        setbootBtn->setObjectName(QStringLiteral("setbootBtn"));

        gridLayout_3->addWidget(setbootBtn, 2, 4, 1, 1);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer_4, 0, 2, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer_3, 3, 3, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_6, 2, 5, 1, 1);

        tabWidget->addTab(tab, QString());

        gridLayout_4->addWidget(tabWidget, 1, 0, 1, 2);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_4->addItem(verticalSpacer_2, 2, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        rebootBtn = new QPushButton(centralWidget);
        rebootBtn->setObjectName(QStringLiteral("rebootBtn"));

        horizontalLayout->addWidget(rebootBtn);

        checkButton = new QPushButton(centralWidget);
        checkButton->setObjectName(QStringLiteral("checkButton"));

        horizontalLayout->addWidget(checkButton);

        cancelButton = new QPushButton(centralWidget);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));

        horizontalLayout->addWidget(cancelButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        gridLayout_4->addLayout(horizontalLayout, 3, 0, 1, 2);

        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "adb_tool", Q_NULLPTR));
        setupButton->setText(QApplication::translate("MainWindow", "\345\256\211\350\243\205\347\250\213\345\272\217", Q_NULLPTR));
        uploadButton->setText(QApplication::translate("MainWindow", "\344\270\212\344\274\240\346\226\207\344\273\266", Q_NULLPTR));
        pathtext->setText(QApplication::translate("MainWindow", "\346\226\207\344\273\266\350\267\257\345\276\204", Q_NULLPTR));
        choseButton->setText(QApplication::translate("MainWindow", "\346\265\217\350\247\210", Q_NULLPTR));
        startButton->setText(QApplication::translate("MainWindow", "\345\256\211\350\243\205", Q_NULLPTR));
        uninstallBtn->setText(QApplication::translate("MainWindow", "\345\215\270\350\275\275", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "\345\256\211\350\243\205\345\215\270\350\275\275", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "\345\257\206\347\240\201:", Q_NULLPTR));
        bootCkb->setText(QApplication::translate("MainWindow", "\345\274\200\346\234\272\350\207\252\345\220\257", Q_NULLPTR));
        lineEdit->setText(QString());
        setbootBtn->setText(QApplication::translate("MainWindow", "\350\256\276\347\275\256", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", " \345\274\200\346\234\272\350\207\252\345\220\257", Q_NULLPTR));
        rebootBtn->setText(QApplication::translate("MainWindow", "\351\207\215\345\220\257", Q_NULLPTR));
        checkButton->setText(QApplication::translate("MainWindow", "\346\243\200\346\265\213\350\243\205\347\275\256", Q_NULLPTR));
        cancelButton->setText(QApplication::translate("MainWindow", "\345\205\263\351\227\255", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADB_TOOL_H
