// ====================================================================
// Copyright INRIA 2008
// Allan CORNET
// This file is released into the public domain
// ====================================================================
mode(-1);
lines(0);

initRTM("RTCscilabDemo");


printf("initRTM(""RTCscilabDemo"");\n");
printf("rtc = RTC_create();\n");
printf("port_in0 = RTC_registerInPort(rtc, ""TimedFloat"", ""in0"");\n");
printf("port_out0 = RTC_registerOutPort(rtc, ""TimedFloat"", ""out0"");\n");

rtc = RTC_create();
port_in0 =RTC_registerInPort(rtc, "TimedFloat", "in0");
port_out0 = RTC_registerOutPort(rtc, "TimedFloat", "out0");

disp("INSTRUCTION>> Use RT System Editor, then connect RTCscilabDemo0.out0 --> RTCscilabDemo0.in0. After that, activate it. \nThen, hit ""resume"" to continue....");
pause;


printf("OutPort_write(port_out0, 1234);");
printf("if(InPort_isNew(port_in0)) then, disp(InPort_read(port_in0, [1 1])); else, disp(""No Data.""); end;");

OutPort_write(port_out0, 1234);
if(InPort_isNew(port_in0)) then, disp(InPort_read(port_in0, [1 1])); else, disp("No Data."); end;
// ====================================================================
