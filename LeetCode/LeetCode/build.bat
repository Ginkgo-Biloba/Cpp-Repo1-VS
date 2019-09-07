@echo off

call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat" x86

set compilerflags=/Od /Zi /EHsc /W4

set linkerflags=/out:leetcode.exe

cl.exe %compilerflags% leetcode.cpp /link %linkerflags%
