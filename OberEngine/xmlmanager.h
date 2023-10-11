/*

OberEngine Decompilation

File name:
  xmlmanager.h

*/

#ifndef _XMLMANAGER_H_
#define _XMLMANAGER_H_

#include <xmlnode.h>

class XmlManager
{
public:
  XmlNode* GetXml(const wchar_t* szFileName);
  XmlNode* Load(const wchar_t* szFileName);
};

extern XmlManager* g_pXmlManager;

#endif // _XMLMANAGER_H_
