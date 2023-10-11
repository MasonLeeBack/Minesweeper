/*

OberEngine Decompilation

File name:
  font.h

*/

#ifndef _FONT_H_
#define _FONT_H_

#include <array.h>

class Font {
  class CachedEntry {
  public:
    void Cleanup();
  };

  Array<CachedEntry> m_FontCache; // 0x4
  int m_iField14; // 0x14
  HFONT m_hFont; // 0x18
  HDC m_hDC; // 0x1C
  ID3DXFont* m_pD3DXFont; // 0x20
  int m_FontHeight; // 0x24
  bool m_bUnknown; // 0x28 (this is used with DoubleDPI)

public:
  Font(HFONT hFont, ID3DXFont* pD3DXFont, int height, bool unknown);
  ~Font();

  bool Initialize();
  void PrepReset();

  void OnDeviceLost();

  void SetDxFont(ID3DXFont* font, int height, bool unknown);
  void SetHFont(HFONT font);

  BOOL VerifyPow2(unsigned int num);
};

#endif // _FONT_H_
