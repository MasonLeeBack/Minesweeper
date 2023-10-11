/*

Minesweeper Decompilation

*/

#ifndef _HIGHSCORE_H_
#define _HIGHSCORE_H_

#include <str.h>
#include <xmlnode.h>
#include "SerialXML.h"

class HighScore
{
public:
  int m_Score;
  __time64_t m_Time;

  HighScore();
  ~HighScore();

  void ToXML(SerialXML* xml);
  bool FromXML(SerialXML* xml, XmlNode* node);

  Str* GetFormattedScore(Str* retStr);
};

#endif // _HIGHSCORE_H_
