/*

OberEngine Decompilation
Original Game: Purble Place

*/

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <wchar.h>

#include "localize.h"

wchar_t g_wSeparator = '|';

wchar_t* __stdcall LocalizeMessageV(wchar_t* Source, va_list* Arguments)
{
  size_t length;
  HRSRC hResource;

  // TODO: Descramble this
  HGLOBAL v8;
  wchar_t* v9;
  int v10;
  char v18;

  // Get the length of the source string
  length = wcslen(Source);

  // Limit the length of the Source string
  if (length > 0x40000000)
    length = 0x40000000;

  if (length != 0) {
    if (*Source == g_wSeparator)
    {
      // TODO: Descramble this
      unsigned int resourceNumber = wcstoul(Source + 1, 0, 10);
      v18 = resourceNumber;
      if (resourceNumber)
      {
        // MAKEINTRESOURCE may be incorrect in this scenario. Will need to check.
        // For documentation purposes, this is the decompiled output:
        // (const wchar_t*)(unsigned __int16)((resourceNumber >> 4) + 1);
        hResource = FindResourceEx(GetModuleHandle(0), RT_STRING, MAKEINTRESOURCE(resourceNumber), 0);
        if (hResource || ((hResource = FindResourceEx(GetModuleHandle(0), RT_STRING, MAKEINTRESOURCE(resourceNumber), (WORD)GetThreadLocale())) != 0))
        {
          v8 = LoadResource(GetModuleHandle(0), hResource);

          if (v8)
          {
            v9 = (wchar_t*)LockResource(v8);
            if (v9)
            {
              v10 = v18 & 0xF;

              if ((v18 & 0xF) != 0)
              {
                do
                {
                  --v10;
                  v9 += *v9 + 1;
                } while (v10);
              }

              length = *v9;
              Source = v9 + 1;
            }

          }

        }

      }

    }

  }

  // Allocate a buffer for the localized string
  wchar_t* tempBuffer = new wchar_t[length + 1];

  if (tempBuffer) {
    // Copy the source string to the buffer
    memcpy(tempBuffer, Source, 2 * length);
    tempBuffer[length] = '\0';

    wchar_t* Buffer = new wchar_t[2];
    Buffer[1] = '\0';

    // Check if the buffer is empty
    if (wcslen(tempBuffer))
    {
      // Format the message using the provided arguments
      FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_STRING, tempBuffer, 0, 0, Buffer, 1, Arguments);

      // Deallocate the temporary buffer
      delete[] tempBuffer;
    }
    else {
      // Deallocate the temporary buffer
      delete[] tempBuffer;

      Buffer = (wchar_t*)LocalAlloc(0, sizeof(WCHAR) * (wcslen(Source) + 1));

      // Check to make sure the buffer was allocated
      if (!Buffer)
        return NULL;

      // Copy the source string to the buffer
      wcscpy_s(Buffer, wcslen(Source) + 1, Source);
    }

    tempBuffer = Buffer;
  }

  return tempBuffer;
}


wchar_t* LocalizeMessage(wchar_t* Source, ...)
{
  va_list Arguments;
  va_list va;

  va_start(va, Source);
  va_copy(Arguments, va);
  return LocalizeMessageV(Source, &Arguments);
}
