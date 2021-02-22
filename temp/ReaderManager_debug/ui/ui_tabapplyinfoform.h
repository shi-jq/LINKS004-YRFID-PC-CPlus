/********************************************************************************
** Form generated from reading UI file 'tabapplyinfoform.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TABAPPLYINFOFORM_H
#define UI_TABAPPLYINFOFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TabApplyInfoForm
{
public:
    QGridLayout *gridLayout_3;
    QFrame *frame;
    QGridLayout *gridLayout_2;
    QWidget *widget_5;
    QVBoxLayout *verticalLayout_3;
    QWidget *widget_6;

    void setupUi(QWidget *TabApplyInfoForm)
    {
        if (TabApplyInfoForm->objectName().isEmpty())
            TabApplyInfoForm->setObjectName(QStringLiteral("TabApplyInfoForm"));
        TabApplyInfoForm->resize(400, 300);
        gridLayout_3 = new QGridLayout(TabApplyInfoForm);
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        frame = new QFrame(TabApplyInfoForm);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setStyleSheet(QLatin1String(".QFrame\n"
"{\n"
"	background-color: rgb(245, 245, 245);\n"
"}"));
        frame->setFrameShape(QFrame::NoFrame);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(frame);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        widget_5 = new QWidget(frame);
        widget_5->setObjectName(QStringLiteral("widget_5"));
        widget_5->setStyleSheet(QStringLiteral(""));
        verticalLayout_3 = new QVBoxLayout(widget_5);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setContentsMargins(1, 1, 1, 1);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        widget_6 = new QWidget(widget_5);
        widget_6->setObjectName(QStringLiteral("widget_6"));
        widget_6->setStyleSheet(QStringLiteral(""));

        verticalLayout_3->addWidget(widget_6);


        gridLayout_2->addWidget(widget_5, 0, 0, 2, 1);


        gridLayout_3->addWidget(frame, 0, 0, 1, 1);


        retranslateUi(TabApplyInfoForm);

        QMetaObject::connectSlotsByName(TabApplyInfoForm);
    } // setupUi

    void retranslateUi(QWidget *TabApplyInfoForm)
    {
        TabApplyInfoForm->setWindowTitle(QApplication::translate("TabApplyInfoForm", "Form", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class TabApplyInfoForm: public Ui_TabApplyInfoForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TABAPPLYINFOFORM_H
