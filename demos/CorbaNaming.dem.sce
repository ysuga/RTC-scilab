// ====================================================================
// Copyright DIGITEO 2008
// Allan CORNET
// This file is released into the public domain
// ====================================================================
mode(-1);
lines(0);

disp("CorbaNaming.dem.sce");

printf("rtcconf_modify(""exec_cxt.periodic.type"", ""PeriodicExecutionContext"")");
rtcconf_modify("exec_cxt.periodic.type", "PeriodicExecutionContext");
printf("rtcconf_modify(""naming.formats"", ""%%n.rtc"")");
rtcconf_modify("naming.formats", "\%n.rtc");


printf("initRTM(""CorbaNamingDemo"");\n");
initRTM("CorbaNamingDemo");

printf("//// Preparing RT-Component.\n\n");

printf("rtc = RTC_create();\n");
rtc = RTC_create();

printf("in0 = RTC_addInPort(rtc, ""TimedFloat"", ""in0"");\n");
in0 = RTC_addInPort(rtc, "TimedFloat", "in0");

printf("out0 = RTC_addOutPort(rtc, ""TimedFloat"", ""out0"");\n\n");
out0 = RTC_addOutPort(rtc, "TimedFloat", "out0");


printf("\n//// Creating Connection between InPort & OutPort.\n\n");

printf("corbaNaming = CorbaNaming_create(""localhost:2809"");\n");
corbaNaming = CorbaNaming_create("localhost:2809");

printf("rtobj = CorbaNaming_resolve(corbaNaming, ""scilab.app_cxt/CorbaNamingDemo0.rtc"");\n");
rtobj = CorbaNaming_resolve(corbaNaming, "CorbaNamingDemo0.rtc");

printf("in0_ref = RTObject_getPort(rtobj, ""in0"");\n");
in0_ref = RTObject_getPort(rtobj, "in0");
printf("out0_ref = RTObject_getPort(rtobj, ""out0"");\n");
out0_ref = RTObject_getPort(rtobj, "out0");

printf("connection = Connection_create(in0_ref, out0_ref);\n");
connection = Connection_create(in0_ref, out0_ref);

printf("RTObject_activate(rtobj)\n");
RTObject_activate(rtobj);

printf("// Testing Port read/write\n");
printf("disp(InPort_isNew(in0))\n");
disp(InPort_isNew(in0));
printf("OutPort_write(out0, 3.141592)\n");
OutPort_write(out0, 3.141592);
printf("disp(InPort_isNew(in0))\n");
disp(InPort_isNew(in0));
printf("data_size = [1, 1]\n");
data_size = [1, 1];
printf("buf = InPort_read(in0, data_size)\n");
buf = InPort_read(in0, data_size);
printf("disp(buf)\n");
disp(buf);

// ====================================================================
