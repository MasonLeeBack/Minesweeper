/*

OberEngine Decompilation

File name:
  animationdescriptor.h

*/

#ifndef _ANIMATIONDESCRIPTOR_H_
#define _ANIMATIONDESCRIPTOR_H_

class AnimationState {
public:
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
  AnimationDescriptor();
  ~AnimationDescriptor();

  AnimationState* CreateState(bool);
};

#endif // _ANIMATIONDESCRIPTOR_H_
