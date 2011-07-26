// SciCos_CompFunc.sci
// Create : 2009/12/02
// Author : yuki suga @ ysuga.net
//
// copyright : ysuga.net, 2009
// This file must be used under the terms of GNU Public License version 3.
// This source file is licensed as described in the file license.txt, which
// you should have received as part of this distribution.



function [block_upd] = XCos_InPort(block, flag)
  block_upd = block; 
  global( "sciComp" );
//  global( "i_xcos_evtdly" );
  
  portName = block.opar(1);
  typeName = block.opar(2);
  sz = block.opar(3);

 // t = scicos_time();
 // printf("Time=%f:Psim=%d:flag=%d", scicos_time(), phase_simulation(), flag);
  
  // Outputs update ///////////////////////////////
  if flag == 2 then,
  //  inport = RTC_getInPort(sciComp, portName); 
  //  if(InPort_poll(inport)) then,
  //    val = InPort_read(inport, sz);
   //   if (length(val) == 0) then, 
   //     error("RTC InPort value size("+string(sz)+") is not equal to scilab output port.");
   //   end;
  //  else,
  //    val = InPort_read(inport, sz);
  //  end;
    //block.outptr(1) = sin(scicos_time());
 //   block.outptr(1) = matrix(val, size(block.outptr(1)) );
  //  block.outptr(1)(1) = sin(t);
  // printf("  dat(out)%f\n", block.outptr(1)(1));
    block_upd = block;
  elseif flag == 1 then, 
    inport = RTC_getInPort(sciComp, portName);        
    if(InPort_poll(inport)) then,
      val = InPort_read(inport, sz);
      if (length(val) == 0) then, 
        error("RTC InPort value size("+string(sz)+") is not equal to scilab output port.");
      end;
    else,
 //     printf("No coming Data............\n");
      val = InPort_read(inport, sz);
    end;  
    //block.outptr(1) = sin(scicos_time());
    block.outptr(1) = matrix(val, size(block.outptr(1)) );
  //  block.outptr(1)(1) = sin(t);
    block_upd = block;
 //   printf("  dat(new)%f\n", block.outptr(1)(1));
 //   disp(block.outptr(1));
    
  // Initialization /////////////////////////////////
  elseif flag == 4 then,
    if(length(sciComp)==0) then,
      sciComp = RTC_create();
      if(sciComp < 0) then,
        disp("RTC_create failed."); pause;
      end;
    end;
    inport     = RTC_getInPort(sciComp, portName);
    if(inport < 0) then,
      RTC_addInPort(sciComp, typeName, portName);
    elseif (InPort_getType(inport) ~= typeName) then,
      RTC_deleteInPort(sciComp, portName);
      RTC_addInPort(sciComp, typeName, portName);
    end;
//	block.outptr(1) = zeros(block.outptr(1));
//    i_xcos_evtdly = -1;
    block.outptr = [];
    block_upd = block;
  else, // other flags
    block_upd = block;   
  end; // select flag ....
endfunction




