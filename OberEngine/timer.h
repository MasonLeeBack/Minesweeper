/*

OberEngine Decompilation
Original Game: Purble Place

*/

#ifndef _TIMER_H_
#define _TIMER_H_

class Timer {
  SortedListI<Event::RegisteredType> m_EventList; // 0

  SortedListI<Event::RegisteredType> m_DeleteList; // 24
};

extern Timer g_pTimer;

#endif // _TIMER_H_
