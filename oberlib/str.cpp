/*

OberEngine Decompilation
Original game: Purble Place

*/

#include <stdio.h>
#include <cstdarg>
#include <string.h>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "str.h"

Str::Str(Str* other)
{
  // Store the current length in a temporary variable
  size_t tempLength = m_iLength;

  // Update the current length with the length of the 'other' Str object
  m_iLength = other->m_iLength;

  // Increment the temporary length variable and assign it to 'm_iCount'
  m_iCount = tempLength++;

  // Allocate memory for the new string based on the updated count
  m_pStr = new wchar_t[tempLength];

  if (m_pStr) {
    // Copy the string from 'other' to the newly allocated memory
    wcscpy_s(m_pStr, m_iCount, other->m_pStr);
  }
  else {
    // Set count and length to 0 if memory allocation failed
    m_iCount = 0;
    m_iLength = 0;
  }
}

Str::Str(const wchar_t* Source)
{
  if (Source) {
    // Find the length of the source string
    size_t srcLength = wcslen(Source);

    m_iLength = srcLength++;
    m_iCount = srcLength;

    // Allocate memory for the new string
    m_pStr = new wchar_t[srcLength];

    if (m_pStr) {
      // Copy the string from 'Source' to the newly allocated memory
      wcscpy_s(m_pStr, m_iCount, Source);
      return;
    }

  }
  else {
    m_pStr = 0;
  }

  // Set count and length to 0 if memory allocation failed
  m_iLength = 0;
  m_iCount = 0;
}

Str::Str(wchar_t* Source, size_t Length)
{
  if (Source) {
    m_iLength = Length;
    m_iCount = Length + 1;

    // Allocate memory for the new string
    m_pStr = new wchar_t[m_iCount];

    if (m_pStr) {
      // Copy the string from 'Source' to the newly allocated memory
      wcsncpy_s(m_pStr, m_iCount, Source, Length);
      return;
    }
  }
  else {
    m_pStr = 0;
  }

  // Set count and length to 0 if memory allocation failed
  m_iLength = 0;
  m_iCount = 0;
}

Str::Str(unsigned int resourceID)
{
  int cchBufferMax; // Maximum buffer size for loading the string resource

  // Initialize member variables
  m_iLength = 0;
  m_iCount = 0;
  m_pStr = 0;

  cchBufferMax = 1024; // Set the initial buffer size to 1024 characters

  while (1)
  {
    wchar_t* buffer = new wchar_t[cchBufferMax]; // Allocate a buffer to load the string resource

    if (!buffer)
      break; // Memory allocation failed, exit the loop

    int cchBuffer = LoadString(GetModuleHandle(0), resourceID, buffer, cchBufferMax); // Load the string resource into the buffer

    delete[] buffer; // Free the buffer memory

    if (cchBuffer < cchBufferMax - 1) {
      // The string was successfully loaded

      m_iLength = cchBuffer; // Set the length of the string

      if (!cchBuffer)
        return; // Empty string, return

      m_iCount = m_iLength + 1; // Set the count to accommodate the string and null-terminator
      m_pStr = new wchar_t[m_iCount]; // Allocate memory for the string

      if (m_pStr) {
        LoadString(GetModuleHandle(NULL), resourceID, m_pStr, (int)m_iCount); // Load the string resource into the member variable
        return; // Return after successful allocation and loading
      }
      break;
    }

    cchBufferMax *= 2; // Double the buffer size

    if (cchBufferMax > 0x100000)
    {
      // The buffer size exceeds the limit

      m_iLength = STR_MAX_LENGTH; // Set the length to a maximum value
      m_iCount = m_iLength + 1; // Set the count to accommodate the string and null-terminator
      m_pStr = new wchar_t[m_iCount]; // Allocate memory for the string

      if (m_pStr) {
        LoadString(GetModuleHandle(NULL), resourceID, m_pStr, (int)m_iCount); // Load the string resource into the member variable
        return; // Return after successful allocation and loading
      }
      break;
    }
  }

  // Memory allocation failed or string loading failed, set count and length to 0
  m_iCount = 0;
  m_iLength = 0;
}


Str::~Str()
{
  delete[] m_pStr;
}

Str* Str::operator=(wchar_t* Source)
{
  size_t length; // Variable to hold the length of the source string
 
  // Find the length of the source string
  length = wcslen(Source);

  // Check if the source string is longer than the current string
  if (m_iCount <= length)
  {
    // Free the memory allocated for the current string, if any
    // and allocate memory for the new string.
    delete[] m_pStr;
    m_iCount = length + 1;
    m_pStr = new wchar_t[length + 1];
  }

  // Copy the source string to the member variable
  if (m_pStr)
  {
    m_iLength = length;
    wcscpy_s(m_pStr, m_iCount, Source);
  }

  return this;
}

Str* Str::operator=(Str* rhs)
{
  size_t length; // Variable to hold the length of the source string

  // Find the length of the source string
  length = wcslen(rhs->m_pStr);

  // Check if the source string is longer than the current string
  if (m_iCount <= length) {
    // Free the memory allocated for the current string, if any
    // and allocate memory for the new string.
    delete[] m_pStr;
    m_iCount = length + 1;
    m_pStr = new wchar_t[length + 1];
  }
  
  if (m_pStr) {
    m_iLength = length;
    wcscpy_s(m_pStr, m_iCount, rhs->m_pStr); // Copy the string from rhs to the member variable
  }
  return this;
}

