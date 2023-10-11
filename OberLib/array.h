/*

OberEngine Decompilation
Original Game: Purble Place

*/

#ifndef _ARRAY_H_
#define _ARRAY_H_

#include "utils.h"
#include <memory>

template <typename T>
class Array
{
public:
  unsigned int count;
  unsigned int field_4;
  unsigned int field_8;
  T* data;

  Array<T>();
  Array<T>(unsigned int count);
  ~Array<T>();

  int Add(T item);
  int Find(T item);
  void FreeExtra();
  void Reserve(unsigned int Size);
  void Insert(unsigned int index, T item);

  bool FindRemove(T item);
  unsigned int Remove(unsigned int index);
};

#endif // _ARRAY_H_

// I see no mention of this constructor
// ANYWHERE, but VS will complain if we
// don't have it.
template<typename T>
inline Array<T>::Array()
{
  count = 0;
  field_4 = 0;
  field_8 = 10;
  data = NULL;
}

template<typename T>
inline Array<T>::Array(unsigned int size)
{
  count = 0;
  field_4 = 0;
  field_8 = count;
  data = NULL;
}

template<typename T>
inline Array<T>::~Array()
{
  if (data)
  {
    delete[] data;
  }
}

template<typename T>
inline int Array<T>::Add(T item)
{
  T* v5;

  count++;
  if (count > field_4)
  {
    field_4 = field_8 + field_4;
    v5 = (T*)realloc(data, sizeof(T) * field_4);
    if (!v5)
    {
      CheckAllocation(0);
      return -1;
    }

    data = v5;
  }

  memcpy(&data[count - 1], &item, sizeof(data[count - 1]));
  return count - 1;
}

template<typename T>
inline int Array<T>::Find(T item)
{
  unsigned int v2; // edx
  int result; // eax
  T* i; // ecx

  v2 = count;
  result = 0;
  if (!count)
    return -1;
  for (i = data; *i != item; ++i)
  {
    if (++result >= v2)
      return -1;
  }
  return result;
}

template<typename T>
inline void Array<T>::FreeExtra()
{
  int v2; // eax
  T* v3; // edi

  v2 = count;
  field_4 = count;
  if (v2)
  {
    v3 = (T*)realloc(data, v2);
    if (!v3)
      CheckAllocation(0);
    data = v3;
  }
  else
  {
    free(data);
    data = 0;
  }
}

template<typename T>
inline void Array<T>::Reserve(unsigned int Size)
{
  T* v3;
  T* v4;

  if (Size > field_4) {
    v4 = data;
    field_4 = Size;
    v3 = realloc(v4, Size);
    if (!v3)
      CheckAllocation(0);
    data = v3;
  }
}

template<typename T>
inline void Array<T>::Insert(unsigned int index, T item)
{
  unsigned int v4; // eax
  int v5; // eax
  T* v6; // eax
  unsigned int i; // eax
  T* v8; // ecx

  ++this->count;
  v4 = this->field_4;
  if (this->count > v4)
  {
    v5 = this->field_8 + v4;
    this->field_4 = v5;
    v6 = (T*)_realloc(this->data, sizeof(T) * v5);
    if (!v6)
    {
      CheckAllocation(0);
      return;
    }
    this->data = v6;
  }
  for (i = this->count - 1; i > index; *v8 = *(v8 - 1))
    v8 = &this->data[i--];
  this->data[index] = item;
}

template<typename T>
inline bool Array<T>::FindRemove(T item)
{
  int index;

  index = Find(item);
  if (index == -1)
    return false;

  Remove(index);

  return true;
}

template<typename T>
inline unsigned int Array<T>::Remove(unsigned int index)
{
  unsigned int v2; // edx
  unsigned int result; // eax

  v2 = index;
  result = count - 1;
  if (index < result)
  {
    do
    {
      data[v2] = data[v2 + 1];
      ++v2;
      result = count - 1;
    } while (v2 < result);
  }
  --count;
  return result;
}
