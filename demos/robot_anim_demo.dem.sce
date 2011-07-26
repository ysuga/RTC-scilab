// ====================================================================
// Copyright INRIA 2008
// Allan CORNET
// This file is released into the public domain
// ====================================================================
mode(-1);
lines(0);

exec(demopath + filesep() +"robot_arm_anim.sci");
exec(demopath + filesep() +"robot_arm_kinematics.sci");

disp("initRTM(""RobotAnimDemo"");\n");
initRTM("RobotAnimDemo");


demo_xcos = demopath + filesep() + "robot_anim_demo.xcos";

disp("xcos(""" + demo_xcos + """)");
xcos(demo_xcos);
// ====================================================================
