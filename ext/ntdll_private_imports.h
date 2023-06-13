/*

OberEngine Decompilation
Original Game: Purble Place

This is not a header file that's part of the original project.
It's a file that I created to store the private imports of ntdll.dll,
along with a function that's implemented in this program for some reason.

*/

#ifndef _NTDLL_PRIVATE_IMPORTS_H_
#define _NTDLL_PRIVATE_IMPORTS_H_

// These functions use internal NTDLL functions
// that are not exposed by the Windows API.
// We need to declare them ourselves.

// NTDLL.DLL

#if (_WIN32_WINNT <= _WIN32_WINNT_WIN8)
typedef struct _SQM_STREAM_ENTRY {
  DWORD dwType; // Type of data
  union {
    WCHAR* pwszVal; // String value
    DWORD dwVal; // DWORD value
    UINT64 qwVal; // UINT64 value
  }val;
}SQM_STREAM_ENTRY, * PSQM_STREAM_ENTRY;
#else
typedef struct _SQM_STREAM_ENTRY_EX {
  DWORD cbStruct; // Size of this structure
  DWORD dwType; // Type of data
  union {
    WCHAR* pwszVal; // String value
    DWORD dwVal; // DWORD value
    UINT64 qwVal; // UINT64 value
  }val;
}SQM_STREAM_ENTRY_EX, * PSQM_STREAM_ENTRY_EX;
#endif

extern "C" void WINAPI WinSqmIncrementDWORD(LPGUID hSession, DWORD dwDatapointId, const wchar_t* pwszDatapointValue);

#if (_WIN32_WINNT <= _WIN32_WINNT_WIN8)
extern "C" void WINAPI WinSqmAddToStream(LPGUID hSession, DWORD dwDatapointId, DWORD cSqmStreamEntries, PSQM_STREAM_ENTRY pbData);
#else
extern "C" void WINAPI WinSqmAddToStreamEx(LPGUID hSession, DWORD dwDatapointId, DWORD cSqmStreamEntries, PSQM_STREAM_ENTRY_EX pbData, DWORD dwFlags);
#endif

// I don't know why this is here, but it is. Find a better home for it.
// Windows 8(?) and above use WinSqmCreateStringStreamEntryEx instead.
// Consider using that instead if you want to support Windows 8 and above
// without compatibility mode.

#if (_WIN32_WINNT <= _WIN32_WINNT_WIN8)
static void WinSqmCreateStringStreamEntry(PSQM_STREAM_ENTRY pSqmStreamEntry, const wchar_t* pwszVal)
{
  if (!pwszVal || !*pwszVal)
    pwszVal = L"(null)";

  // dunno why this casts to the dwVal member of the union
  // but it does
  pSqmStreamEntry->val.dwVal = (DWORD)pwszVal;
  pSqmStreamEntry->dwType = 2;
}
#endif

#endif // _NTDLL_PRIVATE_IMPORTS_H_
