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
    mIpEdit = ui->lineEdit;
    mPortEdit = ui->lineEdit_2;

    connect(mReadForwardBtn,SIGNAL(clicked()), this ,SLOT(slot_ReadForwardBtnClicked()));
    connect(mWriteForwardBtn,SIGNAL(clicked()), this ,SLOT(slot_WriteForwardBtnClicked()));
}

ForwardSetDlg::~ForwardSetDlg()
{
    delete ui;
}

void ForwardSetDlg::slot_ReadForwardBtnClicked()
{
	QueryAll();

}

void ForwardSetDlg::slot_WriteForwardBtnClicked()
{
	ReaderDllBase*	pReaderDllBase = pMainApp->GetReader();
	if (!pReaderDllBase)
	{
		MainShowMsg(GET_TXT("IDCS_READ_NO_LINK"));
		return;
	}
	if (!pReaderDllBase->CheckState(STATE_CONNET))
	{
		MainShowMsg(GET_TXT("IDCS_READ_NO_LINK"));
		return;
	}

	bool bRet = true;
	if (bRet)
	{
		bRet = SetIpAddr();
	}

	if (bRet)
	{
		bRet = SetDSCPort();
	}

	if (bRet)
	{
		MainShowMsg(GET_TXT("IDCS_SET_SUCCESS"));
	}
	else
	{
		MainShowMsg(GET_TXT("IDCS_SET_FAILED"), true);
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


bool ForwardSetDlg::QueryAll()
{
	ReaderDllBase*	pReaderDllBase = pMainApp->GetReader();
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

	bool bRet = true;
	if (bRet)
	{
		bRet = QueryIpAddr();
	}

	if (bRet)
	{
		bRet = QueryPort();
	}

	if (bRet)
	{
		MainShowMsg(GET_TXT("IDCS_QUERY_SUCCESS"));
	}
	else
	{

		MainShowMsg(GET_TXT("IDCS_QUERY_FAILED"), true);
	}

	return bRet;
}

bool ForwardSetDlg::QueryIpAddr()
{
	ReaderDllBase*	pReaderDllBase = pMainApp->GetReader();
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

	unsigned char btAddr = 126;	//设备名称起始地址
	unsigned char nDataLen = 20;//长度
	unsigned char btExportData[20];
	ZeroMemory(btExportData, 20);
	unsigned char nBufferSize = 20;

	btAddr = 250;		//IP地址起始地址
	nDataLen = 4;		//IP地址长度
	ZeroMemory(btExportData, 20);
	nBufferSize = 20;
	bool bRet = SAAT_ParmOp(pReaderDllBase->m_hCom,
		0x02,
		btAddr,
		nDataLen,
		btExportData,
		&nBufferSize);

	if (bRet)
	{
		in_addr ia;
		memcpy(&ia, &btExportData, 4);
		mIpEdit->setText(QString::fromUtf8(inet_ntoa(ia)));
	}

	return bRet;
}

bool ForwardSetDlg::QueryPort()
{
	ReaderDllBase*	pReaderDllBase = pMainApp->GetReader();
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

	unsigned char btAddr = 126;	//设备名称起始地址
	unsigned char nDataLen = 20;//长度
	unsigned char btExportData[20];
	ZeroMemory(btExportData, 20);
	unsigned char nBufferSize = 20;

	btAddr = 254;		//端口号起始地址
	nDataLen = 2;		//端口号长度
	ZeroMemory(btExportData, 20);
	nBufferSize = 20;
	bool bRet = SAAT_ParmOp(pReaderDllBase->m_hCom,
		0x02,
		btAddr,
		nDataLen,
		btExportData,
		&nBufferSize);

	if (bRet)
	{
		int gprsPort = MAKEWORD(btExportData[1], btExportData[0]);
		mPortEdit->setText(QString("%1").arg(gprsPort));
	}

	return bRet;
}

bool ForwardSetDlg::SetIpAddr()
{
	ReaderDllBase*	pReaderDllBase = pMainApp->GetReader();
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

	if (!CheckIPEdit(mIpEdit->text()))
	{
		MainShowMsg(GET_TXT("IDCS_IPADDR_INVAID"));
		return false;
	}

	unsigned char btParams[16];
	ZeroMemory(btParams, 16);

	QStringList tmpList = mIpEdit->text().split(".");
	if (tmpList.size() < 4)
	{
		MainShowMsg(GET_TXT("IDCS_IP_ERRO"));
		return false;
	}

	btParams[0] = tmpList.at(0).toUInt();
	btParams[1] = tmpList.at(1).toUInt();
	btParams[2] = tmpList.at(2).toUInt();
	btParams[3] = tmpList.at(3).toUInt();

	unsigned char btAddr = 126;
	unsigned char nDataLen = 11;
	unsigned char nBufferSize = 16;

	btAddr = 250;	//IP地址参数表中起始地址
	nDataLen = 4;	//IP地址长度
	nBufferSize = 4;

	bool bRet = SAAT_ParmOp(pReaderDllBase->m_hCom,
		0x01,
		btAddr,
		nDataLen,
		btParams,
		&nBufferSize);

	return bRet;
}

bool ForwardSetDlg::SetDSCPort()
{
	ReaderDllBase*	pReaderDllBase = pMainApp->GetReader();

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

	if (mPortEdit->text().isEmpty())
	{
		MainShowMsg(GET_TXT("IDCS_INPUT_EMPTY"));
		return false;
	}

	unsigned char btParams[16] = { 0 };

	unsigned char btAddr = 126;
	unsigned char nDataLen = 11;
	unsigned char nBufferSize = 16;

	btAddr = 254;
	nDataLen = 2;
	nBufferSize = 2;

	ZeroMemory(btParams, 16);
	WORD dLoSocketPort = LOWORD(mPortEdit->text().toUInt());
	btParams[0] = HIBYTE(dLoSocketPort);
	btParams[1] = LOBYTE(dLoSocketPort);

	bool bRet = SAAT_ParmOp(pReaderDllBase->m_hCom,
		0x01,
		btAddr,
		nDataLen,
		btParams,
		&nBufferSize);

	return bRet;
}
