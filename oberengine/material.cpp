/*

OberEngine Decompilation

File name:
  material.cpp

*/

#include "stdafx.h"
#include "material.h"

Material::SavedRender::SavedRender()
{
  arr_1 = new int[16];
  CheckAllocation(arr_1);
  arr_2 = new int[16];
  CheckAllocation(arr_2);

  field_C = -1;
  field_10 = 0.0f;
  field_8 = 0;
  field_14 = 0;
  field_16 = 0;
  field_17 = 0;
  field_18 = 0;
  field_15 = 1;
}

Material::SavedRender::~SavedRender()
{
  delete[] arr_1;
  delete[] arr_2;
}
