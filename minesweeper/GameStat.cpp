/*

Minesweeper Decompilation

File name:
  GameStat.cpp

*/

#include "GameStat.h"
#include "Game.h"

GameStat::GameStat()
{
  Reset(false);
}

GameStat::~GameStat()
{
  freeRes();
}

int GameStat::GetPercentWon()
{
  if (m_GamesPlayed) {
    return (int)(m_GamesWon / m_GamesPlayed * 100.0);
  }

  return 0;
}

bool GameStat::IsEmpty()
{
  if (m_GamesWon == 0
    && m_GamesPlayed == 0
    && m_LowestScore == 0
    && m_HighestScore == 0
    && m_AverageScore == 0
    && m_LongestWinStreak == 0
    && m_LongestLoseStreak == 0
    && m_CurrentStreak == 0)
  {
    return true;
  }

  return false;
}

HighScore* GameStat::GetHighScore(int index)
{
  return m_pHighScores.data[index];
}

bool GameStat::attemptAddNewHighScore(int score)
{
  bool result;
  HighScore* i, *temp;
  int j;

  HighScore* pScore = new HighScore(score);
  for (i = pScore; j < m_pHighScores.count; ++j) {
    if (!result) {
      if (score >= m_pHighScores.data[j]->m_Score) {
        if (m_pHighScores.data[j] != 0)
          continue;
      }
    }

    if (j == 0) {
      g_Game->field_D9 = true;
    }

    // Get the old high score, replace, and delete
    temp = i;
    i = m_pHighScores.data[j];
    result = true;
    m_pHighScores.data[j] = temp;
  }
  if (i)
    delete i;

  return result;
}

bool GameStat::AddNewGameScore(int score, bool bWon)
{
  if (bWon) {
    attemptAddNewHighScore(score);
  }

  return false;
}

void GameStat::freeRes()
{
  for (unsigned int i = 0; i < m_pHighScores.count; ++i) {
    if (m_pHighScores.data[i]) {
      delete m_pHighScores.data[i];
      m_pHighScores.data[i] = 0;
    }
  }
  m_pHighScores.count = 0;
}

void GameStat::Reset(bool bFree)
{
  if (bFree)
    freeRes();

  m_GamesWon = 0;
  m_GamesPlayed = 0;
  m_LowestScore = 0;
  m_HighestScore = 0;
  m_AverageScore = 0;
  m_LongestWinStreak = 0;
  m_LongestLoseStreak = 0;
  m_CurrentStreak = 0;
  m_bCurrentStreakTypeIsWin = false;

  for (int i = 5; i != 0; --i) {
    HighScore* score = new HighScore(0);
    
    m_pHighScores.Add(score);
  }
}
