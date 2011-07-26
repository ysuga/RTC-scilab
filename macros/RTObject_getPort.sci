// RTObject_getConfSet.sci
// Create : 2009/12/02
// Author : yuki suga @ ysuga.net
//
// copyright : ysuga.net, 2009
// This file must be used under the terms of GNU Public License version 3.
// This source file is licensed as described in the file license.txt, which
// you should have received as part of this distribution.


//////////////////////////////
// RTC_getCSet
//
// this: RTC
//////////////////////////////
function ret = RTObject_getPort(this, names)
	ret = call("Port_create", ... 
	 this, 1, "i",...
	 "___"+RTObject_getInstanceName(this)+"."+names, 2, "c",...
	 "out", [1 1], 3, "i");
endfunction

