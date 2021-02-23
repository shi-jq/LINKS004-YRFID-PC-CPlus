#pragma once
#include <QThread>
#include "udpclient.h"

class UdpWorkerThread : public QThread
{
	Q_OBJECT
		void run();
public:
	bool StartUdp();
signals:
	void resultReady(const QString &ipStr,const QString& nameStr);
private:
	UdpClient mUdpclient;
	QString GetBroadcastStr();
	
};