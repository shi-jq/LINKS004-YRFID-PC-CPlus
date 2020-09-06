#ifndef BUSADDRCONFIGDLG_H
#define BUSADDRCONFIGDLG_H

#include <QWidget>

namespace Ui {
class BusAddrConfigDlg;
}
class QLineEdit;
class QPushButton;

class BusAddrConfigDlg : public QWidget
{
    Q_OBJECT
    
public:
    explicit BusAddrConfigDlg(QWidget *parent = 0);
    ~BusAddrConfigDlg();    
protected:
	void showEvent(QShowEvent *event);
private:
    Ui::BusAddrConfigDlg *ui;
	QLineEdit*  mBusEdit;
	QPushButton* mQueryBtn;
	QPushButton* mSetBtn;

	bool mFirst;

	bool Query();
private slots:
	void slot_QueryBtnClicked();
	void slot_SetBtnClicked();
};

#endif // BUSADDRCONFIGDLG_H
