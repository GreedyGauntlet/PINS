@echo off
PUSHD ..
call vendor\premake\bin\premake5.exe vs2019
POPD
pause