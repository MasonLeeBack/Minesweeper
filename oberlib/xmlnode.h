/*

OberEngine Decompilation
Original Game: Purble Place

*/

#ifndef _XMLNODE_H_
#define _XMLNODE_H_

#include "sortedlistw.h"

class XmlNode {
  class XmlString {
  public:
    bool m_bAllocated;
    wchar_t* m_pStr;
    int m_iSize;

    ~XmlString();

    void Cleanup();
  };

public:
  SortedListW<XmlString*> m_StringList; // 0x0
  Array<XmlNode*> m_Children;
  XmlString m_NodeName; // 0x24
  XmlString m_SourceFileName; // 0x34
  XmlString m_NodeValue; // 0x40

  XmlNode* XPathElementSearchSingle(const wchar_t* elementName);

  void SetNodeName(const wchar_t* pName);
  wchar_t* GetNodeName();

  bool GetNodeValue(wchar_t* Dest, unsigned int Size);
  wchar_t* GetNodeValue();

  int GetXmlInt(const wchar_t* pName, int nDefault);
  
  bool MatchName(wchar_t* pName, unsigned int iLength);
  bool MatchName(wchar_t* pName);

  bool GetXmlString(wchar_t* Dest, unsigned int Size, const wchar_t* pName);
  wchar_t* GetXmlStringAlloc(const wchar_t* pName);

  XmlNode* getChild(unsigned int index);
};

#endif // _XMLNODE_H_
