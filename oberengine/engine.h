/*

OberEngine Decompilation

File name:
  engine.h

*/

#ifndef _ENGINE_H_
#define _ENGINE_H_

typedef void(*timerCallback)();

extern bool g_bDoubleDPI;
extern int g_bLogFillRate;
extern HWND g_hWnd;

bool ShouldGoHighDPI(unsigned int w, unsigned int h);
void SetDPIFromWindowSize();

class IEngineInterface {
public:
  const wchar_t* GetResourceDllFileName();
  GUID* GetRichGameMediaGameID();
  void GetInitialLayout(unsigned int* width, unsigned int* height);
  int GetContextMenu();
  const wchar_t* GetGdfPath();
  const wchar_t* GetSplashTextFont();
  int GetSplashTextFontSize();
};

void Engine_ResetTimer();
void Engine_RegisterSecondTimer(timerCallback timer);

#endif // _ENGINE_H_
