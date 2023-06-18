
#include <cassert>
#include "utils.h"

#include "sortedlist.h"

void CheckAllocation(void* pPointer)
{
  if (!pPointer) {
#ifdef _DEBUG
    assert(pPointer);
#else
    DialogHelper::ShowMessageBox(0, 0, 1, 0xFFFE, L"Fatal Error", L"Out of memory.", 1);
    ExitProcess(0);
#endif
  }
}
