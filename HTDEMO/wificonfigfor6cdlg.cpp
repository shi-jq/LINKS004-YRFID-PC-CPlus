#include "wificonfigfor6cdlg.h"
#include "ui_wificonfigfor6cdlg.h"
#include <QShowEvent>
#include "LanguageSrc.h"
#include "appconfig.h"
#include "mainapp.h"
#include "RFIDAPIEXPORT.h"
#include "readerdllcommon.h"
#include "AtTransExport.h"
#include "wifiselectdlg.h"

WIFIConfigFor6CDLg::WIFIConfigFor6CDLg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WIFIConfigFor6CDLg)
{
    ui->setupUi(this);
	this->setWindowTitle(GET_TXT("IDCS_WIFI_CONFIG"));

	mIpAddrEdit = ui->lineEdit;
	mAutoGetIpCb= ui->checkBox;
	mMaskEdit=ui->lineEdit_2;
	mGatewayEdit=ui->lineEdit_3;
	mDNSEdit=ui->lineEdit_4;
	mMacEdit=ui->lineEdit_5;
	mNetQueryBtn = ui->pushButton_2;
	mNetSetBtn=ui->pushButton;
	
	mSSIDEdit = ui->lineEdit_6;
	mSModelCb = ui->comboBox;
	mPwdFomortCb=ui->comboBox_2;
	mPwdIndexCb=ui->comboBox_3;
	mPwdEdit=ui->lineEdit_7;
	mWirelessQueryBtn=ui->pushButton_3;
	mWirelessSetBtn=ui->pushButton_5;

	mAutoWorkModel=ui->checkBox_2;
	mProtocolCb=ui->comboBox_4;
	mCSModelCb=ui->comboBox_5;
	mServerEdit=ui->lineEdit_8;
	mServerPortEdit=ui->lineEdit_9;

	mModelQueryBtn=ui->pushButton_4;
	mModelSetBtn=ui->pushButton_6;
	
	mSelectSSIDBtn=ui->pushButton_7;
	mQueryStateBtn=ui->pushButton_8;
	mResetBtn=ui->pushButton_9;
	mStateLabel = ui->label_20;
	mEnterTransBtn=ui->pushButton_10;
	mExitTransBtn=ui->pushButton_11;
	mBg1 = ui->widget_5;
	mBg2 = ui->widget_7;
	mBg3 = ui->widget_9;
	mEnterTransFailedTig = ui->label_19;

	ui->label->setText(GET_TXT("IDCS_IP_ADDR"));
	ui->label_2->setText(GET_TXT("IDCS_IP_MASK"));
	ui->label_3->setText(GET_TXT("IDCS_IP_GATEWAY"));
	ui->label_4->setText(GET_TXT("IDCS_DNS"));
	ui->label_5->setText(GET_TXT("IDCS_MAC_ADDR"));
	ui->checkBox->setText(GET_TXT("IDCS_AUTO_GETIP"));
	mNetQueryBtn->setText(GET_TXT("IDCS_QUERY"));
	mNetSetBtn->setText(GET_TXT("IDCS_SET"));
	ui->label_15->setText(GET_TXT("IDCS_NET_CONFIG"));
	ui->label_16->setText(GET_TXT("IDCS_WIRELESS_CONFIG"));
	ui->label_17->setText(GET_TXT("IDCS_WORK_MODEL_CONFIG"));

	ui->label_6->setText(GET_TXT("IDCS_SSID_NAME"));
	ui->label_7->setText(GET_TXT("IDCS_SECURE_MODEL"));
	ui->label_8->setText(GET_TXT("IDCS_PWD_FOMORT"));
	ui->label_9->setText(GET_TXT("IDCS_PWD_INDEX"));
	ui->label_10->setText(GET_TXT("IDCS_PWD_Y"));
	mEnterTransFailedTig->setText(GET_TXT("IDCS_WIFI_ENTER_TRANS_TIG"));
	mWirelessQueryBtn->setText(GET_TXT("IDCS_QUERY"));
	mWirelessSetBtn->setText(GET_TXT("IDCS_SET"));

	ui->checkBox_2->setText(GET_TXT("IDCS_ENABLE_AUTO_MODEL"));
	ui->label_11->setText(GET_TXT("IDCS_PROTOCOL_TYPE"));
	ui->label_12->setText(GET_TXT("IDCS_CS_MODEL"));
	ui->label_13->setText(GET_TXT("IDCS_SERVER_ADDR"));
	ui->label_14->setText(GET_TXT("IDCS_LISENT_PORT"));
	mModelQueryBtn->setText(GET_TXT("IDCS_QUERY"));
	mModelSetBtn->setText(GET_TXT("IDCS_SET"));
	mSelectSSIDBtn->setText(GET_TXT("IDCS_SELECT_WIFI"));
	mResetBtn->setText(GET_TXT("IDCS_RESTORATION"));
	mQueryStateBtn->setText(GET_TXT("IDCS_LINK_STATE"));
	mEnterTransBtn->setText(GET_TXT("IDCS_ENTER_TRANS"));
	mExitTransBtn->setText(GET_TXT("IDCS_EXIT_TRANS"));

	mWifiSelectDlg = new WifiSelectDlg(this);
	mWifiSelectDlg->setModal(true);

	mIpAddrEdit->setInputMask(QString("000.000.000.000;"));
	mMaskEdit->setInputMask(QString("000.000.000.000;"));
	mGatewayEdit->setInputMask(QString("000.000.000.000;"));
	mDNSEdit->setInputMask(QString("000.000.000.000;"));
	mMacEdit->setInputMask(QString("HH:HH:HH:HH:HH:HH;"));
	mServerEdit->setInputMask(QString("000.000.000.000;"));

	mAutoGetIpCb->setEnabled(false);
	QStringList sl;
	sl<<QString("OPEN")
		<<QString("WEP64")
		<<QString("WEP128")
		<<QString("WPA-PSK(TKIP)")
		<<QString("WPA-PSK(CCMP/AES)")
		<<QString("WPA2-PSK(TKIP)")
		<<QString("WPA2-PSK(CCMP/AES)");
	mSModelCb->addItems(sl);
	sl.clear();
	sl<<QString("1")
		<<QString("2")
		<<QString("3")
		<<QString("4");
	mPwdIndexCb->addItems(sl);
	sl.clear();
	sl<<QString("HEX")
		<<QString("ASCII");
	mPwdFomortCb->addItems(sl);

	sl.clear();
	sl<<QString("TCP")
		<<QString("UDP");
	mProtocolCb->addItems(sl);

	sl.clear();
	sl<<QString("Client")
		<<QString("Server");
	mCSModelCb->addItems(sl);
	mCSModelCb->setEnabled(false);
	mAutoWorkModel->setEnabled(false);
	mMacEdit->setReadOnly(true);

	mAutoWorkModel->hide();
	mAutoGetIpCb->hide();


	connect( mNetQueryBtn, SIGNAL( clicked()), this, SLOT( slot_NetQueryBtnClicked( ) ) );
	connect( mNetSetBtn, SIGNAL( clicked()), this, SLOT( slot_NetSetBtnClicked( ) ) );
	connect( mWirelessQueryBtn, SIGNAL( clicked()), this, SLOT( slot_WirelessQueryBtnClicked( ) ) );
	connect( mWirelessSetBtn, SIGNAL( clicked()), this, SLOT( slot_WirelessSetBtnClicked( ) ) );
	connect( mModelQueryBtn, SIGNAL( clicked()), this, SLOT( slot_ModelQueryBtnClicked( ) ) );
	connect( mModelSetBtn, SIGNAL( clicked()), this, SLOT( slot_ModelSetBtnClicked( ) ) );
	connect( mSelectSSIDBtn, SIGNAL( clicked()), this, SLOT( slot_SelectSSIDBtnClicked( ) ) );
	connect( mQueryStateBtn, SIGNAL( clicked()), this, SLOT( slot_QueryStateBtnClicked( ) ) );
	connect( mResetBtn, SIGNAL( clicked()), this, SLOT( slot_ResetBtnClicked( ) ) );
	connect( mSModelCb, SIGNAL( currentIndexChanged(int)), this, SLOT( slot_SModelCbIndexChange(int ) ) );
	connect( mEnterTransBtn, SIGNAL( clicked()), this, SLOT( slot_EnterTransBtnClicked( ) ) );
	connect( mExitTransBtn, SIGNAL( clicked()), this, SLOT( slot_ExitTransBtnClicked() ) );

}

