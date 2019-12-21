// ringzero.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "ringzero.h"
#include <atlstr.h>

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.
#ifdef RUN_TIME_DYNAMIC_LINKING
    m_hOpenLibSys = NULL;
    if (!InitOpenLibSys(&m_hOpenLibSys))
    {
        MessageBox(NULL, _T("DLL Load Error!!!"), _T("Message"), MB_OK);
        return FALSE;
    }
#else
    if (!InitializeOls())
    {
        MessageBox(NULL, _T("Error InitializeOls()!!!"), _T("Message"), MB_OK);
        return FALSE;
    }
#endif

    CString cstr, edit;

    switch (GetDllStatus())
    {
    case OLS_DLL_NO_ERROR:
        MessageBox(NULL, _T("DLL Status Success!"), _T("Message"), MB_OK);
        break;
    case OLS_DLL_UNSUPPORTED_PLATFORM:
        MessageBox(NULL, _T("DLL Status Error!! UNSUPPORTED_PLATFORM"), _T("Message"), MB_OK);
        return 0;
        break;
    case OLS_DLL_DRIVER_NOT_LOADED:
        MessageBox(NULL, _T("DLL Status Error!! DRIVER_NOT_LOADED"), _T("Message"), MB_OK);
        return 0;
        break;
    case OLS_DLL_DRIVER_NOT_FOUND:
        MessageBox(NULL, _T("DLL Status Error!! DRIVER_NOT_FOUND"), _T("Message"), MB_OK);
        return 0;
        break;
    case OLS_DLL_DRIVER_UNLOADED:
        MessageBox(NULL, _T("DLL Status Error!! DRIVER_UNLOADED"), _T("Message"), MB_OK);
        return 0;
        break;
    case OLS_DLL_DRIVER_NOT_LOADED_ON_NETWORK:
        MessageBox(NULL, _T("DLL Status Error!! DRIVER_NOT_LOADED_ON_NETWORK"), _T("Message"), MB_OK);
        return 0;
        break;
    case OLS_DLL_UNKNOWN_ERROR:
    default:
        MessageBox(NULL, _T("DLL Status Error!! UNKNOWN_ERROR"), _T("Message"), MB_OK);
        return 0;
        break;
    }
    BYTE buffer = 0xFF;
    DWORD count = 1L;
    DWORD unitSize = sizeof(BYTE);
    DWORD_PTR address = 0xfed8C428;
    DWORD sizeOfBytesRead = ReadPhysicalMemory(address, &buffer, count, unitSize);
    if (sizeOfBytesRead > 0)
    {
        TCHAR tMessage[MAXCHAR] = { 0 };
        _sntprintf(tMessage, sizeof(tMessage) / sizeof(*tMessage), _T("0x%x=0x%02X"), address, buffer);
        MessageBox(NULL, tMessage, _T("Message"), MB_OK);
    }
#ifdef RUN_TIME_DYNAMIC_LINKING
    DeinitOpenLibSys(&m_hOpenLibSys);
#else
    DeinitializeOls();
#endif

    return (0);
}

