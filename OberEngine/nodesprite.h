/*

OberEngine Decompilation

File name:
  nodesprite.h

*/

#ifndef _NODESPRITE_H_
#define _NODESPRITE_H_

#include "nodebase.h"

#define NODESPRITE_TYPE 0x7

class NodeSprite : public NodeBase
{
  struct Source {
    Source();
    ~Source();
  };

  unsigned int m_CurrentFrame; // 0x108
  unsigned int m_Unk10C; // 0x10C
  unsigned int m_Unk110; // 0x110
  int m_Alpha; // 0x114
  unsigned int m_Unk118; // 0x118
  unsigned int m_Color; // 0x11C

  NodeSprite::Source m_Source; // 0x128
public:

  void SetAlpha(int alpha);
  void SetAnimation(unsigned int, bool, bool);
  void SetColor(unsigned int color);
  void SetCurrentFrame(unsigned int frame);

  void Update();
  void UpdateCurrentUVs();
  void UpdateZero();

  static void Copy(NodeSprite* source, NodeSprite* dest);
  NodeSprite* Copy();

  static NodeBase* CreateNode(unsigned int* nodeType);
  static void Register();
};

#endif // !1
