/*

Minesweeper Decompilation

File name:
  GameStats.cpp

*/

#include "GameStats.h"
#include "SerialXML.h"

GameStats::GameStats()
{
  for (unsigned int i = 4; i != 0; --i) {
    GameStat* stat = new GameStat();
    m_pIndividualStats.Add(stat);
  }
}

GameStats::~GameStats()
{
  for (int i = 0; i <= 3; ++i) {
    if (m_pIndividualStats.data[i]) {
      delete m_pIndividualStats.data[i];
      m_pIndividualStats.data[i] = 0;
    }
  }
}

GameStat* GameStats::GetGameStat(EDifficulty difficulty)
{
  return m_pIndividualStats.data[(int)difficulty - 1];
}

bool GameStats::AddNewScore(EDifficulty difficulty, int time, bool bWon)
{
  if (((int)difficulty - 1) > 2)
    return false;
  else
    return m_pIndividualStats.data[(int)difficulty - 1]->AddNewGameScore(time, bWon);
}

void GameStats::ToXML(SerialXML* xmlFile)
{
  xmlFile->WriteStartTag(L"GameStats", true);
  xmlFile->ToXML((int)&m_pIndividualStats, L"IndividualStats");
  xmlFile->WriteEndTag(L"GameStats", true);
}

bool GameStats::IsEmpty()
{
  return m_pIndividualStats.data[0]->IsEmpty() &&
    m_pIndividualStats.data[1]->IsEmpty() &&
    m_pIndividualStats.data[2]->IsEmpty();
}
