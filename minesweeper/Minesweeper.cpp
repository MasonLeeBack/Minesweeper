/*

Minesweeper Decompilation

*/

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <utils.h>
#include "Minesweeper.h"
#include <localize.h>

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int iCmdShow)
{
  int result;
  EngineHandler* handler;

  HeapSetInformation(0, HeapEnableTerminationOnCorruption, 0, 0);

  if (IsGamePlayable(L"Shell-InBoxGames-Minesweeper-EnableGame") == false)
    return 1;

  handler = new EngineHandler();
  RegisterLogNameResolver(MsLog::MsLogResolver);
  if (InitializeEngine(handler, 0))
    result = 0;
  else
    result = 1;

  if (handler)
    delete handler;

  return result;
}

const wchar_t* EngineHandler::GetProjectName()
{
  return L"Minesweeper";
}

wchar_t* EngineHandler::GetWindowTitle()
{
  static wchar_t wszTitle[512];
  
  if (!wszTitle[0]) {
    if (!LoadStringW(GetModuleHandle(NULL), 0x66, wszTitle, 512)) {
      wcsncpy_s(wszTitle, )
    }
  }

  return nullptr;
}

const wchar_t* EngineHandler::GetResourceDllFileName()
{
  return L"Minesweeper.dll";
}

void EngineHandler::GetInitialLayout(unsigned int* width, unsigned int* height)
{
  int w = 0, h = 0;

  if (Game::SafeGetSingleton())
  {
    if (g_Game->GetCanvasDimensions(&w, &h)) {
      *width = w;
      *height = h;
    }
  }
}

bool EngineHandler::InitializeGameCode()
{
  if (!Game::SafeGetSingleton() || !g_Game->InitUi())
    return false;

  g_Game->SetSoundEnabled(g_Game->m_bSoundEnabled);
  g_Game->SetAnimationsEnabled(g_Game->m_bAnimationsEnabled);
  g_Game->UpdateMenu();
  g_pRenderManager->SetBackground(1, 0xFF000000);
  Engine_ResetTimer();

  return true;
}

void EngineHandler::UpdateGameCode()
{
  if (g_Game)
    g_Game->Update(0.0);
}

int EngineHandler::GetWindowMenu()
{
  return 0xA3;
}

int EngineHandler::GetKeyAcceleratorResId()
{
  return 0xA7;
}

const wchar_t* EngineHandler::GetGdfPath()
{
  return L"\\Microsoft Games\\Minesweeper\\Minesweeper.exe";
}

void EngineHandler::ReportOutOfMemory()
{
  DialogHelper::ShowMessageBox(0x66, 0x67, 1, 0xFFFE, 0, 0, 1);
}

const wchar_t* EngineHandler::GetHelpGUID()
{
  FireHelpEntryDataPoint(L"HELP_ENTRY_ID_GAMES_MINESWEEPER_HELP");
  return L"mshelp://windows/?id=ea853d89-9242-48a8-a655-20c5bf92a90e";
}

GUID* EngineHandler::GetRichGameMediaGameID()
{
  static const GUID sGuid = { 0x89FE5CB3, 0x11CB, 0x489C, {0xAC, 0x0D, 0x0C, 0x0B, 0x67, 0x07, 0xE1, 0xF6} };
  return sGuid;
}

const wchar_t* EngineHandler::GetSplashText()
{
  return L"|41308|SplashScreen|LOADING// Splash screen text";
}

const wchar_t* EngineHandler::GetSplashTextFont()
{
  return L"|63004|SplashScreen|Segoe UI// Splash screen font";
}

int EngineHandler::GetSplashTextFontSize()
{
  wchar_t* sizeLocalized;

  sizeLocalized = LocalizeMessage(L"|63357|SplashScreen|60// Splash screen font size");

  int size = _wtoi(sizeLocalized);
  LocalFree(sizeLocalized);

  return size;
}
