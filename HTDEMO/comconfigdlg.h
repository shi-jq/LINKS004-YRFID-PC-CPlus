#ifndef COMCONFIGDLG_H
#define COMCONFIGDLG_H

#include <QWidget>

namespace Ui {
class ComConfigDlg;
}

class QComboBox;
class QPushButton;

class ComConfigDlg : public QWidget
{
    Q_OBJECT
    
public:
    explicit ComConfigDlg(QWidget *parent = 0);
    ~ComConfigDlg();
protected:
	void showEvent(QShowEvent *event);
private:
    Ui::ComConfigDlg *ui;
	QComboBox* mBaudRateCb;
	QPushButton* mQueryBtn;
	QPushButton* mSetBtn;
	bool mFirst;
private:
	bool Query();
private slots:
	void slot_QueryBtnClicked();
	void slot_SetBtnClicked();
};

#endif // COMCONFIGDLG_H
