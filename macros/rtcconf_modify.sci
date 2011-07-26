// Create : 2009/12/02
// Author : yuki suga @ ysuga.net
//
// copyright : ysuga.net, 2009
// This file must be used under the terms of GNU Public License version 3.
// This source file is licensed as described in the file license.txt, which
// you should have received as part of this distribution.


function e=rtcconf_modify(key, value)
  [u, e] = mopen("rtc.conf", "r");
  if e ~= 0 then,
    disp("Opening rtc.conf failed.");
    return;
  end;
  
  strvec = mgetl(u);
  mclose(u);
  sz = size(strvec);
  for k=1:sz(1),
    strveckey = strtok(strvec(k), ":");
    strvecvalue = stripblanks(strsubst(strvec(k), strveckey+":", ""));
    tkn = [stripblanks(strveckey), strvecvalue];
    ret=strcmp(key, tkn(1));
    if ret == 0 then, // match!
      tkn(2) = value;
      strvec(k) = tkn(1) + ": " + tkn(2);
      e = 0;
      
      [u,e]=mopen("rtc.conf", "w");
      mputl(strvec, u);
      mclose(u);
      return;
    end;
  end;
  e = -1;    
endfunction