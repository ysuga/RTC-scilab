// initRTM.sci
// Create : 2009/12/02
// Author : yuki suga @ ysuga.net
//
// copyright : ysuga.net, 2009
// This file must be used under the terms of GNU Public License version 3.
// This source file is licensed as described in the file license.txt, which
// you should have received as part of this distribution.


///////////////////////////////////////////////
// WARNING....
// This module does not allow you to re-call
// initRTM function.
// because OpenRTM-aist can not exit without
// any error or memory-leaking.
// If you do so, scilab will halt with error.
///////////////////////////////////////////////





////////////////////////////////////////////
// initRTM
//
// arg: 
//  ManagerName: Default Component Name.
//  libpath: directry path for rtc.conf file.
// 
// ex:
//  initRTM("ScilabComponent", "C:/users/ysuga/");
//
// Initializing RTC-Sci Module
// If you call this function with "debug" string argument,
// debug mode dll (RTC-scilabd.dll) will be loaded.
// otherwise, release mode dll (RTC-scilab.dll) will be loaded.
///////////////////////////////////////////

function initRTM(ManagerName, libpath)

  if(~exists("libpath")) then,
    libpath = ".";
  end;

  e = rtcconf_generate(libpath);
  if(e == 0) then,
    disp("rtc.conf is automatically generated in """ + libpath + """");
  elseif (e ~= 24) then,
    disp("rtc.conf automatic generation is failed. stop initializing RTCscilab.");
    return; 
  end;

if getos() == "Windows" then,
  filename = RTCscilab_libpath + filesep() + "RTCscilab.dll";
else,
  filename = RTCscilab_libpath + filesep() + "RTCscilab.so";
end;

  functions = [...
       "Manager_create", "Manager_destroy",...
       "CorbaNaming_create", "CorbaNaming_destroy", "CorbaNaming_destroyAll", "CorbaNaming_getRTCNameList",...
       "RTObject_create", "RTObject_destroy",...
       "RTObject_getCurrentState", "RTObject_reset", "RTObject_activate", "RTObject_deactivate", "RTObject_exit",...
       "RTObject_getPortNameList", "RTObject_getConfSetNameList", "RTObject_getInstanceName", ...
       "Port_create", "Port_destroy", "Port_getProfile", "Port_getName", ...
       "Connection_create", "Connection_destroy",...
       "ConfigurationSet_getConfNameList", "Configuration_configure", "Configuration_getValue", ...
       "RTC_create", "RTC_destroy", "RTC_getInstanceName", "RTC_registerOutPort", "RTC_registerInPort",...
       "RTC_getOutPort", "RTC_getOutPortType", "RTC_getInPort", "RTC_getInPortType", ...
       "RTC_writePortDouble", "RTC_writePortFloat", "RTC_writePortLong", "RTC_writePortBoolean",...
       "RTC_readPortDouble", "RTC_readPortFloat", "RTC_readPortLong", "RTC_readPortBoolean",...
       "RTC_pollInPort", "RTC_readInPort",...
       "RTC_deleteInPort", "RTC_deleteOutPort", "RTC_isAlive",...
       "RTC_wait", "RTC_notify",...
       "RTC_startSync", "RTC_stopSync" ...
       ];
    

  link(filename, functions, "c");

  global("defaultCompName");
  if( length(defaultCompName) ~= 0 ) then, 
    disp("!! initRTM has already called.");
    return;
   end;
  

  if(~exists("ManagerName")) then,
    ManagerName = "LabRTC";
    defaultCompName ="LabRTC";
  else,
    defaultCompName = ManagerName;
  end;

  usecanvas(%F);


  Manager_create(ManagerName, libpath);
endfunction


