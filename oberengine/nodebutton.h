/*

OberEngine Decompilation

File name:
  nodebutton.h

*/

#ifndef _NODEBUTTON_H_
#define _NODEBUTTON_H_

#include "nodesprite.h"

#define NODEBUTTON_TYPE 0xC

class NodeButton : public NodeSprite {
private:

public:
  NodeButton();
  ~NodeButton();

  bool Load(XmlNode* xmlNode);
  void HandleEvent(Event* event);

  static NodeBase* CreateNode(unsigned int* nodeType);
  static void Register();
};

#endif // _NODEBUTTON_H_