WIFIConfigFor6CDLg::~WIFIConfigFor6CDLg()
{
    delete ui;
}

bool WIFIConfigFor6CDLg::EnterTrans()
{
	ReaderDllCommon*	pReaderDllCommon = (ReaderDllCommon*)pMainApp->GetReader();	
	Q_ASSERT(pReaderDllCommon);
	if (!pReaderDllCommon->CheckState(STATE_CONNET))
	{
		MainShowMsg(GET_TXT("IDCS_READ_NO_LINK"));
		SetViewEnable(false);
		return false;
	}

	bool bRet = false;

	bRet = Wifi_Exit(pReaderDllCommon->m_hCom);
	bRet = SAAT_EnterTrans(pReaderDllCommon->m_hCom, 0);
	if (bRet)
	{
		Sleep(500);
		bRet = Wifi_Enter(pReaderDllCommon->m_hCom);		
	}

	if (!bRet)
	{
		MainShowMsg(GET_TXT("IDCS_ENTER_TRANS_FAILED"));
		Wifi_Exit(pReaderDllCommon->m_hCom);
		SetViewEnable(false);
		mEnterTransBtn->setEnabled(true);
		mExitTransBtn->setEnabled(true);
		mEnterTransFailedTig->show();
	}	
	else
	{
		MainShowMsg(GET_TXT("IDCS_ENTER_TRANS_SUCCESS"));
		SetViewEnable(true);
		mEnterTransBtn->setEnabled(false);
		mExitTransBtn->setEnabled(false);
		mEnterTransFailedTig->hide();
	}
	
	return bRet;
}

