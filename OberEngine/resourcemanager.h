/*

OberEngine Decompilation
Original Game: Purble Place

*/

#ifndef _RESOURCEMANAGER_H_
#define _RESOURCEMANAGER_H_

#include "resourcebase.h"

class ResourceManager : public ResourceBase
{
public:
  bool Initialize();
  void UnpinResource(unsigned int uResourceID);

};

#endif // _RESOURCEMANAGER_H_
