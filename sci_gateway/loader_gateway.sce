// This file is released into the public domain
// Generated by builder_gateway.sce: Please, do not edit this file
//

try
  v = getversion('scilab');
catch
  v = [ 5 0 ]; // or older 
end
if (v(1) <= 5) & (v(2) < 2) then
  // new API in scilab 5.2
  error(gettext('Scilab 5.2 or more is required.'));
end

sci_gateway_dir = get_absolute_file_path('loader_gateway.sce');
current_dir     = pwd();

chdir(sci_gateway_dir);
if ( isdir('c') ) then
  chdir('c');
  exec('loader.sce');
end

chdir(current_dir);
// ====================================================================
clear sci_gateway_dir;
clear current_dir;
// ====================================================================
