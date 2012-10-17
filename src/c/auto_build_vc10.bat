@for /f "skip=2 tokens=2*" %%A in ('reg query HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\MSBuild\ToolsVersions\4.0 /v MSBuildToolsPath') do @set FILE=%%B

%FILE%\MSbuild RTCscilab_vc10.sln /p:Configuration="Release"
@rem vcbuild RTCscilab_vc9.sln "Release|Win32"

