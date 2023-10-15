/*

Minesweeper Decompilation

*/

#include "Minesweeper_const.h"
#include "MSLog.h"

int EDifficultyToWidth(EDifficulty difficulty)
{
  switch (difficulty) {
    case EDifficulty::Beginner:
      return 9;
    case EDifficulty::Intermediate:
      return 16;
    case EDifficulty::Advanced:
      return 30;
    default:
      StrErr(Str(L"Invalid difficulty", 1));
      return 9;
  }
}

int EDifficultyToHeight(EDifficulty difficulty)
{
  return 0;
}

int EDifficultyToMineCount(EDifficulty difficulty)
{
  return 0;
}

Str* EDifficultyToStr(EDifficulty difficulty)
{
  return nullptr;
}

Str* EDifficultyToLocalizedStr(EDifficulty difficulty)
{
  return nullptr;
}
