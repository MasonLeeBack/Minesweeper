/*

Minesweeper Decompilation

*/

#ifndef _ENGINE_H_
#define _ENGINE_H_

class IEngineInterface {
public:
  const wchar_t* GetResourceDllFileName();
  _GUID* GetRichGameMediaGameID();
  void GetInitialLayout(unsigned int* width, unsigned int* height);
  int GetContextMenu();
  const wchar_t* GetGdfPath();
  const wchar_t* GetSplashTextFont();
  int GetSplashTextFontSize();
};

#endif // _ENGINE_H_
