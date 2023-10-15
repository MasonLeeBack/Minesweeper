/*

Minesweeper Decompilation

File name:
  window.cpp

*/

#include <windows.h>

#include "Game.h"
#include "UITile.h"
#include "Board.h"
#include "UIBoardCanvas.h"
#include "Minesweeper_const.h"
#include "UIDialogs.h"

#include <time.h>

#include <audio.h>
#include <gameaudio.h>
#include <engine.h>
#include <sqmtimerecorder.h>
#include <dialoghelper.h>
#include <str.h>
#include <rendermanager.h>
#include <userinterface.h>
#include <localize.h>

Game* g_Game = NULL;
const wchar_t* gameXml = L"UI\Minesweeper.xml";
const wchar_t* saveGameFilename = L"Minesweeper.MineSweeperSave-ms";
int g_RandomSeed;

void Game::PlaySound(ESound sound, int volume)
{
}

bool Game::CanSetAnimationsEnabled()
{
  return !g_pRenderManager->IsRGBRast();
}

void Game::RandomizeSeedOnTime()
{
  unsigned int ltime;

  ltime = time(0);
  SetRandomSeed(ltime);
}

void Game::ToggleChangeSettingsMenus(bool bEnabled)
{
  if (g_hMainMenu) {
    // Todo: figure these resource offsets out
    EnableMenuItem(g_hMainMenu, 40002, bEnabled ? MF_ENABLED : MF_DISABLED | MF_GRAYED);
    EnableMenuItem(g_hMainMenu, 40004, bEnabled ? MF_ENABLED : MF_DISABLED | MF_GRAYED);
  }
}

void Game::RequestSkipAnimation()
{
  if (m_GameState == EGameState::Won || m_GameState == EGameState::Lost && m_pCanvas)
  {
    unknownFloat = 0.0f;
    m_pCanvas->ClearAnimations();
    GameAudio::StopAllSounds();
  }
}

bool Game::RequestFlagToggle()
{
  NodeBase* focusedNode;
  UITile* tile;

  if (m_pCanvas && m_pBoard && m_GameState == EGameState::Playing) {
    focusedNode = g_pUserInterface->GetCurrentFocus();

    if (focusedNode) {
      tile = m_pCanvas->FindTileWithBack(focusedNode);
      if (tile) {
        tile->ToggleFlag();
        return true;
      }
    }
  }

  return false;
}

void Game::DoNewBoardAnimation()
{

  if (!m_bCanSetAnimations || !m_pBoard || !m_pCanvas) {
    return;
  }
}

int Game::AttemptReveal(int x, int y)
{
  return m_pBoard->AttemptReveal(x, y);
}

void Game::OnSecondElapsed()
{
  if (g_Game) {
    if (g_Game->m_GameState == EGameState::Playing) {
      g_Game->m_pBoard->m_TimeElapsed = g_Game->m_pBoard->m_TimeElapsed + 1.0f;
      g_Game->m_pCanvas->RefreshLabels();
      InvalidateRect(g_hWnd, 0, 0);
    }
  }
}

void Game::CreateScene()
{
  m_pBaseScene = NodeBase::CreateFromType(L"Base", 0, 1);
  if (!m_pBaseScene) {
    SharedDialogs::FatalDialog::Show(0);
  }
  // To do: Determine what this access role is
  m_pBaseScene->SetAccessible(0, 0x3B);
}

void Game::SetTipsEnabled(bool bEnabled)
{
  m_bTipsEnabled = bEnabled;
  if (bEnabled == false)
  {
    if (m_pCanvas)
      m_pCanvas->HideTip();
  }
}

void Game::SetSoundEnabled(bool bEnabled)
{
  m_bSoundEnabled = g_pAudio->GetDS() != NULL && bEnabled;
  CacheSounds();
}

void Game::SetTimerEnabled(bool bEnabled)
{
  if (bTimerEnabled != bEnabled) {
    bTimerEnabled = bEnabled;

    if (bEnabled)
      Engine_RegisterSecondTimer(OnSecondElapsed);
    else
      Engine_RegisterSecondTimer(NULL);
  }
}

void Game::SetUserOptionSoundEnabled(bool bEnabled)
{
  m_bSoundEnabled = bEnabled;
  SetSoundEnabled(bEnabled);
}

bool Game::GetClientAreaAnimation()
{
  int param = TRUE;
  SystemParametersInfo(SPI_GETCLIENTAREAANIMATION, 0, &param, 0);
  return param != 0;
}

