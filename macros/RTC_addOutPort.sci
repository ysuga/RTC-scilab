// RTC_addOutPort
// Create : 2009/12/02
// Author : yuki suga @ ysuga.net
//
// copyright : ysuga.net, 2009
// This file must be used under the terms of GNU Public License version 3.
// This source file is licensed as described in the file license.txt, which
// you should have received as part of this distribution.


///////////////////////////////////////////
// RTC_registerOutPort
// 
// register OutPort to SciComp object.
// rtc: SciComp
// type_name: string (TimedFloat, TimedDouble, TimedLong, and 
//  TimedFloatSeq, TimedDoubleSeq, TimedLongSeq.
// name: string (Port name);
///////////////////////////////////////////
function port=RTC_addOutPort(rtc, type_name, name)
  port = OutPort_create(rtc, type_name, name);
endfunction
