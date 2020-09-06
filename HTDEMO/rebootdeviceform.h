#ifndef REBOOTDEVICEFORM_H
#define REBOOTDEVICEFORM_H

#include <QWidget>

namespace Ui {
class RebootDeviceForm;
}
class QPushButton;
class RebootDeviceForm : public QWidget
{
    Q_OBJECT
    
public:
    explicit RebootDeviceForm(QWidget *parent = 0);
    ~RebootDeviceForm();
    
private:
    Ui::RebootDeviceForm *ui;
	QPushButton* mRebootBtn;
private slots:
	void slot_rebootBtnClicked(); 
};

#endif // REBOOTDEVICEFORM_H
