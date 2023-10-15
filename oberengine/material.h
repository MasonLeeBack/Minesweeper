/*

OberEngine Decompilation

File name:
  material.h

*/

#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include <array.h>

// size: 0x18 (24)
class Material {
  // size: 0x1C (28)
  class SavedRender {
  public:
    void* arr_1; // 0x0
    void* arr_2; // 0x4
    IDirect3DTexture9* field_8; // 0x8
    int field_C; // 0xC
    float field_10; // 0x10
    bool field_14; // 0x14
    bool field_15; // 0x15
    bool field_16; // 0x16
    bool field_17; // 0x17
    bool field_18; // 0x18

    SavedRender();
    ~SavedRender();
  };

  Array<SavedRender*> m_pSavedRenders; // 0x4
  int field_14; // 0x14 (count of some sort)
public:

};

#endif // _MATERIAL_H_
