
#include "stdafx.h"

bool ResourceManager::Initialize()
{
  XmlNode* xmlFile;

  if (!wszCache) {
    wszCache = new wchar_t[100];
    CacheCch = 50;
  }

  xmlFile = g_pXmlManager->GetXml(L"SplitList.xml");
  if (!xmlFile) {
    LOG(4, L"No split list found.");
    return true;
  }

  int j, k;
  for (XmlNode* i = xmlFile->XPathElementSearch(L"/Texture", &j); k < j; k++)
  {
    wchar_t* name = i[k].XPathAttributeSearchSingle(L"./@name");
    wchar_t* width = i[k].XPathAttributeSearchSingle(L"./@width");
    wchar_t* height = i[k].XPathAttributeSearchSingle(L"./@height");

    if (name)
    {

    }

    delete[] name;
    delete[] width;
    delete[] height;
  }

  return true;
}
