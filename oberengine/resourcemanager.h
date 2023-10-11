/*

OberEngine Decompilation

File name:
  resourcemanager.h

*/

#ifndef _RESOURCEMANAGER_H_
#define _RESOURCEMANAGER_H_

#include "resourcebase.h"
#include <array.h>

class ResourceManager
{
public:

  uint32_t field_0;
  uint32_t field_4;
  uint32_t field_8;
  uint32_t field_C;
  uint32_t field_10;
  uint32_t field_14;
  uint32_t field_18;
  uint32_t field_1C;
  uint32_t field_20;
  Array<ResourceBase*> resources;
  SortedListW<tagPOINT> textureDimensions;
  uint32_t field_48;
  uint32_t field_4C;
  uint32_t field_50;

  bool Initialize();
  bool PinResource(unsigned int uResourceID);
  void UnpinResource(unsigned int uResourceID);
  bool GetResource(unsigned int uResourceID, bool noIdea);
  void Cleanup();
};

extern ResourceManager* g_pResourceManager;

#endif // _RESOURCEMANAGER_H_
