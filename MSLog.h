/*

Minesweeper Decompilation

*/

#ifndef _MSLOG_H_
#define _MSLOG_H_

enum ELogType {
  LOG_GENERAL = 0x10000,
  LOG_ERROR = 0x20000,
  LOG_WARNING = 0x40000,
  LOG_EVENTS = 0x80000,
  LOG_SCORING = 0x100000,
  LOG_BOARDLOGIC = 0x200000,
  LOG_LOADSAVE = 0x400000,
  LOG_SOUND = 0x800000,
};

class MsLog {
public:
  static const wchar_t* MsLogResolver(unsigned int LogType);
};

#endif // _MSLOG_H_
