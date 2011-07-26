// OutPort_write.sci
// Create : 2009/12/02
// Author : yuki suga @ ysuga.net
//
// copyright : ysuga.net, 2009
// This file must be used under the terms of GNU Public License version 3.
// This source file is licensed as described in the file license.txt, which
// you should have received as part of this distribution.



///////////////////////////////////////////////
// OutPort_writeD
//
///////////////////////////////////////////////
function retval = OutPort_write(port, arg) 
  sz = size(arg);
  len = sz(1)*sz(2); 

  if(port < 2000) then,
    retval = call("RTC_writePortLong",...
	  port, 1, "i", arg, 2, "i", len, 3, "i",...
	  "out", [1 1], 4, "i");
  elseif(port < 3000) then,
    retval = call("RTC_writePortFloat",...
	  port, 1, "i", arg, 2, "r", len, 3, "i",...
	  "out", [1 1], 4, "i");
  elseif(port < 4000) then,
    retval = call("RTC_writePortDouble",...
	  port, 1, "i", arg, 2, "d", len, 3, "i",...
	  "out", [1 1], 4, "i");
  elseif(port < 5000) then,
    retval = call("RTC_writePortLong",...
	  port, 1, "i", arg, 2, "i", len, 3, "i",...
	  "out", [1 1], 4, "i");
  else,
    retval = -1;
  end;
endfunction
