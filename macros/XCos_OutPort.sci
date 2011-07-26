// Create : 2009/12/02
// Author : yuki suga @ ysuga.net
//
// copyright : ysuga.net, 2009
// This file must be used under the terms of GNU Public License version 3.
// This source file is licensed as described in the file license.txt, which
// you should have received as part of this distribution.




function [block_upd] = XCos_OutPort(block, flag)
  block_upd = block; 
  global( "sciComp" );
  
  portName    = block.opar(1);
  typeName    = block.opar(2);
  
  
  // Update ///////////////////////////////
  if flag == 2 then, 
    //disp("XCos_OutPort.sci update...");
    outport = RTC_getOutPort(sciComp, portName);          
    OutPort_write(outport, block.inptr(1));
    block_upd = block;
    
  // Initialization /////////////////////////////////
  elseif flag == 4 then,
    //disp("XCos_OutPort.sci initialization...");
    if(length(sciComp)==0) then,
      sciComp = RTC_create();
      if(sciComp < 0) then,
        disp("RTC_create failed.");
      end;
    end;

    outport = RTC_getOutPort(sciComp, portName);
    if(outport < 0) then,
      RTC_registerOutPort(sciComp, typeName, portName);
    elseif (OutPort_getType(outport) ~= typeName) then,
      RTC_deleteOutPort(sciComp, portName);
      RTC_addOutPort(sciComp, typeName, portName);
    end;
    
    block_upd = block;
  else, // other flags
    block_upd = block;   
  end; // select flag ....
  
endfunction

function [block_upd] = XCos_InstanceName(block, flag)
  block_upd = block; 
  global( "sciComp" );
  instanceName    = block.opar(1);
    
  // Initialization /////////////////////////////////
  if flag == 4 then     
    if(length(sciComp)==0) then,
      sciComp = ScilabComp_create();
      sciComp = SciComp_setInstanceName(sciComp, instanceName);
    end;
  end; // select flag ....
  
endfunction





