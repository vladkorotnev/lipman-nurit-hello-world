@echo off
rem *****************************************************
rem *                                                   *
rem *     Batch file to run the MetaWare SeeCode        *
rem *     debugger                                      *
rem *                                                   *
rem *****************************************************
@echo on
scarm -load=0x100040 -startup=sc.cmd -nogoifmain -OK -toggle=include_local_symbols=1 -off=download -on=program_zeros_bss -wiggler -adapter=Raven -io=LPT1 -speed=1 -startup_mode=0xd3 -mem=0x20_000 -chipinit=asicinit.cmd debug\demo.elf