/*

OberEngine Decompilation

File name:
  resourcesound.h

*/

#ifndef _RESOURCESOUND_H_
#define _RESOURCESOUND_H_

#include "resourcebase.h"

class ResourceSound : public ResourceBase
{
public:
  ResourceSound();
  ~ResourceSound();

  unsigned int GetVolume(unsigned int a1);
  void SetVolume(unsigned int volume, unsigned int a2); // todo : figure out vars
};

#endif // _RESOURCESOUND_H_
