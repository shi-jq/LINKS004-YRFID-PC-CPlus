#ifndef TAGFILTERFORM_H
#define TAGFILTERFORM_H

#include <QWidget>

namespace Ui {
class TagFilterForm;
}
class QLineEdit;
class QPushButton;
class TagFilterForm : public QWidget
{
    Q_OBJECT
    
public:
    explicit TagFilterForm(QWidget *parent = 0);
    ~TagFilterForm();
     void SetTagID(const QString& tagStr);
private:
    Ui::TagFilterForm *ui;
	QLineEdit* mTagEdit;
	QPushButton* mFilterBtn;
	QPushButton* mClearFilterBtn;
private slots:
	void slot_filterBtnClicked();
	void slot_ClearFilterBtnClicked();

};

#endif // TAGFILTERFORM_H
