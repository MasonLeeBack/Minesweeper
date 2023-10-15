/*

OberEngine Decompilation
Original Game: Purble Place

*/

#include <Windows.h>
#include "xmlnode.h"

#include "array.h"

// XmlString functions
XmlNode::XmlString::~XmlString()
{
  Cleanup();
}

void XmlNode::XmlString::Cleanup()
{
  if (m_bAllocated) {
    delete[] m_pStr;
    m_pStr = 0;
  }
}

// XmlNode functions

void XmlNode::SetNodeName(const wchar_t* pName)
{
  int size = wcslen(pName);

  if (m_NodeName.m_bAllocated)
    delete[] m_NodeName.m_pStr;

  m_NodeName.m_pStr = new wchar_t[size + 1];

  if (m_NodeName.m_pStr) {
    m_NodeName.m_iSize = size;
    m_NodeName.m_bAllocated = true;
    wcscpy_s(m_NodeName.m_pStr, size + 1, pName);
  }
}

wchar_t* XmlNode::GetNodeName()
{
  wchar_t* result;

  // Verify that the node name is allocated
  if (m_NodeName.m_iSize > 0x3FFFFFF)
    return NULL;

  // Allocate space for the node name
  result = new wchar_t[m_NodeName.m_iSize + 1];

  if (result) {
    wcsncpy_s(result, m_NodeName.m_iSize + 1, m_NodeName.m_pStr, m_NodeName.m_iSize);
    return result;
  }
  
  return NULL;
}

bool XmlNode::GetNodeValue(wchar_t* Dest, unsigned int Size)
{
  int i;

  if (Size != 0)
    *Dest = NULL;

  if (m_NodeValue.m_pStr && (i = m_NodeValue.m_iSize, Size >= i + 1))
    return wcsncpy_s(Dest, Size, m_NodeValue.m_pStr, i) == 0;

  return false;
}

wchar_t* XmlNode::GetNodeValue()
{
  wchar_t* result;

  if (!m_NodeValue.m_pStr)
    return NULL;

  if (m_NodeValue.m_iSize > 0x3FFFFFF)
    return NULL;

  result = new wchar_t[m_NodeValue.m_iSize + 1];
  if (result)
  {
    wcsncpy_s(result, m_NodeValue.m_iSize + 1, m_NodeValue.m_pStr, m_NodeValue.m_iSize);
    return result;
  }

  return NULL;
}

bool XmlNode::MatchName(wchar_t* pName, unsigned int iLength)
{
  if (m_NodeName.m_iSize == iLength)
    return wcsncmp(pName, m_NodeName.m_pStr, m_NodeName.m_iSize) == 0;
  else
    return false;
}

bool XmlNode::MatchName(wchar_t* pName)
{
  return MatchName(pName, wcslen(pName));
}

bool XmlNode::GetXmlString(wchar_t* Dest, unsigned int Size, const wchar_t* pName)
{
  XmlNode* element;

  // Allocate space
  memset(Dest, 0, sizeof(wchar_t) * Size);

  element = XPathElementSearchSingle(pName);

  if (element)
    return element->GetNodeValue(Dest, Size);
  else
    return false;
}

wchar_t* XmlNode::GetXmlStringAlloc(const wchar_t* pName)
{
  XmlNode* element;

  element = XPathElementSearchSingle(pName);

  if (element)
    return element->GetNodeValue();
  else
    return NULL;
}

XmlNode* XmlNode::getChild(unsigned int index)
{
  if (index < m_Children.count) {
    return m_Children.data[index];
  }

  return NULL;
}
