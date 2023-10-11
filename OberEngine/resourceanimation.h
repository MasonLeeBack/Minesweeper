/*

OberEngine Decompilation

File name:
  resourceanimation.h

*/

#ifndef _RESOURCEANIMATION_H_
#define _RESOURCEANIMATION_H_

#include "resourcebase.h"
#include "animationdescriptor.h"

class ResourceAnimation : public ResourceBase
{
public:
  AnimationDescriptor* descriptor;
  wchar_t* XmlFile;
  int XmlFileSize;

  AnimationState* CreateAnimationState(bool toDetermine);
  bool Recreate();

  ResourceAnimation(AnimationDescriptor* desc);
  ResourceAnimation(wchar_t* Source, unsigned int size);

  unsigned int Create(AnimationDescriptor* desc);
  unsigned int Create(wchar_t* Source, unsigned int size);
  ~ResourceAnimation();
};

#endif // _RESOURCEANIMATION_H_
