#ifndef PARAMADD6CDLG_H
#define PARAMADD6CDLG_H

#include <QWidget>

namespace Ui {
class ParamAdd6CDlg;
}
class QPushButton;
class QLineEdit;

class ParamAdd6CDlg : public QWidget
{
    Q_OBJECT
    
public:
    explicit ParamAdd6CDlg(QWidget *parent = 0);
    ~ParamAdd6CDlg();
    
private:
    Ui::ParamAdd6CDlg *ui;
	QPushButton* mReadParamBtn;
	QPushButton* mWriteParamBtn;
	QPushButton* mResetBtn;
	QLineEdit* mStartAddrEdit;
	QLineEdit* mLenEdit;
	QLineEdit* mDataEdit;


private slots:
	void slot_ReadParamBtnClicked();
	void slot_WriteParamBtnClicked();
	void slot_ResetBtnClicked();
};

#endif // PARAMADD6CDLG_H
