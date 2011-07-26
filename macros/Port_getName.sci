// PortProf_create.sci
// Create : 2009/12/02
// Author : yuki suga @ ysuga.net
//
// copyright : ysuga.net, 2009
// This file must be used under the terms of GNU Public License version 3.
// This source file is licensed as described in the file license.txt, which
// you should have received as part of this distribution.

///////////////////////////////////////////
// Port_getPortProfList
//
// port: Port
///////////////////////////////////////////
function retval = Port_getName(port)
	str=call("Port_getName", port, 1, "i", "out", [1 1024], 2, "c");
	retval = stripblanks(str);
	tok=tokens(retval, ".");
	retval = tok(2);
endfunction