/*

Minesweeper Decompilation

File name:
  GameStat.h

*/

#ifndef _GAMESTAT_H_
#define _GAMESTAT_H_

#include "HighScore.h"
#include <array.h>

class GameStat {
private:
  unsigned int m_GamesWon;
  unsigned int m_GamesPlayed;
  unsigned int m_LowestScore;
  unsigned int m_HighestScore;
  unsigned int m_AverageScore;
  unsigned int m_LongestWinStreak;
  unsigned int m_LongestLoseStreak;
  unsigned int m_CurrentStreak;
  bool m_bCurrentStreakTypeIsWin;
  Array<HighScore*> m_pHighScores;
public:
  GameStat();
  ~GameStat();

  int GetPercentWon();
  bool IsEmpty();

  HighScore* GetHighScore(int index);
  bool attemptAddNewHighScore(int score);
  bool AddNewGameScore(int score, bool bWon);

  void freeRes();
  void Reset(bool bFree);

  void ToXML(class SerialXML* xmlFile);
  void FromXML(class SerialXML* xmlFile, class XmlNode* xmlNode);
};

#endif // _GAMESTAT_H_
