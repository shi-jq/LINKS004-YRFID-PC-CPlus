#ifndef READCONFIGFOR6CDLG_H
#define READCONFIGFOR6CDLG_H

#include <QWidget>

namespace Ui {
class ReadConfigFor6CDlg;
}

class QLabel;
class QPushButton;
class QCheckBox;
class QComboBox;
class QListWidget;
class QTextEdit;
class QSpinBox;
class AntennaPrmForm;
class CarrierConfigForm;
class PointConfigForm;
class BuzzerConfigForm;
class ReadConfigFor6CDlg : public QWidget
{
    Q_OBJECT
    
public:
    explicit ReadConfigFor6CDlg(QWidget *parent = 0);
    ~ReadConfigFor6CDlg();
	void CreateView();
	void updateLanguage();
protected:
	void showEvent(QShowEvent *event);
    
private:
    Ui::ReadConfigFor6CDlg *ui;

	AntennaPrmForm* mAntennaPrmForm;
	CarrierConfigForm* mCarrierConfigForm;
	PointConfigForm* mPointConfigForm;
	BuzzerConfigForm* mBuzzerConfigForm;

	bool mIsFirst;
private:
	bool QurAll();
};

#endif // READCONFIGFOR6CDLG_H
