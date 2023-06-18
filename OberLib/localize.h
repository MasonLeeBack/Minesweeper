/*

OberEngine Decompilation
Original Game: Purble Place

*/

#ifndef _ENGINE_H_
#define _ENGINE_H_

#include <stdarg.h>

wchar_t* LocalizeMessageV(wchar_t* Source, va_list* Args);
wchar_t* LocalizeMessage(wchar_t* Source, ...);

#endif // _ENGINE_H_
