#ifndef FLASHCONFIGFOR6CDLG_H
#define FLASHCONFIGFOR6CDLG_H

#include <QWidget>
#include <QThread>
#include "Lock.h"

namespace Ui {
class FlashConfigFor6CDlg;
}
class QCheckBox;
class QLineEdit;
class QPushButton;
class QTreeWidget;
class FlashThread;
class FlashConfigFor6CDlg : public QWidget
{
    Q_OBJECT    
public:
    explicit FlashConfigFor6CDlg(QWidget *parent = 0);
    ~FlashConfigFor6CDlg();

protected:
	void showEvent(QShowEvent *event);

private:
    Ui::FlashConfigFor6CDlg *ui;
	QCheckBox* mFlashEnableCb;
	QLineEdit* mAllTagNumEdit;
	QPushButton* mQueryBtn;
	QPushButton* mClearBtn;
	
	bool mFirst;
private:
	void setFlashEnable(bool isEnable);
	bool QueryFlashEnable();
	bool QueryTagNum();
	bool QueryAll();
private slots:
	void slot_QueryBtnClicked();
	void slot_ClearBtnClicked();
	void slot_EnableStateChanged(int state);
};

#endif // FLASHCONFIGFOR6CDLG_H
