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
function portprofilelist = Port_getProfileList(port)
  res = call("Port_getProfile", port, 1, "i",...
      "out", [1 1024], 2, "c");
      // Here the "dmy"+port.m_Name is very important.
      // If the port.m_Name is "out",scilab function "call" always fails,
      // because the "out" is keyword for "call" function 
      // to express that following arguments mean the profile of return value.
        
  profile_list = tokens(res);


  sz = size(profile_list);
  if (profile_list(1) == "failed") then
    error("FAILED TO GET PROFILE LIST.");
    portprofilelist = list(); return;
  else

    command = "[";
    for k=0:(sz(1)/2-1),
      command = command + ...
        "[""" + profile_list(k*2+1) + """, """ + profile_list(k*2+2) + """]";
      if k ~= (sz(1)/2-1) then,
        command = command + ";";
      end;
    end;
    command = command + "];";
    ppl = evstr(command);
  end;
  portprofilelist = ppl;
endfunction