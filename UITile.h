/*

Minesweeper Decompilation

*/

#ifndef _UITILE_H_
#define _UITILE_H_

#include "UIBoardCanvas.h"

#include <OberEngine/event.h>
#include <OberEngine/nodesprite.h>

#include <d3dx9.h>

class UITileConstructionInfo {
  
};

enum ETileStatus {

};

class UITile : public IEventListener {
private:
  // All static variables
  static bool _bothButtonsWereDown;
  static bool _mouseDownWasCanceled;

  static UITile* _pMouseEnterNode;

  static int _leftRumbleCount;
  static int _rightRumbleCount;
  static int _tileWidth;
  static int _tileSize;

  static AnimationState* _alphaQuickPulseAnimationId;
  static AnimationState* _alphaQuickFadeOutAnimationId;
  static AnimationState* _alphaQuickFadeInAnimationId;
  static AnimationState* _disarmFrameControlAnimationId;
  static AnimationState* _explosionControlAnimationId;

  static int _mineExplodeXOffset;
  static int _mineExplodeYOffset;

  static UITile* _mouseDragNode;

  static NodeSprite* _pExplosionAnimatedSpriteBase;
  static NodeSprite* _pDisarmAnimatedSpriteBase;
  static NodeSprite* _pHighlightSpriteBase;
  static NodeSprite* _pTopSpriteBase;
  static NodeSprite* _pFlagSpriteBase;
  static NodeSprite* _pMineSpriteBase;
  static NodeSprite* _pBadGuessSpriteBase;
  static NodeSprite* _pQuestionMarkSpriteBase;
  static NodeSprite* _pNumberSpriteBase;
  static NodeSprite* _pUpperShadowBase;
  static NodeSprite* _pLeftShadowBase;
  static NodeBase* _pShadowLayerContainer;
  static NodeBase* _pLabelLayerContainer;
  static NodeBase* _pTopLayerContainer;
  static NodeBase* _pHighlightLayerContainer;
  static NodeBase* _pFlagLayerContainer;
  static NodeBase* _pXLayerContainer;
  static NodeBase* _pAnimLayerContainer;

  static Array<NodeBase*> _backContainerRows;
  static Array<NodeSprite*> _backSpriteRowBases;
  static Array<NodeSprite*> _accessibilityGroups;

  // All member variables
  NodeSprite* m_Highlight;
  NodeSprite* m_Top;
  NodeSprite* m_FocusNode;
  NodeSprite* m_ExplosionAnimationBase;
  NodeSprite* m_DisarmAnimationBase;

  int m_Column;
  int m_Row;

  int field_20;

  bool m_bTopVisible;

  UIBoardCanvas* m_Canvas;

  NodeSprite* m_Mine;
  NodeSprite* m_Flag;
  NodeSprite* m_BadGuess;
  NodeSprite* m_QuestionMark;
  NodeSprite* m_Number;
  NodeSprite* m_UpperShadow;
  NodeSprite* m_LeftShadow;

  bool field_48;

  int m_InvalidMoveAnimationId;
  int m_ExplosionAnimationId;
  int m_DisarmAnimationId;
  int m_AlphaFadeInAnimationId;

public:

  void DestroyBaseNodes();

  void SetHighlight(bool bHighlight);
  void HandleEsc();

  void ClearRumble();
  void StartRumble(bool bLeftRumble);
  void EndRumble(bool bLeftRumble);

  bool IsNumberVisible();

  void QuickFadeOutFlag();

  void StartDisarmAnimation();
  void RemoveDisarmAnimation();
  void StartExplosionAnimation();
  void RemoveExplosionAnimation();
  void StartInvalidMoveAnimation();
  void RemoveInvalidMoveAnimation();

  NodeSprite* ShowBadGuess();
  void RemoveBadGuess();
  NodeSprite* ShowFlag();
  void RemoveFlag();
  NodeSprite* ShowMine();
  void RemoveMine();
  NodeSprite* ShowNumber(ETileStatus status);
  void RemoveNumber();
  NodeSprite* ShowQuestionMark();
  void RemoveQuestionMark();

  NodeSprite* ShowLeftShadow(int a1);
  void RemoveLeftShadow();
  NodeSprite* ShowUpperShadow(int a1);
  void RemoveUpperShadow();

};

#endif // _UITILE_H_
