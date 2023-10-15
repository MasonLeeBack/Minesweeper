/*

OberEngine Decompilation

File name:
  materialadditive.h

*/

#ifndef _MATERIALADDITIVE_H_
#define _MATERIALADDITIVE_H_

#include "material.h"

// size: 0x24 (36)
class MaterialAdditive : public Material {
  IDirect3DVertexBuffer9* m_pVertexBuffer; // 0x18
  IDirect3DIndexBuffer9* m_pIndexBuffer; // 0x1C
  int m_VertexSize; // 0x20

  MaterialAdditive();
  ~MaterialAdditive();

  bool Initialize();
  void PrepReset();
  HRESULT OnDeviceLost();
};

#endif // _MATERIALADDITIVE_H_
