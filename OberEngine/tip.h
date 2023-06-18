/*

OberEngine Decompilation
Original Game: Purble Place

*/

#ifndef _TIP_H_
#define _TIP_H_

#include "nodebase.h"

class Tip
{
public:
  struct TipSource {

  };

  Tip(NodeBase* base);
  ~Tip();

  void Arrange();
  void OnTipFadedOut();

  void Show();
  void Close(bool a1);

  void HandleEvent(struct Event* a1);
  bool Initialize(const TipSource* a1, bool a2);
};

#endif // _TIP_H_
