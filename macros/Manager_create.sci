// Manager_create.sci
// Create : 2009/12/02
// Author : yuki suga @ ysuga.net
//
// copyright : ysuga.net, 2009
// This file must be used under the terms of GNU Public License version 3.
// This source file is licensed as described in the file license.txt, which
// you should have received as part of this distribution.



////////////////////////////////////////
// Manager_create
//
// You do not have to call this function, 
// because this function is called in
// initRTC().
// This function is indispensable because
// CorbaORB object is also created with
// RTC::Manager object.
/////////////////////////////////////////
function []=Manager_create(naming_formats, pathrtcconf)
  if(~exists("naming_formats")) then,
    naming_formats = "LabComp";
    pathrtcconf = "rtc.conf";
  elseif (~exists("pathrtcconf")) then,
    pathrtcconf = "rtc.conf";
  end;

  pathrtcconf = "-f " + pathrtcconf;
  call("Manager_create", naming_formats, 1, "c", pathrtcconf, 2, "c", "out");
endfunction