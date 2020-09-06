#ifndef POINTCONFIGFORM_H
#define POINTCONFIGFORM_H

#include <QWidget>

namespace Ui {
class PointConfigForm;
}
class QPushButton;
class QComboBox;
class PointConfigForm : public QWidget
{
    Q_OBJECT
    
public:
    explicit PointConfigForm(QWidget *parent = 0);
    ~PointConfigForm();
    bool QueryAll();
private:
    Ui::PointConfigForm *ui;
	QPushButton*  mQueryBtn;
	QPushButton*  mSetBtn;
	QComboBox* mPortEnableCb;//��������
    QComboBox* mPowerCb; //���Ž�������
	QComboBox* m2401Cb;//��Ƶ���书��
	QComboBox* mFreqPwrCb;//����˥����˥��
private slots:
	void slot_QurBtnClicked();
	void slot_SetBtnClicked();
	void slot_currentIndexChanged(int index);
};

#endif // POINTCONFIGFORM_H
