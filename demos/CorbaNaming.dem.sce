// ====================================================================
// Copyright DIGITEO 2008
// Allan CORNET
// This file is released into the public domain
// ====================================================================
mode(-1);
lines(0);

disp("CorbaNaming.dem.sce");

printf("initRTM(""CorbaNamingDemo"");\n");
initRTM("CorbaNamingDemo");

printf("//// Preparing RT-Component.\n\n");

printf("rtc = ScilabComp_create();\n");
rtc = ScilabComp_create();

printf("rtc = rtc.registInPort(rtc, ""TimedLong"", ""in0"");\n");
rtc = rtc.registInPort(rtc, "TimedLong", "in0");

printf("rtc = rtc.registOutPort(rtc, ""TimedLong"", ""out0"");\n\n");
rtc = rtc.registOutPort(rtc, "TimedLong", "out0");


printf("\n//// Creating Connection between InPort & OutPort.\n\n");

printf("corbaNaming = CorbaNaming_create(""localhost:2809"");\n");
corbaNaming = CorbaNaming_create("localhost:2809");

printf("rtobj = corbaNaming.resolve(corbaNaming, ""scilab.app_cxt/CorbaNamingDemo0.rtc"");\n");
rtobj = corbaNaming.resolve(corbaNaming, "scilab.app_cxt/CorbaNamingDemo0.rtc");

printf("in0 = rtobj.getPort(rtobj, ""in0"");\n");
in0 = rtobj.getPort(rtobj, "in0");
printf("out0 = rtobj.getPort(rtobj, ""out0"");\n");
out0 = rtobj.getPort(rtobj, "out0");

printf("connection = Connection_create(in0, out0);\n");
connection = Connection_create(in0, out0);

printf("rtobj.activate(rtobj)\n");
rtobj.activate(rtobj);




// ====================================================================
