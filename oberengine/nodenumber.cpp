/*

OberEngine Decompilation
Original Game: Purble Place

*/

#include "stdafx.h"
#include "nodenumber.h"

NodeNumber::NodeNumber()
{
  field_108 = -1;
  field_10C = -1;
  field_110 = 0;
  field_114 = -1;
  field_120 = 1;
  field_124 = 1;
  field_118 = 255;
}

NodeNumber::~NodeNumber()
{
  Cleanup();
}

void NodeNumber::Cleanup()
{
  unsigned int i = 0;
  if (m_Numbers.count != 0) {
    do {
      NodeBase* node = m_Numbers.data[i];
      if (node) {
        node->DeleteSelf();
        m_Numbers.data[i];
      }
      ++i;
    } while ( i < m_Numbers.count );
  }
  m_Numbers.count = 0;
  m_Numbers.FreeExtra();
}

bool NodeNumber::Load(XmlNode* xmlNode)
{
  return true;
}

NodeBase* NodeNumber::CreateNode(unsigned int* nodeType)
{
  // Assign the node type so we can identify
  // what node type this is
  *nodeType = NODENUMBER_TYPE;

  NodeNumber* newNode = new NodeNumber();
  return newNode;
}

void NodeNumber::Register()
{
  NodeBase::RegisterNodeType(L"Number", CreateNode);
}
