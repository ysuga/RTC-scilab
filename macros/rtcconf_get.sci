// Create : 2009/12/02
// Author : yuki suga @ ysuga.net
//
// copyright : ysuga.net, 2009
// This file must be used under the terms of GNU Public License version 3.
// This source file is licensed as described in the file license.txt, which
// you should have received as part of this distribution.

function e=rtcconf_get(key)
  [u, e] = mopen("rtc.conf", "r");
  if e ~= 0 then,
    disp("Opening rtc.conf failed.");
    e = [];
    return;
  end;
  
  strvec = mgetl(u); // read all line. string vector
  mclose(u);
  sz = size(strvec); // sz == lines
  for k=1:sz(1),
    strveckey = stripblanks(strtok(strvec(k), ":"));
    strvecvalue = stripblanks(strsubst(strvec(k), strveckey+":", ""));
    tkn = [strveckey, strvecvalue];
    ret=strcmp(key, tkn(1));
    if ret == 0 then, // match!
      e = tkn(2);
      return;
    end;
  end;
  e = [];
endfunction
