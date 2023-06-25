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
  if (g_pCommonController) {
    if (bLeftRumble)
      --_leftRumbleCount;
    else
      --_rightRumbleCount;

    if (bLeftRumble) {
      if (_leftRumbleCount == 0) {
        g_pCommonController->DeactivateRumble(true);
      }
    }
    else {
      if (_rightRumbleCount == 0) {
        g_pCommonController->DeactivateRumble(false);
      }
    }
  }
}

bool UITile::IsNumberVisible()
{
  return m_Number && m_Number->m_bVisible;
}

void UITile::QuickFadeOutFlag()
{
  unsigned int animationID;

  if (m_Flag) {
    animationID = m_Flag->AddAnimation(_alphaQuickFadeOutAnimationId, 0);
    m_Flag->ResumeAnimation(animationID);
  }
}

NodeSprite* UITile::ShowBadGuess()
{
  if (!m_BadGuess) {
    m_BadGuess = _pBadGuessSpriteBase->Copy();
    m_BadGuess->SetPosition(_tileSize * m_Column, m_BadGuess->m_YPos);
    m_BadGuess->SetPosition(m_BadGuess->m_XPos, _tileSize * m_Row);
    m_BadGuess->field_44 = 0;
    m_BadGuess->SetVisible(true);
  }

  return m_BadGuess;
}

void UITile::RemoveBadGuess()
{
  if (m_BadGuess) {
    m_BadGuess->DeleteSelf();
    m_BadGuess = NULL;
  }
}

NodeSprite* UITile::ShowFlag()
{
  if (!m_Flag) {
    m_Flag = _pFlagSpriteBase->Copy();
    m_Flag->SetPosition(_tileSize * m_Column, m_Flag->m_YPos);
    m_Flag->SetPosition(m_Flag->m_XPos, _tileSize * m_Row);
    m_Flag->field_44 = 0;
    m_Flag->SetVisible(true);
  }

  return m_Flag;
}

void UITile::RemoveFlag()
{
  if (m_Flag) {
    m_Flag->DeleteSelf();
    m_Flag = NULL;
  }
}

NodeSprite* UITile::ShowMine()
{
  if (!m_Mine) {
    m_Mine = _pMineSpriteBase->Copy();
    m_Mine->SetPosition(_tileSize * m_Column, m_Mine->m_YPos);
    m_Mine->SetPosition(m_Mine->m_XPos, _tileSize * m_Row);
    m_Mine->field_44 = 0;
    m_Mine->SetVisible(true);
  }
  
  return m_Mine;
}

void UITile::RemoveMine()
{
  if (m_Mine) {
    m_Mine->DeleteSelf();
    m_Mine = NULL;
  }
}

NodeSprite* UITile::ShowNumber(ETileStatus status)
{
  if (!m_Number) {
    m_Number = _pNumberSpriteBase->Copy();
    m_Number->SetPosition(_tileSize * m_Column + 5, m_Number->m_YPos);
    m_Number->SetPosition(m_Number->m_XPos, _tileSize * m_Row + 3);
    m_Number->field_44 = 0;
    m_Number->SetVisible(true);
    m_Number->SetCurrentFrame(status - 1);
  }

  return m_Number;
}

void UITile::RemoveNumber()
{
  if (m_Number) {
    m_Number->DeleteSelf();
    m_Number = NULL;
  }
}

NodeSprite* UITile::ShowQuestionMark()
{
  if (!m_QuestionMark) {
    m_QuestionMark = _pQuestionMarkSpriteBase->Copy();
    m_QuestionMark->SetPosition(_tileSize * m_Column, m_QuestionMark->m_YPos);
    m_QuestionMark->SetPosition(m_QuestionMark->m_XPos, _tileSize * m_Row);
    m_QuestionMark->field_44 = 0;
    m_QuestionMark->SetVisible(true);
  }

  return m_QuestionMark;
}

void UITile::RemoveQuestionMark()
{
  if (m_QuestionMark) {
    m_QuestionMark->DeleteSelf();
    m_QuestionMark = NULL;
  }
}

NodeSprite* UITile::ShowLeftShadow(int alpha)
{
  if (!m_LeftShadow) {
    m_LeftShadow = _pLeftShadowBase->Copy();
    m_LeftShadow->SetPosition(_tileSize * m_Column, m_LeftShadow->m_YPos);
    m_LeftShadow->SetPosition(m_LeftShadow->m_XPos, _tileSize * m_Row);
    m_LeftShadow->field_44 = 0;
    m_LeftShadow->SetVisible(true);
    m_LeftShadow->SetAlpha(alpha);
  }

  return m_LeftShadow;
}

void UITile::RemoveLeftShadow()
{
  if (m_LeftShadow) {
    m_LeftShadow->DeleteSelf();
    m_LeftShadow = NULL;
  }
}

NodeSprite* UITile::ShowUpperShadow(int alpha)
{
  if (!m_UpperShadow) {
    m_UpperShadow = _pUpperShadowBase->Copy();
    m_UpperShadow->SetPosition(_tileSize * m_Column, m_UpperShadow->m_YPos);
    m_UpperShadow->SetPosition(m_UpperShadow->m_XPos, _tileSize * m_Row);
    m_UpperShadow->field_44 = 0;
    m_UpperShadow->SetVisible(true);
    m_UpperShadow->SetAlpha(alpha);
  }

  return m_UpperShadow;
}

void UITile::RemoveUpperShadow()
{
  if (m_UpperShadow) {
    m_UpperShadow->DeleteSelf();
    m_UpperShadow = NULL;
  }
}
