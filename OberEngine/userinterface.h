/*

OberEngine Decompilation

File name:
  userinterface.h

*/

#ifndef _USERINTERFACE_H_
#define _USERINTERFACE_H_

#include "nodebase.h"
#include "event.h"

class UserInterface {
public:
  enum FocusDirection {
    FOCUS_0 = 0,
    FOCUS_1 = 1,
    FOCUS_2 = 2,
    FOCUS_3 = 3,
  };

  void UpdateLayout();

  void MarkLayoutDirty();

  bool IsLastInputKeyboard();
  NodeBase* GetNodeFromTabIndex(unsigned int iTabIndex);
  // this isn't a void*
  void* GetNextFocus(FocusDirection direction);
  NodeBase* GetCurrentFocus();
  void ClearFocus();
  void AddToDeleteList(NodeBase* node);
  void AddGlobalMouseHandler(IEventListener* pListener);
  void AddGlobalKeyHandler(IEventListener* pListener);
  void Access_OnNodeImport(NodeBase* node1, NodeBase* node2, NodeBase* node3);
  void Access_OnNodeAccessible(NodeBase* node);
  void Access_OnGetObjectPositive(int iNum);
  void Access_OnGetObject();
  void Accces_GetANodeParentOf(NodeBase* node);
  void Access_GetANodeFor(NodeBase* node);
  void Access_ClipNode(NodeBase* node);

protected:
  static const bool m_bDefaultLastInputKeyboard = true;
};

extern UserInterface* g_pUserInterface;

#endif // _USERINTERFACE_H_
