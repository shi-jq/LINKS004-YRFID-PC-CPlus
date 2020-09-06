#ifndef WIFISELECTDLG_H
#define WIFISELECTDLG_H

#include <QDialog>

namespace Ui {
class WifiSelectDlg;
}
class QPushButton;
class QTreeWidget;
class QTreeWidgetItem;

class WifiSelectDlg : public QDialog
{
    Q_OBJECT
    
public:
    explicit WifiSelectDlg(QWidget *parent = 0);
    ~WifiSelectDlg();
    QString GetSelectSSID();
protected:
	void showEvent(QShowEvent *ev);
private:
    Ui::WifiSelectDlg *ui;
	QPushButton* mScanBtn;
	QPushButton* mSelectBtn;
	QTreeWidget* mTreeWidget;
	QString mCurSSID;

private slots:
	void slot_scanBtnClicked();
	void slot_selectBtnClicked();
	void slot_itemDoubleClicked(QTreeWidgetItem *item, int column);
};

#endif // WIFISELECTDLG_H
