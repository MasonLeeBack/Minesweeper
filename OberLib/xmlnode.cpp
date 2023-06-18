/*

OberEngine Decompilation
Original Game: Purble Place

*/

#include "xmlnode.h"

// XmlString functions
XmlNode::XmlString::~XmlString()
{
  Cleanup();
}

void XmlNode::XmlString::Cleanup()
{
  if (m_bAllocated)
  {
    delete[] m_pStr;
    m_pStr = 0;
  }
}

// XmlNode functions
