/*

Minesweeper Decompilation

File name:
  UIBoardCanvas.h

*/

#ifndef _UIBOARDCANVAS_H_
#define _UIBOARDCANVAS_H_

class Event;
class UITile;
class TipManager;
class Board;
class NodeBase;
class NodeLabel;
class XmlNode;
class DelayedExplosionCheck;
class DelayedExplosion;

// size: 0xE8 (232)
class UIBoardCanvas {
public:

  Array<Array<UITile*>*> m_pTiles; // 0x4
  XmlNode* field_14; // 0x14

  int field_20; // 0x20

  Board* m_pBoard; // 0x24
  bool m_bShowMines; // 0x28

  NodeLabel* m_pMinesRemainingLabel; // 0x58
  NodeLabel* m_pTimeElapsedLabel; // 0x5C

  int m_MinBoardHeight; //0x7C
  int m_MaxBoardHeight; // 0x80
  int m_MinBoardWidth; // 0x84
  int m_MaxBoardWidth; // 0x88
  int m_MinMines; // 0x8C
  int m_MaxMines; // 0x90
  int m_MaxMinesPercent; // 0x94

  UITile* m_pHighlightedTile; // 0x98

  UITile* field_9C;

  TipManager* m_pTipManager; // 0xA4

  bool field_AC; // 0xAC (used in ToggleFlag)
  bool m_bPlayOnlyFirstLoseSound; // 0xAD

  Array<DelayedExplosionCheck*> m_pDelayedExplosionChecks; // 0xB0
  Array<DelayedExplosion*> m_pDelayedExplosions; // 0xC0
  Array<UITile*> m_pAnimatingTiles; // 0xD0

  void PlayTileRevealSound(int numTilesRevealed);
  void ToggleFlag(UITile* tile);
  void ShowTipMessage(wchar_t* message);
  void HideTip();
  void ClearHighlightTile();
  void SetHighlightTile(UITile* tile);
  UIBoardCanvas();
  bool DoRevealAction(UITile* tile);
  UITile* FindTileWithBack(NodeBase* node);
  void DoDisarmAction();
  void HandleEvent(Event* event);
  bool IsDisarmComplete();
  bool IsMineTripComplete();
  void disarmTilesAtYPos(int yPos);
  void RefreshLabels();

  void removeDelayedExplosionCheck(DelayedExplosionCheck* expchk);
  void clearExplosionCheckers();
  void removeDelayedExplosion(DelayedExplosion* exp);
  void removeAnimatingTile(UITile* tile);

  UITile* getTile(unsigned int x, unsigned int y);

  void ClearAnimations();

  void Refresh(bool bForceRefresh);
  void MakeAllTilesDirty();
  void SetShowMines(bool bShowMines);
  void SetAllTilesTopAlpha(int alpha);
};

#endif // _UIBOARDCANVAS_H_
