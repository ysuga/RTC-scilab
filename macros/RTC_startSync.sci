// RTC_startSync
// Create : 2009/12/02
// Author : yuki suga @ ysuga.net
//
// copyright : ysuga.net, 2009
// This file must be used under the terms of GNU Public License version 3.
// This source file is licensed as described in the file license.txt, which
// you should have received as part of this distribution.



///////////////////////////////////////////
// RTC_startSync
//
//
///////////////////////////////////////////
function retval = RTC_startSync(rtc)
  retval = call("RTC_startSync", rtc, 1, "i",...
      "out", [1 1], 2, "i");
endfunction

