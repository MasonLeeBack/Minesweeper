/*

OberEngine Decompilation
Original Game: Purble Place

*/

#include "resourceanimation.h"

AnimationState* ResourceAnimation::CreateAnimationState(bool toDetermine)
{
  return descriptor->CreateState(toDetermine);
}

bool ResourceAnimation::Recreate()
{
  if (!descriptor) {
    descriptor = new AnimationDescriptor();

    if (!descriptor) {
      CheckAllocation(0);
      return false;
    }

    if (!XmlFile) {
      return false;
    }

    if (!descriptor->ParseXml(XmlFile))
    {
      LOG(L"ParseXml failed (%s)", XmlFile);
      return false;
    }
  }
  return true;
}

ResourceAnimation::ResourceAnimation(AnimationDescriptor* desc)
{
  XmlFile = 0;
  XmlFileSize = 0;
  descriptor = desc;
  field_14 = 4; // might be an enum
}

ResourceAnimation::ResourceAnimation(wchar_t* Source, unsigned int size)
{
  XmlFile = new wchar_t[size];
  if (XmlFile)
    wcscpy_s(XmlFile, size, Source);
  descriptor = 0;
  XmlFileSize = size;
}

unsigned int ResourceAnimation::Create(AnimationDescriptor* desc)
{
  return 0;
}

unsigned int ResourceAnimation::Create(wchar_t* Source, unsigned int size)
{
  return 0;
}

ResourceAnimation::~ResourceAnimation()
{
  delete[] XmlFile;
  if (descriptor)
    delete descriptor;
}
