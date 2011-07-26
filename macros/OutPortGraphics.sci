// Create : 2009/12/02
// Author : yuki suga @ ysuga.net
//
// copyright : ysuga.net, 2009
// This file must be used under the terms of GNU Public License version 3.
// This source file is licensed as described in the file license.txt, which
// you should have received as part of this distribution.


function [x,y,typ]=OutPortGraphics(job,arg1,arg2)
//
x=[];y=[];typ=[];
select job
case 'plot' then
  standard_draw(arg1)
case 'getinputs' then
  [x,y,typ]=standard_inputs(arg1)
case 'getoutputs' then
  [x,y,typ]=standard_outputs(arg1)
case 'getorigin' then
  [x,y]=standard_origin(arg1)
case 'set' then
  x=arg1
  model=arg1.model;graphics=arg1.graphics;label=graphics.exprs
  if size(label,'*')==14 then label(9)=[],end //compatiblit
  // label=[sci2exp(1); sci2exp(1); sci2exp(list("Hi"))];
  while %t do
    junction_name = "XCos_OutPort"; // function name
    funtyp        = 5; // function type
    out            = [];// input port size
    ot            = 1; // input port type
    ci            = [1]; // input event port size;
    co            = []; // output event port size;
    xx            = [0]; // initial continuous state;
    z             = [0]; // initial discrete state;
    oz            = list(); // initial object state;
    rpar          = [0]; // real parmeters vector;
    ipar          = [0]; // integer parameters vector;
    nmode         = 0;// number of modes;
    nzcr          = 0;// number of zero crossings;
    auto0         = []; // initial firing vector (<0 for no firing);
    depu          = 'y'; // direct feedthrough (y or n);
    dept          = 'n'; // time dependence (y or n);
  
    [ok,portname, porttype, in,lab]=..
        scicos_getvalue('Set DataInPort block parameters',..
        ['DataOutPort name';
         'DataOutPort type';
         'Size'],..
         list('str',-1,'str',-1,'mat',[-1 2]),label)
    if ~ok then break,end
    label=lab
    junction_name=stripblanks(junction_name)
    xx=xx(:);z=z(:);rpar=rpar(:);ipar=int(ipar(:));
    opar= list(portname, porttype);
    it = 1;
    
    ci=int(ci(:));
    co=int(co(:));
    funtyp=funtyp
    if funtyp<0 then message('function type cannot be negative');ok=%f;end
    //if [ci;co]<>[] then
    //  if maxi([ci;co])>1 then message('vector event links not supported');ok=%f;end
    //end
    if type(opar)<>15 then message('object parameter must be a list');ok=%f;end
    if type(oz)<>15 then message('discrete object state must be a list');ok=%f;end
    depu=stripblanks(depu);if part(depu,1)=='y' then depu=%t; else depu=%f;end
    dept=stripblanks(dept);if part(dept,1)=='y' then dept=%t; else dept=%f;end
    dep_ut=[depu dept];
    if ok then
      [model,graphics,ok]=set_io(model,graphics,list(in,it),list(out,ot),ci,co)
    end
    if ok then
      if funtyp==3 then needcompile=4;end
      model.sim=list(junction_name,funtyp);
      model.state=0
      model.dstate=0;
      model.odstate=[];//oz
      model.rpar=rpar
      model.ipar=ipar
      model.opar=opar
      model.firing=auto0
      model.nzcross=nzcr
      model.nmode=nmode
      model.blocktype = 'c'
      model.dep_ut=dep_ut
      arg1.model=model
      graphics.exprs=label
      arg1.graphics=graphics
      x=arg1
      break
    end
  end
  needcompile=resume(needcompile)

case 'define' then
  model=scicos_model()
  junction_name='XCos_OutPort';
  funtyp=5;
  model.sim=list(junction_name,funtyp)

  model.in=1
  model.in2=1
  model.intyp=1
  model.out=[]
  model.out2=1
  model.evtin =[1]
  model.outtyp=1
  model.dep_ut=[%f %t]
  label=[//junction_name;sci2exp(funtyp);
         //sci2exp([model.in model.in2]);
         //sci2exp(model.intyp);
         //sci2exp([model.out model.out2]);
         //sci2exp(model.outtyp);
         //sci2exp(model.evtin);
         //sci2exp(model.evtout);
         //sci2exp(model.state);
         //sci2exp(model.dstate);
         //sci2exp(model.odstate);
         //sci2exp(model.rpar);
         //sci2exp(model.ipar);
         //sci2exp(model.opar)];
         //sci2exp(model.nmode);
         //sci2exp(model.nzcross);
         //sci2exp(model.firing);
         //'y';'n'
         "out0"; "TimedFloat"; "[1 1]"];
  gr_i=['xstringb(orig(1),orig(2),''OUTPORT'',sz(1),sz(2));']

  x=standard_define([2 2],model,label,gr_i)
end
endfunction

