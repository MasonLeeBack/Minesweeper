/*

OberEngine Decompilation

File name:
  engine.cpp

*/

#include "stdafx.h"
#include "engine.h"
#include "rendermanager.h"
#include "timekeeping.h"

bool g_bMediaCenter = false;
bool g_bDoubleDPI = false;
HWND g_hRenderWindow;
unsigned int g_uiLayoutX = 800;
unsigned int g_uiLayoutY = 496;

bool Engine_IsMediaCenter()
{
  return g_bMediaCenter;
}

void Engine_LostFocus()
{
   
}

const wchar_t* IEngineInterface::GetResourceDllFileName()
{
  return L"files.dll";
}

_GUID* IEngineInterface::GetRichGameMediaGameID()
{
  GUID* res = new GUID;
  *res = GUID_NULL;
  return res;
}

void IEngineInterface::GetInitialLayout(unsigned int* width, unsigned int* height)
{
  *width = 800;
  *height = 496;
}

int IEngineInterface::GetContextMenu()
{
  return 0;
}

const wchar_t* IEngineInterface::GetGdfPath()
{
  return NULL;
}

const wchar_t* IEngineInterface::GetSplashTextFont()
{
  return L"Segoe UI";
}

int IEngineInterface::GetSplashTextFontSize()
{
  return 60;
}

bool ShouldGoHighDPI(unsigned int w, unsigned int h)
{
  return w > g_uiLayoutX && h > g_uiLayoutY || Engine_IsMediaCenter() && w > 0x320;
}

void SetDPIFromWindowSize()
{
  RECT Rect;
  
  GetWindowRect(g_hRenderWindow, &Rect);
  if (g_pRenderManager && g_pRenderManager->m_EngineState) {
    if (ShouldGoHighDPI(Rect.right - Rect.left, Rect.bottom - Rect.top) && g_pRenderManager->m_bHighDPI == 1) {
      Engine_SetDPIInternal(true);
    }
    else {
      Engine_SetDPIInternal(false);
    }
  }
}

void Engine_ResetTimer()
{
  Timekeeping::ResetTimers();
}
