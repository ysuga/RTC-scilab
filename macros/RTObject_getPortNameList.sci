// RTObject_getPortNameList.sci
// Create : 2009/12/02
// Author : yuki suga @ ysuga.net
//
// copyright : ysuga.net, 2009
// This file must be used under the terms of GNU Public License version 3.
// This source file is licensed as described in the file license.txt, which
// you should have received as part of this distribution.


//////////////////////////////
// RTObject_getPortNameList
//
// this: RTC
//////////////////////////////
function name_list=RTObject_getPortNameList(this)
	ret = call("RTObject_getPortNameList", this, 1, "i",...
	   "out",  [1 1024],2, "c");
	name_list = tokens(ret);
	
	if(name_list(1) == "failed") then 
		error("Cannot get RTC Name List from CorbaNaming."); return;
	end;

	sz = size(name_list);
	for k=1:sz(1),
		buf = tokens(name_list(k), ".");
		name_list(k) = buf(2);
	end;
endfunction
