/*

Minesweeper Decompilation

*/

#ifndef _UIBOARDCANVAS_H_
#define _UIBOARDCANVAS_H_

class UIBoardCanvas {
public:

  class TipManager* tipManager; // 41

  bool bUnknownBool; // 172 (used in ToggleFlag)

  void PlayTileRevealSound(int numTilesRevealed);
  void ToggleFlag(class UITile* tile);
  void ShowTipMessage(wchar_t* message);
  void HideTip();
  void ClearHighlightTile();
  void SetHighlightTile(class UITile* tile);
  UIBoardCanvas();
  bool DoRevealAction(class UITile* tile);
  UITile* FindTileWithBack(class NodeBase* node);
  void DoDisarmAction();
  void HandleEvent(class Event* event);
  bool IsDisarmComplete();
  bool IsMineTripComplete();
  void disarmTilesAtYPos(int yPos);
  void RefreshLabels();

  void ClearAnimations();

  void Refresh(bool bForceRefresh);
  void MakeAllTilesDirty();
};

#endif // _UIBOARDCANVAS_H_
