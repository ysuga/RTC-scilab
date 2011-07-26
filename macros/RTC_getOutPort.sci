// ScilabComp.sci
// Create : 2009/12/02
// Author : yuki suga @ ysuga.net
//
// copyright : ysuga.net, 2009
// This file must be used under the terms of GNU Public License version 3.
// This source file is licensed as described in the file license.txt, which
// you should have received as part of this distribution.


function port=RTC_getOutPort(rtc, name)
  port = call("RTC_getOutPort", rtc, 1, "i",...
     "___"+name, 2, "c",...
     "out", [1 1], 3, "i");
endfunction
