#ifndef PWDSETFORM_H
#define PWDSETFORM_H

#include <QWidget>

namespace Ui {
class PwdSetForm;
}
class QComboBox;
class QLineEdit;
class QRadioButton;
class QPushButton;
class PwdSetForm : public QWidget
{
    Q_OBJECT
    
public:
    explicit PwdSetForm(QWidget *parent = 0);
    ~PwdSetForm();
	void SetTagID(const QString& tagStr);
private:
    Ui::PwdSetForm *ui;
	QComboBox* mIdTypeCb;
	QLineEdit* mTagIdEdit;
	QRadioButton* mAccessPwdRbt;
	QRadioButton* mConfigPwdRbt;
	QLineEdit* mOldPwdEdit;
	QLineEdit* mNewPwdEdit;
	QPushButton* mSetBtn;
private slots:
	void slot_setBtnClicked();
};

#endif // PWDSETFORM_H
