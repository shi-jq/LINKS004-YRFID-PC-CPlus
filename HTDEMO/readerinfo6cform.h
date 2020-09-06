#ifndef READERINFO6CFORM_H
#define READERINFO6CFORM_H

#include <QWidget>

namespace Ui {
class ReaderInfo6CForm;
}
class QLineEdit;
class QPushButton;

class ReaderInfo6CForm : public QWidget
{
    Q_OBJECT
    
public:
    explicit ReaderInfo6CForm(QWidget *parent = 0);
    ~ReaderInfo6CForm();
    
private:
    Ui::ReaderInfo6CForm *ui;


protected:
    void showEvent(QShowEvent *event);

private:
    QLineEdit* mProductNameEdit;
    QLineEdit* mProductSerialEdit;
    QLineEdit* mRWerTypeEdit;
    QLineEdit* mProcessSoftVerEdit;
    QLineEdit* mBaseHardVerEdit;
	QLineEdit* mSerialPwdEdit;

    QPushButton* mQureyBtn;
    QPushButton* mProductNameSetBtn;
    QPushButton* mRWerTypeSetBtn;
    QPushButton* mProductSerialSetBtn;

	bool mFirst;
private:
    bool QuerySysInfo(int index , QString& str);
	bool QueryAll();
private slots:
    void slot_QureyBtnClicked();
    void slot_ProductNameSetBtnClicked();
    void slot_RWerTypeSetBtnClicked();
    void slot_ProductSerialSetBtnClicked();


};

#endif // READERINFO6CFORM_H
