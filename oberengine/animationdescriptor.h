/*

OberEngine Decompilation

File name:
  animationdescriptor.h

*/

#ifndef _ANIMATIONDESCRIPTOR_H_
#define _ANIMATIONDESCRIPTOR_H_

#include <array.h>

class Affector_Base {

};

class Animator_Base {

};

class AnimationState {
public:
  uint32_t field_0;
  uint32_t field_4;
  uint32_t field_8;
  uint32_t field_C;
  bool field_10;
  uint32_t field_14;
  AnimationDescriptor* animDescriptor;
  bool m_Playing;
  bool m_Reversed;
  bool field_1E;
  uint32_t field_20;
  uint32_t field_24;
  float field_28;

  AnimationState(class AnimationDescriptor*, bool);
  ~AnimationState();

  void Update();
  void SetTime(float fTime);
  void SetTarget(class NodeBase* pTarget);
  void SetPlaying(bool bPlaying);
  void SetReverse(bool bReverse);
  void SetAnimationHandle(unsigned int nAnimationHandle);
  void Reset();
};

class AnimationDescriptor
{
public:
  bool field_0;
  Array<Animator_Base*> animators;
  Array<Affector_Base*> affectors;

  AnimationDescriptor();
  ~AnimationDescriptor();

  AnimationState* CreateState(bool);
  void AddAnimator(Animator_Base* animator, Affector_Base* affector);
};

#endif // _ANIMATIONDESCRIPTOR_H_
