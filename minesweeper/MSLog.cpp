/*

Minesweeper Decompilation

File name:
  MSLog.cpp

*/

#include "MSLog.h"

const wchar_t* MsLog::MsLogResolver(unsigned int LogType)
{
  ELogType type = (ELogType)LogType;

  switch (type) {
  case ELogType::General:
    return L"General";
  case ELogType::Error:
    return L"Err";
  case ELogType::Warning:
    return L"Warn";
  case ELogType::Events:
    return L"Events";
  case ELogType::Scoring:
    return L"Scoring";
  case ELogType::BoardLogic:
    return L"BoardLogic";
  case ELogType::LoadSave:
    return L"LoadSave";
  case ELogType::Sound:
    return L"Sound";
  }

  return 0;
}
