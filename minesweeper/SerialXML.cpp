/*

Minesweeper Decompilation

File name:
  SerialXML.cpp

*/

#include "SerialXML.h"

SerialXML::SerialXML()
{
  m_IndentLength = 0;
  field_10 = NULL;
  field_4.SetAllocLength(2500);
}

SerialXML::~SerialXML()
{
  Cleanup();
}

void SerialXML::Cleanup()
{
  if (field_10) {
    delete field_10;
    field_10 = NULL;
  }
}

void SerialXML::Reset()
{
  Cleanup();
  m_IndentLength = 0;
  field_4 = L"";
  field_10 = NULL;
}

void SerialXML::PrintTabs()
{
  for (int i = 0; i < m_IndentLength; ++i) {
    field_4.AppendF(L"\t");
  }
}

void SerialXML::WriteStartTag(const wchar_t* tag, bool bNewLine)
{
  if (tag) {
    PrintTabs();
    field_4.AppendF(L"<%s>", tag);
  }
  if (bNewLine) {
    field_4.AppendF(L"\n");
    ++m_IndentLength;
  }
}

void SerialXML::WriteEndTag(const wchar_t* tag, bool bNewLine)
{
  if (bNewLine) {
    --m_IndentLength;
    PrintTabs();
  }
  if (tag) {
    field_4.AppendF(L"</%s>\n", tag);
  }
}

void SerialXML::ToXML(int i, const wchar_t* tag)
{
  WriteStartTag(tag, false);
  field_4.AppendF(L"%d", i);
  WriteEndTag(tag, false);
}

bool SerialXML::FromXML(int& i, const XmlNode* node)
{
  const wchar_t* data;

  if (!node)
    return true;

  data = node->GetNodeValue();
  if (data) {
    i = wcstol(data, 0, 10);
    delete[] data;
    return true;
  }


  return false;
}

void SerialXML::ToXML(float f, const wchar_t* tag)
{
  WriteStartTag(tag, false);
  field_4.AppendF(L"%f", f);
  WriteEndTag(tag, false);
}

bool SerialXML::FromXML(float& f, const XmlNode* node)
{
  const wchar_t* data;

  if (!node)
    return true;

  data = node->GetNodeValue();
  if (data) {
    f = wcstod(data, 0);
    delete[] data;
    return true;
  }

  return false;
}

void SerialXML::ToXML(unsigned int u, const wchar_t* tag)
{
  WriteStartTag(tag, false);
  field_4.AppendF(L"%d", u);
  WriteEndTag(tag, false);
}

bool SerialXML::FromXML(unsigned int& u, const XmlNode* node)
{
  const wchar_t* data;

  if (!node)
    return true;

  data = node->GetNodeValue();
  if (data) {
    u = wcstoul(data, 0, 10);
    delete[] data;
    return true;
  }

  return false;
}

void SerialXML::ToXML(bool b, const wchar_t* tag)
{
  const wchar_t* data;

  WriteStartTag(tag, false);
  if (b) {
    data = L"true";
  }
  else {
    data = L"false";
  }

  field_4.AppendF(L"%s", data);
  WriteEndTag(tag, false);
}

bool SerialXML::FromXML(bool& b, const XmlNode* node)
{
  const wchar_t* data;

  if (!node)
    return true;

  data = node->GetNodeValue();
  if (data) {
    b = _wcsicmp(data, L"true") == 0;
    delete[] data;
    return true;
  }

  return false;
}

void SerialXML::ToXML(__int64 i, const wchar_t* tag)
{
  wchar_t* buffer = new wchar_t[0x100];

  swprintf_s(buffer, 0x100, L"%I64u", i);
  WriteStartTag(tag, false);
  field_4.AppendF(L"%s", buffer);
  WriteEndTag(tag, false);

  delete[] buffer;
}

bool SerialXML::FromXML(__int64& i, const XmlNode* node)
{
  const wchar_t* data;

  if (!node)
    return true;

  data = node->GetNodeValue();
  if (data) {
    i = _wcstoui64(data, 0, 10);
    delete[] data;
    return true;
  }

  return false;
}

void SerialXML::ToXML(EDifficulty d, const wchar_t* tag)
{
  WriteStartTag(tag, false);
  field_4.AppendF(L"%ul", d);
  WriteEndTag(tag, false);
}

bool SerialXML::FromXML(EDifficulty& d, const XmlNode* node)
{
  const wchar_t* data;

  if (!node)
    return true;

  data = node->GetNodeValue();
  if (data) {
    d = (EDifficulty)wcstoul(data, 0, 10);
    delete[] data;
    return true;
  }

  return false;
}
