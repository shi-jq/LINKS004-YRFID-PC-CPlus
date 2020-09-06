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

	QWidget*	mLinkWidget; //���ӷ�ʽ�Ŀ�,���������û��Ƿ���ʹ�õ�
	QStackedWidget* mConnetStackedWidget;//tcp,com usb udp


	QComboBox* mIpAddrCb;	//tcp ip��ַ
	QLineEdit* mTcpPortEdit;//tcp�˿�
	QComboBox* mComCb;		//����
	QComboBox* mBaudRateCb; //������

	QComboBox* mUdpIpAddrCb;	//udp ip��ַ
	QLineEdit* mUdpPortEdit;//udp�˿�
	QComboBox* mUsbCb;		//usb����
	QComboBox* mUsbBaudRateCb; //usb������

	QPushButton* mConnetBtn;//������Ӱ�ť
	QPushButton* mClearBtn;//��հ�ť
	QPushButton* mQueryIPBtn;//udp��ѯip
	QPushButton* mRebootBtn;//�����豸
	QPushButton* mCutDownBtn;//�Ͽ���ť
	QPushButton* mConnectItemBtn;//�����ť

	QComboBox* mConnetTypeCb;//���ӷ�ʽ

	QLabel* mCardCountLabel;//��ǩ������
	QLabel* mCardReadSpeedLabel;//��ǩ����

	int mSpeed;
	int mRefeshTime;
	QList<int> mCardCoundList;
	UdpWorkerThread* mUdpWorkerThread;

	QTreeWidget* mDeviceList;

	bool CheckIPEdit(const QString& str);//���ip��ַ�Ƿ�Ϸ�

	void CreateView();//������ͼ
	void UpdateLanguage();//��������
	void StartUDP();	//����udp��ѯ
	bool isEnableEdit(int nConnetType);//�ж��Ƿ��ܱ༭ҳ��

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
	void slot_RebootBtnClicked();//�����豸
	void slot_connetBtnClicked();//�������
	void slot_ClearBtnClicked();//�������
	void slot_CutDownBtnClicked();//�Ͽ�����
	void slot_connetItemBtnClicked();//����
	
	void slot_quitBtnClicked();//�˳�����
	void slot_queryIpBtnClicked();//udp��ѯ
	void slot_GetUdpResult(const QString& ipStr, const QString& nameStr);//����udp���
	void slot_ConnetTypeIndexChanged(int index);//��������
	void slot_itemRightClicked(QTreeWidgetItem *,int);
	void slot_itemDoubleClicked(QTreeWidgetItem *,int);
	void slot_connectItem();
	void slot_disconnectItem();
	void slot_deleteItem();
	void slot_setCurItem();

};

#endif // CONNETDLG_H
