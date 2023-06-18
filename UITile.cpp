/*

Minesweeper Decompilation

*/

#include "UITile.h"
#include <OberLib/commoncontroller.h>

void UITile::ClearRumble()
{
  if (g_pCommonController) {
    g_pCommonController->DeactivateRumble(true);
    g_pCommonController->DeactivateRumble(false);
  }
  _leftRumbleCount = 0;
  _rightRumbleCount = 0;
}

void UITile::StartRumble(bool bLeftRumble)
{
  if (g_pCommonController) {
    if (_leftRumbleCount) {
      ++_leftRumbleCount;
      return;
    }
    g_pCommonController->ActivateRumble(true, 0x8000);
  }
  else {
    if (_rightRumbleCount) {
      ++_rightRumbleCount;
      return;
    }
    g_pCommonController->ActivateRumble(false, 0x8000);
  }

  if (bLeftRumble) {
    ++_leftRumbleCount;
  }
  else {
    ++_rightRumbleCount;
  }
}

void UITile::EndRumble(bool bLeftRumble)
{
}
