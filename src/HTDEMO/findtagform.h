#ifndef FINDTAGFORM_H
#define FINDTAGFORM_H

#include <QWidget>

namespace Ui {
class FindTagForm;
}
class QPushButton;
class QLineEdit;
class QCheckBox;
class FindTagForm : public QWidget
{
    Q_OBJECT
    
public:
    explicit FindTagForm(QWidget *parent = 0);
    ~FindTagForm();
    void SetTagID(const QString& tagStr);
private:
    Ui::FindTagForm *ui;
	QPushButton* mFindBtn;
	QPushButton* mStopFindBtn;
	QLineEdit* mTagEdit;
	QCheckBox* mLedCkb;
	QCheckBox* mBeepCkb;
private slots:
	void slot_FindBtnClicked();
	void slot_StopBtnClicked();
};

#endif // FINDTAGFORM_H
