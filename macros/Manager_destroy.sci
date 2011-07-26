// Manager_destroy.sci
// Create : 2009/12/02
// Author : yuki suga @ ysuga.net
//
// copyright : ysuga.net, 2009
// This file must be used under the terms of GNU Public License version 3.
// This source file is licensed as described in the file license.txt, which
// you should have received as part of this distribution.

////////////////////////////////////////
// Manager_destroy
//
// This function is also called in
// exitRTC function automatically
////////////////////////////////////////
function []=Manager_destroy()
  call("Manager_destroy");
endfunction

