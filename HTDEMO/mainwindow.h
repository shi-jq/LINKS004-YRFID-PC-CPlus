#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QSplitter;
class ConnetDlg;
class workDpaceDlg;
class OpListDlg;
class QCloseEvent;
class FirmWareUpdateFor6CDlg;
class R2000LogDlg;
class ComConfigDlg;
class BusAddrConfigDlg;
class NetConfigFor6CDlg;
class ReaderTimeSetDlg;
class FlashConfigFor6CDlg;
class FiltrateTagFor6CDlg;
class QValueDlg;
class IoConfigFor6CDlg;
class CarrierWaveFor6CDlg;
class ParamConfigFor6CDlg;
class WIFIConfigFor6CDLg;
class GprsConfigDlg;
class SoftConfigDlg;

class VersionCommonDlg;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT    
public:
     explicit MainWindow( QWidget *parent = 0);
	 bool isNeedReboot();
	 void SetNeedReboot(bool isneed);
    ~MainWindow();
	void ShowMsg(QString msg,bool getErro,bool getReader);//��ʾ������¼
	void updateReaderState(int nConnetType);//��д��״̬����,ˢ�½���
	void CutConnet();//�Ͽ�����

protected:
	void closeEvent(QCloseEvent *event);//�˳������¼�
	void keyPressEvent(QKeyEvent *ev);//�����¼�
private:
    Ui::MainWindow *ui;

	bool mIsNeetReboot;//�Ƿ���Ҫ����

	ConnetDlg* mConnetDlg;//����
	workDpaceDlg* mworkDpaceDlg;//������
	OpListDlg* mOpListDlg;//����ҳ��

	QAction* mVersionCommonAc;//����汾
	//�˵���	
	QAction* mExitAc;

	//6c���ֵĲ˵���Action
	QAction* mReaderInfoFor6CAc;
	QAction* mFirmWareUpdateFor6CAc;
	QAction* mR2000LogAc;
	QAction* mNetConfigFor6CAc;
	QAction* mComConfigAc;
	QAction* mBusAddrConfigAc;
	QAction* mReaderTimeSetAc;
	QAction* mFiltrateTagFor6CAc;
	QAction* mFlashConfigFor6CAc;
	QAction* mQVlaueAc;
	QAction* mIoConfigFor6CAc;
	QAction* mCarrierWaveFor6CAc;
	QAction* mParamConfigFor6CAc;
	QAction* mWIFIConfigFor6CAC;
	QAction* mGprsConfigFor6CAc;
	QAction* mRebootDeviceFor6CAc;

	QAction* mSoftCongfigAc;


	VersionCommonDlg* mVersionCommonDlg;
	

	//6c���ֵĵ�������		
	CarrierWaveFor6CDlg* mCarrierWaveFor6CDlg;
	ParamConfigFor6CDlg* mParamConfigFor6CDlg;
	GprsConfigDlg* mGprsConfigDlg;


	SoftConfigDlg* mSoftConfigDlg;
private:
	void CreateMenuBar();//���ɲ˵���
	void CreateFileMenu();//�ļ�
	
	void CreateHelpMenu();//����


	void CreateView();//������ͼ

	bool checkConnet();//�������״̬
	
private slots:
	void slot_leftBtnClicked();
	void slot_downBtnClicked();
	void slot_CutConnet();
	//�˵���
	void slot_ExitAc();
	void slot_updateReaderState(int nConnetType);
	void slot_HelpAc();

	void slot_WIFIConfigFor6CAc();

	void slot_SoftConfigAc();


	void slot_VersionCommonAc();

	void slot_UpdateReadCount(int count,int speed, int nReset);//ˢ�¶�������,�ܴ����ͼ�ʱ����
	
};

#endif // MAINWINDOW_H
