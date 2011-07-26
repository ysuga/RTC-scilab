// RTObject_getCSetNameList.sci
// Create : 2009/12/02
// Author : yuki suga @ ysuga.net
//
// copyright : ysuga.net, 2009
// This file must be used under the terms of GNU Public License version 3.
// This source file is licensed as described in the file license.txt, which
// you should have received as part of this distribution.


//////////////////////////////
// RTC_getConfSetList
//
// this: RTC
//////////////////////////////
function name_list = RTObject_getCSNameList(this)
	ret = call("RTC_getConfSetNameList", ... 
	 this, 1, "i",...
	 "out", [1024 1], 2, "c");
	
	name_list = tokens(ret);

	if(name_list(1) == "failed") then 
		name_list = [];
		return;
	end;
endfunction

