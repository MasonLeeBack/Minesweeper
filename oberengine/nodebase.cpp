/*

OberEngine Decompilation

File name:
  nodebase.cpp

*/

#include "stdafx.h"
#include "nodebase.h"

#include <localize.h>
#include <logger.h>
#include "animationdescriptor.h"
#include "rendermanager.h"
#include "userinterface.h"

unsigned int NodeBase::GetTabIndex()
{
  return m_TabIndex;
}

bool NodeBase::ShowTip(Tip::TipSource* tipSource, bool bPinSprite)
{
  if (m_Tip)
    m_Tip->Close(true);

  m_Tip = new Tip(this);

  if (m_Tip->Initialize(tipSource, bPinSprite)) {
    m_Tip->Show();
    return true;
  }
  else {
    if (m_Tip)
      m_Tip->Close(true);
    m_Tip = NULL;
  }

  return false;
}

void NodeBase::DestroyTip()
{
  if (m_Tip)
    m_Tip->Close(true);
  m_Tip = NULL;
}

void NodeBase::HideTip(bool bHide)
{
  if (m_Tip)
    m_Tip->Close(bHide);
}

void NodeBase::SetAnimationReverse(unsigned int animationID, bool bReversed)
{
  AnimationState* state;
  if (m_AnimationStates.TryGet(animationID, &state))
  {
    state->SetReverse(bReversed);
  }
  else {
    LOG(200, L"Cannot set non existing animation: %d (type : %d)", animationID, GetHandleType(animationID));
  }
}

void NodeBase::SetAnimationTime(unsigned int animationID, float time)
{
  AnimationState* state;
  if (m_AnimationStates.TryGet(animationID, &state))
  {
    state->SetTime(time);
  }
  else {
    LOG(200, L"Cannot set non existing animation: %d (type : %d)", animationID, GetHandleType(animationID));
  }
}

void NodeBase::SetAnimationTimeToEnd(unsigned int animationID)
{
  SetAnimationTime(animationID, 99999.0f);
}

AnimationState* NodeBase::GetAnimationState(unsigned int animationID)
{
  AnimationState* state;

  if (m_AnimationStates.TryGet(animationID, &state)) {
    return state;
  }
  else {
    LOG(200, L"Cannot get non existing animation: %d (type : %d)", animationID, GetHandleType(animationID));
  }

  return NULL;
}

void NodeBase::ResumeAnimation(unsigned int animationID)
{
  AnimationState* state;
  if (m_AnimationStates.TryGet(animationID, &state)) {
    if (state->field_10)
      state->Reset();

    state->SetPlaying(true);
  }
  else {
    LOG(200, L"Cannot set non existing animation: %d (type : %d)", animationID, GetHandleType(animationID));
  }
}

void NodeBase::StopAnimation(unsigned int animationID)
{
  AnimationState* state;
  if (m_AnimationStates.TryGet(animationID, &state)) {
    state->SetPlaying(false);
  }
  else {
    LOG(200, L"Cannot set non existing animation: %d (type : %d)", animationID, GetHandleType(animationID));
  }
}

void NodeBase::CompleteAnimation(unsigned int animationID, bool a2)
{
  AnimationState* state;
  if (m_AnimationStates.TryGet(animationID, &state)) {
    state->Complete(a2);
  }
  else {
    LOG(200, L"Cannot set non existion animation: %d (type : %d)", animationID, GetHandleType(animationID));
  }
}

void NodeBase::SetMaterial(MaterialType materialType)
{
  m_Material = materialType;
}

void NodeBase::SetMaterial(Material* material)
{
  m_Material = g_pRenderManager->MaterialClassFromPtr(material);
}

void NodeBase::SetName(unsigned short* name)
{
  const unsigned short* srcPtr; // Pointer to the source string
  int srcLength; // Length of the source string
  unsigned short* newNamePtr; // Pointer to the newly allocated name

  // Delete the existing name
  operator delete[](this->m_Name);

  // Find the length of the source string
  srcPtr = name;
  while (*srcPtr++)
    ;

  // Calculate the required size for the new name
  srcLength = srcPtr - (name + 1) + 1;

  // Allocate memory for the new name
  newNamePtr = new unsigned short[srcLength];

  // Store the new name and its length in the object
  this->m_Name = newNamePtr;
  memcpy(newNamePtr, name, sizeof(unsigned short) * srcLength);
}

