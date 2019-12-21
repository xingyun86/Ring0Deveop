// header.h : include file for standard system include files,
// or project specific include files
//

#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>
// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#ifndef _PHYSICAL_MEMORY_SUPPORT
#define _PHYSICAL_MEMORY_SUPPORT
#endif // !_PHYSICAL_MEMORY_SUPPORT

#include <OlsDef.h>

#ifdef RUN_TIME_DYNAMIC_LINKING
#include <OlsApiInitExt.h>
#else // for Load-Time Dynamic Linking
#include <OlsApi.h>
#endif