#include "MessageBox.h"

#include <QtDebug>
#include <QApplication>
#include "LanguageSrc.h"
#include <QLabel>
#include <QPushButton>
#include <QResizeEvent>

HtMessageBox::HtMessageBox(const QString &text, int btnMode, HT_MSG_BOX_ICON icon, QWidget* parent)
    : QDialog(parent)
    , m_curReturnValue(RET_NONE)
    , m_btnMode(btnMode)
{
	this->setWindowTitle(GET_TXT("IDCS_WINTITLE2"));
	this->setMaximumSize(QSize(300,200));
	this->setMinimumSize(QSize(300,200));
    //初始化图标
    switch ( icon )
    {
    case ICON_WARNING:
        m_icon = new AdaptImage(":/message/skin/Warning.png", this);
        break;
    case ICON_ERROR:
        m_icon = new AdaptImage(":/message/skin/Error.png", this);
        break;
    case ICON_INFORMATION:
        m_icon = new AdaptImage(":/message/skin/Information.png", this);
        break;
    case ICON_QUESTION:
        m_icon = new AdaptImage(":/message/skin/Question.png", this);
        break;
    default:
        m_icon = new AdaptImage("", this);
        break;
    }

    //初始化文字及分割线
    m_text      = new QLabel(text, this);
    m_text->setAlignment( Qt::AlignTop | Qt::AlignLeft);
	m_text->setWordWrap(true);

    //初始化按钮
    m_btnList = new QButtonGroup(this);
    connect(m_btnList, SIGNAL(buttonClicked(int)), this, SLOT(slot_Finish(int)) );


    QPushButton* lastButton = 0;
    if ( 0 != (RET_ALL_YES & btnMode) ) {
        AddButton( RET_ALL_YES, GET_TXT("IDCS_ALL_YES") );
        lastButton =(QPushButton*)( m_btnList->button( RET_ALL_YES ) );
    }
	if ( 0 != (RET_ALL_NO & btnMode) ) {
		AddButton( RET_ALL_NO, GET_TXT("IDCS_ALL_NOT") );
		lastButton = (QPushButton*)( m_btnList->button( RET_ALL_NO ) );
	}
    if ( 0 != (RET_ENTER & btnMode) ) {
        AddButton( RET_ENTER, GET_TXT("IDCS_OK") );
        lastButton = (QPushButton*)( m_btnList->button( RET_ENTER ) );
    }
	if ( 0 != (RET_CANCEL & btnMode) ) {
		AddButton( RET_CANCEL, GET_TXT("IDCS_CANCEL") );
		lastButton = (QPushButton*)( m_btnList->button( RET_CANCEL ) );
	}
    if ( 0 != (RET_YES & btnMode) ) {
        AddButton( RET_YES, GET_TXT("IDCS_YES") );
        lastButton = (QPushButton*)( m_btnList->button( RET_YES ) );
    }
	if ( 0 != (RET_NO & btnMode) ) {
		AddButton( RET_NO, GET_TXT("IDCS_NO") );
		lastButton = (QPushButton*)( m_btnList->button( RET_NO ) );
	}

    //最右边的作为默认按钮
    if ( 0 != lastButton ) {
        lastButton->setDefault( true );
        m_curReturnValue = m_btnList->id( lastButton );
    }

    //全局设置
    QFont font = qApp->font();    
    setFont( font ); //默认值是13
    //根据文字调整大小,但是基类会有最少大小
    const QFontMetrics fm = fontMetrics();
    QSize sz = fm.size(Qt::TextShowMnemonic, text);
    resize(sz.width()+120, sz.height());
}

HtMessageBox::~HtMessageBox()
{
}

int HtMessageBox::message(const QString &text, int btnMode, HT_MSG_BOX_ICON icon, QWidget* parent )
{
    HtMessageBox box(text, btnMode, icon, parent);
    box.exec();

    return box.m_curReturnValue;
}

void HtMessageBox::Warning(const QString & text, QWidget* parent )
{
    HtMessageBox::message(text, RET_ENTER, ICON_WARNING, parent);
}

void HtMessageBox::Error(const QString & text, QWidget* parent)
{
    HtMessageBox::message(text, RET_ENTER, ICON_ERROR, parent);
}

void HtMessageBox::Information(const QString & text, QWidget* parent)
{
    HtMessageBox::message(text, RET_ENTER, ICON_INFORMATION, parent);
}

int HtMessageBox::Question(const QString & text, QWidget* parent)
{
    return HtMessageBox::message(text, RET_ENTER | RET_CANCEL, ICON_QUESTION, parent);
}

int HtMessageBox::Choice(const QString & text, QWidget* parent)
{
    return HtMessageBox::message(text, RET_YES | RET_NO, ICON_QUESTION, parent);
}


void HtMessageBox::slot_Finish(int btnValue)
{
    m_curReturnValue = btnValue;
    accept();
}

void HtMessageBox::resizeEvent(QResizeEvent *event)
{
    QDialog::resizeEvent(event);

    const int y = 60;
    const int w = event->size().width();
    const int h = event->size().height();

    m_icon->setGeometry(40+20, y, 48, 48 );
    m_text->setGeometry( 40+80, y+15, w-140, h-15*2-65 );

    QList<QAbstractButton*> listBtn = m_btnList->buttons();
  
	int AllWidth = 0;
	for (int i=0; i<listBtn.size(); ++i)
	{
		AllWidth += listBtn[i]->width();
		AllWidth += 10;
	}

	int curX = (w -AllWidth)/2;
    for ( int i = 0; i<listBtn.size(); ++i ) {

		listBtn[i]->move(curX,h-50);
		curX += listBtn[i]->width();  
		curX += 10;		
    }
}

void HtMessageBox::keyPressEvent( QKeyEvent *ev )
{
    bool ok = false;
#ifdef Q_OS_MAC
    if(ev->modifiers() == Qt::ControlModifier && ev->key() == Qt::Key_Period)
    {
        ok = true;
    }else
#endif
        if (!ev->modifiers() && ev->key() == Qt::Key_Escape  )//不是单纯的esc键就退出
        {
            ok = true;
        }

    if ( ok )
    {
        if ( 0 != (RET_ALL_NO & m_btnMode) )
        {
            m_curReturnValue = RET_ALL_NO;
        }
        if ( 0 != (RET_NO & m_btnMode) )
        {
            m_curReturnValue = RET_NO;
        }
        if ( 0 != (RET_CANCEL & m_btnMode) )
        {
            m_curReturnValue = RET_CANCEL;
        }
    }
    QDialog::keyPressEvent( ev );
}

void HtMessageBox::AddButton(HT_MSG_BOX_RETURN retValue, QString text)
{
    QPushButton* btn = new QPushButton( text, this );

	//全局设置
	QFont font = qApp->font();   
	const QFontMetrics fm = fontMetrics();
	QSize sz = fm.size(Qt::TextShowMnemonic, text);
	btn->setFixedWidth(sz.width()+45);

    m_btnList->addButton(btn, retValue);
}


/***********************************************************************************************************/
AdaptImage::AdaptImage( const QString &fileName, QWidget *parent )
: QFrame( parent )
{
	setStyleSheet( QString( "AdaptImage { background: transparent; image:url(%1); }" ).arg( fileName ) );
}

AdaptImage::~AdaptImage()
{
}

void AdaptImage::setAdaptImage( const QString &fileName )
{
	setStyleSheet( QString( "AdaptImage { background: transparent; image:url(%1); }" ).arg( fileName ) );
}