void NodeBase::SetOverriddenBoundingBox(int x0, int y0, unsigned int x1, unsigned int y1)
{
  // Update the coordinates of the overridden bounding box
  m_BBoxX0 = x0;
  m_BBoxY0 = y0;
  m_BBoxX1 = x1;
  m_BBoxY1 = y1;

  // Set the flag indicating that the bounding box is overridden
  m_bOverrideBoundingBox = true;
}

void NodeBase::GetOverriddenBoundingBox(int& x0, int& y0, unsigned int& x1, unsigned int& y1)
{
  x0 = m_BBoxX0;
  y0 = m_BBoxY0;
  x1 = m_BBoxX1;
  y1 = m_BBoxY1;
}

void NodeBase::SetPosition(unsigned int xPos, unsigned int yPos)
{
  // Check if the position has changed
  if (m_XPos != xPos || m_YPos != yPos) {
    // Update the position
    m_XPos = xPos;
    m_YPos = yPos;

    // Mark the scene and layout as dirty
    g_pRenderManager->MarkSceneDirty();
    g_pUserInterface->MarkLayoutDirty();
  }
}

void NodeBase::SetRotation(float rotation)
{
  // Check if the rotation has changed
  if (m_Rotation != rotation) {
    // Update the rotation
    m_Rotation = rotation;

    // Mark the scene and layout as dirty
    g_pRenderManager->MarkSceneDirty();
    g_pUserInterface->MarkLayoutDirty();
  }
}

void NodeBase::SetScale(unsigned int scale)
{
  // Check if the scale has changed
  if (m_Scale != scale) {
    // Update the scale
    m_Scale = scale;

    // Mark the scene and layout as dirty
    g_pRenderManager->MarkSceneDirty();
    g_pUserInterface->MarkLayoutDirty();
  }
}

void NodeBase::SetSize(unsigned int xSize, unsigned int ySize)
{
  // Check if the size has changed
  if (m_XSize != xSize || m_YSize != ySize) {
    // Update the size
    m_XSize = xSize;
    m_YSize = ySize;

    // Mark the scene and layout as dirty
    g_pRenderManager->MarkSceneDirty();
    g_pUserInterface->MarkLayoutDirty();
  }
}

void NodeBase::SetVisible(bool bVisible)
{
  // Check if the visibility flag has changed
  if (m_bVisible != bVisible) {
    // Update the visibility flag
    m_bVisible = bVisible;

    // Mark the scene and layout as dirty
    g_pRenderManager->MarkSceneDirty();
    g_pUserInterface->MarkLayoutDirty();
  }
}

bool NodeBase::TreeVisible()
{
  while (m_bVisible)
  {
    if (!m_Parent)
      return true;
  }

  return false;
}

void NodeBase::UpdateChildren(float timeDelta)
{
  for (unsigned int i = 0; i < m_Children.count; ++i) {
    m_Children.data[i]->Update(timeDelta);
  }
}

void NodeBase::UpdateZero()
{
  UpdateCurrentPositions();
  for (unsigned int i = 0; i < m_Children.count; ++i) {
    m_Children.data[i]->UpdateZero();
  }
}

void NodeBase::HandleEvent(Event* event)
{
/*
  unsigned int v3; // edi
  NodeBase *v4; // ecx

  v3 = 0;
  for ( *((_DWORD *)a2 + 1) = this; v3 < this->m_EventListeners.count; ++v3 )
  {
    v4 = this->m_EventListeners.data[v3];
    (*(void (__thiscall **)(NodeBase *, struct Event *))v4->vtabl)(v4, a2);
  }
*/
}

void NodeBase::HandleEventRecursive(Event* event)
{
  HandleEvent(event);
  for (unsigned int i = 0; i < m_Children.count; ++i)
  {
    m_Children.data[i]->HandleEventRecursive(event);
  }
}

