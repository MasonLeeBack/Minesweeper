/*

OberEngine Decompilation

File name:
  timekeeping.cpp

*/

#include "stdafx.h"
#include "timekeeping.h"
#include <logger.h>

bool Timekeeping::Check30FPS()
{
  if (g_CurrentTimeMethod == QUERYPERFORMANCECOUNTER) {
    if (g_NewTime.QuadPart - g_LastTime.QuadPart > g_ThirtyFPSTicks)
    {
      if (g_NewTime.QuadPart - g_LastTime.QuadPart <= 2 * g_PerfFreq.QuadPart)
        g_LastTime.QuadPart += g_ThirtyFPSTicks;
      else
        g_LastTime = g_NewTime;
      return true;
    }
    return false;
  }
  if (g_CurrentTimeMethod == TIMEGETTIME) {
    if (g_NewTime.LowPart - g_LastTime.LowPart > 1000 / m_uiGameUpdatesPerSec)
    {
      if (g_NewTime.LowPart - g_LastTime.LowPart <= 2000)
        g_LastTime.LowPart += 1000 / m_uiGameUpdatesPerSec;
      else
        g_LastTime.LowPart = g_NewTime.LowPart;
      return true;
    }
    return false;
  }
  return true;
}

void Timekeeping::CleanupTimekeeping()
{
  if (g_CurrentTimeMethod == TIMEGETTIME)
    timeEndPeriod(33);
}

bool Timekeeping::InitializeTimekeeping()
{
  LOG(8, L"Initializing timekeeping with QPC:");

  g_CurrentTimeMethod = QUERYPERFORMANCECOUNTER;

  if (!QueryPerformanceFrequency(&Timekeeping::g_PerfFreq))
  {
    LOG(8, L"QueryPerformanceFrequency check failed: falling back to TimeGetTime");

    g_CurrentTimeMethod = TIMEGETTIME;

    timeBeginPeriod(33);

    LOG(8, L"timeGetTime selected for timekeeping");

    Timekeeping::g_LastTime.LowPart = timeGetTime();

    LOG(8, L"Timekeeping initialized");

    return true;
  }

  if (!QueryPerformanceCounter(&Timekeeping::g_LastTime))
  {
    LOG(8, L"QueryPerformanceCounter check failed: falling back to TimeGetTime");

    g_CurrentTimeMethod = TIMEGETTIME;

    timeBeginPeriod(33);

    LOG(8, L"timeGetTime selected for timekeeping");

    Timekeeping::g_LastTime.LowPart = timeGetTime();

    LOG(8, L"Timekeeping initialized");

    return true;
  }

  LOG(8, L"QueryPerformanceCounter selected for timekeeping");
  g_ThirtyFPSTicks = g_PerfFreq.QuadPart / 30;

  if (Timekeeping::g_CurrentTimeMethod == 1) {
    timeBeginPeriod(33);
    LOG(8, L"timeGetTime selected for timekeeping");
    Timekeeping::g_LastTime.LowPart = timeGetTime();
  }

  LOG(8, L"Timekeeping initialized");

  return true;
}

void Timekeeping::UpdateTimekeeping()
{
  if (g_CurrentTimeMethod == QUERYPERFORMANCECOUNTER) {
    if (QueryPerformanceCounter(&g_NewTime)) {
      if (g_LastTime.QuadPart > g_NewTime.QuadPart)
        g_NewTime = g_LastTime;
    }
    else {
      LOG(8, L"SkippingQPC failed - Falling back to timeGetTime()");
      g_CurrentTimeMethod = TIMEGETTIME;
      timeBeginPeriod(33);
    }
  }

  if (g_CurrentTimeMethod == TIMEGETTIME) {
    g_NewTime.LowPart = timeGetTime();
  }
}

void Timekeeping::ResetTimers()
{
  LOG(8, L"Reset timers");

  if (g_CurrentTimeMethod == QUERYPERFORMANCECOUNTER && !QueryPerformanceCounter(&g_LastTime))
  {
    LOG(8, L"SkippingQPC failed - Falling back to timeGetTime()");
    g_CurrentTimeMethod = TIMEGETTIME;
    timeBeginPeriod(33);
  }

  if (Timekeeping::g_CurrentTimeMethod == TIMEGETTIME) {
    g_LastTime.LowPart = timeGetTime();
  }

  UpdateTimekeeping();
}
