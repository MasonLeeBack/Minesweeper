#include "MSLog.h"

const wchar_t* MsLog::MsLogResolver(unsigned int LogType)
{
  switch (LogType) {
  case LOG_GENERAL:
    return L"General";
  case LOG_ERROR:
    return L"Err";
  case LOG_WARNING:
    return L"Warn";
  case LOG_EVENTS:
    return L"Events";
  case LOG_SCORING:
    return L"Scoring";
  case LOG_BOARDLOGIC:
    return L"BoardLogic";
  case LOG_LOADSAVE:
    return L"LoadSave";
  case LOG_SOUND:
    return L"Sound";
  }

  return 0;
}
