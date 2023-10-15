/*

OberEngine Decompilation

*/

#ifndef _DIALOGHELPER_H_
#define _DIALOGHELPER_H_

#include <gdiplus.h>

namespace DialogHelper {
  extern HINSTANCE m_hInstance;
  extern bool m_bIsMediaCenter;
  extern bool m_bRTL;
  extern bool m_bMouseOverCtl;
  extern HWND m_hLastFocus;
  extern HWND m_hHotCtl;
  extern HGDIOBJ m_hFont;
  extern HDC m_uiTitle;
  extern Gdiplus::Image* m_Background;

  bool Init(HINSTANCE hInstance, HWND hWnd, bool bIsMediaCenter);
};

#endif // _DIALOGHELPER_H_
