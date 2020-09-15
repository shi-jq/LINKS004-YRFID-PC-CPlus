#ifndef ANTENNAPRMFORM_H
#define ANTENNAPRMFORM_H

#include <QWidget>

namespace Ui {
class AntennaPrmForm;
}
class QPushButton;
class QCheckBox;
class QSpinBox;
class QComboBox;
class AntennaPrmForm : public QWidget
{
    Q_OBJECT
    
public:
    explicit AntennaPrmForm(QWidget *parent = 0);
    ~AntennaPrmForm();
	bool QurAntenna();   
private:
    Ui::AntennaPrmForm *ui;
	QPushButton* mQurAntennaBtn;//���ð�ť
	QPushButton* mSetAntennaBtn;//��ѯ��ť

	QCheckBox* mAntenna1CheckBox;//����1234
	QCheckBox* mAntenna2CheckBox;
	QCheckBox* mAntenna3CheckBox;
	QCheckBox* mAntenna4CheckBox;

	QSpinBox* mAntenna1TimeSb;//����ʹ��ʱ��1234
	QSpinBox* mAntenna2TimeSb;
	QSpinBox* mAntenna3TimeSb;
	QSpinBox* mAntenna4TimeSb;


	QComboBox* mFreqPwrCb1;//����˥����˥��
	QComboBox* mFreqPwrCb2;//����˥����˥��
	QComboBox* mFreqPwrCb3;//����˥����˥��
	QComboBox* mFreqPwrCb4;//����˥����˥��
	
	bool SetAntenna();
private slots:
	void slot_QurAntennaBtnClicked();
	void slot_SetAntennaBtnClicked();
};

#endif // ANTENNAPRMFORM_H
