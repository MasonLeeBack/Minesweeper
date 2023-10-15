/*

Minesweeper Decompilation

*/

#ifndef _MINESWEEPER_CONST_H_
#define _MINESWEEPER_CONST_H_

#include <str.h>

enum class EDifficulty {
  Beginner = 1,
  Intermediate = 2,
  Advanced = 3,
  Custom = 4,
};

int EDifficultyToWidth(EDifficulty difficulty);
int EDifficultyToHeight(EDifficulty difficulty);
int EDifficultyToMineCount(EDifficulty difficulty);
Str* EDifficultyToStr(EDifficulty difficulty);
Str* EDifficultyToLocalizedStr(EDifficulty difficulty);

enum class ETileStatus {
  None = 0,
  Flagged = 1,
  Question = 2,
  Revealed = 3,
};

extern int g_iMinesweeperFudge;

#endif // _MINESWEEPER_CONST_H_