bool WIFIConfigFor6CDLg::QueryNetPram()
{
	ReaderDllCommon*	pReaderDllCommon = (ReaderDllCommon*)pMainApp->GetReader();	
	Q_ASSERT(pReaderDllCommon);
	if (!pReaderDllCommon->CheckState(STATE_CONNET))
	{
		MainShowMsg(GET_TXT("IDCS_READ_NO_LINK"));
		return false;
	}
	unsigned char pMode = 0;
	char pIP[255];
	char pSubNet[255];
	char pGateWay[255];
	char pDNS[255];
	ZeroMemory(pIP, 255*sizeof(char));
	ZeroMemory(pSubNet, 255*sizeof(char));
	ZeroMemory(pGateWay, 255*sizeof(char));
	ZeroMemory(pDNS, 255*sizeof(char));
	bool bRet = Wifi_ReadNetPara(pReaderDllCommon->m_hCom,
		&pMode, pIP, pSubNet, pGateWay, pDNS);
	if (bRet)
	{		
		mAutoGetIpCb->setChecked(pMode==1);		
		mIpAddrEdit->setText(QString::fromUtf8(pIP));
		mMaskEdit->setText(QString::fromUtf8(pSubNet));
		mGatewayEdit->setText(QString::fromUtf8(pGateWay));
		mDNSEdit->setText(QString::fromUtf8(pDNS));
		MainShowMsg(GET_TXT("IDCS_NET_QUERY_SUCCESS"));
	}
	else
	{
		MainShowMsg(GET_TXT("IDCS_NET_QUERY_FAILED"));
	}

	return bRet;
}

bool WIFIConfigFor6CDLg::QuerySSID()
{
	ReaderDllCommon*	pReaderDllCommon = (ReaderDllCommon*)pMainApp->GetReader();	
	Q_ASSERT(pReaderDllCommon);
	if (!pReaderDllCommon->CheckState(STATE_CONNET))
	{
		MainShowMsg(GET_TXT("IDCS_READ_NO_LINK"));
		return false;
	}

	char pIP[255];
	ZeroMemory(pIP, 255*sizeof(char));
	bool bRet = Wifi_QuerySSID(pReaderDllCommon->m_hCom, pIP);
	if (bRet)
	{
		mSSIDEdit->setText(QString::fromUtf8(pIP));
		MainShowMsg(GET_TXT("IDCS_SSID_QUERY_SUCCESS"));
	}
	else
	{
		MainShowMsg(GET_TXT("IDCS_SSID_QUERY_FAILED"),true);
	}

	return bRet;
}

