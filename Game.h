/*

Minesweeper Decompilation

*/

#ifndef _GAME_H_
#define _GAME_H_

#include "Minesweeper_const.h"

enum EGameState {
  GAMESTATE_NONE = 0,
  GAMESTATE_PLAYING = 1,
  GAMESTATE_2 = 2,
  GAMESTATE_3 = 3,
  GAMESTATE_4 = 4,
};

enum ESound {

};

class Game
{
public:
  struct NodeBase* baseScene; // 2
  struct UIBoardCanvas* canvas; // 3
  class Board* board; // 4
  struct XmlNode* someXmlNode; // 5

  int winLoseDialogX; // 8
  int winLoseDialogY; // 9

  EGameState gameState; // 10

  float unknownFloat; // 11

  int boardStyleIndex; // 12
  int gameStyleIndex; // 13

  int unknownVariable; // 24
  int bCanSetAnimations; // 25
  int bSoundEnabled; // 26
  int bAnimationsEnabled; // 27
  int bQuestionMarksEnabled; // 28
  int bTipsEnabled; // 29
  int bUserPrefersKeyboard; // 30 (might be larger)

  GameStats* stats; // 42

  EDifficulty preferredDifficulty; // 50
  int customWidth; // 51
  int customHeight; // 52
  int customMines; // 53

  class CSQMTimeRecorder* timeRecorder; // 152

  class GameStats* gameStats; // 168 (is this a pointer or embedded?)

  int autoContinueSaveGames; // 194
  int firstPlay; // 195
  int autoSaveGameOnExit; // 196

  int bReadyForInput; // 216

  bool bTimerEnabled; // 218

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
