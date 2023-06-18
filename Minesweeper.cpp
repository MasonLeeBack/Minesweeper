/*

Minesweeper Decompilation

*/

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int iCmdShow)
{
  HeapSetInformation(0, HeapEnableTerminationOnCorruption, 0, 0);
}