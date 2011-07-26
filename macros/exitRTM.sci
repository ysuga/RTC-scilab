// exitRTM.sci
// Create : 2009/12/02
// Author : yuki suga @ ysuga.net
//
// copyright : ysuga.net, 2009
// This file must be used under the terms of GNU Public License version 3.
// This source file is licensed as described in the file license.txt, which
// you should have received as part of this distribution.


///////////////////////////////////////////////
// WARNING....
// This module does not allow you to re-call
// initRTM function.
// because OpenRTM-aist can not exit without
// any error or memory-leaking.
// If you do so, scilab will halt with error.
///////////////////////////////////////////////

//////////////////////////////////////////////
// exitRTM
//
// cleanup RTC-Sci Module
//////////////////////////////////////////////
function exitRTM()
  printf("\n");
  printf("/////////////////////////////////////////\n");
  printf("//              RTC-scilab             //\n");
  printf("//                                     //\n");
  printf("// Author: Yuki Suga (ysuga@ysuga.net) //\n");
  printf("//     Copyright: ysuga.net 2009       //\n");
  printf("//                                     //\n");
  printf("/////////////////////////////////////////\n");
  
  printf("RTC-scilab: exit...");
  Manager_destroy();
endfunction
