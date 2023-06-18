/*

OberEngine Decompilation
Original Game: Purble Place

*/

#ifndef _COMMONCONTROLLER_H_
#define _COMMONCONTROLLER_H_

#include "thread.h"

class CommonController
{
private:
  HWND hWnd;
public:

  bool Poll();
};

class CommonControllerThread : public Thread
{
public:
  CommonControllerThread(HWND hWnd, int a2, struct IControllerInterface* a3);
  ~CommonControllerThread();

  // Used in minesweeper
  void ActivateRumble(bool bLeftMotor, unsigned short motorSpeed);
  void DeactivateRumble(bool bLeftMotor);

  DWORD ThreadProc(LPVOID lpParameter);

private:
  CommonController* m_pController;
};

extern CommonControllerThread* g_pCommonController;

#endif // _COMMONCONTROLLER_H_
