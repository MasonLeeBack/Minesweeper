/*

Minesweeper Decompilation

File name:
  Board.cpp

*/

#include "Board.h"

int Board::GetMineableTileCount(int a1, int a2)
{
  return a2 * a1 - 9;
}

void Board::ToXML(SerialXML* xmlFile)
{
  xmlFile->WriteStartTag(L"Board", true);
  xmlFile->ToXML(3, L"SaveVersion");
  xmlFile->ToXML(Mines, L"Mines");
  xmlFile->ToXML(Height, L"Height");
  xmlFile->ToXML(Width, L"Width");
  xmlFile->ToXML(Difficulty, L"Difficulty");
  xmlFile->ToXML(TimeElapsed, L"TimeElapsed");
  xmlFile->ToXML(FlagsPlaced, L"FlagsPlaced");
  xmlFile->ToXML(RevealedSquares, L"RevealedSquares");
  xmlFile->ToXML(RevealsAttempted, L"RevealsAttempted");
  xmlFile->ToXML(FirstXClickPos, L"FirstXClickPos");
  xmlFile->ToXML(FirstYClickPos, L"FirstYClickPos");
  xmlFile->ToXML(RandSeed, L"RandSeed");
  xmlFile->ToXML((int)&BoardTiles, L"BoardTiles");
  xmlFile->ToXML((int)&BoardMines, L"BoardMines");
  xmlFile->WriteEndTag(L"Board", 1);
}

void Board::StartAlphaAnimation(int a1, int a2, float a3, bool a4)
{
  TileAnimationInfo* info = new TileAnimationInfo(a1, a2, a3, a4);
  BoardNodes.Add(info);
}

UITile* Board::SetTileStatus(int x, int y, ETileStatus status)
{
  return nullptr;
}

void Board::Update(float deltaTime, UIBoardCanvas* canvas)
{
  
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

Board::~Board()
{
  freeRes();
}
