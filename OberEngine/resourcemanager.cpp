/*

OberEngine Decompilation

File name:
  resourcemanager.cpp

*/

#include "stdafx.h"
#include "resourcemanager.h"

#include <string.h>
#include <logger.h>
#include "xmlmanager.h"

bool ResourceManager::Initialize()
{
  XmlNode* xmlFile;

  if (!ResourceBase::wszCache) {
    ResourceBase::wszCache = new wchar_t[100];
    ResourceBase::CacheCch = 50;
  }

  xmlFile = g_pXmlManager->GetXml(L"SplitList.xml");
  if (!xmlFile) {
    LOG(4, L"No split list found.");
    return true;
  }

  int j, k;
  XmlNode* i;
  for (i = xmlFile->XPathElementSearch(L"/Texture", &j); k < j; k++)
  {
    wchar_t* name = i[k].XPathAttributeSearchSingle(L"./@name");
    wchar_t* width = i[k].XPathAttributeSearchSingle(L"./@width");
    wchar_t* height = i[k].XPathAttributeSearchSingle(L"./@height");

    if (name)
    {
      tagPOINT res;
      res.x = wcstol(width, 0, 0);
      res.y = wcstol(height, 0, 0);

      textureDimensions.Add(name, res);
    }

    delete[] name;
    delete[] width;
    delete[] height;
  }
  delete[] i;

  return true;
}

void ResourceManager::Cleanup()
{

  if (ResourceBase::wszCache) {
    delete[] ResourceBase::wszCache;
    ResourceBase::wszCache = 0;
    ResourceBase::CacheCch = 0;
  }
}
