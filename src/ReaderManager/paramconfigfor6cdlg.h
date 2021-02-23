#ifndef PARAMCONFIGFOR6CDLG_H
#define PARAMCONFIGFOR6CDLG_H

#include <QWidget>
#include <QComboBox>

namespace Ui {
class ParamConfigFor6CDlg;
}
class QComboBox;
class QLineEdit;
class QPushButton;
class QTableWidget;
class QTableWidgetItem;
class TableWidgetCombox;
class ParamAdd6CDlg;

class ParamConfigFor6CDlg : public QWidget
{
    Q_OBJECT
    
public:
    explicit ParamConfigFor6CDlg(QWidget *parent = 0);
    ~ParamConfigFor6CDlg();
    
private:
    Ui::ParamConfigFor6CDlg *ui;
	ParamAdd6CDlg* mParamAdd6CDlg;
};

#endif // PARAMCONFIGFOR6CDLG_H