void Game::RequestSetState(EGameState state)
{
  if (m_pCanvas)
    m_pCanvas->MakeAllTilesDirty();

  switch (state) {
  case EGameState::Playing:
  case EGameState::Done:
    break;
  case EGameState::Won:
  case EGameState::Lost:
    ToggleChangeSettingsMenus(1);
    break;
  default:
    StrErr(Str(L"Unknown state"), 1); // this may not work
  }

  switch (state) {
  case EGameState::Playing:
  case EGameState::Won: {
    if (m_pCanvas) {
      m_pCanvas->RefreshLabels();
      break;
    }
  }
  case EGameState::Done:
    return;
  case EGameState::Lost:
    break;
  default: {
    StrErr(Str(L"Unknown state"), 1); // this may not work
    return;
  }
  }
}

void Game::freeGameRes(bool bFreeScene)
{
  if (m_pBoard) {
    delete m_pBoard;
    m_pBoard = NULL;
  }
  if (bFreeScene) {
    m_pBaseScene->DeleteSelf();

    if (m_pCanvas) {
#error todo
    }
  }
}

void Game::UpdateMenu()
{
  HMENU menu;

  if (m_pBoardStyles.count == 1 && m_pGameStyles.count == 1) {
    if (g_bDebugEnabled == true) {
      menu = LoadMenu(g_hInstance, MAKEINTRESOURCE(165))
    }
    else {
      menu = LoadMenu(g_hInstance, MAKEINTRESOURCE(166))
    }
  }
  else {
    if (g_bDebugEnabled == false) {
      return;
    }
    menu = LoadMenu(g_hInstance, MAKEINTRESOUCE(164))
  }

  HMENU oldMenu = GetMenu(g_hWnd);
  DestroyMenu(oldMenu);

  SetMenu(g_hWnd, menu);
  DrawMenuBar(g_hWnd);
}

bool Game::InitUi()
{
  bool result;

  g_iMinesweeperFudge = 1;
  Engine_SetBackMode(1, 0, 1);
  CreateScene();
  m_pCanvas = new UIBoardCanvas();

  result = m_pCanvas->Initialize(
          m_pBaseXmlNode,
          m_pBaseScene,
          m_pBoard,
          m_pBoardStyles.data[m_BoardStyleIndex],
          m_pGameStyles.data[m_GameStyleIndex]);
  if (result) {
    wchar_t* local = LocalizeMessage(L"|54922|ACC|Minesweeper//accessibility root node name");
    g_pRenderManager->m_BaseNode->SetAccessName(local);
    LocalFree(local);
    RequestSetState(EGameState::Playing);
    m_pCanvas->Refresh(true);
    CacheSounds();

    result = true;
  }

  return result;
}

void Game::ResetCanvas()
{
  if (m_pCanvas) {
    m_pCanvas->Reset(
      m_pBoard,
      m_pBoardStyles[m_BoardStyleIndex],
      m_pGameStyles[m_GameStyleIndex],
      m_pBoard->m_Difficulty,
      NULL,
      true
    );

    m_pCanvas->Refresh(true);
  }
}

bool Game::IsReadyForInput()
{
  if (m_GameState != EGameState::Playing
    || m_pBoard == NULL || m_pBoard->var_48 || m_bFirstPlay == true)
  {
    return false;
  }

  return m_bReadyForInput != false;
}

void Game::SetAnimationsEnabled(bool bEnabled)
{
  bool clearAnim;

  m_bCanSetAnimations = CanSetAnimationsEnabled() && bEnabled;
  if (GetClientAreaAnimation())
    clearAnim = m_bCanSetAnimations;
  else
    clearAnim = false;

  m_bCanSetAnimations = clearAnim;

  if (!clearAnim)
  {
    if (m_pCanvas) {
      m_pCanvas->ClearAnimations();
    }
  }
}

void Game::SetUserOptionAnimationsEnabled(bool bEnabled)
{
  m_bAnimationsEnabled = bEnabled;
  SetAnimationsEnabled(bEnabled);
}

void Game::ToXML(SerialXML* xml)
{

  xml->WriteEndTag(L"Game", 1);
}

bool Game::DoesSaveExist()
{
  SerialXML xml;

  return xml.FileExists(saveGameFilename, 40);
}

void Game::RemoveSavedGame()
{
  SerialXML xml;

  xml.RemoveFile(saveGameFilename, 40);
}

void Game::Win()
{
  RequestSetState(EGameState::Done);
  RemoveSavedGame();
  UIDialogs::StartWinDialog();
}

void Game::Lose()
{
  RequestSetState(EGameState::Done);
  RemoveSavedGame();
  UIDialogs::StartLoseDialog();
}

