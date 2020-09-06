#include "rebootdeviceform.h"
#include "ui_rebootdeviceform.h"
#include "RFIDAPIEXPORT.h"
#include "readerdllbase.h"
#include "mainapp.h"
#include "LanguageSrc.h"
#include "MessageBox.h"

RebootDeviceForm::RebootDeviceForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RebootDeviceForm)
{
    ui->setupUi(this);

	mRebootBtn = ui->pushButton;

	connect( mRebootBtn, SIGNAL( clicked()), this, SLOT( slot_rebootBtnClicked( ) ) );
}

RebootDeviceForm::~RebootDeviceForm()
{
    delete ui;
}

void RebootDeviceForm::slot_rebootBtnClicked()
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
		return ;
	}

	if (HtMessageBox::Question(GET_TXT("IDCS_READLY_REBOOT_DEVICE"),this)
		!= HtMessageBox::RET_ENTER )
	{
		return;
	}

	bool retB = SAAT_Reboot (
		pReaderDllBase->m_hCom,
		0x00);

	if (retB)
	{		
		pMainApp->CutConnet();		
		MainShowMsg(GET_TXT("IDCS_REBOOT_SUCCESS"));	
	}
	else
	{
		MainShowMsg(GET_TXT("IDCS_REBOOT_FAILED"),true);
	}
}
