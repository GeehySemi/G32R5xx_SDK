FILE:    readme.txt
TITLE:   Fixed-Point DSP examples - code region and linker notes
VERSION: 1.0.0
DATE:    2026-06-30

Fixed-Point DSP Examples - Code Execution Region
============================================================

Overview
------------------------------------------------------------
Application code placement is listed per example and per toolchain (MDK,
IAR, Eclipse). Values reflect the linker script configured in each IDE
project.

  ITCM       - code at 0x00000000 (g32r502xc_itcm_ram_noramvector.*)
  CBUS Flash - code at 0x08000000 (g32r502xc_cbus_flash_noramvector.*)

Some examples use ITCM on MDK/IAR and CBUS Flash on Eclipse because the
Eclipse link step produces a larger image for the same sources.

Interrupt / RAM vector table
------------------------------------------------------------
All examples below use *_noramvector.* linker scripts. They do NOT reserve
DTCM or ITCM space for .bss.ram.intvec (runtime NVIC RAM vector table).
Benchmarks do not call Interrupt_initVectorTable() or Interrupt_register().

These examples are intended for algorithm validation and cycle measurement
only. For product firmware that uses Interrupt_initModule(),
Interrupt_initVectorTable(), and peripheral interrupts, copy the general
linker templates (without *_noramvector*) and follow the integration
template:

  driverlib/g32r502/examples/eval/empty_projects/empty_mathlib_project

See device_support/g32r502/common/{sct,icf,ld}/readme.txt for script
selection and vector-table options.

DWT cycle count (CYCCNT)
------------------------------------------------------------
These examples report elapsed cycles through the DWT cycle counter. Code
linked to ITCM runs from TCM with fixed low latency; code linked to CBUS
Flash is fetched from flash and is typically slower. For the same C
source, MDK/IAR (ITCM) and Eclipse (CBUS Flash) cycle counts are therefore
not directly comparable unless all toolchains use the same linker region.

Examples
------------------------------------------------------------
No.  Example                          MDK          IAR          Eclipse     
------------------------------------------------------------
1    FixedPoint_BRevAcq               ITCM         ITCM         CBUS Flash  
2    FixedPoint_CFFT                  CBUS Flash   CBUS Flash   CBUS Flash  
3    FixedPoint_FIR16                 ITCM         ITCM         CBUS Flash  
4    FixedPoint_FIR16_Alt             ITCM         ITCM         CBUS Flash  
5    FixedPoint_FIR32                 ITCM         ITCM         CBUS Flash  
6    FixedPoint_FIR32_Alt             ITCM         ITCM         CBUS Flash  
7    FixedPoint_IIR16                 ITCM         ITCM         CBUS Flash  
8    FixedPoint_IIR32                 ITCM         ITCM         CBUS Flash  
9    FixedPoint_RFFT                  CBUS Flash   CBUS Flash   CBUS Flash  
10   FixedPoint_Win                   CBUS Flash   CBUS Flash   CBUS Flash  
------------------------------------------------------------
