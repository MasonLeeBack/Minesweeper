/*

OberEngine Decompilation

File name:
  nodeshot.cpp
  
*/

#include "stdafx.h"
#include "nodeshot.h"

NodeShot::NodeShot()
{
  m_Unknown.Add(5);
}

NodeBase* NodeShot::CreateNode(unsigned int* nodeType)
{
  *nodeType = NODESHOT_TYPE;

  NodeShot* newNode = new NodeShot();
  return newNode;
}

void NodeShot::Register()
{
  NodeBase::RegisterNodeType(L"Shot", CreateNode);
}