bool WIFIConfigFor6CDLg::QuerySecureType()
{
	ReaderDllCommon*	pReaderDllCommon = (ReaderDllCommon*)pMainApp->GetReader();	
	Q_ASSERT(pReaderDllCommon);
	if (!pReaderDllCommon->CheckState(STATE_CONNET))
	{
		MainShowMsg(GET_TXT("IDCS_READ_NO_LINK"));
		return false;
	}
	unsigned char pType = 0;
	bool bRet = Wifi_QuerySecurityType(pReaderDllCommon->m_hCom,
		&pType);
	if (bRet)
	{
		mSModelCb->setCurrentIndex(pType);
		if (pType == 0)
		{
			mPwdFomortCb->setEnabled(false);
			mPwdIndexCb->setEnabled(false);
			mPwdEdit->setEnabled(false);
		}
		else
		{
			mPwdFomortCb->setEnabled(true);
			mPwdIndexCb->setEnabled(true);
			mPwdEdit->setEnabled(true);
		}
		MainShowMsg(GET_TXT("IDCS_SECURE_TYPE_SUCCESS"));
	}
	else
	{
		MainShowMsg(GET_TXT("IDCS_SECURE_TYPE_FAILED"));
	}
	return bRet;
}

bool WIFIConfigFor6CDLg::QueryKey()
{
	ReaderDllCommon*	pReaderDllCommon = (ReaderDllCommon*)pMainApp->GetReader();	
	Q_ASSERT(pReaderDllCommon);
	if (!pReaderDllCommon->CheckState(STATE_CONNET))
	{
		MainShowMsg(GET_TXT("IDCS_READ_NO_LINK"));
		return false;
	}

	unsigned char pType = 0;
	unsigned char pIndex = 0;
	char pKey[255];
	ZeroMemory(pKey, 255*sizeof(char));
	bool bRet = Wifi_QueryKey(pReaderDllCommon->m_hCom,
		&pType, &pIndex, pKey);
	

	if (bRet)
	{
		mPwdFomortCb->setCurrentIndex(pType);
		mPwdIndexCb->setCurrentIndex(pIndex);
		mPwdEdit->setText(QString::fromUtf8(pKey));
		MainShowMsg(GET_TXT("IDCS_QUERY_NET_KEY_SUCCESS"));
	}
	else
	{
		MainShowMsg(GET_TXT("IDCS_QUERY_NET_KEY_FAILED"));
	}
	return bRet;
}

bool WIFIConfigFor6CDLg::QueryMac()
{
	ReaderDllCommon*	pReaderDllCommon = (ReaderDllCommon*)pMainApp->GetReader();	
	Q_ASSERT(pReaderDllCommon);
	if (!pReaderDllCommon->CheckState(STATE_CONNET))
	{
		MainShowMsg(GET_TXT("IDCS_READ_NO_LINK"));
		return false;
	}

	char pMac[255];
	ZeroMemory(pMac, 255*sizeof(char));
	bool bRet = Wifi_QueryMac(pReaderDllCommon->m_hCom, pMac);
	if (bRet)
	{
		mMacEdit->setText(QString::fromUtf8(pMac).toUpper());
		MainShowMsg(GET_TXT("IDCS_MAC_ADDR_QUERY_SUCCESS"));
	}
	else
	{
		MainShowMsg(GET_TXT("IDCS_MAC_ADDR_QUERY_FAILED"));
	}
	return bRet;
}

