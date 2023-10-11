/*

OberEngine Decompilation

File name:
  tip.h

*/

#ifndef _TIP_H_
#define _TIP_H_

#include "event.h"

class Tip
{
public:
  struct TipSource {

  };

  Tip(class NodeBase* base);
  ~Tip();

  void Arrange();
  void OnTipFadedOut();

  void Show();
  void Close(bool a1);

  void HandleEvent(Event* a1);
  bool Initialize(const TipSource* a1, bool a2);
};

#endif // _TIP_H_
