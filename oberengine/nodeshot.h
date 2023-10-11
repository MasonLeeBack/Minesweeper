/*

OberEngine Decompilation

File name:
  nodeshot.h

*/

#ifndef _NODESHOT_H_
#define _NODESHOT_H_

#include "nodesprite.h"

#define NODESHOT_TYPE 0x8

class NodeShot : public NodeSprite {
public:
  NodeShot();

  static NodeBase* CreateNode(unsigned int* nodeType);
  static void Register();
};

#endif // _NODESHOT_H_
