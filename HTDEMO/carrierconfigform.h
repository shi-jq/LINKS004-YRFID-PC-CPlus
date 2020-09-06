#ifndef CARRIERCONFIGFORM_H
#define CARRIERCONFIGFORM_H

#include <QWidget>

namespace Ui {
class CarrierConfigForm;
}
class QComboBox;
class QPushButton;
class CarrierConfigForm : public QWidget
{
    Q_OBJECT
    
public:
    explicit CarrierConfigForm(QWidget *parent = 0);
    ~CarrierConfigForm();
    bool QueryAll();
private:
    Ui::CarrierConfigForm *ui;
	QComboBox*  mCarrierCb;
	QPushButton* mQueryBtn;
	QPushButton* mSetBtn;
private slots:
	void slot_QurBtnClicked();
	void slot_SetBtnClicked();
};

#endif // CARRIERCONFIGFORM_H
