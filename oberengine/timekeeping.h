/*

OberEngine Decompilation

File name:
  timekeeping.h

*/

#ifndef _TIMEKEEPING_H_
#define _TIMEKEEPING_H_

namespace Timekeeping {
  enum TimeMethod {
    QUERYPERFORMANCECOUNTER,
    TIMEGETTIME
  };

  extern TimeMethod g_CurrentTimeMethod;

  extern const unsigned int m_uiGameUpdatesPerSec = 30;

  extern LONGLONG g_ThirtyFPSTicks;

  extern LARGE_INTEGER g_NewTime;
  extern LARGE_INTEGER g_LastTime;
  extern LARGE_INTEGER g_PerfFreq;

  bool Check30FPS();
  void CleanupTimekeeping();
  bool InitializeTimekeeping();
  void UpdateTimekeeping();
  void ResetTimers();
};

#endif // _TIMEKEEPING_H_