Str* Str::operator+=(Str* rhs)
{
  m_iLength += rhs->m_iLength; // Increase the length of the string

  wchar_t* buffer; // Temporary buffer to hold the concatenated string

  if (m_iCount > m_iLength) {
    // If the total count is greater than the updated length,
    // concatenate the string from rhs to the member variable
    wcscat_s(m_pStr, m_iCount, rhs->m_pStr);
  }
  else {
    buffer = new wchar_t[m_iLength + 1]; // Allocate memory for the concatenated string

    if (buffer) {
      if (m_pStr) {
        m_iCount = m_iLength + 1;
        wcscpy_s(buffer, m_iCount, m_pStr); // Copy the current string to the buffer
      }
      else {
        *buffer = '\0'; // Set the buffer as an empty string if the current string is null
      }

      wcscat_s(buffer, m_iCount, rhs->m_pStr); // Concatenate the string from rhs to the buffer

      delete[] m_pStr; // Free the memory occupied by the current string
      m_pStr = buffer; // Update the pointer to the concatenated string
    }
  }

  return this; // Return a pointer to the current object
}

Str* Str::operator+=(wchar_t* rhs)
{
  Str* temp = new Str(rhs); // Create a temporary string object from the rhs string
  *this += temp; // Concatenate the temporary string to the current string
  delete temp; // Free the memory occupied by the temporary string

  return this;
}

bool Str::Equals(const Str* other)
{
  // Check if both strings are valid
  if (m_pStr && other->m_pStr != 0) {
    return wcscmp(m_pStr, other->m_pStr) == 0;
  }
  else {
    return false;
  }
}

bool Str::CIEquals(const Str* other)
{
  // Check if both strings are valid
  if (m_pStr && other->m_pStr != 0) {
    return _wcsicmp(m_pStr, other->m_pStr) == 0;
  }
  else {
    return false;
  }
}

void Str::Clear()
{
  // Free the memory allocated for the string
  delete[] m_pStr;
  m_pStr = nullptr;
  m_iLength = 0;
  m_iCount = 0;
}

size_t Str::Format(wchar_t* Format, ...)
{
  size_t count;        // Variable to hold the count of characters needed for the formatted string
  va_list ArgList;  // Variable to hold the argument list

  // Start processing the variable argument list
  va_start(ArgList, Format);

  // Get the count of characters required for the formatted string
  count = _vscwprintf(Format, ArgList);

  // Update the length of the string
  m_iLength = count;

  // Check if the current allocated size is insufficient
  if (m_iCount <= count) {
    delete[] m_pStr;

    // Update the size to accommodate the formatted string and null-terminator
    m_iCount = m_iLength + 1;

    // Allocate memory for the string
    m_pStr = new wchar_t[m_iCount];
  }

  if (m_pStr && m_iCount != 0) {
    // Format the string with the provided arguments
    _vsnwprintf_s(m_pStr, m_iLength + 1, m_iLength, Format, ArgList);
  }
  else {
    // Set length and count to 0 if memory allocation failed
    m_iCount = 0;
    m_iLength = 0;
  }

  // Clean up the variable argument list
  va_end(ArgList);

  // Return the length of the formatted string
  return m_iLength;
}

size_t Str::AppendF(wchar_t* Format, ...)
{
  size_t count;        // Variable to hold the count of characters needed for the formatted string
  size_t originalLength; // Variable to hold the original length of the string
  va_list ArgList;  // Variable to hold the argument list
  wchar_t* buffer; // Temporary buffer to hold the concatenated string

  // Start processing the variable argument list
  va_start(ArgList, Format);

  // Get the count of characters required for the formatted string
  count = _vscwprintf(Format, ArgList);
  originalLength = m_iLength;

  m_iLength += count; // Update the length of the string

  if (m_iCount > m_iLength) {
    // If the total count is greater than the updated length,
    // concatenate the string from rhs to the member variable
    _vsnwprintf_s(&this->m_pStr[originalLength], count + 1, count, Format, ArgList);
  }
  else {
    buffer = new wchar_t[m_iLength + 1]; // Allocate memory for the concatenated string
    
    if (buffer) {
      m_iCount = m_iLength + 1;
      if (m_pStr) {
        wcscpy_s(buffer, m_iCount, m_pStr); // Copy the current string to the buffer
      }
      else {
        *buffer = '\0'; // Set the buffer as an empty string if the current string is null
      }

      // Format the string with the provided arguments
      _vsnwprintf_s(&buffer[originalLength], count + 1, count, Format, ArgList);

      delete[] m_pStr;
      m_pStr = buffer;
    }
  }

  // Clean up the variable argument list
  va_end(ArgList);

  // Return the length of the formatted string
  return m_iLength;
}

Str* Str::SubString(Str* result, size_t startIndex, size_t length)
{
  size_t availableLength; // Local variable to hold the available length of the substring

  // Check if the startIndex or length is less than 0, or if the substring exceeds the length of the string
  if (startIndex < 0 || length < 0 || m_iLength < startIndex + length)
    availableLength = m_iLength - startIndex; // Set availableLength to the remaining length of the string
  else
    availableLength = length; // Set availableLength to the provided length

  // Create a new Str object using the substring of the underlying wchar_t array

  result = new Str(&m_pStr[startIndex], availableLength);

  // Return the pointer to the result object
  return result;
}

Str* Str::FromNumber(int n)
{
  Str* result;
  wchar_t Buffer[128];

  // Convert the integer to a wide character string
  swprintf_s(Buffer, 128, L"%i", n);

  // Call the constructor
  result = new Str(Buffer);

  // Return a pointer to the current object
  return result;
}
