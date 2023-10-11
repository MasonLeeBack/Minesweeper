/*

OberEngine Decompilation
Original Game: Purble Place

*/

#include "oberlib.h"
#include <fdi.h>

namespace CabLoader {

  Array<CabLoader::CabStream*> sCabStreams;
  HFDI sCabContext;
  ERF sCabErf;

  FNALLOC(CabAlloc)
  {
    return malloc(cb);
  }

  FNFREE(CabFree)
  {
    free(pv);
  }

  FNOPEN(CabOpenFunc)
  {
    return 0;
  }
  
  FNREAD(CabReadFunc)
  {
    return 0;
  }

  FNWRITE(CabWriteFunc)
  {
    return 0;
  }

  FNSEEK(CabSeekFunc)
  {
    return 0;
  }

  FNCLOSE(CabCloseFunc)
  {
    if (((CabStream*)hf)->bSomething1)
    {
      ((CabStream*)hf)->bSomething2 = true;
    }
    else
    {
      UnregisterCabStream((CabStream*)hf);
      delete (CabStream*)hf;
    }

    return 0;
  }

  void StaticExit()
  {
    CabStream* stream;

    for (unsigned int i = 0; i < sCabStreams.count; i++)
    {
      stream = sCabStreams.data[i];
      if (stream)
      {
        delete stream;
      }
    }

    sCabStreams.count = 0;
    if (sCabContext)
    {
      FDIDestroy(sCabContext);
      sCabContext = NULL;
    }
  }

  bool StaticInit()
  {
    StaticExit();

    sCabContext = FDICreate(
      CabAlloc,
      CabFree,
      CabOpenFunc,
      CabReadFunc,
      CabWriteFunc,
      CabCloseFunc,
      CabSeekFunc,
      0,
      &sCabErf);

    return sCabContext != NULL;
  }

  CabStream* FindStreamNamed(const Str& name)
  {
    unsigned int i = 0;
    CabStream* stream;

    if (sCabStreams.count == 0)
      return NULL;

    while (true)
    {
      stream = sCabStreams.data[i];

      if (stream)
      {
        if (!_wcsicmp(name.m_pStr, stream->streamName.m_pStr))
          break;
      }

      if (++i >= sCabStreams.count)
        return NULL;

    }

    return sCabStreams.data[i];
  }

  void RegisterCabStream(CabStream* stream)
  {
    unsigned int i = 0;

    if (sCabStreams.count)
    {
      while (sCabStreams.data[i])
      {
        if (++i >= sCabStreams.count)
        {
          sCabStreams.Add(stream);
          break;
        }
      }
      sCabStreams.data[i] = stream;
    }
    else {
      sCabStreams.Add(stream);
    }
  }

  void UnregisterCabStream(CabStream* stream)
  {
    unsigned int i = 0;

    if (sCabStreams.count == 0)
      return;

    while (sCabStreams.data[i] != stream)
    {
      if (++i >= sCabStreams.count)
        return;
    }

    sCabStreams.data[i] = 0;
  }

} // namespace CabLoader
