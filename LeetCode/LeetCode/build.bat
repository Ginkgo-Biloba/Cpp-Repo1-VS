@echo off

call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat" x86

set compilerflags=/Od /Zi /EHsc /W4

set linkerflags=/out:lcvsc.exe

cl.exe %compilerflags% lcvsc.cpp /link %linkerflags%
