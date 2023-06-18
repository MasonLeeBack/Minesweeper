/*

OberEngine Decompilation
Original Game: Purble Place

*/

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>

LPCWSTR GetHResult(HRESULT hr)
{
  switch (hr)
  {
  case S_OK:
    return L"S_OK";
  case S_FALSE:
    return L"S_FALSE";
  case E_NOTIMPL:
    return L"E_NOTIMPL";
  case E_FAIL:
    return L"E_FAIL";
  case DISP_E_EXCEPTION:
    return L"DISP_E_EXCEPTION";
  case E_OUTOFMEMORY:
    return L"E_OUTOFMEMORY";
  case E_INVALIDARG:
    return L"E_INVALIDARG";
  case D3DERR_OUTOFVIDEOMEMORY:
    return L"D3DERR_OUTOFVIDEOMEMORY";
  case D3DERR_WRONGTEXTUREFORMAT:
    return L"D3DERR_WRONGTEXTUREFORMAT";
  case D3DERR_UNSUPPORTEDCOLORARG:
    return L"D3DERR_UNSUPPORTEDCOLORARG";
  case D3DERR_DRIVERINTERNALERROR:
    return L"D3DERR_DRIVERINTERNALERROR";
  case D3DERR_NOTFOUND:
    return L"D3DERR_NOTFOUND";
  case D3DERR_DEVICELOST:
    return L"D3DERR_DEVICELOST";
  case D3DERR_DEVICENOTRESET:
    return L"D3DERR_DEVICENOTRESET";
  case D3DERR_NOTAVAILABLE:
    return L"D3DERR_NOTAVAILABLE";
  case D3DERR_INVALIDCALL:
    return L"D3DERR_INVALIDCALL";
  case D3DERR_DEVICEREMOVED:
    return L"D3DERR_DEVICEREMOVED";
  case D3DXERR_INVALIDDATA:
    return L"D3DXERR_INVALIDDATA";
  default:
    return L"Unknown HR";
  }
}