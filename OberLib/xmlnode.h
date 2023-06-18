/*

OberEngine Decompilation
Original Game: Purble Place

*/

#ifndef _XMLNODE_H_
#define _XMLNODE_H_

class XmlNode {
  class XmlString {
  public:
    bool m_bAllocated;
    wchar_t* m_pStr;

    ~XmlString();

    void Cleanup();

    
  };

public:

  XmlNode* XPathElementSearchSingle(const wchar_t* elementName);

  wchar_t* GetXmlStringAlloc(const wchar_t* pName);
  int GetXmlInt(const wchar_t* pName, int nDefault);
};

#endif // _XMLNODE_H_
