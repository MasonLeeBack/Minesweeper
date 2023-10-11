/*

OberEngine Decompilation

File name:
  nodesprite.cpp

*/

#include "stdafx.h"
#include "nodesprite.h"
#include "rendermanager.h"

void NodeSprite::SetAlpha(int alpha)
{
  if (alpha != m_Alpha) {
    m_Alpha = alpha;
    g_pRenderManager->MarkSceneDirty();
  }
}

void NodeSprite::SetColor(unsigned int color)
{
  if (color != m_Color) {
    m_Color = color;
    g_pRenderManager->MarkSceneDirty();
  }
}

void NodeSprite::SetCurrentFrame(unsigned int frame)
{
  if (frame != m_CurrentFrame) {
    m_CurrentFrame = frame;
    g_pRenderManager->MarkSceneDirty();
  }
}

NodeSprite* NodeSprite::Copy()
{
  NodeSprite* sprite;

  sprite = NodeBase::CreateFromType(L"Sprite", this->m_Parent, true);
  Copy(sprite, this);

  return sprite;
}

NodeBase* NodeSprite::CreateNode(unsigned int* nodeType)
{
  *nodeType = NODESPRITE_TYPE;

  NodeSprite* newNode = new NodeSprite();
  return newNode;
}

void NodeSprite::Register()
{
  RegisterNodeType(L"Sprite", CreateNode);
}
