/*

OberEngine Decompilation
Original Game: Purble Place

*/

#ifndef _RESOURCEBASE_H_
#define _RESOURCEBASE_H_

class ResourceBase
{
public:
  static wchar_t* wszCache;
  static unsigned int CacheCch;

  int field_4; // 4
  int field_8; // 8
  int field_C; // 12
  bool pinned; // 16
  int field_14; // 20
  wchar_t* description; // 24 
  unsigned int descriptionSize; // 28 

  unsigned int GetPurgeTimeout();
  void SetNameForDPI(bool);

  ResourceBase();
  void Cleanup();
  static void VerifyCache(unsigned int cacheSize);
  void SetDescription(wchar_t* wszDescription, unsigned int size);
  void SetPin(bool bPinned);
  ~ResourceBase();
};

#endif // _RESOURCEBASE_H_
