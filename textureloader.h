/*

OberEngine Decompilation
Original Game: Purble Place

*/

#ifndef _TEXTURELOADER_H_
#define _TEXTURELOADER_H_

class TextureLoader
{
public:
  static HRESULT CreateTextureFromFileInMemory(IDirect3DDevice9* pDevice, const void* pData, void* Src, IDirect3DTexture9** pTexture, unsigned int* Width, unsigned int* Height);
};

#endif // _TEXTURELOADER_H_
