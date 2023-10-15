/*

Minesweeper Decompilation

File name:
  Stash.h

*/

#ifndef _STASH_H_
#define _STASH_H_

#include <array.h>

struct FileData {
  unsigned int size;
  char* data;
};

class Stash {
  Array<FileData*> m_pBuffers;
public:
  Stash();
  ~Stash();

  bool FileExists(const wchar_t* lpFileName, unsigned long csidl);

  bool RemoveFile(const wchar_t* lpFileName, unsigned long csidl);
  bool LoadFile(const wchar_t* lpFileName, unsigned long csidl);
  bool SaveFile(const wchar_t* lpFileName, unsigned long csidl, bool bBackup);

  bool GetBuffer(unsigned int id, unsigned int* size, char** data);
  bool SetBuffer(unsigned int id, unsigned int size, char* data);

  void Cleanup();
};

#endif // _STASH_H_
