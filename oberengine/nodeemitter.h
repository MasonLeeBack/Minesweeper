/*

OberEngine Decompilation

File name:
  nodeemitter.h

*/

#ifndef _NODEEMITTER_H_
#define _NODEEMITTER_H_

#include "nodesprite.h"

#define NODEEMITTER_TYPE 0xB

class NodeEmitter : public NodeSprite {
public:
  static NodeBase* CreateNode(unsigned int* nodeType);
  static void Register();
};

#endif // _NODEEMITTER_H_
