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
#include <QtWidgets/QGroupBox>
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
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_5;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QLineEdit *pathtEdit;
    QPushButton *choseButton;
    QLabel *pathtext;
    QProgressBar *progressBar;
    QPushButton *startButton;
    QWidget *installtypewdg;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_5;
    QRadioButton *setupButton;
    QRadioButton *uploadButton;
    QSpacerItem *horizontalSpacer_4;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_3;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *uninstallBtn;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_4;
    QCheckBox *bootCkb;
    QPushButton *setbootBtn;
    QSpacerItem *horizontalSpacer_8;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *rebootBtn;
    QPushButton *checkButton;
    QPushButton *cancelButton;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer;
    QSpacerItem *verticalSpacer_2;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(404, 324);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_5 = new QGridLayout(centralWidget);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        pathtEdit = new QLineEdit(groupBox);
        pathtEdit->setObjectName(QStringLiteral("pathtEdit"));

        gridLayout->addWidget(pathtEdit, 0, 1, 1, 1);

        choseButton = new QPushButton(groupBox);
        choseButton->setObjectName(QStringLiteral("choseButton"));

        gridLayout->addWidget(choseButton, 0, 2, 1, 1);

        pathtext = new QLabel(groupBox);
        pathtext->setObjectName(QStringLiteral("pathtext"));

        gridLayout->addWidget(pathtext, 0, 0, 1, 1);

        progressBar = new QProgressBar(groupBox);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setValue(24);

        gridLayout->addWidget(progressBar, 2, 1, 1, 2);

        startButton = new QPushButton(groupBox);
        startButton->setObjectName(QStringLiteral("startButton"));

        gridLayout->addWidget(startButton, 0, 3, 1, 1);


        gridLayout_2->addLayout(gridLayout, 1, 0, 1, 1);

        installtypewdg = new QWidget(groupBox);
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


        gridLayout_5->addWidget(groupBox, 2, 0, 1, 2);

        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        gridLayout_3 = new QGridLayout(groupBox_2);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        horizontalSpacer_6 = new QSpacerItem(282, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_6, 0, 0, 1, 1);

        uninstallBtn = new QPushButton(groupBox_2);
        uninstallBtn->setObjectName(QStringLiteral("uninstallBtn"));

        gridLayout_3->addWidget(uninstallBtn, 0, 1, 1, 1);


        gridLayout_5->addWidget(groupBox_2, 3, 0, 1, 2);

        groupBox_3 = new QGroupBox(centralWidget);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        gridLayout_4 = new QGridLayout(groupBox_3);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        bootCkb = new QCheckBox(groupBox_3);
        bootCkb->setObjectName(QStringLiteral("bootCkb"));
        bootCkb->setChecked(true);

        gridLayout_4->addWidget(bootCkb, 0, 1, 1, 1);

        setbootBtn = new QPushButton(groupBox_3);
        setbootBtn->setObjectName(QStringLiteral("setbootBtn"));

        gridLayout_4->addWidget(setbootBtn, 0, 2, 1, 1);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_8, 0, 0, 1, 1);


        gridLayout_5->addWidget(groupBox_3, 4, 0, 1, 2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));

        gridLayout_5->addLayout(horizontalLayout_2, 0, 0, 1, 2);

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


        gridLayout_5->addLayout(horizontalLayout, 6, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_5->addItem(verticalSpacer, 1, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_5->addItem(verticalSpacer_2, 5, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "adb_tool", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("MainWindow", "\345\215\207\347\272\247", Q_NULLPTR));
        choseButton->setText(QApplication::translate("MainWindow", "\346\265\217\350\247\210", Q_NULLPTR));
        pathtext->setText(QApplication::translate("MainWindow", "\346\226\207\344\273\266\350\267\257\345\276\204", Q_NULLPTR));
        startButton->setText(QApplication::translate("MainWindow", "\345\215\207\347\272\247", Q_NULLPTR));
        setupButton->setText(QApplication::translate("MainWindow", "\345\256\211\350\243\205\347\250\213\345\272\217", Q_NULLPTR));
        uploadButton->setText(QApplication::translate("MainWindow", "\344\270\212\344\274\240\346\226\207\344\273\266", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "\345\215\270\350\275\275", Q_NULLPTR));
        uninstallBtn->setText(QApplication::translate("MainWindow", "\345\215\270\350\275\275", Q_NULLPTR));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "\345\274\200\346\234\272\350\207\252\345\220\257", Q_NULLPTR));
        bootCkb->setText(QApplication::translate("MainWindow", "\345\274\200\346\234\272\350\207\252\345\220\257", Q_NULLPTR));
        setbootBtn->setText(QApplication::translate("MainWindow", "\350\256\276\347\275\256", Q_NULLPTR));
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
