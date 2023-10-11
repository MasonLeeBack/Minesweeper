/*

Minesweeper Decompilation

*/

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <utils.h>
#include "Minesweeper.h"

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

  g_Game->SetSoundEnabled(g_Game->bSoundEnabled);
  g_Game->SetAnimationsEnabled(g_Game->bAnimationsEnabled);
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

const wchar_t* EngineHandler::GetGdfPath()
{
  return L"\\Microsoft Games\\Minesweeper\\Minesweeper.exe";
}
