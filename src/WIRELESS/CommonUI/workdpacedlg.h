#ifndef WORKDPACEDLG_H
#define WORKDPACEDLG_H

#include <QWidget>
#include <QFrame>
#include <QTabWidget>
#include "wirelessrecv.h"

class ReaderDllBase;

namespace Ui {
class workDpaceDlg;
}

class workDpaceDlg : public QFrame
{
    Q_OBJECT
    
public:
    explicit workDpaceDlg(QWidget *parent = 0);
    ~workDpaceDlg();


    void UpdateReaderState(int nConnetType);
	
	void setDownBtnUp(bool isDown);
	void setLeftBtnRight(bool left);


private:
    Ui::workDpaceDlg *ui;
	QTabWidget* mTabWidget;
	WirelessRecvDlg* mWirelessRecvDlg;

	QPushButton* mDownBtn;
	QPushButton* mLeftBtn;

	void CreateView();
	
signals:
	void leftBtnClicked();
	void downBtnClicked();

private slots:
	void slot_leftBtnClicked();
	void slot_downBtnClicked();
	void slot_tabChanged(int index);
};

#endif // WORKDPACEDLG_H
