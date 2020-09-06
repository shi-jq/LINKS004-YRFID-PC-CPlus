#include "netconfigfor6cdlg.h"
#include "ui_netconfigfor6cdlg.h"
#include "LanguageSrc.h"
#include "appconfig.h"
#include "mainapp.h"
#include "RFIDAPIEXPORT.h"
#include "readerdllbase.h"
#include <QRegExpValidator>
NetConfigFor6CDlg::NetConfigFor6CDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NetConfigFor6CDlg)
{
    ui->setupUi(this);
	this->setWindowTitle(GET_TXT("IDCS_NET_CONFIG"));
	mIpAddrEdit= ui->lineEdit;
	mMaskEdit=ui->lineEdit_2;
	mGatewayEdit=ui->lineEdit_3;
	mUdpEdit=ui->lineEdit_4;
	mTcpEdit=ui->lineEdit_5;
	mMacEdit=ui->lineEdit_6;
	mQurBtn=ui->pushButton;
	mSetBtn=ui->pushButton_2;

	mIpAddrEdit->setInputMask(QString("000.000.000.000;"));
	mMaskEdit->setInputMask(QString("000.000.000.000;"));
	mGatewayEdit->setInputMask(QString("000.000.000.000;"));
	mMacEdit->setInputMask(QString("HH:HH:HH:HH:HH:HH;"));

	ui->label->setText(GET_TXT("IDCS_IP_ADDR"));
	ui->label_2->setText(GET_TXT("IDCS_IP_MASK"));
	ui->label_3->setText(GET_TXT("IDCS_IP_GATEWAY"));
	ui->label_4->setText(GET_TXT("IDCS_MAC_ADDR"));
	ui->label_5->setText(GET_TXT("IDCS_UDP_PORT"));
	ui->label_6->setText(GET_TXT("IDCS_TCP_PORT"));
	ui->pushButton->setText(GET_TXT("IDCS_QUERY"));
	ui->pushButton_2->setText(GET_TXT("IDCS_SET"));

	mFirst = true;

	connect( mSetBtn, SIGNAL( clicked()), this, SLOT( slot_SetBtnClicked( ) ) );
	connect( mQurBtn, SIGNAL( clicked()), this, SLOT( slot_QueryBtnClicked( ) ) );
}

NetConfigFor6CDlg::~NetConfigFor6CDlg()
{
    delete ui;
}

void NetConfigFor6CDlg::slot_QueryBtnClicked()
{
	QueryAll();
}

void NetConfigFor6CDlg::slot_SetBtnClicked()
{
	SetAll();
}

bool NetConfigFor6CDlg::QueryAll()
{
	bool bRet = QueryIp();
	if (bRet)
	{
		bRet = QueryUdpPort();
	}
	if (bRet)
	{
		bRet = QueryTcpPort();
	}
	if (bRet)
	{
		bRet = QueryMac();
	}
	return bRet;
}

bool NetConfigFor6CDlg::QueryIp()
{
	bool bRet = false;

	ReaderDllBase*	pReaderDllBase = pMainApp->GetReader();	
	if (!pReaderDllBase)
	{
		MainShowMsg(GET_TXT("IDCS_READ_NO_LINK"));
		return false;
	}
	if (!pReaderDllBase->CheckState(STATE_CONNET))
	{
		MainShowMsg(GET_TXT("IDCS_READ_NO_LINK"));
		return bRet;
	}

	int iInfoType = 0x02;
	unsigned char btParams[BYTE_BUFFER_SIZE];
	unsigned char size = BYTE_BUFFER_SIZE;

	bRet = SAAT_NetParaQuery(
		pReaderDllBase->m_hCom,
		iInfoType,
		btParams,
		&size) ;

	if (bRet)
	{
		DWORD dwIPAddr,dwSubNet,dwGate;
		memcpy(&dwIPAddr,btParams,4);
		memcpy(&dwSubNet,btParams+4,4);
		memcpy(&dwGate,btParams+4+4,4);
		in_addr ia;
		memcpy(&ia,&dwIPAddr,4);
		mIpAddrEdit->setText(QString::fromUtf8(inet_ntoa(ia)));
		memcpy(&ia,&dwSubNet,4);
		mMaskEdit->setText(QString::fromUtf8(inet_ntoa(ia)));
		memcpy(&ia,&dwGate,4);
		mGatewayEdit->setText(QString::fromUtf8(inet_ntoa(ia)));

		MainShowMsg(GET_TXT("IDCS_NET_QUERY_SUCCESS"));
	}
	else
	{
		MainShowMsg(GET_TXT("IDCS_NET_QUERY_FAILED"),true);
	}

	return bRet;
}

