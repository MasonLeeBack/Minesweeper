/*

Minesweeper Decompilation

*/

#include "HighScore.h"

HighScore::HighScore()
{
  this->m_Score = 0;
  _time64(&m_Time);
}

HighScore::~HighScore()
{
}

void HighScore::ToXML(SerialXML* xml)
{
  xml->WriteStartTag(L"HighScore", true);
  xml->ToXML(m_Score, L"Score");
  xml->ToXML(m_Time, L"Time");
  xml->WriteEndTag(L"HighScore", true);
}

Str* HighScore::GetFormattedScore(Str* retStr)
{
  retStr->FromNumber(m_Score);
  return retStr;
}
