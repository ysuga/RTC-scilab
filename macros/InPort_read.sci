// InPort_read.sci
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
function retval = InPort_read(port, sz)
  if(~exists("sz")) then, sz = [1 1];
  elseif(length(sz) < 2) then, sz = [sz 1];
  elseif(length(sz) > 2) then, sz = [sz(1) sz(2)];
  end;

  rcvSize = call("RTC_readInPort",...
          port, 1, "i", ...
	  "out", [1 1], 2, "i");

  readSize = sz(1) * sz(2);
  if( readSize > rcvSize ) then, 
    retval = []; return;
  end;

  if(port < 2000) then,
    retval = call("RTC_readPortLong",...
	  port, 1, "i", readSize, 2, "i", ...
	  "out", sz, 3, "i");
  elseif(port < 3000) then,
    retval = call("RTC_readPortFloat",...
	  port, 1, "i", readSize, 2, "i", ...
	  "out", sz, 3, "r");
  elseif(port < 4000) then,
    retval = call("RTC_readPortDouble",...
	  port, 1, "i", readSize, 2, "i", ...
	  "out", sz, 3, "d");
  elseif(port < 5000) then,
    retval = call("RTC_readPortLong",...
	  port, 1, "i", readSize, 2, "i", ...
	  "out", sz, 3, "i");
  else,
    retval = [];
  end;
endfunction
