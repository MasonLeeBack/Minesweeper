/*

OberEngine Decompilation
Original Game: Purble Place

*/

#include <d3d9.h>
#include <d3dx9.h>
#include <memory.h>
#include <ddraw.h>

#include <stdint.h>
#include "ext/dds.h"

#include "logger.h"
#include "textureloader.h"

HRESULT TextureLoader::CreateTextureFromFileInMemory(
  IDirect3DDevice9* pDevice,
  const void* pData, void* Src,
  IDirect3DTexture9** pTexture,
  unsigned int* Width,
  unsigned int* Height
  )
{
  HRESULT hr;
  IDirect3DTexture9* pTexture_tmp = NULL;
  DirectX::DDS_HEADER header;
  D3DFORMAT format = D3DFMT_UNKNOWN;
  int depth = 0;

  if (!pDevice && !pData && !Src && !pTexture) {
    LOG(4, L"NULL in parameter list for CreateTextureFromFileInMemory()");
    return D3DERR_INVALIDCALL;
  }

  // Check if pData is a valid DDS file
  if (*(unsigned int*)pData != 0x20534444) {
    LOG(4, L"Input is not a DDS file");
    return D3DXERR_INVALIDDATA;
  }

  // Get the DDS header
  memcpy(&header, (char*)pData + 4, sizeof(DirectX::DDS_HEADER));

  // Set Src variable to the start of the DDS data
  Src = (char*)pData + 4 + sizeof(DirectX::DDS_HEADER);

  // Check the size of the header
  if (header.size != 0x7C) {
    LOG(4, L"Input header is not the correct size (%s found, expected %s)", header.size, 0x7C);
    return D3DXERR_INVALIDDATA;
  }

  // Check the flags for the DDS file
  if (!(header.flags & DDSD_CAPS) || !(header.flags & DDSD_HEIGHT) || !(header.flags & DDSD_WIDTH) || !(header.flags & DDSD_PIXELFORMAT)) {
    LOG(4, L"Invalid flags in DDS source");
    return D3DXERR_INVALIDDATA;
  }

  // Check if the DDS file is a depth texture
  if (header.flags & DDSD_DEPTH) {
    LOG(4, L"We don't support depth textures");
    return D3DXERR_INVALIDDATA;
  }

  // Check the mipmap count, we only support 1
  if (header.flags & DDSD_MIPMAPCOUNT) {
    LOG(4, L"Forced DDS mipmap count to 1");
    header.mipMapCount = 1;
  }

  // Validate settings
  if (header.ddspf.size != 32
    || (header.caps & DDSCAPS_TEXTURE) == 0
    || header.mipMapCount > 1 && ((header.caps & DDSCAPS_MIPMAP) == 0 || (header.caps & DDSCAPS_COMPLEX) == 0)
    || (header.caps2 & DDSCAPS2_CUBEMAP) != 0
    || (header.caps2 & DDSCAPS2_CUBEMAP_POSITIVEX) != 0
    || (header.caps2 & DDSCAPS2_CUBEMAP_NEGATIVEX) != 0
    || (header.caps2 & DDSCAPS2_CUBEMAP_POSITIVEY) != 0
    || (header.caps2 & DDSCAPS2_CUBEMAP_NEGATIVEY) != 0
    || (header.caps2 & DDSCAPS2_CUBEMAP_POSITIVEZ) != 0
    || (header.caps2 & DDSCAPS2_CUBEMAP_NEGATIVEZ) != 0
    || (header.caps2 & DDSCAPS2_VOLUME) != 0) {
    return D3DXERR_INVALIDDATA;
  }

  // Validate that the pixel format is A8R8G8B8
  if ((header.ddspf.flags & DDPF_RGB) != 0)
  {
    if (header.ddspf.RGBBitCount != 32
      || header.ddspf.RBitMask != 0x00FF0000
      || header.ddspf.GBitMask != 0x0000FF00
      || header.ddspf.BBitMask != 0x000000FF
      || header.ddspf.ABitMask != 0xFF000000) {
      LOG(4, L"DDS loader currently only supports the RGB format A8R8G8B8");
      return D3DXERR_INVALIDDATA;
    }

    format = D3DFMT_A8R8G8B8;
    depth = 32;
  }
  else if ((header.ddspf.flags & DDPF_FOURCC) != 0) {
    // Check to see if the FourCC is DXT1, DXT3, or DXT5
    if (header.ddspf.fourCC != MAKEFOURCC('D', 'X', 'T', '1')
      && header.ddspf.fourCC != MAKEFOURCC('D', 'X', 'T', '3')
      && header.ddspf.fourCC != MAKEFOURCC('D', 'X', 'T', '5')) {
      LOG(4, L"DDS loader currently only supports the FOURCC formats DXT1, DXT3, and DXT5");
      return D3DXERR_INVALIDDATA;
    }
    return D3DXERR_INVALIDDATA;
  }

  // Create the texture
  hr = pDevice->CreateTexture(header.width, header.height, header.mipMapCount, 0, format, D3DPOOL_MANAGED, &pTexture_tmp, NULL);
  if (FAILED(hr)) {
    LOG(4, L"CreateTexture failed: %x", hr);
    return D3DXERR_INVALIDDATA;
  }

  // Make sure we have a texture
  if (pTexture_tmp)
  {
    // Check if we have a mipmap
    if (header.mipMapCount == 1)
    {
      unsigned int i = 0;

      while (1) {
        D3DLOCKED_RECT lockedRect;

        // Get the surface description
        D3DSURFACE_DESC desc;
        hr = pTexture_tmp->GetLevelDesc(i, &desc);
        if (FAILED(hr)) {
          break;
        }

        // Calculate the size of the texture
        int size = (depth * header.width * header.height) >> 3;

        // Lock the rect
        hr = pTexture_tmp->LockRect(i, &lockedRect, NULL, 0);
        if (FAILED(hr) || !lockedRect.pBits) {
          pTexture_tmp->Release();
          return hr;
        }

        // Copy the texture data
        memcpy(lockedRect.pBits, Src, size);

        // Unlock the rect
        hr = pTexture_tmp->UnlockRect(i);

        // Set the source offset
        Src = (char*)Src + size;

        // Make sure we unlocked the rect
        if (FAILED(hr)) {
          break;
        }
        
        // Check if we are done
        if (++i >= header.mipMapCount) {
          // Return the texture
          *pTexture = pTexture_tmp;

          // Return the width and height
          if (Width)
            *Width = header.width;
          if (Height)
            *Height = header.height;

          return S_OK;
        }
      }
      
      // We should only get here if we failed
      // to get texture data
      pTexture_tmp->Release();
      return hr;
    }
  }

  return E_FAIL;
}
