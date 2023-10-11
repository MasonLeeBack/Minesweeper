/*

OberEngine Decompilation

File name:
  nodelabel.h

*/

#ifndef _NODELABEL_H_
#define _NODELABEL_H_

#include "nodesprite.h"

#define NODELABEL_TYPE 0x9

class NodeLabel : public NodeSprite {
public:


  bool Load(XmlNode* xmlFile);
  void UpdateZero();

  static NodeBase* CreateNode(unsigned int* nodeType);
  static void Register();
};

#endif // _NODELABEL_H_
