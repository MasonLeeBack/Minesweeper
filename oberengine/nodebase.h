/*

OberEngine Decompilation

File name:
  nodebase.h

*/

#ifndef _NODEBASE_H_
#define _NODEBASE_H_

#include <array.h>
#include <xmlnode.h>
#include "event.h"
#include "tip.h"
#include "animationdescriptor.h"

#define NODEBASE_TYPE 0x6

enum NodeType {
  NODE_0,
  NODE_1,
  NODE_2,
};

class NodeBase
{
public:
  typedef NodeBase* (*CreateFunction)(unsigned int*);
  struct RegisteredType {
    wchar_t m_Name[0x28];
    // Callback function for creating a new node
    CreateFunction m_CreateFunction;
  };
  static Array<NodeBase::RegisteredType> m_TypeList;
  static unsigned int* m_RenderLayerNodeCount; // static variable, 01087504
  static bool m_RenderLayerNodeCountInitialized; // static variable, 0108751C

  unsigned int m_XPos;   // 0x4
  unsigned int m_YPos;   // 0x8
  unsigned int m_XSize;  // 0xC
  unsigned int m_YSize;  // 0x10
  unsigned int m_Scale;  // 0x14
  unsigned int m_XScale; // 0x18
  unsigned int m_YScale; // 0x1C
  float m_Rotation;      // 0x20
  // 0x24 is padding
  bool m_bVisible;       // 0x25

  // Bounding box, defines all 4 corners of the node
  bool m_bOverrideBoundingBox; // 0x26
  // 0x27 is padding
  int m_BBoxX0; // 0x28
  int m_BBoxY0; // 0x2C
  unsigned int m_BBoxX1; // 0x30
  unsigned int m_BBoxY1; // 0x34

  Array<NodeBase*> m_Children; // 0x48 .. 0x54
  Array<int> m_Unknown; // 0x58 .. 0x64

  unsigned short* m_Name; // 0x68

  NodeBase* m_Parent; // 0x6C

  bool m_bAccessible; // 0x70
  // 0x71, 0x72, 0x73 are padding
  wchar_t* m_AccessDefaultAction; // 0x74
  wchar_t* m_AccessDescription; // 0x78
  wchar_t* m_AccessKeyShortcut; // 0x7C
  wchar_t* m_AccessName; // 0x80;
  wchar_t* m_AccessValue; // 0x84;
  unsigned int m_AccessRole; // 0x88

  Array<IEventListener*> m_EventListeners; // 0x90 .. 0x9C

  unsigned int m_TabIndex; // 0xA0

  class Tip* m_Tip; // 0xA4

  SortedListI<AnimationState*> m_AnimationStates; // 0xA8 .. 0xB4

  int m_LayoutLocationX; // 0xB8
  int m_LayoutLocationY; // 0xBC
  unsigned int m_LayoutSizeX; // 0xC0
  unsigned int m_LayoutSizeY; // 0xC4

  // MaterialType material; // 0xFC

  unsigned int GetTabIndex();

  bool ShowTip(Tip::TipSource* tipSource, bool bPinSprite);
  void DestroyTip();
  void HideTip(bool bHide);

  void SetAnimationReverse(unsigned int animationID, bool bReversed);
  void SetAnimationTime(unsigned int animationID, float time);
  void SetAnimationTimeToEnd(unsigned int animationID);
  AnimationState* GetAnimationState(unsigned int animationID);

  void StopAnimation(unsigned int animationID);
  void CompleteAnimation(unsigned int animationID, bool a2);

  void SetMaterial(unsigned int materialID);
  void SetMaterial(class Material* material);

  void SetName(unsigned short* name);

  void SetOverriddenBoundingBox(int x0, int y0, unsigned int x1, unsigned int y1);
  void GetOverriddenBoundingBox(int& x0, int& y0, unsigned int& x1, unsigned int& y1);

  void SetPosition(unsigned int xPos, unsigned int yPos);
  void SetRotation(float rotation);
  void SetScale(unsigned int scale);

  void SetSize(unsigned int xSize, unsigned int ySize);
  void SetXScale(unsigned int xScale);
  void SetYScale(unsigned int yScale);

  void SetVisible(bool bVisible);
  bool TreeVisible();

  NodeBase* HitTest(int x, int y, bool idk);
  NodeBase* HitTestChildren(int x, int y);

  void Update(float timeDelta);
  void UpdateChildren(float timeDelta);
  void UpdateZero();
  void UpdateCurrentPositions();

  void HandleEvent(Event* event);
  void HandleEventRecursive(Event* event);

  NodeBase* GetChild(unsigned int index);
  void DeleteChild(NodeBase* node);

  void DeleteSelf();

  void RenderChildren(unsigned int renderLayer);
  void Render(unsigned int renderLayer);

  bool IsDescendantOf(NodeBase* node);

  void ImportNode(NodeBase* node);

  bool Load(XmlNode* xmlNode);

  static NodeBase* CreateNode(unsigned int* nodeType);
  static void RegisterNodeType(const wchar_t* name, CreateFunction createFunction);
  static void Register();
  static int GetRenderLayerIsUsed(unsigned int renderLayer);

  void GetLayoutLocation(int& x, int& y);
  void GetLayoutSize(unsigned int& x, unsigned int& y);

  void SetAccessible(bool bAccessible, unsigned int accessRole);

  void SetAccessDefaultAction(wchar_t* action);
  wchar_t* GetAccessDefaultAction();
  void SetAccessDescription(wchar_t* description);
  wchar_t* GetAccessDescription();
  void SetAccessKeyShortcut(wchar_t* shortcut);
  wchar_t* GetAccessKeyShortcut();
  void SetAccessName(wchar_t* name);
  wchar_t* GetAccessName();
  void SetAccessValue(wchar_t* value);
  wchar_t* GetAccessValue();
  void SetAccessRole(unsigned int role);
  unsigned int GetAccessRole();

  void AddListener(IEventListener* listener);
  void RemoveListener(IEventListener* listener);

};

#endif // _NODEBASE_H_
