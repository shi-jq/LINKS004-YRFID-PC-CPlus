#ifndef OPLISTDLG_H
#define OPLISTDLG_H

#include <QWidget>
#include <QTreeWidget>

class QPushButton;

namespace Ui {
class OpListDlg;
}

class OpListDlg : public QWidget
{
    Q_OBJECT
    
public:
    explicit OpListDlg(QWidget *parent = 0);
    ~OpListDlg();
    
	void ShowMsg(QString msg,bool getErro,bool getReader);
private:
    Ui::OpListDlg *ui;
	QTreeWidget* mOpListWidget;
	QPushButton* mClearBtn;

	int itemCount;
	int MaxOpRecord;
	int ToDeleteRecord;

private slots:
	void slot_showMsg(QString,bool getErro,bool getReader);
	void slot_clearBtnClicked();
	

	

};

#endif // OPLISTDLG_H
