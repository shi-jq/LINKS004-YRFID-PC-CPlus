// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__D6B41DDB_13E4_4235_94CE_7318AF3105E4__INCLUDED_)
#define AFX_STDAFX_H__D6B41DDB_13E4_4235_94CE_7318AF3105E4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <winsock2.h>
//#include <afxtempl.h>
#include <Windows.h>
#include <Mmsystem.h>
#pragma warning(disable:4786)


#define GUARD_ACTION(MUTEX,OBJ,LOCK,ACTION,REACTION) \
	CGuard< MUTEX > OBJ (LOCK); \
	if (OBJ.Locked() != 0) {ACTION;} \
else { REACTION;}

#define GUARD_REACTION(MUTEX , OBJ , LOCK , REACTION) \
GUARD_ACTION(MUTEX, OBJ, LOCK, ;, REACTION)

#define GUARD(MUTEX , OBJ , LOCK) \
GUARD_REACTION(MUTEX,OBJ,LOCK,return)

#define GUARD_RETURN(MUTEX , OBJ , LOCK , RETURN) \
	GUARD_REACTION(MUTEX,OBJ,LOCK,return RETURN)

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__D6B41DDB_13E4_4235_94CE_7318AF3105E4__INCLUDED_)

