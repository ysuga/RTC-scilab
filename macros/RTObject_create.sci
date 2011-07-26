// RTObject_create.sci
// Create : 2009/12/02
// Author : yuki suga @ ysuga.net
//
// copyright : ysuga.net, 2009
// This file must be used under the terms of GNU Public License version 3.
// This source file is licensed as described in the file license.txt, which
// you should have received as part of this distribution.



//////////////////////////////////////////
// RTObject_create
//
// naming: int CorbaNamingHandle
// name: string (name of RT Component)
/////////////////////////////////////////
function component = RTObject_create(naming, name)
   component = call("RTObject_create", naming, 1, "i", name, 2, "c", "out", [1 1], 3, "i");
endfunction