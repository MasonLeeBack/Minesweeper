/*

OberEngine Decompilation

File name:
  nodelabel.cpp

*/

#include "stdafx.h"
#include "nodelabel.h"

NodeBase* NodeLabel::CreateNode(unsigned int* nodeType)
{
  *nodeType = NODELABEL_TYPE;

  NodeLabel* newNode = new NodeLabel();
  return newNode;
}

void NodeLabel::Register()
{
  NodeBase::RegisterNodeType(L"Label", CreateNode);
}
