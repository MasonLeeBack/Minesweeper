/*

OberEngine Decompilation

*/

#include "oberlib.h"

bool DialogHelper::Init(HINSTANCE hInstance, HWND hWnd, bool bIsMediaCenter)
{
  HMODULE hCommonControl;
  OSVERSIONINFO versionInformation;

  if (!hInstance)
    return false;

  m_hInstance = hInstance;
  m_hWnd = hWnd;
  m_bIsMediaCenter = bIsMediaCenter;

  if (!m_hTaskDialogDll) {
    hCommonControl = LoadLibrary(L"comctl32");
    m_hTaskDialogDll = hCommonControl;

    if (hCommonControl) {

      m_TaskDialogIndirect = TaskDialogIndirect;
      if (m_TaskDialog || TaskDialogIndirect) {
        versionInformation.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
        if (GetVersionEx(&versionInformation) &&
          versionInformation.dwMajorVersion >= 6 &&
          versionInformation.dwMinorVersion == 0 &&
          versionInformation.dwPlatformId == 2 &&
          versionInformation.dwBuildNumber < 5244)
        {
          m_TaskDialogOld = m_TaskDialog;
          m_TaskDialog = 0;
          m_TaskDialogIn
        }
      }
    }

    m_bRTL = IsRTL();
    m_DlgTemplateAlloc = 3000;
    m_hWritableTemplate = GlobalAlloc(GMEM_ZEROINIT, 3000);
    m_hLastFocus = NULL;
  }


  return true;
}
