// Create : 2009/12/02
// Author : yuki suga @ ysuga.net
//
// copyright : ysuga.net, 2009
// This file must be used under the terms of GNU Public License version 3.
// This source file is licensed as described in the file license.txt, which
// you should have received as part of this distribution.


function e=rtcconf_generate(libpath)
  if (~exists("libpath")) then,
    libpath = ".";
  end;

  if(length(libpath) >= 2) then,
    libpathchars = strsplit(libpath);
    lastchar = libpathchars(length(libpath));
  else,
    lastchar = libpath;
  end;

  if(lastchar ~= "\" & lastchar ~= "/") then,
    libpath = libpath + filesep();
  end;

  
  if isfile(libpath+"rtc.conf") then,
    e = 24;
    return;
  end;
  
  [uo, eo] = mopen(libpath + "rtc.conf", "w");
  if eo~=0 then,
    disp("Creating rtc.conf failed.");
    e = eo;
    return;
  end;
  
  [ui, ei] = mopen(rtcscilab_rootdir + filesep() + "rtc.conf.example", "r");
  if ei ~= 0 then,
    disp("Opening original rtc.conf (" + rtcscilab_rootdir + filesep() + "rtc.conf) failed.");
    e = ei;
    return;
  end;
  
  strvec = mgetl(ui);
  mputl( strvec, uo);
  mclose(uo);
  mclose(ui);
  
  e = 0;
endfunction

