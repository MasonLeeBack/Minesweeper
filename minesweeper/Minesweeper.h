/*

Minesweeper Decompilation

*/

#ifndef _MINESWEEPER_H_
#define _MINESWEEPER_H_

// Engine includes
#include <engine.h>
#include <rendermanager.h>

// Game includes
#include "Board.h"
#include "Game.h"
#include "GameStat.h"
#include "GameStats.h"
#include "HighScore.h"
#include "Minesweeper_const.h"
#include "MSLog.h"
#include "SerialXML.h"
#include "UIBoardCanvas.h"
#include "UIDialogs.h"
#include "UITile.h"

// Default engine handler class
class EngineHandler : public IEngineInterface {
  const wchar_t* GetProjectName();
  wchar_t* GetWindowTitle();

  const wchar_t* GetResourceDllFileName();
  void GetInitialLayout(unsigned int* width, unsigned int* height);

  bool InitializeGameCode();
  void UpdateGameCode();

  int GetWindowMenu();
  const wchar_t* GetGdfPath();
};

#endif // _MINESWEEPER_H_
