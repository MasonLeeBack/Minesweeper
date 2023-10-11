/*

Minesweeper Decompilation

File name:
  SerialXML.h

*/

#ifndef _SERIALXML_H_
#define _SERIALXML_H_

class Stash {

};

class SerialXML {
public:
  void PrintTabs();

  void ToXML(int i, const wchar_t* tag);
  void ToXML(float f, const wchar_t* tag);
  void ToXML(unsigned int u, const wchar_t* tag);
  void ToXML(bool b, const wchar_t* tag);
  void ToXML(__int64 i, const wchar_t* tag);

  void WriteStartTag(const wchar_t* tag, bool bNewLine);
  void WriteEndTag(const wchar_t* tag, bool bNewLine);
};

#endif // _SERIALXML_H_
