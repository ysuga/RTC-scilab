// InPort_poll.sci
// Create : 2009/12/02
// Author : yuki suga @ ysuga.net
//
// copyright : ysuga.net, 2009
// This file must be used under the terms of GNU Public License version 3.
// This source file is licensed as described in the file license.txt, which
// you should have received as part of this distribution.



//////////////////////////////////////////////
//
//
///////////////////////////////////////////////
function retval = InPort_poll(port)
  ret = call("RTC_pollInPort",... 
    port, 1, "i", ...
    "out", [1 1], 2, "i");
  if(ret ~= 0) then,
    retval = %T;
  else
    retval = %F;
  end;
endfunction