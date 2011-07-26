// SciCos_CompFunc.sci
// Create : 2009/12/02
// Author : yuki suga @ ysuga.net
//
// copyright : ysuga.net, 2009
// This file must be used under the terms of GNU Public License version 3.
// This source file is licensed as described in the file license.txt, which
// you should have received as part of this distribution.


function [block_upd] = XCos_EvtDly(block, flag)
  block_upd = block; 
  
  global( "sciComp" );
  global( "i_xcos_evtdly" );


  // Outputs update ///////////////////////////////
  if flag == 1 then, 

  elseif flag == 3 then,
    RTC_notify(sciComp);
    t = scicos_time();
    // printf("t=%f\n", t);
    i_xcos_evtdly = i_xcos_evtdly + block.rpar(1);
    ret = RTC_wait(sciComp);
    block.evout(1) = i_xcos_evtdly - t;
    if ret == -2 then,
       disp("Synchronization failed. RTC is deactivated. Please stop xcos simulation, then type ""resume""");
       pause;
    elseif ret < 0 then, 
       disp("Synchronization error. Please restart scilab. ret = " + string(ret));
       pause;
    end;

    block_upd = block;
    
  // Initialization /////////////////////////////////
  elseif flag == 4 then,
    if(length(sciComp)==0) then,
      sciComp = RTC_create();
    end;
    
    RTC_startSync(sciComp);
    ret = RTC_wait(sciComp);
    if ret < 0 then,
       disp("RTC_wait failed.");
       disp("ret = " + string(ret) + " sciComp = " + string(sciComp));
       pause;
    end;
//    i_xcos_evtdly = 0;
    i_xcos_evtdly = block.rpar(2);
    block_upd = block;
  elseif flag == 5 then,
    printf("stopSync......");
    RTC_stopSync(sciComp);
    printf("OK.\nnotify......");
    RTC_notify(sciComp);
    printf("OK.\n");
    block_upd = block;
  else, // other flags
    block_upd = block;   
  end; // select flag ....
endfunction




