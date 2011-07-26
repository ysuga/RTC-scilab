

function mat=matrix_rotate(axis, Theta) 
  if (axis=="x") then,
    mat = matrix_rotatex(Theta);
  elseif (axis=="y") then,
    mat = matrix_rotatey(Theta);
  elseif (axis=="z") then,
    mat = matrix_rotatez(Theta);
  else,
  end;
endfunction

function mat=matrix_rotatex(Theta) 
  sinTheta = sin(Theta);
  cosTheta = cos(Theta);
  mat = [1,        0,         0, 0;...
         0, cosTheta, -sinTheta, 0;...
         0, sinTheta,  cosTheta, 0;...
         0,        0,         0, 1];
endfunction

function mat=matrix_rotatey(Theta) 
  sinTheta = sin(Theta);
  cosTheta = cos(Theta);
  mat = [cosTheta, 0, -sinTheta, 0;...
         0,        1,         0, 0;...
         sinTheta, 0,  cosTheta, 0;...
         0,        0,         0, 1];
endfunction

function mat=matrix_rotatez(Theta) 
  sinTheta = sin(Theta);
  cosTheta = cos(Theta);
  mat = [cosTheta, -sinTheta,  0, 0;...
         sinTheta,  cosTheta,  0, 0;...
         0,        0,          1,  0;...
         0,        0,         0,  1];
endfunction

function mat=matrix_transition(x, y, z)
  mat = [1, 0, 0, x;...
         0, 1, 0, y;...
         0, 0, 1, z;...
         0, 0, 0, 1];
endfunction

function y=robot_fwd_kinematics(th)
    y=[0; 0; 0; 0];
    L=[100, 100, -151.35, 140, 115, 81, -1.5, 63, 441.35];
    
    lp = [0, L(3), 0;
          0, 0, L(4);
          0, 0, L(5);
          0, 0, L(6);
          L(7), 0, 0;
          0, 0, L(8);
          0, L(9), 0;
          0, 0, 50;
          0, -L(9),0]; // Matrix Translations
    axis = ["y", "y", "y", "z"]; // Rotation Axes
    
    R = matrix_transition(L(1), 0, L(2));
    /// Rotation after Transition 
    R = R * matrix_transition(lp(1, 1), lp(1, 2), lp(1, 3)) ...
           * matrix_rotate(axis(1), th(1)); 
    R = R * matrix_transition(lp(2, 1), lp(2, 2), lp(2, 3)) ...
           * matrix_rotate(axis(2), th(2));
    R = R * matrix_transition(lp(3, 1), lp(3, 2), lp(3, 3)) ...
           * matrix_rotate(axis(3), th(3));

//    for k = 1:3,
//      R=  R * matrix_transition(lp(k, 1), lp(k, 2), lp(k, 3)) ...
//                 * matrix_rotate(axis(k), th(k));
//    end;
    
    //R= R* matrix_transition(lp(4, 1), lp(4, 2), lp(4, 3));
    
    //R= R * matrix_transition(lp(5, 1), lp(5, 2), lp(5, 3))...
    //             * matrix_rotate(axis(4), th(4));
    
    //R= R* matrix_transition(lp(6, 1), lp(6, 2), lp(6, 3));                
    y(1) = R(1, 4); // x
    y(2) = R(3, 4); // z
    y(3) = th(1)+th(2)+th(3); // z
    y(4) = th(4);
endfunction

function y=robot_inv_kinematics(u1, u2)
  s1 = sin(u2(1));
  s2 = sin(u2(2));
  c1 = cos(u2(1));
  c2 = cos(u2(2));
  s12 = sin(u2(1)+u2(2));
  c12 = cos(u2(1)+u2(2));
  l1 = 3.00;
  l2 = 3.00;
  epsilon = 0.0005;
  
  J = [ -l1*s1-l2*s12, -l2*s12, 0;...
        l1*c1+l2*c12 , l2*c12, 0;...
        1, 1, 1 ];
  if(det(J) == 0) then,
    th1 = epsilon;
    th2 = epsilon;
    th3 = epsilon;
    ybuf = [th1; th2; th3];
  else,
    iJ = inv(J);
    u = [u1(1); u1(2); u1(3)];
    ybuf = iJ * u;
  end;
  y = [ybuf(1); ybuf(2); ybuf(3); u1(4)];
endfunction