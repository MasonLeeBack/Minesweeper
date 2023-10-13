/*

OberEngine Decompilation

File name:
  access_node.h

*/

#ifndef _ACCESS_NODE_H_
#define _ACCESS_NODE_H_

#include <oleacc.h>

class Access_Node : IAccessible {
public:
  STDMETHODIMP accDoDefaultAction(VARIANT varChild) override;
};

#endif // _ACCESS_NODE_H_
