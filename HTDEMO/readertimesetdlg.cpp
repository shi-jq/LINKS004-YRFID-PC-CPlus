#include "readertimesetdlg.h"
#include "ui_readertimesetdlg.h"
#include "LanguageSrc.h"
#include "appconfig.h"
#include "mainapp.h"
#include "RFIDAPIEXPORT.h"
#include "readerdllbase.h"


ReaderTimeSetDlg::ReaderTimeSetDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReaderTimeSetDlg)
{
    ui->setupUi(this);
	this->setWindowTitle(GET_TXT("IDCS_TIME_CONFIG"));
	
	mTimeEdit = ui->timeEdit;
	mDateEidt = ui->dateEdit;
	mQueryBtn = ui->pushButton;
	mSetBtn = ui->pushButton_2;
	mGetCurtimeBtn=ui->pushButton_3;

	mFirst = true;


	ui->label->setText(GET_TXT("IDCS_DATE"));
	ui->label_2->setText(GET_TXT("IDCS_TIME"));
	ui->pushButton_3->setText(GET_TXT("IDCS_SYNCH_TIME"));
	mQueryBtn->setText(GET_TXT("IDCS_QUERY"));
	mSetBtn->setText(GET_TXT("IDCS_SET"));	

	connect( mQueryBtn, SIGNAL( clicked()), this, SLOT( slot_QueryBtnClicked( ) ) );
	connect( mSetBtn, SIGNAL( clicked()), this, SLOT( slot_SetBtnClicked( ) ) );
	connect( mGetCurtimeBtn, SIGNAL( clicked()), this, SLOT( slot_GetCurtimeBtnClicked( ) ) );

}

ReaderTimeSetDlg::~ReaderTimeSetDlg()
{
    delete ui;
}

void ReaderTimeSetDlg::showEvent(QShowEvent *event)
{
	ReaderDllBase*	pReaderDllBase = pMainApp->GetReader();	
	if (!pReaderDllBase)
	{
		return;
	}

	if (pReaderDllBase->GetState() == STATE_READING ||
		pReaderDllBase->GetState() == STATE_DISCONNET ||
		pReaderDllBase->GetState() == STATE_DISABLE)
	{
		return;
	}
	if (mFirst)
	{
        //mFirst = !QueryTime();
	}
	QWidget::showEvent(event);
}

void ReaderTimeSetDlg::slot_QueryBtnClicked()
{
	QueryTime();
}

void ReaderTimeSetDlg::slot_SetBtnClicked()
{
	ReaderDllBase*	pReaderDllBase = pMainApp->GetReader();	
	if (!pReaderDllBase)
	{
		MainShowMsg(GET_TXT("IDCS_READ_NO_LINK"));
		return;
	}
	if (!pReaderDllBase->CheckState(STATE_CONNET))
	{
		MainShowMsg(GET_TXT("IDCS_READ_NO_LINK"));
		return ;
	}

	unsigned char btPara[7] ;
	ZeroMemory(btPara,7);

	QDate tmpDate = mDateEidt->date();
	QTime tmpTime = mTimeEdit->time();

	btPara[0] = C16Convert10(tmpTime.second());
	btPara[1] = C16Convert10(tmpTime.minute());
	btPara[2] = C16Convert10(tmpTime.hour());
	btPara[3] = C16Convert10(tmpDate.dayOfWeek());
	btPara[4] = C16Convert10(tmpDate.day());
	btPara[5] = C16Convert10(tmpDate.month());
	int nYear = C16Convert10(tmpDate.year() %100);		
	btPara[6] = nYear;

	bool bRet = SAAT_SetReaderTime(
		pReaderDllBase->m_hCom,
		btPara,7);

	if (bRet)
	{
		MainShowMsg(GET_TXT("IDCS_SET_TIME_CONFIG_SUCCESS"));
	}
	else
	{
		MainShowMsg(GET_TXT("IDCS_SET_TIME_CONFIG_FAILED"),true);
	}
}

unsigned int ReaderTimeSetDlg::C16Convert10(int a)
{
	bool bok;
	return QString("%1").arg( a).toUInt(&bok,16);
}

unsigned int ReaderTimeSetDlg::C10Convert16(int a)
{
	return QString("%1").arg( a,2,16,QLatin1Char('0')).toUInt();	
}

void ReaderTimeSetDlg::slot_GetCurtimeBtnClicked()
{
	QDateTime curTimeDate = QDateTime::currentDateTime();
	mDateEidt->setDateTime(curTimeDate);
	mTimeEdit->setDateTime(curTimeDate);
	
	slot_SetBtnClicked();
}

bool ReaderTimeSetDlg::QueryTime()
{
	ReaderDllBase*	pReaderDllBase = pMainApp->GetReader();	
	if (!pReaderDllBase)
	{
		MainShowMsg(GET_TXT("IDCS_READ_NO_LINK"));
		return false;
	}
	if (!pReaderDllBase->CheckState(STATE_CONNET))
	{
		MainShowMsg(GET_TXT("IDCS_READ_NO_LINK"));
		return false;
	}

	unsigned char btPara[200] ;
	ZeroMemory(btPara,200);
	unsigned char nLen = 200;

	bool retB = SAAT_ReaderTimeQuery(
		pReaderDllBase->m_hCom,
		btPara,
		&nLen);

	if (retB)
	{

		int nSec =C10Convert16( btPara[0]);
		int nMin = C10Convert16(btPara[1]); 
		int nHour = C10Convert16(btPara[2]);
		int nDayWeek = C10Convert16(btPara[3]);
		int nDay = C10Convert16(btPara[4]);
		int nMonth = C10Convert16(btPara[5]);
		int nYear = C10Convert16(btPara[6])+2000;
		if (nYear >= 2070)
		{
			nYear -= 100;
		}

		if ( (0==nDay) || (0==nMonth) )
		{
			MainShowMsg(GET_TXT("IDCS_QUERY_TIME_CONFIG_FAILED"));
			return false;
		}

		mDateEidt->setDate(QDate(nYear,nMonth,nDay));
		mTimeEdit->setTime(QTime(nHour,nMin,nSec));
		MainShowMsg(GET_TXT("IDCS_QUERY_TIME_CONFIG_SUCCESS"));
	}
	else
	{
		MainShowMsg(GET_TXT("IDCS_QUERY_TIME_CONFIG_FAILED"),true);
	}

	return retB;
}