bool WIFIConfigFor6CDLg::QuerySocketConnectInfo()
{
	ReaderDllCommon*	pReaderDllCommon = (ReaderDllCommon*)pMainApp->GetReader();	
	Q_ASSERT(pReaderDllCommon);
	if (!pReaderDllCommon->CheckState(STATE_CONNET))
	{
		MainShowMsg(GET_TXT("IDCS_READ_NO_LINK"));
		return false;
	}


	unsigned char pProcl = 0;
	unsigned char pCS = 0;
	unsigned short pPort = 0;
	char pHost[255];
	ZeroMemory(pHost, 255*sizeof(char));
	bool bRet = Wifi_QuerySocketConnectInfo(pReaderDllCommon->m_hCom, 
		&pProcl, &pCS, pHost, &pPort);
	if (bRet)
	{
		mProtocolCb->setCurrentIndex(pProcl);
		mCSModelCb->setCurrentIndex(pCS);
		mServerEdit->setText(QString::fromUtf8(pHost));
		mServerPortEdit->setText(QString("%1").arg(pPort));
		MainShowMsg(GET_TXT("IDCS_WORK_MODEL_QUERY_SUCCESS"));
	}
	else
	{
		MainShowMsg(GET_TXT("IDCS_WORK_MODEL_QUERY_FAILED"));
	}

	return bRet;
}

bool WIFIConfigFor6CDLg::QueryWorkMode()
{
	ReaderDllCommon*	pReaderDllCommon = (ReaderDllCommon*)pMainApp->GetReader();	
	Q_ASSERT(pReaderDllCommon);
	if (!pReaderDllCommon->CheckState(STATE_CONNET))
	{
		MainShowMsg(GET_TXT("IDCS_READ_NO_LINK"));
		return false;
	}

	unsigned char pWorkMode = 0;
	bool bRet = Wifi_QueryWorkMode(pReaderDllCommon->m_hCom, &pWorkMode);
	if (bRet)
	{
		//nWorkMode = pWorkMode;
		//MainShowMsg(GET_TXT("IDCS_AUTO_WORK_MODEL_QUERY_SUCCESS"));
	}
	else
	{
		//MainShowMsg(GET_TXT("IDCS_AUTO_WORK_MODEL_QUERY_FAILED"));
	}

	return bRet;
}

void WIFIConfigFor6CDLg::slot_NetQueryBtnClicked()
{
	bool bRet = QueryNetPram();
	if (bRet)
	{
		bRet= QueryMac();
	}
}

void WIFIConfigFor6CDLg::slot_NetSetBtnClicked()
{
	SetNetPram();	
}

void WIFIConfigFor6CDLg::slot_WirelessQueryBtnClicked()
{
	bool bRet = QuerySSID();
	if (bRet)
	{
		bRet= QuerySecureType();
	}
	if (bRet)
	{
		bRet= QueryKey();
	}
}

void WIFIConfigFor6CDLg::slot_WirelessSetBtnClicked()
{
	bool bRet = SetSSID();
	if (bRet)
	{
		bRet= SetSecureType();
	}

	if (bRet)
	{
		if (mSModelCb->currentIndex() != 0)
		{
			bRet = SetKey();
		}
	}
}

void WIFIConfigFor6CDLg::slot_ModelQueryBtnClicked()
{
	bool bRet = QuerySocketConnectInfo();
	if (bRet)
	{
		bRet= QueryWorkMode();
	}
}

void WIFIConfigFor6CDLg::slot_ModelSetBtnClicked()
{
	SetSocketConnectInfo();
}

void WIFIConfigFor6CDLg::slot_SelectSSIDBtnClicked()
{
	bool bRet = false;
	ReaderDllCommon*	pReaderDllCommon = (ReaderDllCommon*)pMainApp->GetReader();	
	Q_ASSERT(pReaderDllCommon);
	if (!pReaderDllCommon->CheckState(STATE_CONNET))
	{
		MainShowMsg(GET_TXT("IDCS_READ_NO_LINK"));
		return ;
	}

	if (mWifiSelectDlg->exec() == QDialog::Accepted)
	{
		QString ssidStr = mWifiSelectDlg->GetSelectSSID();
		if (!ssidStr.isEmpty())
		{
			mSSIDEdit->setText(ssidStr);
		}
	}	
}

