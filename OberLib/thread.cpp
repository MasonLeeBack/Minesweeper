/*

OberEngine Decompilation
Original Game: Purble Place

*/

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "thread.h"

DWORD WINAPI sThreadProc(LPVOID lpParameter)
{
  // Cast the lpParameter back to Thread pointer and invoke the ThreadProc function
  return ((Thread*)lpParameter)->ThreadProc(lpParameter);
}

Thread::Thread()
{
  m_hThread = NULL;
  m_dwThreadID = 0;
  m_bRunning = false;
}

Thread::~Thread()
{
  End();
}

void Thread::End()
{
  if (m_hThread)
  {
    m_bRunning = false;

    // Wait for the thread to exit
    WaitForSingleObject(m_hThread, INFINITE);

    // Close the thread handle
    CloseHandle(m_hThread);
    m_hThread = NULL;
  }
}

bool Thread::IsRunning()
{
  return m_bRunning;
}

void Thread::Begin()
{
  if (m_hThread)
    End();

  m_bRunning = true;

  // Create the thread and pass sThreadProc as the start routine
  m_hThread = CreateThread(NULL, 0, sThreadProc, this, 0, &m_dwThreadID);
}

