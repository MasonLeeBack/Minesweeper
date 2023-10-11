/*

OberEngine Decompilation

File name:
  event.h

*/

#ifndef _EVENT_H_
#define _EVENT_H_

#include <sortedlist.h>

class IEventListener {

};

class Event {
public:
  struct RegisteredType {

  };
  typedef int GameEventId;

  static SortedListI<Event::RegisteredType> m_RegisteredTypes;

  void Delete();

  RegisteredType* CreateGameEvent(GameEventId id);
};

#endif // _EVENT_H_
