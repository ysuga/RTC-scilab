
@set VS9_HOME=%VS90COMNTOOLS%\..\..\
@set PATH=%VS9_HOME%VC\vcpackages;%PATH%
@set VC_VERSION=Visual C++ 2008

@ vcbuild /clean RTCscilab_vc9.sln
@ rm RTCscilabd.dll
@ rm RTCscilab.dll
@ rm Release
@ rm RTCscilab\rtm_config.vsprops
@ rm -r Release
@ rm -r Debug
@ cd RTCscilab
@ rm -r Release
@ rm -r Debug
@ cd ..