void WIFIConfigFor6CDLg::slot_QueryStateBtnClicked()
{
	bool bRet = false;
	ReaderDllCommon*	pReaderDllCommon = (ReaderDllCommon*)pMainApp->GetReader();	
	Q_ASSERT(pReaderDllCommon);
	if (!pReaderDllCommon->CheckState(STATE_CONNET))
	{
		MainShowMsg(GET_TXT("IDCS_READ_NO_LINK"));
		return ;
	}
	
	unsigned char pMode = 0;
	char pIP[255];
	char pSubNet[255];
	char pGateWay[255];
	char pDNS[255];
	ZeroMemory(pIP, 255*sizeof(char));
	ZeroMemory(pSubNet, 255*sizeof(char));
	ZeroMemory(pGateWay, 255*sizeof(char));
	ZeroMemory(pDNS, 255*sizeof(char));
	bRet = Wifi_QueryConnectStauts(pReaderDllCommon->m_hCom,
		&pMode, pIP, pSubNet, pGateWay, pDNS);

	if (bRet)
	{
		if (pMode == 1)
		{
			mStateLabel->setText(GET_TXT("IDCS_LINKED"));
		}
		else
		{
			mStateLabel->setText(GET_TXT("IDCS_NO_LINK"));
		}
		MainShowMsg(GET_TXT("IDCS_STATE_QUERY_SUCCESS"));
	}
	else
	{
		mStateLabel->setText(GET_TXT("IDCS_NO_LINK"));
		MainShowMsg(GET_TXT("IDCS_STATE_QUERY_FALIED"));
	}
}

void WIFIConfigFor6CDLg::slot_ResetBtnClicked()
{
	bool bRet = false;
	ReaderDllCommon*	pReaderDllCommon = (ReaderDllCommon*)pMainApp->GetReader();	
	Q_ASSERT(pReaderDllCommon);
	if (!pReaderDllCommon->CheckState(STATE_CONNET))
	{
		MainShowMsg(GET_TXT("IDCS_READ_NO_LINK"));
		return ;
	}
	
	bRet = Wifi_Reset(pReaderDllCommon->m_hCom);

	if (bRet)
	{
		MainShowMsg(GET_TXT("IDCS_WIFI_RESET_SUCCESS"));
	}
	else
	{
		MainShowMsg(GET_TXT("IDCS_WIFI_RESET_FAILED"));
	}


}

void WIFIConfigFor6CDLg::showEvent(QShowEvent *ev)
{
	if (EnterTrans())
	{
		slot_NetQueryBtnClicked();
		slot_WirelessQueryBtnClicked();
		slot_ModelQueryBtnClicked();
	}
	
	QDialog::showEvent(ev);		
}


void WIFIConfigFor6CDLg::closeEvent(QCloseEvent *ev)
{
	if (!ExitTrans())
	{
		ev->ignore();
		return;
	}

	ev->accept();
}


bool WIFIConfigFor6CDLg::ExitTrans()
{
	ReaderDllCommon*	pReaderDllCommon = (ReaderDllCommon*)pMainApp->GetReader();	
	Q_ASSERT(pReaderDllCommon);
	bool bRet = Wifi_Exit(pReaderDllCommon->m_hCom);
	if (!bRet)
	{
		MainShowMsg(GET_TXT("IDCS_EXIT_TRANS_FAILED"));
	}
	return bRet;
}

void  WIFIConfigFor6CDLg::SetViewEnable(bool isEnable)
{
	mBg1->setEnabled(isEnable);
	mBg2->setEnabled(isEnable);
	mBg3->setEnabled(isEnable);
	mResetBtn->setEnabled(isEnable);
	mQueryStateBtn->setEnabled(isEnable);
	
}

void WIFIConfigFor6CDLg::slot_EnterTransBtnClicked()
{
	EnterTrans();
}

void WIFIConfigFor6CDLg::slot_ExitTransBtnClicked()
{
	if (ExitTrans())
	{
		MainShowMsg(GET_TXT("IDCS_EXIT_TRANS_SUCCESS"));
	}
	else
	{
		MainShowMsg(GET_TXT("IDCS_EXIT_TRANS_FAILED"));
	}
}

void WIFIConfigFor6CDLg::slot_SModelCbIndexChange(int index)
{
	if (index == 0)
	{
		mPwdFomortCb->setEnabled(false);
		mPwdIndexCb->setEnabled(false);
		mPwdEdit->setEnabled(false);
	}
	else
	{
		mPwdFomortCb->setEnabled(true);
		mPwdIndexCb->setEnabled(true);
		mPwdEdit->setEnabled(true);
	}
}

