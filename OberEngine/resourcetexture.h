/*

OberEngine Decompilation
Original Game: Purble Place

*/

#ifndef _RESOURCETEXTURE_H_
#define _RESOURCETEXTURE_H_

#include "resourcebase.h"

class ResourceTexture : public ResourceBase
{
public:
  ResourceTexture();
  ~ResourceTexture();
};

class ResourceTextureD3D : public ResourceTexture
{
  
  bool IsLoaded();
  bool IsSplit();
  void Purge();
  bool ReleaseD3D();
  void SetNameForDPI(bool bDoubleDPI);
  void GetDimensions(unsigned int* width, unsigned int* height);

};

#endif