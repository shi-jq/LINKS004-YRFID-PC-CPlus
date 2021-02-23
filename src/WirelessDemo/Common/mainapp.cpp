#include "mainapp.h"
#include <QDateTime>
#include "mainwindow.h"

MainApp::MainApp()
{
	pMainWindow = NULL;
}


bool MainApp::Initial()
{
	//mEventHeartThread = new EventHeartThread();
	return true;
}

void MainApp::Quit()
{
}



void MainApp::ShowMsg(QString str,bool getErro)
{
	if (pMainWindow)
	{
		pMainWindow->ShowMsg(str,getErro);
	}

}

void MainApp::UpdateReaderState(int nConnetType)
{
	if (pMainWindow)
	{
		pMainWindow->updateReaderState(nConnetType);
	}
	
}

QString MainApp::GetStrFromChar(unsigned char* buff, int len)
{
	QString retStr;
	for (int i=0; i< len ; i++)
	{		
		retStr += QString("%1").arg(buff[i],2,16,QLatin1Char('0')).toUpper();
	}

	return retStr;
}

int MainApp::CheckTimeout(unsigned int start, unsigned int hasElapsed)
{
	unsigned int now;
	unsigned int deadline = start + hasElapsed;
	int rc = 0;

	now = GetSysTickCount();

	if (deadline < start)
	{
		// adding the deadline time made a wrap-
		// deadline is past IF: 
		//      (deadline <= now < start)
		if ((now >= deadline) && (now < start))
			rc = 1;
	}
	else if (now >= deadline)
	{
		rc = 1;
	}
	else if (now < start)
		rc = 1;

	return rc;
}

unsigned int MainApp::GetSysTickCount()
{
	return GetTickCount();
}

int MainApp::getBitBuffFromStr(const QString& str,unsigned char* buff,int bitlen)
{
	QString tmp;
	bool isOK;
	int index = 0; 
	for(index=0; index<bitlen/8; ++index)
	{
		tmp = str.mid(index*2,2);
		*(buff++) = tmp.toUInt(&isOK,16);
	}	

	int lastindex = bitlen%8;
	if (lastindex != 0)
	{
		tmp = str.mid(index*2,2);
		unsigned char tmpbyte = tmp.toUInt(&isOK,16);
		*(buff++) = tmpbyte & (0xff << (8-lastindex));
		index++;
	}	

	return index;
}


