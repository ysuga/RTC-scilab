// RTC_deletePort.sci
// Create : 2009/12/02
// Author : yuki suga @ ysuga.net
//
// copyright : ysuga.net, 2009
// This file must be used under the terms of GNU Public License version 3.
// This source file is licensed as described in the file license.txt, which
// you should have received as part of this distribution.




///////////////////////////////////////////
// RTC_deleteInPort(rtc, port)
//
// This function allows 2 style of calling
// one: port is Port type object.
// two: port is name (string) of port 
///////////////////////////////////////////
function retval=RTC_deleteInPort(rtc, port)
  retval = call("RTC_deleteInPort", rtc, 1, "i",...
    port, 2, "i",...
    "out", [1 1], 3, "i");
endfunction


