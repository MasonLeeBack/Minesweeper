/*

OberEngine Decompilation
Original Game: Purble Place

*/

#ifndef _XMLMANAGER_H_
#define _XMLMANAGER_H_

class XmlNode {
public:
  XmlNode* XPathElementSearch(const wchar_t* element, int* unk1);
  wchar_t* XPathAttributeSearchSingle(const wchar_t* element);
};

class XmlManager
{
public:
  XmlNode* GetXml(const wchar_t* szFileName);
  XmlNode* Load(const wchar_t* szFileName);
};


extern XmlManager* g_pXmlManager;

#endif // _XMLMANAGER_H_
