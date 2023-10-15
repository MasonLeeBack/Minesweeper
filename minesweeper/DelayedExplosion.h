/*

Minesweeper Decompilation

File name:
  DelayedExplosion.h

*/

#ifndef _DELAYEDEXPLOSION_H_
#define _DELAYEDEXPLOSION_H_

#include <timer.h>

// size: 0x14 (20)
class DelayedExplosion : public ITimerEventPrototype {
  
  int m_Event; // 0x4, (Event::RegisteredType)
  bool field_8; // 0x8
  bool field_9; // 0x9
  int field_C; // 0xC
  int field_10; // 0x10

public :
  DelayedExplosion(int a1, int a2);
  ~DelayedExplosion();

  void HandleEvent(unsigned int a1, void* a2 = NULL);
};

// size: 0x18 (24)
class DelayedExplosionCheck : public ITimerEventPrototype {

};

#endif // _DELAYEDEXPLOSION_H_
