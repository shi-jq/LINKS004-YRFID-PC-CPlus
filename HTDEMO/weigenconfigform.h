#ifndef WEIGENCONFIGFORM_H
#define WEIGENCONFIGFORM_H

#include <QWidget>

namespace Ui {
class WeiGenConfigForm;
}
class QLineEdit;
class QComboBox;
class QPushButton;
class WeiGenConfigForm : public QWidget
{
    Q_OBJECT
    
public:
    explicit WeiGenConfigForm(QWidget *parent = 0);
    ~WeiGenConfigForm();
protected:
	void showEvent(QShowEvent *event);
private:
    Ui::WeiGenConfigForm *ui;
	QLineEdit* m_WegenStartValueEdit;
	QComboBox* m_WegenLenValueCb;
	QPushButton* mQueryBtn;
	QPushButton* mSetBtn;

	bool  mFirst;

	bool WegenStartQuery();
	bool WegenLenQuery();
	bool WegenStartSet();
	bool WegenLenSet();

	bool QueryAll();
	bool SetAll();

private slots:
	void slot_QueryBtnClicked();
	void slot_SetBtnClicked();
};

#endif // WEIGENCONFIGFORM_H
