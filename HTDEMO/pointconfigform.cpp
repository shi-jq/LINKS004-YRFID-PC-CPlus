#include "pointconfigform.h"
#include "ui_pointconfigform.h"
#include "widgetconfig.h"
#include "RFIDAPIEXPORT.h"
#include "LanguageSrc.h"
#include "readerdllbase.h"
#include "mainapp.h"
#include "readermanager.h"

PointConfigForm::PointConfigForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PointConfigForm)
{
    ui->setupUi(this);
    mQueryBtn = ui->pushButton_2;
    mSetBtn = ui->pushButton;
    mPortEnableCb = ui->comboBox;
    m2401Cb = ui->comboBox_3;
    mFreqPwrCb = ui->comboBox_2;
    mPowerCb = ui->comboBox_4;

    QStringList sl;
    sl<<GET_TXT("IDCS_EDIT_ALL_PRM_CONFIG");
    sl<<GET_TXT("IDCS_EDIT_SEND_POWER");
    sl<<GET_TXT("IDCS_EDIT_RECV_DECAY");
    sl<<GET_TXT("IDCS_EDIT_POWER");
    mPortEnableCb->addItems(sl);

    sl.clear();
    sl<<GET_TXT("IDCS_POWER_HIGHT");
    sl<<GET_TXT("IDCS_POWER_LOW");
    mPowerCb->addItems(sl);

    sl.clear();
    sl<<QString("-18dBm");
    sl<<QString("-12dBm");
    sl<<QString("-6dBm");
    sl<<QString("0dBm");
    m2401Cb->addItems(sl);

    sl.clear();
    for (int i=0; i<=15; i++)
    {
        sl<<QString("%1db").arg(i);
    }
    mFreqPwrCb->addItems(sl);

    slot_currentIndexChanged(mPortEnableCb->currentIndex());

    connect( mQueryBtn, SIGNAL( clicked()), this, SLOT( slot_QurBtnClicked( ) ) );
    connect( mSetBtn, SIGNAL( clicked()), this, SLOT( slot_SetBtnClicked( ) ) );
    connect( mPortEnableCb, SIGNAL( currentIndexChanged(int)), this, SLOT( slot_currentIndexChanged(int ) ) );

}

PointConfigForm::~PointConfigForm()
{
    delete ui;
}

void PointConfigForm::slot_QurBtnClicked()
{
    QueryAll();
}

void PointConfigForm::slot_SetBtnClicked()
{
    ReaderDllBase* pReaderDllBase = pMainApp->GetReader();
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
    unsigned char btPara[12];
    ZeroMemory(btPara,12);

    int index = mPortEnableCb->currentIndex();

    int iPwrRecPlus = mPowerCb->currentIndex();
    int i2401		= m2401Cb->currentIndex();
    int iAttenuator = mFreqPwrCb->currentIndex();

    if(iPwrRecPlus == 0)
    {
        btPara[4] = 0x02;
    }else
    {
        btPara[4] = 0x03;
    }
    btPara[0] = btPara[1] = btPara[2] = 0x03;
    btPara[5] = i2401; btPara[6] = iAttenuator;
//    switch (index)
//    {
//    case 0:
//        break;
//    case 1:
//        btPara[0] = btPara[2] = btPara[4] = btPara[6] = 0x00;
//        break;
//    case 2:
//        btPara[0] = btPara[1] = btPara[4] = btPara[5] = 0x00;
//        break;
//    default:
//        break;
//    }
    if(SAAT_YAntennaParmSet(pReaderDllBase->m_hCom, btPara, 12))
    {
        MainShowMsg(GET_TXT("IDCS_RADIO_CONFIG_SET_SUCCESS"));
    }
    else
    {
        MainShowMsg(GET_TXT("IDCS_RADIO_CONFIG_SET_FAILED"),true);
    }
}

void PointConfigForm::slot_currentIndexChanged(int index)
{
    switch(index)
    {
    case 0:
        m2401Cb->setEnabled(true);
        mFreqPwrCb->setEnabled(true);
        mPowerCb->setEnabled(true);
        break;
    case 1:
        m2401Cb->setEnabled(true);
        mFreqPwrCb->setEnabled(false);
        mPowerCb->setEnabled(false);
        break;
    case 2:
        m2401Cb->setEnabled(false);
        mFreqPwrCb->setEnabled(true);
        mPowerCb->setEnabled(false);
        break;
    case 3:
        m2401Cb->setEnabled(false);
        mFreqPwrCb->setEnabled(false);
        mPowerCb->setEnabled(true);
        break;
    default:
        m2401Cb->setEnabled(false);
        mFreqPwrCb->setEnabled(false);
        break;
    }
}

bool PointConfigForm::QueryAll()
{
    ReaderDllBase* pReaderDllBase = pMainApp->GetReader();
    if (!pReaderDllBase)
    {
        MainShowMsg(GET_TXT("IDCS_READ_NO_LINK"));
        return false;
    }
    if (!pReaderDllBase->CheckState(STATE_CONNET))
    {
        MainShowMsg(GET_TXT("IDCS_READ_NO_LINK"));
        return false;
    }
    unsigned char btPowerRecvPlus;
    unsigned char bt2401FreqSendPwr;
    unsigned char btAttenuatorPower;
    if (SAAT_YAntennaParmQuery(pReaderDllBase->m_hCom,
                               &btPowerRecvPlus,
                               &bt2401FreqSendPwr,
                               &btAttenuatorPower))
    {
        mPowerCb->setCurrentIndex(btPowerRecvPlus);
        m2401Cb->setCurrentIndex(bt2401FreqSendPwr);
        mFreqPwrCb->setCurrentIndex(btAttenuatorPower);

        MainShowMsg(GET_TXT("IDCS_RADIO_CONFIG_QUERY_SUCCESS"));

        return true;
    }
    else
    {
        MainShowMsg(GET_TXT("IDCS_RADIO_CONFIG_QUERY_FAILED"),true);

        return false;
    }
}
