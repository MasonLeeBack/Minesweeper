/*

OberEngine Decompilation
Original Game: Purble Place

*/

#include "engine.h"
#include <Windows.h>

bool g_bMediaCenter = false;
bool g_bDoubleDPI = false;

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
