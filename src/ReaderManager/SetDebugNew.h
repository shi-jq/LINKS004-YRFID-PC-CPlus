﻿#ifndef SET_DEBUG_NEW_H
#define SET_DEBUG_NEW_H

#ifdef _DEBUG
#define DEBUG_CLIENTBLOCK new(_CLIENT_BLOCK, __FILE__,__LINE__)
#else
#define  DEBUG_CLIENTBLOCK
#endif

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <malloc.h>
#include <crtdbg.h>

#ifdef _DEBUG
#define  new DEBUG_CLIENTBLOCK
#endif

#if defined(WIN32)  
	void setFilterDebugHook(void);  
#endif  


#endif