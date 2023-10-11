/*

OberEngine Decompilation

File name:
  font.cpp

*/

#include "stdafx.h"
#include "font.h"
#include "resourcemanager.h"
#include <logger.h>

Font::Font(HFONT hFont, ID3DXFont* pD3DXFont, int height, bool unknown)
{
  m_hDC = NULL;
  m_iField14 = NULL;
  m_hFont = hFont;
  m_pD3DXFont = pD3DXFont;
  m_FontHeight = height;
  m_bUnknown = unknown;
}

Font::~Font()
{
  if (m_hDC) {
    DeleteDC(m_hDC);
  }

  if (m_pD3DXFont) {
    m_pD3DXFont->Release();
    m_pD3DXFont = NULL;
  }

  if (m_FontCache.count != 0) {
    for (int i = 0; i < m_FontCache.count; i++) {
      m_FontCache.data[i].Cleanup();
    }
  }

  m_FontCache.count = 0;
}

bool Font::Initialize()
{
  m_hDC = CreateCompatibleDC(NULL);

  if (!m_hDC) {
    LOG(2, L"CreateCompatibleDC Failed: %d", GetLastError());
    return false;
  }

  return true;
}

void Font::PrepReset()
{
  LOG(2, L"Invalidating a font cache");

  for (int i = 0; i < m_FontCache.count; i++)
  {
    g_pResourceManager->DestroyResource(this);
    m_FontCache.data[i].Cleanup();
  }
  m_FontCache.count = 0;

  m_hDC = NULL;

  if (m_pD3DXFont) {
    m_pD3DXFont->Release();
    m_pD3DXFont = NULL;
  }
}

void Font::OnDeviceLost()
{
  m_hDC = CreateCompatibleDC(NULL);
}

void Font::SetDxFont(ID3DXFont* font, int height, bool unknown)
{
  if (m_pD3DXFont) {
    m_pD3DXFont->Release();
    m_pD3DXFont = NULL;
  }

  m_pD3DXFont = font;
  m_FontHeight = height;
  m_bUnknown = unknown;
}

void Font::SetHFont(HFONT font)
{
  m_hFont = font;
}

BOOL Font::VerifyPow2(unsigned int num)
{
  return num == (num & -num);
}
