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
  xmlFile->ToXML(m_Mines, L"Mines");
  xmlFile->ToXML(m_Height, L"Height");
  xmlFile->ToXML(m_Width, L"Width");
  xmlFile->ToXML((int)m_Difficulty, L"Difficulty");
  xmlFile->ToXML(m_TimeElapsed, L"TimeElapsed");
  xmlFile->ToXML(m_FlagsPlaced, L"FlagsPlaced");
  xmlFile->ToXML(m_RevealedSquares, L"RevealedSquares");
  xmlFile->ToXML(m_RevealsAttempted, L"RevealsAttempted");
  xmlFile->ToXML(m_FirstXClickPos, L"FirstXClickPos");
  xmlFile->ToXML(m_FirstYClickPos, L"FirstYClickPos");
  xmlFile->ToXML(m_RandSeed, L"RandSeed");
  xmlFile->ToXML((int)&m_pBoardTiles, L"BoardTiles");
  xmlFile->ToXML((int)&m_pBoardMines, L"BoardMines");
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
  m_TimeElapsed = 0.0f;
  m_Mines = 0;
  m_Height = 0;
  m_Width = 0;
  m_Difficulty = 0;
  m_FlagsPlaced = 0;
  m_RevealedSquares = 0;
  m_RevealsAttempted = 0;
  m_FirstXClickPos = 0;
  m_FirstYClickPos = 0;
  m_RandSeed = 0;
  freeRes();
}

Board::~Board()
{
  freeRes();
}
