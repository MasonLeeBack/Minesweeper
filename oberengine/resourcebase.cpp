/*

OberEngine Decompilation

File name:
  resourcebase.cpp

*/

#include "stdafx.h"
#include "resourcebase.h"

unsigned int ResourceBase::GetPurgeTimeout()
{
  return 35;
}

void ResourceBase::SetNameForDPI(bool)
{
  return;
}

ResourceBase::ResourceBase()
{
  field_14 = 0;
  field_C = 0;
  field_4 = 1;
  field_8 = 0;
  descriptionSize = 0;
  description = NULL;
  pinned = false;
}

void ResourceBase::Cleanup()
{
  field_4 = 0;
  delete[] description;
}

void ResourceBase::VerifyCache(unsigned int cacheSize)
{
  if (CacheCch < cacheSize)
  {
    delete[] wszCache;
    wszCache = new wchar_t[cacheSize + 1];
    CacheCch = cacheSize + 1;
  }
}

void ResourceBase::SetDescription(wchar_t* wszDescription, unsigned int size)
{
  if (descriptionSize < size)
  {
    delete[] description;
    description = new wchar_t[size];
    descriptionSize = size;
  }
  if (description)
    wcscpy_s(description, descriptionSize, wszDescription);
}

void ResourceBase::SetPin(bool bPinned)
{
  pinned = bPinned;
}

ResourceBase::~ResourceBase()
{
  Cleanup();
}
