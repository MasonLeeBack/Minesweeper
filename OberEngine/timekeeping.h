/*

OberEngine Decompilation
Original Game: Purble Place

*/

#ifndef _TIMEKEEPING_H_
#define _TIMEKEEPING_H_

class Timekeeping {
  enum TimeMethod {
    QUERYPERFORMANCECOUNTER,
    TIMEGETTIME
  };

  static TimeMethod g_CurrentTimeMethod;

  static const unsigned int m_uiGameUpdatesPerSec = 30;

  static LONGLONG g_ThirtyFPSTicks;

  static LARGE_INTEGER g_NewTime;
  static LARGE_INTEGER g_LastTime;
  static LARGE_INTEGER g_PerfFreq;

  static bool Check30FPS();
  static void CleanupTimekeeping();
  static bool InitializeTimekeeping();
  static void UpdateTimekeeping();
  void ResetTimers();
};

#endif // _TIMEKEEPING_H_
