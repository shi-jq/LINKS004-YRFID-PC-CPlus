#ifndef WRITEEIDFORM_H
#define WRITEEIDFORM_H

#include <QWidget>

namespace Ui {
class WriteEidForm;
}
class QLineEdit;
class QPushButton;
class WriteEidForm : public QWidget
{
    Q_OBJECT
    
public:
    explicit WriteEidForm(QWidget *parent = 0);
    ~WriteEidForm();
     void SetTagID(const QString& tagStr);
private:
    Ui::WriteEidForm *ui;
	QLineEdit*  mOldEidEdit;
	QLineEdit*  mWirteEidEdit;
	QLineEdit*  mPwdEdit;
	QPushButton* mSetBtn;
private slots:
	void slot_SetBtnClicked();
};

#endif // WRITEEIDFORM_H
