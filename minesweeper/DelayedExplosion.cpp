/*

Minesweeper Decompilation

File name:
  DelayedExplosion.cpp

*/

#include "DelayedExplosion.h"
#include "UIBoardCanvas.h"

DelayedExplosion::DelayedExplosion(int a1, int a2)
{
  field_C = a1;
  field_10 = a2;
  field_9 = false;
}

void DelayedExplosion::HandleEvent(unsigned int a1, void* a2)
{
  UIBoardCanvas* canvas = (UIBoardCanvas*)a2;

  field_9 = true;

  g_pTimer->DeleteEvent(a1);

  field_8 = false;

  canvas->doMineExplosion(field_C, field_10, false);
  canvas->removeDelayedExplosion(this);

  HandleEvent(1);
}
