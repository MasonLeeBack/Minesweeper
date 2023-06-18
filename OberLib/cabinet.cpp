/*

OberEngine Decompilation
Original Game: Purble Place

*/

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <memory>
#include <fdi.h>

#include "cabinet.h"

namespace CabLoader {

  ATL::CSimpleArray<CabLoader::CabStream*> sCabStreams;
  HFDI sCabContext;


  FNALLOC(CabAlloc)
  {
    return malloc(cb);
  }

  FNOPEN(CabOpenFunc)
  {
    
  }

  FNSEEK(CabSeekFunc)
  {

  }

  FNCLOSE(CabCloseFunc)
  {


    return 0;
  }

  void StaticExit()
  {
    for (int i = 0; i < sCabStreams.GetSize(); i++)
    {
      // todo
    }

    sCabStreams = 0;
    if (sCabContext)
    {
      FDIDestroy(sCabContext);
      sCabContext = NULL;
    }
  }

  bool StaticInit()
  {
    StaticExit();
    
    return sCabContext != NULL;
  }

} // namespace CabLoader
