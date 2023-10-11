/*

Minesweeper Decompilation

File name:
  UIBoardCanvas.cpp

*/

#include "Game.h"
#include "UIBoardCanvas.h"

void UIBoardCanvas::PlayTileRevealSound(int numTilesRevealed)
{
  if (numTilesRevealed >= 10 && g_Game->unknownVariable) {
    GameAudio::PlaySoundProto(3, 0, 0);
  }
}

void UIBoardCanvas::ToggleFlag(UITile* tile)
{
  board->ToggleFlag(tile->xPos, tile->yPos);
  bUnknownBool = true;
}

void UIBoardCanvas::ShowTipMessage(wchar_t* message)
{
  LOG(1, L"ShowTipMessage( %s )", message);
  if (g_Game->bTipsEnabled == TRUE) {
    tipManager->ShowTipIfEnabled(message, 0, 0);
  }
}

void UIBoardCanvas::HideTip()
{
  tipManager->HideTip(false);
}
