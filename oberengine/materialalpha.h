/*

OberEngine Decompilation

File name:
  materialalpha.h

*/

#ifndef _MATERIALALPHA_H_
#define _MATERIALALPHA_H_

#include "material.h"

// size: 0x24 (36)
class MaterialAlpha : public Material {
public:
  IDirect3DVertexBuffer9* m_pVertexBuffer; // 0x18
  IDirect3DIndexBuffer9* m_pIndexBuffer; // 0x1C
  int m_VertexSize; // 0x20

  MaterialAlpha();
  ~MaterialAlpha();

  bool Initialize();
  void PrepReset();
  HRESULT OnDeviceLost();
};

#endif // _MATERIALALPHA_H_
