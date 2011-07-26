// RTC_delAllPort.sci
// Create : 2009/12/02
// Author : yuki suga @ ysuga.net
//
// copyright : ysuga.net, 2009
// This file must be used under the terms of GNU Public License version 3.
// This source file is licensed as described in the file license.txt, which
// you should have received as part of this distribution.


//////////////////////////////////////////
// SciComp_delAllPort (delete All port function)
//
//////////////////////////////////////////
function new_rtc=SciComp_delAllPort(rtc)
  for k=1:rtc.m_InPorts.m_Size,
    port = rtc.m_InPorts.get(rtc.m_InPorts, k);
    rtc.deletePort(rtc, port);
  end;
  for k=1:rtc.m_OutPorts.m_Size,
    port = rtc.m_OutPorts.get(rtc.m_OutPorts, k);
    rtc.deletePort(rtc, port);
  end;  
  
  rtc.m_OutPorts = rtc.m_OutPorts.delAllPort(rtc.m_OutPorts);
  rtc.m_InPorts  = rtc.m_InPorts.delAllPort(rtc.m_InPorts);

  new_rtc = rtc;
endfunction
