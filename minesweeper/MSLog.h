/*

Minesweeper Decompilation

File name:
  MSLog.h

*/

#ifndef _MSLOG_H_
#define _MSLOG_H_

enum class ELogType {
  General = 0x10000,
  Error = 0x20000,
  Warning = 0x40000,
  Events = 0x80000,
  Scoring = 0x100000,
  BoardLogic = 0x200000,
  LoadSave = 0x400000,
  Sound = 0x800000,
};

class MsLog {
public:
  static const wchar_t* MsLogResolver(unsigned int LogType);
};

#endif // _MSLOG_H_
