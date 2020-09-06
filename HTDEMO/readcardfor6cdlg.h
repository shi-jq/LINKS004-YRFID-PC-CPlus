#ifndef READCARDFOR6CDLG_H
#define READCARDFOR6CDLG_H

#include <QWidget>
#include <QTime>
#include <map>

namespace Ui {
class ReadCardFor6CDlg;
}
class QComboBox;
class QCheckBox;
class QSpinBox;
class QPushButton;
class QLabel;
class QTreeWidget;
class QTimer;
class ReadCardFor6CThread;
class QTreeWidgetItem;
class QSound;
class workDpaceDlg;
class ReaderDllBase;
class TagOpDialog;

class ReadCardFor6CDlg : public QWidget
{
    Q_OBJECT
    
public:
    explicit ReadCardFor6CDlg(QWidget *parent,workDpaceDlg* pWorkSpaceDlg);
    ~ReadCardFor6CDlg();
	void CreateView();
	void UpdateLanguage();
	//void keyPress(QKeyEvent *ev);

private:
    Ui::ReadCardFor6CDlg *ui;
	QPushButton* mTagOpBtn;//��ǩ����
	TagOpDialog*  mTagOpDialog;

	QCheckBox* mRecordCheckBox;//��Ϣ��¼
	QSpinBox* mRecordSb;//��Ϣ��¼ʱ��

	QPushButton* mMakeTagUpLoadBtn;//��������ǩ����
	QPushButton* mYTagReadBtn;//��������ǩ����
	QPushButton* mStopReadBtn; //ֹͣ����
	QPushButton* mClearBtn;//���
	QPushButton* mAddFilterBtn;//��ӹ���
	QPushButton* mClearFilterBtn;//��չ���

	QLabel* mAllCountLable;//�����ܴ���
	QTreeWidget* mTagTree;//��ǩ�� 	

	QTimer *mRefreshTimer; //ˢ�¶�ʱ��
	QTimer *mSaveTimer; //�����ļ���ʱ��
	QSound* mBeepSound;

	unsigned int mReadCount; //��������
	bool haveNewCard;		//�Ƿ����¿�
	QTime mFreshTime;		//ˢ�¼�ʱ

	bool mIsReading;
	workDpaceDlg* mWorkSpaceDlg;
	std::map<QString,ReadCardFor6CThread*> mThreadMap;
	
	QStringList mFilterMap;
private:
	bool SendReadCommand(const QString& strInfo,int nReadType);
	bool SendStopCommand(const QString& strInfo);
	QTreeWidgetItem* GetTagItem(const QString&strInfo, const QString& cardStr);
	QTreeWidgetItem* FindTagItem(const QString&strInfo,const QString& cardStr);
	QTreeWidgetItem* GetReaderItem(const QString&strInfo);
	
	QTreeWidgetItem* CreateTagItem(const QString&strInfo,const QString& cardStr);
	bool SaveDataToFile(const QString& fileStr);
	
	void UpdateReaderThreadMap();
	ReadCardFor6CThread* FindThread(const QString& strInfo);
	void CreateThread(ReaderDllBase* pReaderDllBase,const QString& strInfo);
	void ClearAllThread();

	bool StartRead(int nReadType);
	bool StopRead();
	bool ClearCard();

	void startReadBtnClicked(int nReadType);
private slots:
	void slot_refresh_time(); //ˢ���б�
	void slot_makeTagUpLoadBtnClicked();//��������
	void slot_yTagReadBtnClicked();//��������
	void slot_TagOpBtnClicked();//��ǩ����
	
	void slot_stopReadBtnClicked();
	void slot_ClearBtnClicked();
	void slot_AddFilterBtnClicked();
	void slot_ClearFilterBtnClicked();
	void slot_beep();
	void slot_save_file();

	void slot_itemRightClicked(QTreeWidgetItem* item, int column);
	void slot_exportItem();

signals:
	void sig_sendReadCount(int count,int nReadCount,int nReset);
};

#endif // READCARDFOR6CDLG_H
