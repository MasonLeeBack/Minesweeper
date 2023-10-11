/*

OberEngine Decompilation
Original Game: Purble Place

*/

#ifndef _CABINET_H_
#define _CABINET_H_

#include "str.h"

namespace CabLoader {
  class CabStream {
  public:
    Str streamName;


    bool bSomething1;
    bool bSomething2;
  };

  void StaticExit();

  CabStream* FindStreamNamed(const Str& streamName);
  void RegisterCabStream(CabStream* stream);
  void UnregisterCabStream(CabStream* stream);
}

#endif // _CABINET_H_
