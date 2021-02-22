#ifndef READWRITEDATAFORM_H
#define READWRITEDATAFORM_H

#include <QWidget>

namespace Ui {
class ReadWriteDataForm;
}
class QComboBox;
class QLineEdit;
class QRadioButton;
class QTextEdit;
class QPushButton;
class QLabel;
class ReadWriteDataForm : public QWidget
{
    Q_OBJECT
    
public:
    explicit ReadWriteDataForm(QWidget *parent = 0);
    ~ReadWriteDataForm();
     void SetTagID(const QString& tagStr);
private:
    Ui::ReadWriteDataForm *ui;
	QComboBox* mIdTypeCb;
	QLineEdit* mTagEdit;
	QLineEdit* mPwdEdit;
	QComboBox* mBankCb;
	QLineEdit* mStartAddrEdit;
	QLineEdit* mLenEdit;
	QTextEdit* mResultEdit;

	QPushButton* mReadBtn;
	QPushButton* mWriteBtn;
	QPushButton* mClearBtn;

	QLineEdit* mWaitTimeEdit;
	QLabel* mUseTimeLabel;
private slots:
	void slot_ReadBtnClicked();
	void slot_WriteBtnClicked();
	void slot_ClearBtnClicked();
};

#endif // READWRITEDATAFORM_H
