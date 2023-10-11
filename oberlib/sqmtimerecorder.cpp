/*

OberEngine Decompilation
Original Game: Purble Place

*/

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "ext/ntdll_private_imports.h"
#include "sqmtimerecorder.h"

CSQMTimeRecorder::~CSQMTimeRecorder()
{
  ULONGLONG tickCount;

  if (m_iDataId)
  {
    tickCount = GetTickCount64();

    if (tickCount > m_qTickCount) {
      // I'm so confused about this casting. But it seems right.
      WinSqmIncrementDWORD(0, m_iDataId, (const wchar_t*)(tickCount - m_qTickCount / 0xEA60));
    }
  }
}

void CSQMTimeRecorder::SetDataId(unsigned int dataId)
{
  if (dataId != 0) {
    m_iDataId = dataId;
    m_qTickCount = GetTickCount64();
  }
}
