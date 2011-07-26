// Connection_create.sci
// Create : 2009/12/02
// Author : yuki suga @ ysuga.net
//
// copyright : ysuga.net, 2009
// This file must be used under the terms of GNU Public License version 3.
// This source file is licensed as described in the file license.txt, which
// you should have received as part of this distribution.

//////////////////////////////////////////////
// Connection_create
//
//
//////////////////////////////////////////////
function retval = Connection_create(portA, portB)
  id   = "connection_id";
  name = "connection_name";
  
  retval = call("Connection_create",...
        id, 1, "c", name, 2, "c",...
        portA, 3, "i", ...
        portB, 4, "i", ...
        "out", [1 1], 5, "i");

endfunction

