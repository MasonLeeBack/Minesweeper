/*

Minesweeper Decompilation

File name:
  Stash.cpp

*/

#include <Windows.h>

#include "Stash.h"

#include <logger.h>

Stash::Stash()
{
}

Stash::~Stash()
{
  Cleanup();
}

void Stash::Cleanup()
{
  if (m_pBuffers.count != 0) {
    for (int i = 0; i < m_pBuffers.count; ++i) {
      FileData** data = &m_pBuffers.data[i];
      if (*data) {
        delete[] (*data)->data;
        m_pBuffers.data[i]->data = NULL;
        delete m_pBuffers.data[i];
        m_pBuffers.data[i] = NULL;
      }
    }
  }

  m_pBuffers.count = 0;

  m_pBuffers.FreeExtra();
}

bool Stash::FileExists(const wchar_t* lpFileName, unsigned long csidl)
{
  HANDLE hFile;

  if (!csidl) {
    hFile = CreateFile(lpFileName, GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (hFile == INVALID_HANDLE_VALUE)
      return false;

    CloseHandle(hFile);
  }
  else {
    hFile = CreateSpecialFolderFile(lpFileName, 1, csidl, 1, 102);
    if (hFile == INVALID_HANDLE_VALUE)
      return false;

    CloseSpecialFolderFile(hFile, csidl, 1);
  }

  return true;
}

bool Stash::RemoveFile(const wchar_t* lpFileName, unsigned long csidl)
{
  return DeleteSpecialFolderFile(lpFileName, csidl);
}

bool Stash::LoadFile(const wchar_t* lpFileName, unsigned long csidl)
{
  Cleanup();


}

bool Stash::GetBuffer(unsigned int id, unsigned int* size, char** data)
{
  if (id >= m_pBuffers.count) {
    LOG(0x80, L"Stash::GetBuffer(): Invalid buffer id(%u)", id);
    return false;
  }

  *size = m_pBuffers.data[id]->size;
  *data = m_pBuffers.data[id]->data;

  return true;
}

bool Stash::SetBuffer(unsigned int id, unsigned int size, char* data)
{
  return false;
}