NodeBase* NodeBase::GetChild(unsigned int index)
{
  if (index >= m_Children.count) {
    return NULL;
  }
  else {
    return m_Children.data[index];
  }
}

void NodeBase::DeleteChild(NodeBase* node)
{
  unsigned int j = 0;
  if (m_Children.count != 0) {
    for (NodeBase** i = m_Children.data; *i != node; ++i) {
      if (++j >= m_Children.count)
        return;
    }
    g_pUserInterface->AddToDeleteList(m_Children.data[j]);
    m_Children.data[j]->m_EventListeners.count = 0;
    m_Children.Remove(j);
  }
}

void NodeBase::DeleteSelf()
{
  m_Parent->DeleteChild(this);
}

void NodeBase::RenderChildren(unsigned int renderLayer)
{
  for (unsigned int i = 0; i < m_Children.count; ++i) {
    if (!m_Children.data[i]) {
      m_Children.data[i]->Render(renderLayer);
    }
  }
}

void NodeBase::Render(unsigned int renderLayer)
{
  if (m_bVisible) {
    RenderChildren(renderLayer);
  }
}

bool NodeBase::IsDescendantOf(NodeBase* node)
{
  for (NodeBase* i = m_Parent; ; i = i->m_Parent) {
    if (!i)
      return false;

    if (i == node)
      break;
  }
  return true;
}

void NodeBase::ImportNode(NodeBase* node)
{
  unsigned int index = 0;
  NodeBase* nodeParent;

  if (m_Children.count != 0) {
    for (auto i = m_Children.data; *i != node; ++i) {
      if (++index >= m_Parent->m_Children.count)
        return;
    }

    m_Parent->m_Children.Remove(index);
    nodeParent = node->m_Parent;
    m_Children.Add(node);
    node->m_Parent = this;

    g_pUserInterface->Access_OnNodeImport(this, node, nodeParent);
  }
}

bool NodeBase::Load(XmlNode* xmlNode)
{
  if (xmlNode) {

    if (wchar_t* aName = xmlNode->GetXmlStringAlloc(L"/AccessName")) {
      SetAccessName(aName);
      delete[] aName;
    }

    if (wchar_t* aDesc = xmlNode->GetXmlStringAlloc(L"/AccessDesc")) {
      SetAccessDescription(aDesc);
      delete[] aDesc;
    }

    if (wchar_t* aValue = xmlNode->GetXmlStringAlloc(L"/AccessValue")) {
      SetAccessValue(aValue);
      delete[] aValue;
    }

    if (wchar_t* aDefAction = xmlNode->GetXmlStringAlloc(L"/AccessDefAction")) {
      SetAccessDefaultAction(aDefAction);
      delete[] aDefAction;
    }

    if (wchar_t* aKeyShort = xmlNode->GetXmlStringAlloc(L"/AccessKeyShort")) {
      SetAccessKeyShortcut(aKeyShort);
      delete[] aKeyShort;
    }

    XmlNode* overrideBB = xmlNode->XPathElementSearchSingle(L"/OverrideBB");
    if (overrideBB) {
      m_bOverrideBoundingBox = true;
      m_BBoxX0 = overrideBB->GetXmlInt(L"/X0", 0);
      m_BBoxY0 = overrideBB->GetXmlInt(L"/Y0", 0);
      m_BBoxX1 = overrideBB->GetXmlInt(L"/X1", 0) - m_BBoxX0;
      m_BBoxY1 = overrideBB->GetXmlInt(L"/Y1", 0) - m_BBoxY0;
    }
  }

  return true;
}

NodeBase* NodeBase::CreateNode(unsigned int* nodeType)
{
  *nodeType = NODEBASE_TYPE;

  NodeBase* newNode = new NodeBase();
  return newNode;
}

void NodeBase::RegisterNodeType(const wchar_t* name, CreateFunction createFunction)
{
  RegisteredType type;

  wcsncpy_s(&type.m_Name[0], 20, name, 0xFFFFFFFF);
  type.m_CreateFunction = createFunction;

  m_TypeList.Add(type);
}

