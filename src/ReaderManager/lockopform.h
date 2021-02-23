#ifndef LOCKOPFORM_H
#define LOCKOPFORM_H

#include <QWidget>

namespace Ui {
class LockOpForm;
}
class QComboBox;
class QLineEdit;
class QPushButton;
class LockOpForm : public QWidget
{
    Q_OBJECT
    
public:
    explicit LockOpForm(QWidget *parent = 0);
    ~LockOpForm();
	void SetTagID(const QString& tagStr); 
private:
    Ui::LockOpForm *ui;
	QComboBox* mIdTypeCb;
	QLineEdit* mTagEdit;
	QLineEdit* mConfigPwdEdit;
	QComboBox* mOpTypCb;
	QLineEdit* mStartAddrEdit;
	QLineEdit* mLenEdit;
	QPushButton*  mSetBtn;
private slots:
	void slot_SetBtnClicked();
};

#endif // LOCKOPFORM_H
