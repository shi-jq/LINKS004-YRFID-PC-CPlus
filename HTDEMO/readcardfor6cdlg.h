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
	QPushButton* mTagOpBtn;//标签操作
	TagOpDialog*  mTagOpDialog;

	QCheckBox* mRecordCheckBox;//消息记录
	QSpinBox* mRecordSb;//消息记录时间

	QPushButton* mMakeTagUpLoadBtn;//读主动标签读卡
	QPushButton* mYTagReadBtn;//读被动标签读卡
	QPushButton* mStopReadBtn; //停止读卡
	QPushButton* mClearBtn;//清空
	QPushButton* mAddFilterBtn;//添加过滤
	QPushButton* mClearFilterBtn;//清空过滤

	QLabel* mAllCountLable;//读卡总次数
	QTreeWidget* mTagTree;//标签表 	

	QTimer *mRefreshTimer; //刷新定时器
	QTimer *mSaveTimer; //保存文件定时器
	QSound* mBeepSound;

	unsigned int mReadCount; //读卡次数
	bool haveNewCard;		//是否有新卡
	QTime mFreshTime;		//刷新计时

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
	void slot_refresh_time(); //刷新列表
	void slot_makeTagUpLoadBtnClicked();//主动读卡
	void slot_yTagReadBtnClicked();//被动读卡
	void slot_TagOpBtnClicked();//标签操作
	
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
