/*

Minesweeper Decompilation

File name:
  SerialXML.h

*/

#ifndef _SERIALXML_H_
#define _SERIALXML_H_

#include "Stash.h"
#include "Minesweeper_const.h"

#include <str.h>
#include <xmlmanager.h>

class GameStat;

class SerialXML {
  int m_IndentLength; // 0x0;
  Str field_4; // 0x4;
  XmlNode* field_10; // 0x10
  Stash field_14; // 0x14

public:
  SerialXML();
  ~SerialXML();

  void Cleanup();
  void Reset();

  void PrintTabs();

  void ToXML(int i, const wchar_t* tag);
  bool FromXML(int& i, const XmlNode* node);

  void ToXML(float f, const wchar_t* tag);
  bool FromXML(float& f, const XmlNode* node);

  void ToXML(unsigned int u, const wchar_t* tag);
  bool FromXML(unsigned int& u, const XmlNode* node);

  void ToXML(bool b, const wchar_t* tag);
  bool FromXML(bool& b, const XmlNode* node);

  void ToXML(__int64 i, const wchar_t* tag);
  bool FromXML(__int64& i, const XmlNode* node);

  void ToXML(Array<Array<ETileStatus>*>* a, const wchar_t* tag);
  bool FromXML(Array<Array<ETileStatus>*>*& a, const XmlNode* node);

  void ToXML(Array<Array<bool>*>* a, const wchar_t* tag);
  bool FromXML(Array<Array<bool>*>*& a, const XmlNode* node);

  void ToXML(Array<GameStat*>& a, const wchar_t* tag);
  bool FromXML(Array<Array<bool>*>*& a, const XmlNode* node);

  void ToXML(EDifficulty d, const wchar_t* tag);
  bool FromXML(EDifficulty& d, const XmlNode* node);

  void WriteStartTag(const wchar_t* tag, bool bNewLine);
  void WriteEndTag(const wchar_t* tag, bool bNewLine);
};

#endif // _SERIALXML_H_
