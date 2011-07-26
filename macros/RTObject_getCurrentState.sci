// RTObject_getConfSet.sci
// Create : 2009/12/02
// Author : yuki suga @ ysuga.net
//
// copyright : ysuga.net, 2009
// This file must be used under the terms of GNU Public License version 3.
// This source file is licensed as described in the file license.txt, which
// you should have received as part of this distribution.


///////////////////////////////////////////
// RTObject_getCurrentSate
//
// this: RTC
///////////////////////////////////////////
function result = RTObject_getCurrentState(this)
  resstr = call("RTObject_getCurrentState", this, 1, "i",...
     "out", [1024 1], 2, "c");
  result = stripblanks(resstr);
endfunction


