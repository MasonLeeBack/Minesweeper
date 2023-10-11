/*

Minesweeper Decompilation

*/

#ifndef _MINESWEEPER_CONST_H_
#define _MINESWEEPER_CONST_H_

#include <str.h>

enum EDifficulty {
  DIFFICULTY_BEGINNER = 1,
  DIFFICULTY_INTERMEDIATE = 2,
  DIFFICULTY_ADVANCED = 3,
  DIFFICULTY_CUSTOM = 4,
};

int EDifficultyToWidth(EDifficulty difficulty);
int EDifficultyToHeight(EDifficulty difficulty);
int EDifficultyToMineCount(EDifficulty difficulty);
Str* EDifficultyToStr(EDifficulty difficulty);
Str* EDifficultyToLocalizedStr(EDifficulty difficulty);

enum ETileStatus {
  TILESTATUS_NONE = 0,
  TILESTATUS_FLAGGED = 1,
  TILESTATUS_QUESTION = 2,
  TILESTATUS_REVEALED = 3,
};



#endif // _MINESWEEPER_CONST_H_
