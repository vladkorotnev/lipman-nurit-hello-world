@echo off
rem *****************************************************
rem *                                                   *
rem *     Batch file to build the demo application      *
rem *     for a debug session                           *
rem *                                                   *
rem *****************************************************
@echo on

hcarm -g -c ..\src\applhead.c -o debug\obj\\applhead.o -Hliteral_pointers -Hthumb -Hoff=Char_default_unsigned -HB -Hoff=Word_align_vars
pause

hcarm -g -c ..\src\demo.c -o debug\obj\demo.o -Hoff=recognize_library -Hpic -Hthumb -Hoff=Char_default_unsigned -Hinterwork -HB -Hoff=Word_align_vars -Hon=Version3M -Hon=Version4 -Hefile=demo.log
pause

ldarm debug\obj\applhead.o debug\obj\demo.o linker.cmd -z dup -zpurgetext -Xnocompress -Bpictable -Bcopydata -Csymbols -Cglobals -o debug\demo.elf -m >debug\demo.map
pause

elf2hex debug\demo.elf -o debug\demo.hex
pause