bool NetConfigFor6CDlg::QueryUdpPort()
{
	bool bRet = false;

	ReaderDllBase*	pReaderDllBase = pMainApp->GetReader();	
	if (!pReaderDllBase)
	{
		MainShowMsg(GET_TXT("IDCS_READ_NO_LINK"));
		return false;
	}
	if (!pReaderDllBase->CheckState(STATE_CONNET))
	{
		MainShowMsg(GET_TXT("IDCS_READ_NO_LINK"));
		return bRet;
	}

	int iInfoType = 0x04;
	unsigned char btParams[BYTE_BUFFER_SIZE];
	unsigned char size = BYTE_BUFFER_SIZE;

	bRet = SAAT_NetParaQuery(
		pReaderDllBase->m_hCom,
		iInfoType,
		btParams,
		&size) ;

	if (bRet)
	{
		DWORD dwSocket;
		memcpy(&dwSocket,btParams,size);
		int Port = MAKEWORD(btParams[1],btParams[0]);	
		mUdpEdit->setText(QString("%1").arg(Port));

		MainShowMsg(GET_TXT("IDCS_UDP_PORT_QUERY_SUCCESS"));
	}
	else
	{
		MainShowMsg(GET_TXT("IDCS_UDP_PORT_QUERY_FAILED"),true);
	}
	return bRet;
}

bool NetConfigFor6CDlg::QueryTcpPort()
{
	bool bRet = false;

	ReaderDllBase*	pReaderDllBase = pMainApp->GetReader();	
	if (!pReaderDllBase)
	{
		MainShowMsg(GET_TXT("IDCS_READ_NO_LINK"));
		return false;
	}
	if (!pReaderDllBase->CheckState(STATE_CONNET))
	{
		MainShowMsg(GET_TXT("IDCS_READ_NO_LINK"));
		return bRet;
	}

	int iInfoType = 0x03;
	unsigned char btParams[BYTE_BUFFER_SIZE];
	unsigned char size = BYTE_BUFFER_SIZE;

	bRet = SAAT_NetParaQuery(
		pReaderDllBase->m_hCom,
		iInfoType,
		btParams,
		&size) ;

	if (bRet)
	{
		DWORD dwSocket;
		memcpy(&dwSocket,btParams,size);
		int Port = MAKEWORD(btParams[1],btParams[0]);	
		mTcpEdit->setText(QString("%1").arg(Port));

		MainShowMsg(GET_TXT("IDCS_TCP_PORT_QUERY_SUCCESS"));
	}
	else
	{
		MainShowMsg(GET_TXT("IDCS_TCP_PORT_QUERY_FAILED"),true);
	}
	return bRet;
}

bool NetConfigFor6CDlg::QueryMac()
{
	bool bRet = false;

	ReaderDllBase*	pReaderDllBase = pMainApp->GetReader();	
	if (!pReaderDllBase)
	{
		MainShowMsg(GET_TXT("IDCS_READ_NO_LINK"));
		return false;
	}
	if (!pReaderDllBase->CheckState(STATE_CONNET))
	{
		MainShowMsg(GET_TXT("IDCS_READ_NO_LINK"));
		return bRet;
	}

	int iInfoType = 0x01;
	unsigned char btParams[BYTE_BUFFER_SIZE];
	unsigned char size = BYTE_BUFFER_SIZE;

	bRet = SAAT_NetParaQuery(
		pReaderDllBase->m_hCom,
		iInfoType,
		btParams,
		&size) ;

	if (bRet)
	{
		mMacEdit->setText(
			QString("%1:%2:%3:%4:%5:%6")
			.arg(btParams[0],2,16,QLatin1Char('0')).toUpper()
			.arg(btParams[1],2,16,QLatin1Char('0')).toUpper()
			.arg(btParams[2],2,16,QLatin1Char('0')).toUpper()
			.arg(btParams[3],2,16,QLatin1Char('0')).toUpper()
			.arg(btParams[4],2,16,QLatin1Char('0')).toUpper()
			.arg(btParams[5],2,16,QLatin1Char('0')).toUpper()
			);

		MainShowMsg(GET_TXT("IDCS_MAC_ADDR_QUERY_SUCCESS"));
	}
	else
	{
		MainShowMsg(GET_TXT("IDCS_MAC_ADDR_QUERY_FAILED"),true);
	}

	return bRet;
}