bool WIFIConfigFor6CDLg::CheckIPEdit(const QString& str)
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

bool WIFIConfigFor6CDLg::SetNetPram()
{
	bool bRet = false;
	ReaderDllCommon*	pReaderDllCommon = (ReaderDllCommon*)pMainApp->GetReader();	
	Q_ASSERT(pReaderDllCommon);
	if (!pReaderDllCommon->CheckState(STATE_CONNET))
	{
		MainShowMsg(GET_TXT("IDCS_READ_NO_LINK"));
		return bRet;
	}

	if (!CheckIPEdit(mIpAddrEdit->text()))
	{
		MainShowMsg(GET_TXT("IDCS_IPADDR_INVAID"));
		return bRet;
	}
	if (!CheckIPEdit(mMaskEdit->text()))
	{
		MainShowMsg(GET_TXT("IDCS_SUBMASK_INVAID"));
		return bRet;
	}

	if (!CheckIPEdit(mGatewayEdit->text()))
	{
		MainShowMsg(GET_TXT("IDCS_GATEWAY_INVAID"));
		return bRet;
	}
	char* pIP;
	char* pSubNet;
	char* pGateWay;
	char* pDNS;
	int nCheck = 0;
	QByteArray tempBa1 = mIpAddrEdit->text().toUtf8();
	pIP = tempBa1.data();
	QByteArray tempBa2 = mMaskEdit->text().toUtf8();
	pSubNet = tempBa2.data();
	QByteArray tempBa3 = mGatewayEdit->text().toUtf8();
	pGateWay = tempBa3.data();
	QByteArray tempBa4 = mDNSEdit->text().toUtf8();
	pDNS = tempBa4.data();
	/*if (!mAutoGetIpCb->isChecked())
	{
		nCheck = 1;
	}
	else
	{
		nCheck = 0;
	}*/
	nCheck = 1; //不自动获取ip

	bRet = Wifi_SetNetPara(pReaderDllCommon->m_hCom,
		nCheck, pIP, pSubNet, pGateWay, pDNS);
	if (bRet)
	{
		MainShowMsg(GET_TXT("IDCS_NET_SET_SUCCESS"));
	}
	else
	{
		MainShowMsg(GET_TXT("IDCS_NET_SET_FAILED"));
	}

	return bRet;
}

bool WIFIConfigFor6CDLg::SetSSID()
{
	bool bRet = false;
	ReaderDllCommon*	pReaderDllCommon = (ReaderDllCommon*)pMainApp->GetReader();	
	Q_ASSERT(pReaderDllCommon);
	if (!pReaderDllCommon->CheckState(STATE_CONNET))
	{
		MainShowMsg(GET_TXT("IDCS_READ_NO_LINK"));
		return bRet;
	}
	
	QString strSSID = mSSIDEdit->text();
	char* pSSID;

	if (strSSID.isEmpty())
	{
		MainShowMsg(GET_TXT("IDCS_DATA_LEN_ERRO"));
		return bRet;
	}
	QByteArray tmpBa = strSSID.toUtf8();
	pSSID = tmpBa.data();

	bRet = Wifi_SetSSID(pReaderDllCommon->m_hCom, pSSID);
	if (bRet)
	{
		MainShowMsg(GET_TXT("IDCS_SSID_SET_SUCCESS"));
	}
	else
	{
		MainShowMsg(GET_TXT("IDCS_SSID_SET_FAILED"));
	}

	return bRet;
}

