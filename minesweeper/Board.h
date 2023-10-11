/*

Minesweeper Decompilation

File name:
  board.h

*/

#ifndef _BOARD_H_
#define _BOARD_H_

#include <array.h>
#include "UITile.h"
#include "SerialXML.h"

class Board {
public:
  int Mines;
  int Height;
  int Width;
  int FlagsPlaced;
  int RevealedSquares;
  int RevealsAttempted;
  float TimeElapsed;
  int Difficulty;
  int FirstXClickPos;
  int FirstYClickPos;
  int RandSeed;

  int var_44;
  int var_48;
  int var_52;
  int var_56;
  int var_60;
  int var_64;
  int var_68;

  Array<TileAnimationInfo*> BoardAnimations;
  Array<UITile*> BoardTiles;
  Array<UITile*> BoardMines;

  int GetMineableTileCount(int a1, int a2);
  int AttemptReveal(int x, int y);

  void ToXML(SerialXML* xmlFile);

  void StartAlphaAnimation(int, int, float, bool);
  UITile* SetTileStatus(int x, int y, ETileStatus status);
  void Update(float deltaTime, class UIBoardCanvas* canvas);

  void ResetBoard();

  Board(int difficulty, int width, int height, int totalMines, int seed, int firstclickx, int firstclicky, bool placeMines);
  ~Board();
};

#endif // _BOARD_H_
 