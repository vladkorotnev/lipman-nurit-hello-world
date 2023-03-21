#
# Metaware linker commnad file
#

LOAD ..\..\nos_api\lip_crt.o
LOAD ..\..\nos_api\libnos.a

# DLMs


# Standard library

LOAD D:\HCARM\LIB\BE\THUMB\PIC\LIBC.A
LOAD D:\HCARM\LIB\BE\THUMB\PIC\LIBHL.A
LOAD D:\HCARM\LIB\BE\THUMB\PIC\LIBMW.A

# Memory map

SECTIONS {

        GROUP ADDRESS 0x50040 : {
              .rodata1 : {applhead.o}
              .text?: {lip_crt.o}
              
              * (TEXT): {}
              * (LIT): {}
              }

        GROUP: {
              RW_data_Base=.;
              .sdatai?: {}
              .sdata?: {}
               sb$$adcons?: {} 
              .sbss?: { * {.sbss} }
              *(DATA): {}
              C$$zidata? : { * { TYPE bss } }
              static_data_size = .-RW_data_Base;
              }

}