bool WIFIConfigFor6CDLg::SetSecureType()
{
	bool bRet = false;
	ReaderDllCommon*	pReaderDllCommon = (ReaderDllCommon*)pMainApp->GetReader();	
	Q_ASSERT(pReaderDllCommon);
	if (!pReaderDllCommon->CheckState(STATE_CONNET))
	{
		MainShowMsg(GET_TXT("IDCS_READ_NO_LINK"));
		return bRet;
	}

	int nType = mSModelCb->currentIndex();
	int nKeyType = mPwdFomortCb->currentIndex();
	QString strKey = mPwdEdit->text();
	switch (nType)
	{
	case 0:
		break;
	case 1:
		if (nKeyType == 0)
		{
			if (strKey.length() != 10)
			{
				MainShowMsg(GET_TXT("IDCS_TIG_NET_SET_KEY_LENGTH_10"));
				return bRet;
			}
		}
		else
		{
			if (strKey.length() != 5)
			{
				MainShowMsg(GET_TXT("IDCS_TIG_NET_SET_KEY_LENGTH_5"));
				return bRet;
			}
		}

		break;
	case 2:
		if (nKeyType == 0)
		{
			if (strKey.length() != 26)
			{
				MainShowMsg(GET_TXT("IDCS_TIG_NET_SET_KEY_LENGTH_26"));
				return bRet;
			}
		}
		else
		{
			if (strKey.length() != 13)
			{
				MainShowMsg(GET_TXT("IDCS_TIG_NET_SET_KEY_LENGTH_13"));
				return bRet;
			}
		}
		break;
	default:
		if (nKeyType == 0)
		{
			if (strKey.length() != 64)
			{
				MainShowMsg(GET_TXT("IDCS_TIG_NET_SET_KEY_LENGTH_64"));
				return bRet;
			}
		}
		else
		{
			if (strKey.length() < 8)
			{
				MainShowMsg(GET_TXT("IDCS_TIG_NET_SET_KEY_LENGTH_8_63"));
				return bRet;
			}
		}
		break;
	}


	bRet =  Wifi_SetSecurityType(pReaderDllCommon->m_hCom, 
		(unsigned char)nType);
	if (bRet)
	{
		MainShowMsg(GET_TXT("IDCS_SECURE_TYPE_SET_SUCCESS"));
	}
	else
	{
		MainShowMsg(GET_TXT("IDCS_SECURE_TYPE_SET_FAILED"));
	}

	return bRet;
}

bool WIFIConfigFor6CDLg::SetKey()
{
	bool bRet = false;
	ReaderDllCommon*	pReaderDllCommon = (ReaderDllCommon*)pMainApp->GetReader();	
	Q_ASSERT(pReaderDllCommon);
	if (!pReaderDllCommon->CheckState(STATE_CONNET))
	{
		MainShowMsg(GET_TXT("IDCS_READ_NO_LINK"));
		return bRet;
	}
	int nKeyType = mPwdFomortCb->currentIndex();
	int nIndex = mPwdIndexCb->currentIndex();
	QString strKey = mPwdEdit->text();
	QByteArray tmpBa = strKey.toUtf8();
	char* pKey = tmpBa.data();
	bRet = Wifi_SetKey(pReaderDllCommon->m_hCom, 
		(unsigned char)nKeyType, (unsigned char)nIndex, pKey);
	if (bRet)
	{
		MainShowMsg(GET_TXT("IDCS_SET_NET_KEY_SUCCESS"));
	}
	else
	{
		MainShowMsg(GET_TXT("IDCS_SET_NET_KEY_FAILED"));
	}

	return bRet;
}



bool WIFIConfigFor6CDLg::SetSocketConnectInfo()
{
	bool bRet = false;
	ReaderDllCommon*	pReaderDllCommon = (ReaderDllCommon*)pMainApp->GetReader();	
	Q_ASSERT(pReaderDllCommon);
	if (!pReaderDllCommon->CheckState(STATE_CONNET))
	{
		MainShowMsg(GET_TXT("IDCS_READ_NO_LINK"));
		return bRet;
	}
	int nProtcl = mProtocolCb->currentIndex();
	int nCS = mCSModelCb->currentIndex();
	QString strHost = mServerEdit->text();
	QByteArray tmpBa = strHost.toUtf8();
	char* pHost = tmpBa.data();
	int nPort = mServerPortEdit->text().toInt();

	bRet =  Wifi_SetSocketConnectInfo(
		pReaderDllCommon->m_hCom, 
		(unsigned char)nProtcl, (unsigned char)nCS,
		pHost, (unsigned short)nPort);

	if (bRet)
	{
		MainShowMsg(GET_TXT("IDCS_WORK_MODEL_SET_SUCCESS"));
	}
	else
	{
		MainShowMsg(GET_TXT("IDCS_WORK_MODEL_SET_FAILED"));
	}

	return bRet;
}

