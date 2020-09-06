#ifndef READERTIMESETDLG_H
#define READERTIMESETDLG_H

#include <QWidget>

namespace Ui {
class ReaderTimeSetDlg;
}
class QTimeEdit;
class QDateEdit;
class QPushButton;
class ReaderTimeSetDlg : public QWidget
{
    Q_OBJECT
    
public:
    explicit ReaderTimeSetDlg(QWidget *parent = 0);
    ~ReaderTimeSetDlg();
protected:
	void showEvent(QShowEvent *event);
private:
    Ui::ReaderTimeSetDlg *ui;
	QTimeEdit* mTimeEdit;
	QDateEdit* mDateEidt;
	QPushButton* mQueryBtn;
	QPushButton* mSetBtn;
	QPushButton* mGetCurtimeBtn;

	bool mFirst;
private:
	unsigned int C16Convert10(int a);
	unsigned int C10Convert16(int a);
	bool QueryTime();
private slots:
	void slot_QueryBtnClicked();
	void slot_SetBtnClicked();
	void slot_GetCurtimeBtnClicked();
};

#endif // READERTIMESETDLG_H
