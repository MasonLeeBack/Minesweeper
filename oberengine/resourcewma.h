/*

OberEngine Decompilation

File name:
  resourcewma.h

*/

#ifndef _RESOURCEWMA_H_
#define _RESOURCEWMA_H_

#include "resourcesound.h"

class ResourceWMA : public ResourceSound
{
public:
  bool Recreate();
  bool LoadAsNeeded();
};

#endif // _RESOURCEWMA_H_
