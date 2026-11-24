@echo off
setlocal

set CFLAGS=-std:c++20 -nologo -WX -W4 -wd4100 -wd4189 -wd4505 -Zi

mkdir build
pushd build

cl %CFLAGS% ..\main.cpp

popd
