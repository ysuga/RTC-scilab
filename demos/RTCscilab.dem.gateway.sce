// ====================================================================
// Copyright INRIA 2008
// Allan CORNET
// This file is released into the public domain
// ====================================================================
demopath = get_absolute_file_path("RTCscilab.dem.gateway.sce");

subdemolist = ["Creating Scilab RT Component", "ScilabComp.dem.sce";
	       "Using Corba Naming Service",   "CorbaNaming.dem.sce";
               "RTCscilab with xcos" , "xcos_demo.dem.sce";
               "Function Generator (Sine Wave)", "function_generator_demo.dem.sce";
               "Scope","scope_demo.dem.sce";
               "Robot Controller" ,"robot_ctrl_demo.dem.sce";
               "Robot Animation" ,"robot_anim_demo.dem.sce";
               "OpenHRP3 DEMO (Launch GRXUI first!)", "openhrp_demo.dem.sce"];

subdemolist(:,2) = demopath + subdemolist(:,2);
// ====================================================================
