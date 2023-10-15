/*

Minesweeper Decompilation

File name:
  game.h

*/

#ifndef _GAME_H_
#define _GAME_H_

#include "Minesweeper_const.h"
#include "GameStats.h"

enum class EGameState {
  None = 0,
  Playing = 1,
  Done = 2,
  Won = 3, // win animation
  Lost = 4, // lose animation
};

enum ESound {

};

// size: 0xE0 (224)
class Game
{
public:
  struct NodeBase* m_pBaseScene; // 0x08
  struct UIBoardCanvas* m_pCanvas; // 0x0C
  class Board* m_pBoard; // 0x10
  struct XmlNode* m_pBaseXmlNode; // 0x14

  float unknownFloat; // 11

  bool field_18; // 0x18
  bool m_bCanSetAnimations; // 0x19
  bool m_bSoundEnabled; // 0x1A
  bool m_bAnimationsEnabled; // 0x1B
  bool m_bQuestionMarksEnabled; // 0x1C
  bool m_bTipsEnabled; // 0x1D
  bool m_bUserPrefersKeyboard; // 0x1E (might be larger)

  int m_WinLoseDialogX; // 0x20
  int m_WinLoseDialogY; // 0x24

  EGameState m_GameState; // 0x28

  int m_BoardStyleIndex; // 0x30
  int m_GameStyleIndex; // 0x34

  Array<XmlNode*> m_pBoardStyles; // 0x58

  Array<XmlNode*> m_pGameStyles; // 0x88

  class CSQMTimeRecorder* m_pTimeRecorder; // 0x98

  GameStats m_GameStats; // 0xA8

  bool field_C0; // 0xC0
  bool m_bUseRandomArt; // 0xC1
  bool m_bAutoContinueSaveGames; // 0xC2
  bool m_bFirstPlay; // 0xC3
  bool m_bAutoSaveGameOnExit; // 0xC4
  bool field_C5; // 0xC5

  EDifficulty m_Difficulty; // 0xC8

  int m_CustomWidth; // 0xCC
  int m_CustomHeight; // 0xD0
  int m_CustomMines; // 0xD4

  int m_bReadyForInput; // 0xD8
  bool field_D9; // 0xD9
  bool m_bTimerEnabled; // 0xDA

  void PlaySound(ESound sound, int volume);
  bool CanSetAnimationsEnabled();
  void RandomizeSeedOnTime();
  void ToggleChangeSettingsMenus(bool bEnabled);
  void RequestSkipAnimation();
  bool RequestFlagToggle();
  void CacheSounds();
  void DoNewBoardAnimation();
  int AttemptReveal(int x, int y); // this may not be int
  static void OnSecondElapsed();
  bool GetCanvasDimensions(int* width, int* height);
  void CreateScene();
  void SetTipsEnabled(bool bEnabled);
  void SetSoundEnabled(bool bEnabled);
  void SetTimerEnabled(bool bEnabled);
  void SetUserOptionSoundEnabled(bool bEnabled);
  bool GetClientAreaAnimation();
  void RequestSetState(EGameState state);
  void freeGameRes(bool bFreeScene);
  bool parseXml(Str& str);
  void UpdateMenu();
  bool InitUi();
  void ResetCanvas();
  bool IsReadyForInput();
  void SetTimerEnabled(bool bTimerEnabled);
  void SetAnimationsEnabled(bool bEnabled);
  void SetUserOptionAnimationsEnabled(bool bEnabled);
  ~Game();
  void ToXML(class SerialXML* xml);
  bool FromXML(class SerialXML* xml, class XmlNode* node);
  void SaveGameExplorerStatistics();
  bool DoesSaveExist();
  void RemoveSavedGame();
  void Win();
  void Lose();
  void Save(bool, bool);
  void DisarmBoard();
  void ExplodeBoard();
  static void PrintFatalErrorAndQuit(int errorCode);
  void RebuildCanvas();
  bool SetArt(int boardStyle, int GameStyle, bool bRebuildCanvas);
  bool RandomizeArt(bool bRebuildCanvas);
  bool Load(bool, bool, bool);
  bool initLogic(class Str gameXml);
  void Reset(bool, bool restartLastGame, bool);
  void Update(float time); // this variable doesn't seem to be used
  Game();
  void RequestStartNewGame();
  void RestartLast();
  static Game* SafeGetSingleton();
  void AddLoss();
  int GetUnflaggedMineCount();
};

extern Game* g_Game;

#endif // _GAME_H_
