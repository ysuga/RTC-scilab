// CorbaNaming_getRTCList.sci 
// Create : 2009/12/02
// Author : yuki suga @ ysuga.net
//
// copyright : ysuga.net, 2009
// This file must be used under the terms of GNU Public License version 3.
// This source file is licensed as described in the file license.txt, which
// you should have received as part of this distribution.





////////////////////////////////
//   CorbaNaming_getRTCList
//
// naming: CorbaNaming
////////////////////////////////
function name_list=CorbaNaming_getRTCList(naming)
	ret = call("CorbaNaming_getRTCNameList", naming, 1, "i", "out",  [1 1024], 2, "c");
	name_list = tokens(ret);
	if(name_list == "failed") then,
		name_list = [];
	end;
endfunction