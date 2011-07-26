lines(0);

disp("OpenHRP demonstraton");
disp("Please launch GRXUI (OpenHRP) first, and load openhrp_demo.xml before launching this demonstration. To continue simulation, input resume and press enter key.");

if ~isfile("rtc.conf") then,
  disp("rtc.conf does not exist in current directory. Please create rtc.conf using rtcconf_generate function.");
  return;
end;

disp("rtc.conf is automatically modified.");

rtcconf_modify("naming.formats", "%n.rtc");
rtcconf_modify("exec_cxt.periodic.rate", "1000");
if MSDOS then,
SimulationEC_loadpath = strsubst(getenv("OPENHRP_SDK_ROOT") + "\bin", "\", "/");rtcconf_modify("manager.modules.load_path", SimulationEC_loadpath);
rtcconf_modify("manager.modules.preload", "SimulationEC.dll");
else, // Linux
rtcconf_modify("manager.modules.load_path", "/usr/lib");
rtcconf_modify("manager.modules.preload", "SimulationEC.so");
end;
rtcconf_modify("exec_cxt.periodic.type", "SimulationEC");


disp("------------ rtc.conf -----------------------");
rtcconf_showall;
disp("-------------- NOTICE!! rtc.conf is modified.");

disp("initRTM(""InvPenController"")");
initRTM("InvPenController");

disp("Now calculating Feedback gain.");

M=10;
m=3;
l=3;
g=9.81;

printf("M=%f, m=%f, l=%f, g=%f\n", M, m, l, g);

J=[(M+m) m*l;m*l, m*l^2];
G=[0 0; 0 m*g*l];
b=[1; 0];

printf("J=[(M+m) m*l;m*l, m*l^2];\n");
printf("G=[0 0; 0 m*g*l];\n");
printf("b=[1; 0];\n");

printf("A=[zeros(J) eye(J); inv(J)*G zeros(J)];\n");
printf("B=[0;0;inv(J)*b];\n");
printf("C=[0 0 1 0; 0 0 0 1];\n");
printf("D=[];\n");


A=[zeros(J) eye(J); inv(J)*G zeros(J)];
B=[0;0;inv(J)*b];
C=[0 0 1 0; 0 0 0 1];
D=[];

printf("x0=[0; 0.1; 0; 0];\n");
printf("pol=[-1 -2 -3 -4];\n");
printf("K= -ppol(A, B, pol);\n");


x0=[0; 0.1; 0; 0];
pol=[-1 -2 -3 -4];
K= -ppol(A, B, pol);

printf("Feedback gain K is...\n");
disp(K);
demo_xcos = demopath + filesep() + "openhrp_demo.xcos";

printf("xcos(%s);\n", demo_xcos);
xcos(demo_xcos);


disp("INSTRUCTION>> Start Simulation of xcos! After that, Start OpenHRP3 simulation.\n");