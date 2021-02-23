#ifndef FILTRATETAGFOR6CDLG_H
#define FILTRATETAGFOR6CDLG_H

#include <QWidget>

namespace Ui {
class FiltrateTagFor6CDlg;
}
class QCheckBox;
class QSpinBox;
class QPushButton;
class FiltrateTagFor6CDlg : public QWidget
{
    Q_OBJECT
    
public:
    explicit FiltrateTagFor6CDlg(QWidget *parent = 0);
    ~FiltrateTagFor6CDlg();
protected:
	void showEvent(QShowEvent *event);  
private:
    Ui::FiltrateTagFor6CDlg *ui;
	QCheckBox* mEnableCb;
	QSpinBox* mTimeEdit;
	QPushButton* mQueryBtn;
	QPushButton* mSetBtn;

	bool mFirst;
private: 
	void SetFiltrateEnable(bool isEnable);
	bool QueryEnable();
	bool QueryValue();
	bool QueryAll();
	bool SetAll();

	bool SetEnable();
	bool SetValue();

private slots:
	void slot_QueryBtnClicked();
	void slot_SetBtnClicked();
	
};

#endif // FILTRATETAGFOR6CDLG_H
