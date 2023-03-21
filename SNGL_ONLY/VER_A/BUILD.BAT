@echo off
rem *****************************************************
rem *                                                   *
rem *     Batch file to build the demo application      *
rem *                                                   *
rem *****************************************************
@echo off

REM Set PATH pointing to directory where hcarm.exe is installed
set PATH=%PATH%;D:\HCARM\BIN


REM Set HCDIR pointing to the base arm installation directory
set HCDIR=D:\HCARM

REM Set LM_LICENSE_FILE pointing to the path and file name of the license file 
set LM_LICENSE_FILE=D:\HCARM\bin\license.dat

hcarm -c ..\src\applhead.c -o release\obj\applhead.o -Hliteral_pointers -Hthumb -Hoff=Char_default_unsigned -HB -Hoff=Word_align_vars
pause

hcarm -c ..\src\demo.c -o release\obj\demo.o -Hoff=recognize_library -Os -Hpic -Hthumb -Hoff=Char_default_unsigned -Hinterwork -HB -Hoff=Word_align_vars -Hon=Version3M -Hon=Version4 -Hefile=demo.log
pause

ldarm release\obj\applhead.o release\obj\demo.o linker.cmd -z dup -zpurgetext -Xnocompress -Bpictable -Bcopydata -Csymbols -Cglobals -o release\demo.elf -m >release\demo.map
pause

elf2hex release\demo.elf -o release\demo.hex
pause

if exist release\demo.elf del release\demo.elf
pause