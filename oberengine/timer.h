/*

OberEngine Decompilation

File name:
  timer.h

*/

#ifndef _TIMER_H_
#define _TIMER_H_

#include "event.h"
#include <sortedlist.h>

class Timer {
  SortedListI<Event::RegisteredType> m_EventList; // 0

  SortedListI<Event::RegisteredType> m_DeleteList; // 24
};

extern Timer* g_pTimer;

#endif // _TIMER_H_
