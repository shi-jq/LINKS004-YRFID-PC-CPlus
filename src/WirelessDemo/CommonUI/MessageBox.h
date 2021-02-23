/*******************************************************************************
* Create Data: 2012.05.07
* Description: 可公用的消息提示对话框
*******************************************************************************/
/*
 * update:
 * @1 2013.06.29 new messagebox
 *
 */
#ifndef _NVMS_1200_QT_MESSAGE_BOX_H_
#define _NVMS_1200_QT_MESSAGE_BOX_H_
#pragma once

#include <QFrame>
#include <QList>
#include <QString>
#include <QButtonGroup>
#include "QDialog"

class QFrame;
class QWidget;
class QLabel;
class AdaptImage;
class QPushButton;

/*******************************************************************************
* 公用消息提示对话框基类
*******************************************************************************/
class HtMessageBox : public QDialog
{
    Q_OBJECT

public:
    /* 可选图标,只允许一个图标 */
    enum HT_MSG_BOX_ICON
    {
        ICON_NONE = 0,
        ICON_WARNING,
        ICON_ERROR,
        ICON_INFORMATION,
        ICON_QUESTION
    };
    /* 可选按钮，可选择多个按钮（按钮顺序由内部决定）甚至自定义按钮（按钮顺序根据用户定义的列表决定） */
    enum HT_MSG_BOX_RETURN
    {
        RET_NONE    = 0,
        //////////
        RET_YES     = 0x00000001,
        RET_NO      = 0x00000002,
        RET_ALL_YES = 0x00000004,
        RET_ALL_NO  = 0x00000008,
        ///////////
        RET_ENTER   = 0x00000010,
        RET_CANCEL  = 0x00000020,
        ///////////
        RET_CUSTTOM = 0x80000000
    };

private:
    HtMessageBox(const QString & text, int btnMode = RET_ENTER, HT_MSG_BOX_ICON icon = ICON_WARNING, QWidget* parent = 0);
    virtual ~HtMessageBox();

public:
    //////////////////////////////////////////////////////
    /////////全部消息函数的返回值均为HT_MSG_BOX_RETURN的值
    //////////////////////////////////////////////////////

    /* 自定义消息提示 －－ 可选图标 －－可选按钮（btnMode为HT_MSG_BOX_RETURN的值，也是点击某个后的返回值，按钮顺序内部决定）*/
    static int message(const QString & text, int btnMode = RET_ENTER, HT_MSG_BOX_ICON icon = ICON_WARNING, QWidget* parent = 0 );

    /* 单按钮提示 －－确定 */
    static void Warning(const QString & text, QWidget* parent = 0);
    static void Error(const QString & text, QWidget* parent = 0);
    static void Information(const QString & text, QWidget* parent = 0);

    /* 询问 －－ 确认--BTN_ENTER  /  取消--BTN_CANCEL*/
    static int Question(const QString & text, QWidget* parent = 0);

    /* 选择 －－  是--BTN_YES  /  否--BTN_NO */
    static int Choice(const QString & text, QWidget* parent = 0);

private slots:
    void slot_Finish(int btnValue);

protected:
    virtual void resizeEvent(QResizeEvent *event);
    virtual void keyPressEvent(QKeyEvent * event);

private:
    void AddButton(HT_MSG_BOX_RETURN retValue, QString text);
protected:
    AdaptImage*     m_icon;
    QLabel*         m_text;
    QWidget*        m_line;

    QButtonGroup*   m_btnList;
    /*返回值（点击某个按钮之后的值）*/
    int m_curReturnValue;
    ///
    int m_btnMode;
};

/*****************************************************************************/
/* 带一个图片居中显示的窗口												     */
/* 主要用于显示一个图标														 */
/*****************************************************************************/
class AdaptImage : public QFrame
{
	Q_OBJECT
public:
	AdaptImage( const QString &fileName, QWidget *parent = 0 );
	virtual ~AdaptImage();

	void setAdaptImage( const QString &fileName );
};

#endif //       MESSAGE_BOX_H_
