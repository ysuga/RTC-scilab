// ====================================================================
// Allan CORNET
// Simon LIPP
// INRIA 2008
// This file is released into the public domain
// ====================================================================

src_c_path = get_absolute_file_path('builder_c.sce');

CFLAGS = "-I" + src_c_path;

//tbx_build_src(['csum','csub'], ['csum.c','csub.c'], 'c', ..
//              src_c_path, '', '', CFLAGS);


//chdir(src_c_path + "RTCscilab");
chdir(src_c_path);
if MSDOS then,
unix("auto_build_vc9.bat");
unix("auto_build_SimulationEC_vc9.bat");
else,
unix("bash ./auto_build.sh");
end;

//msbuild = """C:\Program Files (x86)\Microsoft Visual Studio 9.0\VC\vcpackages\vcbuild """;
//msbuild = "c:\windows\Microsoft.NET\Framework\v4.0.30319\MSBuild  ";
///unix(msbuild + src_c_path + "RTCscilab\RTCscilab.vcproj Release");

clear tbx_build_src;
clear src_c_path;
clear CFLAGS;
