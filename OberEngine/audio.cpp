/*

OberEngine Decompilation
Original Game: Purble Place

*/

#include "stdafx.h"
#include "hresult.h"

bool Audio::Initialize()
{
  if (!LoadLibraryW(L"wmvcore.dll"))
  {
    LOG(0x1000, L"wmvcore.dll LoadLibrary failed, winerror %d", GetLastError());
    m_pDirectSound = NULL;
    return true;
  }


}

IDirectSound8* Audio::GetDS()
{
  return m_pDirectSound;
}
