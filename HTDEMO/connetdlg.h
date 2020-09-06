#ifndef CONNETDLG_H
#define CONNETDLG_H

#include <QWidget>
#include <QPushButton>
#include <QRadioButton>
#include <QComboBox>
#include <QLineEdit>
#include <QLabel>
#include <QTimer>
#include "UdpWorkerThread.h"

namespace Ui {
class ConnetDlg;
}
class QWidget;
class QStackedWidget;
class QLineEdit;
class QTreeWidget;
class ReaderDllBase;
class QTreeWidgetItem;

class ConnetDlg : public QWidget
{
    Q_OBJECT
    
public:
    explicit ConnetDlg(QWidget *parent = 0);
	void UpdateReaderState(int nConnetType);
    ~ConnetDlg();
 
public slots:
	void slot_UpdateReadCount(int count,int speed,int nReset);
	void slot_cutCurConnect();
	
private:
    Ui::ConnetDlg *ui;

	QWidget*	mLinkWidget; //连接方式的框,用来控制用户是否能使用的
	QStackedWidget* mConnetStackedWidget;//tcp,com usb udp


	QComboBox* mIpAddrCb;	//tcp ip地址
	QLineEdit* mTcpPortEdit;//tcp端口
	QComboBox* mComCb;		//串口
	QComboBox* mBaudRateCb; //波特率

	QComboBox* mUdpIpAddrCb;	//udp ip地址
	QLineEdit* mUdpPortEdit;//udp端口
	QComboBox* mUsbCb;		//usb串口
	QComboBox* mUsbBaudRateCb; //usb波特率

	QPushButton* mConnetBtn;//添加连接按钮
	QPushButton* mClearBtn;//清空按钮
	QPushButton* mQueryIPBtn;//udp查询ip
	QPushButton* mRebootBtn;//重启设备
	QPushButton* mCutDownBtn;//断开按钮
	QPushButton* mConnectItemBtn;//连接项按钮

	QComboBox* mConnetTypeCb;//连接方式

	QLabel* mCardCountLabel;//标签总张数
	QLabel* mCardReadSpeedLabel;//标签速率

	int mSpeed;
	int mRefeshTime;
	QList<int> mCardCoundList;
	UdpWorkerThread* mUdpWorkerThread;

	QTreeWidget* mDeviceList;

	bool CheckIPEdit(const QString& str);//检查ip地址是否合法

	void CreateView();//创建视图
	void UpdateLanguage();//更新语言
	void StartUDP();	//启用udp查询
	bool isEnableEdit(int nConnetType);//判断是否能编辑页面

	QTreeWidgetItem* AddConnectUdp();
	QTreeWidgetItem* AddConnectTcp();
	QTreeWidgetItem* AddConnectCom();
	QTreeWidgetItem* AddConnectUsb();

	bool SavaIni();

	QTreeWidgetItem*  CreateItem(const QString& strInfo,ReaderDllBase* pReaderDllBase);
	int  GetReaderItemIndex();
	QTreeWidgetItem* FindIndexItem(int nIndex);
	void UpdateItemState(QTreeWidgetItem *item, ReaderDllBase* pReaderDllBase);
	void SetCurItem(QTreeWidgetItem *item);
	void ClearAllItem();
	bool ConnectItem(QTreeWidgetItem *item);
	bool DisConnectItem(QTreeWidgetItem *item);
	bool RebootItem(QTreeWidgetItem *item);
private slots:
	void slot_RebootBtnClicked();//重启设备
	void slot_connetBtnClicked();//添加连接
	void slot_ClearBtnClicked();//清空连接
	void slot_CutDownBtnClicked();//断开连接
	void slot_connetItemBtnClicked();//连接
	
	void slot_quitBtnClicked();//退出程序
	void slot_queryIpBtnClicked();//udp查询
	void slot_GetUdpResult(const QString& ipStr, const QString& nameStr);//接收udp结果
	void slot_ConnetTypeIndexChanged(int index);//连接类型
	void slot_itemRightClicked(QTreeWidgetItem *,int);
	void slot_itemDoubleClicked(QTreeWidgetItem *,int);
	void slot_connectItem();
	void slot_disconnectItem();
	void slot_deleteItem();
	void slot_setCurItem();

};

#endif // CONNETDLG_H
