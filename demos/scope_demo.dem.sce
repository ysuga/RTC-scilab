// ====================================================================
// Copyright INRIA 2008
// Allan CORNET
// This file is released into the public domain
// ====================================================================
mode(-1);
lines(0);

initRTM("ScopeDemo");

demo_xcos = demopath + filesep() + "scope_demo.xcos";

disp("xcos(""" + demo_xcos + """)");
xcos(demo_xcos);
// ====================================================================
