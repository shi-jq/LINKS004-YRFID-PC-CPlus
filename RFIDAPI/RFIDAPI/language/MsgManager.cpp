#include "StdAfx.h"
#include "ErrorMsgFactory.h"
#include "MsgManager.h"

CMsgManager::CMsgManager(void)
{
}

CMsgManager::~CMsgManager(void)
{
	map <string, IGetMsgInterface*> :: const_iterator m1_AcIter = mapLanguage.begin();
	for( ; m1_AcIter != mapLanguage.end() ; m1_AcIter++)
	{
		IGetMsgInterface* IMsgIF = m1_AcIter->second;
		delete IMsgIF;
		IMsgIF = NULL;
	}
	mapLanguage.clear();
}


void CMsgManager::GetErrorMessage(string strType,int nCode,string& strMessage)
{
	map <string, IGetMsgInterface*> :: const_iterator m1_AcIter, m1_RcIter;
	typedef pair <string, IGetMsgInterface*> Int_Pair;

	if( strType == "cn" || strType == "tw" || strType == "en") //÷–∑±”¢
	{
		m1_RcIter = mapLanguage.find(strType);
		if ( m1_RcIter == mapLanguage.end() )
		{
			CErrorMsgFactory factory;
			IGetMsgInterface* IMsgIF = factory.ConcreteConn(strType);
			if( NULL != IMsgIF )
			{
				mapLanguage.insert( Int_Pair(strType,IMsgIF) );
			}
		}
		
		IGetMsgInterface* IMsgIF = mapLanguage[strType];
		IMsgIF->GetErrorMsg(nCode,strMessage);
		
	}

	//∆‰À˚”Ô—‘
	
}
