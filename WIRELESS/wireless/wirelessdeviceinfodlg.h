#ifndef WIRELESSDEVICEINFODLG_H
#define WIRELESSDEVICEINFODLG_H

#include <QDialog>
#include "WIRELESSRFIDAPIEXPORT.h"

namespace Ui {
class WirelessDeviceInfoDlg;
}
class QTabWidget;
class WirelessSysinfoWidget;
class WirelessReadParamWidget;
class WirelessReadConfigWidget;
class WirelessIOCtrlWidget;
class WirelessDeviceInfoDlg : public QDialog
{
    Q_OBJECT
    
public:
    explicit WirelessDeviceInfoDlg(QWidget *parent = 0);
    ~WirelessDeviceInfoDlg();
	void SetWirelessReaderInfo(WirelessReaderInfo* pReaderInfo);
	WirelessReaderInfo* GetReaderInfo();
	void SetRevMsg(WirelessReaderInfo* pReaderInfo,int msgID,unsigned char bCommand,unsigned char* pData, int nLen);
private:
    Ui::WirelessDeviceInfoDlg *ui;
	QTabWidget* mtabWidget;
	WirelessSysinfoWidget* mWirelessSysinfoWidget;
	WirelessReadParamWidget* mWirelessReadParamWidget;
	WirelessReadConfigWidget* mWirelessReadConfigWidget;
	WirelessIOCtrlWidget* mWirelessIOCtrlWidget;
	WirelessReaderInfo* mReaderInfo;
};

#endif // WIRELESSDEVICEINFODLG_H
