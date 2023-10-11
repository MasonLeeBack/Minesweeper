/*

OberEngine Decompilation
Original Game: Purble Place

// Sorted by Integer list

*/

#ifndef _SORTEDLIST_H_
#define _SORTEDLIST_H_

#include <memory>

template <class T>
class SortedListI
{
public:
  wchar_t** field_0;
  T* data;
  unsigned int field_8;
  unsigned int field_C;
  int field_10;

  ~SortedListI();

  void AtLocation(T* result, int index);
  void RemoveAll(bool bFreeMemory);
  bool TryGet(int index, T* result);
};

template<class T>
inline SortedListI<T>::~SortedListI()
{
  RemoveAll(true);
}

template<class T>
inline void SortedListI<T>::AtLocation(T* result, int index)
{
  memcpy(result, data[index], sizeof(T));
}



#endif // _SORTEDLIST_H_