bool NetConfigFor6CDlg::SetAll()
{
	bool bRet = SetIp();
	if (bRet)
	{
		bRet = SetUdpPort();
	}
	if (bRet)
	{
		bRet = SetTcpPort();
	}
	if (bRet)
	{
		bRet = SetMac();
	}
	return bRet;
}

bool NetConfigFor6CDlg::SetIp()
{
	bool bRet = false;

	ReaderDllBase*	pReaderDllBase = pMainApp->GetReader();	
	if (!pReaderDllBase)
	{
		MainShowMsg(GET_TXT("IDCS_READ_NO_LINK"));
		return false;
	}
	if (!pReaderDllBase->CheckState(STATE_CONNET))
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

	byte btParams[52];
	ZeroMemory(btParams,52);

	QStringList tmpList = mIpAddrEdit->text().split(".");
	if (tmpList.size() < 4)
	{
		MainShowMsg(GET_TXT("IDCS_IP_ERRO"));
		return bRet;
	}

	btParams[0] = tmpList.at(0).toUInt();
	btParams[1] = tmpList.at(1).toUInt();
	btParams[2] = tmpList.at(2).toUInt();
	btParams[3] = tmpList.at(3).toUInt();

	tmpList = mMaskEdit->text().split(".");
	if (tmpList.size() < 4)
	{
		MainShowMsg(GET_TXT("IDCS_SUBMASK_ERRO"));
		return bRet;
	}
	btParams[4] = tmpList.at(0).toUInt();
	btParams[5] = tmpList.at(1).toUInt();
	btParams[6] = tmpList.at(2).toUInt();
	btParams[7] = tmpList.at(3).toUInt();

	tmpList = mGatewayEdit->text().split(".");
	if (tmpList.size() < 4)
	{
		MainShowMsg(GET_TXT("IDCS_GATEWAY_ERRO"));
		return bRet;
	}
	btParams[8] = tmpList.at(0).toUInt();
	btParams[9] = tmpList.at(1).toUInt();
	btParams[10] = tmpList.at(2).toUInt();
	btParams[11] = tmpList.at(3).toUInt();

	unsigned char nType = 0x02;
	bRet = SAAT_NetParaSet(pReaderDllBase->m_hCom,
		nType,
		btParams,
		12);
	if (bRet)
	{

		MainShowMsg(GET_TXT("IDCS_IP_CONFIG_SUCCESS"));
	}
	else
	{
		MainShowMsg(GET_TXT("IDCS_IP_CONFIG_FAILED"),true);
	}

	return bRet;
}

bool NetConfigFor6CDlg::SetUdpPort()
{
	bool bRet = false;

	ReaderDllBase*	pReaderDllBase = pMainApp->GetReader();	
	if (!pReaderDllBase)
	{
		MainShowMsg(GET_TXT("IDCS_READ_NO_LINK"));
		return false;
	}
	if (!pReaderDllBase->CheckState(STATE_CONNET))
	{
		MainShowMsg(GET_TXT("IDCS_READ_NO_LINK"));
		return bRet;
	}

	byte nType = 0x04;
	byte nSize = 0x02;
	byte byteData[BYTE_BUFFER_SIZE];
	ZeroMemory(byteData,0);

	DWORD dSocketPort = mUdpEdit->text().toUInt();
	WORD dLoSocketPort =  LOWORD(dSocketPort);
	byteData[0] = HIBYTE(dLoSocketPort);
	byteData[1] = LOBYTE(dLoSocketPort);
	bRet = SAAT_NetParaSet(
		pReaderDllBase->m_hCom,
		nType,
		byteData,
		nSize);

	if (bRet)
	{
		MainShowMsg(GET_TXT("IDCS_UDP_PORT_SET_SUCCESS"));
	}
	else
	{
		MainShowMsg(GET_TXT("IDCS_UDP_PORT_SET_FAILED"),true);
	}

	return bRet;
}

