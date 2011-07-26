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
function retval = Port_getDataflowType(port)
  plist = Port_getProfileList(port);
  if length(plist) == 0 then,
    retval = "NULL";
    return;
  end;

  retval = plist(4, 2);
endfunction