#ifndef UPLOADPRAMFORM_H
#define UPLOADPRAMFORM_H

#include <QWidget>

namespace Ui {
class UploadPramForm;
}
class QComboBox;
class QPushButton;
class UploadPramForm : public QWidget
{
    Q_OBJECT 
public:
    explicit UploadPramForm(QWidget *parent = 0);
    ~UploadPramForm();
protected:
	void showEvent(QShowEvent *event);
private:
    Ui::UploadPramForm *ui;
	QComboBox* m_WorkModelCb;
	QComboBox* m_DeviceTypeValueCb;
	QComboBox* m_CommandTypeValueCb;	
	QComboBox* m_ConnetPortValueCb;
	QPushButton* mQueryBtn;
	QPushButton* mSetBtn;

	bool  mFirst;

	bool WorkModelQuery();
	bool DeviceTypeQuery();	
	bool CommandTypeQuery();
	bool ConnetPortQuery();
	bool QueryAll();

	bool WorkModelSet();
	bool DeviceTypeSet();
	bool CommandTypeSet();
	bool ConnetPortSet();

	bool SetAll();

	private slots:
		void slot_QueryBtnClicked();
		void slot_SetBtnClicked();
};

#endif // UPLOADPRAMFORM_H