void NodeBase::Register()
{
  RegisterNodeType(L"Base", CreateNode);
  memset(&m_RenderLayerNodeCount, 0, 24);
  m_RenderLayerNodeCountInitialized = true;
}

int NodeBase::GetRenderLayerIsUsed(unsigned int renderLayer)
{
  return (&m_RenderLayerNodeCount)[renderLayer] != 0;
}

void NodeBase::GetLayoutLocation(int& x, int& y)
{
  g_pUserInterface->UpdateLayout();
  x = m_LayoutLocationX;
  y = m_LayoutLocationY;
}

void NodeBase::GetLayoutSize(unsigned int& x, unsigned int& y)
{
  g_pUserInterface->UpdateLayout();
  x = m_LayoutSizeX - m_LayoutLocationX;
  y = m_LayoutSizeY - m_LayoutLocationY;
}

void NodeBase::SetAccessible(bool bAccessible, unsigned int accessRole)
{
  if (m_bAccessible != bAccessible) {
    m_bAccessible = bAccessible;
    m_AccessRole = accessRole;
    if (bAccessible)
      g_pUserInterface->Access_OnNodeAccessible(this);
    else
      g_pUserInterface->Access_ClipNode(this);
  }
}

void NodeBase::SetXScale(unsigned int xScale)
{
  // Check if the X scale has changed
  if (m_XScale != xScale) {
    // Update the X scale
    m_XScale = xScale;

    // Mark the scene and layout as dirty
    g_pRenderManager->MarkSceneDirty();
    g_pUserInterface->MarkLayoutDirty();
  }
}

void NodeBase::SetYScale(unsigned int yScale)
{
  // Check if the Y scale has changed
  if (m_YScale != yScale) {
    // Update the Y scale
    m_YScale = yScale;

    // Mark the scene and layout as dirty
    g_pRenderManager->MarkSceneDirty();
    g_pUserInterface->MarkLayoutDirty();
  }
}

void NodeBase::SetAccessDefaultAction(wchar_t* action)
{
  LocalFree(m_AccessDefaultAction);
  m_AccessDefaultAction = LocalizeMessage(action);
}

wchar_t* NodeBase::GetAccessDefaultAction()
{
  return m_AccessDefaultAction;
}

void NodeBase::SetAccessDescription(wchar_t* description)
{
  LocalFree(m_AccessDescription);
  m_AccessDescription = LocalizeMessage(description);
}

wchar_t* NodeBase::GetAccessDescription()
{
  return m_AccessDescription;
}

void NodeBase::SetAccessKeyShortcut(wchar_t* shortcut)
{
  LocalFree(m_AccessKeyShortcut);
  m_AccessKeyShortcut = LocalizeMessage(shortcut);
}

wchar_t* NodeBase::GetAccessKeyShortcut()
{
  return m_AccessKeyShortcut;
}

void NodeBase::SetAccessName(wchar_t* name)
{
  LocalFree(m_AccessName);
  m_AccessName = LocalizeMessage(name);
}

wchar_t* NodeBase::GetAccessName()
{
  return m_AccessName;
}

void NodeBase::SetAccessValue(wchar_t* value)
{
  LocalFree(m_AccessValue);
  m_AccessValue = LocalizeMessage(value);
}

wchar_t* NodeBase::GetAccessValue()
{
  return m_AccessValue;
}

void NodeBase::SetAccessRole(unsigned int role)
{
  m_AccessRole = role;
}

unsigned int NodeBase::GetAccessRole()
{
  return m_AccessRole;
}

void NodeBase::AddListener(IEventListener* listener)
{
  m_EventListeners.Add(listener);
}

void NodeBase::RemoveListener(IEventListener* listener)
{
  unsigned int i = 0;
  IEventListener** j;

  if (m_EventListeners.count != 0) {
    j = m_EventListeners.data;

    while (*j != listener)
    {
      ++i;
      ++j;
      if (i >= m_EventListeners.count) {
        LOG(100, L"RemoveListener(), event did not exist");
        return;
      }
    }
    m_EventListeners.Remove(i);
  }
  else {
    LOG(100, L"RemoveListener(), event did not exist");
  }

}
