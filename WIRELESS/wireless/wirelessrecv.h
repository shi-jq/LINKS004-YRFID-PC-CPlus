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
		WirelessReaderInfo*    pReaderInfo	//���յĶ�д������
		);
	void RecvreaderInfo(WirelessReaderInfo* pReaderInfo);//���ն�д��

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
	void ClearAllReadItem();//������еĶ�д��Item

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
	QPushButton* mStartBtn;//��ʼ
	QPushButton* mAdvancedBtn; //�������
	QPushButton* mClearBtn;//���
	QPushButton* mServerListenBtn;//��ʼ����
	QPushButton* mAddReaderBtn;//��Ӷ�д��
	//QPushButton* mServerConfigBtn;//����������

	QCheckBox* mSaveLogCkb;	//������־

	QCheckBox* mEnableAsysTimeCkb;
	QTreeWidget* mTagTree;
	TreeRightMenu* mRightMenu;

	bool mIsStart;
	bool mIsServerActive;

	WirelessDeviceInfoDlg* mWirelessDeviceInfoDlg;//�豸��ϸ
	WirelessAdvancedDlg* mWirelessAdvancedDlg; //�������
	WirelessTcpServerConfigDlg* mWirelessTcpServerConfigDlg;//����������

	QTimer *mRefreshTimer; //ˢ�¶�ʱ��
	QTimer *mCheckOnline;//����Ƿ���߶�ʱ��

	AddClientDlg* mAddClientDlg;
	
private slots:
	void slot_SetRevMsg(void* pReaderInfo,
		int msgID,
		unsigned char bCommand,
		void*  pData, 
		int nLen);
	void slot_RecvIOState(const QString& strState);
	void slot_SaveCardInfo(const QString& strCard);
	void slot_stop(); //ֹͣ
	void slot_start();//��ʼ
	void slot_Oper(); //��ť����
	void slot_Clear(); //���
	void slot_disconnet(); //�Ͽ�����

	void slot_advanceBtnClicked();//�������
	void slot_RecvreaderInfo(void* pReaderInfo); 
	void slot_ServerConfigBtnClicked();//����������

	void slot_ServerListenBtnStopClicked();//������ֹͣ����
	void slot_ServerListenBtnStartClicked();//��������ʼ����
	void slot_ServerListenBtnClicked();//������������ť
	void slot_AddReaderBtnClicked();//��Ӷ�д��
	
	void slot_refresh_time();//ˢ�½���
	void slot_checkOnline_time();//����Ƿ�����
	void slot_itemRightClicked(QTreeWidgetItem *item, int column);
	void slot_itemRemoveClicked();//�Ҽ��Ƴ���д��
	void slot_itemRebootClicked();//�Ҽ�������д��
	void slot_itemSaveClicked();//�Ҽ�����������¼
	void slot_EnableAsysTimeCkbChange(int ); //����ʱ��
	void slot_itemSyncTimeClicked();//ͬ��ʱ��
	void slot_itemQueryNameClicked();//��ѯ��д������
	void slot_itemDeviceConfig();//�豸����
};

/************************************************************************/
/* �Ҽ��˵�                                                                    */
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
