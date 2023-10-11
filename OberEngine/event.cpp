/*

OberEngine Decompilation

File name:
  event.cpp

*/

#include "stdafx.h"
#include "event.h"

void Event::Delete()
{
  if (this)
    delete this;
}

Event::RegisteredType* Event::CreateGameEvent(GameEventId id)
{
  return NULL;
}
