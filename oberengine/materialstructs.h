/*

OberEngine Decompilation

File name:
  materialstructs.h

*/

#ifndef _MATERIALSTRUCTS_H_
#define _MATERIALSTRUCTS_H_

struct float4 {
  float x, y, z, w;
};

struct float2 {
  float x, y;
};

class MaterialBasicVertex {
public:
  static const DWORD FVF = D3DFVF_TEX1 | D3DFVF_DIFFUSE | D3DFVF_XYZRHW;

  float4 position;
  DWORD diffuse;
  float2 tex;
};

class AddVertex {
public:
  static const DWORD FVF = D3DFVF_TEX1 | D3DFVF_DIFFUSE | D3DFVF_XYZRHW;

  float4 position;
  DWORD diffuse;
  float2 tex;
};

#endif // _MATERIALSTRUCTS_H_
