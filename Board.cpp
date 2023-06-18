/*

Minesweeper Decompilation

*/

#include "Board.h"

int Board::GetMineableTileCount(int a1, int a2)
{
  return a2 * a1 - 9;
}

void Board::ResetBoard()
{
  TimeElapsed = 0.0f;
  Mines = 0;
  Height = 0;
  Width = 0;
  Difficulty = 0;
  FlagsPlaced = 0;
  RevealedSquares = 0;
  RevealsAttempted = 0;
  FirstXClickPos = 0;
  FirstYClickPos = 0;
  RandSeed = 0;
  freeRes();
}
