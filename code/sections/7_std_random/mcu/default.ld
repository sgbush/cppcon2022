



ENTRY(Reset_Handler)

/* AXI SRAM (512kB) */
AXISRAM_Origin = 0x24000000;
AXISRAM_Length = 0x80000;

/* DTCM RAM (128kB) */
DTCM_Origin = 0x20000000;
DTCM_Length = 0x20000;

/* ITCM RAM (64kB) */
ITCM_Origin = 0x00000000;
ITCM_Length = 0x10000;

/* SRAM1 (128kB) */
AHBSRAM1_Origin = 0x30000000;
AHBSRAM1_Length = 0x20000;

/* SRAM2 (128kB) */
AHBSRAM2_Origin = 0x30000000 + AHBSRAM1_Length;
AHBSRAM2_Length = 0x20000;

/* SRAM3 (32kB) */
AHBSRAM3_Origin = 0x30000000 + AHBSRAM1_Length + AHBSRAM2_Length;
AHBSRAM3_Length = 0x8000;

/* SRAM4 (64kB) */
AHBSRAM4_Origin = 0x38000000;
AHBSRAM4_Length = 0x10000;

/* flash (2048kB) */
Flash_Origin = 0x08000000;
Flash_Length = 0x200000;

/* boot ROM */
BootROM_Origin = 0x1FF00000;
BootROM_Length = 0x20000;

/* LP SRAM (4kB) */
LPSRAM_Origin = 0x38800000;
LPSRAM_Length = 0x1000;

/* place stack in DTCM */
EndOfStack = DTCM_Origin + DTCM_Length;
StackMinSize = 0x1000;

/* heap size (see section placement below) */
HeapSize = 0x1000;


MEMORY
{
    AXISRAM (rwx)       : ORIGIN = AXISRAM_Origin,   LENGTH = AXISRAM_Length
    DTCM (rwx)          : ORIGIN = DTCM_Origin,      LENGTH = DTCM_Length
    ITCM (rwx)          : ORIGIN = ITCM_Origin,      LENGTH = ITCM_Length
    SRAM1 (rwx)         : ORIGIN = AHBSRAM1_Origin,  LENGTH = AHBSRAM1_Length
    SRAM2 (rwx)         : ORIGIN = AHBSRAM2_Origin,  LENGTH = AHBSRAM2_Length
    SRAM3 (rwx)         : ORIGIN = AHBSRAM3_Origin,  LENGTH = AHBSRAM3_Length
    SRAM4 (rwx)         : ORIGIN = AHBSRAM4_Origin,  LENGTH = AHBSRAM4_Length
    FLASH (rx)          : ORIGIN = Flash_Origin,     LENGTH = Flash_Length
}



SECTIONS
{

    .isr_vector : 
    { 
        StartOfVectors = . ;
        KEEP( *(.isr_vector) ) 
        EndOfVectors = . ;
    } >FLASH

    .text : 
    { 
        StartOfCode = . ;

        *(.text) 
        *(.text.*) 
        KEEP( *(.init) ) 
        KEEP( *(.fini) ) 

        EndOfCode = . ;
        SizeOfCode = EndOfCode - StartOfCode;
    } >FLASH

    .rodata : 
    { 
        StartOfConstants = . ;

        *(.rodata) 
        *(.rodata.*) 

        EndOfConstants = . ;
        SizeOfConstants = EndOfConstants - StartOfConstants;
    } >FLASH

    .ARM.extab : 
    { 
        *(.ARM.extab* .gnu.linkonce.armextab.*) 
    } >FLASH

    .ARM : 
    { 
        __exidx_start = . ;
         *(.ARM.exidx*)
          __exidx_end = . ;
    } >FLASH

    .preinit_array  :
    {
        PROVIDE_HIDDEN (__preinit_array_start = .);
        KEEP (*(.preinit_array*))
        PROVIDE_HIDDEN (__preinit_array_end = .);
    } >FLASH

    .init_array :
    {
        PROVIDE_HIDDEN (__init_array_start = .);
        KEEP (*(SORT(.init_array.*)))
        KEEP (*(.init_array*))
        PROVIDE_HIDDEN (__init_array_end = .);
    } >FLASH

    .fini_array :
    {
        PROVIDE_HIDDEN (__fini_array_start = .);
        KEEP (*(SORT(.fini_array.*)))
        KEEP (*(.fini_array*))
        PROVIDE_HIDDEN (__fini_array_end = .);
    } >FLASH

    InitializationData = LOADADDR(.data);

    .data : 
    {
        . = ALIGN(4);
        StartOfData = . ;

        *(.data)
        *(.data*)

        . = ALIGN(4);
        EndOfData = .;
        SizeOfData = . - StartOfData;
    } >DTCM AT>FLASH

    .bss :
    {
        . = ALIGN(4);
        StartOfBSS = . ;

        *(.bss)
        *(.bss*)
        *(COMMON)

        . = ALIGN(4);
        EndOfBSS = . ;
        SizeOfBSS = EndOfBSS - StartOfBSS;
    } >DTCM

    .heap :
    {
        . = ALIGN(8);
        HeapStart = . ;
        end = . ;
        . = . + HeapSize;
        . = ALIGN(8);
        HeapEnd = . ;
    } >AXISRAM

    .stack :
    {
        . = ALIGN(8);
        StartOfStack = . ;
        . = . + StackMinSize;
        . = ALIGN(8);
        SizeOfStack = EndOfStack - StartOfStack;
    } >DTCM


}







