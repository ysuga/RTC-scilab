
function [block_upd] = robot_arm_anim(block, flag)
  block_upd = block; 
  ofst = 20000;
  win = ofst + curblock();


 /// disp("robot_arm_anim(" + string(flag) + ")" );
  JNT1_ID     = 7;
  LINK1_ID    = 6;
  JNT2_ID     = 5;
  LINK2_ID    = 4;
  JNT3_ID     = 3;
  LINK3_ID    = 2;
  END_EFCT_ID = 1;
  
  /// offset: When the robot arm is animated,
  /// the offset values are added by the joint angle th*.
  /// so these parameters define the initial posture of the arm.
  th1_offset = 0;
  th2_offset = %pi/2;
  th3_offset = 0;

  /// limitation of joint angle.
  th1_max = %pi/2;
  th1_min = -%pi/2;
  th2_max = %pi/2-0.1;
  th2_min = -%pi/2+0.1;
  th3_max = %pi;
  th3_min = -%pi;
  
  /// link length
  lp1 = block.rpar(1);  
  lp2 = block.rpar(2);  
  lp3 = block.rpar(3);
  
  // values for drawing joint point.
  RI = 0.25; 
  RO = 0.38; 
  ANG1 = 0;
  ANG2 = 360*64; 

  /// link1
  x1 = [0,  0];
  y1 = [0, lp1];

  /// link2
  x2 = [0,  0];
  y2 = [0,  lp2];
  
  // link3
  x3 = [0,  0];
  y3 = [0,  lp3];
  
  
  if flag == 4 then // Initialization //////////////////////////////////////////////////
    scf(win);                   
    set("figure_style", "new"); 
    h = gcf();
    toolbar(h.figure_id, "off");
    h.figure_name     = "Robot Arm";
    h.figure_position = [0, 0];
    h.figure_size     = [400, 400];
    clf(h);          
    h.pixmap = "on";
    axes = h.children;

    axes.data_bounds = [-7; 7; -7; 7]; 
    
    axes.isoview = "on";

    xfarc(x1(1) - RI, y1(1) + RI, 2*RI, 2*RI, ANG1, ANG2);
    a_in = gce();
    xarc(x1(1) - RO, y1(1) + RO, 2*RO, 2*RO, ANG1, ANG2);
    a_out = gce();
    glue([a_in, a_out]);

    // draw link1
    xpoly(x1, y1);

    // draw joint2
    xx = x2 + x1(2);
    yy = y2 + y1(2);
    xarc(xx(1) - RI, yy(1) + RI, 2*RI, 2*RI, ANG1, ANG2);
    a_in = gce();
    xarc(xx(1) - RO, yy(1) + RO, 2*RO, 2*RO, ANG1, ANG2);
    a_out = gce();
    glue([a_in, a_out]); 
    
    // draw link2
    xpoly(xx, yy);

    // draw joint3
    xx = x3 + x2(2);
    yy = y3 + y2(2);
    xarc(xx(1) - RI, yy(1) + RI, 2*RI, 2*RI, ANG1, ANG2);
    a_in = gce();
    xarc(xx(1) - RO, yy(1) + RO, 2*RO, 2*RO, ANG1, ANG2);
    a_out = gce();
    glue([a_in, a_out]); 
    
    // draw link3
    xpoly(xx, yy);


    // draw end effector
    xarc(xx(2) - RI, yy(2) + RI, 2*RI, 2*RI, ANG1, ANG2);
    
  elseif flag == 1 then // Request Output //////////////////////////////////
    h = scf(win);
    axes  = h.children;

    // read input datas.
    th1 = modulo(block.inptr(1)(1), 2*%pi);  
    if (th1 > th1_max) then, 
      th1 = th1_max;
    elseif (th1 < th1_min) then,
      th1 = th1_min;
    end;
    th1 = th1 + th1_offset;
    
    th2 = modulo(block.inptr(1)(2), 2*%pi);  
    if (th2 > th2_max) then, 
      th2 = th2_max;
    elseif (th2 < th2_min) then,
      th2 = th2_min;
    end;
    th2 = th2 + th2_offset;
    
    th3 = modulo(block.inptr(1)(3), 2*%pi);  
    if (th3 > th3_max) then, 
      th3 = th3_max;
    elseif (th3 < th3_min) then,
      th3 = th3_min;
    end;
    th3 = th3 + th3_offset;
 
    xy1 = rotate([x1; y1], th1, [0; 0]);
    axes.children(LINK1_ID).data = xy1';
    px = xy1(1, 2);
    py = xy1(2, 2);
    axes.children(JNT2_ID).children(2).data(1:2) = [px - RI, py + RI]; // [x, y]
    axes.children(JNT2_ID).children(1).data(1:2) = [px - RO, py + RO]; // [x, y]
    
    xy2 = rotate([x2 + px; y2 + py], th1 + th2, [px; py]);
    axes.children(LINK2_ID).data = xy2';
    px2 = xy2(1, 2);
    py2 = xy2(2, 2);
    axes.children(JNT3_ID).children(2).data(1:2) = [px2 - RI, py2 + RI]; // [x, y]
    axes.children(JNT3_ID).children(1).data(1:2) = [px2 - RO, py2 + RO]; // [x, y]
    
    xy3 = rotate([x3 + px2; y3 + py2], th1 + th2 + th3, [px2; py2]);
    axes.children(LINK3_ID).data = xy3';
    
    axes.children(END_EFCT_ID).data(1:2) = [xy3(1, 2) - RI, xy3(2, 2) + RI];
    
    show_pixmap();
 // elseif flag == 1 then, // request output data /////////////////////
      // read input datas.
    th1 = modulo(block.inptr(1)(1), 2*%pi);  
    if (th1 > th1_max) then, 
      th1 = th1_max;
    elseif (th1 < th1_min) then,
      th1 = th1_min;
    end;
    th1 = th1 + th1_offset;
    
    th2 = modulo(block.inptr(1)(2), 2*%pi);  
    if (th2 > th2_max) then, 
      th2 = th2_max;
    elseif (th2 < th2_min) then,
      th2 = th2_min;
    end;
    th2 = th2 + th2_offset;
  
    
    th3 = modulo(block.inptr(1)(3), 2*%pi);  
    if (th3 > th3_max) then, 
      th3 = th3_max;
    elseif (th3 < th3_min) then,
      th3 = th3_min;
    end;
    th3 = th3 + th3_offset;
    
  //  disp(th3);

    block.outptr(1)(1) = th1;  
    block.outptr(1)(2) = th2;  
    block.outptr(1)(3) = th3;
    
    block_upd = block;
  end;
endfunction

