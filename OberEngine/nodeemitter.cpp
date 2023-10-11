/*

OberEngine Decompilation

File name:
  nodeemitter.cpp

*/

#include "stdafx.h"
#include "nodeemitter.h"

NodeBase* NodeEmitter::CreateNode(unsigned int* nodeType)
{
  *nodeType = NODEEMITTER_TYPE;

  NodeEmitter* newNode = new NodeEmitter();
  return newNode;
}

void NodeEmitter::Register()
{
  NodeBase::RegisterNodeType(L"Emitter", CreateNode);
}
