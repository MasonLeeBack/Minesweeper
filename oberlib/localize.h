/*

OberEngine Decompilation
Original Game: Purble Place

*/

#ifndef _LOCALIZE_H_
#define _LOCALIZE_H_

#include <stdarg.h>

wchar_t* LocalizeMessageV(const wchar_t* Source, va_list* Args);
wchar_t* LocalizeMessage(const wchar_t* Source, ...);

#endif // _LOCALIZE_H_
