// OutPort_create.sci
// Create : 2009/12/02
// Author : yuki suga @ ysuga.net
//
// copyright : ysuga.net, 2009
// This file must be used under the terms of GNU Public License version 3.
// This source file is licensed as described in the file license.txt, which
// you should have received as part of this distribution.



//////////////////////////////////////////////////
// OutPort_create
//
///////////////////////////////////////////////////
function port = OutPort_create(rtc, port_type, name)
  if ~exists("rtc") then, 
    error ("No argument"); return;
  end;

  port = call("RTC_registerOutPort", rtc, 1, "i",...
     port_type, 2, "c",...
     "___"+name, 3, "c",...
     "out", [1 1], 4, "i");
endfunction
