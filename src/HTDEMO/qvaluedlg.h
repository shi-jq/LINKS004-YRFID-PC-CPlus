#ifndef QVALUEDLG_H
#define QVALUEDLG_H

#include <QWidget>

namespace Ui {
class QValueDlg;
}
class QPushButton;
class QSpinBox;
class QValueDlg : public QWidget
{
    Q_OBJECT
    
public:
    explicit QValueDlg(QWidget *parent = 0);
    ~QValueDlg();
protected:
	void showEvent(QShowEvent *event);    
private:
    Ui::QValueDlg *ui;
	QPushButton* mQueryBtn;
	QPushButton* mSetBtn;
	QSpinBox* mValueEdit;

	bool mIsFirst;
private slots:
	void slot_QueryBtnClicked();
	void slot_SetBtnClicked();
private:
	bool Query();

};

#endif // QVALUEDLG_H
