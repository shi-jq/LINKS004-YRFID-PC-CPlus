#ifndef TABUPLOADFORM_H
#define TABUPLOADFORM_H

#include <QWidget>

namespace Ui {
class TabUploadForm;
}
class FiltrateTagFor6CDlg;
class FlashConfigFor6CDlg;
class UploadPramForm;
class ForwardSetDlg;
class GprsConfigDlg;
class TabUploadForm : public QWidget
{
    Q_OBJECT
    
public:
    explicit TabUploadForm(QWidget *parent = 0);
    ~TabUploadForm();
    
private:
    Ui::TabUploadForm *ui;
	FiltrateTagFor6CDlg* mFiltrateTagFor6CDlg;
	FlashConfigFor6CDlg* mFlashConfigFor6CDlg;
	UploadPramForm* mUploadPramForm;
	ForwardSetDlg* mForwardSetDlg;
	GprsConfigDlg* mGprsConfigDlg;
};

#endif // TABUPLOADFORM_H
