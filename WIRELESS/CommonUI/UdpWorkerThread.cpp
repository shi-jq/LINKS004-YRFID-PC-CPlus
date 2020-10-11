#include "UdpWorkerThread.h"
#include <string.h>
#include <QtNetwork/QNetworkInterface>
#include <QtNetwork/QNetworkAddressEntry>
#include "CheckTime.h"
#include "mainapp.h"
#include "LanguageSrc.h"
#include "widgetconfig.h"

void UdpWorkerThread::run()
{
	QString result;

	unsigned long mBroadcast;
	mBroadcast = inet_addr(GetBroadcastStr().toUtf8().data());
	bool retb =mUdpclient.OpenConn(
		WIDGETSTRING_GET("ConnetDlg","UDP_PORT").toInt(),
		mBroadcast);
	if (!retb)
	{
		CSingleton<MainApp>::GetInstance()->ShowMsg(GET_TXT("IDCS_UDP_GET_FAILED_TG"));
		return;
	}

	unsigned char SendDataBuff[24]={ 0x01 ,0xFE ,0x00 ,0x18, 0x34, 0x12, 
		0x00, 0x00, 0x00, 0x01,	0x03 ,0xE8 ,0x00 ,0x0E ,0x00 ,0x00 ,
		0x00 ,0x01 ,0x00 ,0x7B ,0x00 ,0x00 ,0x00 ,0x00};
	unsigned char sendLen = 24;

	mUdpclient.Send(SendDataBuff,sendLen);

	unsigned char recvDataBuff[255];
	unsigned char nBuffLen= 255;
	bool retB = false;

	unsigned long startTime = CheckTime::GetSysTickCount();
	while(!CheckTime::CheckTimeout(startTime,3000))
	{
		int nRet = mUdpclient.RevMsg(recvDataBuff,&nBuffLen);
		if (nRet >= 33)
		{
			if (recvDataBuff[10] == 0x03 && recvDataBuff[11] == 0xe8 )
			{
				QString tmp = QString("%1.%2.%3.%4")
					.arg(recvDataBuff[20])
					.arg(recvDataBuff[21])
					.arg(recvDataBuff[22])
					.arg(recvDataBuff[23]);

				QString ipStr = tmp;

				tmp = QString("%1.%2.%3.%4")
					.arg(recvDataBuff[24])
					.arg(recvDataBuff[25])
					.arg(recvDataBuff[26])
					.arg(recvDataBuff[27]);
				tmp = QString("%1.%2.%3.%4")
					.arg(recvDataBuff[28])
					.arg(recvDataBuff[29])
					.arg(recvDataBuff[30])
					.arg(recvDataBuff[31]);

				tmp.clear();
				unsigned int sysinfoLen=  recvDataBuff[32];
				for (int i=0; i<sysinfoLen; ++i)
				{
					tmp.append(recvDataBuff[33+i]);
				}

				QString nameStr = tmp;					

				emit resultReady(ipStr,nameStr);

				tmp.clear();
				unsigned int otherLen=  recvDataBuff[sysinfoLen+33];
				for (int i=0; i<otherLen; ++i)
				{
					tmp.append(recvDataBuff[sysinfoLen+34+i]);
				}
				if (otherLen != 0)
				{
					//mOtherEdit->setText(tmp);
				}
				retB = true;
			}

		}
	}

	if (retB)
	{
		MainShowMsg(GET_TXT("IDCS_UDP_GET_SUCCESS"));
	}
	else
	{
		MainShowMsg(GET_TXT("IDCS_UDP_GET_FAILED"));
	}

	mUdpclient.CloseConn();

}

QString UdpWorkerThread::GetBroadcastStr()
{
	QString tmpRet ;
	QString ipStr;
	QString maskStr;
	bool isGet = false;
	QList<QNetworkInterface> nets =QNetworkInterface::allInterfaces();
	for (int i=0; i<nets.size(); ++i)
	{
		QNetworkInterface item = nets.at(i);
		QList<QNetworkAddressEntry> entryList = item.addressEntries();
		for(int j=0; j<entryList.size(); ++j)
		{
			tmpRet = entryList.at(j).broadcast().toString();		
			if (!tmpRet.isEmpty())
			{
				isGet = true;
				break;
			}
		}
		if (isGet)
		{
			break;
		}
	}

	return tmpRet;
}

bool UdpWorkerThread::StartUdp()
{
	if (this->isRunning())
	{
		MainShowMsg(GET_TXT("IDCS_UDP_DOING"));
		return false;
	}

	this->start();
	return true;
}
