// This file is released into the public domain
// Generated by builder.sce : Please, do not edit this file
// cleaner.sce
// ------------------------------------------------------
curdir = pwd();
cleaner_path = get_file_path('cleaner.sce');
chdir(cleaner_path);
// ------------------------------------------------------
//if fileinfo('loader.sce') <> [] then
//  mdelete('loader.sce');
//end
// ------------------------------------------------------
//if fileinfo('Makelib.mak') <> [] then
//  unix_s('nmake /Y /nologo /f Makelib.mak clean');
//  mdelete('Makelib.mak');
//end
// ------------------------------------------------------
//if fileinfo('libcsum.dll') <> [] then
//  mdelete('libcsum.dll');
//end


if MSDOS then,

if fileinfo('RTCscilab.dll') <> [] then
  unix("auto_clean_vc9.bat");
  unix("auto_clean_SimulationEC_vc9.bat");
end

else,

end;

// ------------------------------------------------------
chdir(curdir);
// ------------------------------------------------------
