/********************************************************************************
** Form generated from reading UI file 'wirelessdeviceinfodlg.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIRELESSDEVICEINFODLG_H
#define UI_WIRELESSDEVICEINFODLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTabWidget>

QT_BEGIN_NAMESPACE

class Ui_WirelessDeviceInfoDlg
{
public:
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;

    void setupUi(QDialog *WirelessDeviceInfoDlg)
    {
        if (WirelessDeviceInfoDlg->objectName().isEmpty())
            WirelessDeviceInfoDlg->setObjectName(QStringLiteral("WirelessDeviceInfoDlg"));
        WirelessDeviceInfoDlg->resize(484, 331);
        gridLayout = new QGridLayout(WirelessDeviceInfoDlg);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        tabWidget = new QTabWidget(WirelessDeviceInfoDlg);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));

        gridLayout->addWidget(tabWidget, 0, 0, 1, 1);


        retranslateUi(WirelessDeviceInfoDlg);

        tabWidget->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(WirelessDeviceInfoDlg);
    } // setupUi

    void retranslateUi(QDialog *WirelessDeviceInfoDlg)
    {
        WirelessDeviceInfoDlg->setWindowTitle(QApplication::translate("WirelessDeviceInfoDlg", "Dialog", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class WirelessDeviceInfoDlg: public Ui_WirelessDeviceInfoDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIRELESSDEVICEINFODLG_H
