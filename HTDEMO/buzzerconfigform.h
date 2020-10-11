#ifndef BUZZERCONFIGFORM_H
#define BUZZERCONFIGFORM_H

#include <QWidget>

namespace Ui {
class BuzzerConfigForm;
}
class QComboBox;
class QPushButton;
class BuzzerConfigForm : public QWidget
{
    Q_OBJECT

public:
    explicit BuzzerConfigForm(QWidget *parent = 0);
    ~BuzzerConfigForm();
protected:
	void showEvent(QShowEvent *event);
private slots:
	void slot_QueryBtnClicked();
	void slot_SetBtnClicked();
private:
	bool EnableQuery();
	bool EnableSet();
private:
    Ui::BuzzerConfigForm *ui;
	QComboBox* m_enableCb;
	QPushButton* mQueryBtn;
	QPushButton* mSetBtn;
};

#endif // BUZZERCONFIGFORM_H
