// RFIDAPI.cpp : ���� DLL Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "RFIDReaderManager.h"

#ifdef _MANAGED
#pragma managed(push, off)
#endif

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch ( ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
			{
				CRFIDReaderManager::Instance();
			}
			break;
		case DLL_PROCESS_DETACH:
			{
				delete CRFIDReaderManager::Instance();
			}
			break;
		case DLL_THREAD_ATTACH:
			{
				
			}
			break;
		case DLL_THREAD_DETACH:
			{
				
			}
			break;
	}
    return TRUE;
}

#ifdef _MANAGED
#pragma managed(pop)
#endif

