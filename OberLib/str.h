/*

OberEngine Decompilation
Original Game: Purble Place

*/

#ifndef _STR_H_
#define _STR_H_

#define STR_MAX_LENGTH 0xFFFFF

class Str
{
public:
  size_t m_iLength; // 0
  size_t m_iCount; // 1
  wchar_t* m_pStr; // 2

  Str(Str* other);
  Str(const wchar_t* other);
  Str(wchar_t* Source, size_t Length);
  Str(unsigned int resourceID);

  ~Str();

  Str* operator=(wchar_t* rhs);
  Str* operator=(Str* rhs);
  Str* operator+=(Str* rhs);
  Str* operator+=(wchar_t* rhs);

  bool Equals(const Str* other);
  bool CIEquals(const Str* other);

  void Clear();

  size_t Format(wchar_t* Format, ...);
  size_t AppendF(wchar_t* Format, ...);

  Str* SubString(Str* result, size_t startIndex, size_t length);
  static Str* FromNumber(int n);
};

#endif // _STR_H_
