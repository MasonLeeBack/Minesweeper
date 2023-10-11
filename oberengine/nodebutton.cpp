/*

OberEngine Decompilation

File name:
  nodebutton.cpp

*/

#include "stdafx.h"
#include "nodebutton.h"

NodeBase* NodeButton::CreateNode(unsigned int* nodeType)
{
  *nodeType = NODEBUTTON_TYPE;

  NodeButton* newNode = new NodeButton();
  return newNode;
}

void NodeButton::Register()
{
  NodeBase::RegisterNodeType(L"Button", CreateNode);
}
