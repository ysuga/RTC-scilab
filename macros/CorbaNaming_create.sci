// CorbaNaming_create.sci
// Create : 2009/12/02
// Author : yuki suga @ ysuga.net
//
// copyright : ysuga.net, 2009
// This file must be used under the terms of GNU Public License version 3.
// This source file is licensed as described in the file license.txt, which
// you should have received as part of this distribution.

////////////////////////////////
//   CorbaNaming_create
//
// addr: string (IP Address of NamingService)
// retval: CorbaNaming object.
//   if error, retval = empty (length=0)
////////////////////////////////
function retval = CorbaNaming_create(addr)
	retval = call("CorbaNaming_create", addr, 1, "c", "out", [1 1], 2, "i");
endfunction
