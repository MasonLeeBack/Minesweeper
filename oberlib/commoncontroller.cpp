/*

OberEngine Decompilation
Original Game: Purble Place

*/

#include "oberlib.h"
#include <Xinput.h>

CommonControllerThread::CommonControllerThread(HWND hWnd, int a2, IControllerInterface* a3)
{
  m_pController = new CommonController(hWnd, a2, a3);
}

CommonControllerThread::~CommonControllerThread()
{
  delete m_pController;
}

void CommonControllerThread::ActivateRumble(bool bLeftMotor, unsigned short motorSpeed)
{
  XINPUT_VIBRATION vibration = {};

  if (bLeftMotor)
    vibration.wLeftMotorSpeed = motorSpeed;
  else
    vibration.wRightMotorSpeed = motorSpeed;

  XInputSetState(0, &vibration);
}

void CommonControllerThread::DeactivateRumble(bool bLeftMotor)
{
  XINPUT_VIBRATION vibration = {};

  if (bLeftMotor)
    vibration.wLeftMotorSpeed = 0;
  else
    vibration.wRightMotorSpeed = 0;

  XInputSetState(0, &vibration);
}

DWORD CommonControllerThread::ThreadProc(LPVOID lpParameter)
{
  while (IsRunning())
  {
    m_pController->Poll();
    Sleep(25);
  }
  return 0;
}