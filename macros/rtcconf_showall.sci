// Create : 2009/12/02
// Author : yuki suga @ ysuga.net
//
// copyright : ysuga.net, 2009
// This file must be used under the terms of GNU Public License version 3.
// This source file is licensed as described in the file license.txt, which
// you should have received as part of this distribution.


function e=rtcconf_showall()
  [u, e] = mopen("rtc.conf", "r");
  if e ~= 0 then,
    disp("Opening rtc.conf failed.");
    return;
  end;
  
  strvec = mgetl(u);
  mclose(u);
  sz = size(strvec);
  outvec = [];

  for k=1:sz(1),
    if length(strvec(k)) ~= 0 then, 
    if strindex(strvec(k), "#") ~= 1 then,
      printf("%s\n", strvec(k));
    end;
    end;
  end;

endfunction