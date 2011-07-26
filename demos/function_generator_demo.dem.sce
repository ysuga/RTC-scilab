// ====================================================================
// Copyright INRIA 2008
// Allan CORNET
// This file is released into the public domain
// ====================================================================
mode(-1);
lines(0);

initRTM("FunctionDemo");

demo_xcos = demopath + filesep() + "function_generator_demo.xcos";

disp("xcos(""" + demo_xcos + """)");
xcos(demo_xcos);
// ====================================================================
