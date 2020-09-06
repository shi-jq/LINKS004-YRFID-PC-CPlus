#ifndef VERSIONCOMMONDLG_H
#define VERSIONCOMMONDLG_H

#include <QDialog>

namespace Ui {
class VersionCommonDlg;
}
class QLabel;
class VersionCommonDlg : public QDialog
{
    Q_OBJECT
    
public:
    explicit VersionCommonDlg(QWidget *parent = 0);
    ~VersionCommonDlg();
public:
	void showEvent(QShowEvent *ev);
private:
    Ui::VersionCommonDlg *ui;
	QLabel* mSoftLabel;
	QLabel* mApiLabel;
	QLabel* mSoftCreateTimeLabel;
};

#endif // VERSIONCOMMONDLG_H
