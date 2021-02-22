#include "StdAfx.h"
#include "IConnect.h"

IConnect::IConnect()
{
	m_pDataPrcoessInterface = NULL;
	pHandle = NULL;
}

IConnect::~IConnect(void)
{
}

void IConnect::SetErrorCode(int nErrorCode,bool bCommandError )
{
	if( m_pDataPrcoessInterface != NULL )
	{
		m_pDataPrcoessInterface->SetErrorCode(nErrorCode);
	}
}

