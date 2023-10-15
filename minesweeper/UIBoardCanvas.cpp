/*

Minesweeper Decompilation

File name:
  UIBoardCanvas.cpp

*/

#include "Game.h"
#include "Board.h"
#include "UIBoardCanvas.h"

#include <tipmanager.h>
#include <gameaudio.h>
#include <logger.h>

void UIBoardCanvas::PlayTileRevealSound(int numTilesRevealed)
{
  if (numTilesRevealed >= 10 && g_Game->field_18) {
    GameAudio::PlaySoundProto(3, 0, 0);
  }
}

void UIBoardCanvas::ToggleFlag(UITile* tile)
{
  m_pBoard->ToggleFlag(tile->m_Column, tile->m_Row);
  field_AC = true;
}

void UIBoardCanvas::ShowTipMessage(wchar_t* message)
{
  LOG(1, L"ShowTipMessage( %s )", message);
  if (g_Game->m_bTipsEnabled == true) {
    m_pTipManager->ShowTipIfEnabled(message, 0, 0);
  }
}

void UIBoardCanvas::HideTip()
{
  m_pTipManager->HideTip(false);
}

void UIBoardCanvas::ClearHighlightTile()
{
  if (m_pHighlightedTile) {
    m_pHighlightedTile->SetHighlight(false);
    m_pHighlightedTile->m_FocusNode->SetColor(0xFFFFFF);
  }
}

void UIBoardCanvas::SetHighlightTile(UITile* tile)
{
  if (g_Game->IsReadyForInput()) {
    m_pHighlightedTile = tile;
    if (tile->field_48) {
      tile->SetHighlight(true);
    }
    else if (g_Game->m_bUserPrefersKeyboard) {
      tile->m_FocusNode->SetColor(0xD8D8D8);
    }
  }
  else {
    m_pHighlightedTile = NULL;
  }
}

bool UIBoardCanvas::DoRevealAction(UITile* tile)
{
  bool result = false;

  g_Game->field_C5 = true;

  int revealedTiles = g_Game->AttemptReveal(tile->m_Column, tile->m_Row);
  if (revealedTiles > 0) {
    PlayTileRevealSound(revealedTiles);
  }
  else {
    field_9C = tile;

    result = true;
  }

  field_AC = true;

  return result;
}

UITile* UIBoardCanvas::FindTileWithBack(NodeBase* node)
{
  UITile* res;
  unsigned int i, j;

  do {
    if (i >= m_pTiles.count)
      break;
  }
  while (!res);

  return res;
}

bool UIBoardCanvas::IsDisarmComplete()
{
  if (m_pAnimatingTiles.count == 0 && field_20 == 0)
    return true;

  return false;
}

bool UIBoardCanvas::IsMineTripComplete()
{
  if (m_pDelayedExplosions.count == 0 && m_pDelayedExplosionChecks.count == 0 && m_pAnimatingTiles.count == 0)
    return true;
  
  return false;
}

void UIBoardCanvas::disarmTilesAtYPos(int yPos)
{
  if (yPos >= 0) {

  }
}

void UIBoardCanvas::removeDelayedExplosionCheck(DelayedExplosionCheck* expchk)
{
  for (unsigned int i = 0; i < m_pDelayedExplosionChecks.count; ++i) {
    if (m_pDelayedExplosionChecks.data[i] == expchk) {
      m_pDelayedExplosionChecks.Remove(i);
    }
  }
}

void UIBoardCanvas::removeDelayedExplosion(DelayedExplosion* exp)
{
  for (unsigned int i = 0; i < m_pDelayedExplosions.count; ++i) {
    if (m_pDelayedExplosions.data[i] == exp) {
      m_pDelayedExplosions.Remove(i);
    }
  }
}

void UIBoardCanvas::removeAnimatingTile(UITile* tile)
{
  for (unsigned int i = 0; i < m_pAnimatingTiles.count; ++i) {
    if (m_pAnimatingTiles.data[i] == tile) {
      m_pAnimatingTiles.Remove(i);
    }
  }
}

UITile* UIBoardCanvas::getTile(unsigned int x, unsigned int y)
{
  return m_pTiles.data[x]->data[y];
}

void UIBoardCanvas::MakeAllTilesDirty()
{
  for (unsigned int i = 0; i < m_pTiles.count; ++i) {
    for (unsigned int j = 0; j < m_pTiles.data[i]->count; ++j) {
      getTile(i, j)->m_bTopVisible = true;
    }
  }
}

void UIBoardCanvas::SetShowMines(bool bShowMines)
{
  m_bShowMines = bShowMines;
  MakeAllTilesDirty();
}

void UIBoardCanvas::SetAllTilesTopAlpha(int alpha)
{
  for (unsigned int i = 0; i < m_pTiles.count; ++i) {
    for (unsigned int j = 0; j < m_pTiles.data[i]->count; ++j) {
      getTile(i, j)->SetTopAlpha(alpha);
    }
  }
}
