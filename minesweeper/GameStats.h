/*

Minesweeper Decompilation

File name:
  GameStats.h

*/

#ifndef _GAMESTATS_H_
#define _GAMESTATS_H_

#include "GameStat.h"
#include "Minesweeper_const.h"

#include <array.h>

class GameStats {
private:
  Array<GameStat*> m_pIndividualStats;
public:
  GameStats();
  ~GameStats();

  GameStat* GetGameStat(EDifficulty difficulty);
  bool AddNewScore(EDifficulty difficulty, int time, bool bWon);

  void ToXML(class SerialXML* xmlFile);
  bool IsEmpty();
};

#endif // _GAMESTATS_H_
