#include "forwardsetdlg.h"
#include "ui_forwardsetdlg.h"
#include "LanguageSrc.h"
#include "mainapp.h"
#include "RFIDAPIEXPORT.h"
#include "readerdllbase.h"

ForwardSetDlg::ForwardSetDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ForwardSetDlg)
{
    ui->setupUi(this);
    this->setWindowTitle(GET_TXT("IDCS_FORWARD_READ_WRITE"));
    mReadForwardBtn = ui->pushButton;
    mWriteForwardBtn =ui->pushButton_2;
    mForwardChanCbx = ui->comboBox;
    mIpEdit = ui->lineEdit;
    mPortEdit = ui->lineEdit_2;

    QStringList sl;
    sl<<QString("WIFI")
     <<QString("4G");
    mForwardChanCbx->addItems(sl);
    connect(mReadForwardBtn,SIGNAL(clicked()), this ,SLOT(slot_ReadForwardBtnClicked()));
    connect(mWriteForwardBtn,SIGNAL(clicked()), this ,SLOT(slot_WriteForwardBtnClicked()));
}

ForwardSetDlg::~ForwardSetDlg()
{
    delete ui;
}

void ForwardSetDlg::slot_ReadForwardBtnClicked()
{
    ReaderDllBase*	pReaderDllBase = pMainApp->GetReader();
    if (!pReaderDllBase)
    {
        MainShowMsg(GET_TXT("IDCS_READ_NO_LINK"));
        return ;
    }
    if (!pReaderDllBase->CheckState(STATE_CONNET))
    {
        MainShowMsg(GET_TXT("IDCS_READ_NO_LINK"));
        return ;
    }
    bool bRet = false;
    unsigned char param[256];
    unsigned char pLen[256];
    bRet = SAAT_ForwardQuery(pReaderDllBase->m_hCom,param,pLen);
    if(bRet)
    {
        //需要补充显示在界面上
        MainShowMsg(GET_TXT("IDCS_READ_DATA_SUCCESS"));
    }else
    {
        MainShowMsg(GET_TXT("IDCS_READ_DATA_FAILED"),true);
    }

}

void ForwardSetDlg::slot_WriteForwardBtnClicked()
{
    ReaderDllBase* pReaderDllBase = pMainApp->GetReader();
    if (!pReaderDllBase)
    {
        MainShowMsg(GET_TXT("IDCS_READ_NO_LINK"));
        return;
    }
    if (!pReaderDllBase->CheckState(STATE_CONNET))
    {
        MainShowMsg(GET_TXT("IDCS_READ_NO_LINK"));
        return ;
    }
    if (mIpEdit->text().isEmpty() || mPortEdit->text().isEmpty())
    {
        MainShowMsg(GET_TXT("IDCS_INPUT_EMPTY"));
        return ;
    }
    if (!CheckIPEdit(mIpEdit->text()))
    {
        MainShowMsg(GET_TXT("IDCS_IPADDR_INVAID"));
        return ;
    }
    if (mPortEdit->text().isEmpty() || mPortEdit->text().toUInt() <=0)
    {
        MainShowMsg(GET_TXT("IDCS_IP_PORT_ERRO"));
        return ;
    }
    unsigned char nType = 0x00;
    if(mForwardChanCbx->currentIndex() == 0)
    {
        nType = 0x01;
    }else
    {
        nType = 0x02;
    }
    unsigned char communication =0x00;//默认为TCP
    int nLen = 16;//先写16 具体情况看需要
    bool retB = SAAT_ForwardSet(pReaderDllBase->m_hCom,nType,communication,mIpEdit->text().toUtf8().data(),mPortEdit->text().toInt(),nLen);
    if(retB)
    {
        MainShowMsg(GET_TXT("IDCS_FORWARD_SET_SUCCESS"));
    }else
    {
        MainShowMsg(GET_TXT("IDCS_FORWARD_SET_FAILED"),true);
    }
}

bool ForwardSetDlg::CheckIPEdit(const QString &str)
{
    QRegExp regexp( "((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)" );

    QRegExpValidator regexp_validator( regexp, this );
    int nPos = 0;
    if ( str.isEmpty() )
    {
        return false;
    }
    QString tmp = str;
    if ( !str.isEmpty() && regexp_validator.validate( tmp, nPos ) != QValidator::Acceptable )
    {
        return false;
    }
    return true;
}
