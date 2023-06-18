/*

Minesweeper Decompilation

*/

#ifndef _UITILE_H_
#define _UITILE_H_

#include <OberEngine/event.h>
#include <OberEngine/nodesprite.h>

enum ETileStatus {

};

class UITile : public IEventListener {
private:
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

  static NodeBase* _pExplosionAnimatedSpriteBase;
  static NodeBase* _pDisarmAnimatedSpriteBase;
  static NodeBase* _pHighlightSpriteBase;
  static NodeBase* _pTopSpriteBase;
  static NodeBase* _pFlagSpriteBase;
  static NodeBase* _pMineSpriteBase;
  static NodeBase* _pBadGuessSpriteBase;
  static NodeBase* _pQuestionMarkSpriteBase;
  static NodeBase* _pNumberSpriteBase;
  static NodeBase* _pUpperShadowBase;
  static NodeBase* _pLeftShadowBase;
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

public:

  void ClearRumble();
  void StartRumble(bool bLeftRumble);
  void EndRumble(bool bLeftRumble);

};

#endif // _UITILE_H_
