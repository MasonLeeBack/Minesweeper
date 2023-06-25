/*

Minesweeper Decompilation

*/

#ifndef _BOARD_H_
#define _BOARD_H_

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

  void ResetBoard();

  Board(int difficulty, int width, int height, int totalMines, int seed, int firstclickx, int firstclicky, bool placeMines);
};

#endif // _BOARD_H_
 