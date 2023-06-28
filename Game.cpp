/*

Minesweeper Decompilation

*/

#include "Game.h"
#include "Board.h"
#include "UIBoardCanvas.h"
#include <time.h>

#include <OberLib/str.h>
#include <OberEngine/rendermanager.h>

Game* g_Game = NULL;
const wchar_t* gameXml = L"UI\Minesweeper.xml";
const wchar_t* saveGameFilename = L"Minesweeper.MineSweeperSave-ms";
int g_RandomSeed;

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
  if (gameState == GAMESTATE_3 || gameState == GAMESTATE_4 && canvas)
  {
    unknownFloat = 0.0f;
    canvas->ClearAnimations();
    GameAudio::StopAllSounds();
  }
}

bool Game::RequestFlagToggle()
{
  NodeBase* focusedNode;
  UITile* tile;

  if (canvas && board && gameState == GAMESTATE_PLAYING) {
    focusedNode = g_pUserInterface->GetCurrentFocus();

    if (focusedNode) {
      tile = canvas->FindTileWithBack(focusedNode);
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

  if (!bCanSetAnimations || !board || !canvas) {
    return;
  }
}

int Game::AttemptReveal(int x, int y)
{
  return board->AttemptReveal(x, y);
}

void Game::OnSecondElapsed()
{
  if (g_Game) {
    if (g_Game->gameState == GAMESTATE_PLAYING) {
      g_Game->board->TimeElapsed = g_Game->board->TimeElapsed + 1.0f;
      g_Game->canvas->RefreshLabels();
      InvalidateRect(g_hWnd, 0, 0);
    }
  }
}

void Game::CreateScene()
{
  baseScene = NodeBase::CreateFromType(L"Base", 0, 1);
  if (!baseScene) {
    SharedDialogs::FatalDialog::Show(0);
  }
  // To do: Determine what this access role is
  baseScene->SetAccessible(0, 0x3B);
}

void Game::SetTipsEnabled(bool bEnabled)
{
  bTipsEnabled = bEnabled;
  if (bEnabled == false)
  {
    if (canvas)
      canvas->HideTip();
  }
}

void Game::SetSoundEnabled(bool bEnabled)
{
  bSoundEnabled = g_pAudio->GetDS() != NULL && bEnabled;
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
  bSoundEnabled = bEnabled;
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
  if (canvas)
    canvas->MakeAllTilesDirty();

  switch (state) {
  case GAMESTATE_PLAYING:
  case GAMESTATE_2:
    break;
  case GAMESTATE_3:
  case GAMESTATE_4:
    ToggleChangeSettingsMenus(1);
    break;
  default:
    StrErr(Str(L"Unknown state"), 1); // this may not work
  }

  switch (state) {
  case GAMESTATE_PLAYING:
  case GAMESTATE_3: {
    if (canvas) {
      canvas->RefreshLabels();
      break;
    }
  }
  case GAMESTATE_2:
    return;
  case GAMESTATE_4:
    break;
  default: {
    StrErr(Str(L"Unknown state"), 1); // this may not work
    return;
  }
  }
}

void Game::freeGameRes(bool bFreeScene)
{
  if (board) {
    delete board;
    board = NULL;
  }
  if (bFreeScene) {
    baseScene->DeleteSelf();

    if (canvas) {
#error todo
    }
  }
}

bool Game::InitUi()
{
  bool result;

  g_iMinesweeperFudge = true;
  Engine_SetBackMode(1, 0, 1);
  CreateScene();
  canvas = new UIBoardCanvas();

  result = canvas->Initialize();
  if (result) {
    wchar_t* local = LocalizeMessage(L"|54922|ACC|Minesweeper//accessibility root node name");
    g_pRenderManager->m_BaseNode->SetAccessName(local);
    LocalFree(local);
    RequestSetState(GAMESTATE_PLAYING);
    canvas->Refresh(true);
    CacheSounds();

    result = true;
  }

  return result;
}

bool Game::IsReadyForInput()
{
  if (gameState != GAMESTATE_PLAYING
    || board == NULL || board->var_48 || firstPlay == true)
  {
    return false;
  }

  return bReadyForInput != false;
}

void Game::SetAnimationsEnabled(bool bEnabled)
{
  bool clearAnim;

  bCanSetAnimations = CanSetAnimationsEnabled() && bEnabled;
  if (GetClientAreaAnimation())
    clearAnim = bCanSetAnimations;
  else
    clearAnim = false;

  bCanSetAnimations = clearAnim;

  if (!clearAnim)
  {
    if (canvas) {
      canvas->ClearAnimations();
    }
  }
}

void Game::SetUserOptionAnimationsEnabled(bool bEnabled)
{
  bAnimationsEnabled = bEnabled;
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
  RequestSetState(2);
  RemoveSavedGame();
  UIDialogs::StartWinDialog();
}

void Game::Lose()
{
  RequestSetState(2);
  RemoveSavedGame();
  UIDialogs::StartLoseDialog();
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
  if (gameStyleIndex == gameStyle && boardStyleIndex == boardStyle)
    return false;

  boardStyleIndex = boardStyle;
  gameStyleIndex = gameStyle;

  if (bRebuildCanvas) {
    // Save the state of the clicked variable and restore
    // after rebuilding
    clicked = board->RevealsAttempted;
    RebuildCanvas();
    board->RevealsAttempted = clicked;
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
  g_Game = this;

  baseScene = NULL;
  canvas = NULL;
  board = NULL;

  winLoseDialogX = -1;
  winLoseDialogY = -1;

  gameState = GAMESTATE_NONE;

  boardStyleIndex = 0;
  gameStyleIndex = 0;

  // 197 = 0
  firstPlay = true;
  // 193 = 0
  autoContinueSaveGames = false;
  autoSaveGameOnExit = false;
  // 192 = 0;

  // 47 = 0;
  unknownVariable = true;
  bCanSetAnimations = true;
  bSoundEnabled = true;
  bAnimationsEnabled = true;
  bQuestionMarksEnabled = true;
  bTipsEnabled = true;
  bUserPrefersKeyboard = false;

  preferredDifficulty = DIFFICULTY_EASY;
  customWidth = EDifficultyToWidth(preferredDifficulty);
  customHeight = EDifficultyToHeight(preferredDifficulty);
  customMines = EDifficultyToMineCount(preferredDifficulty);

  // figure out this data id
  timeRecorder->SetDataId(0x17C7u);

  Reset(0, 0, 0);
  RequestSetState(GAMESTATE_NONE);

  bReadyForInput = 0;
  // 217 = 0;

  bTimerEnabled = false;
}

void Game::RequestStartNewGame()
{
  if (gameState == GAMESTATE_PLAYING && board->RevealsAttempted > 0)
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
      // make sense of this bologna
      PrintFatalErrorAndQuit(103);
    }
  }

  return g_Game;
}
