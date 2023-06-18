/*

OberEngine Decompilation
Original Game: Purble Place

I don't know much about this class, but 
I documented as much of it as I could. The array
could be a completely different type, but I'm not
sure.

*/

#ifndef _NODENUMBER_H_
#define _NODENUMBER_H_

#include "nodebase.h"

#define NODENUMBER_TYPE 0xA

class NodeNumber : public NodeBase
{
private: // todo: are these supposed to be private?
  uint32_t field_108; // 0x108
  uint32_t field_10C; // 0x10C
  uint32_t field_110; // 0x110
  uint32_t field_114; // 0x114
  uint32_t field_118; // 0x118
  uint32_t field_11C; // 0x11C
  uint32_t field_120; // 0x120
  uint32_t field_124; // 0x124
  Array<NodeBase*> m_Numbers; // 0x128

public:
  NodeNumber();
  ~NodeNumber();

  void Cleanup();

  bool Load(XmlNode* xmlNode);

  static NodeBase* CreateNode(unsigned int* nodeType);
  static void Register();
};

#endif // _NODENUMBER_H_
