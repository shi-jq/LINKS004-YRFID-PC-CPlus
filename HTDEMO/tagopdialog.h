#ifndef TAGOPDIALOG_H
#define TAGOPDIALOG_H

#include <QDialog>

namespace Ui {
class TagOpDialog;
}
class QListWidgetItem;
class QListWidget;
class QStackedWidget;
class FindTagForm;
class LockOpForm;
class PwdSetForm;
class ReadWriteDataForm;
class WriteEidForm;
class TagOpDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit TagOpDialog(QWidget *parent = 0);
    ~TagOpDialog();
    void SetTagStr(const QString& tagStr);
private:
    Ui::TagOpDialog *ui;
	QListWidget* mListWidget;
	QStackedWidget* mStackedWidget;

	FindTagForm* mFindTagForm;
	LockOpForm* mLockOpForm;
	PwdSetForm* mPwdSetForm;
	ReadWriteDataForm* mReadWriteDataForm;
	WriteEidForm* mWriteEidForm;
private slots:
	void slot_ListItemClicked(QListWidgetItem* item);
};

#endif // TAGOPDIALOG_H