bool NetConfigFor6CDlg::SetTcpPort()
{
	bool bRet = false;

	ReaderDllBase*	pReaderDllBase = pMainApp->GetReader();	
	if (!pReaderDllBase)
	{
		MainShowMsg(GET_TXT("IDCS_READ_NO_LINK"));
		return false;
	}
	if (!pReaderDllBase->CheckState(STATE_CONNET))
	{
		MainShowMsg(GET_TXT("IDCS_READ_NO_LINK"));
		return bRet;
	}

	byte nType = 0x03;
	byte nSize = 0x02;
	byte byteData[BYTE_BUFFER_SIZE];
	ZeroMemory(byteData,0);

	DWORD dSocketPort = mTcpEdit->text().toUInt();
	WORD dLoSocketPort =  LOWORD(dSocketPort);
	byteData[0] = HIBYTE(dLoSocketPort);
	byteData[1] = LOBYTE(dLoSocketPort);
	bRet = SAAT_NetParaSet(
		pReaderDllBase->m_hCom,
		nType,
		byteData,
		nSize);

	if (bRet)
	{
		MainShowMsg(GET_TXT("IDCS_TCP_PORT_SET_SUCCESS"));
	}
	else
	{
		MainShowMsg(GET_TXT("IDCS_TCP_PORT_SET_FAILED"),true);
	}

	return bRet;
}

bool NetConfigFor6CDlg::SetMac()
{
	bool bRet = false;

	ReaderDllBase*	pReaderDllBase = pMainApp->GetReader();	
	if (!pReaderDllBase)
	{
		MainShowMsg(GET_TXT("IDCS_READ_NO_LINK"));
		return false;
	}
	if (!pReaderDllBase->CheckState(STATE_CONNET))
	{
		MainShowMsg(GET_TXT("IDCS_READ_NO_LINK"));
		return bRet;
	}

	byte nType = 0x01;
	byte nSize = 0x06;
	byte byteData[BYTE_BUFFER_SIZE];
	ZeroMemory(byteData,0);

	QString strMac = mMacEdit->text();

	QStringList tmpList = strMac.split(":");
	if (tmpList.size() < 6)
	{
		MainShowMsg(GET_TXT("IDCS_MAC_FARMOT_ERRO"));
		return bRet;
	}

	bool isOk;
	byteData[0] = tmpList.at(0).toUInt(&isOk,16);
	byteData[1] = tmpList.at(1).toUInt(&isOk,16);
	byteData[2] = tmpList.at(2).toUInt(&isOk,16);
	byteData[3] = tmpList.at(3).toUInt(&isOk,16);
	byteData[4] = tmpList.at(4).toUInt(&isOk,16);
	byteData[5] = tmpList.at(5).toUInt(&isOk,16);

	bRet = SAAT_NetParaSet(
		pReaderDllBase->m_hCom,
		nType,
		byteData,
		nSize);

	if (bRet)
	{
		MainShowMsg(GET_TXT("IDCS_MAC_SET_SUCCESS"));
	}
	else
	{
		MainShowMsg(GET_TXT("IDCS_MAC_SET_FAILED"),true);
	}

	return bRet;
}

void NetConfigFor6CDlg::showEvent(QShowEvent *event)
{
	ReaderDllBase*	pReaderDllBase = pMainApp->GetReader();	
	if (!pReaderDllBase)
	{
		return;
	}

	if (pReaderDllBase->GetState() == STATE_READING ||
		pReaderDllBase->GetState() == STATE_DISCONNET ||
		pReaderDllBase->GetState() == STATE_DISABLE)
	{
		return;
	}
	if (mFirst)
	{
		mFirst = !QueryAll();
	}

	QWidget::showEvent(event);
}

bool NetConfigFor6CDlg::CheckIPEdit(const QString& str)
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