void Game::DisarmBoard()
{
  if (m_GameState != EGameState::Playing)
    return;

  if (m_pBoard->m_Difficulty != EDifficulty::Custom) {
    m_GameStats.AddNewScore(m_pBoard->m_Difficulty, (int)floorf(m_pBoard->m_TimeElapsed), true);
    Game::Save(false, false);
  }

  RequestSetState(EGameState::Won);

  if (field_18) {
    GameAudio::ForceLoadResource(1, false);
    Game::PlaySoundW((ESound)1, 100);
  }

  m_pCanvas->DoDisarmAction();
}

void Game::ExplodeBoard()
{
  if (m_GameState != EGameState::Playing)
    return;

  if (m_pBoard->m_Difficulty != EDifficulty::Custom)

  if (m_bCanSetAnimations == true) {
    RequestSetState(EGameState::Lost);
    m_pCanvas->DoMineExplodeAction();
  }
  else {
    Lose();
  }
}

void Game::PrintFatalErrorAndQuit(int errorCode)
{
  // todo: figure out these resource offsets
  DialogHelper::ShowMessageBox(0x66, errorCode, 1, 0xFFFE, 0, 0, 1);
  if (g_Game) {
    delete g_Game;
    g_Game = NULL;
  }
  PostQuitMessage(1);
}

bool Game::SetArt(int boardStyle, int gameStyle, bool bRebuildCanvas)
{
  int clicked;

  // check to see if the art is already set
  if (m_GameStyleIndex == gameStyle && m_BoardStyleIndex == boardStyle)
    return false;

  m_BoardStyleIndex = boardStyle;
  m_GameStyleIndex = gameStyle;

  if (bRebuildCanvas) {
    // Save the state of the clicked variable and restore
    // after rebuilding
    clicked = m_pBoard->m_RevealsAttempted;
    RebuildCanvas();
    m_pBoard->m_RevealsAttempted = clicked;
  }

  return true;
}

bool Game::initLogic(Str gameXml)
{
  bool result = false;

  if (parseXml(gameXml))
  {
    result = true;
    Load(1, 0, 0);
  }

  // There's a call to Str's destructor here -
  // not sure if it's automatically added
  // since it's out of scope
  // Str::~Str(&gameXml);

  return result;
}

Game::Game()
{
  m_pTimeRecorder = NULL;

  g_Game = this;

  m_WinLoseDialogX = -1;
  m_WinLoseDialogY = -1;

  m_pBoard = NULL;
  m_pCanvas = NULL;
  m_pBaseScene = NULL;

  m_GameState = EGameState::None;

  m_GameStyleIndex = 0;
  m_GameStyleIndex = 0;

  // 197 = 0
  m_bFirstPlay = true;
  m_bUseRandomArt = false;
  m_bAutoContinueSaveGames = false;
  m_bAutoSaveGameOnExit = false;
  // 192 = 0;

  // 47 = 0;
  field_18 = true;
  m_bCanSetAnimations = true;
  m_bSoundEnabled = true;
  m_bAnimationsEnabled = true;
  m_bQuestionMarksEnabled = true;
  m_bTipsEnabled = true;
  m_bUserPrefersKeyboard = false;

  m_Difficulty = EDifficulty::Beginner;
  m_CustomWidth = EDifficultyToWidth(m_Difficulty);
  m_CustomHeight = EDifficultyToHeight(m_Difficulty);
  m_CustomMines = EDifficultyToMineCount(m_Difficulty);

  // figure out this data id
  m_pTimeRecorder->SetDataId(0x17C7u);

  Reset(0, 0, 0);
  RequestSetState(EGameState::None);

  m_bReadyForInput = 0;
  // 217 = 0;

  m_bTimerEnabled = false;
}

void Game::RequestStartNewGame()
{
  if (m_GameState == EGameState::Playing && m_pBoard->m_RevealsAttempted > 0)
    UIDialogs::StartNewGameDialog();
  else
    Reset(1, 0, 1);
}

void Game::RestartLast()
{
  Reset(1, 1, 1);
}

Game* Game::SafeGetSingleton()
{
  if (!g_Game)
  {
    g_Game = new Game();
    if (!g_Game && !g_Game->initLogic(Str(gameXml))) {
      PrintFatalErrorAndQuit(103);
    }
  }

  return g_Game;
}

void Game::AddLoss()
{
  float timeElapsed = (floorf(m_pBoard->m_TimeElapsed));
  m_GameStats.AddNewScore(m_Difficulty, timeElapsed, false);
}

int Game::GetUnflaggedMineCount()
{
  if (m_GameState == EGameState::Won) {
    return 0;
  }
  else {
    return m_pBoard->m_Mines - m_pBoard->m_FlagsPlaced;
  }
}
