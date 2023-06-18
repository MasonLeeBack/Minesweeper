/*

OberEngine Decompilation
Original Game: Purble Place

*/

#ifndef _THREAD_H_
#define _THREAD_H_

class Thread
{
public:
  Thread();
  ~Thread();

  void End();
  bool IsRunning();
  void Begin();

private:
  HANDLE m_hThread;
  DWORD m_dwThreadID;

public:
  DWORD(*ThreadProc)(LPVOID lpParameter);

private:
  bool m_bRunning;
};

#endif // _THREAD_H_
