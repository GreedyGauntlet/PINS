@echo off
PUSHD ..
call vendor\premake\bin\WINpremake5.exe vs2019
POPD
pause