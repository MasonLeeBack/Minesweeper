/*

OberEngine Decompilation

File name:
  animationdescriptor.cpp

*/

#include "stdafx.h"
#include "animationdescriptor.h"

AnimationState* AnimationDescriptor::CreateState(bool a1)
{
  AnimationState* newState = new AnimationState(this, a1);

  if (newState)
    newState->Reset();

  return newState;
}

void AnimationDescriptor::AddAnimator(Animator_Base* animator, Affector_Base* affector)
{
  animators.Add(animator);
  affectors.Add(affector);
}
