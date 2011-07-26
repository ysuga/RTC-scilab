



@set VS9_HOME=%VS90COMNTOOLS%\..\..\
@set PATH=%VS9_HOME%VC\vcpackages;%PATH%
@set VC_VERSION=Visual C++ 2008

@ cd RTCscilab
@ call copyprops.bat
@ cd ..
@rem vcbuild /M2 /rebuild RTCscilab_vc9.sln
@ vcbuild /M2 RTCscilab_vc9.sln "Release|Win32"

