/*

OberEngine Decompilation
Original Game: Purble Place

*/

#ifndef _SORTEDLISTW_H_
#define _SORTEDLISTW_H_

#include <memory>
#include <string>
#include "utils.h"

template <class T>
class SortedListW
{
public:
  wchar_t** field_0;
  T* field_4;
  unsigned int field_8;
  unsigned int field_C;
  int field_10;

  void Add(wchar_t* wszKey, T value);
  int BinSearch(wchar_t* wszKey, int a2, int a3);
  bool TryGet(wchar_t* wszKey, T* result);
  void RemoveAll(bool bFreeMemory);

  SortedListW(unsigned int InitialListSize);
  ~SortedListW();
};

template<class T>
inline void SortedListW<T>::Add(wchar_t* wszKey, T value)
{
  // again, i do not care. Should work fine on x86 and x64.
  int v4; // edi
  unsigned int v5; // eax
  unsigned int v6; // edi
  T* v7; // eax
  T* v8; // ebx
  unsigned int v9; // eax
  T* v10; // ecx
  unsigned int v11; // ebx
  wchar_t** v12; // eax
  T* v13; // [esp+8h] [ebp-8h]
  void* v14; // [esp+Ch] [ebp-4h]

  v4 = BinSearch(wszKey, 0, this->field_8);
  if (v4 < 0)
  {
    v5 = this->field_C;
    v6 = ~v4;
    if (this->field_8 + 1 >= v5)
    {
      if (!v5)
        this->field_C = 2;
      v14 = _malloc(2 * sizeof(wchar_t*) * this->field_C);
      v7 = (T*)_malloc(2 * sizeof(T) * this->field_C);
      v8 = v7;
      v13 = v7;
      if (!v7 || !v14)
      {
        CheckAllocation(v7);
        CheckAllocation(v14);
        return;
      }
      memcpy(v14, this->field_0, sizeof(wchar_t*) * this->field_8);
      memcpy(v8, this->field_4, 8 * this->field_8);
      _free(this->field_0);
      _free(this->field_4);
      this->field_0 = v14;
      this->field_C *= 2;
      this->field_4 = v13;
    }
    v9 = this->field_8;
    while (--v9 >= v6 && v9 < this->field_8)
    {
      field_0[v9 + 1] = field_0[v9];
      v10 = &this->field_4[v9];
      v10[1] = v10;
    }
    ++this->field_8;
    v11 = wcslen(wszKey);
    field_0[v6] = malloc(sizeof(wchar_t*) * v11 + 4);
    v12 = (wchar_t**)((char*)this->field_0 + 4 * v6);
    if (*v12)
    {
      wcscpy_s(*v12, v11 + 1, wszKey);
      this->field_4[v6] = value;
    }
    else
    {
      CheckAllocation(*v12);
    }
  }
}

template<class T>
inline int SortedListW<T>::BinSearch(wchar_t* wszKey, int a2, int a3)
{
  // I stopped caring. here's ida output.
  int v4; // eax
  int v6; // esi

  v4 = a3 - a2;
  if (a3 == a2)
    return ~a2;
  while (1)
  {
    v6 = a2 + v4 / 2;
    if (!wcsicmp(field_0[v6], wszKey))
      break;
    if (wcsicmp(field_0[v6], wszKey) >= 0)
      a2 = v6 + 1;
    else
      a3 = v6;
    v4 = a3 - a2;
    if (a3 == a2)
      return ~a2;
  }
  return v6;
}

template<class T>
inline bool SortedListW<T>::TryGet(wchar_t* wszKey, T* result)
{
  int pos = BinSearch(wszKey, 0, field_8);
  if (pos < 0)
    return false;

  *result = field_4[pos];

  return true;
}

template<class T>
inline void SortedListW<T>::RemoveAll(bool bFreeMemory)
{
  for (unsigned int i = 0; i < field_8; i++)
    free(field_0[i]);

  field_8 = 0;

  if (bFreeMemory) {
    field_C = 0;
    free(field_0);
    free(field_4);
    field_0 = NULL;
    field_4 = NULL;
  }
}

template<class T>
inline SortedListW<T>::SortedListW(unsigned int InitialListSize)
{
  unsigned int size = InitialListSize;

  if (InitialListSize >= 4)
  {
    if (size > 0x3FFFFFFF)
      size = 0x3FFFFFFF;
  }
  else {
    size = 0;
  }

  // This is an assumption, if it's an array for wchar_t it probably is
  // dynamic for 32-bit and for 64-bit. Will have to dig through
  // the binary to find out.
  field_0 = malloc(sizeof(wchar_t*) * size);
  field_4 = malloc(sizeof(T) * size);
  field_8 = 0;
  field_C = size;
}

template<class T>
inline SortedListW<T>::~SortedListW()
{
  RemoveAll(true);
}

#endif // _SORTEDLISTW_H_
