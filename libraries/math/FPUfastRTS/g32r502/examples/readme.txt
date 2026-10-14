FILE:    readme.txt
TITLE:   FPUfastRTS examples - code region and linker notes
VERSION: 1.0.0
DATE:    2026-06-30

FPUfastRTS Examples - Code Execution Region
============================================================

Overview
------------------------------------------------------------
Application code for every example below is linked to ITCM
(0x00000000) on MDK, IAR, and Eclipse.
Linker scripts: g32r502xc_itcm_ram_noramvector.sct /
g32r502xcx7_itcm_ram_noramvector.icf / g32r502xc_itcm_ram_noramvector.ld.

Interrupt / RAM vector table
------------------------------------------------------------
These examples use *_noramvector.* scripts. They do NOT reserve RAM for
.bss.ram.intvec and do not use Interrupt_initVectorTable().

Examples are for benchmark and library validation only. For product
firmware with NVIC interrupts, use general linker templates and follow:

  driverlib/g32r502/examples/eval/empty_projects/empty_mathlib_project

See device_support/g32r502/common/{sct,icf,ld}/readme.txt.

Examples
------------------------------------------------------------
No.  Example                                 
------------------------------------------------------------
1    atan2_f32                               
2    atan_f32                                
3    cos_f32                                 
4    div_f32                                 
5    exp_f32                                 
6    isqrt_f32                               
7    log_f32                                 
8    pow_f32                                 
9    sin_f32                                 
10   sincos_f32                              
11   sqrt_f32                                
------------------------------------------------------------
