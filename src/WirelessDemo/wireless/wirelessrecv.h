#ifndef WIRELESSRECV_H
#define WIRELESSRECV_H
#include "WIRELESSRFIDAPIEXPORT.h"
#include <QWidget>
#include <wtypes.h>
#include <QTimer>
#include <QMenu>

namespace Ui {
class wirelessrecv;
}

class QPushButton;
class QTreeWidget;
class QTreeWidgetItem;
class CWirelessEpcCardInfo;
class TreeRightMenu;
class WirelessDeviceInfoDlg;
class WirelessAdvancedDlg;
class WirelessTcpServerConfigDlg;
class AddClientDlg;
class QCheckBox;
class WirelessRecvDlg : public QWidget
{
    Q_OBJECT    
public:
	enum WIRELESS_ITEM_TYPE
	{
		WIRELESS_ITEM_TYPE_IPADDR,
		WIRELESS_ITEM_TYPE_TAG
	};
	enum WIRELESS_ITEM_READ_TYPE
	{
		WIRELESS_ITEM_READ_TYPE_NORMAL,
		WIRELESS_ITEM_READ_TYPE_READING
	};

    explicit WirelessRecvDlg(QWidget *parent = 0);
    ~WirelessRecvDlg();

	bool static  PacketCallbackFunction(
		void*		pHandle,
		WirelessReaderInfo*    pReaderInfo	//接收的读写器对象
		);
	void RecvreaderInfo(WirelessReaderInfo* pReaderInfo);//接收读写器

	void RecvIOState(WirelessReaderInfo* pReaderInfo,QString& strState);
	void SaveCardInfo(const QString& cardStr);
	void SetRevMsg(WirelessReaderInfo*pWirelessReaderInfo,int msgID,unsigned char bCommand,unsigned char* pData, int nLen);
private:
	void updateLanguage();
	void CreateView();
	bool StartServer();
	bool StopServer();
	bool QuitServer();

	QTreeWidgetItem* GetReaderItem(WirelessReaderInfo* pReaderInfo);
	QTreeWidgetItem* FindReaderItem(WirelessReaderInfo* pReaderInfo);
	QTreeWidgetItem* CtreateReaderItem(WirelessReaderInfo* pReaderInfo);
	void UpdateItem(QTreeWidgetItem* tagItem,CWirelessEpcCardInfo* pCWirelessEpcCardInfo);
	void ClearAllReadItem();//清空所有的读写器Item

	int GetReaderItemIndex();
	QTreeWidgetItem* FindItemIndex(int nIndex);
	
	QTreeWidgetItem* GetTagItem(QTreeWidgetItem* ipItem,const QString& tagID);
	QTreeWidgetItem* FindTagItem(QTreeWidgetItem* ipItem,const QString& tagID);
	QTreeWidgetItem* CtreateTagItem(QTreeWidgetItem* ipItem,const QString& tagID);
	void ClearAllTagItem(QTreeWidgetItem* ipItem);

	void StartReadItem(QTreeWidgetItem* item);
	void StopReadItem(QTreeWidgetItem* item);
	void DeleteReadItem(QTreeWidgetItem* item);

	void refalshOnlineTime(QTreeWidgetItem* item);

	void UpdateCheckOnlineTimer();

	bool SaveDataToFile(const QString& fileStr);

	void SaveReaderState(WirelessReaderInfo*pReaderInfo ,bool bOnline);

	bool IsEnableAnalysisTime();

	bool QueryReaderName(WirelessReaderInfo* pReaderInfo);

	unsigned int C16Convert10(int a);
private:
    Ui::wirelessrecv *ui;
	QPushButton* mStartBtn;//开始
	QPushButton* mAdvancedBtn; //软件配置
	QPushButton* mClearBtn;//清空
	QPushButton* mServerListenBtn;//开始监听
	QPushButton* mAddReaderBtn;//添加读写器
	//QPushButton* mServerConfigBtn;//服务器配置

	QCheckBox* mSaveLogCkb;	//保存日志

	QCheckBox* mEnableAsysTimeCkb;
	QTreeWidget* mTagTree;
	TreeRightMenu* mRightMenu;

	bool mIsStart;
	bool mIsServerActive;

	WirelessDeviceInfoDlg* mWirelessDeviceInfoDlg;//设备详细
	WirelessAdvancedDlg* mWirelessAdvancedDlg; //软件设置
	WirelessTcpServerConfigDlg* mWirelessTcpServerConfigDlg;//服务器配置

	QTimer *mRefreshTimer; //刷新定时器
	QTimer *mCheckOnline;//检测是否断线定时器

	AddClientDlg* mAddClientDlg;
	
private slots:
	void slot_SetRevMsg(void* pReaderInfo,
		int msgID,
		unsigned char bCommand,
		void*  pData, 
		int nLen);
	void slot_RecvIOState(const QString& strState);
	void slot_SaveCardInfo(const QString& strCard);
	void slot_stop(); //停止
	void slot_start();//开始
	void slot_Oper(); //按钮操作
	void slot_Clear(); //清空
	void slot_disconnet(); //断开连接

	void slot_advanceBtnClicked();//软件配置
	void slot_RecvreaderInfo(void* pReaderInfo); 
	void slot_ServerConfigBtnClicked();//服务器配置

	void slot_ServerListenBtnStopClicked();//服务器停止监听
	void slot_ServerListenBtnStartClicked();//服务器开始监听
	void slot_ServerListenBtnClicked();//服务器监听按钮
	void slot_AddReaderBtnClicked();//添加读写器
	
	void slot_refresh_time();//刷新界面
	void slot_checkOnline_time();//检测是否在线
	void slot_itemRightClicked(QTreeWidgetItem *item, int column);
	void slot_itemRemoveClicked();//右键移除读写器
	void slot_itemRebootClicked();//右键重启读写器
	void slot_itemSaveClicked();//右键导出读卡记录
	void slot_EnableAsysTimeCkbChange(int ); //解析时间
	void slot_itemSyncTimeClicked();//同步时间
	void slot_itemQueryNameClicked();//查询读写器名称
	void slot_itemDeviceConfig();//设备配置
};

/************************************************************************/
/* 右键菜单                                                                    */
/************************************************************************/
class TreeRightMenu : public  QMenu
{
	Q_OBJECT
public:
	TreeRightMenu( QWidget *slotParent,QWidget *parent );
	~TreeRightMenu();
private:
	QAction *m_DeviceConfigAct;
	QAction *m_RemoveAct;
	QAction *m_RebootAct;
	QAction *m_SaveAct;
	QAction *m_SetTimeAct;
	QAction *m_QueryNameAct;
};


#endif // WIRELESSRECV_H
