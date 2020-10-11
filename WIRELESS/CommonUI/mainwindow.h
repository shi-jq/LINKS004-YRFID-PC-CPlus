#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QSplitter;
class ConnetDlg;
class workDpaceDlg;
class OpListDlg;
class QCloseEvent;
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
	void ShowMsg(QString msg,bool getErro);//��ʾ������¼
	void updateReaderState(int nConnetType);//��д��״̬����,ˢ�½���
	void CutConnet();//�Ͽ�����

protected:
	void closeEvent(QCloseEvent *event);//�˳������¼�
	void keyPressEvent(QKeyEvent *ev);//�����¼�
private:
    Ui::MainWindow *ui;

	bool mIsNeetReboot;//�Ƿ���Ҫ����

	workDpaceDlg* mworkDpaceDlg;//������
	OpListDlg* mOpListDlg;//����ҳ��

	QAction* mVersionCommonAc;//����汾
	//�˵���	
	QAction* mSoftCongfigAc;
	QAction* mExitAc;

	SoftConfigDlg* mSoftConfigDlg;
	VersionCommonDlg* mVersionCommonDlg;
private:
	void CreateMenuBar();//���ɲ˵���
	void CreateFileMenu();//�ļ�
	void CreateHelpMenu();

	void CreateWirelessMenu();//805s���߽������ò˵�

	void CreateView();//������ͼ
	

	
private slots:
	void slot_leftBtnClicked();
	void slot_downBtnClicked();
	void slot_VersionCommonAc();
	//�˵���
	void slot_SoftConfigAc();
	void slot_ExitAc();
	void slot_updateReaderState(int nConnetType);
	void slot_HelpAc();
	void slot_CutConnet();
};

#endif // MAINWINDOW_H
